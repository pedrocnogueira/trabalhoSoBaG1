#include <stdio.h>
#include <stdlib.h>

#include "converteutf832.h"

int main() {
    // Arquivos para teste
    FILE *arquivoEntradaUtf8 = fopen("testes/entrada_utf8.txt", "rb");
    FILE *arquivoSaidaUtf32 = fopen("testes/saida_utf32.txt", "wb");
    FILE *arquivoSaidaUtf8Final = fopen("testes/saida_utf8_final.txt", "wb");

    // Verifica se os arquivos foram abertos corretamente
    if (!arquivoEntradaUtf8) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo de entrada UTF-8.\n");
        return 1;
    }
    if (!arquivoSaidaUtf32) {
        fprintf(stderr, "Erro: Não foi possível criar o arquivo de saída UTF-32.\n");
        fclose(arquivoEntradaUtf8);
        return 1;
    }

    // Executa a conversão de UTF-8 para UTF-32
    if (convUtf8p32(arquivoEntradaUtf8, arquivoSaidaUtf32) == -1) {
        fprintf(stderr, "Erro ao converter o arquivo de UTF-8 para UTF-32.\n");
        fclose(arquivoEntradaUtf8);
        fclose(arquivoSaidaUtf32);
        return 1;
    }

    // // Fecha os arquivos usados para a primeira conversão
    fclose(arquivoEntradaUtf8);
    fclose(arquivoSaidaUtf32);

    // Abre o arquivo UTF-32 gerado para a conversão de volta para UTF-8
    arquivoSaidaUtf32 = fopen("testes/saida_utf32.txt", "rb");
    if (!arquivoSaidaUtf32) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo de saída UTF-32.\n");
        return 1;
    }
    if (!arquivoSaidaUtf8Final) {
        fprintf(stderr, "Erro: Não foi possível criar o arquivo de saída final UTF-8.\n");
        fclose(arquivoSaidaUtf32);
        return 1;
    }

    // Executa a conversão de UTF-32 para UTF-8
    if (convUtf32p8(arquivoSaidaUtf32, arquivoSaidaUtf8Final) == -1) {
        fprintf(stderr, "Erro ao converter o arquivo de UTF-32 para UTF-8.\n");
        fclose(arquivoSaidaUtf32);
        fclose(arquivoSaidaUtf8Final);
        return 1;
    }

    // Fecha os arquivos finais
    fclose(arquivoSaidaUtf32);
    fclose(arquivoSaidaUtf8Final);

    printf("Conversão completa com sucesso! Arquivos gerados:\n");
    printf("- Arquivo UTF-32: saida_utf32.txt\n");
    printf("- Arquivo final UTF-8: saida_utf8_final.txt\n");

    return 0;
}
