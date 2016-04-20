/**********************************************************************************************************
Nom du fichier: LIB_BSE_GPIO
Auteurs: DAVID Quentin, HU Weiyi
Date de dernière modification: 06/10/2015
Version: 1
Objectifs du code: L'objectif de ce code est de faire la configuration des ports entrées sorties
***********************************************************************************************************/

//Includes--------------------------------------
#include <c8051f020.h>
#include <Declarations_GPIO_BSE.h>
#include <intrins.h>
#include <LIB_BSE_GPIO.h>
//---------------------------------------

sbit P1__0 = P1^2;
//Fonctions----------------------------------------
void Config_GPIO() 
{
	  //P0MDOUT   |= 0x01; //P0.0 en sortie (Tx de UART0)
    P0MDOUT   = 0x01; //P1.0 en sortie PushPull
	

    XBR0      = 0x08;
    XBR2      = 0x40;
	
		//P1__2=1;

}




void Init_GPIO(void)
{
	Config_GPIO();
	
}