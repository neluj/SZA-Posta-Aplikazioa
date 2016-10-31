#include "bez_fitx.h"
#include <stdio.h>


int main(int argc, char const *argv[])
{
	char buf[MAX_BUF], param[MAX_BUF], param2[MAX_BUF];
	char zerbitzaria[MAX_BUF];
	int portua = PORT;

	// Parametroak prozesatu.
	switch(argc)
	{
		case 1:
			strcpy(zerbitzaria, SERVER);
			break;
		case 3:
			portua = atoi(argv[2]);
		case 2:
			strcpy(zerbitzaria, argv[1]);
			break;
		default:
			printf("Erabilera: %s <zerbitzaria> <portua>\n", argv[0]);
			exit(1);
	}

	// Socketa sortu.
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Errorea socketa sortzean");
		exit(1);
	}
//proba
	// Zerbitzariko socketaren helbidea sortu.
	zerb_helb.sin_family = AF_INET;
	zerb_helb.sin_port = htons(portua);
	if((hp = gethostbyname(zerbitzaria)) == NULL)
	{
		herror("Errorea zerbitzariaren izena ebaztean");
		exit(1);
	}
	memcpy(&zerb_helb.sin_addr, hp->h_addr, hp->h_length);
	
	// Konektatu zerbitzariarekin.
	if(connect(sock, (struct sockaddr *) &zerb_helb, sizeof(zerb_helb)) < 0)
	{
		perror("Errorea zerbitzariarekin konektatzean");
		exit(1);
	}

	// Erabiltzaile eta pasahitza bidali.
	int i=0;
	do
	{
		printf("Erabiltzaile izena: ");
		fgets(param,MAX_BUF,stdin);
		param[strlen(param)-1] = 0;
		sprintf(buf,"%s%s\r\n",KOMANDOAK[COM_LGIN],param);
		
		write(sock, buf, strlen(buf));
		readline(sock, buf, MAX_BUF);
		status = parse(buf);
		if(status != 0)
		{
			fprintf(stderr,"Errorea: ");
			fprintf(stderr,"%s",ER_MEZUAK[status]);
			continue;
		}

		printf("Pasahitza: ");
		fgets(param,MAX_BUF,stdin);
		param[strlen(param)-1] = 0;
		sprintf(buf,"%s%s\r\n",KOMANDOAK[COM_PASS],param);
		
		write(sock, buf, strlen(buf));
		readline(sock, buf, MAX_BUF);
		status = parse(buf);
		if(status != 0)
		{
			fprintf(stderr,"Errorea: ");
			fprintf(stderr,"%s",ER_MEZUAK[status]);
			continue;
		}
		break;

	} while(1);

	// Begizta bat aukeren menua erakutsi eta aukera prozesatzeko.
	//bez_fitx.h fitxategixen komanduek aldatu
	do
	{
		aukera = menua();		// Erakutsi aukeren menua.
		switch(aukera)
		{
			case COM_INBX:	// Fitxategi zerrenda eskatu eta pantailaratu.
				sprintf(buf,"%s\r\n",KOMANDOAK[COM_INBX]);
				write(sock,buf,strlen(buf));				// Bidali komandoa.
				n = readline(sock, buf, MAX_BUF);		// Erantzuna jaso.
				status = parse(buf);
				if(status != 0)
				{
					fprintf(stderr,"Errorea: ");
					fprintf(stderr,"%s",ER_MEZUAK[status]);
				}
				else
				{
					// Fitxategi zerrenda jaso eta pantailaratu lerroz lerro.
					int kop = 0;	// Zerrendako fitxategi kopurua kontrolatzeko.
					printf("Jasotako mezuen zerrenda:\n");
					printf("------------------------------------------\n");
					n = readline(sock, buf, MAX_BUF);
					while(n > 2){ //while hau zetako?
						buf[n-2] = 0;
						printf("%s\t\t",strtok(buf,"?")); 
						fitx_tamaina = atol(strtok(NULL,"?"));
						kop++;
						n = readline(sock, buf, MAX_BUF);
					}
					if(kop > 0)
					{
						printf("------------------------------------------\n");
						printf("Guztira %d fitxategi eskuragarri.\n",kop);
					}
					else
						printf("Ez dago fitxategirik eskuragarri.\n");
					printf("------------------------------------------\n");
				}	
				break;

				//Behar ez diren kode-lerroak ezabatu
			case COM_SENT:	// Fitxategi zerrenda eskatu eta pantailaratu.
				sprintf(buf,"%s\r\n",KOMANDOAK[COM_SENT]);
				write(sock,buf,strlen(buf));				// Bidali komandoa.
				n = readline(sock, buf, MAX_BUF);		// Erantzuna jaso.
				status = parse(buf);
				if(status != 0)
				{
					fprintf(stderr,"Errorea: ");
					fprintf(stderr,"%s",ER_MEZUAK[status]);
				}
				else
				{
					// Fitxategi zerrenda jaso eta pantailaratu lerroz lerro.
					int kop = 0;	// Zerrendako fitxategi kopurua kontrolatzeko.
					printf("Bidalitako mezuen zerrenda:\n");
					printf("------------------------------------------\n");
					n = readline(sock, buf, MAX_BUF);
					while(n > 2){ //while hau zetako?
						buf[n-2] = 0;
						printf("%s\t\t",strtok(buf,"?")); 
						fitx_tamaina = atol(strtok(NULL,"?"));
						kop++;
						n = readline(sock, buf, MAX_BUF);
					}
					if(kop > 0)
					{
						printf("------------------------------------------\n");
						printf("Guztira %d fitxategi eskuragarri.\n",kop);
					}
					else
						printf("Ez dago fitxategirik eskuragarri.\n");
					printf("------------------------------------------\n");
				}	
				break;			

			case COM_REMV: // Mezu bat ezabatu.
				printf("Idatzi ezabatu nahi duzun fitxategiaren izena: ");
				fgets(param,MAX_BUF,stdin);
				param[strlen(param)-1] = 0;
				sprintf(buf,"%s%s\r\n",KOMANDOAK[COM_REMV], param);
				write(sock,buf,strlen(buf));				// Eskaera bidali.
				n = readline(sock, buf, MAX_BUF);		// Erantzuna jaso.
				status = parse(buf);
				if(status != 0){
					fprintf(stderr,"Errorea: ");
					fprintf(stderr,"%s",ER_MEZUAK[status]);
				}else{
					printf("%s fitxategia ezabatua izan da.\n", param);
				}
				break;

			case COM_OPEN:		// Mezu bat zabaldu.
				printf("Idatzi zabaldu nahi duzun fitxategiaren izena: ");
				fgets(param,MAX_BUF,stdin);
				param[strlen(param)-1] = 0;
				sprintf(buf,"%s%s\r\n",KOMANDOAK[COM_OPEN], param);
				write(sock,buf,strlen(buf));				// Eskaera bidali.
				n = readline(sock, buf, MAX_BUF);		// Erantzuna jaso.
				status = parse(buf);
				if(status != 0){
					fprintf(stderr,"Errorea: ");
					fprintf(stderr,"%s",ER_MEZUAK[status]);
				}else{
					//printf("%s fitxategia ezabatua izan da.\n", param);
					//mezu hori bistaratu.
					//mezuaren izenburua
					//mezuaren testua
				}
				break;

			case COM_SENT:		// Mezu bat bidali.
				printf("Idatzi bidali nahi duzun fitxategiaren izena: ");
				fgets(param,MAX_BUF,stdin);
				param[strlen(param)-1] = 0;
				printf("Idatzi hartzailearen erabiltzaile izena mesedez: ");
				fgets(param2,MAX_BUF,stdin);
				param2[strlen(param2)-1] = 0;
				sprintf(buf,"%s%s\r\n",KOMANDOAK[COM_SENT], param, param2);
				write(sock,buf,strlen(buf));				// Eskaera bidali.
				n = readline(sock, buf, MAX_BUF);		// Erantzuna jaso.
				status = parse(buf);
				if(status != 0){
					fprintf(stderr,"Errorea: ");
					fprintf(stderr,"%s",ER_MEZUAK[status]);
				}else{
					printf("%s fitxategia bidalia izan da.\n", param);
				}
				break;

			case COM_LGOU:		// Sesioa amaitu.
				sprintf(buf,"%s\r\n",KOMANDOAK[COM_LGOU]);
				write(sock,buf,strlen(buf));				// Eskaera bidali.
				n = readline(sock, buf, MAX_BUF);		// Erantzuna jaso.
				status = parse(buf);
				if(status != 0)
				{
					fprintf(stderr,"Errorea: ");
					fprintf(stderr,"%s",ER_MEZUAK[status]); //igual status aldatu ein bida
				}
				break;
		}
	}

}

