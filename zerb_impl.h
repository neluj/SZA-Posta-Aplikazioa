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
char * erab_zer[] = {"xabiier", "tiza", "", NULL};
char * pass_zer[] = {"djsona", "pipo", "", NULL};
int bilatu_erab_pass(char* kom, char** args);
int bilatu_string(char *string, char **string_zerr);
int bilatu_substring(char *string, char **string_zerr);
void sesioa(int s);

int f_lgin(char *com);
int f_lgou();
int f_text(char *com);
int f_rfsh();
