#include <stdio.h>

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

int comparaEndereco(const void *a, const void *b) {
    return strncmp(((Endereco *)a)->cep, ((Endereco *)b)->cep, 8);
}

void intercalaArquivos(const char *arq1, const char *arq2, const char *saida) { // mesma lógica que intercala.c
    FILE *a, *b, *out;
    Endereco ea, eb;
    int la, lb;

    a = fopen(arq1, "rb");
    b = fopen(arq2, "rb");
    out = fopen(saida, "wb");

    la = fread(&ea, sizeof(Endereco), 1, a);
    lb = fread(&eb, sizeof(Endereco), 1, b);

    while (la == 1 && lb == 1) {
        if (strncmp(ea.cep, eb.cep, 8) <= 0) {
            fwrite(&ea, sizeof(Endereco), 1, a);
        } else {
            fwrite(&eb, sizeof(Endereco), 1, out);
            lb = fread(&eb, sizeof(Endereco), 1, b);
        }
    }

    while (la == 1) {
        fwrite(&ea, sizeof(Endereco), 1, out);
        la = fread(&ea, sizeof(Endereco), 1, a);
    }

    while (lb == 1) {
        fwrite(&eb, sizeof(Endereco), 1, out);
        lb = fread(&eb, sizeof(Endereco), 1, b);
    }

    fclose(a);
    fclose(b);
    fclose(out);
}

int main (int argc, char **argv) {
    if (argc != 3) {
    fprintf(stderr, "USO: %s [arquivo_entrada.dat] [tam_bloco_em_registros]", argv[0]);
    return 1;
    }
}