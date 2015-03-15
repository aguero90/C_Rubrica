/*
 * File:   Rubrica.h
 * Author: alex
 *
 * Created on 15 marzo 2015, 16.54
 */

#ifndef Rubrica1
#define Rubrica1
#include "ItemType.h"
#include <string.h>
typedef struct nodo *Rubrica;

typedef struct nodo {
    ItemType item;
    Rubrica next;
} nodo;

/*Inizializza la rubrica: Ritorna un puntatore nullo*/
Rubrica CreaRubrica();

/*Chiede tutti i dati di un contatto e lo inserisce in un ItemType temporaneo che poi restituirà*/
ItemType CreaContatto();

/*Inserisce un contatto al posto giusto nella lista (INSERIMENTO ORDINATO)*/
Rubrica InserisciContatto(Rubrica, ItemType);

/*Modifica un contatto esistente*/
void ModificaContatto(Rubrica);

/*Cerca un contatto per cognome*/
Rubrica RicercaCognome(Rubrica, const char *);

/*Cerca un contatto per nome*/
Rubrica RicercaNome(Rubrica, const char *);

/*Cerca un contatto per numero*/
Rubrica RicercaNumero(Rubrica, const char *);

/*Cancella un contatto dalla rubrica*/
Rubrica CancellaContatto(Rubrica, ItemType);

/*Stampa la rubrica*/
void VisualizzaRubrica(Rubrica);

/*Cancella la rubrica: cancella tutto e restituisce un puntatore NULL*/
Rubrica CancellaRubrica(Rubrica);

#endif


