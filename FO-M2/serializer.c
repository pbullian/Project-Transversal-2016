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
#include "Structure.h"
#include "LIB_BSE_INT_UART.h"
#include "serializer.h"
#include <stdio.h>



extern xdata IN_M2 Struct_R;
extern xdata OUT_M2 Struct_E;


void talk_serializer(struct COMMANDES_SERIALIZER  *s,struct INFORMATIONS_SERIALIZER *r)
{
    char buf1[15];
    char command[25];
    int placeholder;

    //struct INFORMATIONS_SERIALIZER *cptr = &r ;



    //Commande_non, Reset, Getenc_1, Getenc_2, Getenc_1_2, Clrenc_1, Clrenc_2, Clrenc_1_2, mogo_1, mogo_2, mogo_1_2, Vpid_set, Vpid_read,digo_1, digo_2, digo_1_2, Dpid_set, Dpid_read, Rpid_Stinger, Pids, Stop, Vel, Restore
    switch(s->Etat_Commande){
        case Reset :

            Send_Serializer("reset");
            break;

            //The getenc command returns the values of the encoder count (channel B) for the specified encoder Id(s). NOTE: The encoder counts for channel A are used for internal VPID and DPID algorithms.
        case Getenc_1 :
            Send_Serializer("getenc 1");
            //listen to response
            //            receive_traduite(serializer_response(),1,cptr);
            break;
        case Getenc_2:
            Send_Serializer("getenc 2");
            //           receive_traduite(serializer_response(),2,cptr);
            break;
        case Getenc_1_2 :
            Send_Serializer("getenc 1 2");
            //          receive_traduite(serializer_response(),3,cptr);

            break;

            //clrenc encoderId [encoderId]
            //The clrenc command clears the values of the encoder count (channel B) for the specified encoder Id.
        case Clrenc_1 :
            Send_Serializer("clrenc 1");
            break;
        case Clrenc_2 :
            Send_Serializer("clrenc 2");
            break;
        case Clrenc_1_2 :
            Send_Serializer("clrenc 1 2");
            break;
            /*The mogo command sets motor speed using one or more complex parameters containing a <motorId:spd> value pair->
The motorId can be either 1 or 2, which corresponds to the Motor Terminal port.
The vel value specifies the motor velocity, and itâ€™s range depends on your VPID settings. See the VPID parameters section below to determine your MAX velocity. A positive value rotates the motors in one direction, which a negative value rotates the motors in the opposite direction.
You will have to determine which direction is positive for your motors, and connect the motors wires to the terminals on the Serializer board in the appropriate configuration.*/

        case mogo_1 :
            placeholder=s->Vitesse_Mot1;
            sprintf(buf1, "%d", placeholder);
            strcpy(command, "mogo 1:");
            strcat(command, buf1);
            Send_Serializer(command);
            break;
        case mogo_2 :
            placeholder=s->Vitesse_Mot2;
            sprintf(buf1, "%d", placeholder);
            strcpy(command, "mogo 2:");
            strcat(command, buf1);
            Send_Serializer(command);
            break;
        case mogo_1_2 :
            placeholder=s->Vitesse_Mot1;
            sprintf(buf1, "%d",placeholder);
            strcpy(command, "mogo 1:");
            strcat(command, buf1);
            placeholder=s->Vitesse_Mot2;
            sprintf(buf1, "%d", placeholder);
            strcat(command, " 2:");
            strcat(command, buf1);
            Send_Serializer(command);
            break;
            /*The vpid command gets/sets the PIDL (Proportional, Integral, Derivative, and Loop) parameters for the Velocity PID control on the SerializerTM. If the PIDL parameters are absent, the PIDL values are returned. Otherwise the PIDL parameters are parsed, and saved (in eeprom). */

        case Vpid_set :
            strcpy(command, "vpid ");

            sprintf(buf1, "%d", s->Set_P);
            strcat(command, buf1);
            strcat(command, ":");
            sprintf(buf1, "%d", s->Set_I);
            strcat(command, buf1);
            strcat(command, ":");
            sprintf(buf1, "%d", s->Set_D);
            strcat(command, buf1);
            strcat(command, ":");
            sprintf(buf1, "%d", s->Set_L_A);
            strcat(command, buf1);

            Send_Serializer(command);
            break;
        case Vpid_read :
            Send_Serializer("vpid");
            //           receive_traduite(serializer_response(),4,cptr);

            break;


            /*Simply put, the digo command allows you to command your robot to
travel a specified distance, at a specified speed. This command uses the internal VPID and DPID algorithms to control velocity and distance. Therefore, you must have dual motors, and dual wheel encoders connected to the Serializer motor ports and encoder inputs.
You must also configure the VPID and DPID parameters so match the physical configuration of your robot. Please see the VPID and DPID configuration sections below to configure the parameters for your robot. By default, the Serializer VPID and DPID parameters are configured to work with our Traxster Robot Kit.
Id specifies the motor id, and can be either 1 or 2, which corresponds to the Motor Terminal port.
Distance specifies the distance (in encoder ticks ) which you want your robot to travel.
*/

        case digo_1 :
            strcpy(command, "digo 1 : ");
            placeholder=s->Ticks_mot1;

            sprintf(buf1, "%d", placeholder);
            strcat(command, buf1);
            strcat(command, " : ");
            placeholder=s->Vitesse_Mot1;
            sprintf(buf1, "%d", placeholder);
            strcat(command, buf1);
            Send_Serializer(command);
            break;
        case digo_2 :
            strcpy(command, "digo 2 : ");
            placeholder=s->Ticks_mot2;

            sprintf(buf1, "%d", placeholder);
            strcat(command, buf1);
            strcat(command, " : ");
            placeholder=s->Vitesse_Mot2;
            sprintf(buf1, "%d",placeholder );
            strcat(command, buf1);
            Send_Serializer(command);
            break;
        case digo_1_2 :
            strcpy(command, "digo 1 : ");
            placeholder=s->Ticks_mot1;

            sprintf(buf1, "%d", placeholder);
            strcat(command, buf1);
            strcat(command, " : ");
            placeholder=s->Vitesse_Mot1;
            sprintf(buf1, "%d", placeholder);
            strcat(command, buf1);
            strcat(command, " 2 : ");
            placeholder=s->Ticks_mot2;

            sprintf(buf1, "%d", placeholder);
            strcat(command, buf1);
            strcat(command, " : ");
            placeholder=s->Vitesse_Mot2;
            sprintf(buf1, "%d",placeholder );
            strcat(command, buf1);
            Send_Serializer(command);
            break;


            /*
           The dpid command gets/sets the PIDA (Proportional, Integral, Derivative, and Acceleration) parameters for the distance PID control on the SerializerTM. If the PIDA parameters are absent, the PIDA values are returned.
           */

        case Dpid_set :
            strcpy(command, "dpid ");
            placeholder=s->Set_P;
            sprintf(buf1, "%d", placeholder);
            strcat(command, buf1);
            strcat(command, ":");
            placeholder=s->Set_I;
            sprintf(buf1, "%d", placeholder);
            strcat(command, buf1);
            strcat(command, ":");
            placeholder=s->Set_D;
            sprintf(buf1, "%d", placeholder);
            strcat(command, buf1);
            strcat(command, ":");
            placeholder=s->Set_L_A;
            sprintf(buf1, "%d", placeholder);
            strcat(command, buf1);

            Send_Serializer(command);
            break;
        case Dpid_read :
            Send_Serializer("dpid");
            //           receive_traduite(serializer_response(),5,cptr);

            break;
            /*The rpid command sets the default PID params known to work with either the Stinger or Traxster Robotic Kits in the firmware. This makes it quick and easy to set up the PID params for both robots.*/

        case Rpid_Stinger :
            Send_Serializer("rpid s");
            break;

            /*Once a digo command is issued, an internal state variable within the firmware is set to â€˜1â€™, and it stays in that state until the algorithm has completed. Upon completion, the state is set to â€˜0â€™. The â€˜pidsâ€™ command simply returns the value of the internal variable to determine if the algorithms is currently busy, or if it has finished, thus allowing subsequent digo commands to be issued w/o clobbering previous ones.
*/
        case Pids :
            Send_Serializer("pids");
            receive_traduite(serializer_response(),6,cptr);

            break;

            /*The stop command immediately stops motor 1 and 2 connected to the motor ports. This will override any pwm, mogo, or digo commands which are currently active.*/
        case Stop :
            Send_Serializer("stop");
            break;
            /*The vel command returns the left and right wheel velocities. The
velocity returned is based on the PIDL parameter configuration.*/
        case Vel :
            Send_Serializer("vel");
            //          receive_traduite(serializer_response(),7,cptr);

            break;
            /*Restores the factory default settings, and resets the board. NOTE: This will erase any configurations you have saved to EEPROM, including VPID, DPID, and baud rate settings.*/
        case Restore :
            Send_Serializer("restore");
            break;

    }

}



