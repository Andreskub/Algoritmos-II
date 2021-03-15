#include "aventura_pokemon.h"
#include "logica_batallas.h"
#include "funciones_imprenta.h"
#include "batallas.h"

/*
 * Funcion que dado dos pokemones y el tipo de combate, los hace combatir
 * y retorna el resultado.
 * INPUT: void pointer, void pointer, int.
 * OUTPUT: int.
 */
int seleccionar_batalla(void* pkm_1, void* pkm_2, int id_puntero_funcion){
    if(!pkm_1 || !pkm_2 || !id_puntero_funcion) return -5;

    if(id_puntero_funcion == 1) return funcion_batalla_1(pkm_1, pkm_2);
    else if(id_puntero_funcion == 2) return funcion_batalla_2(pkm_1, pkm_2);
    else if(id_puntero_funcion == 3) return funcion_batalla_3(pkm_1, pkm_2);
    else if(id_puntero_funcion == 4) return funcion_batalla_4(pkm_1, pkm_2);
    else if(id_puntero_funcion == 5) return funcion_batalla_5(pkm_1, pkm_2);
    else return -5;
}

/*
 * Funcion que mejora en 1 todas las caracteristicas del pokemon.
 * Si el pokemon esta al maximo nivel, simplemente lo retorna.
 * INPUT: struct pokemon_t pointer.
 * OUTPUT: void pointer.
 */
void* mejorar_pokemon(pokemon_t* pokemon){
    if(pokemon->cantidad_victorias >= 63) return pokemon;

    pokemon->ataque++;
    pokemon->defensa++;
    pokemon->velocidad++;
    pokemon->cantidad_victorias++;
    return (void*)pokemon;
}

/*
 * Funcion que dado un pokemon devuelve true si pertenece al personaje,
 * fasle de caso contrario.
 * INPUT: sturct personaje_t pointer, int, void pointer.
 * OUTPUT: bool.
 */
bool pokemon_esta_en_pokemones_para_combatir(personaje_t* personaje, int cantidad, void* pokemon){
    if(0 < cantidad  && cantidad <= 6){
        for(int i = 0; i < cantidad; i++){
            if(personaje->pokemon_para_combatir[i] == (pokemon_t*)pokemon) return true;
        }
    }
    return false;
}

/*
 * Funcion que modifica el PARTY del personaje, asignando nuevos 
 * pokemones (de la CAJA) al mismo.
 * INPUT: struct personaje_t pointer.
 * OUTPUT: struct personaje_t pointer.
 */
personaje_t* cambiar_pokemones_para_combatir(personaje_t* personaje){
    imprimir_personaje_completo(personaje);
    size_t i = 0, posicion = 0; 
    while (i < 6){
        pedir_posicion_pokemon(&posicion);
        if(posicion <= personaje->pokemon_obtenidos->cantidad){
            void* pokemon = lista_elemento_en_posicion(personaje->pokemon_obtenidos, posicion-1);
            if(pokemon && !pokemon_esta_en_pokemones_para_combatir(personaje, (int)i, pokemon)){
                personaje->pokemon_para_combatir[i] = (pokemon_t*)pokemon;
                i++;
            } else imprimir_error_doble_seleccionado();
        }
        
    }
    return personaje;
}


//FALTA CORREGIR ESTA FUNCIOOOOOOOON Y HACER UNA BANDERA_VICTORIA
personaje_t* tomar_pokemon_prestado(personaje_t* personaje, entrenador_t* entrenador, int* posicion){
    //Imprimir pokemones de personaje y entrenador
    //size_t posicion = 1;
    
    //while(posicion < 0 && posicion > entrenador->cantidad_pokemones) posicion = pedir_posicion_pokemon(&posicion); //pedir cual quiere
    
    void* pokemon_prestado = lista_elemento_en_posicion(entrenador->v_pokemones, (size_t)posicion);
    //Saco el nodo del entrenador (NO el elemento)
    if(pokemon_prestado) lista_encolar(personaje->pokemon_obtenidos, pokemon_prestado);

    return personaje;
}

/*
 * Imprime el MENU_BATALLA y el resultado de la batalla.
 * Tambien solicita una eleccion sobre el menu al usuario.
 * INPUT: struct pokemon_t pointer, struct pokemon_t pointer, int.
 * OUTPUT: void.
 */
