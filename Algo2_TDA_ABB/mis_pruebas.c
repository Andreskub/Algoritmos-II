#include "abb.h"
#include "pa2mm.h"

#include <string.h>

#define MAX_MARCA 25

#define OK 0
#define ERROR -1
/* ++++++++++++++++++++++++++++++++++++++++++++++++++ PERSONALIZACION ARBOL ++++++++++++++++++++++++++++++++++++++++++++++++++ */

//Mi struct a trabajar
typedef struct{
    char marca[MAX_MARCA];
    size_t precio;
}bicicleta_t;

bicicleta_t* crear_bicicleta(char* marca, size_t precio){
    if (!marca || !precio) return NULL;

    bicicleta_t* bicicleta = malloc(sizeof(bicicleta_t));
    if(!bicicleta) return NULL;

    strcpy(bicicleta->marca,marca);
    //bicicleta->marca = marca;
    bicicleta->precio = precio;

    return bicicleta;
}

//Mi comparador de bicicletas
int comparar_bicicletas(void* bicicleta1, void* bicicleta2){
    if(!bicicleta1 || !bicicleta2) return 0;

    if(((bicicleta_t*)bicicleta1)->precio < ((bicicleta_t*)bicicleta2)->precio)
        return -1;
    
    if(((bicicleta_t*)bicicleta1)->precio > ((bicicleta_t*)bicicleta2)->precio)
        return 1;
    
    return 0;
}

