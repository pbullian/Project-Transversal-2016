/**********************************************************************************************************
Nom du fichier: Test
Auteurs: DAVID Quentin, HU Weiyi
Date de dernière modification: 04/11/2015
Version: 5
Objectifs du code: Ce code est le main.
***********************************************************************************************************/

//Includes

//--------------------------------------
#include <c8051f020.h>
#include <Declarations_GPIO_BSE.h>
#include <LIB_BSE_Config_Globale.h>
#include <LIB_BSE_GPIO.h>


//---------------------------------------


//Variables------------------------------
extern char Angle_actuel_H;


//Main-----------------------------------
void main(void)
{ 

	
	char angle;
	
	unsigned int T;
	Angle_actuel_H = 0;
	Init_Device();
	Init_GPIO();
	angle = 0;
	
	
	while(1)
	{
		//Envoie du message affichant le nombre de colis lorsqu'on saisit R ou r au clavier
		
		T	= CDE_Servo_H(angle);
			
		}
	}
