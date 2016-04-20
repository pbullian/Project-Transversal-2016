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
#include <c8051f020.h>  										// SFR declarations
#include "LIB_BSE_Config_Globale.h"
#include "LIB_BSE_GPIO.h"
#include "LIB_BSE_INT_UART.h"
//#include <stdio.h>   
#include "serializer.h"
#include "Structure.h"

 IN_M2 xdata Struct_R;
 OUT_M2 xdata Struct_E;





void main (void) {
//------------------------------------------------------------------------------------
// Programme de config
//------------------------------------------------------------------------------------
   Init_Device();  													// Initialisation du microcontrôleur
	 Port_IO_Init();
	 CFG_UART1();
	
	
//------------------------------------------------------------------------------------
// Programme main
//------------------------------------------------------------------------------------
while(1)
{
unsigned int num=45;
	
	 xdata char car_recu;
         
        //putchar('\n',80);     
        car_recu=getchar();
        if(car_recu=='>')    
                {
       Struct_R.Etat_Commande=mogo_1_2;
	
	Struct_R.Vitesse_Mot1=45;
	Struct_R.Vitesse_Mot2=45;
	//Send_String("coucou\r\n");
	
	talk_serializer(&Struct_R,&Struct_E);
        car_recu='p';
                //  Send_String("blink 1:50 2:50\r\n");
        }else if (car_recu=='s')                {
        Send_String("stop\r\n\r");
        car_recu='p';
            }
	
}

}