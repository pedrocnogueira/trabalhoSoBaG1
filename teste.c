#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converteutf832.h"

// Protótipo da função convUtf8p32 a ser testada
int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida);

int main() {
    const char *nome_arquivo_entrada = "entrada_utf8.txt";
    const char *nome_arquivo_saida = "saida_utf32.txt";

    // Abre os arquivos de entrada e saída
    FILE *arquivo_entrada = fopen(nome_arquivo_entrada, "rb");
    if (!arquivo_entrada) {
        perror("Erro ao abrir o arquivo de entrada");
        return EXIT_FAILURE;
    }

    FILE *arquivo_saida = fopen(nome_arquivo_saida, "wb");
    if (!arquivo_saida) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(arquivo_entrada);
        return EXIT_FAILURE;
    }

    // Chama a função convUtf8p32 para converter o arquivo de entrada para UTF-32
    if (convUtf8p32(arquivo_entrada, arquivo_saida) == -1) {
        fprintf(stderr, "Erro durante a conversão de UTF-8 para UTF-32.\n");
    } else {
        printf("Conversão concluída com sucesso.\n");
    }

    // Fecha os arquivos de entrada e saída
    fclose(arquivo_entrada);
    fclose(arquivo_saida);
    
    return 0;
}
