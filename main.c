#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_WORD_LENGTH 100

char alfabeto[] = "abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ_0123456789";

int main() {
    int N;
    printf("Numero de Strings por generacion: ");
    scanf("%d", &N);

    char* palabra = (char*)malloc(MAX_WORD_LENGTH * sizeof(char));
    printf("Palabra (maximo %d, alfabeto: [%s]): ", MAX_WORD_LENGTH, alfabeto);
    scanf("%s", palabra);


    printf("Numero de strings por generacion: %d\n", N);
    printf("Palabra: %s\n", palabra);

    return 0;
}