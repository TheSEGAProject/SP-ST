//*************************************************************************************
//
// \file Thermo.c
// \brief This is the primary run file for the Thermocopule Sattelite Processor board
//
// By:   Jeremy Anderson
//       Wireless Networks Research Lab
//       Dept. Of Electrical Engineering, CEFNS
//       Northern Arizona University
//
//
// Fixed by CP
//
//*************************************************************************************


#include "Thermo.h"
#include "msp430f235.h"

//! \var gui_ZeroReading
//! \brief global which stores the offset value
extern unsigned int gui_ZeroReading;

//! \var gui_ThermistorReading
//! \brief global which stores the thermistor value
extern unsigned int gui_ThermistorReading;

//! \def NUM_SAMPLES
//! \brief Number of samples taken by the ADC in repeat-single-channel mode
#define   NUM_SAMPLES   10

//! \var gui_ADCResults
//! \brief Array that stores the results of the ADC measurements
volatile unsigned int gui_ADCResults[NUM_SAMPLES];

//! \var guc_ADCSampleIndex
//! \brief Index into the ADC results array
static unsigned char guc_ADCSampleIndex = 0;

//! \var *ADC_GainFactor
//! \var *ADC_Offset
//! \brief ADC calibration constants
//! Each MCU can have unique calibration constants stored in memory.  An ADC reading is adjusted using the following equation:
//! ADC(adjusted) = ADC(raw)*ADC_GainFactor/2^15 + *ADC_Offset
signed int *ADC_GainFactor = (signed int*)0x10DC;
signed int *ADC_Offset = (signed int*)0x10DE;

//! \var iDivider
//! \brief Divides the ADC reading after it is multiplied by the gain factor (2^15)
signed int iDivider = 0x8000;


//////////////////////////////////////////////////
//!
//! \brief initializes the ADC for use
//!
//! This function does not use variables
//!
//////////////////////////////////////////////////
void vADCInit()
{

	VREF_EN &= ~VREF_PIN; 							// Turn on vref
	ZERO_EN |= ZERO_PIN;  							// Turn on the zero path important to keep the output non-railed
	EN_CH |= (CH4_ENABLE_BIT | CH3_ENABLE_BIT |CH2_ENABLE_BIT |CH1_ENABLE_BIT); //turn off all TC channels

	// Sample hold time = 1024 cycles, multiple sample conversion = true, internal reference off
	ADC12CTL0 = (SHT0_15 | MSC);
	ADC12CTL0 |= ADC12ON;				//Turn on the ADC

	// sample-hold = SC bit, ADC clock source = SMCLK, clock divider = 8, Repeat single channel mode
	ADC12CTL1 = (SHS_0 | SHP | ADC12SSEL_3 | CONSEQ_2 | ADC12DIV_7);

	// Selects input channel A3, and chooses external reference
	ADC12MCTL0 |=  SREF_7;
}


////////////////////////////////////////////////////////////
//!
//! \brief Enters the chosen LPM for the desired time.
//!
//!
//! \param uiDelay, ucLowPowerMode
///////////////////////////////////////////////////////////
void vThermo_LPMDelay(unsigned int uiDelay, unsigned char ucLowPowerMode)
{

	TBCTL = (TBSSEL_2 | ID_3 | TBCLR);
	TBCCR1 = uiDelay;
	TBCCTL1 &= ~CCIFG;
	TBCCTL1 |= CCIE;
	TBCTL |= MC_2;

	switch (ucLowPowerMode) {
		case 0:
			LPM0;
		break;

		case 1:
			LPM1;
		break;

		case 2:
			LPM2;
		break;

		case 3:
			LPM3;
		break;

		default:
			LPM0;
		break;

	}

	TBCCTL1 = 0x00;
	TBCTL = 0x00;
}



