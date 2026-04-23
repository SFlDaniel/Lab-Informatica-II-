#include "rle.h"
#include <stdexcept>

void rleCompress(const char* input, char* output) {
    if (!input || !output) throw std::runtime_error("Puntero nulo");
    int i = 0, j = 0;
    while (input[i] != '\0') {
        char current = input[i];
        int count = 1;
        while (input[i] == input[i + 1]) {
            count++;
            i++;
        }
        // guardar número
        if (count >= 10) {
            output[j++] = (count / 10) + '0';
        }
        output[j++] = (count % 10) + '0';
        output[j++] = current;
        i++;
    }
    output[j] = '\0';
}

void rleDecompress(const char* input, char* output) {
    if (!input || !output) throw std::runtime_error("Puntero nulo");
    int i = 0, j = 0;
    while (input[i] != '\0') {
        int count = input[i++] - '0';
        // soporte básico de 2 dígitos
        if (input[i] >= '0' && input[i] <= '9') {
            count = count * 10 + (input[i++] - '0');
        }
        char c = input[i++];
        for (int k = 0; k < count; k++) {
            output[j++] = c;
        }
    }
    output[j] = '\0';
}