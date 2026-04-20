//
// Created by Silvano on 20/03/2021.
//

#include "video.h"
#include "utils.h"
#include "playlist.h"
#include "fileHandler.h"
void addVideo (Video **array_video, int *length_array_video, const char* logged_user){

    int index_video;	   	         	 //indice di array_video[]
    Video temp_video;	                 //variabile usata per immaganizzare i dati del video

    do
    {
        temp_video.title = inputString(1, 50, "Inserisci titolo del video");
        index_video = searchVideoIndex(temp_video.title, *array_video, *length_array_video);
        if (index_video != -1)
            printf("Nome video gia' presente");
    } while ( index_video != -1 );

    temp_video.author = inputString(1,50, "Inserisci autore del video");
    temp_video.description = inputString(1,150, "Inserisci descrizione del video");
    temp_video.length = inputInteger(1,(int)INFINITY, "Inserisci durata del video");
    temp_video.owner=logged_user;
    *length_array_video += 1;
    *array_video=(Video*)realloc(*array_video, *length_array_video*sizeof(Video));
    (*array_video)[*length_array_video - 1] = temp_video;
            printf("Video creato con successo\n\n");


}

void removeVideo (Video **array_video, int *length_array_video, Playlist **array_playlist, const int length_array_playlist){
    //la funzione non controlla se ci sia almeno un video in archivio
    int i;
    int video_deleted;
    char *video_title = inputString ( 1, 50, "Inserisci titolo del video da cancellare: " );
    i = 0;
    video_deleted = 0;
    while ( i < *length_array_video && video_deleted == 0)
    {
        if ( !strcmp(video_title ,(*array_video)[i].title))
        {
            updateVideoLists(array_playlist, length_array_playlist, video_title);
            (*array_video)[i] = (*array_video)[*length_array_video-1];
            *length_array_video -= 1;
            (*array_video)=(Video*)realloc(*array_video, *length_array_video*sizeof(Video));
            video_deleted = 1;
        }
        i++;
    }
    if ( video_deleted != 1 )
        printf ( "Video non presente\n" );
    else
        printf ( "Video eliminato\n" );

}

void modifyVideo (Video *array_video, int length_array_video){

    int valid_attribute;
    int	video_to_change_index;//l'indice del video da modificare
    int video_index;//indice per controllare che il nuovo titolo non sia gia' presente in archivio
    char *attribute;
    char *title, *new_video_title;

    do
    {
        title = inputString ( 1, 50, "Inserisci il titolo del video da modificare: " );
        video_to_change_index = searchVideoIndex ( title, array_video, length_array_video );
        if ( video_to_change_index == -1 )
            printf ( "Video non presente\n" );
    } while (video_to_change_index == -1);

    do
    {
        valid_attribute = 1;
        attribute = inputString ( 1, 20, "Inserisci l'attributo da cambiare (i valori validi sono: titolo|descrizione|durata|autore): " );
        if ( strcmp (attribute, "titolo" ) == 0)
        {
            do
            {
                new_video_title = inputString ( 1, 50, "Inserire un nuovo titolo per il video: " );
                video_index = searchVideoIndex ( new_video_title, array_video, length_array_video );//controlla che il nuovo titolo non sia gia' presente
                if ( strcmp(new_video_title, title)==0)
                    video_index = -1;
                if ( video_index != -1 )
                    printf ( "Titolo gia' presente\n" );
            } while ( video_index != -1 );
            array_video[video_to_change_index].title = new_video_title;//video_index vale sempre -1 altrimenti non uscirebbe dal while precedente. c'e' bisogno di un'altra variabile
        } else if ( strcmp (attribute, "descrizione" ) == 0 )
            array_video[video_to_change_index].description = inputString ( 1, 150, "Inserire una nuova descrizione del video" );
        else if ( strcmp (attribute, "durata" ) == 0)
            array_video[video_to_change_index].length = inputInteger ( 1, (int)INFINITY, "Inserire la nuova durata del video: " );
        else if ( strcmp (attribute, "autore" ) == 0 )
            array_video[video_to_change_index].author = inputString ( 1, 50, "Inserire il nome dell’autore: " );
        else
        {
            valid_attribute = 0;
            printf ( "Attributo non valido\n" );
        }
    } while ( !valid_attribute );

}

void searchVideoByAuthor (Video *array_video, int length_array_video){

    char *tmp_author;
    int video_matched=0;

    tmp_author = inputString (1, 50, "Inserisci nome del'autore del video: ");

    int i=0;
    while ( i < length_array_video )
    {
        if (strcmp(tmp_author, array_video[i].author)==0)
        {
            printf ( "Titolo: %s\n", array_video[i].title);
            printf ( "Descrizione: %s\n", array_video[i].description );
            printf ( "Durata: %d\n", array_video[i].length );
           printf (  "Proprietario: %s\n", array_video[i].owner );
            video_matched=1;
        }
        i++;
    }
    if (video_matched==0)
        printf ("\nNon sono stati trovati video associati a questo autore!\n");

}