/////////////////////////////////////////////////////////////
//!
//! \brief Reads the requested thermocouple channel
//!
//!
//! \return uiADCTicks
//!
////////////////////////////////////////////////////////////
unsigned int uiThermo_ReadChannel(unsigned char ucChannel)
{
	unsigned int uiADCTicks;
	unsigned char ucChannelIdx;
	unsigned char ucChEnableBits[5] = {CH1_ENABLE_BIT, CH2_ENABLE_BIT, CH3_ENABLE_BIT, CH4_ENABLE_BIT};
	unsigned long ulADC_val;
	signed long lTemp;
	unsigned char ucIndex;


	ucChannelIdx = ucChannel-1;
	ZERO_EN &= ~ZERO_PIN;				//Disable Zero ref
	EN_CH &= ~ucChEnableBits[ucChannelIdx];					//Enables channel 0
	vThermo_LPMDelay(62500, 1);  		//Delay to make sure the reading is independent from last
	ADC12MCTL0 |= INCH_3;				//Put on the right ADC input
	ADC12CTL0 |= ADC12ON;				//Turn on the ADC
	ADC12CTL1 |= CSTARTADD_0;			//Sets MEM0 as the register to write to

	// Clean the ADC results array
	for (ucIndex = 0; ucIndex < NUM_SAMPLES; ucIndex++){
		gui_ADCResults[ucIndex] = 0;
	}

	// Reset the sample index
	guc_ADCSampleIndex = 0;

	// Clear interrupt flag and enable interrupts for mem0
	ADC12IFG = 0x00;
	ADC12IE = BIT0;

	// Start conversions
	ADC12CTL0 |= (ADC12SC | ENC);

	// Sleep until conversion is complete
  LPM1;

	// Disable conversions
	ADC12CTL0 &= ~(ADC12SC | ENC | ADC12ON);

	// Clear input channel for mem0
	ADC12MCTL0 &= ~INCH_3;

	ZERO_EN |= ZERO_PIN;				//Enable Zero ref
	EN_CH |= ucChEnableBits[ucChannelIdx];					//Disable channel 0

	// Average the sequence of readings
  ulADC_val = 0;
	for (ucIndex = 0; ucIndex < NUM_SAMPLES; ucIndex++)
	{
		lTemp = gui_ADCResults[ucIndex];
		lTemp *= *ADC_GainFactor;
		lTemp /= iDivider;
		lTemp += *ADC_Offset;
		ulADC_val += (unsigned long)lTemp;
	}
	uiADCTicks = (unsigned int) ulADC_val/NUM_SAMPLES;

	// Round up when required
	if((ulADC_val % 10) >= 5 )
		uiADCTicks++;

	return uiADCTicks;
}


///////////////////////////////////////////////////////////
//!
//! \brief Reads the thermocouple offset
//!
//! \param none
//!
//! \return stores the offset reading in gui_ZeroReading
//!
////////////////////////////////////////////////////////////
void vZeroReading()
{
	unsigned long ulADC_val;
	signed long lTemp;
	unsigned char ucIndex;

	ADC12MCTL0 |= INCH_3;				//Put on the right ADC input
	ADC12CTL0 |= ADC12ON;				//Turn on the ADC
	ADC12CTL1 |= CSTARTADD_0;			//Sets MEM0 as the register to write to
	vThermo_LPMDelay(62500, 1);  		//Delay to make sure the reading is independent from last
	vThermo_LPMDelay(62500, 1);  		//Delay to make sure the reading is independent from last

	// Clear ADC results buffer
	for (ucIndex = 0; ucIndex < NUM_SAMPLES; ucIndex++){
		gui_ADCResults[ucIndex] = 0;
	}

	// Reset the sample index
	guc_ADCSampleIndex = 0;

	// Clear interrupt flag and enable interrupts for mem0
	ADC12IFG = 0x00;
	ADC12IE |= BIT0;

	// Start conversions
	ADC12CTL0 |= (ADC12SC | ENC);

	// Sleep until conversion is complete
  LPM1;

	// Disable conversions and shutdown ADC
	ADC12CTL0 &= ~(ADC12SC | ENC | ADC12ON);

	// Clear input channel for MEM0
	ADC12MCTL0 &= ~INCH_3;

  // Average the sequence of readings
  ulADC_val = 0;
	for (ucIndex = 0; ucIndex < NUM_SAMPLES; ucIndex++)
	{
		lTemp = gui_ADCResults[ucIndex];
		lTemp *= *ADC_GainFactor;
		lTemp = lTemp / iDivider;
		lTemp += *ADC_Offset;
		ulADC_val += ((unsigned long)lTemp);
	}
	gui_ZeroReading = ((unsigned int) ulADC_val/NUM_SAMPLES);

	// Round up when required
	if((ulADC_val % 10) >= 5 )
		gui_ZeroReading++;
}


