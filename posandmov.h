#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int const ancho, altura;
int scatter;

void movfantasmas();
int checkmov(int, int*, int**);
int screenwrap(int** Lab, int x, int y);
void movact(int mov, int* P, int ov); 
int distancia(int* P, int* T, int mx, int my);