#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/statvfs.h>

#include "zerb_fitx.h"

int main(){
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

void sesioa(int s){
	char buf[MAX_BUF], file_path[MAX_BUF], file_name[MAX_BUF];
	int n, erabiltzaile, komando, error;
	FILE *mezua;
	struct stat file_info;//??
	unsigned long file_size, irakurrita;
	char * sep;
	
	// Zehaztu uneko egoera bezala hasierako egoera.
	egoera = ST_INIT;
	
	
	while(1){
		
		
		// Irakurri bezeroak bidalitako mezua.
		if((n=readline(s,buf,MAX_BUF)) <= 0){
			return;
		}
		
		// Aztertu jasotako komandoa ezaguna den ala ez.
		if((komando=bilatu_substring(buf,KOMANDOAK)) < 0)
		{
			printf("%s komandoa ezezaguna da", komando);
			continue;
		}
		
		switch(komando){//Komandoaren arabera gauza bat egin edo bestea
			case COM_LGIN:
				if( (error = f_lgin()) < 0){
					erroreaBidali(ERR_LGIN) //1
				}
				break:
			case COM_LGOU:
				f_lgou();
				break:
			case COM_TEXT:
				if( (error = f_text()) < 0){
					erroreaBidali(ERR_TEXT) //2
				}
				break:
			case COM_RFSH:
				if( (error = f_rfsh()) < 0){
					erroreaBidali(ERR_RFSH) //3
				}
				break:
			case COM_INBX:
				if( (error = f_inbx()) < 0){
					erroreaBidali(ERR_INBX) //4
				}
				break:
			case COM_SENT:
				if( (error = f_sent()) < 0){
					erroreaBidali(ERR_SENT) //5
				}
				break:
			case COM_OPEN:
				if( (error = f_open()) < 0){
					erroreaBidali(ERR_OPEN) //6
				}
				break:
			case COM_REMV:
				if( (error = f_remv()) < 0){
					erroreaBidali(ERR_REMV) //7
				}
				break:
				
		}
		
		
		
	}
}

int bilatu_substring(char *string, char **string_zerr)
{
	int i=0;
	while(string_zerr[i] != NULL)
	{
		if(!strncmp(string,string_zerr[i],strlen(string_zerr[i])))
			return i;
		i++;
	}
	return -1;
}