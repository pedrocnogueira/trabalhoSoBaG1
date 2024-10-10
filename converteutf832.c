/* Guilherme Ferreira de Ávila - 2311153 */
/* Pedro Carneiro Nogueira - 2310540 */

#include <stdio.h>
#include <stdint.h>

#define BOM_LITTLE 0x0000FEFF
#define BOM_BIG 0xFEFF0000

/* ----- Protótipos de Funções Auxiliares ----- */

int numeroDeBytes(char primeiroByte);
int montarCaractere32(const char* c8, int tamanho);
int numeroDeBytesNecessarios(int caractere32);
void montarCaractere8(int caractere32, unsigned char* c8, int isLittleEndian);
int verificarEndianidade();
int inverterEndianidade(int valor);

/* ------------ Funções Principais ------------ */

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
    int bom = BOM_LITTLE;
    if (fwrite(&bom, sizeof(bom), 1, arquivo_saida) != 1) {
        fprintf(stderr, "Erro na escrita do BOM no arquivo de saída.\n");
        return -1;
    }

    char caractere[4];
    int bytesLidos;
    int caractere32;

    // Lê cada caractere do arquivo de entrada UTF-8
    while ((bytesLidos = fread(&caractere[0], 1, 1, arquivo_entrada)) == 1) {
        int qtdBytes = numeroDeBytes(caractere[0]);

        // Lê os bytes restantes do caractere UTF-8, se necessário
        if (qtdBytes > 1) {
            if (fread(&caractere[1], 1, qtdBytes - 1, arquivo_entrada) != qtdBytes - 1) {
                fprintf(stderr, "Erro na leitura do arquivo de entrada.\n");
                return -1;
            }
        }

        // Converte o caractere UTF-8 para UTF-32
        caractere32 = montarCaractere32(caractere, qtdBytes);

        // Escreve o caractere UTF-32 no arquivo de saída em formato little-endian
        if (fwrite(&caractere32, sizeof(caractere32), 1, arquivo_saida) != 1) {
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

// Função para converter UTF-32 para UTF-8
int convUtf32p8(FILE *arquivo_entrada, FILE *arquivo_saida) {
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

    int bom;

    // Lê e valida o BOM do arquivo UTF-32
    if (fread(&bom, sizeof(bom), 1, arquivo_entrada) != 1) {
        fprintf(stderr, "Erro na leitura do caractere BOM.\n");
        return -1;
    } else if (bom != BOM_BIG && bom != BOM_LITTLE) {
        fprintf(stderr, "Caractere BOM inválido.\n");
        return -1;
    }

    int isLittleEndian = (bom == BOM_LITTLE);
    int caractere32;
    unsigned char caractere8[4] = {0, 0, 0, 0};

    // Lê cada caractere UTF-32 do arquivo de entrada
    while (fread(&caractere32, sizeof(caractere32), 1, arquivo_entrada) == 1) {
        montarCaractere8(caractere32, caractere8, isLittleEndian);
        int qtdBytesSaida = numeroDeBytesNecessarios(caractere32);
        if (fwrite(caractere8, 1, qtdBytesSaida, arquivo_saida) != qtdBytesSaida) {
            fprintf(stderr, "Erro na escrita do arquivo de saída.\n");
            return -1;
        }
    }

    return 0;
}

/* ------------ Funções Auxiliares ------------ */

// Função para verificar se a arquitetura do sistema é little-endian
int verificarEndianidade() {
    unsigned int teste = 0x1;
    char* c = (char*)&teste;
    return *c == 0x1;
}

// Função para inverter a endianidade de um valor de 32 bits
int inverterEndianidade(int valor) {
    return ((valor & 0xFF000000) >> 24) |
           ((valor & 0x00FF0000) >> 8) |
           ((valor & 0x0000FF00) << 8) |
           ((valor & 0x000000FF) << 24);
}

// Função que retorna o número de bytes de um caractere, dado o primeiro byte
int numeroDeBytes(char primeiroByte) {
    if ((primeiroByte & 0x80) == 0) return 1;
    if ((primeiroByte & 0xE0) == 0xC0) return 2;
    if ((primeiroByte & 0xF0) == 0xE0) return 3;
    return 4;
}

// Função para montar um caractere UTF-32 a partir de um array de bytes UTF-8
int montarCaractere32(const char* c8, int tamanho) {
    int caractere32 = 0;

    if (tamanho == 1) {
        caractere32 = c8[0];
    } else if (tamanho == 2) {
        caractere32 = ((c8[0] & 0x1F) << 6) | (c8[1] & 0x3F);
    } else if (tamanho == 3) {
        caractere32 = ((c8[0] & 0x0F) << 12) | ((c8[1] & 0x3F) << 6) | (c8[2] & 0x3F);
    } else if (tamanho == 4) {
        caractere32 = ((c8[0] & 0x07) << 18) | ((c8[1] & 0x3F) << 12) | ((c8[2] & 0x3F) << 6) | (c8[3] & 0x3F);
    }

    return caractere32;
}

// Função que calcula o número de bytes necessários para representar um caractere em UTF-8
int numeroDeBytesNecessarios(int caractere32) {
    if (caractere32 <= 0x7F) {
        return 1;
    } else if (caractere32 <= 0x7FF) {
        return 2;
    } else if (caractere32 <= 0xFFFF) {
        return 3;
    } else {
        return 4;
    }
}

// Função para converter um caractere UTF-32 em UTF-8, levando em conta a endianidade
void montarCaractere8(int caractere32, unsigned char* c8, int isLittleEndian) {
    int numBytes = numeroDeBytesNecessarios(caractere32);

    if (isLittleEndian != verificarEndianidade()) {
        caractere32 = inverterEndianidade(caractere32);
    }

    if (numBytes == 1) {
        c8[0] = (unsigned char)caractere32;
    } else if (numBytes == 2) {
        c8[0] = (caractere32 >> 6) | 0xC0;
        c8[1] = (caractere32 & 0x3F) | 0x80;
    } else if (numBytes == 3) {
        c8[0] = (caractere32 >> 12) | 0xE0;
        c8[1] = ((caractere32 >> 6) & 0x3F) | 0x80;
        c8[2] = (caractere32 & 0x3F) | 0x80;
    } else {
        c8[0] = (caractere32 >> 18) | 0xF0;
        c8[1] = ((caractere32 >> 12) & 0x3F) | 0x80;
        c8[2] = ((caractere32 >> 6) & 0x3F) | 0x80;
        c8[3] = (caractere32 & 0x3F) | 0x80;
    }
}
