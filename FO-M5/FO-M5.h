
#include <Structures.h>
#define TAILLE_TAB 10
#include <Declarations_GPIO_BSE.h>




void Initialisation_INFORMATIONS(struct INFORMATIONS * INFO_INIT);
void MAJ_INFORMATIONS(struct COMMANDES* const COMMANDES_MAJ, struct INFORMATIONS * INFO_INIT);
void MAJ_INFORMATIONS_SLAVE(char const* Tab_INFO,struct INFORMATIONS * INFO_MAJ);
char* Send_Tab_M5_MS1();
void Config_Timer0_F0_M5();
void ISR_Timer0 ();
int Get_Nb_Ticks(int theta);