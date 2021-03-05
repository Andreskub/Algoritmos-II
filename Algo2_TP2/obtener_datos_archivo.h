#ifndef __OBTENER_DATOS_ARCHIVO__
#define __OBTENER_DATOS_ARCHIVO__

#include "aventura_pokemon.h"
#include "m_heap.h"
#include "m_lista.h"


#define Gimnasio 1
#define Lider 2
#define Entrenador 3
#define Pokemon 4

#define FORMATO_PRELECTURA "%[^;];"
#define FORMATO_LECTURA_GIMANSIO "%100[^;];%i;%i\n"
#define FORMATO_LECTURA_ENTRENADOR "%[^\n]\n"
#define FORMATO_LECTURA_POKEMON "%99[^;];%i;%i;%i\n"


int cargar_archivo_gimnasio(const char* ruta_archivo, heap_t* heap);

personaje_t* lectura_y_creacion_personaje(const char* ruta_archivo);

#endif /* __OBTENER_DATOS_ARCHIVO__ */