int menua()
{
	//menu batetik bestera mugitzeko zelan? mezua bistaratu, ta gero menura jueteko berriro?
	char katea[MAX_BUF];
	int aukera;
	
	printf("\n");
	printf("\t\t\t\t*********************************************\n");
	printf("\t\t\t\t*********************************************\n");
	printf("\t\t\t\t**                                         **\n");
	printf("\t\t\t\t**    	  1. Jasotako mezuen zerrenda      **\n"); //OIHAN (einde)
	printf("\t\t\t\t**        2. Bidalitako mezuen zerrenda    **\n"); //OIHAN (einde)
	printf("\t\t\t\t**        3. Mezu bat ezabatu              **\n"); //OIHAN (einde)
	printf("\t\t\t\t**        4. Mezu bat zabaldu              **\n"); //JULEN
	printf("\t\t\t\t**        5. Mezu bat bidali               **\n"); //JULEN (einde)
	printf("\t\t\t\t**        6. Saioa amaitu                  **\n"); //JULEN (einde)
	printf("\t\t\t\t**                                         **\n");
	printf("\t\t\t\t*********************************************\n");
	printf("\t\t\t\t*********************************************\n");
	
	printf("\t\t\t\tEgin zure aukera: ");
	while(1)
	{
		fgets(katea,MAX_BUF,stdin);
		aukera = atoi(katea);
		if(aukera > 0 && aukera < 7)
			break;
		printf("\t\t\t\tAukera okerra, saiatu berriro: ");
	}
	printf("\n");
	return aukera;
}
