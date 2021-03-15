#include "funciones_imprenta.h"
#include "logica_batallas.h"
#include "m_lista.h"

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

void imprimir_mensaje_despedida(){
    printf("\n       ,___          .-;' \n");
    printf("       `'-.`\\_...._/`.`    \n");
    printf("    ,      \\        /      \n");
    printf(" .-' ',    / ()   ()\\       ,d88b.d88b,\n");
    printf("`'._   \\  /()    .  (|      88888888888\n");
    printf("    > .' ;,     -'-  /      `Y8888888Y'\n");
    printf("   / <   |;,     __.;         `Y888Y'\n");
    printf("   '-.'-.|  , \\    , \\          `Y'\n");
    printf("      `>.|;, \\_)    \\_)   \n");
    printf("       `-;     ,    /       \n");
    printf("          \\    /   <       \n");
    printf("           '. <`'-,_)       \n");
    printf("        bye '._)            \n\n");
}


void imprimir_juego_ganado(){
    printf("\n== GANASTE EL JUEGOO!!!! :) ==\n");
}

void imprimir_linea(char* caracter, int multiplicador){
    for (int i = 0; i < multiplicador ; i++){
        printf("%s", caracter);
    }
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
    else if (eleccion == 'F' || eleccion == 'f') return F;
    return ERROR;
}

char* pedir_nombre_archivo(char array[]){
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", array);
    return array;
}

