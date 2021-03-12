#include "aventura_pokemon.h"
#include "obtener_datos_archivo.h"
#include "logica_batallas.h"
#include "batallas.h"
#include "funciones_imprenta.h"

/*
juego_t* jugar_partida_en_gimnasio(juego_t* juego, bool* bandera_derrota){

    int i = 1;
    while(!(*bandera_derrota) && i <= ((gimnasio_t*)juego->gimnasio_actual)->cont_entrenadores){
        
        entrenador_t* entrenador_actual = (entrenador_t*)lista_elemento_en_posicion(((gimnasio_t*)juego->gimnasio_actual)->v_entrenadores, ((gimnasio_t*)juego->gimnasio_actual)->cont_entrenadores -i);
        juego = logica_partida_en_batalla(juego, entrenador_actual, ((gimnasio_t*)juego->gimnasio_actual)->id_puntero_funcion, bandera_derrota);
        
        //if(!(*bandera_derrota) && (((gimnasio_t*)juego->gimnasio_actual)->v_entrenadores->cantidad -i) == 0){
        //    juego = tomar_pokemon_prestado(juego, entrenador_actual); //Preguntar si quiere guardarse uno de sus pokemones
        //}
        i++;
    }

    return juego;
}


juego_t* menu_gimnasio(juego_t* juego, bool* bandera_derrota){
    imprimir_menu_gimnasio();
    int eleccion_usuario = pedir_letra_menu_gimnasio();

    switch (eleccion_usuario){
        case E:
            imprimir_personaje_completo(juego->personaje);
            break;
        case G:
            //Mostrar info del gimnasio
            break;
        case C:
            //Cambiar personajes pokemon batalla
            break;
        case B:
            juego = jugar_partida_en_gimnasio(juego, bandera_derrota);
            //Realizar proxima batalla
            break;        
        default:
            break;
    }

    return juego;
}

juego_t* jugar_partida(juego_t* juego, bool* bandera_interaccion){


    bool bandera = true, bandera_derrota = false;
    while(bandera && juego->heap->cantidad >= 0){  
        if(juego->gimnasio_actual) juego->heap->destructor(juego->gimnasio_actual);
        juego->gimnasio_actual = (gimnasio_t*)extraer_nodo_raiz(juego->heap);
        
        juego = menu_gimnasio(juego);
        
        if(!juego->gimnasio_actual) {
            printf("\nGANASTEEEEE WACHIN!\n\n");
            bandera = false;
        } else juego = menu_gimnasio(juego, &bandera_derrota);
    }
    
    return juego;
}*/

juego_t* menu_inicio(juego_t* juego, bool* bandera_juego){
    if(!juego) return NULL;

    imprimir_menu_inicio();
    int eleccion_usuario = pedir_letra_menu_inicio();
    bool bandera_interaccion_usuario = true;
    char array[MAX_NOMBRE];
    
    switch (eleccion_usuario){
        case E:
            if(!juego->personaje) {
                juego->personaje = lectura_y_creacion_personaje(pedir_nombre_archivo(array));
                if(!juego->personaje) printf("\nOCURRIO UN ERROR!\n");
            }else imprimir_error_inexistencia_personaje();
            break;
        case A:
            if(juego->heap) juego->heap = leer_y_cargar_gimnasio(pedir_nombre_archivo(array), juego->heap);
            else imprimir_error_inexistencia_heap();
            break;
        case I:
            if(juego->personaje && juego->heap->v_gimnasios) {
                bandera_interaccion_usuario = true;
                juego = jugar_partida(juego, &bandera_interaccion_usuario);
            }else imprimir_error_comiezo_partida();
            break;
        case S:
            if(juego->personaje && juego->heap->v_gimnasios)
                bandera_interaccion_usuario = false;
            break;
        default:
            (*bandera_juego) = false;
            printf("\n¡ERROR: LA OPCION INGRESADA ES INCORRECTA!\n");
            break;
    }
    
    return juego;
}



int main(){
    imprimir_mensaje_bienvenida();
    
    juego_t* partida = crear_juego();
    if(!partida) imprimir_error_general();

    bool bandera_juego = true;
    while(bandera_juego){
        partida = menu_inicio(partida, &bandera_juego);
    }
    

    if(partida) destruir_juego(partida);


    return 0;
}
