///////////////////////////////////////////////////////////////////////////////
//! \file Thermo.h
//! \brief Header file for the thermo application code
//!
//! This file provides all of the defines and function prototypes for the
//! \ref SPTC
//!
//! @addtogroup SPTC
//! The thermo application code runs an SPTC to allow temperature readings to be taken
//! @{
//!
///////////////////////////////////////////////////////////////////////////////
//*****************************************************************************
// By: Nicholas Rowe
//     Wireless Networks Research Lab
//     Dept. of Electrical Engineering, CEFNS
//     Northern Arizona University
//
//*****************************************************************************
#ifndef SP_ST_1_THERMO_H_
#define SP_ST_1_THERMO_H_

//! \name VREF_Port
//! these defines allow the VREF port to be addressed by the VREF port name
//! \def VREF_PIN
//! \brief Defines the port which the VREF pin is on
#define VREF_PIN BIT1
//! \def VREF_EN
//! \brief set up the output port name for VREF
#define VREF_EN P5OUT
//! \def VREF_EN_DIR
//! \brief sets up the DIR port name for VREF
#define VREF_EN_DIR P5DIR
//! \def VREF_EN_SEL
//! \brief sets up the SEL port name for VREF
#define VREF_EN_SEL P5SEL

//! \name CJC_port
//! These defines set up the cold junction compensator circuitry
//! \def CJC_PIN
//! \brief defines the name for the CJC_PIN port number
#define CJC_PIN BIT0
//! \def CJC_EN
//! \brief defines the name for CJC output port
#define CJC_EN P5OUT
//! \def CJC_EN_DIR
//! \brief defines the name for the CJC DIR port number
#define CJC_EN_DIR P5DIR
//! \def CJC_EN_SEL
//! \brief defines the name for the CJC SEL port number
#define CJC_EN_SEL P5SEL

//! \name ZERO_port
//! These defines set up the Zero/offset port
//! \def Zero_PIN
//! \brief defines the name for the Zero_PIN port number
#define ZERO_PIN BIT3
//! \def Zero_EN
//! \brief defines the name for the Zero output enable port number
#define ZERO_EN P5OUT
//! \def Zero_EN_DIR
//! \brief defines the name for the Zero DIR port number
#define ZERO_EN_DIR P5DIR
//! \def Zero_EN_SEL
//! \brief defines the name for the Zero select port number
#define ZERO_EN_SEL P5SEL

//! \name TC_port
//! These defines set up the CH4-CH1 port for the thermocouples
//! \def CH4_ENABLE_BIT
//! \brief defines the name for the CH4 EN pin
#define CH4_ENABLE_BIT BIT6
//! \def CH3_ENABLE_BIT
//! \brief defines the name for the CH3 EN pin
#define CH3_ENABLE_BIT BIT5
//! \def CH2_ENABLE_BIT
//! \brief defines the name for the CH2 EN pin
#define CH2_ENABLE_BIT BIT4
//! \def CH1_ENABLE_BIT
//! \brief defines the name for the CH1 EN pin
#define CH1_ENABLE_BIT BIT3

//! \def EN_CH
//! \brief defines the name for the TC EN port
#define EN_CH P4OUT
//! \def EN_CH_DIR
//! \brief defines the name for the TC port direction
#define EN_CH_DIR P4DIR
//! \def EN_CH_SEL
//! \brief defines the name for the TC port select
#define EN_CH_SEL P4SEL

//! \name ADC_INPUT PORT
//! These defines set up the ADC input port
//! \def TC_CH_PORT
//! \brief defines the name for the adc input port
#define TC_CH_PORT P6OUT
//! \def TC_CH_DIR
//! \brief defines the name for the adc input port direction
#define TC_CH_DIR P6DIR
//! \def TC_CH_SEL
//! \brief defines the name for the adc input port select
#define TC_CH_SEL P6SEL


//! @name Initalization Functions
//! These functions handle board initialization
//! @{
void vPortNMemInit();
void vADCInit();
//! @}

//! @name Sensor Functions
//! These functions handle taking data readings
//! @{
unsigned int uiThermo_ReadChannel(unsigned char ucChannel);
void vZeroReading(); //just the offset with no thermocouple in series
void vThermistorReading();
//! @}


#endif /* SP_ST_1_THERMO_H_ */
//! @}
