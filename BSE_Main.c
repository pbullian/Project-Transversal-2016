//------------------------------------------------------------------------------------
// BSE_Main.c
//------------------------------------------------------------------------------------
// AUTH:PEREL/BULLIAN
// DATE:15/03/2016
//
// Target: C8051F02x
// Tool chain: KEIL Eval 'c'
//
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
//#include <stdio.h>   
#include <c8051f020.h>  										// SFR declarations
#include <LIB_BSE_Config_Globale.h>
#include <LIB_BSE_GPIO.h>
#include <LIB_BSE_UART.h>

//----------------------------------------------------------------------------
// Reponse
//----------------------------------------------------------------------------
void Reponse(void)
{
	xdata char car_recu;
	car_recu=getchar();   										//Reception du caractere
	if(car_recu=="R"||car_recu=='r')					//Controle de la réponse aux caractères 'r' et 'R' uniquement
	{
		Send_String("Nombre de Colis detectes :");
		Send_String(&nbr_colis);
		Send_String("\0");
	}
}
void main (void) {
 
   Init_Device();  													// Initialisation du microcontrôleur
	 Port_IO_Init();
	 CFG_Clock_UART1();
	 CFG_UART1();
	 
//------------------------------------------------------------------------------------
// TEST
//------------------------------------------------------------------------------------	
	while(1)
	{
		Reponse();
	}
}