
/**
 * Semplice gestore degli alunni di una classe
 *
 * Funzionalità:
 *      - Creare una nuova classe
 *      - Modificare una classe già esistente
 *      - Aggiungere un alunno
 *      - Visualizzare gli alunni di una classe
 *      - Prendere i dati da file in formato csv
 *      - Caricare i dati su file in formato csv
 *
 *
 * Struttura del file:
 *      - Il titolo indica la classe (es. 4aii, 5aii...)
 *      - Gli alunni sono indicati secondo il seguente schema: nome;cognome;altezza
 *
 *
 * SE SI VUOLE AGGIUNGERE UN FILE MANUALMENTE DEV'ESSERE INSERITO NELLA CARTELLA DELL'ESEGUIBILE
 *
 * Autore: Greta Maria Brugnatti
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[100];
    char cognome [200];
    int altezza; //in centimetri
} Alunno;

void scriviSuFile(FILE * fp, Alunno a); //FUNZIONA
void inizializzaAlunno(char nome[], char cognome[], int altezza, Alunno * pAlunno); //FUNZIONA
void eliminaACapo(char stringa[]); //FUNZIONA
void caricaDaFile(Alunno * a, char line[]);



int main (){
    //Dichiarazione delle variabili
    FILE *fp;
    Alunno classe[40];
    int cont=0;
    int i=0;
    int scelta;
    char nome[100];
    char cognome[200];
    int altezza;
    char line[200];
    char nomeFile[20];


        printf("+----------------------------+\n");
        printf("|       GESTORE CLASSI       |\n");
        printf("+----------------------------+\n");
        printf("Digitare il nome del file e la sua estensione: ");
        fgets(nomeFile, sizeof(nomeFile), stdin);
        eliminaACapo(nomeFile);

        do{
            printf("+----------------------------+\n");
            printf("|       GESTORE ALUNNI       |\n");
            printf("+----------------------------+\n");
            printf("1 - Aggiungi alunni \n");
            printf("2 - Visualizza alunni\n");
            printf("0 - Salva ed esci\n");
            scanf("%d", &scelta);
            fflush(stdin);
            switch(scelta){
                case 1: // Aggiungi utente
                    //Dati alunno
                    printf("Inserisci il nome: ");
                    fgets(nome, sizeof(nome), stdin);
                    eliminaACapo(nome);
                    fflush(stdin);

                    printf("Inserisci il cognome: ");
                    fgets(cognome, sizeof(cognome), stdin);
                    eliminaACapo(cognome);
                    fflush(stdin);

                    printf("Inserisci l'altezza (cm): ");
                    scanf("%d", &altezza);
                    fflush(stdin);

                    inizializzaAlunno(nome, cognome, altezza, &classe[cont]);
                    fp=fopen(nomeFile, "ab"); //Apertura del file, con ab il contenuto verrà scritto dopo l'ultima riga
                                                            // senza dover sovrascrivere il file
                    scriviSuFile(fp, classe[cont]);

                    fclose(fp); //Chiusura del file
                    cont++;
                    break;

                case 2:
                    fp = fopen(nomeFile, "r");

                    if (fp == NULL) {
                        printf("Errore nell'apertura del file \n");
                        break;
                    }
                    while(fgets(line, sizeof(line), fp) != NULL) {

                        caricaDaFile(&classe[cont], line);
                        cont++;

                    }

                        fclose(fp);
                    break;
            }
        }while (scelta!=0);

    if(fp==NULL){
        printf("Errore nell'apertura del file \n");
    }

    printf("Alunni totali: %d", cont);

}

void scriviSuFile(FILE * fp, Alunno a){ //FUNZIONA
    fprintf(fp, "%s;%s;%d\n", a.nome, a.cognome, a.altezza);
}

void inizializzaAlunno(char nome[], char cognome[], int altezza, Alunno * pAlunno){ //FUNZIONA
    strcpy((*pAlunno).nome, nome);
    strcpy((*pAlunno).cognome, cognome);
    (*pAlunno).altezza = altezza;
}

void eliminaACapo(char stringa[]){
    stringa[(strlen(stringa))-1]='\0';
}

void caricaDaFile(Alunno * a, char line[]){
    char * token;
    char nome[100];
    char cognome[200];
    char h[10];
    int altezza;
    token = strtok(line, ";");
    strcpy(nome, token);
    printf("Nome: %s\n", token);
    token = strtok( NULL, ";" );
    strcpy(cognome, token);
    printf("Cognome: %s\n", token);

    token = strtok( NULL, ";" );
    strcpy(h, token);

    altezza=(int) atoll(h);
    printf("Altezza [cm]: %s\n", token);

    inizializzaAlunno(nome, cognome, altezza, a);
}