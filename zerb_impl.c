#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//prueba
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/statvfs.h>
#include <malloc.h>

#include "zerb_fitx.h"

int main(){
    sortuDirektorioak(erab_zer);

	int sock, elkarrizketa;
	struct sockaddr_in zerb_helb;
	socklen_t helb_tam;
	
	// Sortu socketa.
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Errorea socketa sortzean");
		exit(1);
	}
	
	memset(&zerb_helb, 0, sizeof(zerb_helb)); //zerb_helb 0-ra hasieratu
	zerb_helb.sin_family = AF_INET; 
	zerb_helb.sin_addr.s_addr = htonl(INADDR_ANY);  //IP helbidea adierazi
	zerb_helb.sin_port = htons(PORT); //Portua adierazi

	// Esleitu helbidea socketari.	
	if(bind(sock, (struct sockaddr *) &zerb_helb, sizeof(zerb_helb)) < 0){
		perror("Errorea socketari helbide bat esleitzean");
		exit(1);
	}
	
	// Ezarri socketa entzute socket gisa.
	if(listen(sock,5) < 0){
		perror("Errorea socketa entzute socket bezala ezartzean");
		exit(1);
	}

	// Adierzi SIG_CHLD seinalea jasotzean ez dela ezer egingo. Modu honetan amaitutako prozesu umeak ez dira zonbi egoeran geratuko.
	signal(SIGCHLD, SIG_IGN);


	sortuErabiltzaileDir(erab_zer);

	while(1)
	{
	
		// Onartu konexio eskaera eta sortu elkarrizketa socketa.
		if((elkarrizketa = accept(sock, NULL, NULL)) < 0)
		{
			perror("Errorea konexioa onartzean");
			exit(1);
		}

		// Sortu prozesu ume bat bezeroarekin komunikatzeko.
		switch(fork())
		{
			case 0:
				close(sock);
				sesioa(elkarrizketa);
				close(elkarrizketa);
				exit(0);
			default:
				close(elkarrizketa);
		}
	}
}

void sesioa(int elkarrizketa) {
	char buf[MAX_BUF];
	int n, komando, error;

	int erabiltzailea = -1; //Erabiltzailearen indizea 'erab_zer' zerrendan
	FILE *mezua;
	unsigned long file_size, irakurrita;
	char *sep;

	// Zehaztu uneko egoera bezala hasierako egoera.
	int egoera = ST_INIT;


	while (1) {


		// Irakurri bezeroak bidalitako mezua (komandoa bera bere argumentuekin batera)
		if ((n = read(s, buf, MAX_BUF)) <= 0) {
			return;
		}

		// Aztertu jasotako komandoa ezaguna den ala ez.
		if ((komando = bilatu_substring(buf, KOMANDOAK)) < 0) {
			printf("%s komandoa ezezaguna da", komando);
			continue;
		}

		switch (komando) {//Komandoaren arabera gauza bat egin edo bestea
			case COM_LGIN:
				if ((egoera != ST_INIT) || (f_lgin(n, elkarrizketa, &erabiltzailea) < 0)) {
					erroreaBidali(ERR_LGIN, elkarrizketa); //1
				}
				egoera = ST_AUTH;
				break;
			case COM_LGOU:
				if (egoera == ST_AUTH) {
					f_lgou(elkarrizketa, &erabiltzailea);
					egoera = ST_INIT;
				}
				break;
			case COM_TEXT:
				if ((egoera != ST_INIT) || (f_text(n, elkarrizketa, erabiltzaile) < 0)) {
					erroreaBidali(ERR_TEXT, elkarrizketa); //2
				}
				f_text();
				break;
			case COM_RFSH:
				if ((egoera != ST_INIT) || (f_rfsh(elkarrizketa, erabiltzaile) < 0)) {
					erroreaBidali(ERR_RFSH, elkarrizketa); //3
				}
				f_rfsh();
				break;
			case COM_INBX:
				if ((egoera != ST_INIT) || (f_inbx(elkarrizketa, erabiltzaile) < 0)) {
					erroreaBidali(ERR_INBX, elkarrizketa); //4
				}
				f_inbx();
				break;
			case COM_SENT:
				if ((egoera != ST_INIT) || (f_sent(elkarrizketa, erabiltzaile) < 0)) {
					erroreaBidali(ERR_SENT); //5
				}
				break;
			case COM_OPEN:
				if ((egoera != ST_INIT) || (f_open(n, elkarrizketa, erabiltzaile) < 0)) {
					erroreaBidali(ERR_OPEN, elkarrizketa); //6
				}
				break;
			case COM_REMV:
				if ((egoera != ST_INIT) || (f_remv(n, elkarrizketa, erabiltzaile) < 0)) {
					erroreaBidali(ERR_REMV, elkarrizketa); //7
				}
				break;
		}
	}
}
