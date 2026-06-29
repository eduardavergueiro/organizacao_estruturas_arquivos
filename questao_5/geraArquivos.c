#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    FILE *entrada;
    FILE *a1;
    FILE *a2;

    Endereco e;
    double sorteio;

    entrada = fopen("cep.dat", "rb");
    a1 = fopen("a1.dat", "wb");
    a2 = fopen("a2.dat", "wb");

    if(!entrada || !a1 || !a2){
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    srand(time(NULL));

    while(fread(&e, sizeof(Endereco), 1, entrada) == 1){
        sorteio = (double) rand() / RAND_MAX;

        if(sorteio < 0.8){
            fwrite(&e, sizeof(Endereco), 1, a1);
        }

        sorteio = (double) rand() / RAND_MAX;

        if(sorteio < 0.8){
            fwrite(&e, sizeof(Endereco), 1, a2);
        }
    }

    fclose(entrada);
    fclose(a1);
    fclose(a2);

    printf("Arquivos gerados com sucesso.\n");

    return 0;
}