#include "aventura_pokemon.h"
#include "m_heap.h"
#include "m_lista.h"


int comparar_gimnasios(void* gimnasio1, void* gimnasio2){
    if(!gimnasio1 || !gimnasio2) return 0;

    if(((gimnasio_t*)gimnasio1)->dificultad < ((gimnasio_t*)gimnasio2)->dificultad) return -1;
    else if(((gimnasio_t*)gimnasio1)->dificultad > ((gimnasio_t*)gimnasio2)->dificultad) return 1;
    else return 0;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES DESTRUCCION DE ESTRUCTURAS ++++++++++++++++++++++++++++++++++++++++++++++++++ */

void destruir_pokemon(pokemon_t* pokemon){
    if(pokemon) free(pokemon);
}

void destruir_entrenador(entrenador_t* entrenador){
    if(entrenador && entrenador->v_pokemones)
        lista_destruir(entrenador->v_pokemones);
    if(entrenador) free(entrenador);
}

void aux_destruir_gimnasio(gimnasio_t* gimnasio){
    for(int i = 0; i < gimnasio->cont_entrenadores; i++){
        entrenador_t* ultimo_entrenador = (entrenador_t*)lista_tope(gimnasio->v_entrenadores); //Ultimo entrenador porque es una PILA
        for(int j = 0; j < ultimo_entrenador->cantidad_pokemones; j++){
            pokemon_t* primer_pokemon = (pokemon_t*)lista_primero(ultimo_entrenador->v_pokemones); //primer pokemon porque es una COLA
            if(primer_pokemon) destruir_pokemon(primer_pokemon);
            lista_desencolar(ultimo_entrenador->v_pokemones);
        }
        destruir_entrenador(ultimo_entrenador);
        lista_desapilar(gimnasio->v_entrenadores);
    }
    if(gimnasio) free(gimnasio);
}

void destruir_gimnasio(void* gimnasio){
    if(!gimnasio) return;
    else aux_destruir_gimnasio((gimnasio_t*)gimnasio);
}

void destruir_personaje(personaje_t* personaje){
    if(!personaje) return;
    
    for (int i = 0; i < personaje->cantidad_pokemones; i++){
        destruir_pokemon((pokemon_t*)personaje->caja->nodo_inicio->elemento);
        lista_desencolar(personaje->caja);
    }

    if(personaje->caja) lista_destruir(personaje->caja);
    if(personaje->party) free(personaje->party);
    if(personaje) free(personaje);
}