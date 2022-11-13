#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 100
#define N_MAX 100

char alfabeto[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789 ";

//100 caracteres
// 12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901

char getRandomChar() {
    int index = rand() % strlen(alfabeto);
    return alfabeto[index];
}

int main() {
    srand(time(NULL));

    // Cantidad de strings que se crearan por generacion.
    int N;
    do {
        printf("Numero de Strings por generacion: ");
        scanf("%d", &N);
        if (N < 2 || N > N_MAX) {
            printf("El numero debe ser mayor o igual a 2 y menor o igual que %d.\n", N_MAX);
        }
    } while ( N < 2 || N > N_MAX);

    // Palabra de meta.
    bool palabra_valida = false;
    char* palabra = (char*)malloc(MAX_WORD_LENGTH * sizeof(char));
    do {
        printf("Alfabeto valido: %s\n", alfabeto);
        printf("Longitud maxima: %d\n", MAX_WORD_LENGTH);
        printf("Palabra: ");
        scanf("\n%[^\n]", palabra);

        palabra_valida = true;
        for(int i = 0; i < strlen(palabra); i++) {
            if(strchr(alfabeto, palabra[i]) == NULL) {
                printf("La palabra contiene caracteres no permitidos.\n\n");
                palabra_valida = false;
                break;
            }
        }
    } while(!palabra_valida);

    // Chequeo
    printf("Numero de strings por generacion: %d\n", N);
    printf("Palabra: %s\n", palabra);


    // Genera array de punteros a los strings.
    char** strings = (char**)malloc(N * sizeof(char*));


    return 0;
}