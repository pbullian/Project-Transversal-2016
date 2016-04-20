//------------------------------------------------------------------------------------
//LIB_BSE_ADC.c
//------------------------------------------------------------------------------------
//
// AUTH: Farineau Camille - Ngattai Lam Prince
// DATE: 14/10/2015
// Target: C8051F020
//
// Tool chain: KEIL PK51

// Includes
//-----------------------------------------------------------------------------
#include <c8051f020.h> 
#include <LIB_BSE_ADC.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------
//------------------------------------------------------------------------------------
// Global CONSTANTS
//------------------------------------------------------------------------------------




void CFG_VREF(void)
{
	REF0CN=0x03; //autorise l'ADC et la r�ference vref provient de VREF pin avec VREF=2.4V
}


//*****************************************************************************	 
//Cfg_ADC0
//
//	 Configuration de l'ADC0
// 
//*****************************************************************************
void CFG_ADC0(void)
{
		AMX0SL    = 0x03;// Grace au tableau page 48 la configuration associ�e aux 4 bits de poids faible de 			                            //ADC0CF est la combinaison 0011 soit 03 en h�xad�cimal.
		AMX0CF		&=0xF0; // Ce registre permmet de mettre les les Inputs AIN2 et AIN3 en unipolaire 					//et non en bipolaire
    ADC0CF    = 0xA8; // On configure la clock permettant de cadencer la conversion de l'ADC 
		    // Le choix du Gain est de 1 car lors de nos simulations nous g�n�rons un signal de 0-3V
    ADC0CN    = 0x81; // Registre de controle de L'ADC 
		    // La fin de la conversion est donn�e par le passage � 1 de AD0INT.
		    // AD0BUSY g�n�re un 1 sur AD0INT sur front descendant lorsque la conversion est termin�e
		    //La conversion est initialis�e � chaque fois que l'on �crit 1 dans AD0BUSY
		    //ADC0L is left justified
}


//*****************************************************************************	 
//ACQ_ADC
//
//	 La conversion est d�clench�e par �criture dans DAC0H (Fonction Send_to_DAC0)
// 
//*****************************************************************************
unsigned char ACQ_ADC(void) 
{
	AD0INT=0;
	AD0BUSY=1; // La conversion a commenc�
	while(AD0INT!=1){} //On attend qeu le front descendant de AD0BUSY d�clenche la mise � 1 de AD0INT pour que 			  //la conversion soit termin�e
	AD0INT=0;
	return ADC0H;	// On retourne la veleur convertie.
	}
float Conversion (float TensHexa)
{
	float Tension2 = (TensHexa/75);
		
	float Distance=166.38*exp(-0.892*Tension2);
	return Distance;
}