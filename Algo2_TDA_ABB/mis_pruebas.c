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
void pruebas_arbol_vacio(abb_t* arbol){
    pa2m_afirmar((arbol = arbol_crear(comparar_bicicletas,destruir_bicicleta)) != NULL, "Se puede crear un ABB con comparador y destructor");
    pa2m_afirmar(arbol->nodo_raiz == NULL, "El nodo raiz es NULL");
    
    pa2m_afirmar(arbol_crear(comparar_bicicletas,NULL) != NULL, "Se puede crear un ABB sin destructor");
    pa2m_afirmar(arbol_crear(NULL,NULL) == NULL, "No se puede crear un ABB sin comparador");
   
}

void pruebas_de_insercion(abb_t* arbol){
    bicicleta_t* b1 = crear_bicicleta("Specialized", 679000);
    bicicleta_t* b2 = crear_bicicleta("Trek", 400000);
    bicicleta_t* b3 = crear_bicicleta("Scott", 550000);
    bicicleta_t* b4 = crear_bicicleta("Vairo", 215000);
    bicicleta_t* b5 = crear_bicicleta("Venzo", 155000);
    bicicleta_t* b6 = crear_bicicleta("Raleigh", 200000);

    pa2m_afirmar(arbol_insertar(arbol, b3) == OK, "Puedo insertar un elemento en el ABB");
    pa2m_afirmar(((bicicleta_t*)arbol_raiz(arbol)) == b3, "El elemento queda como valor raiz");
    pa2m_afirmar(arbol_insertar(arbol, b2) == OK, "Puedo insertar un elemento menor");
    pa2m_afirmar((arbol->nodo_raiz->elemento == b3)&&(arbol->nodo_raiz->izquierda->elemento == b2)&&(arbol->nodo_raiz->derecha->elemento == NULL), "El ABB queda con un hijo izquierdo y sin hijo derecho");

}

int main(){
    abb_t* arbol = NULL;

    pa2m_nuevo_grupo("PRUEBAS DE CREACIÓN");
    pruebas_arbol_vacio(arbol);

    pa2m_nuevo_grupo("PRUEBAS DE INSERCIÓN");
    pruebas_de_insercion(arbol);


    pa2m_nuevo_grupo("PRUEBAS RECORRIDO INORDEN");

    pa2m_nuevo_grupo("PRUEBAS RECORRIDO PREORDEN");

    pa2m_nuevo_grupo("PRUEBAS RECORRIDO POSTORDEN");

    pa2m_nuevo_grupo("PRUEBAS ITERADOR INTERNO");

    arbol_destruir(arbol);

    return 0;
}
