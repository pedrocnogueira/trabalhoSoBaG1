#include <stdio.h>
#include <stdlib.h>

#include "converteutf832.h"

int main() {

    FILE* arqEntrada = fopen("Modified_File.txt", "rb");
    FILE* arqSaida = fopen("modified_utf8.txt", "wb");

    convUtf32p8(arqEntrada, arqSaida);

    return 0;

    // // Arquivos para o primeiro teste
    // FILE *arqEntrada01 = fopen("testeFinal/entradas/UTF-32-ASCII-Pequeno-BigEndian.txt", "rb");
    // FILE *arqSaida01 = fopen("testeFinal/saidas/UTF-32-ASCII-Pequeno-BigEndian.txt", "wb");

    // // Verifica se os arquivos foram abertos corretamente
    // if (!arqEntrada01) {
    //     fprintf(stderr, "Erro: Não foi possível abrir o arquivo de entrada UTF-8.\n");
    //     return 1;
    // }
    // if (!arqSaida01) {
    //     fprintf(stderr, "Erro: Não foi possível criar o arquivo de saída UTF-32.\n");
    //     fclose(arqEntrada01);
    //     return 1;
    // }

    // // Executa a conversão de UTF-8 para UTF-32
    // if (convUtf32p8(arqEntrada01, arqSaida01) == -1) {
    //     fprintf(stderr, "Erro ao converter o arquivo de UTF-8 para UTF-32.\n");
    //     fclose(arqEntrada01);
    //     fclose(arqSaida01);
    //     return 1;
    // }

    // // Fecha os arquivos após a primeira conversão
    // fclose(arqEntrada01);
    // fclose(arqSaida01);

    // printf("Primeira conversão (UTF-32 -> UTF-8) concluída.\n");

    // // Arquivos para o segundo teste
    // FILE *arqEntrada02 = fopen("testeFinal/entradas/UTF-32-ASCII-Grande-BigEndian.txt", "rb");
    // FILE *arqSaida02 = fopen("testeFinal/saidas/UTF-32-ASCII-Grande-BigEndian.txt", "wb");

    // // Verifica se os arquivos foram abertos corretamente
    // if (!arqEntrada02) {
    //     fprintf(stderr, "Erro: Não foi possível abrir o arquivo de entrada UTF-32.\n");
    //     return 1;
    // }
    // if (!arqSaida02) {
    //     fprintf(stderr, "Erro: Não foi possível criar o arquivo de saída UTF-8.\n");
    //     fclose(arqEntrada02);
    //     return 1;
    // }

    // // Executa a conversão de UTF-32 para UTF-8
    // if (convUtf32p8(arqEntrada02, arqSaida02) == -1) {
    //     fprintf(stderr, "Erro ao converter o arquivo de UTF-32 para UTF-8.\n");
    //     fclose(arqEntrada02);
    //     fclose(arqSaida02);
    //     return 1;
    // }

    // // Fecha os arquivos após a segunda conversão
    // fclose(arqEntrada02);
    // fclose(arqSaida02);

    // printf("Segunda conversão (UTF-32 -> UTF-8) concluída.\n");

    // // Teste 03
    // FILE *arqEntrada03 = fopen("testeFinal/entradas/UTF-32-2bytes-Pequeno-BigEndian.txt", "rb");
    // FILE *arqSaida03 = fopen("testeFinal/saidas/UTF-32-2bytes-Pequeno-BigEndian.txt", "wb");

    // // Verifica se os arquivos foram abertos corretamente
    // if (!arqEntrada03) {
    //     fprintf(stderr, "Erro: Não foi possível abrir o arquivo de entrada UTF-32.\n");
    //     return 1;
    // }
    // if (!arqSaida03) {
    //     fprintf(stderr, "Erro: Não foi possível criar o arquivo de saída UTF-8.\n");
    //     fclose(arqEntrada03);
    //     return 1;
    // }

    // // Executa a conversão de UTF-32 para UTF-8
    // if (convUtf32p8(arqEntrada03, arqSaida03) == -1) {
    //     fprintf(stderr, "Erro ao converter o arquivo de UTF-32 para UTF-8.\n");
    //     fclose(arqEntrada03);
    //     fclose(arqSaida03);
    //     return 1;
    // }

    // // Fecha os arquivos após a segunda conversão
    // fclose(arqEntrada03);
    // fclose(arqSaida03);

    // printf("Terceira conversão (UTF-32 -> UTF-8) concluída.\n");

    // // Teste 04
    // FILE *arqEntrada04 = fopen("testeFinal/entradas/UTF-32-3bytes-Pequeno-BigEndian.txt", "rb");
    // FILE *arqSaida04 = fopen("testeFinal/saidas/UTF-32-3bytes-Pequeno-BigEndian.txt", "wb");

    // // Verifica se os arquivos foram abertos corretamente
    // if (!arqEntrada04) {
    //     fprintf(stderr, "Erro: Não foi possível abrir o arquivo de entrada UTF-32.\n");
    //     return 1;
    // }
    // if (!arqSaida04) {
    //     fprintf(stderr, "Erro: Não foi possível criar o arquivo de saída UTF-8.\n");
    //     fclose(arqEntrada04);
    //     return 1;
    // }

    // // Executa a conversão de UTF-32 para UTF-8
    // if (convUtf32p8(arqEntrada04, arqSaida04) == -1) {
    //     fprintf(stderr, "Erro ao converter o arquivo de UTF-32 para UTF-8.\n");
    //     fclose(arqEntrada04);
    //     fclose(arqSaida04);
    //     return 1;
    // }

    // // Fecha os arquivos após a segunda conversão
    // fclose(arqEntrada04);
    // fclose(arqSaida04);

    // printf("Quarta conversão (UTF-32 -> UTF-8) concluída.\n");

    // // Teste 05
    // FILE *arqEntrada05 = fopen("testeFinal/entradas/UTF-32-4bytes-Pequeno-BigEndian.txt", "rb");
    // FILE *arqSaida05 = fopen("testeFinal/saidas/UTF-32-4bytes-Pequeno-BigEndian.txt", "wb");

    // // Verifica se os arquivos foram abertos corretamente
    // if (!arqEntrada05) {
    //     fprintf(stderr, "Erro: Não foi possível abrir o arquivo de entrada UTF-32.\n");
    //     return 1;
    // }
    // if (!arqSaida05) {
    //     fprintf(stderr, "Erro: Não foi possível criar o arquivo de saída UTF-8.\n");
    //     fclose(arqEntrada05);
    //     return 1;
    // }

    // // Executa a conversão de UTF-32 para UTF-8
    // if (convUtf32p8(arqEntrada05, arqSaida05) == -1) {
    //     fprintf(stderr, "Erro ao converter o arquivo de UTF-32 para UTF-8.\n");
    //     fclose(arqEntrada05);
    //     fclose(arqSaida05);
    //     return 1;
    // }

    // // Fecha os arquivos após a segunda conversão
    // fclose(arqEntrada05);
    // fclose(arqSaida05);

    // printf("Quinta conversão (UTF-32 -> UTF-8) concluída.\n");

    // // Teste 06
    // FILE *arqEntrada06 = fopen("testeFinal/entradas/UTF-32-1-4bytes-Pequeno-BigEndian.txt", "rb");
    // FILE *arqSaida06 = fopen("testeFinal/saidas/UTF-32-1-4bytes-Pequeno-BigEndian.txt", "wb");

    // // Verifica se os arquivos foram abertos corretamente
    // if (!arqEntrada06) {
    //     fprintf(stderr, "Erro: Não foi possível abrir o arquivo de entrada UTF-32.\n");
    //     return 1;
    // }
    // if (!arqSaida06) {
    //     fprintf(stderr, "Erro: Não foi possível criar o arquivo de saída UTF-8.\n");
    //     fclose(arqEntrada06);
    //     return 1;
    // }

    // // Executa a conversão de UTF-32 para UTF-8
    // if (convUtf32p8(arqEntrada06, arqSaida06) == -1) {
    //     fprintf(stderr, "Erro ao converter o arquivo de UTF-32 para UTF-8.\n");
    //     fclose(arqEntrada06);
    //     fclose(arqSaida06);
    //     return 1;
    // }

    // // Fecha os arquivos após a segunda conversão
    // fclose(arqEntrada06);
    // fclose(arqSaida06);

    // printf("Sexta conversão (UTF-32 -> UTF-8) concluída.\n");

    // return 0;
}
