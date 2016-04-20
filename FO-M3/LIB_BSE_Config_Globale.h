
/**********************************************************************************************************
Nom du fichier: LIB_BSE_Config_Globale.h
Auteurs: DAVID Quentin, HU Weiyi
Date de dernière modification: 07/10/2015
Version: 1
Objectifs du code: L'objectif de ce code est de déclarer les fonctions utilisées dans le .c correspondant (et variables)
***********************************************************************************************************/


//Define----------------------------------------
#define ON 1
#define OFF 0
//----------------------------------------------

/****************************************
Fonctions de manipulation pour Init_Device
****************************************/

unsigned int CDE_Servo_H (char Angle);
void Init_PCA (void) ;

//Watchdog
void Reset_Sources_Init();

//Affectation des ports aux broches (sans crossbar)
void Init_CLK();

//Fonction d'appel
void Init_Device (void); 