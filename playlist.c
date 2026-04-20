//
// Created by Silvano on 20/03/2021.
//

#include "playlist.h"
#include "utils.h"
#include "video.h"
#include "fileHandler.h"

void searchPlaylistByTitle (Playlist *array_playlist, int length_array_playlist){

    int i;
    char *plist_title;

    plist_title = inputString(1, 50, "Inserisci titolo della playlist da cercare: ");
    i = searchPlaylistIndex(plist_title, array_playlist, length_array_playlist);
    if (i!=-1)
    {
        printf ("\nTitolo: %s", array_playlist[i].title);
        printf ( "\nProprietario: %s", array_playlist[i].owner );
        printf ( "\nNumero video: %d", array_playlist[i].n_plist_videos );
        printf ( "\nData Creazione: %d/%d/%d", array_playlist[i].creation_date.day, array_playlist[i].creation_date.month, array_playlist[i].creation_date.year);
        if ( array_playlist[i].n_plist_videos != 0 )
        {
            printf ( "\nTitoli dei video presenti: " );

            int j=0;
            while (j < array_playlist[i].n_plist_videos)
            {
                printf(" %s", *(array_playlist[i].video_list[j]));
                j++;
            }
        }
    } else
        printf ("\nNon e' stata trovata nessuna playlist con questo titolo!\n");
}

void searchPlaylistByOwner (Playlist *array_playlist, int length_array_playlist){

    char *tmp_owner;
    int plist_matched;

    tmp_owner = inputString (1, 50, "\nInserisci nickname del proprietario della playlist: ");
    plist_matched = 0;

    int i=0;
    while ( i < length_array_playlist )
    {
        if (strcmp(tmp_owner, array_playlist[i].owner)==0)
        {
            printf ("\nTitolo: %s", array_playlist[i].title);
            printf ( "\nProprietario: %s", array_playlist[i].owner );
            printf ( "\nNumero video: %d", array_playlist[i].n_plist_videos );
            printf ( "\nData Creazione: %d/%d/%d", array_playlist[i].creation_date.day, array_playlist[i].creation_date.month, array_playlist[i].creation_date.year);
            plist_matched++;
            if ( array_playlist[i].n_plist_videos != 0 )
            {
                printf("\nTitoli dei video presenti: ");

                int j = 0;
                while ( j < array_playlist[i].n_plist_videos )
                {
                    printf(" %s", *(array_playlist[i].video_list[j]));
                    j++;
                }
            }
        }
        i++;
    }
    if (plist_matched==0)
        printf ("\nNon sono state trovate playlist associate a questo proprietario\n");
}

void createPlaylist (Playlist ** array_playlist, int *length_array_playlist, char* logged_user){

    int plist_index;
    char *plist_title;
    Playlist tmp_plist;

    do
    {
        plist_title = inputString(1, 50, "\nInserisci titolo della playlist da creare: ");
        plist_index = searchPlaylistIndex (plist_title, *array_playlist, *length_array_playlist);
        if ( plist_index != -1 )
            printf ( "\nNome playlist gia' presente!" );
    } while (plist_index != -1);

    tmp_plist.title = plist_title;
    tmp_plist.owner = logged_user;
    tmp_plist.creation_date=getCurrentDate ();
    tmp_plist.n_plist_videos = 0;
    tmp_plist.video_list=NULL;

    *length_array_playlist += 1;
    *array_playlist=realloc(*array_playlist, sizeof(Playlist)*(*length_array_playlist));
    (*array_playlist)[*length_array_playlist-1]=tmp_plist;
    printf ("Playlist creata con successo");

}

void deletePlaylist (Playlist **array_playlist, int *length_array_playlist, char *logged_user){

    int i;
    int plist_deleted;
    char *plist_title;

    plist_title = inputString ( 1, 50, "\nInserisci il titolo della playlist da cancellare: " );
    i = 0;
    plist_deleted = 0;
    while ( (i < *length_array_playlist) && (plist_deleted == 0) )
    {
        if ( strcmp(plist_title, (*array_playlist)[i].title)==0)
        {
            if ( strcmp(logged_user, (*array_playlist)[i].owner)==0)
            {
                (*array_playlist)[i] = (*array_playlist)[*length_array_playlist-1];
                *length_array_playlist -= 1;
                *array_playlist=realloc(*array_playlist, (sizeof(Playlist))*(*length_array_playlist));
                plist_deleted = 1;
            } else
                printf ( "\nOperazione non consentita" );
        }
        i++;
    }
    if ( plist_deleted != 1 )
        printf ( "\nPlaylist non presente" );
    else
        printf ( "\nPlaylist eliminata" );
}

