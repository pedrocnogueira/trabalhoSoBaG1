/* Guilherme Ferreira de Ávila - 231 */
/* Pedro Carneiro Nogueira - 2310540 */

#include <stdio.h>
#include "converteutf832.h"

int numberOfBytes(char primByte) {
    if (primByte & 0x80 == 0) return 1;
    if (primByte & 0xE0 == 0xC0) return 2;
    if (primByte & 0xC0 == 0xE0) return 3;
    return 4;
}

int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida) {

    // Escrevendo o caractere BOM no inicio do arquivo
    int BOM = 0xFFFE0000;
    fprintf(arquivo_saida, BOM);

    // Array de char que terá todos os bytes de cada caracter (1 a 4)
    char caracter[4] = {0, 0, 0, 0};

    while(!feof(arquivo_entrada)) {
        // Le o primeiro byte do caracter e coloca na posição 0 do array
        fread(&caracter[0], 1, 1, arquivo_entrada);

        // Quantidade de bytes do caracter que está sendo lido
        int qtdBytes = numberOfBytes(caracter[0]);

        // Le o restante dos bytes, se necessário
        if (qtdBytes != 1) {
            fread(&caracter[1], 1, (qtdBytes - 1), arquivo_entrada);
        }

    }

    return -1;
}
