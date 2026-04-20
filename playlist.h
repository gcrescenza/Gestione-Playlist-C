/**
 * @file playlist.h
 * @author GruppoF (Crescenza N., Colonna G., Cavallo R.S.)
 * @date 14/04/2021
 * @brief Header di playlist.c, raccolta delle funzioni per la gestione delle playlist.
 *
 * Raccolta delle funzioni che permettono di operare sulle strutture Playlist
 *
 */
#include "structs.h"
#include "utils.h"

#ifndef UNTITLED_PLAYLIST_H
#define UNTITLED_PLAYLIST_H
/**
 * @brief Funzione di creazione playlist
 *
 * @param[in,out] array_playlist Puntatore ad array di variabili di tipo struct Playlist
 * @param[in,out] lenght_array_playlist Puntatore alla variabile lunghezza di @p array_playlist
 * @param[in] logged_user Variabile char*, stringa con l'utente attualmente loggato
 * @return void
 */
void createPlaylist (Playlist**, int*, char*);
/**
 * @brief Funzione di modifica del titolo playilist
 *
 * @param[in] array_playlist Array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in] length_array_playlist Variabile di tipo int, lunghezza di @p array_playlist
 * @param[in] logged_user utente loggato al momento dell'esecuzione
 * @return void
 */
void modifyPlaylistTitle (Playlist *, int , const char* );
/**
 * @brief Funzione di eliminazione di una playlist
 *
 * @param[in,out] array_playlist Puntatore ad array di variabili di tipo struct Playlist
 * @param[in,out] lenght_array_playlist Puntatore a variabile di tipo int, lunghezza di @p array_playlist
 * @param[in] logged_user Utente loggato al momento dell'esecuzione
 * @return void
 * @warning
 */
void deletePlaylist (Playlist **, int* , char *);
/**
 * @brief Funzione di aggiunta video ad una playlist
 *
 * @param[in] array_playlist Array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in] array_video Array di variabili di tipo struct Video, utilizzato per memorizzare le strutture video
 * @param[in] length_array_playlist Variabile di tipo int, lunghezza di @p array_playlist
 * @param[in] length_array_video Variabile di tipo int, lunghezza di @p array_video
 * @param[in] logged_user utente loggato al momento dell'esecuzione
 *
 * @return void
 */
void addVideoToPlaylist(Playlist*, int, Video*, int, const char*);
/**
 * @brief Funzione di rimozione video da playlist
 *
 * @param[in] array_playlist Array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in] array_video Array di variabili di tipo struct Video, utilizzato per memorizzare le strutture video
 * @param[in] length_array_playlist Variabile di tipo int, lunghezza di @p array_playlist
 * @param[in] length_array_video Variabile di tipo int, lunghezza di @p array_video
 * @param[in] logged_user Utente loggato al momento dell'esecuzione
 */
void removeVideoFromPlaylist (Playlist *, int , Video *, int , const char *);
/**
 * @brief Funzione che stampa tutte le playlists
 *
 * @param[in] array_playlist Array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in] length_array_playlist Variabile di tipo int, lunghezza di @p array_playlist
 * @return void
 */
void printAllPlaylists (Playlist*, int);
/**
 * @brief Funzione di ricerca playlist per autore
 *
 * @param[in] array_playlist Array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in] length_array_playlist Variabile di tipo int, lunghezza di @p array_playlist
 * @return void
 */
void searchPlaylistByOwner (Playlist*, int);
/**
 * @brief Funzione di ricerca playlist per titolo
 *
 * @param[in] array_playlist Array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in] length_array_playlist Variabile di tipo int, lunghezza di @p array_playlist
 * @return void
 */
void searchPlaylistByTitle (Playlist *, int);
/**
 * @brief Funzione che ricerca la presenza dei una playlist
 *
 * La funzione torna la posizione in @p array_playlist del titolo della playlist, se non e' presente
 * torna -1
 *
 * @param[in] title
 * @param[in] array_playlist Array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in] length_array_playlist Variabile di tipo int, lunghezza di @p array_playlist
 * @return i   Intero, indice dell'occorrenza della playlist in @p array_playlist
 */
int  searchPlaylistIndex (char*, Playlist* , int);
/**
 * @brief Funzione che gestisce il menu playlist *
 *
 * @param[in,out] array_playlist Puntatore ad array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in,out] length_array_playlist  Puntatore a variabile di tipo int, riferimento a lunghezza di @p array_playlist
 * @param[in,out] array_video Puntatore ad array di variabili di tipo struct Video, utilizzato per memorizzare i dati dei video
 * @param[in,out] length_array_video  Puntatore a variabile di tipo int, riferimento a lunghezza di @p array_video
 * @param[in,out] logged_user Puntatore a stringa che contiene il @p nickname dell'utente loggato, NULL se non e' loggato nessun utente
 * @return (void)
 */
void menuPlaylist (Playlist **, int *, Video**, const int*, char *);
/**
 * @brief Funzione che elimina video contenuto in playlist
 *
 * Se un video viene eliminato nell'archivio, questa funzione ne cerca il titolo tra i video contenuti nelle
 * playlist e lo elimina
 *
 * @param[in,out] array_playlist Puntatore ad array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in] length_array_playlist Variabile di tipo int, lunghezza di @p array_playlist
 * @param[in] video_title
 * @return void
 */
void updateVideoLists(Playlist **,int ,char *);
/**
 * @brief Funzione che legge dalla memoria le strutture playlist e le scrive su un file
 *
 * @param[in] fp
 * @param[in] nome_file Stringa contenente il nome del file da scrivere
 * @param[in] array_playlist Array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in] length_array_playlist  Variabile di tipo int, riferimento a lunghezza di @p array_playlist
 * @return (void)
 */
void playlistToCSV (FILE *, char *, Playlist*, int);
/**
 * @brief Funzione che salva in memoria le strutture playlist contenute in un file
 *
 * @param[in] fp
 * @param[in] nome_file Stringa contenente il nome del file da leggere
 * @param[in,out] array_playlist Puntatore ad array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in,out] length_array_playlist  Puntatore a variabile di tipo int, riferimento a lunghezza di @p array_playlist
 * @return (void)
 */
void playlistFromCSV (FILE *, char *, Playlist **, Video* , int *, int);

#endif //UNTITLED_PLAYLIST_H
