/*
 * File:   ItemType.h
 * Author: alex
 *
 * Created on 15 marzo 2015, 16.55
 */

#ifndef ItemType1
#define ItemType1
#define NOME 15
#define COGNOME 20
#define NUMERO 15
#define PULIZIA_BUFFER while(getchar() != '\n');

typedef struct contatto {
    char nome[NOME];
    char cognome[COGNOME];
    char numero[NUMERO];
} ItemType;
#endif

