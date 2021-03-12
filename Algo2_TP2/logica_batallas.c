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
juego_t* tomar_pokemon_prestado(juego_t* juego, entrenador_t* entrenador){
    //Imprimir pokemones de personaje y entrenador
    size_t posicion = 1;
    
    //while(posicion < 0 && posicion > entrenador->cantidad_pokemones) posicion = pedir_posicion_pokemon(&posicion); //pedir cual quiere
    
    void* pokemon_prestado = lista_elemento_en_posicion(entrenador->v_pokemones, posicion);
    //Saco el nodo del entrenador (NO el elemento)
    if(pokemon_prestado) {
        lista_borrar_de_posicion(entrenador->v_pokemones, posicion-1);
        entrenador->cantidad_pokemones--;
    }
    if(pokemon_prestado) {
        lista_encolar(juego->personaje->pokemon_obtenidos, pokemon_prestado);
        juego->personaje->cantidad_pokemones++;
    }

    return juego;
}

juego_t* logica_partida_en_batalla(juego_t* juego, entrenador_t* entrenador, int id_puntero_funcion, bool* bandera_derrota){
    int pkm_entrenador1 = 0, pkm_entrenador2 = 0;
    
    while(!(*bandera_derrota) && (pkm_entrenador2 < entrenador->cantidad_pokemones)){
        void* pkm_1 = juego->personaje->pokemon_para_combatir[pkm_entrenador1];
        void* pkm_2 = lista_elemento_en_posicion(entrenador->v_pokemones, pkm_entrenador2);

        int ganador = seleccionar_batalla(pkm_1, pkm_2, id_puntero_funcion);
        if(ganador == GANO_PRIMERO){
            juego->personaje->pokemon_para_combatir[pkm_entrenador1] = mejorar_pokemon((pokemon_t*)pkm_1);
            pkm_entrenador2++;
        }else if(ganador == GANO_SEGUNDO) pkm_entrenador1++;
        
        if(pkm_entrenador1 > juego->personaje->cantidad_pokemones) (*bandera_derrota) = true;
        
    }

    return juego;
}

juego_t* logica_partida_en_gimnasio(juego_t* juego, bool* bandera_derrota){

    int i = 1;
    while(!(*bandera_derrota) && i <= ((gimnasio_t*)juego->gimnasio_actual)->cont_entrenadores){
        
        entrenador_t* entrenador_actual = (entrenador_t*)lista_elemento_en_posicion(((gimnasio_t*)juego->gimnasio_actual)->v_entrenadores, ((gimnasio_t*)juego->gimnasio_actual)->cont_entrenadores -i);
        juego = logica_partida_en_batalla(juego, entrenador_actual, ((gimnasio_t*)juego->gimnasio_actual)->id_puntero_funcion, bandera_derrota);
        
        /*if(!(*bandera_derrota) && (((gimnasio_t*)juego->gimnasio_actual)->v_entrenadores->cantidad -i) == 0){
            juego = tomar_pokemon_prestado(juego, entrenador_actual); //Preguntar si quiere guardarse uno de sus pokemones
        }*/
        i++;
    }

    return juego;
}


juego_t* logica_partida(juego_t* juego){
    if(!juego || !juego->personaje || !juego->heap) return juego;

    bool bandera = true, bandera_derrota = false;
    
    while(bandera && juego->heap->cantidad >= 0){  
        if(juego->gimnasio_actual) juego->heap->destructor(juego->gimnasio_actual);
        juego->gimnasio_actual = (gimnasio_t*)extraer_nodo_raiz(juego->heap);
        
        if(!juego->gimnasio_actual) {
            printf("\nGANASTEEEEE WACHIN!\n\n");
            bandera = false;
        } else juego = logica_partida_en_gimnasio(juego, &bandera_derrota);
    }
    
    return juego;
}