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
void destruir_bicicleta(void* bicicleta){
    if(!bicicleta) return;
    free((bicicleta_t*)bicicleta);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCIONES AUXILIARES ++++++++++++++++++++++++++++++++++++++++++++++++++ */
bicicleta_t* crear_array(){
    bicicleta_t* array = malloc(sizeof(bicicleta_t) * 15);
    return array?array:NULL;
}
/*
void llenar_arbol_y_array(abb_t* arbol, bicicleta_t* array){
    
    bicicleta_t* b1 = crear_bicicleta("Specialized", 679000);
    bicicleta_t* b2 = crear_bicicleta("Trek", 400000);
    bicicleta_t* b3 = crear_bicicleta("Scott", 550000);
    bicicleta_t* b4 = crear_bicicleta("Vairo", 215000);
    bicicleta_t* b5 = crear_bicicleta("Venzo", 455000);
    bicicleta_t* b6 = crear_bicicleta("Raleigh", 200000);
    bicicleta_t* b7 = crear_bicicleta("Cannondale", 600000);
    bicicleta_t* b8 = crear_bicicleta("Santa Cruz", 1100000);
    bicicleta_t* b9 = crear_bicicleta("Firebird", 95000);
    bicicleta_t* b10 = crear_bicicleta("Colner", 330000);
    bicicleta_t* b11 = crear_bicicleta("Specialized", 679000);
    bicicleta_t* b12 = crear_bicicleta("Trek", 400000);
    bicicleta_t* b13 = crear_bicicleta("Scott", 550000);
    bicicleta_t* b14 = crear_bicicleta("Vairo", 215000);
    bicicleta_t* b15 = crear_bicicleta("Venzo", 455000);
    arbol_insertar(arbol, b1);
    arbol_insertar(arbol, b2);
    arbol_insertar(arbol, b3);
    arbol_insertar(arbol, b4);
    arbol_insertar(arbol, b5);
    arbol_insertar(arbol, b6);
    arbol_insertar(arbol, b7);
    arbol_insertar(arbol, b8);
    arbol_insertar(arbol, b9);
    arbol_insertar(arbol, b10);
    arbol_insertar(arbol, b11);
    arbol_insertar(arbol, b12);
    arbol_insertar(arbol, b13);
    arbol_insertar(arbol, b14);
    arbol_insertar(arbol, b15);
    array[0] = b1;
    array[1] = b2;
    array[2] = b3;
    array[3] = b4;
    array[4] = b5;
    array[5] = b6;
    array[6] = b7;
    array[7] = b8;
    array[8] = b9;
    array[9] = b10;
    array[10] = b11;
    array[11] = b12;
    array[12] = b13;
    array[13] = b14;
    array[14] = b15; 
}
*/
/* ++++++++++++++++++++++++++++++++++++++++++++++++++ PRUEBAS ARBOL ++++++++++++++++++++++++++++++++++++++++++++++++++ */
abb_t* pruebas_arbol_vacio(){
    pa2m_nuevo_grupo("PRUEBAS DE CREACIÓN");
    abb_t* arbol = NULL;

    pa2m_afirmar((arbol = arbol_crear(comparar_bicicletas,destruir_bicicleta)) != NULL, "Se puede crear un ABB con comparador y destructor");
    pa2m_afirmar(arbol->nodo_raiz == NULL, "El nodo raiz es NULL");
    abb_t* aux = NULL;
    pa2m_afirmar((aux = arbol_crear(comparar_bicicletas,NULL)) != NULL, "Se puede crear un ABB sin destructor");
    pa2m_afirmar(arbol_crear(NULL,NULL) == NULL, "No se puede crear un ABB sin comparador");
    
    arbol_destruir(aux); 
    return arbol;
}

abb_t* pruebas_insercion(abb_t* arbol){
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
    pa2m_afirmar(arbol_buscar(arbol, b10) == b10,"Busca un elemento existente y lo encuentra");
    pa2m_afirmar(arbol_buscar(arbol, b7) == b7,"Busca un elemento existente y lo encuentra");
    pa2m_afirmar(arbol_buscar(arbol, b9) == NULL,"Buscar un elemento inexistente devuelve NULL");
    destruir_bicicleta(b9);

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

    return arbol;
}

void pruebas_generales(){
    abb_t* arbol = arbol_crear(comparar_bicicletas, destruir_bicicleta);
        
    bicicleta_t* b11 = crear_bicicleta("Specialized", 679000);
    bicicleta_t* b12 = crear_bicicleta("Trek", 400000);
    bicicleta_t* b13 = crear_bicicleta("Scott", 550000);
    bicicleta_t* b14 = crear_bicicleta("Vairo", 215000);
    bicicleta_t* b15 = crear_bicicleta("Venzo", 455000);
    arbol_insertar(arbol, b13);
    arbol_insertar(arbol, b12);
    arbol_insertar(arbol, b11);
    arbol_insertar(arbol, b14);
    arbol_insertar(arbol, b15);

    pa2m_afirmar(arbol_borrar(arbol,b13) == OK, "Borra la raiz del ABB");
    bicicleta_t* aux = crear_bicicleta("Scott", 550000);
    pa2m_afirmar(arbol_buscar(arbol, aux) == NULL, "El elemento no existe mas en el ABB");
    pa2m_afirmar(arbol_insertar(arbol, aux) == OK, "Puede volver a insertar el mismo elemento");
    pa2m_afirmar(arbol->nodo_raiz->derecha->izquierda->elemento == aux, "El elemento fue insertado como nodo hoja");

    arbol_destruir(arbol);
}

void llenar_arbol_7(abb_t* arbol){
    bicicleta_t* b1 = crear_bicicleta("Scott", 550000);
    bicicleta_t* b2 = crear_bicicleta("Trek", 400000);
    bicicleta_t* b3 = crear_bicicleta("Specialized", 679000);
    bicicleta_t* b4 = crear_bicicleta("Vairo", 215000);
    bicicleta_t* b5 = crear_bicicleta("Venzo", 455000);
    bicicleta_t* b6 = crear_bicicleta("Cannondale", 600000);
    bicicleta_t* b7 = crear_bicicleta("Santa Cruz", 1100000);
    arbol_insertar(arbol, b1);
    arbol_insertar(arbol, b2);
    arbol_insertar(arbol, b3);
    arbol_insertar(arbol, b4);
    arbol_insertar(arbol, b5);
    arbol_insertar(arbol, b6);
    arbol_insertar(arbol, b7);
}

size_t aux_recorrido(abb_t* arbol, bicicleta_t** elementos, size_t* precios, size_t cantidad){
    size_t contador = 0;

    for(size_t i = 0; i < cantidad; i++){
        if ( elementos[i]->precio == precios[i])
            contador++;
    }
    return contador;
}

void pruebas_recorrido_inorden(abb_t* arbol){
    size_t precios_inorden[7] = {215000,400000,455000,550000,600000,679000,1100000};

    bicicleta_t* elementos[7];
    size_t cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 7);
    size_t contador = aux_recorrido(arbol, elementos, precios_inorden, cantidad);
    pa2m_afirmar(cantidad == 7,"La funcion de recorrido devuelve la cantidad de elementos esperados");
    pa2m_afirmar(contador == 7, "Los elementos en el vector tienen el oden esperado");
    
    bicicleta_t* elementos2[7];
    size_t cantidad2 = arbol_recorrido_inorden(arbol, (void**)elementos2, 5);
    contador = aux_recorrido(arbol, elementos, precios_inorden, cantidad2);    
    pa2m_afirmar(cantidad2 == 5,"Pido recorrer menos elementos de los existentes para hacer el recorrido");
    pa2m_afirmar(contador == 5, "Los elementos en el vector tienen el oden esperado");

    bicicleta_t* elementos3[7];
    size_t cantidad3 = arbol_recorrido_inorden(arbol, (void**)elementos3, 10);
    contador = aux_recorrido(arbol, elementos, precios_inorden, cantidad3); 
    pa2m_afirmar(cantidad3 == 7,"Pido recorrer mas elementos de los existentes para hacer el recorrido");
    pa2m_afirmar(contador == 7, "Los elementos en el vector tienen el oden esperado");

}

