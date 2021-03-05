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

typedef struct pokemon{
    char especie[MAX_NOMBRE];
    int ataque;
    int defensa;
    int velocidad;
}pokemon_t;

typedef struct entrenador{
    char nombre[MAX_NOMBRE];
    lista_t* v_pokemones;
    int cantidad_pokemones;
    int medallas;
    //Algo++
}entrenador_t;

typedef struct gimnasio{
    char nombre[MAX_NOMBRE];
    int dificultad;
    lista_t* v_entrenadores; //Pila
    int cont_entrenadores;
    int id_puntero_funcion;
    //Algo++
}gimnasio_t;

typedef struct personaje{
    char nombre[MAX_NOMBRE];
    pokemon_t** party; //Vector que apunte a los elementos de la cola
    lista_t* caja; //Cola
    int cantidad_pokemones;
}personaje_t;

void destruir_pokemon(pokemon_t* pokemon);

void destruir_entrenador(entrenador_t* entrenador);

void destruir_gimnasio(gimnasio_t* gimnasio, heap_destructor_elemento destructor);

void destruir_personaje(personaje_t* personaje);

#endif /* __AVENTURA_POKEMON__ */