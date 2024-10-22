#include <stdio.h>
#include <stdlib.h>

#include "converteutf832.h"

int main() {
    // Arquivos para o primeiro teste: UTF-8 para UTF-32
    FILE *arquivoEntradaUtf8 = fopen("utf8/utf8_peq.txt", "rb");
    FILE *arquivoSaidaUtf32 = fopen("utf8/utf8p32.txt", "wb");

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

    // Fecha os arquivos após a primeira conversão
    fclose(arquivoEntradaUtf8);
    fclose(arquivoSaidaUtf32);

    printf("Primeira conversão (UTF-8 -> UTF-32) concluída.\n");

    // Arquivos para o segundo teste: UTF-32 para UTF-8
    FILE *arquivoEntradaUtf32 = fopen("utf8/utf8p32.txt", "rb");
    FILE *arquivoSaidaUtf8 = fopen("utf8/utf8p32p8.txt", "wb");

    // Verifica se os arquivos foram abertos corretamente
    if (!arquivoEntradaUtf32) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo de entrada UTF-32.\n");
        return 1;
    }
    if (!arquivoSaidaUtf8) {
        fprintf(stderr, "Erro: Não foi possível criar o arquivo de saída UTF-8.\n");
        fclose(arquivoEntradaUtf32);
        return 1;
    }

    // Executa a conversão de UTF-32 para UTF-8
    if (convUtf32p8(arquivoEntradaUtf32, arquivoSaidaUtf8) == -1) {
        fprintf(stderr, "Erro ao converter o arquivo de UTF-32 para UTF-8.\n");
        fclose(arquivoEntradaUtf32);
        fclose(arquivoSaidaUtf8);
        return 1;
    }

    // Fecha os arquivos após a segunda conversão
    fclose(arquivoEntradaUtf32);
    fclose(arquivoSaidaUtf8);

    printf("Segunda conversão (UTF-32 -> UTF-8) concluída.\n");

    // Terceiro teste: converter outro UTF-32 para UTF-8 diretamente
    FILE *arquivoEntradaUtf32Outro = fopen("utf32/utf32_peq.txt", "rb");
    FILE *arquivoSaidaUtf8Outro = fopen("utf32/utf8_peq_final.txt", "wb");

    // Verifica se os arquivos foram abertos corretamente
    if (!arquivoEntradaUtf32Outro) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo de entrada UTF-32.\n");
        return 1;
    }
    if (!arquivoSaidaUtf8Outro) {
        fprintf(stderr, "Erro: Não foi possível criar o arquivo de saída UTF-8.\n");
        fclose(arquivoEntradaUtf32Outro);
        return 1;
    }

    // Executa a conversão de UTF-32 para UTF-8 novamente
    if (convUtf32p8(arquivoEntradaUtf32Outro, arquivoSaidaUtf8Outro) == -1) {
        fprintf(stderr, "Erro ao converter o arquivo de UTF-32 para UTF-8.\n");
        fclose(arquivoEntradaUtf32Outro);
        fclose(arquivoSaidaUtf8Outro);
        return 1;
    }

    // Fecha os arquivos finais
    fclose(arquivoEntradaUtf32Outro);
    fclose(arquivoSaidaUtf8Outro);

    printf("Terceira conversão (UTF-32 -> UTF-8) concluída.\n");

    printf("Todos os testes foram concluídos com sucesso!\n");

    return 0;
}
