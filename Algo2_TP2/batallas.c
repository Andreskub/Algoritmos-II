#include "batallas.h"
#include "aventura_pokemon.h"

//Ataque maximo
int funcion_batalla_1(void* pkm_1, void* pkm_2){
    if( ((pokemon_t*)pkm_1)->ataque > ((pokemon_t*)pkm_2)->ataque) return GANO_PRIMERO;
    else return GANO_SEGUNDO;
}

//Se la banca mas
int funcion_batalla_2(void* pkm_1, void* pkm_2){
    int diferencia_ataque;
    int ataque_pkm_1 = ((pokemon_t*)pkm_1)->ataque;
    int ataque_pkm_2 = ((pokemon_t*)pkm_2)->ataque;
    if(ataque_pkm_1 > ataque_pkm_2) diferencia_ataque = ataque_pkm_1-ataque_pkm_2;
    else diferencia_ataque = ataque_pkm_2-ataque_pkm_1;
    if( (((pokemon_t*)pkm_1)->defensa > ((pokemon_t*)pkm_2)->defensa) && diferencia_ataque < 15) return GANO_PRIMERO;
    else return GANO_SEGUNDO;
}

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
    if((((pokemon_t*)pkm_1)->velocidad > ((pokemon_t*)pkm_2)->velocidad) && (((pokemon_t*)pkm_1)->ataque > ((pokemon_t*)pkm_2)->ataque)) return GANO_PRIMERO;
    else return GANO_SEGUNDO;
}