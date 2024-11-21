#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int casillas;
char c, aux;
int i, j, val;
int** crearLaberinto(int* ancho, int* altura, char* fp, int* pos);
int** crearIntersecciones(int** Laberinto, int altura, int ancho);