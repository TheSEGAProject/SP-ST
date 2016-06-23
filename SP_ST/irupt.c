/*
 * irupt.c
 *
 *  Created on: Jun 26, 2013
 *      Author: Christopher Porter
 */

#include <msp430x23x.h>
#include "core.h"
#include "comm.h"

// Timer B is used as a low-power delay module
#pragma vector=TIMERB1_VECTOR
__interrupt void TIMERB1_ISR(void)
{
	switch (TB0IV)
	{
	case TA0IV_NONE:
		break;
	case TBIV_TBCCR1:  // used for the low power mode delay in thermo.c
		__bic_SR_register_on_exit(LPM4_bits);
		break;
	case TBIV_TBCCR2:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
//!   \brief Port 1 interrupt service routine
//!
//! Used for both transducer debugging and bit-banging
//!
//!   \param none
//!   \return none
///////////////////////////////////////////////////////////////////////////////
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
	if (P1IFG & SDA_PIN) {
		P_SDA_IFG &= ~SDA_PIN;
		__bic_SR_register_on_exit(LPM4_bits);
	}

}

//Unused interrupts require a function at the vector to avoid the PC pointing to empty memory space
#pragma vector=COMPARATORA_VECTOR
__interrupt void COMPARATORA_ISR(void)
{}

#pragma vector=NMI_VECTOR
__interrupt void NMI_ISR(void)
{}

#pragma vector=TIMERA1_VECTOR
__interrupt void TIMERA1_ISR(void)
{}

#pragma vector=TIMERB0_VECTOR
__interrupt void TIMERB0_ISR(void)
{}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{}

#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{}



