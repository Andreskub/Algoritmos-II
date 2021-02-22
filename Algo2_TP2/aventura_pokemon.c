#include "aventura_pokemon.h"

#define FORMATO_PRELECTURA "%c;"
#define FORMATO_LECTURA_GIMANSIO "%100[^;];%i;%i\n"
#define FORMATO_LECTURA_ENTRENADOR "%50[^\n]\n"
#define FORMATO_LECTURA_POKEMON "%100[^;];%i;%i;%i\n"

#define Gimnasio "G"
#define Entrenador "E"
#define Lider "L"
#define Pokémon "P"

pokemon_t* crear_pokemon(FILE* info_gimnasio){
    if(!info_gimnasio) return NULL;

    pokemon_t* pokemon = calloc(1, sizeof(pokemon_t));
    if(!pokemon) return NULL;

    int leer_linea = fscanf(info_gimnasio, FORMATO_LECTURA_POKEMON, pokemon.especie, &(pokemon.velocidad), &(pokemon.defensa), &(pokemon.ataque));
    if(leer_linea != 4){
        free(pokemon);
        return NULL;
    }

    return pokemon;
}

entrenador_t* cargar_pokemon_aux(entrenador_t* entrenador, pokemon_t pokemon_recorrido){
	if (entrenador->cantidad_pokemones >= 0){
		void* aux = realloc(entrenador->v_pokemones, (size_t)(entrenador->cantidad_pokemon + 1) * sizeof(pokemon_t));
		if (!aux) return NULL;
		
		entrenador->v_pokemones = aux;
	}

	entrenador->v_pokemones[entrenador->cantidad_pokemon] = pokemon_recorrido;
	entrenador->cantidad_pokemon++;
	return entrenador;
}

entrenador_t* cargar_pokemon(entrenador_t* entrenador, pokemon_t* pokemon){
    if(!entrenador || !pokemon) return NULL;

    entrenador = cargar_pokemon_aux(entrenador, pokemon);
    return entrenador;
}

entrenador_t* crear_entrenador(FILE* info_gimnasio){

    entrenador_t* entrenador = calloc(1, sizeof(entrenador_t));
    if(!entrenador) return NULL;

    int leer_linea = fscanf(info_gimnasio, FORMATO_LECTURA_ENTRENADOR, entrenador.nombre);
    if(leer_linea != 1){
        free(entrenador);
        return NULL;
    }

    return entrenador;
}

entrenador_t* cargar_entrenador_aux (gimnasio_t* gimnasio, entrenador_t entrenador_recorrido){
	if (gimnasio->cont_entrenadores >= 0){
		void* aux = realloc(gimnasio->v_entrenadores, (size_t)(gimnasio->cont_entrenadores + 1) * sizeof(entrenador_t));
		if (!aux) return NULL;
		
        gimnasio->v_entrenadores = aux;
	}

    gimnasio->v_entrenadores[gimnasio->cont_entrenadores] = entrenador_recorrido;
    gimnasio->cont_entrenadores++;

	return gimnasio;
}

gimnasio_t* cargar_entrenador(gimnasio_t* gimnasio, entrenador_t* entrenador){
    if(!gimnasio || !entrenador) return NULL;
    
    cargar_entrenador_aux(gimnasio, entrenador);
    return gimnasio;
}

gimnasio_t* crear_gimnasio(FILE* info_gimnasio){
    
    gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t));
    if(!gimnasio) return NULL;

    int leer_linea = fscanf(info_gimnasio, FORMATO_LECTURA_GIMANSIO, gimnasio.nombre, &(gimnasio).dificultad, &(gimnasio).id_puntero_funcion);
    if(leer_linea != 3){
        free(gimnasio);
        return NULL;
    }

    return gimnasio;
}


void leer_comienzo_linea(FILE* info_gimnasio, gimnasio_t* gimnasio, char expresion, bool* bandera_gimnasio){
    
    switch (expresion){
        case Gimnasio:
            if (!(*bandera_gimnasio))
                //guardar el gimnasio en el heap
                (*gimnasio) = NULL;
            
            (*gimnasio) = crear_gimnasio(info_gimnasio);

            break;
        case Lider:
            (*bandera_gimnasio) = false;
            entrenador_t* entrenador = crear_entrenador(info_gimnasio);
            //Agregar entrenador al gimnasio
            break;
        case Entrenador:
            
            break;
        case Pokémon:
            //cargar_pokemon(gimnasio->v_entrenadores[heap->cantidad])
            break;
        default:
            break;
    }
}

void cargar_archivo(const char* ruta_archio, heap_t* heap){

    FILE* info_gimnasio = fopen(ruta_archivo,"r");
    if(!info_gimnasio) return;

    bool bandera_gimnasio = true;
    char comienzo_linea;
    int leer_prelinea = fscanf(info_gimnasio, FORMATO_PRELECTURA, comienzo_linea);

    if(leer_prelinea != 1){
        fclose(info_gimnasio);
        return NULL;
    }

    gimnasio_t* gimnasio;
    while (leer_prelinea == 1){
        leer_comienzo_linea(info_gimnasio, &gimnasio, comienzo_linea, &bandera_gimnasio);

        leer_prelinea = fscanf(info_gimnasio, FORMATO_PRELECTURA, comienzo_linea);
    }

    fclose(info_gimnasio);
}
