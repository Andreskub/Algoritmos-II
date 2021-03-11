#include "funciones_imprenta.h"

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
    printf("|%-50s |%5i km/h  | %5i | %5i |%5i |\n", pokemon->especie, pokemon->velocidad, pokemon->ataque, pokemon->defensa, pokemon->cantidad_victorias);
}

void imprimir_entrenador_completo(entrenador_t* entrenador){
    if(!entrenador) return;
    //imprimir_pokemon_caracteristicas_aux();
    for(int i = 0; i < entrenador->v_pokemones->cantidad; i++){
        pokemon_t* pokemon_actual = (pokemon_t*)lista_elemento_en_posicion(entrenador->v_pokemones, i);
        imprimir_pokemon_caracteristicas(pokemon_actual);
    }
}

void imprimir_menu_inicio(){
    printf("\n== MENU DE INICIO ==\n");
    printf("E - Ingresar archivo del entrenador principal\nA - Agregar gimnasio\nI - Comenzar partida\nS - Simular partida\n\n");
}

void imprimir_menu_gimnasio(){
    
    printf("E - Mostrar entrenador\nG - Mostrar informacion del gimnasio\nC - Modificar pokemones de combate\nB - Realizar proxima batalla\n\n");
}

void imprimir_menu_batalla(){
    printf("\n== MENU DEL BATALLA ==\n");
    printf("N - Proximo combate\n");
}

void imprimir_menu_victoria(){
    printf("\n== MENU VICTORIA ==\n");
    printf("T - Tomar un pokemon del lider\nC - Modificar pokemones de combate\nN - Proximo gimnasio\n\n");
}

void imprimir_menu_derrota(){
    printf("\n== MENU DERROTA ==\n");
    printf("C - Modificar pokemones de combate\nR - Reintentar gimnasio\nF - Finalizar partida\n\n");
}

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

size_t pedir_posicion_pokemon(size_t* posicion){
    printf("Ingrese el numero de pokemon deseado: ");
    scanf("%li", posicion);
    return *posicion;
}