#include "funciones_imprenta.h"
#include "logica_batallas.h"

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES DE IMPRESIÓN ++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*
void imprimir_mensaje_bienvenida_2(){
    printf("%40s%s\n", " ","   _                  _                       ___      _                              ");
    printf("%40s%s\n", " ","  /_\__   _____ _ __ | |_ _   _ _ __ __ _    / _ \___ | | _____ _ __ ___   ___  _ __  ");
    printf("%40s%s\n", " "," //_\\\ \ / / _ \ '_ \| __| | | | '__/ _` |  / /_)/ _ \| |/ / _ \ '_ ` _ \ / _ \| '_ \ ");
    printf("%40s%s\n", " ","/  _  \ V /  __/ | | | |_| |_| | | | (_| | / ___/ (_) |   <  __/ | | | | | (_) | | | |");
    printf("%40s%s\n", " ","\_/ \_/\_/ \___|_| |_|\__|\__,_|_|  \__,_| \/    \___/|_|\_\___|_| |_| |_|\___/|_| |_|");
    printf("%40s%s\n", " ","                                                                                      ");
}*/

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
    //imprimir_mensaje_bienvenida_2();
}

void imprimir_linea(char* caracter, int multiplicador){
    for (int i = 0; i < multiplicador ; i++){
        printf("%s", caracter);
    }
}

int longitud_string(char* string){
    return strlen(string);
}



/* ++++++++++++++++++++++++++++++++++++++++++++++++++ IMPRESIÓN DE ELECCION ++++++++++++++++++++++++++++++++++++++++++++++++++ */

int pedir_letra_menu_derrota(){
    printf("Ingrese su eleccion: ");
    char eleccion;
    scanf("%s", &eleccion);

    if (eleccion == 'C' || eleccion == 'c') return C;
    else if (eleccion == 'F' || eleccion == 'f') return F;
    else if (eleccion == 'R' || eleccion == 'r') return R;
    else return ERROR;
}

int pedir_letra_menu_victoria(){
    printf("Ingrese su eleccion: ");
    char eleccion;
    scanf("%s", &eleccion);

    if (eleccion == 'C' || eleccion == 'c') return C;
    else if (eleccion == 'N' || eleccion == 'n') return N;
    else if (eleccion == 'T' || eleccion == 't') return T;
    else return ERROR;
}

int pedir_letra_menu_batalla(){
    printf("Ingrese su eleccion: ");
    char eleccion;
    scanf("%s", &eleccion);

    if (eleccion == 'N' || eleccion == 'n') return N;
    else return ERROR;
}

int pedir_letra_menu_gimnasio(){
    printf("Ingrese su eleccion: ");
    char eleccion;
    scanf("%s", &eleccion);

    if (eleccion == 'E' || eleccion == 'e') return E;
    else if (eleccion == 'B' || eleccion == 'b') return B;
    else if (eleccion == 'G' || eleccion == 'g') return G;
    else if (eleccion == 'C' || eleccion == 'c') return C;
    else return ERROR;

}

int pedir_letra_menu_inicio(){
    
    printf("Ingrese su eleccion: ");
    char eleccion;
    scanf("%s", &eleccion);

    if (eleccion == 'A' || eleccion == 'a') return A;
    else if (eleccion == 'E' || eleccion == 'e') return E;
    else if (eleccion == 'I' || eleccion == 'i') return I;
    else if (eleccion == 'S' || eleccion == 's') return S;
    return ERROR;
}

char* pedir_nombre_archivo(char array[]){
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", array);
    return array;
}

