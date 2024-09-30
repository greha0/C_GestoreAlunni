
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



        printf("GESTORE ALUNNI\n");
        printf("Digitare il nome completo del file: ");
        fgets(nomeFile, sizeof(nomeFile), stdin);
        eliminaACapo(nomeFile);

        do{
            printf("GESTORE ALUNNI\n");
            printf("1 - Aggiungi alunni \n");
            printf("2 - Visualizza alunni\n");
            printf("0 - Salva ed esci\n");
            scanf("%d", &scelta);
            fflush(stdin);
            switch(scelta){
                case 1: // Aggiungi utente
                    //Dati alunno
                    printf("Nome: ");
                    fgets(nome, sizeof(nome), stdin);
                    eliminaACapo(nome);
                    fflush(stdin);

                    printf("Cognome: ");
                    fgets(cognome, sizeof(cognome), stdin);
                    eliminaACapo(cognome);
                    fflush(stdin);

                    printf("Altezza in cm: ");
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

    printf("%d", cont);

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
    printf("%s\n", token);
    token = strtok( NULL, ";" );
    strcpy(cognome, token);
    printf("%s\n", token);

    token = strtok( NULL, ";" );
    strcpy(h, token);

    altezza=(int) atoll(h);
    printf("%s\n", token);

    inizializzaAlunno(nome, cognome, altezza, a);
}