#ifndef __FUNCIONES_IMPRENTA__
#define __FUNCIONES_IMPRENTA__

#include "aventura_pokemon.h"
#include "logica_batallas.h"

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

//IMPRESIÓN GENERAL
void imprimir_mensaje_bienvenida();

void imprimir_linea(char* caracter, int multiplicador);

//IMPRESIÓN DE ELECCION
int pedir_letra_menu_derrota();

int pedir_letra_menu_victoria();

int pedir_letra_menu_batalla();

int pedir_letra_menu_gimnasio();

int pedir_letra_menu_inicio();

char* pedir_nombre_archivo(char array[]);

size_t pedir_posicion_pokemon(size_t* posicion);

//IMPRESIÓN DE ESTRUCTURAS
void imprimir_pokemon_caracteristicas(pokemon_t* pokemon);

void imprimir_entrenador_completo(entrenador_t* entrenador);

void imprimir_personaje_completo(personaje_t* personaje);

void imprimir_batalla_y_resultado(pokemon_t* pkm_1, pokemon_t* pkm_2, int ganador);

//IMPRESIÓN DE MENUS
void imprimir_menu_inicio();

void imprimir_menu_gimnasio();

void imprimir_menu_batalla();

void imprimir_menu_victoria();

void imprimir_menu_derrota();

//IMPRESIÓN DE ERRORES
void imprimir_error_general();

void imprimir_error_input();

void imprimir_error_inexistencia_personaje();

void imprimir_error_inexistencia_heap();

void imprimir_error_comiezo_partida();

#endif /* __FUNCIONES_IMPRENTA__ */