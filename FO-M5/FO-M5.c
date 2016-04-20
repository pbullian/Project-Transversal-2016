
#include <FO-M5.h>
#define RAYON_ROUE 10
#define RAYON_PARCOURS 35
#define PI 3.14159
#define TICKS_PAR_TOUR 624


struct INFORMATIONS INFORMATIONS_CDC;
struct COMMANDES_SERIALIZER COMMANDES_SER;
char TAB_COMMANDES_SLAVE[TAILLE_TAB];


int Compteur_Duree;
unsigned char Rechargement_L;
unsigned char Rechargement_H;

void MAJ_STRUCT_INFORMATIONS_CDC_from_MASTER(struct COMMANDES* const COMMANDES){
	/** Variables */
	int Distance; //A changer
	int Duree; //A changer

	/** Communication FO-M4*/


	if(COMMANDES->Etat_DCT_Obst!=DCT_non){

			if(COMMANDES->Etat_DCT_Obst==oui_180){
				AMX0SL    = 0x02; // Choix de AIN02 comme pin de conversion - Correspond au telemetre 180
				INFORMATIONS_CDC.Etat_DCT_Obst=DCT_Obst_180_oui;
			}

			if(COMMANDES->Etat_DCT_Obst==oui_360){
				AMX0SL    = 0x03; // Choix de AIN03 comme pin de conversion - Correspond au telemetre 360
				INFORMATIONS_CDC.Etat_DCT_Obst=DCT_Obst_360_oui;
			}

			P2__2=0;


			INFORMATIONS_CDC.Tab_Val_Obst[INFORMATIONS_CDC.Nbre_Val_obst]=Distance;
			INFORMATIONS_CDC.Nbre_Val_obst++;

			P2__2=1;
		}

	else
			INFORMATIONS_CDC.Etat_DCT_Obst=DCT_Obst_non;

	/** Communication FO-M2*/


	/** Communication FO-M3*/
	if(COMMANDES->Etat_Servo==Servo_H)
	{
		INFORMATIONS_CDC.Etat_BUT_Servo=BUT_Servo_H;

		Rechargement_L=0xF8;
		Rechargement_H=0xCA;
		TL0=Rechargement_L;
		TH0=Rechargement_H;

		TR0=1;

		//Chargement du timer 0 en fct de la duree

		if(Compteur_Duree*100==Duree)
		{
			P2__3=!P2__3;
			INFORMATIONS_CDC.Etat_BUT_Servo=BUT_Servo_non;
			Compteur_Duree=0;
			TR0=0;
		}
	}




}

void MAJ_STRUCT_INFORMATIONS_CDC_from_SLAVE(char const* Tab_INFO){
		/** Communication FO-MS1*/
}

void MAJ_TAB_COMMANDES_SLAVE_from_MASTER(struct COMMANDES* const COMMANDES){

}

void MAJ_STRUCT_COMMANDES_SER_from_MASTER(struct COMMANDES* const COMMANDES){

    //FAIRE UN SWITCH CASE

	switch (COMMANDES->Etat_Mouvement){
	case Avancer:
		COMMANDES_SER.Etat_Commande=mogo_1_2;
		COMMANDES_SER.Vitesse_Mot1=(int)COMMANDES->Vitesse;
		COMMANDES_SER.Vitesse_Mot2=(int)COMMANDES->Vitesse;
	break;

	case Reculer:
		COMMANDES_SER.Etat_Commande=mogo_1_2;
		COMMANDES_SER.Vitesse_Mot1=(int)-1*COMMANDES->Vitesse;
    COMMANDES_SER.Vitesse_Mot2=(int)-1*COMMANDES->Vitesse;
	break;

	case Stopper:
		COMMANDES_SER.Etat_Commande=Stop;
	break;

 	case Rot_90D:
		COMMANDES_SER.Etat_Commande=digo_1;
		COMMANDES_SER.Vitesse_Mot1=(int)COMMANDES->Vitesse;
		COMMANDES_SER.Vitesse_Mot2=0;
		COMMANDES_SER.Ticks_mot1=Get_Nb_Ticks(90);
		COMMANDES_SER.Ticks_mot2=Get_Nb_Ticks(0);
	break;

	case Rot_90G:
		COMMANDES_SER.Etat_Commande=digo_2;
		COMMANDES_SER.Vitesse_Mot1=0;
		COMMANDES_SER.Vitesse_Mot2=(int)COMMANDES->Vitesse;
		COMMANDES_SER.Ticks_mot1=Get_Nb_Ticks(0);
		COMMANDES_SER.Ticks_mot2=Get_Nb_Ticks(90);
	break;

 	case Rot_180D:
		COMMANDES_SER.Etat_Commande=digo_1;
		COMMANDES_SER.Vitesse_Mot1=(int)COMMANDES->Vitesse;
		COMMANDES_SER.Vitesse_Mot2=0;
		COMMANDES_SER.Ticks_mot1=Get_Nb_Ticks(180);
		COMMANDES_SER.Ticks_mot2=Get_Nb_Ticks(0);
	break;

	case Rot_180G:
		COMMANDES_SER.Etat_Commande=digo_2;
		COMMANDES_SER.Vitesse_Mot1=0;
		COMMANDES_SER.Vitesse_Mot2=(int)COMMANDES->Vitesse;
		COMMANDES_SER.Ticks_mot1=Get_Nb_Ticks(0);
		COMMANDES_SER.Ticks_mot2=Get_Nb_Ticks(180);
	break;

 	case Rot_AngD:
		COMMANDES_SER.Etat_Commande=digo_1;
		COMMANDES_SER.Vitesse_Mot1=(int)COMMANDES->Vitesse;
		COMMANDES_SER.Vitesse_Mot2=0;
		COMMANDES_SER.Ticks_mot1=Get_Nb_Ticks(COMMANDES->Angle);
		COMMANDES_SER.Ticks_mot2=Get_Nb_Ticks(0);
	break;

	case Rot_AngG:
		COMMANDES_SER.Etat_Commande=digo_2;
		COMMANDES_SER.Vitesse_Mot1=0;
		COMMANDES_SER.Vitesse_Mot2=(int)COMMANDES->Vitesse;
		COMMANDES_SER.Ticks_mot1=Get_Nb_Ticks(0);
		COMMANDES_SER.Ticks_mot2=Get_Nb_Ticks(COMMANDES->Angle);
	break;

	}
}

