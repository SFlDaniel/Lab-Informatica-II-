#ifndef CRYPTO_H
#define CRYPTO_H

unsigned char rotateLeft(unsigned char value, int shift);
unsigned char rotateRight(unsigned char value, int shift);

void encrypt(char* text, int shift, char key);
void decrypt(char* text, int shift, char key);

#endif