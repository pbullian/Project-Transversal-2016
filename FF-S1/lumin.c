//------------------------------------------------------------------------------------
// serializer.c
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
#include <string.h>

#include <stdlib.h>
#include <intrins.h>
#include "LIB_BSE_INT_UART.h"
#include "serializer.h"
#include <stdio.h>




/*
* intensity : intensité lumineuse exprimée en pourcentage de luminosité
*• Lum_ON : Durée d’allumage exprimée en dixièmes de seconde (de 1 à 100)
*• Lum_OFF: Durée d’extinction exprimée en dixièmes de seconde (de 1 à 100)
*• Lum_Nbre: Nombre de cycles d’allumage-Extinction (de 1 à 100)
*/

void Lumiere (unsigned char* intensity, unsigned char* Lum_ON, unsigned char* Lum_OFF, unsigned char* Lum_Nbre) {

    if(intensity != 0){
        send_lumin(intensity);
        return;
    }

    if(Lum_ON != 0){
        send_lumin(Lum_ON);
        return;
    }

    if(Lum_OFF != 0){
        send_lumin(Lum_OFF);
        return;
    }

    if(Lum_Nbre != 0){
        send_lumin("");
        return;
    }






}

/*Extinction inconditionnelle de la source lumineuse*/
void Lumiere_Stop (void) {

send_lumin(255);

}



void Send_Lumin(const char* char_ptr){
    char command[50];

    strcpy(command, char_ptr);

    //Send_String(command);
    serOutstring(command);
}


