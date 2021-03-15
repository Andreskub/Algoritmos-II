#include "m_heap.h"
#include <stdio.h>
/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES AUXILIARES ++++++++++++++++++++++++++++++++++++++++++++++++++ */
int posicion_padre(int n){
    return (n-1)/2;
}

int posicion_hijo_derecho(int n){
    return 2*n+2;
}

int posicion_hijo_izquierdo(int n){
    return 2*n+1;
}

void swap(void** vector, int i, int j){
    void* aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;
}

void shift_up(heap_t* heap, heap_comparador comparador, int pos_hijo){
    if(pos_hijo == 0) return;

    int pos_padre = posicion_padre(pos_hijo);

    if(comparador(heap->v_gimnasios[pos_hijo], heap->v_gimnasios[pos_padre]) < 0){//Heap
        swap(heap->v_gimnasios, pos_hijo, pos_padre);
        shift_up(heap, comparador, pos_padre);
    }
}

void shift_down(heap_t* heap, heap_comparador comparador, int n){
    int pos_der = posicion_hijo_derecho(n);
    int pos_izq = posicion_hijo_izquierdo(n);

    if(pos_izq >= heap->cantidad) return;

    int pos_menor = pos_izq;
    if(pos_der < heap->cantidad)
        if(comparador(heap->v_gimnasios[pos_der], heap->v_gimnasios[pos_izq]) < 0)
            pos_menor = pos_der;

    if(comparador(heap->v_gimnasios[n], heap->v_gimnasios[pos_menor]) > 0){
        swap(heap->v_gimnasios, n, pos_menor);
        shift_down(heap, comparador, pos_menor);
    }

}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES PRINCIPALES ++++++++++++++++++++++++++++++++++++++++++++++++++ */
heap_t* crear_heap(heap_comparador comparador, heap_destructor_elemento destructor){
    if(!comparador || !destructor) return NULL;

    heap_t* heap = calloc(1, sizeof(heap_t));
    if(!heap) return NULL;

    heap->comparador = comparador;
    heap->destructor = destructor;
    return heap;
}

heap_t* heap_insertar_nodo(heap_t* heap, void* elemento){
    if(!heap || !elemento) return NULL;

    void* aux = realloc(heap->v_gimnasios, sizeof(void*) * (size_t)(heap->cantidad+1));
    if(!aux) return NULL;

    heap->v_gimnasios = aux;
    heap->cantidad++;
    heap->v_gimnasios[heap->cantidad-1] = elemento;
    shift_up(heap, heap->comparador, heap->cantidad-1);

    return heap;
}

void* extraer_nodo_raiz(heap_t* heap){
    if(heap->cantidad == 0) return 0;
    
    void* elemento_a_eliminar = heap->v_gimnasios[0];

    swap(heap->v_gimnasios, 0, heap->cantidad-1);
    heap->cantidad--;

    void* aux = realloc(heap->v_gimnasios, sizeof(void*) * (size_t)(heap->cantidad));
    //if(!aux) return elemento_a_eliminar;
    heap->v_gimnasios = aux;

    if(heap->cantidad != 0)
        shift_down(heap, heap->comparador, 0);

    return elemento_a_eliminar;
}

void heap_destruir_elementos(heap_t* heap, heap_destructor_elemento destructor){
    for(int i = 0; i < heap->cantidad; i++){
        if(destructor) destructor(heap->v_gimnasios[i]);
    }

}

void heap_destruir(heap_t* heap){
    if(!heap) return;

    heap_destruir_elementos(heap, heap->destructor);
    if(heap->v_gimnasios) free(heap->v_gimnasios);
    if(heap) free(heap);
}

/*
void mostrar_arbol(int* buffer, int n){
    printf("\n");
    int niveles = 0;
    for(int restantes = n; restantes > 0; restantes >>= 1){
        niveles++;
    }

    int n_nodo = 0;
    for(int nivel = 0; nivel < niveles; nivel++){
        int posicion = 1<<(niveles-nivel-1);

        for(int nodo = 0; nodo < (1<<nivel); nodo++){
            for(int i =0; i < posicion; i++){
                if(i <= posicion/2-1 || 2*n_nodo+1 >= n || buffer[2*n_nodo+1]==0)
                    printf("  ");
                else{
                    if(i == posicion/2)
                        printf(" r");
                    else
                        printf("---");
                }
            }
        }
    }
}

*/

/*
//Crea y me devuelve un heap ordenado (ordena el vector)
heap_t* heapify(gimnasio_t* v_gimnasios, int n){
    heap_t* mi_heap = crear_heap();
    mi_heap->v_gimnasios = v_gimnasios;
    mi_heap->cantidad = n;

    printf("\n\n Arbol antes del heapify:\n");
    mostrar_arbol(mi_heap->v_gimnasios, mi_heap->cantidad);

    int primero = posicion_padre(n-1);

    while(n >= 0){
        shift_down(&mi_heap, n);
        n--;
    }

    printf("\n\n Arbol despues del heapify:\n");
    mostrar_arbol(mi_heap->v_gimnasios, mi_heap->cantidad);
    return mi_heap;
}

void heap_sort(void* v_gimnasios, int n){
    heap_t* heap = heapify(v_gimnasios, n);

    while(n > 0){
        extraer_nodo_raiz(heap);
        n--;
    }

    free(heap);
    //Mostrar arbol
}
*/