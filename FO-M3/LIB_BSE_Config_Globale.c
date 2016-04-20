
/**********************************************************************************************************
FO_M3
***********************************************************************************************************/

//Includes

//--------------------------------------
#include <c8051f020.h>
#include <Declarations_GPIO_BSE.h>
#include <LIB_BSE_Config_Globale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//---------------------------------------

//Declarations Globales

char Angle_actuel_H;


#define vit_angulaire 0.18

#define SYSCLK 22118400

//Fonctions----------------------------------------


void Reset_Sources_Init()
{
	EA=0;
	WDTCN = 0xDE;
	WDTCN = 0xAD;
	EA=1;
}


void Init_CLK()
{
		int i;
	   OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    OSCICN    = 0x0C;
	
}


void Init_Device (void) 
{

	Reset_Sources_Init();
  Init_CLK();
	Init_PCA();
	
}
void Init_PCA (void) 
{

	PCA0CN=0x40;
	PCA0MD=0x08;
	PCA0CPM0=0xC2;
	
	
}



unsigned int CDE_Servo_H (char Angle){
	
	int ang=Angle;
	unsigned long int compteur_max = 65536;
	float duree_totale = 2962;//compteur_max / (SYSCLK); // en microseconde

	int masque = 0x00FF;
	int impulse_max = 2400;
	int impulse_min = 600;
	/*if(Angle > 90) 
		Angle = 90;
	if(Angle < -90) 
		Angle = -90;*/
	
	float largeur_impulse;
	float duty_cycle;
	unsigned int angle_effectif;
	int	T;
	unsigned long int valeur; 
	
	largeur_impulse	= (ang+90)*(float)(impulse_max-impulse_min)/180+impulse_min; // en microseconde
	duty_cycle = largeur_impulse /duree_totale;
	valeur = compteur_max*(1-duty_cycle);
	
	PCA0CPH0=(valeur>>8)&masque;
	PCA0CPL0=(valeur&masque);
	
	angle_effectif = abs(Angle - Angle_actuel_H);
	
	Angle_actuel_H=Angle;
	
	T=(vit_angulaire*angle_effectif/60)*1000;// T en milli
	
	return T;
}
