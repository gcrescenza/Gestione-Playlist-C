#include "structs.h"
#include "utils.h"
#include "video.h"
#include "playlist.h"
#include "user.h"
#include "fileHandler.h"
//.c .h video / playlist / user

int main()

{
    //creazione e allocazione memoria array user, video e playlist
    User *ar_user=NULL;
    Playlist *ar_playlist=NULL;
    Video *ar_video=NULL;
    char *logged_user=NULL;

    int choise;
    //dichiarazione e inizializzazione variali lunghezza arrays
    int len_ar_playlist=0, len_ar_video=0, len_ar_user=0;
    //file per video
    char *f_namevideo = "video.csv";
    char *f_nameplaylist="playlist.csv";
    char *f_nameuser= "user.csv";

    FILE *fp=NULL;

    do{
        printf ("1) Gestione utente\
                \n2) Gestione Video\
                \n3) Gestione Playlist\
                \n4) Carica dati di collaudo\
                \n5) Carica dati\
                \n6) Salva dati\
                \n7) Esci dal programma\n\n");

        choise = inputInteger(1, 7,"\nScegliere un'operazione da effettuare:  ");
        switch (choise){
            case 1:
                menuUser(&ar_user, &len_ar_user, &logged_user);
                break;
            case 2:
                menuVideo(&ar_video, &len_ar_video, &ar_playlist, len_ar_playlist, logged_user);
                break;
            case 3:
                menuPlaylist(&ar_playlist, &len_ar_playlist, &ar_video, &len_ar_video, logged_user);
                break;
            case 4:
                initArrays(&ar_playlist, &ar_video, &ar_user, &len_ar_playlist, &len_ar_video, &len_ar_user, &logged_user);
                printf("Dati di collaudo caricati con successo\n");
                break;
            case 5:
                userFromCSV(fp, f_nameuser, &ar_user, &len_ar_user);
                videoFromCSV(fp, f_namevideo, &ar_video, &len_ar_video);
                playlistFromCSV(fp, f_nameplaylist, &ar_playlist,ar_video, &len_ar_playlist,len_ar_video);
                printf("Dati caricati con successo\n");
                break;
            case 6:
                playlistToCSV(fp, f_nameplaylist, ar_playlist, len_ar_playlist);
                userToCSV(fp, f_nameuser, ar_user, len_ar_user);
                videoToCSV(fp, f_namevideo, ar_video, len_ar_video);
                printf("Dati salvati con successo\n");
                break;
            case 7:
                printf("Uscita in corso...\n");
                break;
            default:
                printf ("Scelta non valida!\n");
                break;
        }

    }while (choise!=7);

    printf ("Uscita effettuata!\n");




    return 0;
}