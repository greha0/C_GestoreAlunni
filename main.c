
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[100];
    char cognome [200];
    int altezza; //in centimetri
} Alunno;

//AD OGNI SINGOLA OPERAZIONE, SALVARE
void scriviSuFile(FILE * fp, Alunno a); //FUNZIONA
void inizializzaAlunno(char nome[], char cognome[], int altezza, Alunno * pAlunno); //FUNZIONA
void eliminaACapo(char stringa[]); //FUNZIONA
void caricaDaFile(Alunno * a, char line[]);
void stampaAlunno(Alunno classe[], int cont);



//AD OGNI SINGOLA OPERAZIONE, SALVARE


int main (){
    //Dichiarazione delle variabili

    FILE *fp; //Puntatore al file
    Alunno classe[40]; //Array di struct Alunno
    int idAlunno=0;
    int cont=0; //contatore di alunni
    int scelta;
    char nome[100];
    char cognome[200];
    int altezza;
    char line[200]; //buffer per lettura file
    char nomeFile[20];


// Menù
        printf("+----------------+\n");
        printf("| GESTORE ALUNNI |\n");
        printf("+----------------+\n");
        printf("Digitare il nome completo del file: ");
        fgets(nomeFile, sizeof(nomeFile), stdin);
        eliminaACapo(nomeFile);

        do{
            printf("+-----------------------+\n");
            printf("| GESTORE ALUNNI        |\n");
            printf("+-----------------------+\n");
            printf("| 1 - Aggiungi alunni   |\n");
            printf("| 2 - Visualizza alunni |\n");
            printf("| 3 - Modifica altezza  |\n");
            printf("| 4 - Elimina alunno    |\n");
            printf("| 0 - Salva ed esci     |\n");
            printf("+-----------------------+\n\n");
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

                    if (fp == NULL) {
                        printf("Errore nell'apertura del file \n");
                        break;
                    }

                    scriviSuFile(fp, classe[cont]);

                    fclose(fp); //Chiusura del file
                    cont++;
                    break;

                case 2:
                    cont = 0;
                    fp = fopen(nomeFile, "r");

                    if (fp == NULL) {
                        printf("Errore nell'apertura del file \n");
                        break;
                    }

                    while(fgets(line, sizeof(line), fp) != NULL) {
                        caricaDaFile(&classe[cont], line);
                        stampaAlunno(classe, cont);
                        cont++;
                    }

                        fclose(fp);
                    break;

                case 3: //Modifica altezza alunno
                cont = 0;
                    printf("Quale alunno vuoi modificare (0 - ...): \n");
                    fp=fopen(nomeFile, "r");

                    if (fp == NULL) {
                        printf("Errore nell'apertura del file \n");
                        break;
                    }

                    while(fgets(line, sizeof(line), fp) != NULL) {
                        caricaDaFile(&classe[cont], line);
                        stampaAlunno(classe,cont);
                        cont++;
                    }

                    fclose(fp);

                    scanf("%d", &idAlunno);

                    printf("Inserire nuova altezza: ");
                    scanf("%d", &altezza);

                    classe[idAlunno].altezza = altezza;

                    fp = fopen(nomeFile, "w");

                    if (fp == NULL) {
                        printf("Errore nell'apertura del file \n");
                        break;
                    }

                    for(int i=0; i<cont; i++){
                        scriviSuFile(fp, classe[i]);
                    }

                    fclose(fp);

                    break;

                case 4: //Elimina alunno

                    cont = 0;

                    fp=fopen(nomeFile, "r");

                    if (fp == NULL) {
                        printf("Errore nell'apertura del file \n");
                        break;
                    }

                    printf("Quale alunno vuoi eliminare?\n");
                    while(fgets(line, sizeof(line), fp) != NULL) {
                        caricaDaFile(&classe[cont], line);
                        stampaAlunno(classe,cont);
                        cont++;
                    }
                    fclose(fp);
                    scanf("%d", &idAlunno);

                    fp = fopen(nomeFile, "w");

                    if (fp == NULL) {
                        printf("Errore nell'apertura del file \n");
                        break;
                    }

                    for(int i=0; i<cont; i++){
                        if(i!=idAlunno) {
                            scriviSuFile(fp, classe[i]);
                        }
                    }
                    fclose(fp);

                    break;
            }
        }while (scelta!=0);


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
    //printf("%s\n", token);
    token = strtok( NULL, ";" );
    strcpy(cognome, token);
    //printf("%s\n", token);

    token = strtok( NULL, ";" );
    strcpy(h, token);

    altezza=(int) atoll(h);
    //printf("%s\n", token);

    inizializzaAlunno(nome, cognome, altezza, a);
}

void stampaAlunno(Alunno classe[], int cont){
    printf("%d  %s;%s;%d\n", cont, classe[cont].nome, classe[cont].cognome, classe[cont].altezza);
}