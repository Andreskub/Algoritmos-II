#ifndef __FUNCIONES_IMPRENTA__
#define __FUNCIONES_IMPRENTA__

#include "aventura_pokemon.h"

#define None 0
#define A 1
#define B 2
#define C 3
#define E 4
#define F 5
#define G 6
#define I 7
#define N 8
#define R 9
#define S 10
#define T 11

void imprimir_mensaje_bienvenida();

void imprimir_linea(char* caracter, int multiplicador);

void imprimir_pokemon_caracteristicas(pokemon_t* pokemon);

void imprimir_entrenador_completo(entrenador_t* entrenador);

void imprimir_menu_inicio();

void imprimir_menu_gimnasio();

void imprimir_menu_batalla();

void imprimir_menu_victoria();

void imprimir_menu_derrota();

int pedir_letra();

char* pedir_nombre_archivo(char array[]);

#endif /* __FUNCIONES_IMPRENTA__ */