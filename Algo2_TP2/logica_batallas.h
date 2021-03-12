#ifndef __LOGICA_BATALLAS__
#define __LOGICA_BATALLAS__

#include "aventura_pokemon.h"
#include "batallas.h"

/*
 * Funcion que dado un pokemon devuelve true si pertenece al personaje,
 * fasle de caso contrario.
 * INPUT: sturct personaje_t pointer, int, void pointer.
 * OUTPUT: bool.
 */
bool pokemon_esta_en_pokemones_para_combatir(personaje_t* personaje, int cantidad, void* pokemon);

/*
 * Funcion que dado un pokemon devuelve true si pertenece al personaje,
 * fasle de caso contrario.
 * INPUT: struct juego_t pointer, bool pointer.
 * OUTPUT: struct juego_t pointer.
 */
juego_t* jugar_partida(juego_t* juego, bool* bandera_interaccion);

#endif /* __LOGICA_BATALLAS__ */