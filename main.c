#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 500
#define N_MAX 10000
#define KEEP_BEST false


#define RESET_COLOR "\x1b[0m"
#define NEGRO_T     "\x1b[30m"
#define NEGRO_F     "\x1b[40m"
#define ROJO_T      "\x1b[31m"
#define ROJO_F      "\x1b[41m"
#define VERDE_T     "\x1b[32m"
#define VERDE_F     "\x1b[42m"
#define AMARILLO_T  "\x1b[33m"
#define AMARILLO_F  "\x1b[43m"
#define AZUL_T      "\x1b[34m"
#define AZUL_F      "\x1b[44m"
#define MAGENTA_T   "\x1b[35m"
#define MAGENTA_F   "\x1b[45m"
#define CYAN_T      "\x1b[36m"
#define CYAN_F      "\x1b[46m"
#define BLANCO_T    "\x1b[37m"
#define BLANCO_F    "\x1b[47m"


const char alfabeto[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789 ,.!?():;<>[]{}-+*/%&|^~$#@";

// Devuelve caracter aleatorio del alfabeto
char getRandomChar();

// Devuelve una palabra con una mutacion aleatoria
char* mutate(char* word);

// Muestra la lista de palabras
void showWords(char** words, int n);

// Devuelve el puntaje de una palabra (0 es mejor)
int puntaje(char* word, char* target);

// Devuelve la palabra con mejor puntaje
char* bestWord(char** words, int n, char* target, int* bestScore);

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
    char palabra[MAX_WORD_LENGTH];
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


    // Genera array de punteros a los strings.
    char* strings[N];
    for(int i = 0; i < N; i++) {
        strings[i] = (char*)malloc(2 * sizeof(char));
        strings[i][0] = getRandomChar();
        strings[i][1] = '\0';
    }

    // // Muestra strings generados
    // printf("Strings generados:\n");
    // showWords(strings, N);

    // Mientras no se encuentre la palabra
    for(int i = 0; true; i++) {
        // printf("\n");
        int puntaje_palabra;
        char* mejorT = bestWord(strings, N, palabra, &puntaje_palabra);
        char* mejor = (char*)malloc((strlen(mejorT)+1) * sizeof(char));
        strcpy(mejor, mejorT);

        // Muestra la mejor palabra
        printf(
            AMARILLO_T "%d" AZUL_T " puntaje:"VERDE_T" %d" BLANCO_T "\t%s\n" RESET_COLOR, 
            i, 
            puntaje_palabra, 
            mejor);


        if(strcmp(mejor, palabra) == 0) {
            printf("Palabra \"%s\" encontrada en %d iteraciones\n", mejor, i);
            free(mejor);
            break;
        }

        // Genera nuevas palabras
        int inicio = 0;
        if (KEEP_BEST) {
            free(strings[0]);
            strings[0] = mejor;
            inicio = 1;
        }
        for(int i = inicio; i < N; i++) {
            free(strings[i]);
            strings[i] = mutate(mejor);
        }
        if(!KEEP_BEST) {
            free(mejor);
        }

        // // Muestra strings generados
        // printf("Strings generados:\n");
        // showWords(strings, N);
    }

    for (int i = 0; i < N; i++) {
        free(strings[i]);
    }

    return 0;
}

char getRandomChar() {
    int index = rand() % strlen(alfabeto);
    return alfabeto[index];
}

char* mutate(char* word) {
    // si choice == 0, se agrega un caracter
    // si choice == 1, se elimina un caracter

    int choice = rand() % 2;
    if (strlen(word) <= 1) {
        choice = 0;
    }

    if (choice == 0) {
        char* newWord = (char*)malloc((strlen(word)+1 +1) * sizeof(char));
        int index = rand() % (strlen(word)+1);

        for(int i = 0; i < strlen(word); i++) {
            if (i < index) {
                newWord[i] = word[i];
            } else {
                newWord[i+1] = word[i];
            }
        }
        newWord[index] = getRandomChar();
        newWord[strlen(word)+1] = '\0';
        return newWord;
    }

    else {
        char* newWord = (char*)malloc((strlen(word)-1 +1) * sizeof(char));
        int index = rand() % strlen(word);

        for(int i = 0; i < strlen(word); i++) {
            if (i < index) {
                newWord[i] = word[i];
            } else if (i > index) {
                newWord[i-1] = word[i];
            }
        }
        newWord[strlen(word)-1] = '\0';
        return newWord;
    }
}

void showWords(char** words, int n) {
    for(int i = 0; i < n; i++) {
        printf("%s\n", words[i]);
    }
}

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int puntaje(char* word, char* target) {
    int scoreTable[strlen(word)+1][strlen(target)+1];

    for(int i = 0; i <= strlen(word); i++) {
        scoreTable[i][0] = i;
    }
    for(int i = 0; i <= strlen(target); i++) {
        scoreTable[0][i] = i;
    }

    for(int i = 1; i <= strlen(word); i++) {
        for(int j = 1; j <= strlen(target); j++) {
            int scoreL, scoreU, scoreD, scoreF;
            scoreL = scoreTable[i-1][j] + 1;
            scoreU = scoreTable[i][j-1] + 1;
            scoreD = scoreTable[i-1][j-1];
            if (word[i-1] == target[j-1]) {
                scoreF = min(min(scoreL, scoreU), scoreD);
            } else {
                scoreF = min(scoreL, scoreU);
            }
            scoreTable[i][j] = scoreF;
        }
    }

    // // Muestra tabla de puntajes
    // printf("Tabla de puntajes para palabra %s y %s:\n", word, target);
    // for(int j = 0; j <= strlen(target); j++) {
    //     for(int i = 0; i <= strlen(word); i++) {
    //         printf("%d ", scoreTable[i][j]);
    //     }
    //     printf("\n");
    // }
    return scoreTable[strlen(word)][strlen(target)];
}

char* bestWord(char** words, int n, char* target, int* bestScore) {
    *bestScore = puntaje(words[0], target);
    int bestIndex = 0;
    for(int i = 1; i < n; i++) {
        int score = puntaje(words[i], target);
        if (score < *bestScore) {
            *bestScore = score;
            bestIndex = i;
        }
    }
    return words[bestIndex];
}