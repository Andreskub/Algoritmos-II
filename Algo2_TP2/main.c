#include "aventura_pokemon.h"
#include "obtener_datos_archivo.h"
#include "batallas.h"


/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES DE IMPRESIÓN ++++++++++++++++++++++++++++++++++++++++++++++++++ */
void imprimir_mensaje_bienvenida(){
    printf("%60s%s\n"," ","                                  ,'\\");
    printf("%60s%s\n"," ","    _.----.        ____         ,'  _\\   ___    ___     ____");
    printf("%60s%s\n"," ","_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.");
    printf("%60s%s\n"," ","\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |");
    printf("%60s%s\n"," "," \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |");
    printf("%60s%s\n"," ","   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |");
    printf("%60s%s\n"," ","    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |");
    printf("%60s%s\n"," ","     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |");
    printf("%60s%s\n"," ","      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |");
    printf("%60s%s\n"," ","       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |");
    printf("%60s%s\n"," ","        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |");
    printf("%60s%s\n"," ","                                `'                            '-._|");
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES PRINCIPALES ++++++++++++++++++++++++++++++++++++++++++++++++++ */

int main(){
    imprimir_mensaje_bienvenida();
    /*
    personaje_t* personaje = lectura_y_creacion_personaje("personaje.txt");
    if(!personaje) printf("FALLO EL PERSONAJE! (main)\n");

    if(personaje) destruir_personaje(personaje);
    */

    heap_t* heap = crear_heap(comparar_gimnasios, destruir_gimnasio);
    cargar_archivo_gimnasio("gimnasio1.txt", heap);
    heap_destruir(heap);

    return 0;
}
