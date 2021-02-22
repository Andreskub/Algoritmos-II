#include "m_heap.h"

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES AUXILIARES ++++++++++++++++++++++++++++++++++++++++++++++++++ */
int posicion_padre(int n){
    return (n-1)/2;
}

int posicion_pos_derecho(int n){
    return 2*n+2;
}

int posicion_pos_izquierdo(int n){
    return 2*n+1;
}

void swap(int* vector, int i, int j){
    int aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;
}

void shift_up(heap_t* heap, int n){
    if(n == 0) return;

    int padre = posicion_padre(n);

    if(heap->v_gimnasios[n] > heap->v_gimnasios[padre]){
        swap(heap->v_gimnasios, n, padre);
        shift_up(heap, padre);
    }
}

void shift_down(heap_t* heap, int n){
    int pos_der = posicion_pos_derecho(n);
    int pos_izq = posicion_pos_izquierdo(n);

    if(pos_izq >= heap->cantidad) return;

    int pos_mayor = pos_izq;
    if(pos_der < heap->cantidad)
        if(heap->v_gimnasios[pos_der] < heap->v_gimnasios[pos_izq])
            pos_mayor = pos_der;
    
    if(heap->v_gimnasios[n] < heap->v_gimnasios[pos_mayor]){
        swap(heap->v_gimnasios, n, pos_mayor);
        shift_down(heap, pos_mayor);
    }

}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES PRINCIPALES ++++++++++++++++++++++++++++++++++++++++++++++++++ */
heap_t* crear_heap(destructor_elemento destructor){
    if(!destructor) return NULL

    heap_t* heap = calloc(1, sizeof(heap_t));
    if(!heap) return NULL;

    heap->destructor_elemento = destructor;
    return heap;
}

heap_t* insertar_nodo(heap_t* heap, void* elemento){
    if(!heap || !elemento) return NULL;

    void* aux = realloc(heap->v_gimnasios, sizeof(void*) * heap->cantidad);
    if(!aux) return NULL;

    heap->v_gimnasios = aux;
    heap->cantidad++;
    heap->v_gimnasios[heap->cantidad-1] = elemento;

    shift_up(heap, heap->cantidad-1);
    return heap;
}

int extraer_nodo_raiz(heap_t* heap){
    if(heap->cantidad == 0)
        return 0;
    
    int valor = heap->v_gimnasios[0];

    swap(heap->v_gimnasios, 0, heap->cantidad-1);
    heap->cantidad--;

    if(heap->cantidad != 0)
        shift_down(heap, 0);

    return valor;
}

void heap_destruir_elementos(heap_t* heap){
    for( int i = 0; i < heap->cantidad; i++){
        if(heap->v_gimnasios[i] && heap->destructor)
            destructor(heap->v_gimnasios[i]);
    }

    if(heap->v_gimnasios)
        free(heap->v_gimnasios);
}

void heap_destruir(heap_t* heap){
    if(!heap) return;

    heap_destruir_elementos(heap);
    free(heap);
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