void pruebas_recorrido_preorden(abb_t* arbol){
    size_t precios_preorden[7] = {550000,400000,215000,455000,679000,600000,1100000};

    bicicleta_t* elementos[7];
    size_t cantidad = arbol_recorrido_preorden(arbol, (void**)elementos, 7);
    size_t contador = aux_recorrido(arbol, elementos, precios_preorden, cantidad);
    pa2m_afirmar(cantidad == 7,"La funcion de recorrido devuelve la cantidad de elementos esperados");
    pa2m_afirmar(contador == 7, "Los elementos en el vector tienen el oden esperado");
    
    bicicleta_t* elementos2[7];
    size_t cantidad2 = arbol_recorrido_preorden(arbol, (void**)elementos2, 5);
    contador = aux_recorrido(arbol, elementos, precios_preorden, cantidad2);    
    pa2m_afirmar(cantidad2 == 5,"Pido recorrer menos elementos de los existentes para hacer el recorrido");
    pa2m_afirmar(contador == 5, "Los elementos en el vector tienen el oden esperado");

    bicicleta_t* elementos3[7];
    size_t cantidad3 = arbol_recorrido_preorden(arbol, (void**)elementos3, 10);
    contador = aux_recorrido(arbol, elementos, precios_preorden, cantidad3); 
    pa2m_afirmar(cantidad3 == 7,"Pido recorrer mas elementos de los existentes para hacer el recorrido");
    pa2m_afirmar(contador == 7, "Los elementos en el vector tienen el oden esperado");
}

