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
    if(entrenador && entrenador->v_pokemones){
        for(int i = 0; i < entrenador->cantidad_pokemones; i++){
            destruir_pokemon((pokemon_t*)lista_primero(entrenador->v_pokemones));
            lista_desencolar(entrenador->v_pokemones);
        }
    }
    if(entrenador->v_pokemones) free(entrenador->v_pokemones);
    if(entrenador) free(entrenador);
}



void aux_destruir_gimnasio(gimnasio_t* gimnasio){

    for(int i = 0; i < gimnasio->cont_entrenadores; i++){

        entrenador_t* ultimo_entrenador = (entrenador_t*)lista_tope(gimnasio->v_entrenadores); //Ultimo entrenador porque es una PILA
        destruir_entrenador(ultimo_entrenador);
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
    
    for (int i = 0; i < personaje->cantidad_pokemones; i++){
        destruir_pokemon((pokemon_t*)personaje->pokemon_obtenidos->nodo_inicio->elemento);
        lista_desencolar(personaje->pokemon_obtenidos);
    }

    if(personaje->pokemon_obtenidos) lista_destruir(personaje->pokemon_obtenidos);
    if(personaje->pokemon_para_combatir) free(personaje->pokemon_para_combatir);
    if(personaje) free(personaje);
}