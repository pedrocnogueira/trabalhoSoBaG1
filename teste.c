#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converteutf832.h"

// Protótipo da função convUtf8p32 a ser testada
int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida);

// Função auxiliar para criar um arquivo de teste UTF-8
void criaArquivoEntradaUtf8(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (!arquivo) {
        perror("Erro ao criar o arquivo de entrada");
        exit(EXIT_FAILURE);
    }

    // Escrevendo uma série de caracteres UTF-8 no arquivo de entrada
    const char *conteudo_utf8 = "Año€𐍈😊"; // Inclui caracteres ASCII, 2 bytes, 3 bytes e 4 bytes
    fwrite(conteudo_utf8, 1, strlen(conteudo_utf8), arquivo);
    fclose(arquivo);
}

// Função auxiliar para exibir o conteúdo de um arquivo UTF-32
void exibeArquivoSaidaUtf32(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de saída");
        exit(EXIT_FAILURE);
    }

    // Leitura e exibição dos caracteres UTF-32 do arquivo de saída
    uint32_t caracter;
    printf("Conteúdo do arquivo de saída UTF-32:\n");
    while (fread(&caracter, sizeof(uint32_t), 1, arquivo) == 1) {
        printf("0x%08X\n", caracter);
    }
    fclose(arquivo);
}

int main() {
    const char *nome_arquivo_entrada = "entrada_utf8.txt";
    const char *nome_arquivo_saida = "saida_utf32.txt";

    // Cria o arquivo de entrada com caracteres UTF-8
    criaArquivoEntradaUtf8(nome_arquivo_entrada);

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

    // Exibe o conteúdo do arquivo de saída para verificação
    exibeArquivoSaidaUtf32(nome_arquivo_saida);

    return 0;
}
