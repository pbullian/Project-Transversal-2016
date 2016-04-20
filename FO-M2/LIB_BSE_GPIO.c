//------------------------------------------------------------------------------------
// LIB_BSE_GPIO.c
//------------------------------------------------------------------------------------
// Copyright (C) 2005 Silicon Laboratories, Inc.
// AUTH:PEREL/BULLIAN
// DATE:15/03/2016
// Version:1.0
// Objectif: COnfigurer les entrées/sorties du 8051F020
// Target: C8051F02x
// Tool chain: KEIL Eval 'c'
//
// 
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>                    // SFR declarations
#include <LIB_BSE_GPIO.h>                 //Config du µcontroleur
#include <intrins.h>
//-----------------------------------------------------------------------------
//  Gestion des I/O
//----------------------------------------------------------------------------
void Port_IO_Init()
{
    // P0.0  -  TX1 (UART1), Open-Drain, Digital
    // P0.1  -  RX1 (UART1), Open-Drain, Digital
    // P0.2  -  T1 (Timer1), Open-Drain, Digital
    // P0.3  -  INT1 (Tmr1), Open-Drain, Digital
    // P0.4  -  T4 (Timer4), Open-Drain, Digital
    // P0.5  -  T4EX (Tmr4), Open-Drain, Digital
    // P0.6  -  SYSCLK,      Open-Drain, Digital
    // P0.7  -  Unassigned,  Open-Drain, Digital

    // P1.0  -  Unassigned,  Open-Drain, Digital
    // P1.1  -  Unassigned,  Open-Drain, Digital
    // P1.2  -  Unassigned,  Open-Drain, Digital
    // P1.3  -  Unassigned,  Open-Drain, Digital
    // P1.4  -  Unassigned,  Open-Drain, Digital
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  Unassigned,  Open-Drain, Digital
    // P1.7  -  Unassigned,  Open-Drain, Digital

    // P2.0  -  Unassigned,  Open-Drain, Digital
    // P2.1  -  Unassigned,  Open-Drain, Digital
    // P2.2  -  Unassigned,  Open-Drain, Digital
    // P2.3  -  Unassigned,  Open-Drain, Digital
    // P2.4  -  Unassigned,  Open-Drain, Digital
    // P2.5  -  Unassigned,  Open-Drain, Digital
    // P2.6  -  Unassigned,  Open-Drain, Digital
    // P2.7  -  Unassigned,  Open-Drain, Digital

    // P3.0  -  Unassigned,  Open-Drain, Digital
    // P3.1  -  Unassigned,  Open-Drain, Digital
    // P3.2  -  Unassigned,  Open-Drain, Digital
    // P3.3  -  Unassigned,  Open-Drain, Digital
    // P3.4  -  Unassigned,  Open-Drain, Digital
    // P3.5  -  Unassigned,  Open-Drain, Digital
    // P3.6  -  Unassigned,  Open-Drain, Digital
    // P3.7  -  Unassigned,  Open-Drain, Digital

    XBR1      = 0x98;
    XBR2      = 0x5C;
		P0MDOUT   = 0x03;
}

