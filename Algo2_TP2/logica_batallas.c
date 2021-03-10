#include "logica_batallas.h"
#include "batallas.h"


int seleccionar_batalla(void* pkm_1, void* pkm_2, int id_puntero_funcion){
    if(id_puntero_funcion == 1) return funcion_batalla_1(pkm_1, pkm_2);
    else if(id_puntero_funcion == 2) return funcion_batalla_2(pkm_1, pkm_2);
    else if(id_puntero_funcion == 3) return funcion_batalla_3(pkm_1, pkm_2);
    else if(id_puntero_funcion == 4) return funcion_batalla_4(pkm_1, pkm_2);
    else if(id_puntero_funcion == 5) return funcion_batalla_5(pkm_1, pkm_2);
    else return -5;
}

pokemon_t* mejorar_pokemon(pokemon_t* pokemon){
    if(pokemon->cantidad_victorias >= 63) return pokemon;

    pokemon->ataque++;
    pokemon->defensa++;
    pokemon->velocidad++;
    pokemon->cantidad_victorias++;
    return pokemon;
}

personaje_t* tomar_pokemon_prestado(personaje_t* personaje, entrenador_t* entrenador){
    //Imprimir pokemones de personaje y entrenador
    int posicion;
    //pedir cual quiere
    void* pokemon_prestado = lista_elemento_en_posicion(entrenador->v_pokemones, *posicion*);
    for(int i = 0; i < entrenador->cantidad_pokemones; i++){
        if(lista_primero(entrenador->v_pokemones) == pokemon_prestado){
            lista_desencolar(entrenador->v_pokemones);
        }else {
            destruir_pokemon(lista_primero(entrenador->v_pokemones));
            lista_desencolar(entrenador->v_pokemones);
        }
    }

    //ME FALTA HACER CALLOC DE V_POKEMONES Y AGREGARLO 
}

bool logica_partida_en_batalla(personaje_t* personaje, entrenador_t* entrenador, int id_puntero_funcion){
    bool bandera_victoria = true;
    int pkm_entrenador1 = 0, pkm_entrenador2 = 0;
    //int max_pokemones = max_cantidad_pokemones(personaje, entrenador, &i);
    
    while (bandera && (pkm_entrenador1 <= personaje->cantidad_pokemones) && (pkm_entrenador2 <= entrenador->cantidad_pokemones)){
        int ganador = seleccionar_batalla(personaje->pokemon_para_combatir[pkm_entrenador1], lista_elemento_en_posicion(entrenador->v_pokemones, pkm_entrenador2), id_puntero_funcion);
        //if(ganador == -5) bandera = false;

        if(ganador == GANO_PRIMERO) {
            mejorar_pokemon(personaje->pokemon_para_combatir[pkm_entrenador1]);
            pkm_entrenador2++;
        }else if(ganador == GANO_SEGUNDO) pkm_entrenador1++;

    }

    return bandera_victoria;
}

void logica_partida_en_gimnasio(personaje_t* personaje, gimnasio_t* gimnasio){


    while(bandera_derrota && gimnasio->cont_entrenadores > 0){
        entrenador_t* ultimo_entrenador = (entrenador_t*)lista_ultimo(gimnasio->v_entrenadores);
        if(logica_partida_en_batalla(personaje, ultimo_entrenador, gimnasio->id_puntero_funcion)){
            if(gimnasio->cont_entrenadores == 1){
                //Preguntar si quiere guardarse uno de sus pokemones
            } else if(ultimo_entrenador) destruir_entrenador(ultimo_entrenador);

            lista_desapilar(gimnasio->v_entrenadores);
        } else bandera_derrota = true;
    }
}


void logica_partida(juego_t* juego){
    if(!juego || !juego->personaje || !juego->heap) return;

    bool bandera = true;
    int contador_gimnasios = 0;

    while(bandera && contador_gimnasios < juego->heap->cantidad){
        if(juego->gimnasio_actual) juego->heap->destructor(juego->gimnasio_actual);

        juego->gimnasio_actual = (gimnasio_t*)extraer_nodo_raiz(juego->heap);
        if(!juego->gimnasio_actual) bandera = false;

        logica_partida_en_gimnasio(juego->personaje, juego->gimnasio_actual);

        contador_gimnasios++;
    }
    
}