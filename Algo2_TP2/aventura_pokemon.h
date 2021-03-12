#ifndef __AVENTURA_POKEMON__
#define __AVENTURA_POKEMON__

#include "m_heap.h"
#include "m_lista.h"

#include <stdio.h>
#include <stdbool.h> //printf
#include <stdlib.h> //calloc
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
    lista_t* v_pokemones; //cola
    int cantidad_pokemones;
    int medallas;
}entrenador_t;

typedef struct gimnasio{
    char nombre[MAX_NOMBRE];
    int dificultad;
    lista_t* v_entrenadores; //Pila
    int cont_entrenadores;
    int id_puntero_funcion;
}gimnasio_t;

typedef struct personaje{
    char nombre[MAX_NOMBRE];
    pokemon_t** pokemon_para_combatir; //PARTY //Vector que apunte a los elementos de la cola
    lista_t* pokemon_obtenidos; //CAJA //Cola
    int cantidad_pokemones;
}personaje_t;

typedef struct juego{
    heap_t* heap;
    personaje_t* personaje;
    void* gimnasio_actual;
}juego_t;

int comparar_gimnasios(void* gimnasio1, void* gimnasio2);

void destruir_pokemon(pokemon_t* pokemon);

void destruir_entrenador(entrenador_t* entrenador);

void destruir_gimnasio(void* gimnasio);

void destruir_personaje(personaje_t* personaje);

void destruir_juego(juego_t* juego);

juego_t* crear_juego();

#endif /* __AVENTURA_POKEMON__ */