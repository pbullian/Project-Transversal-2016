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
#include <Structure_Serializer.c>

#include <Structures.h>

//
//#include <stdio.h>
//    /* card structure definition */
//    struct card
//    {
//      int face; // define pointer face
//    };// end structure card
//
//    typedef struct card Card ;
//
//    /* prototype */
//    void passByReference(Card *c) ;
//
//    int main(void)
//    {
//    Card c ;
//    c.face = 1 ;
//    Card *cptr = &c ; // pointer to Card c
//
//    printf("The value of c before function passing = %d\n", c.face);
//    printf("The value of cptr before function = %d\n",cptr->face);
//
//    passByReference(cptr);
//
//    printf("The value of c after function passing = %d\n", c.face);
//
//        return 0 ; // successfully ran program
//    }
//
//
//    void passByReference(Card *c)
//    {
//        c->face = 4;
//    }
//


typedef struct COMMANDES_SERIALIZER Struct_R ;
typedef struct INFORMATIONS_SERIALIZER Struct_E;




void serializer (Struct_R *s,Struct_E *r) {

 Struct_R *cpts = &s ;
 Struct_E *cptr = &r ;

    //this should be done in another file
   Init_Device();  													// Initialisation du microcontrÙleur
	 Port_IO_Init();
	 CFG_UART1();
    //


talk_serializer(cpts,cptr);



}
