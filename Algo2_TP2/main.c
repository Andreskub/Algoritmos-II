#include "aventura_pokemon.h"
#include "obtener_datos_archivo.h"
#include "logica_batallas.h"
#include "batallas.h"
#include "funciones_imprenta.h"

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
                if(!juego->personaje) imprimir_error_archivo_erroneo();
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
            imprimir_error_input();
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
