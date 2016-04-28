//-----------------------------------------------------------------------------
// pca_util.c
//-----------------------------------------------------------------------------
//
// AUTH: BULLIAN
/
//
// Description:
//						Example source code for implementing 8-bit PWM.
//						The PCA is configured in 8-bit PWM mode using
//						SYSCLK/4 as its time base.  <PWM> holds the number of
//						PCA cycles for the output waveform to remain low per 256-
//						count period.  The waveform is high for (256 - PWM) cycles.
//						The duty cycle of the output is equal to (256 - PWM) / 256.
//
//						Because the 8-bit PWM is handled completely in hardware,
//						no CPU cycles are expended in maintaining a fixed duty
//						cycle.  Altering the duty cycle requires a single 8-bit
//						write to the high byte of the module's compare register,
//						PCA0CP0H, in this example.
//
//						Achievable duty cycle ranges are 0.38% (PCA0CP0H = 0xff)
//						to 100% (PCA0CP0H = 0x00).
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <c8051f020.h>  				// SFR declarations
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void init_pca_lumin (void);
void Timer_Init_pca (void);
void initTimer0_pca(void);
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------








void init_pca_lumin (void) {


	// configure the PCA
	//PCA0MD = 0x02;							// disable CF interrupt

												// PCA time base = SYSCLK / 4
    	PCA0MD=0x08;//system clock


	PCA0CPL0 = 0x00;						// initialize minumium PCA PWM value
	PCA0CPH0 = 0x00;

		PCA0CPM0=0xC2;
						// CCM0 in 16-bit PWM mode
	PCA0CN = 0x40;							// enable PCA counter


}

void send_lumin (unsigned char* pwm_value,unsigned char* Lum_ON) {
    int time= Lum_ON;
    unsigned long int compteur_max = 65536;
	float duree_totale = 2962;//compteur_max / (SYSCLK); // en microseconde

	int masque = 0x00FF;
	int impulse_max = 2400;
	int impulse_min = 600;
    float largeur_impulse;
	float duty_cycle;
    unsigned long int valeur;


    largeur_impulse	= (time/10)*10^5;
    duty_cycle = largeur_impulse /duree_totale;
    valeur = compteur_max*(1-duty_cycle);


	PCA0CPL0=(valeur&masque);
	PCA0CPH0=(valeur>>8)&masque;

}