void menu_batalla(){
    imprimir_menu_batalla();
    int eleccion_usuario = pedir_letra_menu_batalla();
    while(eleccion_usuario != N){
        imprimir_error_input();
        eleccion_usuario = pedir_letra_menu_batalla();
    }
}

/*
 * Imprime el MENU_VICTORIA y le solicita una eleccion sobre el menu 
 * al usuario.
 * INPUT: struct juego_t pointer, struct entrenador_t pointer, bool pointer.
 * OUTPUT: struct juego_t pointer.
 */
juego_t* menu_victoria(juego_t* juego, entrenador_t* lider, bool* bandera_sig_gimnasio){
    imprimir_menu_victoria();
    int eleccion_usuario = pedir_letra_menu_victoria();

    switch (eleccion_usuario){
        case T:
            //juego = tomar_pokemon_prestado(juego, lider);
            break;
        case C:
            juego->personaje = cambiar_pokemones_para_combatir(juego->personaje);
            break;
        case N:
            (*bandera_sig_gimnasio) = false;
            break;
        default:
            imprimir_error_input();
            break;
    }
    return juego;
}

/*
 * Imprime el MENU_DERROTA y le solicita una eleccion sobre el menu 
 * al usuario.
 * INPUT: struct juego_t pointer, bool pointer, bool pointer.
 * OUTPUT: struct juego_t pointer.
 */
juego_t* menu_derrota(juego_t* juego, bool* bandera_salir, bool* bandera_eleccion){
    imprimir_menu_derrota();

    int eleccion_usuario = pedir_letra_menu_victoria();

    switch (eleccion_usuario){
        case C:
            juego->personaje = cambiar_pokemones_para_combatir(juego->personaje);
            break;
        case R:
            (*bandera_eleccion) = false;
            break;
        case F:
            (*bandera_salir) = false;
            (*bandera_eleccion) = false;
        default:
            imprimir_error_input();
            break;
    }
    return juego;
}

/*
 * Funcion que realiza la logica de combate de personaje vs entrenador.
 * Retorna el juego con sus modificaciones correspondientes
 * INPUT: struct juego_t pointer, struct entrenador_t pointer, int, bool pointer.
 * OUTPUT: struct juego_t pointer.
 */
juego_t* batallar_entrenador(juego_t* juego, entrenador_t* entrenador, int id_puntero_funcion, bool* bandera_derrota_entrenador){
    int pkm_entrenador1 = 0, pkm_entrenador2 = 0;
    
    while(!(*bandera_derrota_entrenador) && (pkm_entrenador2 < entrenador->v_pokemones->cantidad)){
        void* pkm_1 = juego->personaje->pokemon_para_combatir[pkm_entrenador1];
        void* pkm_2 = lista_elemento_en_posicion(entrenador->v_pokemones, (size_t)pkm_entrenador2);

        int ganador = seleccionar_batalla(pkm_1, pkm_2, id_puntero_funcion);
        if(ganador != -5) {
            imprimir_batalla_y_resultado((pokemon_t*)pkm_1, (pokemon_t*)pkm_2, ganador);
            menu_batalla();
        }

        if(ganador == GANO_PRIMERO){
            juego->personaje->pokemon_para_combatir[pkm_entrenador1] = mejorar_pokemon((pokemon_t*)pkm_1);
            pkm_entrenador2++;
        }else if(ganador == GANO_SEGUNDO) pkm_entrenador1++;

        if(pkm_entrenador1 >= MAX_POKEMONES_PARTY) (*bandera_derrota_entrenador) = true;
    }
    return juego;
}

/*
 * Funcion que realiza la logica del gimnasio recorrido y las batallas entre
 * el personaje vs los entrenadores del gimnasio.
 * Retorna el juego con sus modificaciones correspondientes.
 * INPUT: struct juego_t pointer, bool pointer.
 * OUTPUT: struct juego_t pointer.
 */
