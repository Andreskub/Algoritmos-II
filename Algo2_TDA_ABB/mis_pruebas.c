#include "abb.h"
#include "pa2mm.h"

#define MAX_MARCA 25

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ PERSONALIZACION ARBOL ++++++++++++++++++++++++++++++++++++++++++++++++++ */

//Mi struct a trabajar
typedef struct{
    char marca[MAX_MARCA];
    size_t precio;
}bicicleta_t;

bicicleta_t* crear_bicicleta(char marca, size_t precio){
    if (!marca || !precio) return NULL;

    bicicleta_t* bicicleta = malloc(sizeof(bicicleta_t));
    if(!bicicleta) return NULL;

    bicicleta->marca = marca;
    bicicleta->precio = precio;

    return bicicleta;
}

//Mi comparador de bicicletas
int comparar_precio_bicicleta(void* bicicleta1, void* bicicleta2){
    if(((bicicleta_t*)bicicleta1)->precio < ((bicicleta_t*)bicicleta2)->precio)
        return -1;
    
    if(((bicicleta_t*)bicicleta1)->precio > ((bicicleta_t*)bicicleta2)->precio)
        return 1;
    
    return 0;
}

//Destructor
void destructor_de_bicicletas(void* x){
    if(!x) return;
    free((bicicleta_t*)x);
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++ PRUEBAS ARBOL ++++++++++++++++++++++++++++++++++++++++++++++++++ */
void pruebas_arbol_vacio(abb_t* arbol){

    pa2m_afirmar(arbol_crear(NULL,NULL) == NULL, "Devuelve NULL si el comparador es erroneo");
    

}

int main(){
    abb_t* arbol = NULL;

    pa2m_nuevo_grupo("PRUEBAS ARBOL VACIO");
    pruebas_arbol_vacio(arbol);

    

    pa2m_nuevo_grupo("PRUEBAS RECORRIDO INORDEN");

    pa2m_nuevo_grupo("PRUEBAS RECORRIDO PREORDEN");

    pa2m_nuevo_grupo("PRUEBAS RECORRIDO POSTORDEN");

    pa2m_nuevo_grupo("PRUEBAS ITERADOR INTERNO");

    return 0;
}