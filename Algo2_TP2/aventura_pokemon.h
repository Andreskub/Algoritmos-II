#ifndef __AVENTURA_POKEMON__
#define __AVENTURA_POKEMON__

#include "m_heap.h"
#include "m_lista.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>

#define OK 0
#define ERROR -1

#define MAX_NOMBRE 50
#define MAX_POKEMONES_PARTY 6

#define BATALLA_1 1
#define BATALLA_2 2
#define BATALLA_3 3
#define BATALLA_4 4
#define BATALLA_5 5

typedef struct pokemon{
    char especie[MAX_NOMBRE];
    int ataque;
    int defensa;
    int velocidad;
    int cantidad_victorias;
}pokemon_t;

typedef struct entrenador{
    char nombre[MAX_NOMBRE];
    lista_t* v_pokemones; //Cola
    int medallas;
}entrenador_t;

typedef struct gimnasio{
    char nombre[MAX_NOMBRE];
    int dificultad;
    lista_t* v_entrenadores; //Pila
    int id_puntero_funcion;
}gimnasio_t;

typedef struct personaje{
    char nombre[MAX_NOMBRE];
    pokemon_t** pokemon_para_combatir; //PARTY //Vector que apunte a los elementos de la cola
    lista_t* pokemon_obtenidos; //CAJA //Cola
}personaje_t;

typedef struct juego{
    heap_t* heap;
    personaje_t* personaje;
    void* gimnasio_actual;
}juego_t;

/*
 * COMPARADOR: compara los nieveles de dos gimnasios. devuelve
 * 1 se gana el primero o empatan, -1 si gana el segundo.
 * INPUT: void pointer, void pointer.
 * OUTPUT: int.
 */
int comparar_gimnasios(void* gimnasio1, void* gimnasio2);


/*
 * Funcion que dado un pokemon, libera su memoria dinamica.
 * INPUT: struct pokemon_t pointer.
 * OUTPUT: void.
 */
void destruir_pokemon(pokemon_t* pokemon);


/*
 * Funcion que dado un entrenador, libera su memoria dinamica.
 * INPUT: struct entrenador_t pointer.
 * OUTPUT: void.
 */
void destruir_entrenador(entrenador_t* entrenador);

/*
 * Funcion que dado un gimnasio, libera su memoria dinamica.
 * INPUT: struct gimnasio_t pointer.
 * OUTPUT: void.
 */
void destruir_gimnasio(void* gimnasio);

/*
 * Funcion que dado un personaje, libera su memoria dinamica.
 * INPUT: struct personaje_t pointer.
 * OUTPUT: void.
 */
void destruir_personaje(personaje_t* personaje);


/*
 * Funcion que dado un juego_t, libera su memoria dinamica,
 * tanto su heap como personaje.
 * INPUT: struct juego_t pointer.
 * OUTPUT: void.
 */
void destruir_juego(juego_t* juego);

/*
 * Funcion que crea el juego, y a si mismo, crea su
 * correspondiente heap.
 * INPUT: None.
 * OUTPUT: struct juego_t pointer.
 */
juego_t* crear_juego();

#endif /* __AVENTURA_POKEMON__ */