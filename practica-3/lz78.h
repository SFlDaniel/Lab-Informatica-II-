#ifndef LZ78_H
#define LZ78_H

struct Entry {
    int prefix;
    char c;
};

void compressLZ78(const char* input, int indices[], char chars[], int& outSize);
void decompressLZ78(int indices[], char chars[], int size, char* output);

#endif