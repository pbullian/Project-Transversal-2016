//------------------------------------------------------------------------------------
//LIB_BSE_Config_Globale
//------------------------------------------------------------------------------------
//
// AUTH: Farineau Camille - Ngattai Lam Prince
// DATE: 07/10/2015
// Target: C8051F020
//
// Tool chain: KEIL PK51

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
void Init_Device (void); 
/*
	Objectif: Appelle les fonctions de config 
*/



void Config_GPIO (void);



//void Config_INT1 (void);
///*
//	Objectif: Initialisation et configuration de l'interruption externe INT1
//	
//	Description: 	- Autorisation de l'interruption
//								- Activation de l'interruption
//								- Mise de l'Interruption sur front descendant
//	
//	Variables Entrées: Aucune
//	
//	Variables de Sorties: Aucune
//	
//	Variables globales: Aucune
//*/

void Ports_Init (void);
/*
	Objectif: Initialisation et configuration les Ports I/O
	
	Description: 	- Mise des ports P2.2, P2.3, P3.0, P3.1 en entrée
								- Mise des ports P2.0, P2.1, P2.4, P2.5, P2.6, P3.3, P3.4, P3.5, P3.6, P3.7 en sortie
	
	Variables Entrées: Aucune
	
	Variables de Sorties: Aucune
	
	Variables globales: Aucune
	
	Registres modifiés: - P2
											- P3
											- P2MDOUT
											- P3MDOUT
	
	Pages de datasheet: 174-175

*/

void Reset_Init (void);
/*
	Objectif: Initialisation et configuration des sources de Reset
	
	Description: Désactivation du Watchdog
	
	Variables Entrées: Aucune
	
	Variables de Sorties:Aucune
	
	Variables globales: Aucune
*/