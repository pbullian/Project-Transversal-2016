//------------------------------------------------------------------------------------
//LIB_BSE_Config_Globale
//------------------------------------------------------------------------------------
//
// AUTH: Farineau Camille - Ngattai Lam Prince
// DATE: 07/10/2015
// Target: C8051F020
//
// Tool chain: KEIL PK51
//#include <c8051f020.h> 
#include <LIB_BSE_Config_Globale.h>
#include <Declarations_GPIO_BSE.h>


void Init_Device (void)
{
	Ports_Init ();
	Reset_Init ();
	
}

void Ports_Init (void)
{
	P2MDOUT &=~(0x04); //P2.2
	P2__2=1;
}

void Reset_Init (void)
{
	EA=0; // Desactivation des interruptions
	WDTCN = 0xDE; // Desactivation 
	WDTCN = 0xAD; // du Watchdog
}