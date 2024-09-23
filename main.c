#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome [60];
    char cognome [100];
    int altezza; //in centimetri

}Alunno;

void fileToString (char s[]);

int main (){
    FILE * fp;
    char file[1000];
    int scelta;
    Alunno classe[40];

    do{
        printf("GESTORE ALUNNI        \n");
        printf("Seleziona un opzione: \n");
        printf("1 - Aggiungi alunno   \n");
        printf("2 - Elimina alunno    \n");
        printf("3 - Modifica altezza  \n");
        printf("4 - Visualizza alunno \n\n");
        printf("0 - Esci              \n");
        scanf("%d", &scelta);

        switch(scelta){
            case 1: //Aggiungi alunno
                fileToString(file);
                break;

            case 2:
                break;
        }

    }while(scelta!=0);
}

void fileToString (char s[]){
    /*FILE * fp;
    char ch;
    fp= fopen("classe/4aii.txt", "r");
    if(fp == NULL){
        printf("Errore nell'apertura del file\n");
    }

    while(!feof(fp)){
        fgets(s, 1000, fp);
        printf("Ho letto %s\n", s);
    }



    fclose(fp);*/
}
