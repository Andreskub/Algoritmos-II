#include "obtener_datos_archivo.h"
#include "aventura_pokemon.h"
#include "m_heap.h"
#include "m_lista.h"

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

personaje_t leer_personaje(FILE* info_personaje){
    personaje_t personaje;
    int leer_linea = fscanf(info_personaje, FORMATO_LECTURA_ENTRENADOR, personaje.nombre);
    if(leer_linea != 1) personaje.nombre == NULL;
    
    return personaje;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES CREACION DE ESTRUCTURAS ++++++++++++++++++++++++++++++++++++++++++++++++++ */

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
    entrenador->v_pokemones = lista_crear();
    if(!entrenador->v_pokemones) destruir_entrenador(entrenador);

    return entrenador;
}

gimnasio_t* crear_gimnasio(FILE* info_gimnasio){
    if(!info_gimnasio) return NULL;

    gimnasio_t gimnasio_leido = leer_gimnasio(info_gimnasio);
    if(!gimnasio_leido.nombre || gimnasio_leido.dificultad < 0) return NULL;

    gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t));
    if(!gimnasio) return NULL;

    strcpy(gimnasio->nombre, gimnasio_leido.nombre);
    gimnasio->dificultad = gimnasio_leido.dificultad;
    gimnasio->id_puntero_funcion = gimnasio_leido.id_puntero_funcion;
    gimnasio->v_entrenadores = lista_crear();
    if(!gimnasio->v_entrenadores) destruir_gimnasio(gimnasio);

    return gimnasio;
}

