#include "timeandinput.h"
#include "posandmov.h"
void delay(int ms) {
	clock_t start_time = clock();
	while (clock < start_time + ms)
		; 
}
void inputdec(SDL_Event ev,Uint8* tec, int** L, int** I, int* p,int* t, int* m, int* q, int* d) {
	int maux = 0;
	while (1) {
		if (ev.type != SDL_KEYDOWN) { maux = *m; break; }
		if (tec[SDL_SCANCODE_UP] || tec[SDL_SCANCODE_W]) { maux = 1; break; }
		if (tec[SDL_SCANCODE_RIGHT] || tec[SDL_SCANCODE_D]) { maux = 2; break; }
		if (tec[SDL_SCANCODE_LEFT] || tec[SDL_SCANCODE_S]) { maux = 3; break; }
		if (tec[SDL_SCANCODE_UP] || tec[SDL_SCANCODE_A]) { maux = 4; break; }
		if (tec[SDL_SCANCODE_ESCAPE]) { *q = 0; return; }
	}
	int ov[5] = {0,0,0,0,0};
	switch (checkmov(maux, p, L)) {
	case 1: d[0] = maux; break;
	case 2: d[0] = maux; ov[0] = 1; break;
	case 0: maux = 0; break;
	}
	for (int i = 1; i <= 4; i++) {
		ov[i] = movfantasma(i,d+i,p+2*i,L, m+2*i, I, m+i);
	}


}

void mandarparadisplay(int* P, int* M, int* D, int* O, int**L) {
	//Actualizar rotacion del sprite
	//Realizar movimientos correspondientes (tener forma de hacer overwrap)
	//Checkear muerte de pacman
	//Actualizar matriz en caso de que se comio un punto o powerup
	//Actualizar puntuacion, tiempo
	//Actualizar scatter, powerup

}