void Send_Serializer(const char* char_ptr){
    char command[50];

    strcpy(command, char_ptr);
    strcat(command, "\r\n\r");
    //Send_String(command);
    serOutstring(command);
}

//reply from the serializer
char * serializer_response(){
    char xdata response[50];
    response=serInBuf();
    return response;
}


////receive a string (response) with the response, we can't utilize switch with an array of char
void receive_traduite(char *response, int option,struct INFORMATIONS_SERIALIZER *r){
    char buf1[15];
    char buf2[15];
    char *pch;

    //Reponse_non, Rep_getenc, Rep_vpid, Rep_dpid, Rep_pids, Rep_vel
    switch(response) {

            //The getenc command returns the values of the encoder count (channel B) for the specified encoder Id(s). NOTE: The encoder counts for channel A are used for internal VPID and DPID algorithms.
        case 1 :
            r->Etat_Response=Rep_getenc;
            r->Read_Val_enc_1 = sscanf(response, "%d", &i);
            break;
        case 2 :
            r->Etat_Response=Rep_getenc;
            r->Read_Val_enc_2 = sscanf(response, "%d", &i);
            break;
        case 3 :
            r->Etat_Response=Rep_gestenc;
            pch = strtok (str," ");
            r->Read_Val_enc_1 = pch;
            r->Read_Val_enc_2 = pch;
            break;


            /*The vpid command gets/sets the PIDL (Proportional, Integral, Derivative, and Loop) parameters for the Velocity PID control on the SerializerTM. If the PIDL parameters are absent, the PIDL values are returned. Otherwise the PIDL parameters are parsed, and saved (in eeprom). */


        case 4 :
            r->Etat_Response=Rep_vpid;
            pch = strtok (str," ");
            r->Read_P = pch;
            r->Read_I = pch;
            r->Read_D = pch;
            r->Read_L_A = pch;
            break;


            /*
           The dpid command gets/sets the PIDA (Proportional, Integral, Derivative, and Acceleration) parameters for the distance PID control on the SerializerTM. If the PIDA parameters are absent, the PIDA values are returned.
           */



        case 5 :
            r->Etat_Response=Rep_dpid;
            pch = strtok (str," ");
            r->Read_P = pch;
            r->Read_I = pch;
            r->Read_D = pch;
            r->Read_L_A = pch;
            break;

            /*Once a digo command is issued, an internal state variable within the firmware is set to â€˜1â€™, and it stays in that state until the algorithm has completed. Upon completion, the state is set to â€˜0â€™. The â€˜pidsâ€™ command simply returns the value of the internal variable to determine if the algorithms is currently busy, or if it has finished, thus allowing subsequent digo commands to be issued w/o clobbering previous ones.
*/
        case 6 :
            r->Etat_Response=Rep_pids;
            pch = strtok (str," ");
            r->Read_Pids = sscanf(response, "%d", &i);
            break;

            /*The vel command returns the left and right wheel velocities. The
velocity returned is based on the PIDL parameter configuration.*/
        case 7 :
            r->Etat_Response=Rep_vel;
            pch = strtok (str," ");
            r->Read_Vitesse_mot1 = pch;
            r->Read_Vitesse_mot2 = pch;
            break;

    }
    return 0;
}
