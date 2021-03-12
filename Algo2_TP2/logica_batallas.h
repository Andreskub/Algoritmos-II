#ifndef __LOGICA_BATALLAS__
#define __LOGICA_BATALLAS__

#include "aventura_pokemon.h"
#include "batallas.h"

bool pokemon_esta_en_pokemones_para_combatir(personaje_t* personaje, int cantidad, void* pokemon);

juego_t* jugar_partida(juego_t* juego, bool* bandera_interaccion);

#endif /* __LOGICA_BATALLAS__ */