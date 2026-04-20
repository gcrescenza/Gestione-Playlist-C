/**
 * @file structs.h
 * @author GruppoF (Crescenza N., Colonna G., Cavallo R.S.)
 * @date 14/04/2021
 * @brief Definizione di tutte le strutture dati
 *
 */
#ifndef UNTITLED_STRUCTS_H
#define UNTITLED_STRUCTS_H
/**
 * @brief Struttura che contiene le date
 */
typedef struct
{
    int year;   ///< Anno min 1910 max 3000
    int month;
    int day;
} Date;
/**
 * @brief Struttura che contiene i dati dell'utente
 */
typedef struct
{
    char *nickname; ///< Nickname dell'utente. Lunghezza compresa tra @b 8 e @b 300 caratteri con requisito di unicita'
    char *name;     ///< Nome utente, stringa compresa tra@b 1 e@b 50
    char *surname;  ///< Cognome utente, stringa compresa tra@b 1 e@b 50
    char  gender;   ///< Sesso dell'utente, carattere@b 'M'/'m' o@b 'F'/'f'
    Date  birth_date;///< Data di nascita utente
    char *password; ///< Stringa, min @b 8 max @b 16 caratteri
} User;
/**
 * @brief Struttura che contiene gli attributi video
 */
typedef struct {
    char *title;    ///< Stringa, min @b 1 max@b 50 caratteri. Requisito di univocita'
    char *author;   ///< Stringa, min@b 1 max@b 50
    char *description;///< Stringa, min@b 1 max@b 150 caratteri
    int  length;    ///< Durata del video, min@b 1
    char *owner;    ///< Titolo della playlist
}  Video;
/**
 * @brief Struttura che contiene gli attributi playlist
 */
typedef struct
{
    char   *title;          ///< Stringa, min@b 1 max@b 50. Requisito di univocita'
    char   *owner;          ///< Utente che ha creato la playlist, min 1 max 50 caratteri
    Date   creation_date;   ///< Data corrente al momento della creazione
    int    n_plist_videos;  ///< Numero dei video contenuti in @b video_list
    char   ***video_list;   ///< Video caricati nella palylist

} Playlist;

#endif //UNTITLED_STRUCTS_H