juego_t* batallar_gimnasio(juego_t* juego, bool* bandera_derrota_gimnasio){
    bool bandera_derrota_entrenador = false;
    int cantidad_entrenadores_en_gimnasio = (int)((gimnasio_t*)juego->gimnasio_actual)->v_entrenadores->cantidad;

    int i = 0;
    while(!(*bandera_derrota_gimnasio) && i < cantidad_entrenadores_en_gimnasio){
        
        entrenador_t* entrenador_actual = (entrenador_t*)lista_ultimo(((gimnasio_t*)juego->gimnasio_actual)->v_entrenadores); //lista primero
        juego = batallar_entrenador(juego, entrenador_actual, ((gimnasio_t*)juego->gimnasio_actual)->id_puntero_funcion, &bandera_derrota_entrenador);
        
        //ELSE IF ES EL PRIMER ENTRENADOR
        /*if(!bandera_derrota_entrenador && ((gimnasio_t*)juego->gimnasio_actual)->v_entrenadores->cantidad == 1){
            int posicion = 1;

            juego->personaje = tomar_pokemon_prestado(juego->personaje, entrenador_actual, &posicion);
            lista_borrar_de_posicion(entrenador_actual->v_pokemones, (size_t)posicion-1);
            destruir_entrenador(entrenador_actual);
            lista_desapilar(((gimnasio_t*)juego->gimnasio_actual)->v_entrenadores);
        }else*/ if(!bandera_derrota_entrenador){
            destruir_entrenador(entrenador_actual);
            lista_desapilar(((gimnasio_t*)juego->gimnasio_actual)->v_entrenadores);
        } else (*bandera_derrota_gimnasio) = true;

        i++;
    }
    return juego;
}

/*
 * Imprime el MENU_GIMNASIO y le solicita una eleccion sobre el menu 
 * al usuario.
 * INPUT: struct juego_t pointer, bool pointer, bool pointer.
 * OUTPUT: struct juego_t pointer.
 */
juego_t* menu_gimnasio(juego_t* juego, bool* bandera_derrota, bool* bandera_eleccion){
    imprimir_menu_gimnasio((gimnasio_t*)juego->gimnasio_actual);
    int eleccion_usuario = pedir_letra_menu_gimnasio();

    switch (eleccion_usuario){
        case E:
            imprimir_personaje_completo(juego->personaje);
            break;
        case G:
            imprimir_gimnasio_completo(juego->gimnasio_actual);
            break;
        case C: //Cambiar personajes pokemon batalla
            juego->personaje = cambiar_pokemones_para_combatir(juego->personaje);
            break;
        case B: //Realizar proxima batalla
            juego = batallar_gimnasio(juego, bandera_derrota);
            (*bandera_eleccion) = false;
            break;        
        default:
            imprimir_error_input();
            break;
    }

    return juego;
}

/*
 * Funcion que realiza la logica de toda la partida, recorriendo 
 * los gimnasios del heap y haciendo batallar al jugador contra
 * los mismos.
 * Retorna el juego con sus modificaciones correspondientes.
 * INPUT: struct juego_t pointer, bool pointer.
 * OUTPUT: struct juego_t pointer.
 */
juego_t* jugar_partida(juego_t* juego, bool* bandera_interaccion){
    bool bandera = true, bandera_eleccion = true, bandera_derrota = false;

    while(bandera && juego->heap->cantidad >= 0){
        if(juego->gimnasio_actual) juego->heap->destructor(juego->gimnasio_actual);
        printf("A\n");
        juego->gimnasio_actual = (gimnasio_t*)extraer_nodo_raiz(juego->heap);
        printf("B\n");
        if(bandera_derrota){
            NULL;
        }else if(!juego->gimnasio_actual && !bandera_derrota){
            imprimir_juego_ganado();
            bandera = false;
        } else{
            while(!bandera_derrota && bandera_eleccion){
                juego = menu_gimnasio(juego, &bandera_derrota, &bandera_eleccion);
            }
            bandera_eleccion = true;

            if(juego->gimnasio_actual && juego->heap->cantidad > 1) {
                bool bandera_sig_gimnasio = true;
                while(bandera_sig_gimnasio){
                    juego = menu_victoria(juego, (entrenador_t*)lista_primero(((gimnasio_t*)juego->gimnasio_actual)->v_entrenadores), &bandera_sig_gimnasio);
                }
            }
        }
    }
    return juego;
}