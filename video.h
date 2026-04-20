
#include "structs.h"
#include "utils.h"

#ifndef UNTITLED_VIDEO_H
#define UNTITLED_VIDEO_H
/**
 * @brief Funzione che crea una struttura Video
 *
 * @param[in,out] array_video Array di variabili di tipo struct Video, utilizzato per memorizzare le strutture video
 * @param[in,out] length_array_video Variabile di tipo int, lunghezza di @p array_playlist
 * @return void
 */
void addVideo (Video **, int*,const char*);
/**
 * @brief Funzione che modifica un campo di un Video
 *
 * @param[in,out] array_video Array di variabili di tipo struct Video, utilizzato per memorizzare le strutture video
 * @param[in,out] length_array_video Variabile di tipo int, lunghezza di @p array_playlist
 * @return void
 */
void modifyVideo (Video *, int);
/**
 * @brief Funzione che crea elimina un video
 *
 * Se il video e' presente in una o piu' playlist viene eliminato da a\ list_video
 *
 * @param[in,out] array_video Array di variabili di tipo struct Video, utilizzato per memorizzare le strutture video
 * @param[in,out] length_array_video Variabile di tipo int, lunghezza di @p array_playlist
 * @param[in,out] array_playlist Array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in] length_array_playlist Variabile di tipo int, lunghezza di @p array_playlist
 * @return void
 */
void removeVideo (Video**, int*, Playlist **, const int);
/**
 * @brief Funzione che cerca un Video per autore
 *
 * @param[in] array_video Array di variabili di tipo struct Video, utilizzato per memorizzare le strutture video
 * @param[in] length_array_video Variabile di tipo int, lunghezza di @p array_playlist
 * @return void
 */
void searchVideoByAuthor (Video*, int );
/**
 * @brief Funzione che cerca un Video per il titolo
 *
 * @param[in] array_video Array di variabili di tipo struct Video, utilizzato per memorizzare le strutture video
 * @param[in] length_array_video Variabile di tipo int, lunghezza di @p array_playlist
 * @return void
 */
void searchVideoByTitle (Video*, int );
/**
 * @brief Funzione che stampa tutti i video contenuti  in \a array_video
 *
 * @param[in] array_video Array di variabili di tipo struct Video, utilizzato per memorizzare le strutture video
 * @param[in] length_array_video Variabile di tipo int, lunghezza di @p array_playlist
 * @return void
 */
void printAllVideos (Video*, int);
/**
 * @brief Funzione che cerca l'indice di un video in \a array_user
 *
 * @param[in] array_video Array di variabili di tipo struct Video, utilizzato per memorizzare le strutture video
 * @param[in] length_array_video Variabile di tipo int, lunghezza di @p array_playlist
 * @return i Intero, indice dell'occorrenza di \a title in \a array_video, -1 se non presente
 */
int  searchVideoIndex (char*, Video*, int);
/**
 * @brief Funzione che gestisce interazione con l'utente
 *
 * Se il video e' presente in una o piu' playlist viene eliminato da a\ list_video
 *
 * @param[in,out] array_video Array di variabili di tipo struct Video, utilizzato per memorizzare le strutture video
 * @param[in,out] length_array_video Variabile di tipo int, lunghezza di @p array_playlist
 * @param[in,out] array_playlist Array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in] length_array_playlist Variabile di tipo int, lunghezza di @p array_playlist
 * @param[in] logged_user Stringa con il \a nickname dell'utente loggato, NULL se non e' loggato nessun utente
 * @return void
 */
void menuVideo(Video **, int *, Playlist **, const int, const char *);
/**
 * @brief Funzione che legge dalla memoria le strutture video e le scrive su un file
 *
 * @param[in] fp
 * @param[in] nome_file Stringa contenente il nome del file da scrivere
 * @param[in] array_video Array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in] length_array_video  Variabile di tipo int, riferimento a lunghezza di @p array_video
 * @return (void)
 */
void videoToCSV (FILE *, char *, Video* , int);
/**
 * @brief Funzione che salva in memoria le strutture video contenute in un file
 *
 * @param[in] fp
 * @param[in] nome_file Stringa contenente il nome del file da leggere
 * @param[in,out] array_video Puntatore ad array di variabili di tipo struct Video, utilizzato per memorizzare le strutture video
 * @param[in,out] length_array_video  Puntatore a variabile di tipo int, riferimento a lunghezza di @p array_video
 * @return (void)
 */
void videoFromCSV (FILE *, char *, Video **, int *);


#endif //UNTITLED_VIDEO_H
