#include "m_lista.h"

#include <stdio.h>
#include <stdlib.h>

/*+++++++++++++++++++++++++++++++++++ LISTAS ++++++++++++++++++++++++++++++++++++*/

/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
*/
lista_t* lista_crear(){

	lista_t* nueva_lista = malloc(sizeof(lista_t));
	if (!nueva_lista)
		return NULL;
	
	nueva_lista->cantidad = 0;
	nueva_lista->nodo_inicio = NULL;
	nueva_lista->nodo_fin = NULL;

	return nueva_lista;
}

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar(lista_t* lista, void* elemento){
	if (!lista) return -1;

	//Pido memoria para un nuevo nodo
	nodo_t* nodo_insertar = malloc(sizeof(nodo_t));
	if(!nodo_insertar)
		return -1;
	
	//Asigno valores del nodo a insertar
	nodo_insertar->elemento = elemento;
	nodo_insertar->siguiente = NULL;
	
	//Si la lista existe y esta vacia
	if(lista->cantidad == 0){
		lista->nodo_inicio = nodo_insertar;
		lista->nodo_fin = nodo_insertar;
	} else {
		//Asigno al ultimo de la lista, la referncia de memoria del nuevo nodo
		lista->nodo_fin->siguiente = nodo_insertar;
		lista->nodo_fin = nodo_insertar;
	}
	;
	lista->cantidad++;
	return 0;
}

/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){

	if(!lista)
		return -1;

	//Si el elemento supera la cantidad total lo inserto a lo ultimo
	if (posicion >= lista->cantidad){
		int es_error = lista_insertar(lista, elemento);
		return es_error;
	}

	//Pido memoria para nuevo nodo
	nodo_t* nodo_insertar = malloc(sizeof(nodo_t));
	if(!nodo_insertar){
		return -1;
	}

	nodo_insertar->elemento = elemento;

	//Si es el primero simplemente referencio adecuadamente los nodos modificados
	if (posicion == 0){
		nodo_insertar->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_insertar;
	} else {
		//Sino recorro los n nodos hasta llegar al anterior a la posicion pedida y me lo guardo
		nodo_t* nodo_anterior;
		for(int i = 0; i < posicion; i++){
			if(i == 0){
				nodo_anterior = lista->nodo_inicio;
			} else {
				nodo_anterior = nodo_anterior->siguiente;
			}
		}
		//Referencio adecuadamente los nodos modificados
		nodo_insertar->siguiente = nodo_anterior->siguiente;
		nodo_anterior->siguiente = nodo_insertar;

	}
	
	lista->cantidad++;
	return 0;
	
}

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t* lista){

	if(!lista)
		return -1;

	//Si existe la lista pero esta vacia
	if(lista && lista->cantidad == 0)
		return -1;

	//Si en la lista solo hay 1 elemento
	if (lista->cantidad == 1 && lista->nodo_inicio == lista->nodo_fin){
		free(lista->nodo_inicio);
		lista->cantidad--;
		return 0;
	}

	//Recorro los n elementos y me guardo el anteultimo
	nodo_t* nodo_anteultimo = NULL;
	for(int i = 0; i < (lista->cantidad -1); i++){
		if(i == 0){
			nodo_anteultimo = lista->nodo_inicio;
		} else {
			nodo_anteultimo = nodo_anteultimo->siguiente;
		}
	}

	//Referencio adecuadamente el anteultimo y libero el ultimo
	if(nodo_anteultimo->siguiente){
		lista->nodo_fin = nodo_anteultimo;
		free(nodo_anteultimo->siguiente);
		nodo_anteultimo->siguiente = NULL;
	}
	
	lista->cantidad--;
	return 0;
}

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.  
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.  
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if(!lista) return -1;

	//Si la lista existe pero esta vacia
	if(lista && lista->cantidad == 0) return -1;

	//Si es el ultimo o la posicion supera la cantidad total
	if(posicion > (lista->cantidad -1)){
		int es_error = lista_borrar(lista);
		return es_error;
	}

	nodo_t* nodo_a_borrar = NULL;
	//Si es el primero, referencio adecuadamente y libero el nodo pedido
	if(posicion == 0){
		nodo_a_borrar = lista->nodo_inicio;
		lista->nodo_inicio = nodo_a_borrar->siguiente;
		free(nodo_a_borrar);
	} else {
		nodo_t* nodo_anterior = NULL;
		//Recorro los n nodos
		for(int i = 0; i < posicion; i++){
			if(i == 0){
				nodo_anterior = lista->nodo_inicio;
			} else{
				nodo_anterior = nodo_anterior->siguiente;
			}
		}

		//Referencio adecuadamente y libero el nodo pedido
		nodo_a_borrar = nodo_anterior->siguiente;
		nodo_anterior->siguiente = nodo_a_borrar->siguiente;
		free(nodo_a_borrar);
	}

	lista->cantidad--;
	return 0; 
}

