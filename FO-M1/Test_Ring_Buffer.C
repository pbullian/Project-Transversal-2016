//---------------------------------------------------------------------------------------
// ID_1.1    Test_Ring_Buffer.C -----------------------------------------------------
//---------------------------------------------------------------------------------------
// ID_1.2  
//
// ID_1.3 Auteur F.JOLY - CPE Lyon
// ID_1.4 DATE: 08 Mars 2016 
// ID_1.5 Version 1.0 
// 
// ID_1.6 Objectifs ---------------------------------------------------------------------
// Programme de démo pour la mise en oeuvre du la librairie UART0_RingBuffer
// 
// ID_1.7 Dépendances matérielles "cible" ----------------------------------------------- 
// Processeur cible: C8051F02x

// ID_1.8 Dépendances matérielles "extérieures" -----------------------------------------
// Utilisation d'un Bouton Poussoir sur P3.7
// Utilisation d'un oscillateur externe (Quartz)

// ID_1.9 Dépendances de type communications/protocolaires ------------------------------
// Ce code reçoit et envoie des données sur la liaison série asynchrone UART0
// ID_1.10 Fonctionnement du code -------------------------------------------------------
// Le code est destiné à montrer le fonctionnement de la librairie UART0_RingBuffer
// Chaque donnée reçue sur la liaison série est stockée dans un buffer circulaire.
// A chaque appui sur le Bouton Poussoir les données dans le buffer de réception sont lues 
// et envoyées dans le buffer de transmission.

// ID_1.11 Choix technologiques divers --------------------------------------------------


// ID_1.12 Tests réalisés ---------------------------------------------------------------
// Validation sur plateforme 8051F020TB avec processeur 8051F020
// Vitesse de transmission: 115200 Baud
// Fréquence quartz: 22,1184 MHz
//
// ID_1.13 Chaine de compilation --------------------------------------------------------
// KEIL C51 6.03 / KEIL EVAL C51
//
// ID_1.14 Documentation de référence ---------------------------------------------------
// Datasheet 8051F020/1/2/3  Preliminary Rev. 1.4 12/03 
//
//ID_1.15 Commentaires sur les variables globales et les constantes ---------------------


//*************************************************************************************************
#include <c8051f020.h>                    // SFR declarations
#include <stdio.h>
#include <intrins.h>
#include <string.h>
#include <stdlib.h>
#include <Stucture_Centrale_Commande.h>
#include <Structure_Centrale_Commande.c>
#include <FO_M3.h>

#include <UART0_RingBuffer_lib.h>
#ifndef CFG_Globale
  #define CFG_Globale
  #include <CFG_Globale.h>
#endif

sbit BP = P3^7;     
OUT_M1 xdata Com;
IN_M1 xdata Inf;

// ****************************************************************************
//
//*****************************************************************************
void Oscillator_Init()
{
    int i = 0;
    OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    OSCICN    = 0x0C;
}
void Port_IO_Init()
{
   P0MDOUT   =  0x01;
	 XBR0      = 0x0F;
   XBR2      = 0x44;
	 P3        |= 0x80;
}

BYTE ConversionASCII(char * res)
{
	int i=0;
	BYTE asc=0;
	i=atoi(res);
	asc=(BYTE)i;
	
	return asc;
}

int ConversionAngle(char* ang)
{
	int d=0,i=0;
	while(*(ang+i)!='\0')
	{
		i++;
	}
	if(i==3)
	{
		d=(*(ang)-48)*100+(*(ang+1)-48)*10+*(ang+2)-48;
	}
	else if(i==2)
	{
		d=(*(ang)-48)*10+*(ang+1)-48;
	}
	else if(i==1)
	{
		d=*(ang)-48;
	}	
	return d;
}

// **************************************************************************************************
// MAIN
// **************************************************************************************************
                     /* size of local string buffer */ 



