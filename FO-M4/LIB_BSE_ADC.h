//------------------------------------------------------------------------------------
//LIB_BSE_ADC.h
//------------------------------------------------------------------------------------
//
// AUTH: Farineau Camille - Ngattai Lam Prince
// DATE: 14/10/2015
// Target: C8051F020
//
// Tool chain: KEIL PK51

// Includes
//-----------------------------------------------------------------------------
//#include <Declarations_GPIO_BSE.h>
//-----------------------------------------------------------------------------
void CFG_VREF(void);
void CFG_ADC0(void);
unsigned char ACQ_ADC(void);
float Conversion (float TensHexa);