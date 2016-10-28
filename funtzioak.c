

int sortuErabiltzaileDir(char *erabiltzaileak){

    //SORTU ERABILTZAILE BAKOITZAREN KARPETAK GERO BAKOITZEAN BAKOITZAREN JASOTAKO/BIDALITAKO MEZUAK GORDETZEKO
    int i=0;
    char dir[MAX_BUF];
    char azpidir[MAX_BUF];
    while(erabiltzaileak[i] != NULL){
        getcwd(dir, sizeof(dir));
        sprintf(dir, "mkdir %s%s/", dir, erabiltzaileak[i]);
        struct stat sb;
        //Karpeta ez bada existitzen sortu
        if ( !(stat(dir, &sb) == 0 && S_ISDIR(sb.st_mode))){

            // ./"erabiltzaileIzena"/
            system(dir);

            // ./"erabiltzaileIzena"/inbx/
            azpidir[0] = 0;
            sprintf(azpidir, "%s%s", dir, "inbx/");
            system(azpidir);

            // ./"erabiltzaileIzena"/sent/
            azpidir[0] = 0;
            sprintf(azpidir, "%s%s", dir, "sent/");
            system(azpidir);
        }

        i++;
    }
    return -1;

}

int bilatu_string(char *string, char **string_zerr) {

    int i=0;
    while(string_zerr[i] != NULL){
        if( !strcmp(string,string_zerr[i]) ){
            return i;
        }
        i++;
    }
    return -1;
}

int bilatu_substring(char *string, char **string_zerr) {

    int i=0;
    while(string_zerr[i] != NULL){
        if(!strncmp(string,string_zerr[i],strlen(string_zerr[i]))){
            return i;
        }
        i++;
    }
    return -1;
}

int bilatu_erab_pass(char* kom, char** args){

    if( strlen(kom) == 4){ //LGIN komandoa jaso bada argumenturik gabe
        return -1;
    }
    if( kom[4] == "@"){ //Erabiltzailea falta da
        return -1;
    }
    if( kom[strlen(kom)-1] == "@"){ //Pasahitza falta da
        return -1;
    }
    int i = 5;
    int aurkitua = 0;
    while (i < strlen(kom)-2 && !aurkitua){
        if( kom[i] == "@" ){
            aurkitua = 1;
        }
        else{
            i++;
        }
    }
    if(!aurkitua){ //Ez dago @-rik
        return -1;
    }

    //Erabiltzailea gorde
    for (int j = 4; j<i; j++){
        args[0][j-4] = kom[j];
    }

    //Pasahitza gorde
    for (int j = i+1; j<strlen(kom); j++){
        args[1][j-(i+1)] = kom[j];
    }

    return 0;
}