void main(void) {
		int a=0;
    char *c;
		//char *pd=&c[0];
	  char* tp_ptr_c;
		char xdata Res[12][25];
		unsigned char i=0,j;
		char* Delim=" ";
		char ca=0;
		unsigned char flagdebutepreuve=0;
		BYTE ascRes=0;
     WDTCN     = 0xDE;
     WDTCN     = 0xAD;
	   Oscillator_Init();
	   Port_IO_Init();
	   Init_PCA();
	   cfg_Clock_UART();
     cfg_UART0_mode1();
     init_Serial_Buffer();                            
     EA = 1;                              /* allow interrupts to happen */
	   serOutstring("\n\rTest_Buffer_Circulaire\n\r");
	
while(1) {
    
		if(flaginbuf)
		{
			readInbuf(a);
			checkCR(a);
			a++;
			if(a>=MAX_BUFLEN-1)
				a=0;
			flaginbuf=0;
		}
	
	  if (flagCR) {
				
			//serOutstring("\n\rCoucou\n\r");

			c=serInBuf();
			/*pd=serInBuf();
			if(c[i]!=0)
			{
				//ca=(char) *(c+i);
				serOutchar(c[i]);
				i++;
			}*/
      if (c!= NULL) {		
           i = 0;		
			     /*serOutstring("\n\r STR: "); 				
				   serOutstring(c);  // sans le "if" le serOutsring envoie n'importe quoi Le pointeur NULL vaut 0 certes, mais il pointe qd même sur qq chose.... 
				   serOutstring("\n\r");*/
		       tp_ptr_c = strtok(c, " \t\n");   
				   if (tp_ptr_c != NULL) strcpy(Res[i], tp_ptr_c);
				   else Res[i][0] = 0;
			     i++;
			
			     while(Res[i-1][0]!=0 && i<12){
					    tp_ptr_c = strtok(NULL, " \t\n");
				      if (tp_ptr_c != NULL) strcpy(Res[i], tp_ptr_c);
				      else Res[i][0] = 0;
				      i++;
			     }
					 serOutstring("\n\r");
			     /*for(j=0;j<i;j++)
			     {
				     serOutstring(Res[j]);
				     serOutstring("\n\r");
			     } */
					 serOutstring("END \n\r");
					 flagCR=0;
				 }	
	    
		 
		 if(Res[0][0]=='D' && flagdebutepreuve==0)
		 {
			 if(Res[1][0]!=0)
					 {
						ascRes=ConversionASCII(Res[1]);
						if(ascRes>=1 && ascRes <=8)
						{
							Com.Etat_Epreuve=ascRes;
							serOutstring("I ............\r\n");
							serOutstring("Début de l'épreuve: ");
							serOutchar('0'+ascRes);
							flagdebutepreuve = 1;
						}
						else
						 serOutstring("\r\n # \r\n");
					 }
				else
				 serOutstring("\r\n # \r\n");
		 }
		 else if(Res[0][0]=='E' && flagdebutepreuve==1)
		 {
			 Com.Etat_Epreuve=Fin_Epreuve;
			 serOutstring("Fin de l'épreuve\r\n");
			 flagdebutepreuve=0;
		 }
		 else if(Res[0][0]=='Q' && flagdebutepreuve==1)
		 {
			 Com.Etat_Epreuve=Stop_Urgence;
			 serOutstring("Arret Urgence\r\n");
			 flagdebutepreuve=0;
		 }	 
				 
				 
				 
				 
				 
		 
		 if(flagdebutepreuve)
		 {
			 switch(Res[0][0])
			 {
					 case 'A':
						 Com.Etat_Mouvement = Avancer;
						 Com.Vitesse=20;
						 if (Res[1][0]!=0) 
						 {
							 ascRes=ConversionASCII(Res[1]);
							 if (ascRes<=100 && ascRes>=10)
							 {								 
								 Com.Vitesse = ascRes;
								 serOutstring("Vitesse envoyée : ");
								 serOutstring(Res[1]);
							 }
						 }
						 else
						 {
							 serOutstring("\r\n Vitesse par défault pour avancer :");
							 serOutstring("20");
							 serOutstring("\r\n");
						 }
							 break;
						 
					
						 
					 case 'B':
						 Com.Etat_Mouvement = Reculer;
						 Com.Vitesse=20;
						 if (Res[1][0]!=0) 
						 {
							 ascRes=ConversionASCII(Res[1]);
							 if (ascRes<=100 && ascRes>=10)
							 {								 
								 Com.Vitesse = ascRes;
								 serOutstring("Vitesse envoyée : ");
								 serOutstring(Res[1]);
							 }
						 }
						 else
					   {
							 serOutstring("\r\nVitesse par défault pour reculer :");
							 serOutstring("20");
							 serOutstring("\r\n");
						 }
						 break;
						 
						 
						case 'R':
							if(Res[0][1]=='D')
							{
								Com.Etat_Mouvement=Rot_90D;
								serOutstring("Angle de rotation 90° à droite\r\n");
								//CDE_Servo_H(90);
							}
						  else if(Res[0][1]=='G')
							{
								Com.Etat_Mouvement=Rot_90G;
								serOutstring("Angle de rotation 90° à gauche\r\n");
							}
							else if(Res[0][1]=='C')
							{
								if(Res[1][0]=='D')
								{
									Com.Etat_Mouvement=Rot_180D;
									serOutstring("Demi-tour droite");
								}
								else if(Res[1][0]=='G')
								{
									Com.Etat_Mouvement=Rot_180G;
									serOutstring("Demi-tour gauche");
								}
								else
									serOutstring("\r\n # \r\n");
							}
							else if(Res[0][1]=='A')
							{
								
								if(Res[1][0]=='D')
								{
									Com.Etat_Mouvement=Rot_AngD;
									serOutstring("Rotation à droite, angle: 90 (par défault)");
									Com.Angle=90;
								}
								else if(Res[1][0]=='G')
								{
									Com.Etat_Mouvement=Rot_AngG;
									serOutstring("Rotation à droite, angle: 90 (par défault)");
									Com.Angle=90;
								}
								if(Res[1][1]==':' && Res[1][2]!=0)
								{
									Com.Angle=ConversionAngle(&Res[1][2]);
									serOutstring("Angle changé : ");
									serOutstring(&Res[1][2]);
									serOutstring("\r\n");									
								}
								else
									serOutstring("\r\n # \r\n");
							}
							else
								serOutstring("\r\n # \r\n");
							
							break;
						 
					 case 'S':
						 if(Res[1][0]==0 )
						 { if(Res[0][1]=='\0')
						 {
							 Com.Etat_Mouvement=Mouvement_non;
							 Com.Vitesse=0;
							 serOutstring("Remise à zéro de la vitesse et donc arret du robot");
						 }}
						 else
							 serOutstring("\r\n # \r\n");
					 break;
						 
					 case 'T':
						 if(Res[0][1]=='V')
						 {
							 if (Res[1][0]!=0) 
							 {
								 ascRes=ConversionASCII(Res[1]);
								 if (ascRes<=100 && ascRes>=10)
								 {
									 Com.Vitesse = ascRes;
									 serOutstring("\r\n > \r\n");
									 serOutstring("Vitesse changée en :");
									 serOutstring(Res[1]);
									 serOutstring("\r\n");
								 }
								else
									 serOutstring("\r\n # \r\n");
							 }
							 else
								 serOutstring("\r\n # \r\n");
						 }
						 else
							 serOutstring("\r\n # \r\n");
						break;
						 
						 
						 
					 default:
						 serOutstring("\r\n # \r\n");
						 break;
				 }
				 
				 
		 }
		 
		 for(j=0;j<12;j++)
			for(i=0;i<25;i++)
			 Res[j][i]=0;
			 
		 }//   if (/r)
	
	} /* While(1) */
} /* main */



