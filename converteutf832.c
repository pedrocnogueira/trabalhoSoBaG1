#include <stdio.h>
#include <stdint.h>

// Função que retorna o número de bytes de um caractere, dado o primeiro byte
int numberOfBytes(char primByte) {
    if ((primByte & 0x80) == 0) return 1;
    if ((primByte & 0xE0) == 0xC0) return 2;
    if ((primByte & 0xF0) == 0xE0) return 3;
    return 4;
}

// Função para montar um caractere UTF-32 a partir de um array de bytes UTF-8
// Os & aplicam uma máscara para pegar apenas os bits que serao inclusos no caractere final
// Os << ajeitam esse números na posição que eles ficarão no caractere final
// Os | juntam cada um desses pedacos no caracter final
uint32_t montaCaracter32(const char* c8, int size) {
    uint32_t caracter32 = 0;

    if (size == 1) {
        caracter32 = c8[0];
    } else if (size == 2) {
        caracter32 = ((c8[0] & 0x1F) << 6) | (c8[1] & 0x3F);
    } else if (size == 3) {
        caracter32 = ((c8[0] & 0x0F) << 12) | ((c8[1] & 0x3F) << 6) | (c8[2] & 0x3F);
    } else if (size == 4) {
        caracter32 = ((c8[0] & 0x07) << 18) | ((c8[1] & 0x3F) << 12) | ((c8[2] & 0x3F) << 6) | (c8[3] & 0x3F);
    }

    return caracter32;
}

// Função para converter UTF-8 para UTF-32 little-endian com BOM
int convUtf8p32(FILE *arquivo_entrada, FILE *arquivo_saida) {
    // Verifica se o arquivo de entrada é nulo
    if (!arquivo_entrada) {
        fprintf(stderr, "Erro: Arquivo de entrada nulo.\n");
        return -1;
    }

    // Verifica se o arquivo de saída é nulo
    if (!arquivo_saida) {
        fprintf(stderr, "Erro: Arquivo de saída nulo.\n");
        return -1;
    }

    // Escreve o BOM (Byte Order Mark) para UTF-32 little-endian
    uint32_t bom = 0x0000FEFF;
    if (fwrite(&bom, sizeof(bom), 1, arquivo_saida) != 1) {
        fprintf(stderr, "Erro na escrita do BOM no arquivo de saída.\n");
        return -1;
    }

    char caracter[4];
    size_t bytesRead;
    uint32_t caracter32;

    // Lê cada caractere do arquivo de entrada UTF-8
    while ((bytesRead = fread(&caracter[0], 1, 1, arquivo_entrada)) == 1) {
        int qtdBytes = numberOfBytes(caracter[0]);

        // Lê os bytes restantes do caractere UTF-8, se necessário
        if (qtdBytes > 1) {
            if (fread(&caracter[1], 1, qtdBytes - 1, arquivo_entrada) != qtdBytes - 1) {
                fprintf(stderr, "Erro na leitura do arquivo de entrada.\n");
                return -1;
            }
        }

        // Converte o caractere UTF-8 para UTF-32
        caracter32 = montaCaracter32(caracter, qtdBytes);

        // Escreve o caractere UTF-32 no arquivo de saída em formato little-endian
        if (fwrite(&caracter32, sizeof(caracter32), 1, arquivo_saida) != 1) {
            fprintf(stderr, "Erro na escrita no arquivo de saída.\n");
            return -1;
        }
    }

    // Verifica se houve algum erro na leitura do arquivo de entrada
    if (ferror(arquivo_entrada)) {
        fprintf(stderr, "Erro na leitura do arquivo de entrada.\n");
        return -1;
    }

    return 0;
}
