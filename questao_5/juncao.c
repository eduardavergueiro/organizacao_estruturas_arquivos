#include <stdio.h>
#include "ArvoreB.h"

typedef struct _Endereco Endereco;

struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int main()
{
    FILE *a1;
    FILE *saida;

    ArvoreB *arvore;

    Endereco e;

    char chave[TAM_CHAVE + 1];

    long posicao;
    long lidos = 0;
    long encontrados = 0;

    arvore = ArvoreB_Abre("arvore.dat");

    a1 = fopen("a1.dat", "rb");
    saida = fopen("Intersecoes.dat", "wb");

    if(!a1 || !saida){
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    while(fread(&e, sizeof(Endereco), 1, a1) == 1){
        sprintf(chave, "%.8s", e.cep);

        posicao = ArvoreB_Busca(arvore, chave);

        if(posicao != -1){
            fwrite(&e, sizeof(Endereco), 1, saida);
            encontrados++;
        }

        lidos++;

        if(lidos % 10000 == 0){
            printf("Lidos: %ld  Intersecoes: %ld\n", lidos, encontrados);
        }
    }

    printf("\nTotal lidos: %ld\n", lidos);
    printf("Total de intersecoes: %ld\n", encontrados);

    fclose(a1);
    fclose(saida);
    ArvoreB_Fecha(arvore);

    return 0;
}