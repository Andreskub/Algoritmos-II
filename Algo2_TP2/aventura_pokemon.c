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
    int leer_comienzo_linea = fscanf(info_gimnasio, FORMATO_PRELECTURA, &comienzo_linea);
    if(leer_comienzo_linea != 1) return ERROR;

    if (comienzo_linea == 'G') return Gimnasio;
    else if (comienzo_linea == 'L') return Lider;
    else if (comienzo_linea == 'E') return Entrenador;
    else if (comienzo_linea == 'P') return Pokemon;
    else return ERROR;
}

pokemon_t leer_pokemon(FILE* info_gimnasio){
    pokemon_t pokemon;
    int leer_linea = fscanf(info_gimnasio, FORMATO_LECTURA_POKEMON, pokemon.especie, &(pokemon).velocidad, &(pokemon).defensa, &(pokemon).ataque);
    if(leer_linea != 4) pokemon.especie == NULL;
    
    return pokemon;
}

entrenador_t leer_entrenador(FILE* info_gimnasio){

    entrenador_t entrenador;
    int leer_linea = fscanf(info_gimnasio, FORMATO_LECTURA_ENTRENADOR, entrenador.nombre);
    if(leer_linea != 1) entrenador.nombre == NULL;

    return entrenador;
}

gimnasio_t leer_gimnasio(FILE* info_gimnasio){

    gimnasio_t gimnasio;
    int leer_linea = fscanf(info_gimnasio, FORMATO_LECTURA_GIMANSIO, gimnasio.nombre, &(gimnasio).dificultad, &(gimnasio).id_puntero_funcion);
    if(leer_linea != 3) gimnasio.nombre == NULL;

    return gimnasio;
}
/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES DE ESTRUCTURAS ++++++++++++++++++++++++++++++++++++++++++++++++++ */

pokemon_t* crear_pokemon(FILE* info_gimnasio){
    if(!info_gimnasio) return NULL;

    pokemon_t pokemon_leido = leer_pokemon(info_gimnasio);
    if(!pokemon_leido.especie) return NULL;

    pokemon_t* pokemon = calloc(1, sizeof(pokemon_t));
    if(!pokemon) return NULL;

    strcpy(pokemon->especie, pokemon_leido.especie);
    pokemon->ataque = pokemon_leido.ataque;
    pokemon->defensa = pokemon_leido.defensa;
    pokemon->velocidad = pokemon_leido.velocidad;
    return pokemon;
}

entrenador_t* crear_entrenador(FILE* info_gimnasio){
    if(!info_gimnasio) return NULL;

    entrenador_t entrenador_leido = leer_entrenador(info_gimnasio);
    if(!entrenador_leido.nombre) return NULL;

    entrenador_t* entrenador = calloc(1, sizeof(entrenador_t));
    if(!entrenador) return NULL;

    strcpy(entrenador->nombre, entrenador_leido.nombre);
    return entrenador;
}

gimnasio_t* crear_gimnasio(FILE* info_gimnasio){
    if(!info_gimnasio) return NULL;

    gimnasio_t gimnasio_leido = leer_gimnasio(info_gimnasio);
    if(!gimnasio_leido.nombre) return NULL;

    gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t));
    if(!gimnasio) return NULL;

    strcpy(gimnasio->nombre, gimnasio_leido.nombre);
    gimnasio->dificultad = gimnasio_leido.dificultad;
    gimnasio->id_puntero_funcion = gimnasio_leido.id_puntero_funcion;

    return gimnasio;
}


void lectura_cargado_gimnasio(FILE* info_gimnasio, heap_t* heap, int* bandera){
    bool bandera_gimnasio = false, bandera_lider = false, bandera_entrenador = false, bandera_pokemon = false;

    int comienzo_linea = leer_comienzo_linea(info_gimnasio);
    if(comienzo_linea == ERROR) {
        (*bandera) = ERROR;
        return ;
    }

    while(bandera == OK){
        gimnasio_t* gimnasio;

        while (bandera_gimnasio){
            
            entrenador_t* entrenador;
            pokemon_t* pokemon;
            
            switch (comienzo_linea){
                case Gimnasio:
                    if(gimnasio){
                        bandera_gimnasio = false;
                        break;
                    }
                    bandera_gimnasio = true;
                    gimnasio = crear_gimnasio(info_gimnasio);
                    break;
                case Lider:
                    bandera_lider = true;
                    entrenador = crear_entrenador(info_gimnasio);
                    break;
                case Entrenador:
                    //Same Lider
                    break;
                case Pokemon:
                    bandera_pokemon = true;
                    pokemon = crear_pokemon(info_gimnasio);
                    //lista_insertar(gimnasio->v_entrenadores[gimnasio->v_entrenadores->cantidad -1]->v_pokemones, pokemon);
                    break;
                default:
                    break;
            }

            if(bandera_gimnasio) comienzo_linea = leer_comienzo_linea(info_gimnasio);
        }

        if(bandera == OK)
            insertar_nodo(heap, gimnasio);
        //else destruir_gimnasio
    }
    
}

int cargar_archivo(const char* ruta_archivo, heap_t* heap){
    int bandera = OK; //creo bandera, retorna 0 si se pudo cargar el gimnasio, -1 si no lo pudo cargar

    FILE* info_gimnasio = fopen(ruta_archivo,"r");
    if(!info_gimnasio) return bandera = ERROR;
   

    lectura_cargado_gimnasio(info_gimnasio, &bandera)
    

    if(gimnasio) insertar_nodo(heap, gimnasio);
    else bandera = ERROR;

    fclose(info_gimnasio);
    return bandera;
}