# Video & Playlist Management System (C)

Progetto finale sviluppato per l'esame di **Laboratorio di Informatica** presso l'Università degli Studi di Bari. L'applicazione è un software gestionale basato su riga di comando che permette la gestione di utenti, contenuti video e playlist personalizzate.

## 💻 Caratteristiche Tecniche
Il progetto segue i principi della **programmazione modulare**, con una netta separazione tra le definizioni delle strutture dati (file `.h`) e l'implementazione della logica (file `.c`).

* **Gestione Dati:** Implementazione di strutture dati per la memorizzazione di Utenti, Video e Playlist.
* **Persistenza:** Salvataggio e caricamento dei dati su file per mantenere le informazioni tra diverse sessioni di esecuzione.
* **Logica Applicativa:**
    * `user.c`: Gestione del profilo utente e autenticazione.
    * `video.c`: Operazioni CRUD sui contenuti video.
    * `playlist.c`: Logica per la creazione e modifica di liste video personalizzate.
    * `gestore.c`: Modulo di coordinamento delle funzioni principali del sistema.
* **Build System:** Configurato tramite **CMake** per una compilazione semplificata.

## 🛠️ Requisiti e Compilazione
Per compilare il progetto è necessario un compilatore C (GCC/Clang) e CMake.

```bash