//////////////////////////////////////////////////////////
//!
//! \brief Reads the thermistor voltage
//!
//! \param none
//!
//! \return stores the thermistor reading in gui_ThermistorReading
//!
///////////////////////////////////////////////////////////
void vThermistorReading()
{

	unsigned long ulADC_val;
	signed long lTemp;
	unsigned char ucIndex;

	CJC_EN &= ~CJC_PIN;					//Enable thermistor
	ADC12MCTL0 |= INCH_7;				//turn on right ADC input
	ADC12CTL0 |= SHT0_7;
	ADC12CTL0 |= ADC12ON;				//Turn on the ADC
	ADC12CTL1 |= CSTARTADD_0;			//Sets MEM0 as the register to write to

	// Rise time for thermistor is approximately 3 ms at 24 degrees C , we give it some slack
	vThermo_LPMDelay(10000, 1);

	// Clear the ADC results buffer
	for (ucIndex = 0; ucIndex < NUM_SAMPLES; ucIndex++) {
		gui_ADCResults[ucIndex] = 0;
	}

	// Reset the sample index
	guc_ADCSampleIndex = 0;

	// Clear interrupt flag and enable interrupts for mem0
	ADC12IFG = 0x00;
	ADC12IE |= BIT0;

	// Start conversions
	ADC12CTL0 |= (ADC12SC | ENC);

	// Sleep until conversion is complete
  LPM1;

	// Disable thermister
	CJC_EN |= CJC_PIN;

	// Disable conversions and shutdown ADC
	ADC12CTL0 &= ~(ADC12SC | ENC | ADC12ON);

	// Deselect the channel for mem0
	ADC12MCTL0 &= ~INCH_7;

  // Average the sequence of readings
  ulADC_val = 0;
	for (ucIndex = 0; ucIndex < NUM_SAMPLES; ucIndex++)
	{
		lTemp = gui_ADCResults[ucIndex];
		lTemp *= *ADC_GainFactor;
		lTemp /= iDivider;
		lTemp += *ADC_Offset;
		ulADC_val += (unsigned long)lTemp;
	}

	gui_ThermistorReading = (unsigned int) ulADC_val/NUM_SAMPLES;

	// Round up when required
	if((ulADC_val % 10) >= 5 )
		gui_ThermistorReading++;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//!
//! \brief Triggers when an ADC reading is complete and brings the board out of LPM when
//!				 conversions are complete
//!
//////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma vector = ADC12_VECTOR;
__interrupt void ADC_Conversion(void)
{
	switch (__even_in_range(ADC12IV, 34))
	{
		case ADC12IV_NONE:
		break;
		case ADC12IV_ADC12OVIFG:
		break;
		case ADC12IV_ADC12TOVIFG:
		break;
		case ADC12IV_ADC12IFG0:
			gui_ADCResults[guc_ADCSampleIndex] = ADC12MEM0; // Move results
			guc_ADCSampleIndex++; // Increment results index

			// If we have reached the desired number of conversions then wake the CPU
			if (guc_ADCSampleIndex == NUM_SAMPLES)
			{
				// Reset the sample index
				guc_ADCSampleIndex = 0;
				ADC12IE &= ~BIT0;
				__bic_SR_register_on_exit(LPM3_bits);
			}
		break;
		case ADC12IV_ADC12IFG1:
		break;
		case ADC12IV_ADC12IFG2:
		break;
		case ADC12IV_ADC12IFG3:
		break;
		case ADC12IV_ADC12IFG4:
		break;
		case ADC12IV_ADC12IFG5:
		break;
		case ADC12IV_ADC12IFG6:
		break;
		case ADC12IV_ADC12IFG7:
		break;
		case ADC12IV_ADC12IFG8:
		break;
		case ADC12IV_ADC12IFG9:
		break;
		case ADC12IV_ADC12IFG10:
		break;
		case ADC12IV_ADC12IFG11:
		break;
		case ADC12IV_ADC12IFG12:
		break;
		case ADC12IV_ADC12IFG13:
		break;
		case ADC12IV_ADC12IFG14:
		break;
		case ADC12IV_ADC12IFG15:
		break;

	}
}

//! @}

