
typedef struct _Endereco Endereco;

struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

typedef struct {
    char cep[8];
    long posicao;
} Indice;

int comparaIndice(const void *a, const void *b) {
    return strncmp(((Indice *)a)->cep, ((Indice *)b)->cep, 8);
}
int buscaBinariaIndice(Indice *v, long qtd, char *cepBuscado) {
    long ini = 0, fim = qtd - 1, meio;
    int cmp;

    while (ini <= fim) {
        meio = (ini + fim) / 2;
        cmp = strncmp(cepBuscado, v[meio].cep, 8);

        if (cmp == 0) {
            return meio;
        }
        else if (cmp < 0) {
            fim = meio - 1;
        }
        else {
            ini = meio + 1;
        }
    }
    return -1;
}
int main(int argc, char *argv[]) {
    FILE *fDados, *fIndice;
    Endereco e;
    Indice *indice;
    long qtd, i, tam;
    char cepBuscado[9];
    int posEncontrada;

    if (argc != 4) {
        printf("Uso: %s <arquivo_dados.dat> <arquivo_indice.dat> <CEP>", argv[0]);
        return 1;
    }
    fDados = fopen(argv[1], "rb");
    fseek(fDados, 0, SEEK_END);
    tam = ftell(fDados);
    qtd = tam / sizeof(Endereco);
    rewind(fDados);

    indice = (Indice *) malloc(qtd * sizeof(Indice));

    for (i = 0; i < qtd; i++) {
        fread(&e, sizeof(Endereco), 1, fDados);
        memcpy(indice[i].cep, e.cep, 8);
        indice[i].posicao = i;
    }
    qsort(indice, qtd, sizeof(Indice), comparaIndice);
    fIndice = fopen(argv[2], "wb");
    fwrite(indice, sizeof(Indice), qtd, fIndice);
    fclose(fIndice);
    strncpy(cepBuscado, argv[3], 8);
    cepBuscado[8] = '\0';
    posEncontrada = buscaBinariaIndice(indice, qtd, cepBuscado);

    if (posEncontrada == -1) {
        printf("CEP nao encontrado");
    }
    else {
        printf("CEP encontrado no indice!");
        printf("Posicao no arquivo original: %ld", indice[posEncontrada].posicao);

        fseek(fDados, indice[posEncontrada].posicao * sizeof(Endereco), SEEK_SET);
        fread(&e, sizeof(Endereco), 1, fDados);

        printf("Logradouro: %.72s", e.logradouro);
        printf("Bairro: %.72s", e.bairro);
        printf("Cidade: %.72s", e.cidade);
        printf("UF: %.72s", e.uf);
        printf("Sigla: %.2s", e.sigla);
        printf("CEP: %.8s", e.cep);
    }
    free(indice);
    fclose(fDados);
    return 0;
}