//------------------------------------------------------------------------------------
// serializer.h
//------------------------------------------------------------------------------------
// AUTH:PEREL/RANDU
// DATE:07/10/2015
//
// Target: C8051F02x
// Tool chain: KEIL Eval 'c'
//



void talk_serializer(struct COMMANDES_SERIALIZER  *s,struct INFORMATIONS_SERIALIZER *r);

void Send_Serializer(const char* char_ptr);

void serializer_response();

void receive_traduite(char *response, int option,struct INFORMATIONS_SERIALIZER *r);