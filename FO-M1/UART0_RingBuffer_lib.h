//*************************************************************************************************
// Paramètres modifiables
//*************************************************************************************************
#define       MAX_BUFLEN 64 // Taille des buffers de données

extern unsigned char flaginbuf;
extern unsigned char flagCR;

void init_Serial_Buffer(void);
unsigned char serOutchar(char c);
char serInchar(void); 
unsigned int serInchar_Bin(void);
char* serInBuf(void);
unsigned char serOutstring(char *buf);
void cfg_Clock_UART(void);
void cfg_UART0_mode1(void);
void readInbuf(int i);
void checkCR(int i);