void modifyPlaylistTitle (Playlist *array_playlist, int length_array_playlist, const char* logged_user){

    int plist_idx, i;
    char *old_plist_title, *new_plist_title;

        if (length_array_playlist == 0)
            printf("\nNessuna playlist presente, l'operazione non puo' essere effettuata!\n");
        else
        {
            old_plist_title = inputString(1, 50, "\nInserisci il titolo della playlist da modificare: ");
            plist_idx = searchPlaylistIndex(old_plist_title, array_playlist, length_array_playlist);
            if (plist_idx == -1)
                printf("\nPlaylist non trovata");
            else
            {
                if (strcmp(array_playlist[plist_idx].owner, logged_user) == 0)
                {
                    do
                    {
                        new_plist_title = inputString(1, 50, "\nInserire un nuovo titolo per la playlist\n");
                        i = searchPlaylistIndex(new_plist_title, array_playlist, length_array_playlist);
                        if (i != -1)
                        {
                            if (strcmp(new_plist_title, old_plist_title)==0)
                                i = -1;
                            else
                                printf("\nTitolo gia' presente");
                        }
                    } while (i != -1);
                    array_playlist[plist_idx].title = new_plist_title;
                } else
                    printf("\nOperazione non consentita");
            }
        }
}

void addVideoToPlaylist (Playlist *array_playlist, int length_array_playlist, Video *array_video, int length_array_video, const char *logged_user){

    int plist_idx, v_idx, video_added = 0;
    char *plist_title, *vid_title;

    plist_title = inputString (1, 50, "\nInserisci titolo della playlist:  " );
    plist_idx = searchPlaylistIndex ( plist_title, array_playlist, length_array_playlist);
    if (plist_idx == -1)
        printf ( "\nPlaylist non trovata" );
    else
    if (strcmp(array_playlist[plist_idx].owner, logged_user)!=0)
        printf ( "\nOperazione non consentita" );
    else
    {
        vid_title = inputString ( 1, 50, "\nInserisci titolo del video" );
        v_idx = searchVideoIndex ( vid_title, array_video, length_array_video );
        if ( v_idx == -1 )
            printf( "\nVideo non trovato");
        else
        {
            array_playlist[plist_idx].video_list=(char***)realloc(array_playlist[plist_idx].video_list, (sizeof(char**))*(array_playlist[plist_idx].n_plist_videos+1));
            array_playlist[plist_idx].video_list[array_playlist[plist_idx].n_plist_videos]=&array_video[v_idx].title;
            video_added = 1;
            array_playlist[plist_idx].n_plist_videos += 1;
        }
        if (video_added == 1)
            printf ("\nVideo aggiunto\n");
        else
            printf ("\nVideo non aggiunto\n");
    }
}

void removeVideoFromPlaylist (Playlist *array_playlist, int length_array_playlist, Video *array_video, int length_array_video, const char *logged_user){

    int plist_idx, v_idx, video_deleted = 0, i=0;
    char *plist_title, *vid_title;

    plist_title = inputString (1, 50, "\nInserisci titolo della playlist:  " );
    plist_idx = searchPlaylistIndex ( plist_title, array_playlist, length_array_playlist);
    if (plist_idx == -1)
        printf ( "\nPlaylist non trovata" );
    else
    if (strcmp(array_playlist[plist_idx].owner,logged_user)!=0)
        printf ( "\nOperazione non consentita" );
    else {
        vid_title = inputString(1, 50, "\nInserisci titolo del video");
        v_idx = searchVideoIndex(vid_title, array_video, length_array_video);
        if (v_idx == -1)
            printf("\nVideo non trovato");
        else
        {
            while (i < array_playlist[plist_idx].n_plist_videos && video_deleted == 0)
            {
                if (strcmp(vid_title, *(array_playlist[plist_idx].video_list[i])) == 0)
                {
                    array_playlist[plist_idx].video_list[i] = array_playlist[plist_idx].video_list[
                            array_playlist[plist_idx].n_plist_videos - 1];
                    video_deleted = 1;
                    array_playlist[plist_idx].n_plist_videos -= 1;
                }
                i++;
            }
        }
        if (video_deleted == 1)
            printf ("\nVideo eliminato");
        else
            printf ("\nVideo non presente");
    }
}

