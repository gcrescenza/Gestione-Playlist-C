//
// Created by Silvano on 20/03/2021.
//

#include "utils.h"
#include <time.h>
#include <strings.h>
#include <ctype.h>

void initArrays (Playlist ** array_playlist, Video **array_video, User **array_user, int *length_array_playlist, int*length_array_video, int*length_array_user, char **logged_user) {

    *array_user = (User *) malloc(sizeof(User));
    *array_playlist = (Playlist *) realloc(*array_playlist, 5 * sizeof(Playlist));
    (*array_user)[0] = (User) {
            .nickname="nickname1",
            .name="name1",
            .surname="surname1",
            .gender='M',
            .birth_date =(Date) {.day=1, .month=1, .year=1989},
            .password="password1",
    };
    *logged_user = (*array_user)[0].nickname;

    *array_video = (Video *) realloc(*array_video, 5 * sizeof(Video));
    *length_array_playlist = 5, *length_array_video = 5, *length_array_user = 1;

    int i = 0;
    while (i < 5) {
        (*array_playlist)[i] = (Playlist) {
                .owner=(*array_user)[0].nickname,
                .title=strdup((char[]) {'t', 'i', 't', 'l', 'e', '0' + i, '\0'}),
                .creation_date=getCurrentDate(),
                .n_plist_videos=0,
                .video_list=NULL
        };
        i++;
    }

    i = 0;
    while (i < 5) {
        (*array_video)[i] = (Video) {
                .title=strdup((char[]) {'t', 'i', 't', 'l', 'e', '0' + i, '\0'}),
                .description=strdup(
                        (char[]) {'d', 'e', 's', 'c', 'r', 'i', 'p', 't', 'i', 'o', 'n', '0' + i, '\0'}),
                .author=strdup((char[]) {'a', 'u', 't', 'h', 'o', 'r', '0' + i, '\0'}),
                .length=rand() % 10,
                .owner=(*array_user)[0].nickname,
        };
        i++;
    }

    (*array_playlist)[0].video_list = (char ***) calloc(sizeof(char **), 4);
    (*array_playlist)[0].n_plist_videos = 4;

    i = 0;
    while ( i<4 )
    {
        (*array_playlist)[0].video_list[i] = &(*array_video)[i].title;
        i++;
    }
}


Date getCurrentDate (){
    Date * date= (Date*)malloc(sizeof(Date));
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    date->year = tm.tm_year + 1900;
    date->month = tm.tm_mon + 1;
    date->day = tm.tm_mday;
    return *date;
}

Date inputDate (Date data_max){

    Date * date= (Date*)malloc(sizeof(Date));
    int check_date;
    do
    {
        date->year=inputInteger (1910, 3000, "inserisci anno di nascita: ");
        date->month=inputInteger (1,12, "inserisci mese di nascita: ");
        date->day = inputInteger (1, 31, "inserisci giorno di nascita: ");
        check_date=checkDate(data_max, *date);
        if(check_date==-1)
        {
            printf("la data inserita contiene un errore\n");
        }
        else
        if(check_date==0)
        {
            printf("la data inserita non e' precedente a %d/%d/%d\n",data_max.day,data_max.month,data_max.year);
        }
    } while(check_date!=1);

    return *date;

}

int checkDate (Date date_1, Date date_2){//date_1=data massima; date_2=data nascita utente


    int age_allowed = 0;
    if(!dateCorrect(date_2))
    {
        return -1;
    }


    if ( date_1.year > date_2.year )
        age_allowed = 1;
    else if ( date_1.year == date_2.year )
    {
        if (date_1.month > date_2.month)
            age_allowed = 1;
        else if (date_1.month == date_2.month)
            if (date_1.day >= date_2.day)
                age_allowed = 1;
    }
    return age_allowed;
}

