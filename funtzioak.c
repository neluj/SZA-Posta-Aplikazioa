int sortuErabiltzaileDir(char *erabiltzaileak){

    //SORTU ERABILTZAILE BAKOITZAREN KARPETAK GERO BAKOITZEAN BAKOITZAREN JASOTAKO/BIDALITAKO MEZUAK GORDETZEKO

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