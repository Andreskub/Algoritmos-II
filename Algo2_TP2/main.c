#include "aventura_pokemon.h"
#include "obtener_datos_archivo.h"
#include "logica_batallas.h"
#include "batallas.h"
#include "funciones_imprenta.h"

void menu_gimnasio(gimnasio_t* gimnasio){
    if(!gimnasio) return;

    imprimir_menu_gimnasio();
    int eleccion_usuario = pedir_letra();

    switch (eleccion_usuario){
        case E:
            //Ejemplo: imprimir_entrenador_completo((entrenador_t*)gimnasio->v_entrenadores->nodo_inicio->elemento);
            break;
        case G:
            break;
        case C:
            break;
        case B:
            break;        
        default:
            break;
    }
}

juego_t* menu_inicio(juego_t* juego, bool* bandera_juego){
    if(!juego) return NULL;

    imprimir_menu_inicio();
    int eleccion_usuario = pedir_letra();
    char array[MAX_NOMBRE];
    
    switch (eleccion_usuario){
        case E:
            if(!juego->personaje) {
                juego->personaje = lectura_y_creacion_personaje(pedir_nombre_archivo(array));
                if(!juego->personaje) printf("\nOCURRIO UN ERROR!\n");
            }else printf("\n¡ERROR: YA HAY UN JUGADOR EXISTENTE!\n\n");
            break;
        case A:
            if(juego->heap) juego->heap = leer_y_cargar_gimnasio(pedir_nombre_archivo(array), juego->heap);
            else printf("\n¡ERROR: NO EXISTE EL HEAP!\n");
            break;
        case I:
            if(juego->personaje && juego->heap->v_gimnasios) {
                juego = logica_partida(juego);
            }else printf("\n¡ERROR: NO SE ENCONTRO UN PERSONAJE Y/O GIMNASIO EXISTENTE!\n\n");
            break;
        case S:
            break;
        /*case None:
            //Mensaje Despedida
            (*bandera_juego) = false;
            break;*/
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

    bool bandera_juego = true;
    while(bandera_juego){
        partida = menu_inicio(partida, &bandera_juego);
    }

    if(partida) destruir_juego(partida);
    return 0;
}
