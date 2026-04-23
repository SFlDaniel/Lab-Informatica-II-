#include "crypto.h"

unsigned char rotateLeft(unsigned char value, int shift) {
    shift %= 8;
    return (value << shift) | (value >> (8 - shift));
}

unsigned char rotateRight(unsigned char value, int shift) {
    shift %= 8;
    return (value >> shift) | (value << (8 - shift));
}

void encrypt(char* text, int shift, char key) {
    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char c = (unsigned char)text[i];
        c = rotateLeft(c, shift);
        c = c ^ key;
        text[i] = (char)c;
    }
}

void decrypt(char* text, int shift, char key) {
    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char c = (unsigned char)text[i];
        c = c ^ key;
        c = rotateRight(c, shift);
        text[i] = (char)c;
    }
}