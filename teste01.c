#include <stdio.h>
#include <stdlib.h>

#include "converteutf832.h"

#define BOM_LITTLE 0x0000FEFF
#define BOM_BIG 0xFEFF0000

int main() {

    // Teste 06
    FILE *arqEntrada06 = fopen("testeFinal/entradas/UTF-32-1-4bytes-Pequeno-BigEndian.txt", "rb");
    FILE *arqSaida06 = fopen("testeFinal/saidas/UTF-32-1-4bytes-Pequeno-BigEndian.txt", "wb");

    // Verifica se os arquivos foram abertos corretamente
    if (!arqEntrada06) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo de entrada UTF-32.\n");
        return 1;
    }
    if (!arqSaida06) {
        fprintf(stderr, "Erro: Não foi possível criar o arquivo de saída UTF-8.\n");
        fclose(arqEntrada06);
        return 1;
    }

    int bom;
    fread(&bom, sizeof(bom), 1, arqEntrada06);
    printf("BOM lido: %08x\nlido == BIG: %d\nlido == LITTLE: %d\n", bom, bom == BOM_BIG, bom == BOM_LITTLE);

    // Executa a conversão de UTF-32 para UTF-8
    if (convUtf32p8(arqEntrada06, arqSaida06) == -1) {
        fprintf(stderr, "Erro ao converter o arquivo de UTF-32 para UTF-8.\n");
        fclose(arqEntrada06);
        fclose(arqSaida06);
        return 1;
    }

    // Fecha os arquivos após a segunda conversão
    fclose(arqEntrada06);
    fclose(arqSaida06);

    return 0;
}
