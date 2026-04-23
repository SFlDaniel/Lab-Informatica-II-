#include <iostream>
#include <fstream>
#include <cstring>
#include "rle.h"
#include "lz78.h"
#include "crypto.h"

using namespace std;

int main() {
    try {
        // 1. Leer archivo
        ifstream file("entrada.txt");
        if (!file) throw runtime_error("No se pudo abrir el archivo");

        char input[5000];
        int pos = 0;
        char c;

        while (file.get(c)) {
            input[pos++] = c;
        }

        input[pos] = '\0';
        file.close();

        cout << "Texto original: " << input << endl;

        // 2. Elegir método
        int option;
        cout << "Metodo (1=RLE, 2=LZ78): ";
        cin >> option;

        char compressed[2000];
        char decompressed[2000];

        // Para LZ78
        int indices[1000];
        char chars[1000];
        int size = 0;

        // 3. COMPRESIÓN
        if (option == 1) {
            rleCompress(input, compressed);
        } else {
            compressLZ78(input, indices, chars, size);

            // Convertir a string simple (para poder encriptar)
            int pos = 0;
            for (int i = 0; i < size; i++) {
                compressed[pos++] = indices[i] + '0';
                compressed[pos++] = chars[i];
            }
            compressed[pos] = '\0';
        }

        cout << "Comprimido: " << compressed << endl;

        // 4. ENCRIPTACIÓN
        encrypt(compressed, 3, 'K');
        cout << "Encriptado: " << compressed << endl;

        // 5. DESENCRIPTACIÓN
        decrypt(compressed, 3, 'K');
        cout << "Desencriptado: " << compressed << endl;

        // 6. DESCOMPRESIÓN
        if (option == 1) {
            rleDecompress(compressed, decompressed);
        } else {
            // reconstruir arrays
            int pos = 0;
            for (int i = 0; compressed[pos] != '\0'; i++) {
                indices[i] = compressed[pos++] - '0';
                chars[i] = compressed[pos++];
                size = i + 1;
            }

            decompressLZ78(indices, chars, size, decompressed);
        }

        cout << "Resultado final: " << decompressed << endl;

        // Verificación
        if (strcmp(input, decompressed) == 0) { cout << "coincide con el original\n";
        } else { cout << "no coincide\n"; }

        // 8. Guardar resultado
        ofstream out("salida.txt");
        out << decompressed;
        out.close();

    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}