/**
 * @file user.h
 * @author GruppoF (Crescenza N., Colonna G., Cavallo R.S.)
 * @date 14/04/2021
 * @brief Header di user.c, raccolta delle funzioni per la gestione dei video.
 *
 * Raccolta delle funzioni che permettono di operare sulle strutture User
 *
 */
#include "structs.h"
#include "utils.h"

#ifndef UNTITLED_USER_H
#define UNTITLED_USER_H
/**
 * @brief Funzione che permette il login dell'utente
 *
 * @param[in] array_user Array di variabili di tipo struct User, utilizzato per memorizzare i dati dell'utente
 * @param[in] length_array_user Variabile di tipo int, lunghezza di @p array_user
 * @return logged_user Stringa contenente il @p nickname dell'utente loggato, NULL se non e' loggato nessun utente
 */
char *userLogin (User *, int);
/**
 * @brief Funzione che effettua il logout dell'utente
 *
 * @param[in,out] logged_user Puntatore a stringa che contiene il @p nickname dell'utente loggato, NULL se non e' loggato nessun utente
 * @return (void)
 */
void userLogout (char**);
/**
 * @brief Funzione che ricerca presenza di un utente
 *
 * La funzione torna la posizione del nickname utente in @p array_user, se non e' presente
 * torna -1
 *
 * @param[in]nickname Variabile di tipo char*, contiene la stringa da cercare
 * @param[in,out] array_user Array di variabili di tipo struct User, utilizzato per memorizzare i dati dell'utente
 * @param[in] length_array_user
 * @return i   Intero, indice dell'occorrenza dell'utente in @p array_user
 */
int  searchUserIndex (char*, User*, int);
/**
 * @brief Funzione che crea una struttura utente
 *
 * @param[in,out] array_user Array di variabili di tipo struct User, utilizzato per memorizzare i dati dell'utente
 * @param[in,out] length_array_user Puntatore a variabile di tipo int, riferimento a lunghezza di @p array_user
 * @return (void)
 */
void createUser (User**, int*);
/**
 * @brief Funzione che gestisce il menu utente
 *
 * @param[in,out] array_user Array di variabili di tipo struct User, utilizzato per memorizzare i dati dell'utente
 * @param[in,out] length_array_user Puntatore a variabile di tipo int, riferimento a lunghezza di @p array_user
 * @return (void)
 */
void menuUser(User **, int *, char **);
/**
 * @brief Funzione che legge dalla memoria le strutture User e le scrive su un file
 *
 * @param[in] fp
 * @param[in] nome_file Stringa contenente il nome del file da scrivere
 * @param[in] array_user Array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture user
 * @param[in] length_array_user  Variabile di tipo int, riferimento a lunghezza di @p array_user
 * @return (void)
 */
void userToCSV (FILE *, char *, User*, int);
/**
 * @brief Funzione che salva in memoria le strutture user contenute in un file
 *
 * @param[in] fp
 * @param[in] nome_file Stringa contenente il nome del file da leggere
 * @param[in,out] array_user Puntatore ad array di variabili di tipo struct User, utilizzato per memorizzare le strutture user
 * @param[in,out] length_array_user  Puntatore a variabile di tipo int, riferimento a lunghezza di @p array_user
 * @return (void)
 */
void userFromCSV (FILE *, char *, User **, int *);

#endif //UNTITLED_USER_H
