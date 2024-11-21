#include "posandmov.h"
int checkmov(int dir, int* P, int** M) {
    int x = *P, y = *(P + 1);
    switch (dir) {
    case 1: //up
        if (y <= 0) { //Se revisa primero si el movimiento haria screenwrap o no
            return screenwrap(M,x,altura-1);
        }
        if (M[y-1][x]<0) { //Si es que no, se revisa si es un muro o no para ver si el mov es posible
            return 0;
        }
        return 1; break;
    case 2: //right
        if (x+1 >= ancho) return screenwrap(M, 0, y);
        if (M[y][x+1] < 0) return 0;
        return 1; break;
    case 3: //down
        if (y + 1 >= altura) return screenwrap(M, x, 0);
        if (M[y+1][x] < 0) return 0;
        return 1; break;
    case 4: //left
        if (x <= 0) return screenwrap(M, ancho-1, y);
        if (M[y][x-1] < 0) return 0;
        return 1;
        break;
    }
    printf("Algo sale mal con el check de movimiento X_X \n");
    return -2;
}

int screenwrap(int** Lab, int x, int y) {
    if (Lab[y][x] < 0) return 2;
    else return 0;
}

void movact(int mov, int* P, int ov) {
    if (mov == 0) return;
    if (ov == 0) {
        switch (mov) {
        case 1: *(P + 1) = altura-1; break;
        case 2: *(P) = 0; break;
        case 3: *(P + 1) = 0; break;
        case 4: *(P) = ancho-1; break;
        }
    }
    else {
        switch (mov) {
        case 1: *(P + 1) -= 1; break;
        case 2: *(P) += 1; break;
        case 3: *(P + 1) += 1; break;
        case 4: *(P) -= 1; break;
        }
    }
    return;
}
//Busca el movimiento mas eficiente para llegar al Target en una interseccion (que no sea volver sobre sus pasos)
int interseccion(int dir, int* P, int** M, int* T) {
    int dist = altura * ancho;
    int ef = 0;
    ef = intercheck(dir, 1, P, M, T, 0, -1, ef, &dist);
    ef = intercheck(dir, 2, P, M, T, 1, 0, ef, &dist);
    ef = intercheck(dir, 3, P, M, T, 0, 1, ef, &dist);
    ef = intercheck(dir, 4, P, M, T, -1, 0, ef, &dist);
    return ef;
}
int distancia(int* P, int* T, int mx, int my) {
    return fabs((*P + mx) - *T) + fabs((*(P + 1) + my) - *(T + 1));
}
int intercheck(int dirp, int dira, int* P, int** M, int* T, int mx, int my, int ef, int* dist) {
    if (checkmov(dira, P, M) != 0 && dira != dirp) {
        if (distancia(P, T, mx, my) < *dist) {
            *dist = distancia(P, T, mx, my); ef = dira;
        }
    }
    return ef;
}

void movfantasma(int obj, int* dir, int* P, int** M, int* T, int** I) { //falta interpretar bien el screenwrap
    int mov = 0;
    if (I[*P][*(P+1)] == 1) {
        target(obj, P - 2 * obj, M, T - 2 * obj, dir);
        mov = interseccion(*dir, P, M, T);
    }
    else {
        for (int z = 1; z <= 4; z++) {
            if (checkmov(z, P, M) >= 0 && z != *dir) { //cuidado que aqui no considerara screenwrap
                mov = z;
                break;
            }
        }
    }
    *dir = mov;
    movact(*dir, P, 0);
}

void tscatter(int obj, int* T) {
    int auxx = 0; int auxy = 0;
    switch (obj) {
    case 1: auxx = ancho - 1; auxy = 0; break;
    case 2: auxx = 0; auxy = 0; break;
    case 3: auxx = ancho - 1; auxy = altura - 1; break;
    case 4: auxx = 0; auxy = altura - 1; break;
    }
    *(T + 2 * obj) = auxx; *(T + 2 * obj + 1) = auxy;
    return;
}

void target(int obj, int* P, int* M, int* T, int* dir) {
    if (scatter = 1) {
        tscatter(obj, T);
    }
    else {
        switch (obj) {
        case 1: tblinky(P, M, T); break;
        case 2: tpinky(P, M, T, dir); break;
        case 3: tinky(P, M, T, dir); break;
        case 4: tclyde(P, M, T); break;
        }
    }
    return;
}

void tblinky(int* P, int* M, int* T) {
    *(T + 2) = *P;
    *(T + 3) = *(P + 1);
    return;
}
void tpinky(int* P, int* M, int* T, int* dir) {
    int mx = 0, my = 0, auxy, auxx;
    switch (*dir) {
    case 1: my = -4; break;
    case 2: mx = 4; break;
    case 3: my = 4; break;
    case 4: mx = -4; break;
    }
    auxx = max(0, *(P)+mx); auxx = min(ancho - 1, auxx);
    auxy = max(0, *(P + 1) + my); auxy = min(altura - 1, auxy);
    *(T + 4) = auxx;
    *(T + 5) = auxy;
    return;
}
void tinky(int* P, int* M, int* T, int* dir) {
    int mx = 0, my =0, xf = 0, yf = 0, xs = 0, ys = 0, vx = 0, vy = 0, auxx, auxy;
    switch (*dir) {
    case 1: my = -2; break;
    case 2: mx = 2; break;
    case 3: my = 2; break;
    case 4: mx = -2; break;
    }
    xs = *(P + 2); ys = *(P + 3);
    xf = *(P)+mx; yf = *(P + 1) + my;
    vx = xf - xs; vy = yf - ys;
    vx = xs + 2 * vx; vy = ys + 2 * vy;
    auxx = max(0, vx); auxx = min(ancho - 1, auxx);
    auxy = max(0, vy); auxy = min(altura - 1, auxy);
    *(T + 6) = auxx;
    *(T + 7) = auxy;
}
void tclyde(int* P, int* M, int* T) {
    int d = distancia(P + 8, P, 0, 0);
    if (d > 8) {
        *(T + 8) = *P;
        *(T + 9) = *(P + 1);
    }
    else {
        tscatter(4, T);
    }
    return;
}