size_t pedir_posicion_pokemon(size_t* posicion){
    printf("Ingrese el numero de pokemon deseado: ");
    scanf("%li", posicion);
    return *posicion;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ IMPRESIÓN DE ESTRUCTURAS ++++++++++++++++++++++++++++++++++++++++++++++++++ */


void imprimir_pokemon_caracteristicas_aux_1(){
    printf("\n");
    imprimir_linea("-", 120);
    printf("\n| %73s %44s\n", "TABLA DE POKEMONES DEL ENTRENADOR", "|");
    imprimir_linea("-", 120);
    printf("\n| %-49s | %s  | %s  | %s  |%-28s|\n", "Especie:", "Velocidad:", "Atatque:", "Defensa:", "Victorias:");
    imprimir_linea("-", 120);
    printf("\n");
}

void imprimir_pokemon_caracteristicas_1(pokemon_t* pokemon){
    printf("| %-49s | %6i km/h | %9i | %9i | %-26i |\n", pokemon->especie, pokemon->velocidad, pokemon->ataque, pokemon->defensa, pokemon->cantidad_victorias);
}

void imprimir_entrenador_completo(entrenador_t* entrenador){
    if(!entrenador) return;
    printf("\nNombre del entrenador: %s", entrenador->nombre);
    imprimir_pokemon_caracteristicas_aux_1();
    for(int i = 0; i < entrenador->v_pokemones->cantidad; i++){
        pokemon_t* pokemon_actual = (pokemon_t*)lista_elemento_en_posicion(entrenador->v_pokemones, i);
        imprimir_pokemon_caracteristicas_1(pokemon_actual);
    }
    imprimir_linea("-", 120);
    printf("\n");
}


void imprimir_pokemon_caracteristicas_aux_2(){
    printf("\n");
    imprimir_linea("-", 120);
    printf("\n| %73s %44s\n", "TABLA DE POKEMONES DEL PERSONAJE", "|");
    imprimir_linea("-", 120);
    printf("\n| %-40s | %s | %s | %s | %s | %-25s |\n", "Especie:", "Velocidad:", "Atatque:", "Defensa:", "Victorias:", "Esta en el Party:");
    imprimir_linea("-", 120);
    printf("\n");
}

void imprimir_pokemon_caracteristicas_2(pokemon_t* pokemon, int i, char* afirmacion){
    printf("|%-3i %-37s | %5i km/h | %8i | %8i | %10i | %-25s |\n", i, pokemon->especie, pokemon->velocidad, pokemon->ataque, pokemon->defensa, pokemon->cantidad_victorias, afirmacion);
}

void imprimir_personaje_completo(personaje_t* personaje){
    printf("\nNombre del personaje: %s", personaje->nombre);
    imprimir_pokemon_caracteristicas_aux_2();
    for(int i = 0; i < personaje->cantidad_pokemones; i++){
        void* pokemon = lista_elemento_en_posicion(personaje->pokemon_obtenidos, i);
        bool afirmacion = pokemon_esta_en_pokemones_para_combatir(personaje, 6, pokemon);
        if(afirmacion) imprimir_pokemon_caracteristicas_2((pokemon_t*)pokemon, i+1, "Si");
        else imprimir_pokemon_caracteristicas_2((pokemon_t*)pokemon, i+1, "No");
    }
    imprimir_linea("-", 120);
    printf("\n");
}

void imprimir_batalla_y_resultado(pokemon_t* pkm_1, pokemon_t* pkm_2, int ganador){
    printf("\n%-18s%7s%-22s%7s%-22s\n", " Caracteristicas", " ", "  Pokemon personaje", " ", "Pokemon entrenador");
    imprimir_linea("-",18);
    printf("%7s"," ");
    imprimir_linea("-",22);
    printf("%5s"," ");
    imprimir_linea("-",22);
    printf("\n| %-15s|%7s|%-20s|%5s|%-20s|","Especie:", " ", pkm_1->especie, " ", pkm_2->especie);
    printf("\n| %-15s|%7s|%-20i|%5s|%-20i|", "Velocidad:", " ", pkm_1->velocidad, " ", pkm_2->velocidad);
    printf("\n| %-15s|%7s|%-20i|%5s|%-20i|", "Ataque:", " ", pkm_1->ataque, "vs  ", pkm_2->ataque);
    printf("\n| %-15s|%7s|%-20i|%5s|%-20i|", "Defensa:", " ", pkm_1->defensa, " ", pkm_2->defensa);
    printf("\n| %-15s|%7s|%-20i|%5s|%-20i|\n", "Victorias:", " ", pkm_1->cantidad_victorias, " ", pkm_2->cantidad_victorias);
    imprimir_linea("-",18);
    printf("%7s"," ");
    imprimir_linea("-",22);
    printf("%5s"," ");
    imprimir_linea("-",22);
    printf("\n");

}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ IMPRESIÓN DE MENUS ++++++++++++++++++++++++++++++++++++++++++++++++++ */

void imprimir_menu_inicio(){
    printf("\n");
    imprimir_linea("=", 18);
    printf("%s"," MENU DE INICIO ");
    imprimir_linea("=", 18);
    printf("\n|%-50s|\n|%-50s|\n|%-50s|\n|%-50s|\n", "E - Ingresar archivo del entrenador principal", "A - Agregar gimnasio","I - Comenzar partida","S - Simular partida");
    imprimir_linea("=", 52);
    printf("\n");
}

void imprimir_menu_gimnasio(){
    printf("\n");
    imprimir_linea("=", 18);
    printf("%s"," MENU GIMNASIO ");
    imprimir_linea("=", 19);
    printf("\n|%-50s|\n|%-50s|\n|%-50s|\n|%-50s|\n", "E - Mostrar entrenador", "G - Mostrar informacion del gimnasio","C - Modificar pokemones de combate","B - Realizar proxima batalla");
    imprimir_linea("=", 52);
    printf("\n");
}

void imprimir_menu_batalla(){
    printf("\n");
    imprimir_linea("=", 19);
    printf("%s"," MENU BATALLA ");
    imprimir_linea("=", 19);
    printf("\n|%-50s|\n","N - Proximo combate");
    imprimir_linea("=", 52);
    printf("\n");
}

void imprimir_menu_victoria(){
    printf("\n== MENU VICTORIA ==\n");
    printf("T - Tomar un pokemon del lider\nC - Modificar pokemones de combate\nN - Proximo gimnasio\n");
}

void imprimir_menu_derrota(){
    printf("\n== MENU DERROTA ==\n");
    printf("C - Modificar pokemones de combate\nR - Reintentar gimnasio\nF - Finalizar partida\n");
}



/* ++++++++++++++++++++++++++++++++++++++++++++++++++ IMPRESIÓN DE ERRORES ++++++++++++++++++++++++++++++++++++++++++++++++++ */
void imprimir_error_general(){
    printf("\n¡ERROR: FALLO EL SISTEMA!\n\n");
}

void imprimir_error_input(){
    printf("\n¡ERROR: LA OPCION SELECCIONADA ES INCORRECTA!\n\n");
}

void imprimir_error_inexistencia_personaje(){
    printf("\n¡ERROR: YA HAY UN JUGADOR EXISTENTE!\n\n");
}

void imprimir_error_inexistencia_heap(){
    printf("\n¡ERROR: NO EXISTE EL HEAP!\n");
}

void imprimir_error_comiezo_partida(){
    printf("\n¡ERROR: NO SE ENCONTRO UN PERSONAJE Y/O GIMNASIO EXISTENTE!\n\n");
}