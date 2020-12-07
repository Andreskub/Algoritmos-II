#include "abb.h"
#include <stdio.h>


/*
 * Crea un struct arbol vacio, reservando la memoria necesaria y asignando las funciones pasadas por parametro
 * como elementos del struct. Retorna NULL si no puede crearlo.
 * INPUT: function; function.
 * OUTPUT: struct pointer abb_t.
 */
abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    if(!destructor) return NULL;

    abb_t* arbol = malloc(sizeof(abb_t));
    if(!arbol) return NULL;

    arbol->nodo_raiz = NULL;
    arbol->comparador = comparador;
    arbol->destructor = destructor;

    return arbol;
}

/*
 * Funcion recursiva que dado un elemento, lo inserta en el arbol.
 * INPUT: struct pointer nodo_abb_t; void pointer; function.
 * OUTPUT: struct pointer nodo_abb_t.
 */
nodo_abb_t* recorrer_arbol_insertar(nodo_abb_t* nodo_actual, void* elemento, abb_comparador comparador){
    //Hago el caso para un arbol vacio
    if(!nodo_actual){
        nodo_abb_t* nodo_actual = calloc(1, sizeof(nodo_abb_t));
        if (!nodo_actual) return NULL;

        nodo_actual->elemento = elemento;
        return nodo_actual;
    }

    //Hago caso de los hijos del nodo
    if (comparador(elemento, nodo_actual->elemento) <= 0){
        nodo_actual->izquierda = recorrer_arbol_insertar(nodo_actual->izquierda, elemento, comparador);
    } else {
        nodo_actual->derecha = recorrer_arbol_insertar(nodo_actual->derecha, elemento, comparador);
    }
 
    return nodo_actual;
}

/*
 * Funcion que dado un elemento y un arbol, busca insertar el elemento en el arbol (admite valores repetidos).
 * Retorna 0 si logro insertarlo, caso contrario retorna -1.
 * INPUT: struct pointer abb_t; void pointer.
 * OUTPUT: int.
 */
int arbol_insertar(abb_t* arbol, void* elemento){
    if (!arbol || !elemento) return -1;

    arbol->nodo_raiz = recorrer_arbol_insertar(arbol->nodo_raiz, elemento, arbol->comparador);
    if(!arbol->nodo_raiz) return -1;
    
    return 0;
}


void destruir_nodo(nodo_abb_t* nodo, abb_liberar_elemento destructor){
    if(nodo && destructor)
        destructor(nodo->elemento);
    free(nodo);
}

nodo_abb_t* recorrer_padre_inmediato_inferior(nodo_abb_t* nodo_actual, nodo_abb_t* nodo_destino){
    if (!nodo_actual->derecha)
        return NULL;
    if (nodo_actual->derecha == nodo_destino)
        return nodo_actual;
    return recorrer_padre_inmediato_inferior(nodo_actual->derecha, nodo_destino);
}

nodo_abb_t* recorrer_inmediato_inferior(nodo_abb_t* nodo_actual){
    if(!nodo_actual->derecha)
        return nodo_actual;
    return recorrer_inmediato_inferior(nodo_actual->derecha); 
}

nodo_abb_t* reordenar_arbol(nodo_abb_t* nodo_actual, abb_liberar_elemento destructor){
    if (!nodo_actual->izquierda && !nodo_actual->derecha){ //Si el nodo no tiene hijos, lo elimino
        destruir_nodo(nodo_actual, destructor); 
        return NULL;
    } else if (nodo_actual->izquierda && nodo_actual->derecha){ //Si el nodo tiene 2 hijos

        nodo_abb_t* nodo_insertar = recorrer_inmediato_inferior(nodo_actual->izquierda);
        nodo_abb_t* nodo_padre = recorrer_padre_inmediato_inferior(nodo_actual->izquierda, nodo_insertar);
        if (nodo_padre)
            nodo_padre->derecha = nodo_insertar->izquierda; //Puede tener algo o ser null
        if (nodo_insertar != nodo_actual->izquierda)
            nodo_insertar->izquierda = nodo_actual->izquierda;

        destruir_nodo(nodo_actual, destructor);
        return nodo_insertar;
    }
        
    nodo_abb_t* nodo_aux = nodo_actual->izquierda?nodo_actual->izquierda:nodo_actual->derecha; //Si el nodo solo tiene 1 hijo
    destruir_nodo(nodo_actual, destructor);
    return nodo_aux;
}

/*
 * Funcion recursiva que dado un elemento, busca el mismo en el arbol. Si lo encuentra procede a elimiarlo del arbol (liberar su memoria).
 * INPUT: struct pointer nodo_abb_t; void pointer; function; function.
 * OUTPUT: struct pointer nodo_abb_t.
 */
