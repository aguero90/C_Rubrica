
#include "Rubrica.h"

/*Prototipi funzioni ausiliarie*/
Rubrica CreaNodo(ItemType);
int Confronto(ItemType, ItemType);

/*Inizializza la rubrica: Ritorna un puntatore nullo*/
Rubrica CreaRubrica() {
    return NULL;
}

/*Chiede tutti i dati di un contatto e lo inserisce in un ItemType temporaneo che poi restituirà*/
ItemType CreaContatto() {
    /*NB: ho testato e sembra funzionare!!!*/
    ItemType nuovo;
    //char nome[NOME], cognome[COGNOME], numero[NUMERO];
    printf("Inserire il Cognome: ");
    scanf("%s", &(nuovo.cognome));
    //scanf("%s", &cognome);
    printf("Inserire il Nome: ");
    scanf("%s", &(nuovo.nome));
    //scanf("%s", &nome);
    printf("Inserire il Numero ( senza spazi! ): ");
    scanf("%s", &(nuovo.numero));
    //scanf("%s", &numero);
    //strcpy(nuovo.cognome, cognome);
    //strcpy(nuovo.nome, nome);
    //strcpy(nuovo.numero, numero);
    return nuovo;
}

/*Inserisce un contatto al posto giusto nella lista (INSERIMENTO ORDINATO)*/
Rubrica InserisciContatto(Rubrica r, ItemType c) {
    Rubrica prec, nuovo = CreaNodo(c);
    if (r == NULL) return nuovo;
    /*controllo il primo elemento*/
    if (Confronto(c, r->item) <= 0) {
        nuovo->next = r;
        r = nuovo;
        return r;
    }
    /*Altrimenti andiamo avanti*/
    prec = r;
    while (prec->next != NULL) {
        if (Confronto(c, prec->next->item) <= 0) {
            nuovo->next = prec->next;
            prec->next = nuovo;
            return r;
        }
        prec = prec->next;
    }
    /*Inserisco all'ultimo elemento*/
    prec->next = nuovo;
    return r;
}

/*Cerca un contatto per cognome*/
Rubrica RicercaCognome(Rubrica r, const char *cognome) {
    while (r != NULL) {
        if (strcmp(r->item.cognome, cognome) == 0) {
            printf("Ecco il contatto cercato: %s %s %s\n", r->item.cognome, r->item.nome, r->item.numero);
            return r;
        }
        r = r->next;
    }
    printf("Il contatto cercato non e' presente in rubrica.\n");
    return NULL;
}

/*Cerca un contatto per nome*/
Rubrica RicercaNome(Rubrica r, const char * nome) {
    while (r != NULL) {
        if (strcmp(r->item.nome, nome) == 0) {
            printf("Ecco il contatto cercato: %s %s %s\n", r->item.cognome, r->item.nome, r->item.numero);
            return r;
        }
        r = r->next;
    }
    printf("Il contatto cercato non e' presente in rubrica.\n");
    return NULL;
}

/*Cerca un contatto per numero*/
Rubrica RicercaNumero(Rubrica r, const char * numero) {
    while (r != NULL) {
        if (strcmp(r->item.numero, numero) == 0) {
            printf("Ecco il contatto cercato: %s %s %s\n", r->item.cognome, r->item.nome, r->item.numero);
            return r;
        }
        r = r->next;
    }
    printf("Il contatto cercato non e' presente in rubrica.\n");
    return NULL;
}

/*Cancella un contatto dalla rubrica*/
Rubrica CancellaContatto(Rubrica r, ItemType c) {
    nodo aus;
    Rubrica temp;
    aus.next = r;
    r = &aus;
    while (r->next != NULL) {
        if (!Confronto(c, r->next->item)) {
            temp = r->next;
            r->next = temp->next;
            free(temp);
        }
        r = r->next;
        /*se l'elemento da cencellare è l'ultimo elemento, non procedo al successivo*/
        if (r == NULL) break;
    }
    return aus.next;
}

