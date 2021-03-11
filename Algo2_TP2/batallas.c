#include "batallas.h"
#include "aventura_pokemon.h"

//Ataque maximo
int funcion_batalla_1(void* pkm_1, void* pkm_2){
    if( ((pokemon_t*)pkm_1)->ataque > ((pokemon_t*)pkm_2)->ataque) return GANO_PRIMERO;
    else return GANO_SEGUNDO;
}

//Se la banca mas
int funcion_batalla_2(void* pkm_1, void* pkm_2){
    if( ((pokemon_t*)pkm_1)->defensa > ((pokemon_t*)pkm_2)->defensa) return GANO_PRIMERO;
    else return GANO_SEGUNDO;
}

//Mas pijudo
int funcion_batalla_3(void* pkm_1, void* pkm_2){
    if( ((pokemon_t*)pkm_1)->cantidad_victorias >= ((pokemon_t*)pkm_2)->cantidad_victorias) return GANO_PRIMERO;
    else return GANO_SEGUNDO;
}

//Entrenador mas completo
int funcion_batalla_4(void* pkm_1, void* pkm_2){
    int total_pkm1 = (((pokemon_t*)pkm_1)->ataque) + (((pokemon_t*)pkm_2)->defensa);
    int total_pkm2 = (((pokemon_t*)pkm_1)->ataque) + (((pokemon_t*)pkm_2)->defensa);

    if(total_pkm1 > total_pkm2) return GANO_PRIMERO;
    else return GANO_SEGUNDO;
}


int funcion_batalla_5(void* pkm_1, void* pkm_2){
    if(((pokemon_t*)pkm_1)->velocidad > ((pokemon_t*)pkm_2)->velocidad) return GANO_PRIMERO;
    else return GANO_SEGUNDO;
}