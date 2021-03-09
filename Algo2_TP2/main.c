#include "aventura_pokemon.h"
#include "obtener_datos_archivo.h"
#include "batallas.h"

#define None 0
#define A 1
#define B 2
#define C 3
#define E 4
#define F 5
#define G 6
#define I 7
#define N 8
#define R 9
#define S 10
#define T 11


/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES DE IMPRESIÓN ++++++++++++++++++++++++++++++++++++++++++++++++++ */
void imprimir_mensaje_bienvenida(){
    printf("%40s%s\n"," ","                                  ,'\\");
    printf("%40s%s\n"," ","    _.----.        ____         ,'  _\\   ___    ___     ____");
    printf("%40s%s\n"," ","_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.");
    printf("%40s%s\n"," ","\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |");
    printf("%40s%s\n"," "," \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |");
    printf("%40s%s\n"," ","   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |");
    printf("%40s%s\n"," ","    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |");
    printf("%40s%s\n"," ","     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |");
    printf("%40s%s\n"," ","      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |");
    printf("%40s%s\n"," ","       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |");
    printf("%40s%s\n"," ","        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |");
    printf("%40s%s\n"," ","                                `'                            '-._|");
}

void imprimir_linea(char* caracter, int multiplicador){
    for (int i = 0; i < multiplicador ; i++){
        printf("%s", caracter);
    }
}
/*Revisar
void imprimir_pokemon_caracteristicas_aux(){
    printf("\n\n");
    imprimir_linea("-", 178);
    printf("\n| %103s %72s\n", "TABLA DE POKEMONES EN EL ARRECIFE", "|");
    imprimir_linea("-", 178);
    printf("\n|%-100s |%5s  |%5s    | %-50s|\n", "Especie:", "Velocidad:", "Peso:", "color:");
    imprimir_linea("-", 178);
}
*/
void imprimir_pokemon_caracteristicas(pokemon_t* pokemon){
    printf("|%-100s |%5i km/h  | %5i | %5i |%5i |\n", pokemon->especie, pokemon->velocidad, pokemon->ataque, pokemon->defensa, pokemon->cantidad_victorias);
}

void imprimir_entrenador_completo(entrenador_t* entrenador){
    if(!entrenador) return;
    //imprimir_pokemon_caracteristicas_aux();
    for(int i = 0; i < entrenador->cantidad_pokemones; i++){
        pokemon_t* pokemon_actual = (pokemon_t*)lista_elemento_en_posicion(entrenador->v_pokemones, i);
        imprimir_pokemon_caracteristicas(pokemon_actual);
    }
}

void imprimir_menu_gimnasio(){
    printf("\n== MENU DEL GIMNASIO ==\n");
    printf("Escriba la letra correspondiente a su eleccion:\n");
    printf("E - Mostrar entrenador\nG - Mostrar informacion del gimnasio\nC - Modificar pokemones de combate\nB - Realizar proxima batalla\n\n");
}

void imprimir_menu_inicio(){
    printf("\n== MENU DE INICIO ==\n");
    printf("Escriba la letra correspondiente a su eleccion:\n");
    printf("E - Ingresar archivo del entrenador principal\nA - Agregar gimnasio\nI - Comenzar partida\nS - Simular partida\n\n");
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES PRINCIPALES ++++++++++++++++++++++++++++++++++++++++++++++++++ */

int pedir_letra(){
    
    printf("Ingrese su eleccion: ");
    char eleccion;
    scanf("%s", &eleccion);
    //fgets(&eleccion, 1, stdin);

    //if (eleccion == 0x0A || eleccion == '\n') return None;
    if (eleccion == 'A' || eleccion == 'a') return A;
    else if (eleccion == 'B' || eleccion == 'b') return B;
    else if (eleccion == 'C' || eleccion == 'c') return C;
    else if (eleccion == 'E' || eleccion == 'e') return E;
    else if (eleccion == 'F' || eleccion == 'f') return F;
    else if (eleccion == 'G' || eleccion == 'g') return G;
    else if (eleccion == 'I' || eleccion == 'i') return I;
    else if (eleccion == 'N' || eleccion == 'n') return N;
    else if (eleccion == 'R' || eleccion == 'r') return R;
    else if (eleccion == 'S' || eleccion == 's') return S;
    else if (eleccion == 'T' || eleccion == 't') return T;
    return ERROR;
}

char* pedir_nombre_archivo(char array[]){
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", array);
    return array;
}

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