size_t pedir_posicion_pokemon(size_t* posicion){
    printf("Ingrese el numero de pokemon deseado: ");
    scanf("%li", (long int *)posicion);
    return *posicion;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ IMPRESIÓN DE ESTRUCTURAS ++++++++++++++++++++++++++++++++++++++++++++++++++ */
void imprimir_pokemon_caracteristicas_aux_1(entrenador_t* entrenador){
    printf("\n");
    imprimir_linea("-", 120);
    printf("\n| %s%-82s|\n", "TABLA DE POKEMONES DEL ENTRENADOR: ", entrenador->nombre);
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
    imprimir_pokemon_caracteristicas_aux_1(entrenador);
    for(int i = 0; i < entrenador->v_pokemones->cantidad; i++){
        pokemon_t* pokemon_actual = (pokemon_t*)lista_elemento_en_posicion(entrenador->v_pokemones, (size_t)i);
        imprimir_pokemon_caracteristicas_1(pokemon_actual);
    }
    imprimir_linea("-", 120);
    printf("\n");
}

void imprimir_pokemon_caracteristicas_aux_2(personaje_t* personaje){
    printf("\n");
    imprimir_linea("-", 120);
    printf("\n| %s%-83s|\n", "TABLA DE POKEMONES DEL PERSONAJE: ", personaje->nombre);
    imprimir_linea("-", 120);
    printf("\n| %-40s | %s | %s | %s | %s | %-25s |\n", "Especie:", "Velocidad:", "Atatque:", "Defensa:", "Victorias:", "Esta en el Party:");
    imprimir_linea("-", 120);
    printf("\n");
}

void imprimir_pokemon_caracteristicas_2(pokemon_t* pokemon, int i, char* afirmacion){
    printf("|%-3i %-37s | %5i km/h | %8i | %8i | %10i | %-25s |\n", i, pokemon->especie, pokemon->velocidad, pokemon->ataque, pokemon->defensa, pokemon->cantidad_victorias, afirmacion);
}

void imprimir_personaje_completo(personaje_t* personaje){
    imprimir_pokemon_caracteristicas_aux_2(personaje);
    for(int i = 0; i < personaje->pokemon_obtenidos->cantidad; i++){
        void* pokemon = lista_elemento_en_posicion(personaje->pokemon_obtenidos, (size_t)i);
        bool afirmacion = pokemon_esta_en_pokemones_para_combatir(personaje, 6, pokemon);
        if(afirmacion) imprimir_pokemon_caracteristicas_2((pokemon_t*)pokemon, i+1, "Si");
        else imprimir_pokemon_caracteristicas_2((pokemon_t*)pokemon, i+1, "No");
    }
    imprimir_linea("-", 120);
    printf("\n");
}

void imprimir_gimnasio_completo(gimnasio_t* gimnasio){
    printf("\nInformacion del gimnasio %s\n", gimnasio->nombre);
    for(int i = 0; i < gimnasio->v_entrenadores->cantidad; i++){
        imprimir_entrenador_completo((entrenador_t*)lista_elemento_en_posicion(gimnasio->v_entrenadores, (size_t)i));
    }
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
    printf("\n%48s", " ");
    imprimir_linea("=", 18);
    printf("%s"," MENU DE INICIO ");
    imprimir_linea("=", 18);
    printf("\n%48s|%-50s|\n%48s|%-50s|\n%48s|%-50s|\n%48s|%-50s|\n%48s|%-50s|\n%48s", " ", "E - Ingresar archivo del entrenador principal", " ", "A - Agregar gimnasio", " ", "I - Comenzar partida", " ", "S - Simular partida", " ", "F - Finalizar programa", " ");
    imprimir_linea("=", 52);
    printf("\n");
}

void imprimir_menu_gimnasio(){
    printf("\n%48s", " ");
    imprimir_linea("=", 18);
    printf("%s"," MENU GIMNASIO ");
    imprimir_linea("=", 19);
    printf("\n%48s|%-50s|\n%48s|%-50s|\n%48s|%-50s|\n%48s|%-50s|\n%48s", " ", "E - Mostrar entrenador", " ", "G - Mostrar informacion del gimnasio", " ", "C - Modificar pokemones de combate", " ", "B - Realizar proxima batalla", " ");
    imprimir_linea("=", 52);
    printf("\n");
}

void imprimir_menu_batalla(){
    printf("\n%48s", " ");
    imprimir_linea("=", 19);
    printf("%s"," MENU BATALLA ");
    imprimir_linea("=", 19);
    printf("\n%48s|%-50s|\n%48s", " ", "N - Proximo combate", " ");
    imprimir_linea("=", 52);
    printf("\n");
}

void imprimir_menu_victoria(){
    printf("\n%48s", " ");
    imprimir_linea("=", 18);
    printf("%s"," MENU VICTORIA ");
    imprimir_linea("=", 19);
    printf("\n%48s|%-50s|\n%48s|%-50s|\n%48s|%-50s|\n%48s", " ", "T - Tomar un pokemon del lider", " ", "C - Modificar pokemones de combate", " ", "N - Proximo gimnasio", " ");
    imprimir_linea("=", 52);
    printf("\n");
}

void imprimir_menu_derrota(){
    printf("\n%48s", " ");
    imprimir_linea("=", 19);
    printf("%s"," MENU DERROTA ");
    imprimir_linea("=", 19);
    printf("\n%48s|%-50s|\n%48s|%-50s|\n%48s|%-50s|\n%48s", " ", "C - Modificar pokemones de combate", " ", "R - Reintentar gimnasio", " ", "F - Finalizar partida", " ");
    imprimir_linea("=", 52);
    printf("\n");
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ IMPRESIÓN DE ERRORES ++++++++++++++++++++++++++++++++++++++++++++++++++ */
void imprimir_error_general(){
    printf("\n== ¡ERROR: FALLO EL SISTEMA! ==\n\n");
}

void imprimir_error_input(){
    printf("\n== ¡ERROR: LA OPCION SELECCIONADA ES INCORRECTA! ==\n");
}

void imprimir_error_doble_seleccionado(){
    printf("\n== ¡ERROR: EL POKEMON YA HA SIDO SELECCIONADO ANTERIORMENTE! ==\n");
}

void imprimir_error_archivo_erroneo(){
    printf("\n== ¡ERROR: EL ARCHIVO INGRESADO ES INCORRECTO! ==\n");
}

void imprimir_error_inexistencia_personaje(){
    printf("\n== ¡ERROR: YA HAY UN JUGADOR EXISTENTE! ==\n");
}

void imprimir_error_inexistencia_heap(){
    printf("\n== ¡ERROR: NO EXISTE EL HEAP! ==\n");
}

void imprimir_error_comiezo_partida(){
    printf("\n== ¡ERROR: NO SE ENCONTRO UN PERSONAJE Y/O GIMNASIO EXISTENTE! ==\n");
}