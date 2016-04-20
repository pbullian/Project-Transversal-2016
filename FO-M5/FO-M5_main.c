//#include <Structures.h>
#include <FO-M5.h>

void main()
{
	char Tab_INFO[TAILLE_TAB];
	//struct COMMANDES COMMANDE_M1;
	struct INFORMATIONS INFORMATION_M1;

	Initialisation_INFORMATIONS(&INFORMATION_M1);
	
	//Tab_INFO=Send_Tab_MS1_M1();
	//COMMANDES_MAJ ce que l'on reçoit de M1
	
	MAJ_STRUCT_INFORMATIONS_CDC_from_MASTER(&COMMANDES_MAJ); // En fonction de ce Que M1 nous envoie, modification de la structure information, et communication avec M3 et M4
	MAJ_STRUCT_COMMANDES_SER_from_MASTER(&COMMANDES_MAJ); // MAJ de la structure a envoyer à M2 en fonction de Ce que M1 nous envoie
	

}