//Destructor
void destruir_bicicleta(void* x){
    if(!x) return;
    free((bicicleta_t*)x);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ PRUEBAS ARBOL ++++++++++++++++++++++++++++++++++++++++++++++++++ */
abb_t* pruebas_arbol_vacio(abb_t* arbol){
    pa2m_afirmar((arbol = arbol_crear(comparar_bicicletas,destruir_bicicleta)) != NULL, "Se puede crear un ABB con comparador y destructor");
    pa2m_afirmar(arbol->nodo_raiz == NULL, "El nodo raiz es NULL");
    abb_t* aux = NULL;
    pa2m_afirmar((aux = arbol_crear(comparar_bicicletas,NULL)) != NULL, "Se puede crear un ABB sin destructor");
    pa2m_afirmar(arbol_crear(NULL,NULL) == NULL, "No se puede crear un ABB sin comparador");
    arbol_destruir(aux);
    return arbol;
}

void pruebas_insercion_borrado(abb_t* arbol){
    pa2m_nuevo_grupo("PRUEBAS DE INSERCIÓN");

    bicicleta_t* b1 = crear_bicicleta("Specialized", 679000);
    bicicleta_t* b2 = crear_bicicleta("Trek", 400000);
    bicicleta_t* b3 = crear_bicicleta("Scott", 550000);
    bicicleta_t* b4 = crear_bicicleta("Vairo", 215000);
    bicicleta_t* b5 = crear_bicicleta("Venzo", 455000);

    pa2m_afirmar(arbol_insertar(arbol, b3) == OK, "Puede insertar un elemento en el ABB");
    pa2m_afirmar(((bicicleta_t*)arbol_raiz(arbol)) == b3, "El elemento queda como valor raiz");
    pa2m_afirmar(arbol_insertar(arbol, b2) == OK, "Puede insertar un elemento menor a la raiz");
    pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento == b2, "El elemento queda a la izquierda de la raiz");
    pa2m_afirmar( ((((bicicleta_t*)arbol_raiz(arbol)) == b3) && (arbol->nodo_raiz->izquierda->elemento == b2) && (!arbol->nodo_raiz->derecha)), "El ABB queda con un hijo izquierdo y sin hijo derecho");
    pa2m_afirmar(arbol_insertar(arbol, b1) == OK, "Puede insertar un elemento mayor a la raiz");
    pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == b1, "El elemento queda a la derecha de la raiz");
    pa2m_afirmar( ((((bicicleta_t*)arbol_raiz(arbol)) == b3) && (arbol->nodo_raiz->izquierda->elemento == b2) && (arbol->nodo_raiz->derecha->elemento == b1)), "El ABB queda con un hijo izquierdo y un hijo derecho");
    pa2m_afirmar(arbol_insertar(arbol, b4) == OK, "Puede insertar un elemento menor a los existentes");
    pa2m_afirmar(arbol->nodo_raiz->izquierda->izquierda->elemento == b4, "El hijo izquierdo a la raiz ahora tiene un hijo izquierdo");
    pa2m_afirmar(arbol_insertar(arbol, b5) == OK,"Puede insertar un elemento mayor que el hijo izquierdo del nodo raiz");
    pa2m_afirmar(arbol->nodo_raiz->izquierda->derecha->elemento == b5,"El hijo izquierdo a la raiz ahora tiene un hijo derecho");
    
    bicicleta_t* b6 = crear_bicicleta("Raleigh", 200000);
    bicicleta_t* b7 = crear_bicicleta("Cannondale", 600000);
    bicicleta_t* b8 = crear_bicicleta("Santa Cruz", 1100000);
    bicicleta_t* b9 = crear_bicicleta("Firebird", 95000);
    bicicleta_t* b10 = crear_bicicleta("Colner", 330000);
    arbol_insertar(arbol, b6);
    arbol_insertar(arbol, b7);
    arbol_insertar(arbol, b8);
    arbol_insertar(arbol, b10);

    pa2m_nuevo_grupo("PRUEBAS DE BUSQUEDA");
    pa2m_afirmar(arbol_buscar(arbol, b6) == b6,"Busca un elemento existente y lo encuentra");
    pa2m_afirmar(arbol_buscar(arbol, b6) == b6,"Busca un elemento existente y lo encuentra");
    pa2m_afirmar(arbol_buscar(arbol, b6) == b6,"Busca un elemento existente y lo encuentra");
    pa2m_afirmar(arbol_buscar(arbol, b9) == NULL,"Buscar un elemento inexistente devuelve NULL");
    free(b9);

    pa2m_nuevo_grupo("PRUEBAS DE BORRADO");
    pa2m_afirmar(arbol_borrar(arbol, b7) == OK,"Puede borrar un nodo hoja");
    pa2m_afirmar(arbol->nodo_raiz->derecha->izquierda == NULL, "El nodo eliminado no existe mas");
    pa2m_afirmar(arbol_borrar(arbol, b1) == OK,"Puede borrar un nodo hoja con 1 hijo");
    pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == b8, "El nodo que queda en su lugar es el nodo hijo");
    pa2m_afirmar(arbol_borrar(arbol, b2) == OK,"Puede borrar un nodo hoja con 2 hijos");
    pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento == b10,"El nodo que queda en su lugar es el predecesor inorden");
    pa2m_afirmar(arbol_borrar(arbol, b3) == OK,"Puede borrar el nodo raiz con 2 hijos");
    pa2m_afirmar(arbol->nodo_raiz->elemento == b5, "El nodo que queda en su lugar es el predecesor inorden");

    pa2m_nuevo_grupo("PRUEBAS DE BORRADO (SIEMPRE NODO RAIZ)");
    pa2m_afirmar(arbol_borrar(arbol, arbol->nodo_raiz->elemento) == OK, "Puedo borrar la raíz del ABB");
    pa2m_afirmar(arbol_borrar(arbol, arbol->nodo_raiz->elemento) == OK, "Puedo borrar la raíz del ABB");
    pa2m_afirmar(arbol_borrar(arbol, arbol->nodo_raiz->elemento) == OK, "Puedo borrar la raíz del ABB");
    pa2m_afirmar(arbol_borrar(arbol, arbol->nodo_raiz->elemento) == OK, "Puedo borrar la raíz del ABB");
    pa2m_afirmar(arbol_borrar(arbol, arbol->nodo_raiz->elemento) == OK, "Puedo borrar la raíz del ABB");

    pa2m_afirmar(arbol->nodo_raiz == NULL, "Se eliminaron todos los nodos del ABB");
    pa2m_afirmar(arbol_vacio(arbol) == true, "La funcion arbol_vacio devuelve true");

    /*
    pa2m_nuevo_grupo("ALGUNAS PRUEBAS MAS GENERALES");
    arbol_insertar(arbol, b3);
    arbol_insertar(arbol, b2);
    arbol_insertar(arbol, b1);
    arbol_insertar(arbol, b4);
    arbol_insertar(arbol, b5);
    pa2m_afirmar(arbol_borrar(arbol,b3) == OK, "Borra la raiz del ABB");
    pa2m_afirmar(arbol_buscar(arbol, b3) == NULL, "El elemento no existe mas en el ABB");
    pa2m_afirmar(arbol_insertar(arbol, b3) == OK, "Puede volver a insertar el elemento");
    pa2m_afirmar(arbol->nodo_raiz->derecha->izquierda->elemento == b3, "El elemento fue insertado como nodo hoja");
    */
}


int main(){
    abb_t* arbol = NULL;

    pa2m_nuevo_grupo("PRUEBAS DE CREACIÓN");
    arbol = pruebas_arbol_vacio(arbol);

    
    pruebas_insercion_borrado(arbol);


    pa2m_nuevo_grupo("PRUEBAS RECORRIDO INORDEN");

    pa2m_nuevo_grupo("PRUEBAS RECORRIDO PREORDEN");

    pa2m_nuevo_grupo("PRUEBAS RECORRIDO POSTORDEN");

    pa2m_nuevo_grupo("PRUEBAS ITERADOR INTERNO");

    arbol_destruir(arbol);

    return 0;
}
