#include "aventura_pokemon.h"
#include "m_heap.h"
#include "m_lista.h"


/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES DESTRUCCION DE ESTRUCTURAS ++++++++++++++++++++++++++++++++++++++++++++++++++ */

void destruir_pokemon(pokemon_t* pokemon){
    if(pokemon) free(pokemon);
}

void destruir_entrenador(entrenador_t* entrenador){
    if(entrenador->v_pokemones)
        lista_destruir(entrenador->v_pokemones);
    if(entrenador) free(entrenador);
}
void destruir_gimnasio(gimnasio_t* gimnasio, heap_destructor_elemento destructor){
    if(gimnasio) destructor((void*)gimnasio);
}
