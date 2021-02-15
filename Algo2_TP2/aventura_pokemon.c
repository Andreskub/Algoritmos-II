#include "aventura_pokemon.h"

#include <stdlib.h>

#define FORMATO_PRELECTURA "%1[^;]"
#define FORMATO_LECTURA_GIMANSIO "%100[^;];%i;%i\n"
#define FORMATO_LECTURA_ENTRENADOR "%50[^\n]\n"
#define FORMATO_LECTURA_POKEMON "%100[^;];%i;%i;%i\n"

#define Gimnasio "G"
#define Entrenador "E"
#define Lider "L"
#define Pokémon "P"

gimnasio_t* crear_gimnasio(FILE* info_gimnasio){
    
    gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t));
    if(!gimnasio) return NULL;

    int leer_linea = fscanf(info_gimnasio, FORMATO_LECTURA_GIMANSIO, gimnasio.nombre, &(gimnasio).dificultad, &(gimnasio).id_puntero_funcion);
    if(leer_linea != 3) return NULL;

    return gimnasio;
}

entrenador_t* crear_entrenador(){

    entrenador_t* entrenador = calloc(1, sizeof(entrenador_t));
    if(!entrenador) return NULL;

    return entrenador;
}

pokemon_t* crear_pokemon();

void leer_comienzo_linea(FILE* info_gimnasio, char expresion){
    
    switch (expresion){
        case Gimnasio:
            gimnasio_t* gimnasio = crear_gimnasio(info_gimnasio);

            break;
        case Lider:

            break;
        case Entrenador:

            break;
        case Pokémon:

            break;
        default:
            break;
    }
}

void cargar_archivo(const char* ruta_archio, heap_t* heap){

    FILE* info_gimnasio = fopen(ruta_archivo,"r");
    if(!info_gimnasio) return NULL;

    char comienzo_linea;
    int leer_prelinea = fscanf(info_gimnasio, FORMATO_PRELECTURA, comienzo_linea);

    if(leer_prelinea != 1){
        fclose(info_gimnasio);
        return NULL;
    }

    while (leer_prelinea == 1){
        leer_comienzo_linea(comienzo_linea);

        leer_prelinea = fscanf(info_gimnasio, FORMATO_PRELECTURA, comienzo_linea);
    }

    fclose(info_gimnasio);
}
