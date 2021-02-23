#ifndef __AVENTURA_POKEMON__
#define __AVENTURA_POKEMON__

#include <stdio.h>
#include <stdbool.h> //printf
#include <stdlib.h> //calloc


#define MAX_NOMBRE 50

typedef struct pokemon{
    char especie[MAX_NOMBRE];
    int velocidad;
    int defensa;
    int ataque;
}pokemon_t;

typedef struct entrenador{
    char nombre[MAX_NOMBRE];
    pokemon_t* v_pokemones;
    int cantidad_pokemones;
    int medallas;
    //Algo++
}entrenador_t;

typedef struct gimnasio{
    char nombre[MAX_NOMBRE];
    int dificultad;
    entrenador_t* v_entrenadores;
    int cont_entrenadores;
    int id_puntero_funcion;
    //Algo++
}gimnasio_t;


#endif /* __AVENTURA_POKEMON__ */