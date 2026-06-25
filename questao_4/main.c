#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CSVParser.h"

//questao 1 da p2/Processamento de CSV / Covid (1,5) (total de casos e total de mortes américa do sul). 

#define READ_BUF_SIZE 8192

typedef struct {
    int linhas;
    double totalCasos;
    double totalMortes;
} DadosCovid;

void callback(char** cols, int ncols, void* userData) {
    DadosCovid* dados = (DadosCovid*) userData;

    dados->linhas++;

    //isso é pra pular a primeira linha pq ela define as colunas no csv
    if(dados->linhas == 1)
        return;

    //garante q as colunas existem
    if(ncols > 8) {

        //filtrando apenas a américa do sul
        if(strcmp(cols[1], "South America") == 0) {

            //coluna 5 -> new_cases
            if(cols[5][0] != '\0')
                dados->totalCasos += atof(cols[5]);

            //coluna 8 -> new_deaths
            if(cols[8][0] != '\0')
                dados->totalMortes += atof(cols[8]);
        }
    }
}

int main() {
    int qt;
    unsigned int total = 0;

    char* buf = (char*) malloc(READ_BUF_SIZE);

    CSVParser csv;
    CSVParser_init(&csv);

    DadosCovid dados;
    dados.linhas = 0;
    dados.totalCasos = 0;
    dados.totalMortes = 0;

    FILE *f = fopen("owid-covid-data.csv", "rb");

    if(f) {
        qt = fread(buf, 1, READ_BUF_SIZE, f);

        while(qt > 0) {
            total += qt;
            CSVParser_processLines(&csv, buf, qt, callback, &dados);
            qt = fread(buf, 1, READ_BUF_SIZE, f);
        }
        fclose(f);

        //pra uúltima linha
        CSVParser_processLines(&csv, "\n", 1, callback, &dados);

        printf("Total de linhas lidas: %d\n", dados.linhas);
        printf("Total de casos na America do Sul: %.0lf\n", dados.totalCasos);
        printf("Total de mortes na America do Sul: %.0lf\n", dados.totalMortes);
        printf("Total de bytes lidos: %u\n", total);
    }
    else {
        printf("Erro ao abrir o arquivo.\n");
    }
    free(buf);
    return 0;
}