char inputChar (char char_1, char char_2, char *string_output){

    char c;
    char_1=(char)tolower(char_1);
    char_2=(char)tolower(char_2);
    do
    {
        c=(char)tolower(*inputString(1,1,string_output));
        if ( c != char_2 && c != char_1 )
        {
            printf("Input non valido, il carattere deve essere %c o %c \n", char_2, char_1);
        }
    } while( c != char_2 && c != char_1 );
    return c;
}

int inputInteger (int min, int max, char* string_output){

    int n;
    char s[300];//dichiarando char *s mi dava errore SIGSEGV

    do {
        do
        {
            printf("%s", string_output);
            fgets(s, 300, stdin);
            n = isNaturalNumber(s);  //con il cast ho tolto un warning, strlen() ritorna unsigned long
            if ( n == -1 )
                printf ("Input non valido, inserire un intero\n");
        } while ( n == -1);
        if( n < min ||n > max )
        {
            printf("Input non valido, il valore deve essere compreso tra %d e %d\n", min, max);
        }
    } while( n < min || n > max );
    return n;
}

char* inputString (int min, int max, char* string_output){
    char *s= (char *) calloc(max, sizeof(char));
    do
    {
        printf("%s", string_output);
        fgets(s, 300, stdin);       //fgets() salvera' nella stringa s anche il carattere \n
        s[strcspn(s, "\n")]=0;  //per questo usiamo strcspn che cosi' com'e' scritta l'istruzione scambia il carattere \n contenuto in s  con \0
        if(strlen(s)<min || strlen(s)> max)
        {
            printf("Input non valido la lunghezza della stringa deve essere compresa tra %d e %d\n", min, max);
        }
    } while(strlen(s)<min || strlen(s)> max);
    return s;
}

int dateCorrect(Date data){
    int months30[4]= {4,6,9,11};
    int monthis30=0;

    if(data.month<1 || data.month>12)
        return 0;
    int i=0;
    while (i<4)
    {
        if(months30[i] == data.month)
            monthis30 = 1;
        i++;
    }

    if ( data.month == 2 )
    {
        if (isBisestile(data.year))
            return (data.day <= 29);
        else
            return (data.day <= 28);
    }
    if (data.day <= 30 && monthis30)
        return 1;
    if (data.day <= 31 && !monthis30)
        return 1;
    else
        return 0;


}

int isBisestile (int anno){

    if (anno % 100 == 0)
        return (anno % 400 == 0);

    return (anno % 4 == 0);

}
//isNaturalNumber ritorna -1 se la stringa non contiene un numero valido, altrimenti ritorna la stringa convertita in int
//numero valido: qualsiasi intero 0 compreso (e' concesso solo uno zero) preceduto e/o seguito da un numero arbitrario di spazi
int isNaturalNumber (char *s){

    int n=0;//variabile in cui verra' memorizzata la stringa convertita
    char *ptr;//variabile puntatore in cui verra' memorizzato l'indirizzo del primo carattere non numerico di s

    if (strcmp(s, "0")==0)
    {
        return n;
    }
    if (strcmp(s, "\n")==0)
    {
        return -1;
    }
    n = (int) strtol(s, &ptr,10);//ptr = s + i, dove i e' l'indice del primo carattere non numerico. ovvero a ptr e' assegnato l'indirizzo della prima occorrenza di un carattere non numerico nella stringa s. la funzione strol vuole come argomenti(char* stringa, char** indirizzo_di_una_stringa, int base)
    if ((*ptr != '\n') && n>0) {//se il primo carattere non numerico non e' 'INVIO'
        if (*ptr != ' ')//e se e' anche diverso da uno spazio
            return -1;//la stringa non e' un numero valido
        else {//altrimenti

            while (*ptr == ' ')//finche' il carattere e' uno spazio
                ptr++;//vai al carattere successivo
            if (*ptr != '\n')//se il carattere non e' 'INVIO'
                return -1;//la stringa non e' un numero valido

            return n;
        }
    }
    else//se il primo carattere non numerico della stringa e' 'INVIO'

    return n;//la stringa contiene un numero valido

}