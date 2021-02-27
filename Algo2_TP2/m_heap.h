#ifndef __M_HEAP__
#define __M_HEAP__

#include <stddef.h>
#include <stdlib.h>

/*
 * Comparador de elementos. Recibe dos elementos del heap y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el heap
 * (heap_destruir) se invoca al destructor pasandole
 * el elemento.
 */
typedef void (*heap_destructor_elemento)(void*);

typedef struct heap{
    void** v_gimnasios;
    int cantidad;
    heap_comparador comparador;
    heap_destructor_elemento destructor;
}heap_t;

heap_t* crear_heap();

heap_t* heap_insertar_nodo(heap_t* heap, void* elemento);

void* extraer_nodo_raiz (heap_t* heap);

void heap_destruir(heap_t* heap);

#endif /* __M_HEAP__ */