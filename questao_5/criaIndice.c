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
    FILE *f;
    ArvoreB *a;
    Endereco e;

    char chave[TAM_CHAVE + 1];
    long posicao = 0;

    a = ArvoreB_Abre("arvore.dat");

    f = fopen("a2.dat", "rb");

    if(!f){
        printf("Erro ao abrir a2.dat\n");
        return 1;
    }

    while(fread(&e, sizeof(Endereco), 1, f) == 1){
        sprintf(chave, "%.8s", e.cep);

        ArvoreB_Insere(a, chave, posicao);

        posicao++;

        if(posicao % 10000 == 0){
            printf(".");
            fflush(stdout);
        }
    }

    printf("\nTotal de registros indexados: %ld\n", posicao);

    fclose(f);
    ArvoreB_Fecha(a);

    return 0;
}