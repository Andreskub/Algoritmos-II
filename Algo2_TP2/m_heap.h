#ifndef __M_HEAP__
#define __M_HEAP__

typedef struct heap{
    gimnasio_t* v_gimnasios;
    int cantidad;
}heap_t;

heap_t* crear_heap();

heap_t* insertar_nodo(heap_t* heap, gimnasio_t* gimnasio);

void heap_sort(gimnasio_t* v_gimnasio, int n);

void heap_destruir(heap_t* heap);


#endif /* __M_HEAP__ */