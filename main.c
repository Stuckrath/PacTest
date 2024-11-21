#include <SDL.h>
#include <stdio.h>
#include "MatrizOG.h"
#define WIDTH 600
#define HEIGHT 480
#define esctime 100
int ancho = 0, altura = 1;
int main() {

	int pos[10];
	printf("Ingresar el nombre del archivo .txt a leer (.txt incluido) (Asegurar que se encuentre en la carpeta Laberintos): ");
	char Arch[96] = "Laberintos\\";
	char test = getchar();
	int ii = 0;
	while (test != '\n') {
		Arch[ii + 11] = test;
		ii++;
		test = getchar();
	}
	int i = 0;
	printf("Todo bien 1\n");
	printf("%s \n", Arch);
	int** Laber = crearLaberinto(&ancho, &altura, Arch, pos);
	printf("\n %d %d %d\n ", Laber[1][1], ancho, altura);
	ancho--;
	int** Intersecciones = crearIntersecciones(Laber,altura,ancho);


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError()); return 0;
	}
	// Crear la ventana, renderer, y KeyboardGet
	SDL_Window* window = SDL_CreateWindow("Captura de Eventos de Teclado", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError()); return 0;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		fprintf(stderr, "Error al crear el renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window); SDL_Quit(); return 0;
	}

	const Uint8* tecla = SDL_GetKeyboardState(NULL);
	SDL_Event event;
	int quitaux = esctime;


	while (quitaux) {
		// Manejo de eventos
		while (SDL_PollEvent(&event) != 0) {
			// Evento de salida (por ejemplo, cerrar la ventana)
			if (event.type == SDL_QUIT) {
				quitaux = 0;
			}
			// Evento de teclado
			else if (event.type == SDL_KEYDOWN) {
				// Imprimir la tecla presionada
				printf("Tecla presionada: %s\n",
					SDL_GetKeyName(event.key.keysym.sym));
				if (tecla[SDL_SCANCODE_ESCAPE])
					quitaux--;
				else quitaux = esctime;
			}
		}
	}
	// Liberar recursos
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
