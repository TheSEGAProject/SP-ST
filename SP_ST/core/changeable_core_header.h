///////////////////////////////////////////////////////////////////////////////
//! \file changeable_core_header.h
//! \brief The header file for the core that a user is allowed to change and
//!	adjust settings.
//!
//!
//! @addtogroup core
//! @{
//!
//! @addtogroup hdr Core Changeable Header
//! This is the header file that should be adjusted so the core can be used
//! with any SP Board transducer functions.
//! @{
///////////////////////////////////////////////////////////////////////////////
//*****************************************************************************
// By: Samuel Boegli
//     Wireless Networks Research Lab
//     Dept of Electrical Engineering, CEFNS
//     Northern Arizona University
//
//	edited by CP
//*****************************************************************************

#ifndef CHANGEABLE_CORE_HEADER_H_
#define CHANGEABLE_CORE_HEADER_H_

//! @name SP Board Software Version Variable
//!
//! @{
//!\def SOFTWAREVERSION
//! \brief The software version running on the SP Board. Not the Core version.
#define SOFTWAREVERSION "SP-ST v1.53   "
//! @}

//! @name SP Board ID Variables
//! These variables are used to store the name of the SP Board.
//! @{
#define  ID_PKT_HI_BYTE1	0x53;
#define  ID_PKT_LO_BYTE1	0x54;
#define  ID_PKT_HI_BYTE2	0x00;
#define  ID_PKT_LO_BYTE2	0x00;
#define  ID_PKT_HI_BYTE3	0x00;
#define  ID_PKT_LO_BYTE3	0x00;
#define  ID_PKT_HI_BYTE4	0x00;
#define  ID_PKT_LO_BYTE4	0x00;
//!@}

//! @name I/O Port Setups
//! In some cases the I/O Ports must be defined by the Application Layer
//! Make those defines here. If no change is needed, use 'DEF'
//!
//! @{
#define 	CoreP1DIR	0xFD  //0xE3
#define 	CoreP1OUT	0x00
#define		CoreP1REN	0xFC
#define		CoreP1SEL	0x00

#define 	CoreP2DIR	0xFB
#define 	CoreP2OUT	0x01
#define		CoreP2REN	0xFA
#define		CoreP2SEL	0x00

#define 	CoreP3DIR	0x00
#define 	CoreP3OUT	0x00
#define		CoreP3REN	0xFF
#define		CoreP3SEL	0x00

#define 	CoreP4DIR	0x78
#define 	CoreP4OUT	0x78
#define		CoreP4REN	0x87
#define 	CoreP4SEL	0x00

#define 	CoreP5DIR	0x0B
#define 	CoreP5OUT	0x09
#define		CoreP5REN	0xF4
#define		CoreP5SEL	0x00

#define 	CoreP6DIR	0x00
#define 	CoreP6OUT	0x00
#define		CoreP6REN	0x07
#define		CoreP6SEL	0x7C
//!@}

// Functions visible to the core.  Adding these functions makes the core scalable to any application
// since the core does not need to know anything about the specifics of the application layer.
uint8 ucMain_FetchData(volatile uint8 * pBuff);
void vMain_FetchLabel(uint8 ucTransNum, volatile uint8 * pucArr);
uint16 uiMainDispatch(uint8 ucCmdTransNum, uint8 ucCmdParamLen, uint8 *ucParam);
uint8 ucMAIN_ReturnSensorType(uint8 ucSensorCount);
void vMAIN_RequestSensorType(uint8 ucChannel);
uint8 ucMain_getNumTransducers(void);
uint8 ucMain_getSampleDuration(uint8 ucTransNum);
uint8 ucMain_getTransducerType(uint8 ucTransNum);
void vMain_EventTrigger(void);
uint8 ucMain_ShutdownAllowed(void);
#endif /* CHANGEABLE_CORE_HEADER_H_ */