personaje_t* crear_personaje(FILE* info_personaje){
    if(!info_personaje) return NULL;

    personaje_t personaje_leido = leer_personaje(info_personaje);
    if(!personaje_leido.nombre) return NULL;

    personaje_t* personaje = calloc(1, sizeof(personaje_t));
    if(!personaje) return NULL;

    strcpy(personaje->nombre, personaje_leido.nombre);
    personaje->pokemon_obtenidos = lista_crear();
    if(!personaje->pokemon_obtenidos) destruir_personaje(personaje);

    return personaje;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES GENERALES LECTURA GIMNASIO ++++++++++++++++++++++++++++++++++++++++++++++++++ */

gimnasio_t* lectura_cargado_archivo_gimnasio(FILE* info_gimnasio, gimnasio_t* gimnasio, int comienzo_linea, bool* bandera_archivo, bool* bandera_gimnasio, bool* bandera_entrenador){

    entrenador_t* nuevo_entrenador = NULL;
    pokemon_t* nuevo_pokemon = NULL;
    int bandera_insercion_lista = ERROR;

    switch (comienzo_linea){
        case Gimnasio:
            if((*bandera_gimnasio) == true){

                gimnasio = crear_gimnasio(info_gimnasio);
                if(!gimnasio){
                    (*bandera_gimnasio) = false;
                    (*bandera_archivo) = false;
                }
            } else (*bandera_gimnasio) = false;
            break;
        case Lider:
            if(gimnasio->v_entrenadores->nodo_inicio != NULL){//!gimnasio->v_entrenadores->nodo_inicio
                (*bandera_gimnasio) = false;
                (*bandera_archivo) = false;
            } else {
                nuevo_entrenador = crear_entrenador(info_gimnasio);
                if(!nuevo_entrenador){
                    (*bandera_gimnasio) = false;
                    (*bandera_archivo) = false;
                }
            }
            if(nuevo_entrenador) {
                bandera_insercion_lista = lista_apilar(gimnasio->v_entrenadores, (void*)nuevo_entrenador);
                if(bandera_insercion_lista == ERROR){
                    destruir_entrenador(nuevo_entrenador);
                    (*bandera_gimnasio) = false;
                    (*bandera_archivo) = false;
                } else {
                    (*bandera_entrenador) = true;
                    gimnasio->cont_entrenadores++;
                }
            }

            break;
        case Entrenador:
            if(!gimnasio->v_entrenadores->nodo_inicio){ //Si no hay Lider y/o entrenadores previos
                (*bandera_gimnasio) = false;
                (*bandera_archivo) = false;
            } else {
                nuevo_entrenador = crear_entrenador(info_gimnasio);
                if(!nuevo_entrenador){
                    (*bandera_gimnasio) = false;
                    (*bandera_archivo) = false;
                }
            }

            if(nuevo_entrenador) {
                bandera_insercion_lista = lista_apilar(gimnasio->v_entrenadores, nuevo_entrenador);
                if(bandera_insercion_lista == ERROR){
                    destruir_entrenador(nuevo_entrenador);
                    (*bandera_gimnasio) = false;
                    (*bandera_archivo) = false;
                } else {
                    (*bandera_entrenador) = true;
                    gimnasio->cont_entrenadores++;
                }
            }
            break;
        case Pokemon:
            if(!bandera_entrenador){
                (*bandera_gimnasio) = false;
                (*bandera_archivo) = false;
            } else{
                nuevo_pokemon = crear_pokemon(info_gimnasio);
                if(!nuevo_pokemon){
                    (*bandera_gimnasio) = false;
                    (*bandera_archivo) = false;
                } else {
                    bandera_insercion_lista = lista_apilar( ((entrenador_t*)gimnasio->v_entrenadores->nodo_fin->elemento)->v_pokemones, nuevo_pokemon);
                    if(bandera_insercion_lista == ERROR){
                        destruir_pokemon(nuevo_pokemon);
                        (*bandera_gimnasio) = false;
                        (*bandera_archivo) = false;
                    } else {
                        entrenador_t* ultimo_entrenador = (entrenador_t*)lista_ultimo((void*)gimnasio->v_entrenadores);
                        ultimo_entrenador->cantidad_pokemones++;
                        (*bandera_entrenador) = false;
                    }
                }
            }
            break;
        default:
            (*bandera_archivo) = false;
            break;
    }
    
    return gimnasio;
}

heap_t* leer_y_cargar_gimnasio(const char* ruta_archivo, heap_t* heap){
    if(!ruta_archivo || !heap) return NULL;;

    FILE* info_gimnasio = fopen(ruta_archivo,"r");
    if(!info_gimnasio) return NULL;;

    bool bandera_archivo = true; //Si hay fallas en la lectura 
    bool bandera_gimnasio = true; //Habilita a crear un nuevo gimnasio
    bool bandera_entrenador = false; //Si se carga un entrenador vacio
    int comienzo_linea = leer_comienzo_linea(info_gimnasio);

    while(bandera_archivo && comienzo_linea != ERROR){
        gimnasio_t* nuevo_gimnasio;
        while(bandera_archivo && bandera_gimnasio && comienzo_linea != ERROR){
            nuevo_gimnasio = lectura_cargado_archivo_gimnasio(info_gimnasio, nuevo_gimnasio, comienzo_linea, &bandera_archivo, &bandera_gimnasio, &bandera_entrenador);

            comienzo_linea = leer_comienzo_linea(info_gimnasio);
        }
        
        //Si hubo error
        if(!bandera_archivo){
            if(nuevo_gimnasio) destruir_gimnasio(nuevo_gimnasio);
            heap_destruir(heap);
        }
        //Si hay que guardar el gimnasio
        if(bandera_archivo && bandera_gimnasio == false && comienzo_linea != ERROR){
            heap = heap_insertar_nodo(heap, (void*)nuevo_gimnasio);
            if(!heap) bandera_archivo = false;
            bandera_gimnasio = true;
        }
        //Si se leyo bien y termino
        if(bandera_archivo && comienzo_linea == ERROR){
            heap = heap_insertar_nodo(heap, (void*)nuevo_gimnasio);
            bandera_archivo = false;
        }

    }

    fclose(info_gimnasio);
    return heap;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES GENERALES LECTURA PERSONAJE ++++++++++++++++++++++++++++++++++++++++++++++++++ */

personaje_t* agregar_pokemon_para_combatir(personaje_t* personaje, pokemon_t* pokemon){
    if(!personaje) return NULL;

    if (personaje->cantidad_pokemones >= 0){
		void* aux = realloc(personaje->pokemon_para_combatir, (size_t)(personaje->cantidad_pokemones + 1) * sizeof(pokemon_t*)); //Extiende el espacio de memoria
		if (!aux) return NULL;
		
		personaje->pokemon_para_combatir = aux;
	}

    personaje->pokemon_para_combatir[personaje->cantidad_pokemones] = pokemon;
    return personaje;
}

personaje_t* obtener_datos_personaje(FILE* info_personaje, personaje_t* personaje, bool* bandera, int comienzo_linea){
    pokemon_t* nuevo_pokemon;
    int bandera_insercion_lista;

    switch(comienzo_linea){
        case Entrenador:
            if(personaje) (*bandera) = false;
            else {
                personaje = crear_personaje(info_personaje);
                if(!personaje) (*bandera) = false;
            }
            break;
        case Pokemon:
            if(!personaje) (*bandera) = false;
            else nuevo_pokemon = crear_pokemon(info_personaje);

            if(!nuevo_pokemon) (*bandera) = false;
            else bandera_insercion_lista = lista_encolar(personaje->pokemon_obtenidos, (void*)nuevo_pokemon);

            if(nuevo_pokemon && bandera_insercion_lista == ERROR){
                destruir_pokemon(nuevo_pokemon);
                (*bandera) = false;
            } else{
                personaje->cantidad_pokemones++;
                if(personaje->cantidad_pokemones <= 6) personaje = agregar_pokemon_para_combatir(personaje, nuevo_pokemon);
            }
            break;
        default:
            (*bandera) = false;
            break;
    }
    
    return personaje;
}

personaje_t* lectura_y_creacion_personaje(const char* ruta_archivo){
    if(!ruta_archivo) return NULL;

    FILE* info_personaje = fopen(ruta_archivo, "r");
    if(!info_personaje) return NULL;

    bool bandera = true;
    personaje_t* personaje = NULL;
    int comienzo_linea = leer_comienzo_linea(info_personaje);

    while(bandera && comienzo_linea != ERROR){
        personaje = obtener_datos_personaje(info_personaje, personaje, &bandera, comienzo_linea);

        comienzo_linea = leer_comienzo_linea(info_personaje);
    }

    if(!bandera) destruir_personaje(personaje);

    fclose(info_personaje);
    return personaje;
}