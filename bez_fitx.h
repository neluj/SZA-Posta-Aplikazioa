#define MAX_BUF 1024
#define SERVER "localhost"
#define PORT 6012

#define ERR_LGIN	1
#define ERR_TEXT	2
#define ERR_RFSH	3
#define ERR_INBX	4
#define ERR_SENT	5
#define ERR_OPEN	6
#define ERR_REMV	7

#define OP_SEND_LIST	1
#define OP_RECV_LIST	2
#define OP_DOWN			3
#define OP_UP			4
#define OP_DEL			5
#define OP_EXIT			6


char * KOMANDOAK[] = {"LGIN", "LGOU", "TEXT", "RFSH", "INBX", "SENT", "OPEN", "REMV", NULL};
char * ER_MEZUAK[] = //mezuak aldatu bidie
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