nodo_abb_t* recorrer_arbol_borrar(nodo_abb_t* nodo_actual, void* elemento, abb_comparador comparador, abb_liberar_elemento destructor){
    if (!nodo_actual) return NULL;
    
    int devolucion_comparacion = comparador(elemento, nodo_actual->elemento);

    if (devolucion_comparacion == 0)
        return reordenar_arbol(nodo_actual, destructor); 
    
    if (comparador(elemento, nodo_actual->elemento) == -1){ //Si el elemento es menor al recorrido
        nodo_actual->izquierda = recorrer_arbol_borrar(nodo_actual->izquierda, elemento, comparador, destructor);
    } else if (comparador(elemento, nodo_actual->elemento) == 1){ //Si el elemento es mayor al recorrido
        nodo_actual->derecha = recorrer_arbol_borrar(nodo_actual->derecha, elemento, comparador, destructor);
    }

    return nodo_actual;
}

/*
 * Funcion que dado un elemento y un arbol. Si el elemento se encuentra en el arbol busca eliminarlo.
 * Retorna 0 si logro eliminarlo, caso contrario retorna -1.
 * INPUT: struct pointer abb_t; void pointer.
 * OUTPUT: int.
 */
int arbol_borrar(abb_t* arbol, void* elemento){
    if (!elemento || !arbol || !arbol->comparador) return -1;

    arbol->nodo_raiz = recorrer_arbol_borrar(arbol->nodo_raiz, elemento, arbol->comparador, arbol->destructor);
    if (!arbol->nodo_raiz) return -1;

    return 0;
}


/*
 * Funcion recursiva que dado un elemento, lo busca en el arbol. 
 * Si lo encuentra devuelve el elemento, de caso contrario devuelve NULL..
 * INPUT: struct pointer nodo_abb_t; void pointer; function.
 * OUTPUT: struct pointer nodo_abb_t.
 */
nodo_abb_t* recorrer_arbol_buscar(nodo_abb_t* nodo_actual, void* elemento, abb_comparador comparador){
    if (!nodo_actual) return NULL;

    int devolucion_comparacion = comparador(elemento, nodo_actual->elemento);

    if (devolucion_comparacion == 0){
        return nodo_actual->elemento;
    } else if (devolucion_comparacion < 0){
        return recorrer_arbol_buscar(nodo_actual->izquierda, elemento, comparador);
    } else if (devolucion_comparacion > 0) {
        return recorrer_arbol_buscar(nodo_actual->derecha, elemento, comparador);
    }

}

/*
 * Dado un elemento y un arbol, busca el elemento en el arbol.
 * Retorna el elemento se lo encuentra, caso contrario retorna NULL.
 * INPUT: struct pointer abb_t; void pointer.
 * OUTPUT: void pointer.
 */
void* arbol_buscar(abb_t* arbol, void* elemento){
    if (!arbol || !elemento) return NULL;

    return recorrer_arbol_buscar(arbol->nodo_raiz, elemento, arbol->comparador);
}

/*
 * Devuelve el elemento almacenado como raiz o NULL si el árbol está
 * vacío o no existe.
 */
void* arbol_raiz(abb_t* arbol){
    if (!arbol || !arbol->nodo_raiz) return NULL;
    return arbol->nodo_raiz->elemento;
}

/*
 * Determina si el árbol está vacío.
 * Devuelve true si está vacío o el arbol es NULL, false si el árbol tiene elementos.
 */
bool arbol_vacio(abb_t* arbol){
    if(!arbol || !arbol->nodo_raiz)
        return true;
    return false;
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia inorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array);

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia preorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array);

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia postorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array);







void arbol_destruir_nodos(nodo_abb_t* nodo_actual, abb_liberar_elemento destructor){
    if (nodo_actual->izquierda)
        arbol_destruir_nodos(nodo_actual->izquierda, destructor);
    if (nodo_actual->derecha)
        arbol_destruir_nodos(nodo_actual->derecha, destructor);
    if(!nodo_actual->izquierda && !nodo_actual->derecha)
        destruir_nodo(nodo_actual, destructor);
}
/*
 * Destruye el arbol liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el arbol.
 */
void arbol_destruir(abb_t* arbol){
    if(arbol && arbol->nodo_raiz)
        arbol_destruir_nodos(arbol->nodo_raiz, arbol->destructor);
    if (arbol)    
        free(arbol);
}

/*
 * Iterador interno. Recorre el arbol e invoca la funcion con cada
 * elemento del mismo. El puntero 'extra' se pasa como segundo
 * parámetro a la función. Si la función devuelve true, se finaliza el
 * recorrido aun si quedan elementos por recorrer. Si devuelve false
 * se sigue recorriendo mientras queden elementos.
 * El recorrido se realiza de acuerdo al recorrido solicitado.  Los
 * recorridos válidos son: ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN
 * y ABB_RECORRER_POSTORDEN.
 * Devuelve la cantidad de elementos que fueron recorridos.
*/
size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra);