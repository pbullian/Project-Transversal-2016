
typedef unsigned char BYTE;
typedef char SIGNED_BYTE;

///*****************************************************************************************************************************************
// Structure de donn�es pour les commandes transmises par la centrale ce commande
// Les commandes d�cod�es par FO-M1 seront stock�es dans une structure de ce type pour �tre utilis�es par FO-M5 
//*****************************************************************************************************************************************

enum Epreuve {Epreuve_non, epreuve1, epreuve2, epreuve3, epreuve4, epreuve5, epreuve6, epreuve7, epreuve8, Fin_Epreuve, Stop_Urgence};
enum Mouvement {Mouvement_non, Avancer, Reculer, Stopper, Rot_90D, Rot_90G, Rot_180D, Rot_180G, Rot_AngD, Rot_AngG, Depl_Coord}; 
enum ACQ_Son {ACQ_non, ACQ_oui};
enum DCT_Obst {DCT_non, oui_180, oui_360};
enum Lumiere {Lumiere_non, Allumer, Eteindre};
enum Servo {Servo_non, Servo_H, Servo_V};
enum Energie{Energie_non,Mesure_I,Mesure_E};
enum Position{Position_non, Init_Position, Demande_Position};
enum Photo{Photo_non,Photo_1,Photo_Multiple,Photo_continue,Photo_stop}; 

typedef struct COMMANDES       // Cette structure contient toutes les commandes envoy�es par la centrale de commande
                               // Les variables de type enum correspondent aux commandes
                               // Les variables de type BYTE, UNSIGNED_BYTE ou int correspondent aux param�tres
                
{           
   enum  Epreuve Etat_Epreuve;     //Contient le num�ro d'�preuve en cours - Commandes "D" "E" "Q"
   
   enum  Mouvement Etat_Mouvement; //Contient le type de mouvement demand� - Commandes "A" "B" "S" "RD" "RG" "RC" "RA" "G"
                                   // Param�tres des commandes pr�c�dentes:     
   BYTE  Vitesse;                  // Param�tre vitesse - Peut aussi �tre modifi� par la commande "TV"
   BYTE  Coord_X;	                 // Param�tre coordonn�e X
   BYTE  Coord_Y;                  // Param�tre coordonn�e Y
   int   Angle;                    // Param�tre angle
   
   enum  ACQ_Son Etat_ACQ_Son;     // Contient la commande d'acquisition de signaux sonores "ASS"
                                   // Param�tre de la commande pr�c�dente:     
   BYTE  ACQ_Duree;                // Param�tre dur�e de la s�quence d'acquisition
   
   enum  DCT_Obst Etat_DCT_Obst;   // Contient la commande de d�tection d'obstacle "MOB D" "MOB"
                                   // Param�tre de la commandes pr�c�dente:     
   BYTE  DCT_Obst_Resolution;      // Param�tre r�solution angulaire de la d�tection d'obstacle
   
   enum  Lumiere Etat_Lumiere;     // Contient la commande d'allumage du pointeur lumineux "L" "LS"
                                   // Param�tres de la commande pr�c�dente:     
   BYTE  Lumiere_Intensite;        // Param�tre intensit� lumineuse 							  
   BYTE  Lumiere_Duree;            // Param�tre dur�e d'allumage
   BYTE  Lumire_Extinction;        // Param�tre dur�e d'extinction
   BYTE  Lumiere_Nbre;             // Param�tre nombre de cycles d'allumage/extinction
   
   enum  Servo Etat_Servo;        // Contient la commande de positionnement d'un servo "CS C" "CS H" "CS V" 
                                  // Param�tre de la commande pr�c�dente:     
   SIGNED_BYTE  Servo_Angle;      // Param�tre angle de rotation
   enum  Energie Etat_Energie;    // Contient la commande d'envoi du courant instantan� ou de l'energie consomm�e - Commandes "MI" "ME"
   enum  Position Etat_Position;  // Contient les commandes de gestion de la position, initialisation ou demande d'envoi
		                              // de la position - Commandes: "IPO" "POS"		
   BYTE  Pos_Coord_X;	            // Param�tre coordonn�e X pour initialisation de la position
   BYTE  Pos_Coord_Y;             // Param�tre coordonn�e Y pour initialisation de la position
   int   Pos_Angle;               // Param�tre angle pour initialisation de la position	 
	 enum  Photo Etat_Photo;        // Contient les commandes de la gestion de la prise de photo - Commandes "PPH" "SPH"
	 BYTE  Photo_Duree;	            // Param�tre dur�e entre 2 photos
   BYTE  Photo_Nbre;              // Param�tre nombre de photos	 
		 
} OUT_M1;



//*****************************************************************************************************************************************
// Structure de donn�es pour les informations � emettre vers la centrale ce commande
// Les donn�es "Informations" produites par FO-M5  seront stock�es dans une structure de ce type pour �tre utilis�es par FO-M1 qui devra
// les encoder en messages ASCII 
//*****************************************************************************************************************************************

enum Invite {Invite_non, Invite_oui};
enum BUT_Mouvement {BUT_Atteint_non, BUT_Atteint_oui};
enum BUT_Servo {BUT_Servo_non, BUT_Servo_H, BUT_Servo_V, BUT_Servo_C};
enum RESULT_Courant{RESULT_Courant_non,RESULT_Courant_oui};
enum RESULT_Energie{RESULT_Energie_non,RESULT_Energie_oui};
enum RESULT_Position{RESULT_Position_non,RESULT_Position_oui};
enum RESULT_DCT_Obst {DCT_Obst_non, DCT_Obst_180_oui, DCT_Obst_360_oui};
enum Aux {Aux_non, Aux_oui};

typedef struct INFORMATIONS       // Cette structure contient toutes les informations susceptibles d'�tre transmises � la centrale de commande
	                                // Les variables de type enum correspondent aux types des informations
                                  // Les variables de type BYTE, UNSIGNED_BYTE ou int correspondent aux param�tres
                
{           
   enum  Invite Etat_Invite;      // Contient l'identificateur information d'invite "I"
                                  // Param�tre de l'information pr�c�dente:     
   char  *MSG_Invit;	            //Pointeur sur une chaine de caract�re d'invite     
   
   enum  BUT_Mouvement Etat_BUT_Mouvement; // Contient l'identificateur information Arriv�e au point sp�cifi� "B"
	                                         // Pas de param�tre associ� pour l'information pr�c�dente:     
   enum  BUT_Servo Etat_BUT_Servo;         // Contient l'identificateur information Servomoteur positionn� "AS C" "AS H" "AS H"
	                                         // Pas de param�tre associ� pour l'information pr�c�dente:     
	 
   enum  RESULT_DCT_Obst Etat_DCT_Obst;    // Contient l'identificateur information D�tection des obstacles "KOB"
                                           // Param�tre de l'information pr�c�dente:    
	 int   *Tab_Val_Obst;                    //Pointeur sur un tableau de valeurs de distance
	 BYTE	 Nbre_Val_obst;                    //Nombre de points dans le tableau
	 
	 enum RESULT_Courant Etat_RESULT_Courant; // Contient un idendicateur d'information "courant mesur�"
	 unsigned int Mesure_Courant;            // Valeur du courant mesur� en mA   
	 
	 enum RESULT_Energie Etat_RESULT_Energie; // Contient un idendicateur d'information "Energie Consomm�e"
	 unsigned int Mesure_Energie;            // Valeur de l'�nergie consomm�e depuis le d�but de l'�preuve
	 
	 enum RESULT_Position Etat_RESULT_Position; // Contient un idendicateur d'information "Position"
   BYTE  Pos_Coord_X;	                     // Information Param�tre coordonn�e X
   BYTE  Pos_Coord_Y;                      // Information Param�tre coordonn�e Y
   int   Pos_Angle;                        // Information Param�tre angle
	 
   enum   Aux Etat_Aux;                    // Contient l'identificateur information auxiliaires "IA"
                                           // Param�tre de l'information pr�c�dente:     
   char  *MSG_Aux;	                       //Pointeur sur une chaine de caract�re d'informations auxiliaires  
} IN_M1;
// *******************************************************************************************




//*****************************************************************************************************************************************
// Structure de donn�es pour les commandes � envoyer � la carte Serializer
// Les commandes produites par FO-M5 (� priori) seront stock�es dans une structure de ce type pour �tre utilis�es par FO-M2
// Cette structure ne couvre pas toutes les commandes compr�hensibles par la carte Serializer. 
// Seules les commande potentiellement utiles au projet SEM815 sont trait�es 
// Commandes Trait�es:  Reset - getenc - clrenc - mogo - vpid - digo - dpid - rpid - pids - stop - vel - restore
//*****************************************************************************************************************************************

enum Commande {Commande_non, Reset, Getenc_1, Getenc_2, Getenc_1_2, Clrenc_1, Clrenc_2, Clrenc_1_2, mogo_1, mogo_2, mogo_1_2, Vpid_set, Vpid_read,
               digo_1, digo_2, digo_1_2, Dpid_set, Dpid_read, Rpid_Stinger, Pids, Stop, Vel, Restore };


typedef struct COMMANDES_SERIALIZER  // Cette structure contient toutes les commandes � envoyer au serializer
	                                   // Les variables de type enum correspondent aux commandes
                                    // Les variables de type BYTE, UNSIGNED_BYTE ou int corrspondent aux param�tres
                
{           
   enum  Commande Etat_Commande;   // Contient la commande � transmettre "Reset" "getenc 1" "getenc 2" "getenc 1 2" "clrenc 1" "clrenc 2"
                                   // "clrenc 1 2" "mogo 1" "mogo 1" "mogo 2" "mogo 1 2" "vpid" "digo 1" "digo 2" "digo 1 2" "dpid"
									                 // "rpid s"  "pids" "stop" "vel" "restore"
               
   int   Set_P;                    // param�tre commande vpid dpid
   int   Set_I;                    // param�tre commande vpid dpid
   int   Set_D;                    // param�tre commande vpid dpid
   int   Set_L_A;                  // param�tre commande vpid (L)  dpid (A)
   int   Ticks_mot1;               // param�tre Distance - Encoder Ticks moteur 1 (digo)
   SIGNED_BYTE  Vitesse_Mot1;      // param�tre de vitesse de rotation du moteur 1  (mogo digo)
   int   Ticks_mot2;               // param�tre Distance - Encoder Ticks moteur 2 (digo)
   SIGNED_BYTE  Vitesse_Mot2;      // param�tre de vitesse de rotation du moteur 2 (mogo digo)
} IN_M2;


//*****************************************************************************************************************************************
// Structure de donn�es pour les informations transmises par la carte Serializer
// Les informations Serializer d�cod�es par FO-M2 seront stock�es dans une structure de ce type pour �tre utilis�es par FO-M5
// Cette structure ne couvre pas toutes les informations transmissibles par la carte Serializer. 
// Seules les informations potentiellement utiles au projet SEM815 sont trait�es 
//*****************************************************************************************************************************************

enum Reponse {Reponse_non, Rep_getenc, Rep_vpid, Rep_dpid, Rep_pids, Rep_vel};


typedef struct INFORMATIONS_SERIALIZER // Cette structure contient toutes les informations envoy�es par la carte Serialize
	                                     // Les variables de type enum correspondent aux commandes
                                       // Les variables de type BYTE, UNSIGNED_BYTE ou int corrspondent aux param�tres
                
{  
   enum  Reponse Etat_Response;   	   // Contient le type de r�ponse re�ue � une des commandes suivantes:  "vpid" "dpid" "pids" "vel" 
   int   Read_Val_enc_1;               // information commande getenc1
   int   Read_Val_enc_2;               // information commande getenc2
   
   int   Read_P;                       //   information commande vpid dpid
   int   Read_I;                       //   information commande vpid dpid
   int   Read_D;                       //   information commande vpid dpid
   int   Read_L_A;                     //   information commande vpid (L)  dpid (A)
   BYTE  Read_Pids;                    //   information commande pids
   int   Read_Vitesse_mot1;            //   information commande "velocity" moteur 1
   int   Read_Vitesse_mot2;            //   information commande "velocity" moteur 2
   
} OUT_M2;

