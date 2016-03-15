//------------------------------------------------------------------------------------
// LIB_BSE_INT_UART.c
//------------------------------------------------------------------------------------
// Copyright (C) 2005 Silicon Laboratories, Inc.
// AUTH:PEREL/BULLIAN
// DATE:15/03/2015
// Version:1.0
// Objectif: Conigurer et gérer l'UART1
// Target: C8051F02x
// Tool chain: KEIL Eval 'c'
//
// 
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>                    // SFR declarations
#include <LIB_BSE_UART.h>              //Config du µcontroleur
#include <intrins.h>
#include <LIB_BSE_GPIO.h> 
//------------------------------------------------------------------------------------
// Global Constants
//------------------------------------------------------------------------------------
#define BAUDRATE 115200					//Baudrate du UART en bps
#define SYSCLK   22118400				//SYSCLOCK en HZ
//------------------------------------------------------------------------------------
//  Configure Timer 1
//------------------------------------------------------------------------------------
void CFG_Clock_UART1(void)
{
	CKCON |=0x40;					  				//Timer4 utilise la Sysclock
	//TMOD|=0x20;											//Timer1 CLK=system clock
	//TMOD&=0x2f;											//Timer1 configuréen timer 8bits avec auto-reload
	TF4=0;													//Flag Timer dévalidée
	TH4=-(SYSCLK/BAUDRATE/32);			//Valeur de rechargement
	ET4=0;													//Interruption Timer4 dévalidée
	TR4=1;													//Lance le timer4
}
//------------------------------------------------------------------------------------
//  Configure UART0
//------------------------------------------------------------------------------------
void CFG_UART1(void)
{
	SCON1=0x50;										//UART1->Mode1,8-bits,enable RX
	//T4CON
	RCLK1=1;											//T4CON Source clock timer4
	TCLK1=1;
	
  PCON |=0x10;									//SMOD1=1	
	PCON &=0xFB;									//SSTAT1
	
	TI1=1;												//Flag
}
//------------------------------------------------------------------------------------
//  Fonction de gestion de L'UART Putchar
//------------------------------------------------------------------------------------
char putchar(char c, char csg_tempo)
{
	xdata int i,timeout=0;
	while(!TI1)
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
	TI1=0;
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
	if(RI1==1)
	{
		char_recu=SBUF1;
		RI1=0;
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
	xdata char getchar_test;
	getchar_test=getchar();
	putchar(getchar_test,15);
	/*char longueur;
	longueur=Send_String("abc");*/
}