int Get_Nb_Ticks(int theta){
    theta=theta*PI/180;
    return TICKS_PAR_TOUR*(theta/(2*PI))*(RAYON_PARCOURS/RAYON_ROUE);
}


void INIT_STRUCT_INFORMATIONS_CDC(){
	INFORMATIONS_CDC.Etat_Invite=Invite_non ;
	INFORMATIONS_CDC.MSG_Invit[0]='\0';
	INFORMATIONS_CDC.Etat_BUT_Mouvement=BUT_Atteint_oui;
	INFORMATIONS_CDC.Etat_BUT_Servo=BUT_Servo_non;
	INFORMATIONS_CDC.Etat_DCT_Obst= DCT_Obst_non;
	INFORMATIONS_CDC.Tab_Val_Obst=0;
	INFORMATIONS_CDC.Nbre_Val_obst=0;
	INFORMATIONS_CDC.Etat_RESULT_Courant=RESULT_Courant_non;
	INFORMATIONS_CDC.Etat_RESULT_Energie=RESULT_Energie_non;
	INFORMATIONS_CDC.Etat_RESULT_Position=RESULT_Position_non;
	INFORMATIONS_CDC.Pos_Coord_X=0;
	INFORMATIONS_CDC.Pos_Coord_Y=0;
	INFORMATIONS_CDC.Pos_Angle=0;
	INFORMATIONS_CDC.Etat_Aux=Aux_non;
	INFORMATIONS_CDC.MSG_Aux[0]='\0';
}

void INIT_STRUCT_COMMANDES_SER(){
	COMMANDES_SER.Etat_Commande=Commande_non;
	COMMANDES_SER.Set_P=10;
	COMMANDES_SER.Set_I=0;
	COMMANDES_SER.Set_D=0;
	COMMANDES_SER.Set_L_A=100;
	COMMANDES_SER.Ticks_mot1=0;
	COMMANDES_SER.Vitesse_Mot1=0;
	COMMANDES_SER.Ticks_mot2=0;
	COMMANDES_SER.Vitesse_Mot2=0;
}

void INIT_TAB_COMMADES_SLAVE(){

}

struct INFORMATIONS GET_STRUCT_INFORMATIONS_CDC(){
    return INFORMATIONS_CDC;
}

struct COMMANDES_SERIALIZER GET_STRUCT_COMMANDES_SER(){
    return COMMANDES_SER;
}

char* GET_TAB_COMMANDES_SLAVE()
{
	return TAB_COMMANDES_SLAVE;
}


void Config_Timer0_F0_M5()
{
	CKCON &= 0xF7;
	TF0=0;
	TMOD &= 0xF9; // Mise en mode 16 - bit counter/timer du Timer 0 et Selection de l'incrémentation
	TMOD |= 0x01; // du Timer 0 par la clock
	TR0 = 0;
	PT0 = 1; //INT Timer0 priorité haute
	ET0 = 1; // Activation interruption
}

void ISR_Timer0 () interrupt 1
{
	TL0=Rechargement_L;
	TH0=Rechargement_H;
	Compteur_Duree++;
	TF0=0;
}
