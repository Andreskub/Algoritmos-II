#include "aventura_pokemon.h"
#include "m_heap.h"
#include "m_lista.h"


/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES DESTRUCCION DE ESTRUCTURAS ++++++++++++++++++++++++++++++++++++++++++++++++++ */

void destruir_pokemon(pokemon_t* pokemon){
    if(pokemon) free(pokemon);
}

void destruir_entrenador(entrenador_t* entrenador){
    if(entrenador && entrenador->v_pokemones)
        lista_destruir(entrenador->v_pokemones);
    if(entrenador) free(entrenador);
}

void destruir_gimnasio(gimnasio_t* gimnasio, heap_destructor_elemento destructor){
    if(gimnasio && destructor) destructor((void*)gimnasio);
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