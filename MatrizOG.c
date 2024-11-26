#include "MatrizOG.h"
int** crearLaberinto(int* ancho, int* altura, char* fp, int* pos) {
	FILE* fp1 = fopen(fp, "r");
    if (fp1 == NULL) {
        printf("No se pudo abrir el archivo correctamente\n");
        exit(0);
    }
    casillas = 1;
    while (!feof(fp1)) {
        c = getc(fp1);
        if (c == '\n') {
            (*altura)++;
            if (*ancho == 0) {
                (*ancho) = casillas;
            }
        }
        else {
            casillas++;
        }
    }
    if (*altura<=6 || *ancho<=6 || casillas<70) {
        printf("La matriz no cumple con las condiciones para que sea un juego justo\n");
        printf("(Archivo debe contener al menos 7 columnas, 7 filas, y 70 casillas");
        exit(0);
    }
    int** LABERINTO = malloc(*altura * sizeof(int*));
    for (int i = 0; i < *altura; i++) { LABERINTO[i] = (int*)malloc(*ancho * sizeof(int)); }
    FILE* Laberinto = fopen(fp, "r");
    i = 0; j = 0;
    while ((aux = fgetc(Laberinto)) != EOF)
    {   
        switch (aux) {
        case '#': val = -1; break;
        case '0': val = 0; break;
        case '*': val = 1; break;
        case 'P': val = 2; *(pos + 0) = j; *(pos + 1) = i; break;
        case 'b': val = 3; *(pos + 2) = j; *(pos + 3) = i; break;
        case 'c': val = 4; *(pos + 4) = j; *(pos + 5) = i; break;
        case 'i': val = 5; *(pos + 6) = j; *(pos + 7) = i; break;
        case 'p': val = 6; *(pos + 8) = j; *(pos + 9) = i; break;
        case '+': val = 7; break;
        }
        LABERINTO[i][j] = val;
        j++;
        if (j == *ancho) { j = 0; i++; }
    }
    fclose(fp1);
    fclose(Laberinto);

    return LABERINTO;
}

int** crearIntersecciones(int** Laberinto,int altura, int ancho){
    int** Inter = malloc(altura * sizeof(int*));
    for (int i = 0; i < altura; i++) { Inter[i] = (int*)malloc(ancho * sizeof(int)); }
    int cont=0;
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < ancho; j++) {
            cont = 0;
            if (i == 0 || i == altura - 1 || j == 0 || j == ancho - 1) {
                Inter[i][j] = 0;
                continue;
            }
            if (Laberinto[i+1][j] > -1)cont++;
            if (Laberinto[i-1][j] > -1)cont++;
            if (Laberinto[i][j+1] > -1)cont++;
            if (Laberinto[i][j-1] > -1)cont++;
            if (cont >= 3) Inter[i][j] = 1; else Inter[i][j] = 0;
        }
    }
    return Inter;
}