#define MAX_BUF 1024
#define SERVER "localhost"
#define PORT 6012

#define COM_USER	0 //COM ta OP-ekin dudak. Bakoitza zetako?
#define COM_PASS	1
#define COM_LIST	2
#define COM_DOWN	3
#define COM_DOW2	4
#define COM_UPLO	5
#define COM_UPL2	6
#define COM_DELE	7
#define COM_EXIT	8

#define OP_LIST	1
#define OP_DOWN	2
#define OP_UP	3
#define OP_DEL	4
#define OP_EXIT	5


char * KOMANDOAK[] = {"LGIN",/*PASS beharrezkue da?*/"PASS","TEXT","RFSH","INBX","SENT","OPEN","REMV","LGOU",NULL};
char * ER_MEZUAK[] =
{
	"Dena ondo. Errorerik ez.\n",
	"Komando ezezaguna edo ustegabekoa.\n",
	"Erabiltzaile ezezaguna.\n",
	"Pasahitz okerra.\n",
	"Arazoa fitxategi zerrenda sortzen.\n",
	"Fitxategia ez da existizen.\n",
	"Arazoa fitxategia jeistean.\n",
	"Erabiltzaile anonimoak ez dauka honetarako baimenik.\n",
	"Fitxategiaren tamaina haundiegia da.\n",
	"Arazoa fitxategia igotzeko prestatzean.\n",
	"Arazoa fitxategia igotzean.\n",
	"Arazoa fitxategia ezabatzean.\n"
};

int parse(char *status);
int readline(int stream, char *buf, int tam);
int menua();
