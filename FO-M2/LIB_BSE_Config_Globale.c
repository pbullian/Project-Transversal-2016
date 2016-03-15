//------------------------------------------------------------------------------------
// LIB_BSE_Config_Globale.c
//------------------------------------------------------------------------------------
// Copyright (C) 2005 Silicon Laboratories, Inc.
// AUTH:PEREL/BULLIAN
// DATE:15/03/2016
// Version:1.0
// Objectif: COnfigurer l'horloge et les sources de reset du 8051F020
// Target: C8051F02x
// Tool chain: KEIL Eval 'c'
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>                    // SFR declarations
#include <LIB_BSE_Config_Globale.h>       //Config du µcontroleur
//#include <stdio.h> 
//-----------------------------------------------------------------------------
//  Initialisation subroutines
//-----------------------------------------------------------------------------
void Init_Device(void)
{
   Reset_Sources_Init();   //Sources Reset et watchdog
	 Oscillator_Init();			 //Configuration de l'oscillateur externe
}
//-----------------------------------------------------------------------------
//  Oscillator_Init
//-----------------------------------------------------------------------------
void Oscillator_Init(void)
{
    int i = 0;
    OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    OSCICN    = 0x08;
}
//-----------------------------------------------------------------------------
//  Reset_Sources_Init
//-----------------------------------------------------------------------------
void Reset_Sources_Init(void)
{
   EA=0;           //Désactive les interruptions
   WDTCN = 0xde;   //Enleve le watchdog timer   
   WDTCN = 0xad;   //
	 EA = 1;	 // Active les interruptions
}