void searchVideoByTitle (Video *array_video, int length_array_video){

    int i;	   	         //indice di array_video[]
    char *tmp_title;	                 //titolo del video da cercare

    tmp_title = inputString(1, 50, "Inserisci titolo del video da cercare: ");
    i = searchVideoIndex(tmp_title, array_video, length_array_video);
    if (i!=-1)
    {
        printf ( "Titolo: %s\n", array_video[i].title);
        printf ( "Descrizione: %s\n", array_video[i].description );
        printf ( "Durata: %d\n", array_video[i].length );
        printf ( "Proprietario: %s\n", array_video[i].owner );
    } else
        printf ("Non sono stati trovati video con questo titolo!\n");
}

void printAllVideos (Video* array_video, int length_array_video){

    if (length_array_video == 0)
        printf ("Non ci sono video in archivio\n");

    int i=0;
    while (  i < length_array_video )
    {
        printf ( "Video #%d::\n", i+1);       //aggiunto per elencare il num video, per comodita'
        printf ( "Titolo: %s\n", array_video[i].title);
        printf ( "Autore: %s\n", array_video[i].author);
        printf ( "Descrizione: %s\n", array_video[i].description);
        printf ( "Durata: %d\n", array_video[i].length);
        printf ( "Proprietario: %s\n", array_video[i].owner);
        i++;
    }
}

int searchVideoIndex (char* title, Video* array_video, int length_array_video){

    int i=0;
    while ( i<length_array_video )
    {
        if ( !strcmp(array_video[i].title, title))//array_video[i].title == title non da gli effetti sperati, strcmp si'
            return i;
        i++;
    }
    return -1;
}

void menuVideo(Video **array_video, int *length_array_video, Playlist **array_playlist, const int length_array_playlist, const char *logged_user) {

    int key;

    do
    {
        printf("1) Crea video\
				\n2) Modifica video\
				\n3) Rimuovi video\
				\n4) Stampa tutti i video\
                \n5) Cerca video per titolo\
                \n6) Cerca video per autore\
                \n7) Torna al menu principale\n");

        key = inputInteger(1, 8, "\nScegli operazione da effettuare: ");
        if (logged_user == NULL && key < 4)
        {
            printf("Per effettuare questa operazione devi essere loggato\n");
            continue;
        }
        switch (key)
        {
            case 1:
                printf("\tCrea video\n");
                addVideo(array_video, length_array_video,logged_user);
                break;
            case 2:
                printf("\tModifica video\n");
                modifyVideo(*array_video, *length_array_video);
                break;
            case 3:
                printf("\tRimuovi video\n");
                removeVideo(array_video, length_array_video, array_playlist, length_array_playlist);
                break;
            case 4:
                printf("\tStampa tutti i video\n");
                printAllVideos(*array_video, *length_array_video);
                break;
            case 5:
                printf ("\tCerca video per titolo\n");
                searchVideoByTitle(*array_video, *length_array_video);
                break;
            case 6:
                printf ("\tCerca video per autore\n");
                searchVideoByAuthor(*array_video, *length_array_video);
                break;
            case 7:
                break;
            default:
                printf("!");
                break;
        }//fine switch

    } while (key != 7);
}

void videoToCSV (FILE *fp, char *fname, Video* array_video, int length_array_video){

    fp=fopen(fname, "w");
    if (!fp)
    {
        printf ("Impossibile aprire il file %s (controllare se e' aperto in scrittura da altri processi)\n", fname);
    }
    int i=0;
    while ( i<length_array_video )
    {
        fprintf(fp, "%s;", array_video[i].title);
        fprintf(fp, "%s;", array_video[i].author);
        fprintf(fp, "%s;", array_video[i].description);
        fprintf(fp, "%d;", array_video[i].length);
        fprintf(fp, "%s;", array_video[i].owner);//non viene mem nel video User* owner
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

void videoFromCSV (FILE *fp, char *nome_file, Video **array_video, int *length_array_video){

    fp=fopen(nome_file, "r");
    if (!fp)
    {
        printf ("Impossibile aprire il file %s (controllare se il file esiste ed e' nella stessa cartella del file exe)\n", nome_file);
        return;
    }

    char buff[1024];
    *length_array_video=contaRigheCSV(nome_file);
    *array_video=(Video*)malloc(*length_array_video*sizeof(Video));

    int i=0;
    while ( !feof(fp) )
    {
        if(fgets(buff,sizeof(buff),fp)!=NULL) //non raggiunge EOF prima di leggere caratteri
        {
            if(buff[strlen(buff)-1]!='\0')//consuma il \n finale
                buff[strlen(buff)-1]='\0';

            (*array_video)[i]=(Video)
                {
                    .title=strdup(strtok(buff, ";")),
                    .author=strdup(strtok(NULL, ";")),
                    .description=strdup(strtok(NULL, ";")),
                    .length=atoi(strtok(NULL, ";)")),
                    .owner=strdup(strtok(NULL, ";")),
                };
        }
        i++;
    }
    fclose(fp);
}