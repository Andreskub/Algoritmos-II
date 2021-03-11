#include "aventura_pokemon.h"
#include "logica_batallas.h"
#include "funciones_imprenta.h"
#include "batallas.h"


int seleccionar_batalla(void* pkm_1, void* pkm_2, int id_puntero_funcion){
    if(id_puntero_funcion == 1) return funcion_batalla_1(pkm_1, pkm_2);
    else if(id_puntero_funcion == 2) return funcion_batalla_2(pkm_1, pkm_2);
    else if(id_puntero_funcion == 3) return funcion_batalla_3(pkm_1, pkm_2);
    else if(id_puntero_funcion == 4) return funcion_batalla_4(pkm_1, pkm_2);
    else if(id_puntero_funcion == 5) return funcion_batalla_5(pkm_1, pkm_2);
    else return -5;
}

void* mejorar_pokemon(pokemon_t* pokemon){
    if(pokemon->cantidad_victorias >= 63) return pokemon;

    pokemon->ataque++;
    pokemon->defensa++;
    pokemon->velocidad++;
    pokemon->cantidad_victorias++;
    return (void*)pokemon;
}
//FALTA CORREGIR ESTA FUNCIOOOOOOOON Y HACER UNA BANDERA_VICTORIA
personaje_t* tomar_pokemon_prestado(personaje_t* personaje, entrenador_t* entrenador){
    //Imprimir pokemones de personaje y entrenador
    size_t posicion ;
    while(posicion < 0 && posicion > entrenador->cantidad_pokemones) posicion = pedir_posicion_pokemon(&posicion); //pedir cual quiere
    void* pokemon_prestado = lista_elemento_en_posicion(entrenador->v_pokemones, posicion);
    for(int i = 0; i < entrenador->cantidad_pokemones; i++){
        if(lista_primero(entrenador->v_pokemones) == pokemon_prestado){
            lista_desencolar(entrenador->v_pokemones);
        }else {
            destruir_pokemon(lista_primero(entrenador->v_pokemones));
            lista_desencolar(entrenador->v_pokemones);
        }
    }

    if(pokemon_prestado) lista_encolar(personaje->pokemon_obtenidos, pokemon_prestado);
    return personaje;
}

personaje_t* logica_partida_en_batalla(personaje_t* personaje, entrenador_t* entrenador, int id_puntero_funcion, bool* bandera_derrota){
    int pkm_entrenador1 = 0, pkm_entrenador2 = 0;
    
    while(!(*bandera_derrota) && pkm_entrenador2 <= entrenador->cantidad_pokemones){
        void* pkm_1 = personaje->pokemon_para_combatir[pkm_entrenador1];
        void* pkm_2 = lista_elemento_en_posicion(entrenador->v_pokemones, pkm_entrenador2);
        int ganador = seleccionar_batalla(pkm_1, pkm_2, id_puntero_funcion);

        if(ganador == GANO_PRIMERO){
            personaje->pokemon_para_combatir[pkm_entrenador1] = mejorar_pokemon((pokemon_t*)pkm_1);
            pkm_entrenador2++;
        }else if(ganador == GANO_SEGUNDO) pkm_entrenador1++;
        
        if(pkm_entrenador1 > personaje->cantidad_pokemones) (*bandera_derrota) = true;
    }

    return personaje;
}

personaje_t* logica_partida_en_gimnasio(personaje_t* personaje, gimnasio_t* gimnasio){
    bool bandera_derrota = false;

    int i = 0;
    while(!bandera_derrota && i < gimnasio->cont_entrenadores){
        entrenador_t* entrenador_actual = (entrenador_t*)lista_elemento_en_posicion(gimnasio->v_entrenadores, gimnasio->cont_entrenadores -i);
        personaje = logica_partida_en_batalla(personaje, entrenador_actual, gimnasio->id_puntero_funcion, &bandera_derrota);

        if(!bandera_derrota && gimnasio->cont_entrenadores == 1)
            personaje = tomar_pokemon_prestado(personaje, entrenador_actual); //Preguntar si quiere guardarse uno de sus pokemones
        i++;
    }

    return personaje;
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