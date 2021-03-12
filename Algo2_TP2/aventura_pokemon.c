#include "aventura_pokemon.h"
#include "m_heap.h"
#include "m_lista.h"

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES COMPARADOR ++++++++++++++++++++++++++++++++++++++++++++++++++ */
int comparar_gimnasios(void* gimnasio1, void* gimnasio2){
    if(!gimnasio1 || !gimnasio2) return 0;

    if(((gimnasio_t*)gimnasio1)->dificultad <= ((gimnasio_t*)gimnasio2)->dificultad) return -1;
    else if(((gimnasio_t*)gimnasio1)->dificultad > ((gimnasio_t*)gimnasio2)->dificultad) return 1;
    else return 0;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES DESTRUCCION DE ESTRUCTURAS ++++++++++++++++++++++++++++++++++++++++++++++++++ */
void destruir_pokemon(pokemon_t* pokemon){
    if(pokemon) free(pokemon);
}

void destruir_entrenador(entrenador_t* entrenador){
    if(entrenador && entrenador->v_pokemones){
        while(entrenador->v_pokemones->cantidad > 0){
            destruir_pokemon((pokemon_t*)lista_primero(entrenador->v_pokemones));
            lista_desencolar(entrenador->v_pokemones);
        }
    }
    
    if(entrenador->v_pokemones) free(entrenador->v_pokemones);
    if(entrenador) free(entrenador);
}

void aux_destruir_gimnasio(gimnasio_t* gimnasio){
    
    while(gimnasio->v_entrenadores->cantidad > 0){
        void* ultimo_entrenador = lista_tope(gimnasio->v_entrenadores); //Ultimo entrenador porque es una PILA
        destruir_entrenador((entrenador_t*)ultimo_entrenador);
        lista_desapilar(gimnasio->v_entrenadores);
    }

    if(gimnasio->v_entrenadores) free(gimnasio->v_entrenadores);
    if(gimnasio) free(gimnasio);
}

void destruir_gimnasio(void* gimnasio){
    if(!gimnasio) return;
    else aux_destruir_gimnasio((gimnasio_t*)gimnasio);
}

void destruir_personaje(personaje_t* personaje){
    if(!personaje) return;
    
    while(personaje->pokemon_obtenidos->cantidad >= 1){
        if(personaje->pokemon_obtenidos->nodo_inicio->elemento) destruir_pokemon((pokemon_t*)personaje->pokemon_obtenidos->nodo_inicio->elemento);
        lista_desencolar(personaje->pokemon_obtenidos);
    }

    if(personaje->pokemon_obtenidos) lista_destruir(personaje->pokemon_obtenidos);
    if(personaje->pokemon_para_combatir) free(personaje->pokemon_para_combatir);
    if(personaje) free(personaje);
}

void destruir_juego(juego_t* juego){
    if(!juego) return;

    if(juego->heap) heap_destruir(juego->heap);
    if(juego->personaje) destruir_personaje(juego->personaje);
    if(juego) free(juego);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES CREACION DE ESTRUCTURAS ++++++++++++++++++++++++++++++++++++++++++++++++++ */
juego_t* crear_juego(){
    juego_t* juego = calloc(1, sizeof(juego_t));
    if(!juego) return NULL;

    juego->heap = crear_heap(comparar_gimnasios, destruir_gimnasio);
    if(!juego->heap){
        free(juego);
        return NULL;
    } return juego;
}