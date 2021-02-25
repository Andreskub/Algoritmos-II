#include "aventura_pokemon.h"
#include "m_heap.h"

#define FORMATO_PRELECTURA "%[^;];"
#define FORMATO_LECTURA_GIMANSIO "%100[^;];%i;%i\n"
#define FORMATO_LECTURA_ENTRENADOR "%50[^\n]\n"
#define FORMATO_LECTURA_POKEMON "%100[^;];%i;%i;%i\n"

#define Gimnasio 1
#define Lider 2
#define Entrenador 3
#define Pokemon 4

#define OK 0
#define ERROR -1


/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES DE LECTURA ++++++++++++++++++++++++++++++++++++++++++++++++++ */

int leer_comienzo_linea (FILE* info_gimnasio){
    char comienzo_linea;
    int leer_prelinea = fscanf(info_gimnasio, FORMATO_PRELECTURA, comienzo_linea);
    if(leer_prelinea != 1) return ERROR;

    if (comienzo_linea == 'G') return Gimnasio;
    else if (comienzo_linea == 'L') return Lider;
    else if (comienzo_linea == 'E') return Entrenador;
    else if (comienzo_linea == 'P') return Pokemon;
    else return ERROR;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES DE ESTRUCTURAS ++++++++++++++++++++++++++++++++++++++++++++++++++ */

pokemon_t crear_pokemon(FILE* info_gimnasio){
    //if(!info_gimnasio) return NULL;

    pokemon_t pokemon;
    int leer_linea = fscanf(info_gimnasio, FORMATO_LECTURA_POKEMON, pokemon.especie, &(pokemon).velocidad, &(pokemon).defensa, &(pokemon).ataque);
    //if(leer_linea != 4) return NULL;
    
    return pokemon;
}

entrenador_t* cargar_pokemon_aux(entrenador_t* entrenador, pokemon_t pokemon_recorrido){
	if (entrenador->cantidad_pokemones >= 0){
		void* aux = realloc(entrenador->v_pokemones, (size_t)(entrenador->cantidad_pokemones + 1) * sizeof(pokemon_t));
		if (!aux) return NULL;
		
		entrenador->v_pokemones = aux;
	}

	entrenador->v_pokemones[entrenador->cantidad_pokemones] = pokemon_recorrido;
	entrenador->cantidad_pokemones++;
	return entrenador;
}

entrenador_t* cargar_pokemon(entrenador_t* entrenador, pokemon_t pokemon){
    if(!entrenador || !pokemon.especie) return NULL;

    entrenador = cargar_pokemon_aux(entrenador, pokemon);
    return entrenador;
}

entrenador_t* crear_entrenador(FILE* info_gimnasio){

    entrenador_t* entrenador = calloc(1, sizeof(entrenador_t));
    if(!entrenador) return NULL;

    int leer_linea = fscanf(info_gimnasio, FORMATO_LECTURA_ENTRENADOR, entrenador->nombre);
    if(leer_linea != 1){
        free(entrenador);
        return NULL;
    }

    return entrenador;
}

gimnasio_t* cargar_entrenador_aux (gimnasio_t* gimnasio, entrenador_t* entrenador_recorrido){
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
    
    gimnasio = cargar_entrenador_aux(gimnasio, entrenador);
    return gimnasio;
}

gimnasio_t* crear_gimnasio(FILE* info_gimnasio){
    
    gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t));
    if(!gimnasio) return NULL;

    int leer_linea = fscanf(info_gimnasio, FORMATO_LECTURA_GIMANSIO, gimnasio->nombre, gimnasio->dificultad, gimnasio->id_puntero_funcion);
    if(leer_linea != 3){
        free(gimnasio);
        return NULL;
    }
    return gimnasio;
}


void lectura_cargado_estructuras(FILE* info_gimnasio, int comienzo_linea, gimnasio_t* gimnasio, entrenador_t* entrenador , bool* bandera_gimnasio, bool* bandera_entrenador){
    
    switch (comienzo_linea){
        case Gimnasio:
            if (*bandera_gimnasio)
                //guardar el gimnasio en el heap
                gimnasio = NULL;
            
            gimnasio = crear_gimnasio(info_gimnasio);
            (*bandera_gimnasio) = false;
            break;
        case Lider:
        if(*bandera_entrenador){
                cargar_entrenador(gimnasio, entrenador);
                entrenador = NULL;
            } 
            (*bandera_gimnasio) = true;
            entrenador = crear_entrenador(info_gimnasio);
            (*bandera_entrenador) = false;
            break;
        case Entrenador:
            //Same Lider
            break;
        case Pokemon:
            (*bandera_entrenador) = true;
            pokemon_t pokemon = crear_pokemon(info_gimnasio);
            cargar_pokemon(entrenador, pokemon);
            break;
        default:
            break;
    }
}

void cargar_archivo(const char* ruta_archivo, heap_t* heap){

    FILE* info_gimnasio = fopen(ruta_archivo,"r");
    if(!info_gimnasio) return;

    bool bandera_gimnasio = false, bandera_entrenador = false;
    int prelinea = leer_comienzo_linea(info_gimnasio);

    if(prelinea == ERROR){
        fclose(info_gimnasio);
        return ;
    }

    gimnasio_t* gimnasio;
    entrenador_t* entrenador;
    while (prelinea != ERROR){
        lectura_cargado_estructuras(info_gimnasio, prelinea, gimnasio, entrenador, &bandera_gimnasio, &bandera_entrenador);

        prelinea = leer_comienzo_linea(info_gimnasio);
    }

    fclose(info_gimnasio);
}