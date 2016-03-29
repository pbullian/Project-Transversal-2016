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
#include <stdio.h>   
#include <Structure_Serializer.c>
#include <string.h>

//recibo la estructura y traduzco los comandos.


//Send_String();


void serializer_traductor(struct COMMANDES_SERIALIZER s){
    char buf1[15];
    char command[25];

    //Commande_non, Reset, Getenc_1, Getenc_2, Getenc_1_2, Clrenc_1, Clrenc_2, Clrenc_1_2, mogo_1, mogo_2, mogo_1_2, Vpid_set, Vpid_read,digo_1, digo_2, digo_1_2, Dpid_set, Dpid_read, Rpid_Stinger, Pids, Stop, Vel, Restore
    switch(s.Commande) {
        case 'Reset' :
            Send_Serializer('reset');
            break;

            //The getenc command returns the values of the encoder count (channel B) for the specified encoder Id(s). NOTE: The encoder counts for channel A are used for internal VPID and DPID algorithms.
        case 'Getenc_1' :
            Send_Serializer('getenc 1');
            break;
        case 'Getenc_2' :
            Send_Serializer('getenc 2');
            break;
        case 'Getenc_1_2' :
            Send_Serializer('getenc 1 2');
            break;

            //clrenc encoderId [encoderId]
            //The clrenc command clears the values of the encoder count (channel B) for the specified encoder Id.
        case 'Clrenc_1' :
            Send_Serializer('clrenc 1');
            break;
        case 'Clrenc_2' :
            Send_Serializer('clrenc 2');
            break;
        case 'Clrenc_1_2' :
            Send_Serializer('clrenc 1 2');
            break;
            /*The mogo command sets motor speed using one or more complex parameters containing a <motorId:spd> value pair.
The motorId can be either 1 or 2, which corresponds to the Motor Terminal port.
The vel value specifies the motor velocity, and it’s range depends on your VPID settings. See the VPID parameters section below to determine your MAX velocity. A positive value rotates the motors in one direction, which a negative value rotates the motors in the opposite direction.
You will have to determine which direction is positive for your motors, and connect the motors wires to the terminals on the Serializer board in the appropriate configuration.*/

        case 'mogo_1' :
            sprintf(buf1, "%d", s.Vitesse_Mot1);
            strcpy(command, "mogo 1:");
            strcpy(command, buf1);
            Send_Serializer(command);
            break;
        case 'mogo_2' :
            sprintf(buf1, "%d", s.Vitesse_Mot2);
            strcpy(command, "mogo 2:");
            strcpy(command, buf1);
            Send_Serializer(command);
            break;
        case 'mogo_1_2' :
            sprintf(buf1, "%d", s.Vitesse_Mot1);

            strcpy(command, "mogo 1:");
            strcpy(command, buf1);
            sprintf(buf1, "%d", s.Vitesse_Mot2);

            strcpy(command, " 2:");
            strcpy(command, buf1);
            Send_Serializer(command);
            break;
            /*The vpid command gets/sets the PIDL (Proportional, Integral, Derivative, and Loop) parameters for the Velocity PID control on the SerializerTM. If the PIDL parameters are absent, the PIDL values are returned. Otherwise the PIDL parameters are parsed, and saved (in eeprom). */

        case 'Vpid_set' :
            strcpy(command, "vpid ");
            sprintf(buf1, "%d", s.Set_P);
            strcpy(command, buf1);
            strcpy(command, ":");
            sprintf(buf1, "%d", s.Set_I);
            strcpy(command, buf1);
            strcpy(command, ":");
            sprintf(buf1, "%d", s.Set_D);
            strcpy(command, buf1);
            strcpy(command, ":");
            sprintf(buf1, "%d", s.Set_L_A);
            strcpy(command, buf1);

            Send_Serializer(command);
            break;
        case 'Vpid_read' :
            Send_Serializer('vpid');
            break;


            /*Simply put, the digo command allows you to command your robot to
travel a specified distance, at a specified speed. This command uses the internal VPID and DPID algorithms to control velocity and distance. Therefore, you must have dual motors, and dual wheel encoders connected to the Serializer motor ports and encoder inputs.
You must also configure the VPID and DPID parameters so match the physical configuration of your robot. Please see the VPID and DPID configuration sections below to configure the parameters for your robot. By default, the Serializer VPID and DPID parameters are configured to work with our Traxster Robot Kit.
Id specifies the motor id, and can be either 1 or 2, which corresponds to the Motor Terminal port.
Distance specifies the distance (in encoder ticks ) which you want your robot to travel.
*/

        case 'digo_1' :
            strcpy(command, "digo 1 : ");
            sprintf(buf1, "%d", s.Ticks_mot1);
            strcpy(command, buf1);
            strcpy(command, " : ");
            sprintf(buf1, "%d", s.Vitesse_Mot1);
            strcpy(command, buf1);
            Send_Serializer(command);
            break;
        case 'digo_2' :
            strcpy(command, "digo 2 : ");
            sprintf(buf1, "%d", s.Ticks_mot2);
            strcpy(command, buf1);
            strcpy(command, " : ");
            sprintf(buf1, "%d", s.Vitesse_Mot2);
            strcpy(command, buf1);
            Send_Serializer(command);
            break;
        case 'digo_1_2' :
            strcpy(command, "digo 1 : ");
            sprintf(buf1, "%d", s.Ticks_mot1);
            strcpy(command, buf1);
            strcpy(command, " : ");
            sprintf(buf1, "%d", s.Vitesse_Mot1);
            strcpy(command, buf1);
            strcpy(command, " 2 : ");
            sprintf(buf1, "%d", s.Ticks_mot2);
            strcpy(command, buf1);
            strcpy(command, " : ");
            sprintf(buf1, "%d", s.Vitesse_Mot2);
            strcpy(command, buf1);
            Send_Serializer(command);
            break;


            /*
           The dpid command gets/sets the PIDA (Proportional, Integral, Derivative, and Acceleration) parameters for the distance PID control on the SerializerTM. If the PIDA parameters are absent, the PIDA values are returned.
           */

        case 'Dpid_set' :
            strcpy(command, "dpid ");
            sprintf(buf1, "%d", s.Set_P);
            strcpy(command, buf1);
            strcpy(command, ":");
            sprintf(buf1, "%d", s.Set_I);
            strcpy(command, buf1);
            strcpy(command, ":");
            sprintf(buf1, "%d", s.Set_D);
            strcpy(command, buf1);
            strcpy(command, ":");
            sprintf(buf1, "%d", s.Set_L_A);
            strcpy(command, buf1);

            Send_Serializer(command);
            break;
        case 'Dpid_read' :
            Send_Serializer('dpid');
            break;
            /*The rpid command sets the default PID params known to work with either the Stinger or Traxster Robotic Kits in the firmware. This makes it quick and easy to set up the PID params for both robots.*/

        case 'Rpid_Stinger' :
            Send_Serializer('rpid s');
            break;

            /*Once a digo command is issued, an internal state variable within the firmware is set to ‘1’, and it stays in that state until the algorithm has completed. Upon completion, the state is set to ‘0’. The ‘pids’ command simply returns the value of the internal variable to determine if the algorithms is currently busy, or if it has finished, thus allowing subsequent digo commands to be issued w/o clobbering previous ones.
*/
        case 'Pids' :
            Send_Serializer('pids');
            break;

            /*The stop command immediately stops motor 1 and 2 connected to the motor ports. This will override any pwm, mogo, or digo commands which are currently active.*/
        case 'Stop' :
            Send_Serializer('stop');
            break;
            /*The vel command returns the left and right wheel velocities. The
velocity returned is based on the PIDL parameter configuration.*/
        case 'Vel' :
            Send_Serializer('vel');
            break;
            /*Restores the factory default settings, and resets the board. NOTE: This will erase any configurations you have saved to EEPROM, including VPID, DPID, and baud rate settings.*/
        case 'Restore' :
            Send_Serializer('restore');
            break;

    }

