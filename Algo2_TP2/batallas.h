#ifndef __BATALLAS_H__
#define __BATALLAS_H__

#include "aventura_pokemon.h"

#define GANO_PRIMERO 1
#define GANO_SEGUNDO -1

/*
 * Se deberan implementar las 5 funciones de batalla.
 * Las reglas para decidir al ganador las inventan ustedes
 * 
 * Si el ganador es el primer pokemon, se devolvera 1
 * Si el ganador es el segundo pokemon, se devolvera -1
 * 
 * No habran empates.
 */

/*
 * Funcion que dado dos pokemones, los compara y 
 * devuelve el mas rapido.
 * INPUT: void pointer, void pointer.
 * OUTPUT: int.
 */
int funcion_batalla_1(void* pkm_1, void* pkm_2);

/*
 * Funcion que dado dos pokemones, los compara y 
 * devuelve el mas fuerte en defensa.
 * INPUT: void pointer, void pointer.
 * OUTPUT: int.
 */
int funcion_batalla_2(void* pkm_1, void* pkm_2);

/*
 * Funcion que dado dos pokemones, los compara y 
 * devuelve al que mas batallas ganadas tiene.
 * INPUT: void pointer, void pointer.
 * OUTPUT: int.
 */
int funcion_batalla_3(void* pkm_1, void* pkm_2);

/*
 * Funcion que dado dos pokemones, los compara y 
 * devuelve al mas fuerte con respecto a ataque 
 * y defensa.
 * INPUT: void pointer, void pointer.
 * OUTPUT: int.
 */
int funcion_batalla_4(void* pkm_1, void* pkm_2);

/*
 * Funcion que dado dos pokemones, los compara y 
 * devuelve el mas rapido y ofensivo.
 * INPUT: void pointer, void pointer.
 * OUTPUT: int.
 */
int funcion_batalla_5(void* pkm_1, void* pkm_2);


#endif /* __BATALLAS_H__ */