/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){

	if(!lista || posicion >= lista->cantidad)
		return NULL;

	//Si es el primero o el ultimo lo devuelo COLTA
	if(posicion == 0){
		return lista->nodo_inicio->elemento;
	} else if(posicion == (lista->cantidad -1)){
		return lista->nodo_fin->elemento;
	}

	//Recorro y me voy guardando los nodos hasta llegar al pedido
	nodo_t* nodo_guardar = lista->nodo_inicio;
	for(int i = 0; i < posicion; i++){
		nodo_guardar = nodo_guardar->siguiente;
	}

	return nodo_guardar->elemento;
}

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista){
	if (lista && lista->cantidad > 0)
		return lista->nodo_fin->elemento;
	
	return NULL;
}

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista){
	if(!lista || lista->cantidad == 0)
		return true;

	return false;
}

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista){
	if(!lista)
		return 0;
	//Retorno al cantidad de elementos
	return(lista->cantidad);
}

/*+++++++++++++++++++++++++++++++ PILAS Y COLAS +++++++++++++++++++++++++++++++*/

/* 
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario. 
 */
int lista_apilar(lista_t* lista, void* elemento){
	return lista_insertar(lista, elemento);
}

/* 
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o -1 si no pudo.
 */
int lista_desapilar(lista_t* lista){
	return lista_borrar(lista);
}

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 */
void* lista_tope(lista_t* lista){
	return lista_ultimo(lista);
}

/* 
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int lista_encolar(lista_t* lista, void* elemento){
	return lista_insertar(lista, elemento);
}

/* 
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int lista_desencolar(lista_t* lista){
	return lista_borrar_de_posicion(lista, 0);
}

/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 */
void* lista_primero(lista_t* lista){
	return lista_elemento_en_posicion(lista, 0);
}


void destruir_nodos_lista(nodo_t* nodo){
	if(nodo->siguiente)
		destruir_nodos_lista(nodo->siguiente);
	if (nodo)
		free(nodo);
}
/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista){

 	if(lista && lista->cantidad > 0)
 		destruir_nodos_lista(lista->nodo_inicio);
 	if(lista)
 		free(lista);
}

/*+++++++++++++++++++++++++++++++ ITERADORES +++++++++++++++++++++++++++++++*/

/*
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista). 
 *
 * Al momento de la creación, el iterador queda listo para devolver el
 * primer elemento utilizando lista_iterador_elemento_actual.
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
lista_iterador_t* lista_iterador_crear(lista_t* lista){

	if(!lista)
		return NULL;

	lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
	if(!iterador)
		return NULL;

	iterador->lista = lista;
	iterador->corriente = lista->nodo_inicio;

	return iterador;
}

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(!iterador)
		return false;
	return iterador->corriente;
}

/*
 * Avanza el iterador al siguiente elemento.
 * Devuelve true si pudo avanzar el iterador o false en caso de
 * que no queden elementos o en caso de error.
 *
 * Una vez llegado al último elemento, si se invoca a
 * lista_iterador_elemento_actual, el resultado siempre será NULL.
 */
bool lista_iterador_avanzar(lista_iterador_t* iterador){

	if(!iterador)
		return false;

	if(!iterador->corriente)
		return NULL;

	if(!iterador->corriente->siguiente){
		iterador->corriente = iterador->corriente->siguiente;
		return false;
	}
	//Muevo el puntero de corriente al siguiente elemento
	iterador->corriente = iterador->corriente->siguiente;
	return true;
}

/*
 * Devuelve el elemento actual del iterador o NULL en caso de que no
 * exista dicho elemento o en caso de error.
 */
void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
	if(!iterador || !iterador->lista || !iterador->corriente)
		return NULL;

	//if(iterador->corriente)
	return iterador->corriente->elemento;

}

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador){
	if(iterador)
		free(iterador);
}

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
 * la misma. Dicha función puede devolver true si se deben seguir recorriendo
 * elementos o false si se debe dejar de iterar elementos.
 *
 * La función retorna la cantidad de elementos iterados o 0 en caso de error.
 */
size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void* elemento, void* contexto), void *contexto){

	if(!lista || !funcion)
		return 0;

	nodo_t* nodo_aux = lista->nodo_inicio;
	bool bandera = true;
	size_t contador = 0;

	while(nodo_aux && bandera){
		bandera = funcion(nodo_aux->elemento, contexto);
		contador++;
		nodo_aux = nodo_aux->siguiente;
	}

	return contador;
}