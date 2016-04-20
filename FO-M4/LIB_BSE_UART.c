//------------------------------------------------------------------------------------
// LIB_BSE_UART.c
//------------------------------------------------------------------------------------
//
// AUTH: MAIGRE_VOUILLAT
// DATE: 07/10/2015
// Target: C8051F02x
//
// Tool chain: KEIL PK51
//
//-----------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#ifndef LIB_BSE_UART
#define LIB_BSE_UART
#include <c8051f020.h> 
#include <intrins.h>
#include <LIB_BSE_Config_GPIO.h>
#include <LIB_BSE_Config_Globale.h>
#include <LIB_BSE_DAC.h>
#include <LIB_BSE_UART.h>
#include <Declarations_GPIO_BSE.h>
#endif

//------------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------------
#define BAUDRATE 115200
#define SYSCLK 22118400

//------------------------------------------------------------------------------------
// UART0
//------------------------------------------------------------------------------------

//*****************************************************************************	 
//CFG_Clock_UART0
//
//	 Configure l'horloge de l'UART0 
// 
//*****************************************************************************
void CFG_Clock_UART0(void)
{
	CKCON |= 0x10; //selection du timer1 comme source d'horloge
	TMOD |= 0x20;  //Timer1 clk = system clock
	TMOD &= 0x2F;  // timer1 en mode 2 : 8bit AutoReload
	TF1 = 0;  //flag timer effac�
	TH1 = -(SYSCLK/BAUDRATE/16);
	ET1=0;  //interruption timer1 d�valid�
	TR1=1;  //timer1 demarr�
}
	
//*****************************************************************************	 
//CFG_UART0
//
//	 Configure l'UART0 
// 
//*****************************************************************************
void CFG_UART0(void)
{
	RCLK0 = 0;	//T2CON source clk timer1
	TCLK0 = 0;	//T2CON
	PCON |= 0x80;	//SMOD0: UART0 Baud Rate Doubler
	PCON &=0xBF;	//SSTAT=0
	SCON0 = 0x70; 	// Mode1
	TI0 = 1;
}

//*****************************************************************************	 
//Putchar
//
//	 Fonction d'envoie d'un caract�re sur la liason s�rie 
// 
//*****************************************************************************
char Putchar(char c, unsigned char csg_tempo)
{
	int i;										// i va permettre de cr�er la tempo
	
	
	while(!TI0)								//test drapeau
	{
		for (i=0;i<=20;i++)				
			_nop_();							// si pas pret � transmettre, on tempo de 10us	
		
		csg_tempo--;						// on d�cremente csg_tempo
		
		if (csg_tempo==0)				// on envoie 0 si csg_tempo=0
			return 0;
	}
	
	SBUF0 = c; 								//on envoie char c dans le reg des donn�es de l'uart
	TI0 = 0; 									// raz du drapeau
	
	return c; 								// donn�e renvoy�e = donn�e �mis
}


//*****************************************************************************	 
//Send_String
//
//	 Fonction d'envoie d'une chaine de caract�res sur la liason s�rie 
// 
//*****************************************************************************
char Send_String (char *char_ptr)
{
	int nb_char=0;						// nb caract�res de la chaine de caract�res
	
	while (*char_ptr != 0x00)	// tant qu'on est pas arriv�s � la fin de la chaine de caract�res
	{
		Putchar(*char_ptr,100);	// on envoi le caract�re lu
		char_ptr ++;						//on se d�cale sur la chaine de caract�res de 1
		nb_char ++;							//on augmente le nb de caract�res pr�sents dans la chaine
	}
	
	return nb_char;	// on retourne le nb de caract�res de la chaine
}


//*****************************************************************************	 
//Getchar
//
//	 Fonction de reception d'un caract�re sur la liason s�rie 
// 
//*****************************************************************************
char Getchar (void)
{
	char c;
	
	if(RI0==0)	// test drapeau caract�re recu
		return 0; // si non, on envoi 0
	
	c=SBUF0;	//lecture caract�re recu
	RI0=0;	//raz drapeau 
	
	return c; // on retourne le caract�re recu
}

//*****************************************************************************	 
//Demo_UART
//
//	 Fonction Test de l'UART
// 
//*****************************************************************************
void Demo_UART(void)
{
	int i;
	char c;
	char T[]="bonjour";
	
	Send_String(T);
	
	c=Getchar();
	Putchar(c,10);
	
	for(i=0;i<1000;i++)
		_nop_();
} 

