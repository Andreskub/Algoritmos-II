#include "abb.h"

//Mi strct a trabajar
typedef struct{
    char modelo;
    size_t precio;
}bicicleta_t;

//Mi comparador de bicicletas
int comparar_precio_bicicleta(void* bicicleta1, void* bicicleta2){
    if(((bicicleta_t*)bicicleta1)->precio < ((bicicleta_t*)bicicleta2)->precio)
        return -1;
    
    if(((bicicleta_t*)bicicleta1)->precio > ((bicicleta_t*)bicicleta2)->precio)
        return 1;
    
    return 0;
}



//Comparador
int comparador_elementos(void* elemento, void* comparador){
    if (elemento == comparador) return 0;
    if (elemento < comparador) return -1;
    if (elemento > comparador) return 1;
}

//Destructor
void borrar_del_arbol(void* nodo){
    free(nodo);
}

/*
int main(){

    abb_t* arbol_prueba = arbol_crear(comparador_elementos, NULL);
    free(arbol_prueba);
    
    return 0;
}
*/