/* Guilherme Ferreira de Ávila - 2311153 */
/* Pedro Carneiro Nogueira - 2310540 */

#include <stdio.h>
#include "converteutf832.h"

// Funçao que retorna o numero de bytes do caracter, recebendo o primeiro byte
int numberOfBytes(char primByte) {
    if (primByte & 0x80 == 0) return 1;
    if (primByte & 0xE0 == 0xC0) return 2;
    if (primByte & 0xC0 == 0xE0) return 3;
    return 4;
}

unsigned int montaCaracter32(char* c8, int size) {

    // Testando para o caracter 0
    if (*c8 == 0) return 0;

    // Mascaras para pegar apenas os bits que vao compor o caracter final
    unsigned int masks[4] = {0x7f, 0x7f, 0x7f, 0x7f};
    if (size == 4) {
        masks[0] = 0xF;
    } else if (size == 3) {
        masks[0] = 0x1F;
    } else if (size == 2) {
        masks[0] = 0x3F;
    }

    // Reescreve cada mascara com o conteudo a ser usado
    for (int i = 0; i < size; i++) {
        masks[i] = masks[i] & *(c8 + i);
    }

    // Montando o caracter em 32bits
    unsigned int caracter32 = 0;
    switch (size) {
    case 1:
        return *c8;
        break;
    case 2:
        caracter32 = masks[0] << 6;
        caracter32 |= masks[1];
        break;
    case 3:
        caracter32 = masks[0] << 12;
        caracter32 |= masks[1] << 6;
        caracter32 |= masks[2];
        break;
    default:
        caracter32 = masks[0] << 18;
        caracter32 |= masks[1] << 12;
        caracter32 |= masks[2] << 6;
        caracter32 |= masks[2];
        break;
    }

    return caracter32;
}

int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida) {

    // Testando se o arquivo de entrada é nulo
    if (!arquivo_entrada) {
        fprintf(stderr, "Arquivo de entrada nulo.");
        return -1;
    }

    // Testando se o arquivo de saida é nulo
    if (!arquivo_saida) {
        fprintf(stderr, "Arquivo de saida nulo.");
        return -1;
    }

    // Escrevendo o caractere BOM no inicio do arquivo
    int BOM = 0xFFFE0000;
    if (fprintf(arquivo_saida, BOM) < 0) {
        fprintf(stderr, "Erro na escrita do caracter BOM.");
        return -1;
    }

    // Array de char que terá todos os bytes de cada caracter (1 a 4) e caracter a ser construido
    char caracter[4] = {0, 0, 0, 0};
    unsigned int caracter32;

    while(!feof(arquivo_entrada)) {
        // Le o primeiro byte do caracter e coloca na posição 0 do array
        if (!fread(&caracter[0], 1, 1, arquivo_entrada)) {
            fprintf(stderr, "Erro na leitura do arquivo.");
            return -1;
        }

        // Quantidade de bytes do caracter que está sendo lido
        int qtdBytes = numberOfBytes(caracter[0]);

        // Le o restante dos bytes, se necessário
        if (qtdBytes != 1) {
            if (!fread(&caracter[1], 1, (qtdBytes - 1), arquivo_entrada)) {
                fprintf(stderr, "Erro na leitura do arquivo.");
            }
        }

        // Usa o array de bytes para montar o caracter final
        caracter32 = montaCaracter32(caracter, qtdBytes);

        // Escreve o caracter convertido no arquivo de saida
        if (fprintf(arquivo_saida, caracter32) < 0) {
            fprintf(stderr, "Erro na escrita do arquivo.");
            return -1;
        }
    }

    return 0;
}
