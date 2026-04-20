//
// Created by Silvano on 20/03/2021.
//

#include "user.h"
#include "utils.h"
#include "fileHandler.h"

//problema con INFINITY e inputString
void createUser (User **array_user, int *length_array_user){//il secondo parametro va passato per riferimentp perche' ci serve che ritorni aggiornato. correggere output nello pseudocodice

    User temp_user;
    int user_index;
    Date actual_date=getCurrentDate();//acquisiamo la data dal sistema
    Date data_max=actual_date;
    data_max.year = actual_date.year - 16;//la data limite sara' quella attuale - 16 (che potremmo definire con un '#define AGE 16' in utils.h)
    do
    {
        temp_user.nickname = inputString ( 8, 300, "\nInserisci il tuo Nickname: " );//modificato temporneamente 300 invece di INFINITY
        user_index = searchUserIndex ( temp_user.nickname, *array_user, *length_array_user);
        if (user_index != -1)
            printf ( "\nIl nickname inserito e' gia' in uso da un altro utente");
    } while ( user_index != -1 );
    temp_user.name = inputString ( 1, 50, "Inserisci il tuo nome: " );
    temp_user.surname = inputString ( 1, 50, "Inserisci il tuo cognome: ");
    temp_user.gender = inputChar ( 'M', 'F', "Inserisci il tuo sesso (M/F): ");
    temp_user.birth_date = inputDate (data_max);
    temp_user.password = inputString ( 8, 16, "Inserisci la tua password: " );
    *length_array_user += 1;
    *array_user=(User*)realloc(*array_user, (*length_array_user) *sizeof(User));
    (*array_user)[ *length_array_user-1 ] = temp_user;
    printf ("Account creato\n");
}

char * userLogin (User *array_user, int length_array_user){

    int user_index, attempts, login;
    char *user=NULL, *password=NULL, *logged_user=NULL;

        user = inputString ( 1, 50, "Inserire nickname utente" );
        user_index = searchUserIndex ( user, array_user, length_array_user );
        if ( user_index == -1 ){
            printf ( "Utente non presente\n" );
            return NULL;
        }
    login = 0;
    attempts = 0;
    do
    {
        password = inputString ( 8, 16, "Inserire password" );
        if ( (strcmp(password, array_user[user_index].password) != 0 ))
        {
            printf ( "Password errata!\n" );
            attempts++;
        }
        else
        {
            logged_user = user ;
            login = 1 ;
            printf ( "Login effettuato\n");
        }
    } while (attempts<3 && login != 1);//era sbagliato l'uso dell' OR
    if (attempts == 3)
        printf ("E’ stato raggiunto il limite dei tentativi\n");
    return logged_user;
}

void userLogout (char **logged_user){

    if (!logged_user)
        printf ("Utente non loggato\n");
    else
    {
        printf("Uscita in corso...\nUscita effettuata!\n");
        *logged_user = NULL;
    }

}

int searchUserIndex (char* nickname, User* array_user, int length_array_user){

    int i=0;
    while ( i<length_array_user )
    {
        if (strcmp(array_user[i].nickname, nickname)==0)
            return i;
        i++;
    }
    return -1;
}

void menuUser(User **array_user, int *length_array_user, char **logged_user){

    int key;

    do
    {
        printf("1) Crea utente\
				    \n2) Login\
				    \n3) Logout\
				    \n4) Torna al menu principale\n\n");

        key = inputInteger(1, 4, "Scegli operazione da effettuare: ");
        switch (key)
        {
            case 1:
                printf("\tCrea utente\n");
                createUser(array_user, length_array_user);
                break;
            case 2:
                printf("\tLogin\n");
                *logged_user = userLogin(*array_user, *length_array_user);
                break;
            case 3:
                printf ("Logout\n");
                userLogout(logged_user);
                break;
            case 4:
                break;
            default:
                printf("!");
                break;
        }//fine switch
    } while ( key!=4 );
}

void userToCSV (FILE *fp, char *fname, User* array_user, int length_array_user){

    fp=fopen(fname, "w");
    if (!fp)
    {
        printf ("Impossibile aprire il file %s (controllare se e' aperto in scrittura da altri processi)\n", fname);
    }
    int i=0;
    while (i<length_array_user)
    {
        fprintf(fp, "%s;", array_user[i].nickname);
        fprintf(fp, "%s;", array_user[i].name);
        fprintf(fp, "%s;", array_user[i].surname);
        fprintf(fp, "%c;", array_user[i].gender);
        fprintf(fp, "%d;", array_user[i].birth_date.day);
        fprintf(fp, "%d;", array_user[i].birth_date.month);
        fprintf(fp, "%d;", array_user[i].birth_date.year);
        fprintf(fp, "%s;", array_user[i].password);
        fprintf(fp, "%c", '\n');
        i++;
    }
    printf ("scrittura effettuata con successo!\n");
    fclose(fp);
    if (!feof(fp))//non sono sicuro che sia questo il giusto confronto. feof(fp) se vera allora il file non e' stato chiuso con successo
        printf ("File chiuso con successo\n");
    else
        printf ("File non chiuso\n");

}

void userFromCSV (FILE *fp, char *nome_file, User **array_user, int *length_array_user){

    fp=fopen(nome_file, "r");
    if (!fp)
    {
        printf ("Impossibile aprire il file %s (controllare se il file esiste ed e' nella stessa cartella del file exe)\n", nome_file);
        return;
    }

    char buff[1024];
    *length_array_user=contaRigheCSV(nome_file);
    *array_user=(User*)malloc(*length_array_user*sizeof(User));

    int i=0;
    while (!feof(fp))
    {
        if(fgets(buff,sizeof(buff),fp)!=NULL) //non raggiunge EOF prima di leggere caratteri
        {
            if(buff[strlen(buff)-1]!='\0')//consuma il \n finale
                buff[strlen(buff)-1]='\0';
            (*array_user)[i]=(User){
                    .nickname=strdup(strtok(buff, ";")),
                    .name=strdup(strtok(NULL, ";")),
                    .surname=strdup(strtok(NULL, ";")),
                    .gender=(char) atoi(strtok(NULL, ";")),
                    .birth_date.day=atoi(strtok(NULL, ";)")),
                    .birth_date.month=atoi(strtok(NULL, ";)")),
                    .birth_date.year=atoi(strtok(NULL, ";)")),
                    .password=strdup(strtok(NULL, ";")),
            };
        }
        i++;
    }
    fclose(fp);
}