//------------------------------------------------------------------------------------
//LIB_BSE_GPIO.h
//------------------------------------------------------------------------------------
//
// AUTH: Farineau Camille - Ngattai Lam Prince
// DATE: 07/10/2015
// Target: C8051F020
//
// Tool chain: KEIL PK51

// Includes
//-----------------------------------------------------------------------------
#include <Declarations_GPIO_BSE.h>
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
void Config_GPIO (void);
/*
	Objectif: Configuration des GPIO
	
*/
void Pulse_P20 (void);
void Pulse_P21 (void);
void Pulse_1ms (void);
void Demo_GPIO (void);
//-----------------------------------------------------------------------------