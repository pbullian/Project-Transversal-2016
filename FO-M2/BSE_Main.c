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
	if(car_recu=='R'||car_recu=='r')					//Controle de la r»ponse aux caractÀres 'r' et 'R' uniquement
	{
		Send_String("Test reussi");
		//Send_String(&nbr_colis);
		Send_String("\0");
	}
}
void main (void) {
 
   Init_Device();  													// Initialisation du microcontrŸleur
	 Port_IO_Init();
	 CFG_UART1();
	 
//------------------------------------------------------------------------------------
// TEST
//------------------------------------------------------------------------------------
//Send_String("cfg baud 3\r");

//Send_String("vpid 10:0:0:700\r");
	//Send_String("mogo 1:45 2:45\r");
		//Send_String("blink 1:50 2:100\r");

	while(1)
	{
	xdata char car_recu;

		//putchar('\n',80);
		car_recu=getchar();
		if(car_recu=='>')
				{
		Send_String("mogo 1:45 2:45\r\n\r");
		car_recu='p';
				//	Send_String("blink 1:50 2:50\r\n");
		}else if (car_recu=='s')				{
		Send_String("stop\r\n");
		car_recu='p';
			}
		//Send_String("\r\n");
	//	car_recu=getchar();      //Reception du caractere
		//putchar(car_recu,80);
		//putchar('\r',80);

		//car_recu='e';
		//Send_String("\n\r");

		/*if(car_recu=="R"||car_recu=='r')					//Controle de la r»ponse aux caractÀres 'r' et 'R' uniquement
		{
			//Send_String("Test reussi\n\r");
			Send_String("mogo 1:45 2:45\r");
			Send_String("\r");
		}*/
		//Reponse();
	  //test_getchar_putchar_sendstring();

	}
}
