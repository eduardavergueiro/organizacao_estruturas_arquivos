#include <stdio.h>
#include <stdlib.h>
#include "CSVParser.h"

#define READ_BUF_SIZE 8192

//questao 1 da p2: Processamento de CSV / Covid (1,0)

void callback(char** cols, int ncols, void* userData) {
    int* count = (int*) userData;

    //pra mostrar as primeiras linhas tipo como o prof fez no Teste2.c
    if(*count < 5) {
        printf("--------------------------------------------------\n");
        for(int i = 0; i < ncols; i++) {
            printf("[%s]\n", cols[i]);
        }
    }

    (*count)++;
}

int main() {
    int qt, count=0;
    unsigned int total = 0;

    char* buf = (char*) malloc(READ_BUF_SIZE);

    CSVParser csv;
    CSVParser_init(&csv);

    FILE *f = fopen("owid-covid-data.csv", "rb");

    if(f) {
        qt = fread(buf, 1, READ_BUF_SIZE, f);

        while(qt > 0) {
            total += qt;
            CSVParser_processLines(
                &csv,buf,qt,callback,&count);
            qt = fread(buf, 1, READ_BUF_SIZE, f);
        }

        fclose(f);

        //pra ultima linha
        CSVParser_processLines(&csv,"\n",1,callback,&count);

        printf("\nTotal linhas: %d\n", count);
        printf("Total bytes lidos: %u\n", total);
    }
    else {
        printf("Erro ao abrir.\n");
    }

    free(buf);

    return 0;
}