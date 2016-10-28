int erroreaBidali(int err, int elkarrizketa){

    char *err_mez = (char*)malloc(sizeof(char)*3);
    //Hau da, ER eta X, X 1etik 7-rako zenbaki bat izanik
    //Adibidez: ER1, ER2...
    err_mez[0] = 'E';
    err_mez[1] = 'R';
    err_mez[2] = err + 48; //ASCII-ra pasatu errore-zenbakia
    int luz = strlen(err_mez);
    if( write(elkarrizketa, err_mez, luz) < luz){
        exit(1);
    }
    close(elkarrizketa);
}

int f_lgin(char *kom, int elkarrizketa, int *erabiltzailea){

    char** argumentuak = (char**)malloc(sizeof(char)*2*MAX_BUF);
    if( ( n = bilatu_erab_pass(kom, argumentuak) ) < 0){
        return -1;
    }
    else{
        aurkitu = 0;
        //Erabiltzailearen indizea gordeko du (Aurkitu ezean -1)
        if( (*erabiltzailea=bilatu_string(argumentuak[0], erab_zer)) < 0){
            return -1;
        }
        if( bilatu_string(argumentuak[1], pass_zer) < 0){
            return -1;
        }
        erabiltzaile = (char*)malloc(sizeof(argumentuak[0]));
        strcpy(erabiltzaile, argumentuak[0]);
    }
}

int f_lgou(int elkarrizketa, int *erabiltzaile){

    *erabiltzaile = -1;
    close(elkarrizketa);
    exit(0);

}

int f_text(char* kom, int elkarrizketa, int erabiltzailea){
    //Protokoloa aldatu behar da, fitxategiaren tamaiana jakin behar dugu osorik jaso dugula jakiteko, astelehenean komentatu
    1,2,3,4,5,6,7,8,9,10

}

int f_rfsh(int elkarrizketa, int erabiltzailea){


}

int f_inbx(int elkarrizketa, int erabiltzailea){


}

int f_inbx(int elkarrizketa, int erabiltzailea){


}


int f_open(char* kom, int elkarrizketa, int erabiltzailea){


}

int f_remv(char* kom, int elkarrizketa, int erabiltzailea){


}