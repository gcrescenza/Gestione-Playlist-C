/**
 * @file utils.h
 * @author GruppoF (Crescenza N., Colonna G., Cavallo R.S.)
 * @date 14/04/2021
 * @brief Header di utils.c, raccolta delle funzioni ausiliarie
 *
 * Raccolta delle funzioni ausiliari di gestione delle date ed acquisiszione e conversione degli input
 *
 */
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef UNTITLED_UTILS_H
#define UNTITLED_UTILS_H
/**
 * @brief Funzione di inizializzazione arrays
 *
 * La funzione ha lo scopo di inizializzare gli arrays delle strutture dati con
 * dei valori fittizzi ma che soddisfano i requisiti voluti nel programma.
 *
 * @param[in,out] array_playlist Puntatore ad array di variabili di tipo struct Playlist, utilizzato per memorizzare le strutture playlist
 * @param[in,out] array_video Puntatore ad array di variabili di tipo struct Video, utilizzato per memorizzare le strutture video
 * @param[in,out] array_user Puntatore ad array di variabili di tipo struct User, utilizzato per memorizzare i dati dell'utente
 * @param[in] length_array_playlist Variabile di tipo int, lunghezza di @p array_playlist
 * @param[in] length_array_video Variabile di tipo int, lunghezza di @p array_video
 * @param[in] length_array_user Variabile di tipo int, lunghezza di @p array_user
 * @param[in, out] logged_user Puntatore a stringa che contiene il @p nickname dell'utente loggato, NULL se non è loggato nessun utente
 * @return void
 */
void initArrays (Playlist ** , Video **, User **, int *, int*, int*, char **);
/**
 * @brief Funzione di acquisizione stringa con inserimento da tastiera
 *
 * La funzione utilizza la funzione strcspn(const char*, const char*)
 * inclusa in 'string.h' che scambia il carattere fine riga con quello di fine stringa
 * @code
 * s[strcspn(s, "\n")]=0;
 * @endcode
 *
 * @param[in] min Variabile di tipo int, valore minimo di caratteri contenuti nella stringa inserita
 * @param[in] max Variabile di tipo int, valore massimo di caratteri contenuti nella stringa inserita
 * @param[in] string_output Variabile stringa, messaggio per l'utente
 * @return s Variabile di tipo char*, la stringa inserita dall'utente
 */
char* inputString (int , int, char*);
/**
 * @brief Funzione che converte una stringa in un intero
 *
 * La funzione controlla se una stinga abbia al suo interno un valore intero valido.
 * Come valore intero valido si intende un numero intero preceduto e seguito da un numero arbitrario di spazi.
 *
 * @param[in] s Variabile di tipo char*, stringa che si vuol verificare
 * @return n Variabile di tipo int, numero presente nella stringa @p s
 * @warning Il valore 0 è accettato solo se s=={'0','\0'}
 */
int isNaturalNumber (char *s);
/**
 * @brief Funzione di acquisizione carattere con inserimento da tastiera
 *
 * La funzione ha lo scopo di acquisire un carattere inserito interattivamente dall'utente
 *
 * @param[in] char_1 Variabile di tipo char
 * @param[in] char_2 Variabile di tipo char
 * @param[in] string_output Variabile stringa, messaggio per l'utente
 * @return c Variabile char che conterrà la scelta dell'utente
 */
char inputChar (char, char, char*);
/**
 * @brief Funzione che acquisisce la data dal sistema
 *
 * @param void
 * @return date	Puntatore ad una struct Date
 */
Date getCurrentDate ();
/**
 * @brief Funzione di acquisizione data con inserimento da tastiera
 *
 * @param data_max[in] La data di tipo struct Data che viene usata per controllare il requisito di età minima dell'utente
 * @return date Puntatore ad una structtura Date

 */
Date inputDate (Date data_max);
/**
 * @brief Funzione di acquisizione intero con inserimento da tastiera
 *
 * @param[in] min Variabile di tipo int, valore minimo che l'intero potrà avere
 * @param[in] max Variabile di tipo int, valore massimo che l'intero potrà avere
 * @param[in] string_output Variabile stringa, messaggio per l'utente
 * @return n Variabile di tipo int, l'intero inserito dall'utente
 */
int inputInteger (int, int, char*);
/**
 * @brief Funzione di controllo requisito età minima
 *
 * @param[in] date_1 Variabile di tipo struct Date, data massima per il controllo requisito di età
 * @param[in] date_2 Variabile di tipo struct Date, data inserita dell'untente in #inputDate
 * @return age_allowed Variabile di tipo int che vale 1 se @p data_2 <=@p data_1, 0 altrimenti
 */
int checkDate (Date date_1, Date date_2);
/**
 * @brief Funzione di controllo correttezza di una data
 *
 * @param[in] data Variabile di tipo struct Date, data della quale vogliamo controllarne la correttezza
 * @return @b int @b 1 o @b int @b 0 in base alla correttezza della data passata alla funzione
 */
int dateCorrect(Date data);
/**
 * @brief Funzione di controllo anno bisestile
 *
 * @param anno Variabile di tipo int, anno del quale si vuole verificare se bisestile
 * @return @b int @b 1 o @b int @b 0, rispettivamente se anno è bisestile o no
 */
int isBisestile (int anno);

#endif //UNTITLED_UTILS_H
