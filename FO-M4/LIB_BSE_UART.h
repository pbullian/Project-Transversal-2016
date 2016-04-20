//------------------------------------------------------------------------------------
// LIB_BSE_UART.h
//------------------------------------------------------------------------------------
//
// AUTH: MAIGRE_VOUILLAT
// DATE: 10/11/2015
// Target: C8051F02x
//
// Tool chain: KEIL PK51
//
//------------------------------------------------------------------------------------
// UART
//------------------------------------------------------------------------------------

void CFG_Clock_UART0(void);

void CFG_UART0(void);

char Putchar(char c, unsigned char csg_tempo);

char Send_String (char *char_ptr);

char Getchar (void);

void Demo_UART(void);