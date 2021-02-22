#ifndef __M_HEAP__
#define __M_HEAP__

typedef void (*destructor_elemento)(void*);

typedef struct heap{
    void* v_gimnasios;
    int cantidad;
    destructor_elemento destructor;
}heap_t;

heap_t* crear_heap();

heap_t* insertar_nodo(heap_t* heap, void* elemento);

void heap_sort(void* v_gimnasio, int n);

void heap_destruir(heap_t* heap);


#endif /* __M_HEAP__ */