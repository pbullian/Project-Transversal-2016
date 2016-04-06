//------------------------------------------------------------------------------------
// LIB_BSE_INT_UART.c
//------------------------------------------------------------------------------------
// Copyright (C) 2005 Silicon Laboratories, Inc.
// AUTH:PEREL/BULLIAN
// DATE:15/03/2015
// Version:1.0
// Objectif: Conigurer et gÈrer l'UART1
// Target: C8051F02x
// Tool chain: KEIL Eval 'c'
//
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051F020.h>                    // SFR declarations
#include <LIB_BSE_UART.h>              //Config du µcontroleur
#include <intrins.h>
#include <LIB_BSE_GPIO.h>
//------------------------------------------------------------------------------------
// Global Constants
//------------------------------------------------------------------------------------
#define BAUDRATE 19200					//Baudrate du UART en bps
#define SYSCLK   22118400				//SYSCLOCK en HZ
//----------------------------------------------------------------------------------
//  Configure UART1 & Timer4
//------------------------------------------------------------------------------------
void CFG_UART1(void)
{
	//Config Timer 4
	CKCON |=0x40;					  				    //Timer4 utilise la Sysclock
	T4CON&=0xF7;										  	//Flag Timer 4 EffacÈ
	RCAP4=-(SYSCLK/BAUDRATE/32);				//Valeur de rechargement
	EIE2&=0xFB;												  //Interruption Timer4 dÈvalidÈe
	T4CON=0x04;											  	//Start Timer4
	//Config UART1
	T4CON|=0x30;												//RCLK1=1 TCLK1=1
	PCON|=0x10;											  	//SMOD1=1
	PCON&=0xF7;											  	//SSTAT1=0
	SCON1=0x5E;
	//SCON1&=~0x81;												//8Bit UART Variable Baud Rate et TI1=1
	EIE2|=0x40;	        						  	//Interruption UART1 autorisÈe
}
//------------------------------------------------------------------------------------
//  Fonction de gestion de L'UART Putchar
//------------------------------------------------------------------------------------
char putchar(char c, char csg_tempo)
{
	xdata int i,timeout=0;

	while(!SCON1&0x02)
	{
	for(i=0;i<17;i++)
		_nop_();
	csg_tempo--;
  if(csg_tempo==0)
			return 0;
	timeout++;
	if(timeout==10)
			return 0;
	}
	SBUF1=c;
	SCON1&=0xFD; //Flag ‡ 0
	return c;
}
//------------------------------------------------------------------------------------
//  Fonction de gestion de L'UART envoie de string
//------------------------------------------------------------------------------------
char Send_String(char *char_ptr)
{
	xdata char lg_car=0;
	if(char_ptr!=0x00)
	{
		while(*char_ptr!='\0')
		{
			putchar(*char_ptr,15);
			lg_car++;
			char_ptr++;
		}
	return lg_car;
	}
	else
	{
		return 0;
	}
	return 0;
}
//------------------------------------------------------------------------------------
//  Fonction de gestion de L'UART getchar
//------------------------------------------------------------------------------------
char getchar(void)
{
	xdata char char_recu;
	if(SCON1&0x01)										//RI1==1
	{
		char_recu=SBUF1;
		SCON1&=0xFE;										//RI1=0;
		return char_recu;
	}
	else
	{
		return 0;
	}
	return 0;
}
//------------------------------------------------------------------------------------
//  Fonction de TEST
//------------------------------------------------------------------------------------
void test_getchar_putchar_sendstring(void)
{
	xdata char c,test;
	test=getchar();
	//c='A';
	putchar(test,15);
	//c='A';
	//putchar(c,15);
	/*char longueur;
	longueur=Send_String("abc");*/
	//putchar('a', 50);
}
