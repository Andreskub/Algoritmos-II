#ifndef __OBTENER_DATOS_ARCHIVO__
#define __OBTENER_DATOS_ARCHIVO__

#include "m_heap.h"
#include "m_lista.h"
#include "aventura_pokemon.h"

#define Gimnasio 1
#define Lider 2
#define Entrenador 3
#define Pokemon 4

#define FORMATO_PRELECTURA "%[^;];"
#define FORMATO_LECTURA_GIMANSIO "%100[^;];%i;%i\n"
#define FORMATO_LECTURA_ENTRENADOR "%50[^\n]\n"
#define FORMATO_LECTURA_POKEMON "%100[^;];%i;%i;%i\n"


int cargar_archivo(const char* ruta_archivo, heap_t* heap);

#endif /* __OBTENER_DATOS_ARCHIVO__ */