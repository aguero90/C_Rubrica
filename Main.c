/*
 * File:   Main.c
 * Author: alex
 *
 * Created on 15 marzo 2015, 16.51
 */

#include <stdio.h>
#include <stdlib.h>
#include "Rubrica.h"

int main() {
    printf("Rubrica telefonica!\n");
    int scelta;
    FILE *fp;
    char nome[NOME], cognome[COGNOME], numero[NUMERO];
    Rubrica r = CreaRubrica();
    ItemType nuovo;
    /*Apro il file che contiene tutti i dati salvati fino ad ora*/
    fp = fopen("Contatti.txt", "r+");
    /*se c'è un errore nell'apertura del file esco*/
    if (fp == NULL) {
        printf("C'e' stato un errore nell'apertura del file.\n");
        system("PAUSE");
        exit(1);
    }
    /*Creo la lista dal file*/
    while (!feof(fp)) {
        fscanf(fp, "%s %s %s\n", &cognome, &nome, &numero);
        strcpy(nuovo.cognome, cognome);
        strcpy(nuovo.nome, nome);
        strcpy(nuovo.numero, numero);
        r = InserisciContatto(r, nuovo);
    }
    /*Chiudo il file perché non so come fare per sovrascrivere tutti i dati salvati nel .txt xD*/
    fclose(fp);
    /*Stampo la lista dei contatti presenti sul file*/
    printf("Ecco la lista dei tuoi contatti in rubrica:\n\n");
    VisualizzaRubrica(r);
    /*Menù della rubrica*/
    do {
        printf("\nCosa desideri fare ora?\n"
                "\t1. Inserire un nuovo contatto.\n"
                "\t2. Cercare un contatto per cognome.\n"
                "\t3. Cercare un contatto per nome.\n"
                "\t4. Cercare un contatto per numero.\n"
                "\t5. Cancellare un contatto.\n"
                "\t6. Visualizzare la rubrica.\n"
                "\t7. Cancellare tutta la rubrica.\n"
                "\t8. Modifica un contatto.\n"
                "\tQualsiasi altro numero per uscire.\n");
        scanf("%d", &scelta);
        //while (getchar() != '\n'); //Pulizia del Buffer CONTROLLARE PERCHE' NON VA SEMPRE BENE
        /*Provo questa define messa in ItemType.h: #define PULIZIA_BUFFER while(getchar() != '\n');*/
        PULIZIA_BUFFER /*NB: sembra funzionare anche questo!!!*/
        switch (scelta) {
            case 1: r = InserisciContatto(r, CreaContatto());
                printf("Contatto inserito!\n");
                break;

            case 2: printf("Inserire il Cognome del contatto da cercare: ");
                scanf("%s", &cognome);
                RicercaCognome(r, cognome);
                break;

            case 3: printf("Inserire il Nome del contatto da cercare: ");
                scanf("%s", &nome);
                RicercaNome(r, nome);
                break;

            case 4: printf("Inserire il Numero del contatto da cercare ( senza spazi! ): ");
                scanf("%s", &numero);
                RicercaNumero(r, numero);
                break;

            case 5: r = CancellaContatto(r, CreaContatto());
                printf("Contatto cancellato!\n"); //viene stampato anche se viene immesso un contatto sbagliato!
                break;

            case 6: printf("Ecco la lista dei tuoi contatti:\n");
                VisualizzaRubrica(r);
                break;

            case 7: r = CancellaRubrica(r);
                printf("La rubrica e' stata cancellata!\n");
                break;

            case 8: ModificaContatto(r);
                break;

            default: scelta = 0;
                /*riapro il file in modalità w+ (scrittura e lettura con file ripulito) per poter sovrascrivere tutto*/
                fp = fopen("Contatti.txt", "w+");
                while (r != NULL) {
                    fprintf(fp, "%s %s %s\n", r->item.cognome, r->item.nome, r->item.numero);
                    r = r->next;
                }
                break;
        }
    } while (scelta);
    system("PAUSE");
    return 0;
}


