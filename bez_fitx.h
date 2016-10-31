#define MAX_BUF 1024
#define SERVER "localhost"
#define PORT 6012


#define COM_LGIN	0
#define COM_PASS	1
#define COM_LGOU	2
#define COM_RFSH	3
#define COM_INBX	4
#define COM_SENT	5
#define COM_OPEN	6
#define COM_REMV	7


char * KOMANDOAK[] = {"LGIN","PASS","LGOU", "TEXT", "RFSH", "INBX", "SENT", "OPEN", "REMV", NULL};
char * ER_MEZUAK[] = //mezuak lekuz aldatu bidie
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
