#include "evento_pesca.h"

#include <stdio.h>
#include <string.h>

/*+++++++++++++++++++++++++ FORMATOS DE IMPRESION +++++++++++++++++++++++++*/

void mensaje_bienvenida(){
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

void mensaje_despedida(){
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

void imprimir_linea(char* caracter, int multiplicador){
    for (int i = 0; i < multiplicador ; i++){
        printf("%s", caracter);
    }
}

void imprimir_error_traslado(){
    printf("\n\n%54s", "-");
    imprimir_linea("-", 64);
    printf("\n%54s%58s%6s\n%118s\n","|","ERROR: NO SE PUDO REALIZAR EL TRASLDAO DE POKEMONES!","|","| (verifique que el pokemon este en el arrecife y la cantidad)  |");
    printf("%54s", "-");
    imprimir_linea("-", 64);
}

void imprimir_pretabla_1(){
    printf("\n\n");
    imprimir_linea("-", 178);
    printf("\n| %103s %72s\n", "TABLA DE POKEMONES EN EL ARRECIFE", "|");
    imprimir_linea("-", 178);
    printf("\n|%-100s |%5s  |%5s    | %-50s|\n", "Especie:", "Velocidad:", "Peso:", "color:");
    imprimir_linea("-", 178);
}

void imprimir_pokemones_tabla_1(pokemon_t* pokemon){
    printf("|%-100s |%5i km/h  |%5i kg | %-50s|\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color );
}

void imprimir_pretabla_2(){
    printf("\n\n\n");
    imprimir_linea("-", 49);
    printf("\n|%39s%9s\n", "TABLA DE POKEMONES EN EL ARRECIFE", "|");
    imprimir_linea("-", 49);
}
void imprimir_pokemones_tabla_2(pokemon_t* pokemon){
    //imprimir_linea(30);
    printf("\n\nPokemon\n");
    imprimir_linea("-", 49);
    printf("\nEspecie %40s\nVelocidad %38i\nPeso %43i\nColor %42s\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
}

void imprimir_pokemones_tabla_3(pokemon_t* pokemon){
    imprimir_linea("-", 49);
    printf("\n|%-47s|\n", pokemon->especie);
    printf("|%-3i km/h%40s\n", pokemon->velocidad, "|");
    printf("|%-3i kg%42s\n", pokemon->peso, "|");
    printf("|%-47s|\n", pokemon->color);
}

void imprimir_pokemones_tabla_4(pokemon_t* pokemon){
    printf("\n--> %-33s", pokemon->especie);
    printf("--> %i km/h\n", pokemon->velocidad);
    printf("%40s %i kg\n","-->", pokemon->peso);
    printf("%40s %s\n", "-->", pokemon->color);
    NULL;
}

void imprimir_pokemones_tabla_5(pokemon_t* pokemon){
    printf("\ntypedef struct pokemon{\n");
    printf("    char especie = '%s';\n", pokemon->especie);
    printf("    int velocidad = %i;\n", pokemon->velocidad);
    printf("    int peso = %i;\n", pokemon->peso);
    printf("    char color = '%s';\n", pokemon->color);
    printf("}pokemon_t;\n\n");
}

/*+++++++++++++++++++++++++ CONDICIONES PARA EL POKEMON +++++++++++++++++++++++++*/

//Funcion que dado un pokemon, verifica si cumple con lo pedido
//INPUT: struct puntero pokemon/OUTPUT: bool
bool pokemon_bokita(pokemon_t* pokemon){
  return (strcmp(pokemon->color, "azulyoro") == 0);
}

//Funcion que dado un pokemon, verifica si cumple con lo pedido
//INPUT: struct puntero pokemon/OUTPUT: bool
bool pokemon_rapidito(pokemon_t* pokemon){
    if (pokemon->velocidad >= 20 && pokemon->peso <= 7){
        return true;
    } else {
        return false;
    }
}

//Funcion que dado un pokemon, verifica si cumple con lo pedido
//INPUT: struct puntero pokemon/OUTPUT: bool
bool pokemon_supremo(pokemon_t* pokemon){
    if (pokemon->velocidad >= 30 && strcmp(pokemon->color, "dorado") == 0){
        return true;
    } else {
        return false;
    }
}

//Funcion que dado un pokemon, verifica si cumple con lo pedido
//INPUT: struct puntero pokemon/OUTPUT: bool
bool pokemon_innombrable(pokemon_t* pokemon){
    //Inicializa contadores
    int contador = 0;
    int contador_a = 0;
    //Recorre el char especie
    while(contador < strlen(pokemon->especie)){
        if(pokemon->especie[contador] == 'a') { 
            contador_a++;
        } else if ( pokemon->especie[contador] == 'A'){
            contador_a++;
        }
        contador++;
    }
    //condicion de retorno
    if (contador_a >= 5 && contador >= 30){
        return true;
    } else {
        return false;
    }
}

//Funcion que dado un pokemon, verifica si cumple con lo pedido
//INPUT: struct puntero pokemon/OUTPUT: bool
bool pokemon_front_line(pokemon_t* pokemon){
    if (pokemon->velocidad <= 5 && pokemon->peso > 25){
        return true;
    } else {
        return false;
    }
}

/*+++++++++++++++++++++++++ RELACIONADO AL MAIN +++++++++++++++++++++++++*/

void revisar_free_estructuras(arrecife_t* arrecife, acuario_t* acuario){
    if (acuario)
        liberar_acuario(acuario);
    if (arrecife)
        liberar_arrecife(arrecife);
}

//Funcion que alterna los 5 casos
//INPUT:struct pointer arrecife; struct pointer acuario; entero/OUTPUT:None
void realizar_caso(arrecife_t* arrecife, acuario_t* acuario, int opcion){
    //Inicializo variable donde guardo error
    int vuelto = 0;

    switch(opcion){
        case 1:
            imprimir_pretabla_1();
            censar_arrecife(arrecife, imprimir_pokemones_tabla_1);
            imprimir_linea("-", 178);
            //Realizo traslado
            vuelto = trasladar_pokemon(arrecife, acuario, pokemon_bokita , 3);
            break;
        case 2:
            imprimir_pretabla_2();
            censar_arrecife(arrecife, imprimir_pokemones_tabla_2);
            //Realizo traslado
            vuelto = trasladar_pokemon(arrecife, acuario, pokemon_rapidito , 3);
            break;
        case 3:
            imprimir_pretabla_2();
            censar_arrecife(arrecife, imprimir_pokemones_tabla_3);
            imprimir_linea("-", 49);
            //Realizo traslado
            vuelto = trasladar_pokemon(arrecife, acuario, pokemon_supremo, 2);
            break;
        case 4:
        //Imprimo los pokemones actuales en el arrecife
            imprimir_pretabla_2();
            censar_arrecife(arrecife, imprimir_pokemones_tabla_4);
            //Realizo traslado
            vuelto = trasladar_pokemon(arrecife, acuario, pokemon_innombrable, 1);
            break;
        case 5:
            //Imprimo los pokemones actuales en el arrecife
            imprimir_pretabla_2();
            censar_arrecife(arrecife, imprimir_pokemones_tabla_5);
            //Realizo traslado
            vuelto = trasladar_pokemon(arrecife, acuario, pokemon_front_line, 2);
            break;
    }

    //Compruebo que el traslado halla salido todo OK, sino devuelvo error
    if (vuelto == -1)
        imprimir_error_traslado();
        
}

//Funcion principal del programa
//INPUT: user /OUTPUT: entero
int main(int argc, char **argv){ 

    //Creo el arrecife con la informacion del archivo
    arrecife_t* arrecife = crear_arrecife(argv[1]);

    if (!arrecife)
        return 0;

    //Creo un acuario vacio
    acuario_t* acuario = crear_acuario();
    
    if(!acuario){
        revisar_free_estructuras(arrecife, acuario);
        return 0;
    }


    //Imprimo mensaje de bienvenida
    mensaje_bienvenida();
    //Recorro los 5 casos pedidos y aplico una condicion de corte
    int contador_caso = 1;
    while (contador_caso <= 5 && arrecife){
        //Realizo el n caso
        realizar_caso(arrecife, acuario, contador_caso);
        //Incremento en 1 el contador
        contador_caso++;

    }

    //Si existe el acuario, lo guarda en un .txt
    if(acuario)
        guardar_datos_acuario(acuario, argv[2]);

    //Verifica si no se liberaron las estructuras y las libera
    revisar_free_estructuras(arrecife, acuario);

    //Mensaje de despedida
    mensaje_despedida();

    return 0;
}