void pruebas_recorrido_postorden(abb_t* arbol){
    size_t precios_postorden[7] = {215000,455000,400000,600000,1100000,679000,550000};

    bicicleta_t* elementos[7];
    size_t cantidad = arbol_recorrido_postorden(arbol, (void**)elementos, 7);
    size_t contador = aux_recorrido(arbol, elementos, precios_postorden, cantidad);
    pa2m_afirmar(cantidad == 7,"La funcion de recorrido devuelve la cantidad de elementos esperados");
    pa2m_afirmar(contador == 7, "Los elementos en el vector tienen el oden esperado");
    
    bicicleta_t* elementos2[7];
    size_t cantidad2 = arbol_recorrido_postorden(arbol, (void**)elementos2, 5);
    contador = aux_recorrido(arbol, elementos, precios_postorden, cantidad2);    
    pa2m_afirmar(cantidad2 == 5,"Pido recorrer menos elementos de los existentes para hacer el recorrido");
    pa2m_afirmar(contador == 5, "Los elementos en el vector tienen el oden esperado");

    bicicleta_t* elementos3[7];
    size_t cantidad3 = arbol_recorrido_postorden(arbol, (void**)elementos3, 10);
    contador = aux_recorrido(arbol, elementos, precios_postorden, cantidad3); 
    pa2m_afirmar(cantidad3 == 7,"Pido recorrer mas elementos de los existentes para hacer el recorrido");
    pa2m_afirmar(contador == 7, "Los elementos en el vector tienen el oden esperado");
}

bool es_costosa(void* elemento, void* extra){
    //extra=extra;
    if(((bicicleta_t*)elemento)->precio > 1000000)
        return true;
    return false;
}

void pruebas_iterador_interno(abb_t* arbol){

    size_t contador = abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, es_costosa, NULL);
    pa2m_afirmar(contador == 7, "El iterador interno devuelve la cantidad de elementos que se esperaba iterar");

    contador = abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, es_costosa, NULL);
    pa2m_afirmar(contador == 5, "El iterador interno devuelve la cantidad de elementos que se esperaba iterar");

    contador = abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, es_costosa, NULL);
    pa2m_afirmar(contador == 7, "El iterador interno devuelve la cantidad de elementos que se esperaba iterar");
    //printf("\n%li\n", contador);
}

int main(){
    abb_t* arbol = pruebas_arbol_vacio();

    //bicicleta_t* array = crear_array();
    
    pruebas_insercion(arbol);

    pa2m_nuevo_grupo("ALGUNAS PRUEBAS MAS GENERALES");
    pruebas_generales();

    arbol_destruir(arbol);

    abb_t* arbol_recorrido = arbol_crear(comparar_bicicletas,destruir_bicicleta);
    llenar_arbol_7(arbol_recorrido);

    pa2m_nuevo_grupo("PRUEBAS RECORRIDO INORDEN");
    pruebas_recorrido_inorden(arbol_recorrido);
    pa2m_nuevo_grupo("PRUEBAS RECORRIDO PREORDEN");
    pruebas_recorrido_preorden(arbol_recorrido);
    pa2m_nuevo_grupo("PRUEBAS RECORRIDO POSTORDEN");
    pruebas_recorrido_postorden(arbol_recorrido);
    pa2m_nuevo_grupo("PRUEBAS ITERADOR INTERNO");
    pruebas_iterador_interno(arbol_recorrido);

    arbol_destruir(arbol_recorrido);    

    return 0;
}