void printAllPlaylists (Playlist* array_playlist, int length_array_playlist){

    if (length_array_playlist == 0)
        printf ("\nNessuna playlist presente nell'elenco!\n");

    int i=0;
    while (i<length_array_playlist)
    {
        printf ( "\nTitolo: %s", array_playlist[i].title );
        printf ( "\nProprietario: %s", array_playlist[i].owner );
        printf ( "\nNumero video: %d", array_playlist[i].n_plist_videos );
        if (array_playlist[i].n_plist_videos != 0)
        {
            printf("\nTitoli dei  video presenti:  ");

            int j = 0;
            while (j < array_playlist[i].n_plist_videos)
            {
                printf("\n%s", *array_playlist[i].video_list[j]);
                j++;
            }
        }
        printf ( "\nData Creazione: %d/%d/%d\n", array_playlist[i].creation_date.day, array_playlist[i].creation_date.month, array_playlist[i].creation_date.year );
        i++;
    }
}

int searchPlaylistIndex (char* title, Playlist* array_playlist, int length_array_playlist){

    int i=0;
    while ( i<length_array_playlist )
    {
        if (strcmp(array_playlist[i].title, title)==0)
            return i;
        i++;
    }
    return -1;
}

void menuPlaylist(Playlist** array_playlist, int* length_array_playlist, Video** array_video, const int *length_array_video, char* logged_user){
    int key;

    do
    {
        printf ("1) Crea playlist\
				      \n2) Rinomina playlist\
				      \n3) Rimuovi playlist\
				      \n4) Aggiungi video a playist\
				      \n5) Rimuovi video da playlist\
				      \n6) Cerca playlist per titolo\
				      \n7) Cerca playlist per utente\
				      \n8) Elenca playlist\
				      \n9) Torna al menu principale\n");

        key = inputInteger(1, 9, "Scegli operazione da effettuare: ");
        if (logged_user == NULL && key < 6)
        {
            printf("Per effettuare questa operazione devi essere loggato\n");
            continue;
        }
        switch (key)
        {
            case 1:
                printf ("\tCrea playlist\n");
                createPlaylist(array_playlist, length_array_playlist, logged_user);
                break;
            case 2:
                printf ("\tRinomina playlist\n");
                modifyPlaylistTitle(*array_playlist, *length_array_playlist, logged_user);
                break;
            case 3:
                printf ("\tRimuovi playlist\n");
                deletePlaylist(array_playlist, length_array_playlist, logged_user);
                break;
            case 4:
                printf ("\tAggiungi video a playlist\n");
                addVideoToPlaylist(*array_playlist, *length_array_playlist, *array_video, *length_array_video, logged_user);
                break;
            case 5:
                printf ("\tRimuovi video da playlist\n");
                removeVideoFromPlaylist(*array_playlist, *length_array_playlist, *array_video, *length_array_video, logged_user);
                break;
            case 6:
                printf ("\tCerca playlist per titolo\n");
                searchPlaylistByTitle(*array_playlist, *length_array_playlist);
                break;
            case 7:
                printf ("\tCerca playlist per utente\n");
                searchPlaylistByOwner(*array_playlist, *length_array_playlist);
                break;
            case 8:
                printf ("\tElenca playlist\n");
                printAllPlaylists(*array_playlist, *length_array_playlist);
                break;
            case 9://esce dallo switch
                break;
            default:
                printf ("!");
                break;
        }//fine switch

    }while ( key!=9 );
}

