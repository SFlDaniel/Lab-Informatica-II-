#include "lz78.h"
#include <stdexcept>

int findEntry(Entry* dict, int size, int prefix, char c) {
    for (int i = 1; i < size; i++) {
        if (dict[i].prefix == prefix && dict[i].c == c)
            return i;
    }
    return -1;
}

void compressLZ78(const char* input, int indices[], char chars[], int& outSize) {
    if (!input) throw std::runtime_error("Entrada nula");

    Entry* dict = new Entry[1000];
    int dictSize = 1;
    int currentPrefix = 0;
    outSize = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        int index = findEntry(dict, dictSize, currentPrefix, input[i]);//busca si existe la frase prefijo+carácter

        if (index != -1) {
            currentPrefix = index;//seguir construyendo frase más larga
        } else {//emite la tupla
            indices[outSize] = currentPrefix;
            chars[outSize] = input[i];
            outSize++;

            dict[dictSize].prefix = currentPrefix;
            dict[dictSize].c = input[i];
            dictSize++;//guarda la nueva en el dict

            currentPrefix = 0;//desde cero
        }
    }

    if (currentPrefix != 0) {
        indices[outSize] = currentPrefix;
        chars[outSize] = '\0';
        outSize++;
    }

    delete[] dict;
}

void decompressLZ78(int indices[], char chars[], int size, char* output) {
    char** dict = new char*[1000];
    dict[0] = nullptr;
    int dictSize = 1;
    int outIndex = 0;

    for (int i = 0; i < size; i++) {
        if (indices[i] >= dictSize) throw std::runtime_error("Índice inválido");

        char* newEntry;

        if (indices[i] == 0) {
            newEntry = new char[2];
            newEntry[0] = chars[i];
            newEntry[1] = '\0';
        } else {
            char* prefix = dict[indices[i]];

            int len = 0;
            while (prefix[len] != '\0') len++;

            newEntry = new char[len + 2];

            for (int j = 0; j < len; j++)
                newEntry[j] = prefix[j];

            newEntry[len] = chars[i];
            newEntry[len + 1] = '\0';
        }

        dict[dictSize++] = newEntry;

        // copiar al output
        for (int k = 0; newEntry[k] != '\0'; k++) {
            output[outIndex++] = newEntry[k];
        }
    }

    output[outIndex] = '\0';

    for (int i = 1; i < dictSize; i++)
        delete[] dict[i];

    delete[] dict;
}