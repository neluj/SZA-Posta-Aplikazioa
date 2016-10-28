#define MAX_BUF 1024

#define ST_INIT	0
#define ST_AUTH	1

#define ERR_LGIN	1
#define ERR_TEXT	2
#define ERR_RFSH	3
#define ERR_INBX	4
#define ERR_SENT	5
#define ERR_OPEN	6
#define ERR_REMV	7


#define COM_LGIN	0
#define COM_LGOU	1
#define COM_TEXT	2
#define COM_RFSH	3
#define COM_INBX	4
#define COM_SENT	5
#define COM_OPEN	6
#define COM_REMV	7

char * KOMANDOAK[] = {"LGIN", "LGOU", "TEXT", "RFSH", "INBX", "SENT", "OPEN", "REMV", NULL};
char * erab_zer[] = {"xabiier", "tiza", "a", NULL};
char * pass_zer[] = {"djsona", "pipo", "a", NULL};


void sesioa(int s);