//funzione che cerca ed elimina, in video_list di ogni playlist presente, ogni occorrenza del video che viene eliminato dall'archivio
void updateVideoLists(Playlist **array_playlist, int length_array_playlist, char *video_title){

    char ***tmp_ptr;

    int p_idx=0;
    while ( p_idx<length_array_playlist )
    {

        int v_idx=0;
        while ( v_idx<(*array_playlist)[p_idx].n_plist_videos )
        {
            if (strcmp(*((*array_playlist)[p_idx].video_list[v_idx]), video_title)==0)
            {
                (*array_playlist)[p_idx].video_list[v_idx]=(*array_playlist)[p_idx].video_list[(*array_playlist)[p_idx].n_plist_videos-1];
                (*array_playlist)[p_idx].n_plist_videos -= 1;
                tmp_ptr=(char***)realloc((*array_playlist)[p_idx].video_list, (sizeof(char**))*(*array_playlist)[p_idx].n_plist_videos);
                if (tmp_ptr == NULL)
                {
                    printf("Rimozione di %s dalla playlist %s non andata a buon fine!\n", video_title, (*array_playlist)[p_idx].title);
                } else
                    (*array_playlist)[p_idx].video_list = tmp_ptr;

            }
            v_idx++;
        }
        p_idx++;
    }
}

void playlistToCSV (FILE *fp, char *fname, Playlist* array_playlist, int length_array_playlist){

    fp=fopen(fname, "w");
    if (!fp)
    {
        printf ("Impossibile aprire il file %s (controllare se e' aperto in scrittura da altri processi)\n", fname);
        return;
    }

    int i=0;
    while ( i<length_array_playlist )
    {
        fprintf(fp, "%s;", array_playlist[i].title);
        fprintf(fp, "%s;", array_playlist[i].owner);
        fprintf(fp, "%d;", array_playlist[i].creation_date.year);
        fprintf(fp, "%d;", array_playlist[i].creation_date.month);
        fprintf(fp, "%d;", array_playlist[i].creation_date.day);
        fprintf(fp, "%d;", array_playlist[i].n_plist_videos);
        int j=0;
        while (j<array_playlist[i].n_plist_videos){
            fprintf(fp, "%s;", *(array_playlist[i].video_list[j]));
            j++;
        }
        fprintf(fp, "%c", '\n');
        i++;
    }

    printf ("Scrittura playlist su file effettuata con successo!\n");
    fclose(fp);
    if (!feof(fp))
        printf ("File chiuso con successo\n");
    else
        printf("File non chiuso\n");

}

void playlistFromCSV (FILE *fp, char *nome_file, Playlist **array_playlist, Video* array_video, int *length_array_playlist,  int length_array_video){

    fp=fopen(nome_file, "r");
    if (!fp)
    {
        printf ("Impossibile aprire il file %s (controllare se il file esiste ed e' nella stessa cartella del file exe)\n", nome_file);
        return;
    }

    char buff[1024];
    *length_array_playlist=contaRigheCSV(nome_file);
    *array_playlist=(Playlist*)malloc((*length_array_playlist)*sizeof(Playlist));

    int i=0;
    while ( !feof(fp) )
    {
        if(fgets(buff,sizeof(buff),fp)!=NULL) //non raggiunge EOF prima di leggere caratteri
        {
            if(buff[strlen(buff)-1]!='\0')//consuma il \n finale
                buff[strlen(buff)-1]='\0';
            (*array_playlist)[i]=(Playlist) {
                    .title=strdup(strtok(buff, ";")),
                    .owner=strdup(strtok(NULL, ";")),
                    .creation_date.year=atoi(strtok(NULL, ";)")),
                    .creation_date.month=atoi(strtok(NULL, ";)")),
                    .creation_date.day=atoi(strtok(NULL, ";)")),
                    .n_plist_videos=atoi(strtok(NULL, ";)")),
                    };
            (*array_playlist)[i].video_list=(char***)realloc((*array_playlist)[i].video_list,((*array_playlist)[i].n_plist_videos)*sizeof(char**));
            int j=0;
            while (j<(*array_playlist)[i].n_plist_videos){
                (*array_playlist)[i].video_list[j]=&array_video[searchVideoIndex(strtok(NULL, ";"),array_video,length_array_video)].title;
                j++;
            }
        }
        i++;
    }
    fclose(fp);
}