/*Stampa la rubrica*/
void VisualizzaRubrica(Rubrica r) {
    if (r == NULL) printf("La rubrica e' vuota.\n");
    while (r != NULL) {
        printf("\t%s %s %s\n", r->item.cognome, r->item.nome, r->item.numero);
        r = r->next;
    }
}

/*Cancella la rubrica: cancella tutto e restituisce un puntatore NULL*/
Rubrica CancellaRubrica(Rubrica r) {
    Rubrica temp;
    while (r != NULL) {
        temp = r;
        r = r->next;
        free(temp);
    }
    return r;
}

/*Modifica un contatto in rubrica*/
void ModificaContatto(Rubrica r) {
    int scelta;
    char nome[NOME], cognome[COGNOME], numero[NUMERO], ch;
    Rubrica controllo;
    ItemType nuovo;
    printf("Come vuoi cercare il contatto?\n"
            "\t1. Cognome\n"
            "\t2. Nome\n"
            "\t3. Numero\n");
    scanf("%c", &ch);
    if (ch > '3' || ch < '1') {
        printf("Errore: non hai scelto una delle tre opzioni.\n");
        return;
    }
    scelta = (int) (ch - '0'); // potrebbe creare problemi: CONTROLLARE
    switch (scelta) {
        case 1: printf("Inserire il Cognome da cercare: ");
            scanf("%s", &cognome);
            controllo = RicercaCognome(r, cognome);
            if (controllo == NULL) {
                printf("Non posso modificare un contatto che non esiste!\n");
                printf("Vuoi crearlo ora?\n"
                        "\tSi' (digitare il tasto 's' o 'S')\n"
                        "\tNo (digitare il tasto 'n' o 'N')\n");
                //while (getchar() != '\n'); //Pulizia del Buffer CONTROLLARE PERCHE' NON VA SEMPRE BENE
                PULIZIA_BUFFER
                scanf("%c", &ch);
                if (ch != 's' && ch != 'S' && ch != 'n' && ch != 'N') {
                    printf("Errore: hai inserito una lettera o un valore non validi!\n");
                    return;
                }
                if (ch == 's' || ch == 'S') {
                    r = InserisciContatto(r, CreaContatto());
                    printf("Contatto inserito!\n");
                }
                return;
            }
            break;

        case 2: printf("Inserire il Nome da cercare: ");
            scanf("%s", &nome);
            controllo = RicercaNome(r, nome);
            if (controllo == NULL) {
                printf("Non posso modificare un contatto che non esiste!\n");
                printf("Vuoi crearlo ora?\n"
                        "\tSi' (digitare il tasto 's' o 'S')\n"
                        "\tNo (digitare il tasto 'n' o 'N')\n");
                //while (getchar() != '\n'); //Pulizia del Buffer CONTROLLARE PERCHE' NON VA SEMPRE BENE
                PULIZIA_BUFFER
                scanf("%c", &ch);
                if (ch != 's' && ch != 'S' && ch != 'n' && ch != 'N') {
                    printf("Errore: hai inserito una lettera o un valore non validi!\n");
                    return;
                }
                if (ch == 's' || ch == 'S') {
                    r = InserisciContatto(r, CreaContatto());
                    printf("Contatto inserito!\n");
                }
                return;
            }
            break;

        case 3: printf("Inserire il Numero da cercare ( senza spazi! ): ");
            scanf("%s", &numero);
            controllo = RicercaNumero(r, numero);
            if (controllo == NULL) {
                printf("Non posso modificare un contatto che non esiste!\n");
                printf("Vuoi crearlo ora?\n"
                        "\tSi' (digitare il tasto 's' o 'S')\n"
                        "\tNo (digitare il tasto 'n' o 'N')\n");
                //while (getchar() != '\n'); //Pulizia del Buffer CONTROLLARE PERCHE' NON VA SEMPRE BENE
                PULIZIA_BUFFER
                scanf("%c", &ch);
                if (ch != 's' && ch != 'S' && ch != 'n' && ch != 'N') {
                    printf("Errore: hai inserito una lettera o un valore non validi!\n");
                    return;
                }
                if (ch == 's' || ch == 'S') {
                    r = InserisciContatto(r, CreaContatto());
                    printf("Contatto inserito!\n");
                }
                return;
            }
            break;
    }
    /*Parte per il cognome*/
    printf("Vuoi modificare il cognome?\n"
            "\tSi' (digitare il tasto 's' o 'S')\n"
            "\tNo (digitare il tasto 'n' o 'N')\n");
    //while (getchar() != '\n'); //Pulizia del Buffer CONTROLLARE PERCHE' NON VA SEMPRE BENE
    PULIZIA_BUFFER
    scanf("%c", &ch);
    if (ch != 's' && ch != 'S' && ch != 'n' && ch != 'N') {
        printf("Errore: hai inserito una lettera o un valore non validi!\n");
        return;
    }
    if (ch == 's' || ch == 'S') {
        printf("Inserire il nuovo Cognome da assegnare al contatto: ");
        scanf("%s", &cognome);
        strcpy(controllo->item.cognome, cognome);
        printf("Cognome Modificato!\n");
    }
    /*Parte per il Nome*/
    printf("Vuoi modificare il Nome?\n"
            "\tSi' (digitare il tasto 's' o 'S')\n"
            "\tNo (digitare il tasto 'n' o 'N')\n");
    //while (getchar() != '\n'); //Pulizia del Buffer CONTROLLARE PERCHE' NON VA SEMPRE BENE
    PULIZIA_BUFFER
    scanf("%c", &ch);
    if (ch != 's' && ch != 'S' && ch != 'n' && ch != 'N') {
        printf("Errore: hai inserito una lettera o un valore non validi!\n");
        return;
    }
    if (ch == 's' || ch == 'S') {
        printf("Inserire il nuovo Nome da assegnare al contatto: ");
        scanf("%s", &nome);
        strcpy(controllo->item.nome, nome);
        printf("Nome Modificato!\n");
    }
    /*Parte per il Numero*/
    printf("Vuoi modificare il Numero?\n"
            "\tSi' (digitare il tasto 's' o 'S')\n"
            "\tNo (digitare il tasto 'n' o 'N')\n");
    //while (getchar() != '\n'); //Pulizia del Buffer CONTROLLARE PERCHE' NON VA SEMPRE BENE
    PULIZIA_BUFFER
    scanf("%c", &ch);
    if (ch != 's' && ch != 'S' && ch != 'n' && ch != 'N') {
        printf("Errore: hai inserito una lettera o un valore non validi!\n");
        return;
    }
    if (ch == 's' || ch == 'S') {
        printf("Inserire il nuovo Numero da assegnare al contatto: ");
        scanf("%s", &numero);
        strcpy(controllo->item.numero, numero);
        printf("Numero Modificato!\n");
    }
    return;
}



/******************************************************************************
                          FUNZIONI AUSILIARIE
 *******************************************************************************/

/*Alloca spazio per un nuovo nodo e restituisce un puntatore ad esso*/
Rubrica CreaNodo(ItemType c) {
    Rubrica nuovo = (Rubrica) malloc(sizeof (*nuovo));
    strcpy(nuovo->item.cognome, c.cognome);
    strcpy(nuovo->item.nome, c.nome);
    strcpy(nuovo->item.numero, c.numero);
    nuovo->next = NULL;
    return nuovo;
}

/*Confronta campo per campo*/
int Confronto(ItemType a, ItemType b) {
    if (strcmp(a.cognome, b.cognome) == -1) return -1;
    if (strcmp(a.cognome, b.cognome) == 1) return 1;
    if (strcmp(a.cognome, b.cognome) == 0) {
        if (strcmp(a.nome, b.nome) == -1) return -1;
        if (strcmp(a.nome, b.nome) == 1) return 1;
        if (strcmp(a.nome, b.nome) == 0) return strcmp(a.numero, b.numero);
    }
}



