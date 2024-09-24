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
    int cont=0;
    char ch='a';
    int i=0;
    char datiAlunno[100];
    int scelta=-1;
    Alunno classe[40];

    do{
        printf("\nGESTORE ALUNNI      \n");
        printf("Seleziona un opzione: \n");
        printf("1 - Aggiungi alunno   \n");
        printf("2 - Elimina alunno    \n");
        printf("3 - Modifica altezza  \n");
        printf("4 - Visualizza alunno \n\n");
        printf("0 - Esci              \n");
        scanf("%d", &scelta);

        switch(scelta){
            case 1: //Aggiungi alunno
                fp= fopen("classe/4aii.txt", "r");
                if(fp == NULL){
                    printf("Errore nell'apertura del file\n");
                }

                while(!feof(fp)){ //lettura della stringa di un file
                    fgets(datiAlunno, 100, fp);
                    while(ch!='|'&&i==3){ //Prende il nome
                        ch=gets(datiAlunno);
                        i++

                    }
                    printf("%s", datiAlunno);
                    cont++;
                }
                printf("\n");

                fclose(fp);
                break;

            case 2:
                break;
        }

    }while(scelta!=0);
}
