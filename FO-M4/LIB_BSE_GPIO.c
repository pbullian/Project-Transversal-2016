//------------------------------------------------------------------------------------
//LIB_BSE_GPIO.c
//------------------------------------------------------------------------------------
//
// AUTH: Farineau Camille - Ngattai Lam Prince
// DATE: 07/10/2015
// Target: C8051F020
//
// Tool chain: KEIL PK51

// Includes
//-----------------------------------------------------------------------------
#include <LIB_BSE_GPIO.h>
//-----------------------------------------------------------------------------

void Config_GPIO()
{
    XBR0      = 0x11; // Activation du UART0 sur P0.0 et P0.1
    XBR2      = 0x40; // Activation du Crossbar
}

