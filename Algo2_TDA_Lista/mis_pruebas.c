#include "lista.h"
#include "pa2mm.h"

#include "lista.h"
#include <stdio.h>

void pruebas_lista_invalida(lista_t* lista){
	
	int elemento_prueba = 100;

	pa2m_afirmar(lista_insertar(lista, &elemento_prueba) == -1, "Insertar elemento en una lista invalida devuelve ERROR");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento_prueba, 1) == -1, "Insertar elemento arbitrario en una lista invalida devuelve ERROR ");
	pa2m_afirmar(lista_borrar(lista) == -1,"Borrar el ultimo elemento de una lista invalida devuelve ERROR");
	pa2m_afirmar(lista_borrar_de_posicion(lista, 1) == -1,"Borrar elemento arbitrario de una lista invalida devuelve ERROR");
	pa2m_afirmar(lista_vacia(lista) == true, "Una lista invalida es vacia")
	pa2m_afirmar(lista_elementos(lista) == 0, "Una lista invalida posee 0 elementos")	
}

lista_t* pruebas_lista(lista_t* lista){

	pa2m_afirmar((lista = lista_crear()) != NULL, "Puede crear una lista vacia");
	pa2m_afirmar(lista->nodo_inicio == NULL && lista->nodo_fin == NULL, "Nodo Inicio y Nodo Fin se inicializan en NULL");
	pa2m_afirmar(lista->cantidad == 0, "La cantidad de elementos de la lista se inicializa en 0");

	return lista;
}

lista_t* pruebas_insercion_lista(lista_t* lista){
	int elem1 = 50, elem2 = 150, elem3 = 250, elem4 = 350;

	pa2m_afirmar(lista_insertar(lista, &elem1) == 0, "Se pudo insertar el primer elemento" );
	pa2m_afirmar(lista->cantidad == 1, "La lista tienen 1 elemento");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &elem2, 0) == 0, "Se pudo insertar un elemento en la posicion 0")
	pa2m_afirmar(lista->cantidad == 2, "La lista ahora tiene 2 elementos");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &elem3, 100) == 0, "se pudo insertar un elemento en la posicion 100");
	pa2m_afirmar(lista_elementos(lista) == 3, "La lista ahora tiene 3 elementos");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &elem4, 1) == 0, "Se pudo insertar un elemento en la posicion 1")
	pa2m_afirmar(lista_elementos(lista) == 4, "La lista ahora tiene 4 elementos");

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &elem2, "El primer elemento es el correcto");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &elem4, "El segundo elemento es el correcto");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == &elem1, "El tercer elemento es el correcto");
	pa2m_afirmar(lista_ultimo(lista) == &elem3, "El ultimo elemento es el correcto");

	return lista;
}

lista_t* prueba_lista_borrado(lista_t* lista){

	pa2m_afirmar(lista_borrar(lista) == 0, "Se puedo borrar el ultimo elemento de la lista")
	pa2m_afirmar(lista_borrar_de_posicion(lista, 1) == 0, "se pudo borrar un elemento del medio de la lista");
	pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == 0, "se pudo borrar el primer elemento");
	pa2m_afirmar(lista_elementos(lista) == 1, "La cantidad de elementos en la lista es la correcta");

	return lista;
}

void pruebas_lista_pila(){
	lista_t* pila = lista_crear();

	int elem1 = 5, elem2 = 10;
	
	pa2m_afirmar(lista_apilar(pila, &elem1) == 0, "Se pudo apilar el primer elemento");
	pa2m_afirmar(lista_apilar(pila, &elem2) == 0, "Se pudo apilar el segundo elemento");
	pa2m_afirmar(lista_tope(pila) == &elem2, "El tope de la pila es el esperado");
	pa2m_afirmar(lista_desapilar(pila) == 0, "Se pudo desapilar el elemento");
	pa2m_afirmar(lista_desapilar(pila) == 0, "Se pudo desapilar el elemento");

	lista_destruir(pila);
}

void pruebas_lista_cola(){
	lista_t* cola = lista_crear();
	int elem1 = 25, elem2 = 50, elem3 = 75;

	pa2m_afirmar(lista_encolar(cola, &elem1) == 0, "Se pudo encolar el elemento");
	pa2m_afirmar(lista_tope(cola) == &elem1, "El tope de la cola es el esperado");
	pa2m_afirmar(lista_encolar(cola, &elem2) == 0, "Se pudo encolar el elemento");
	pa2m_afirmar(lista_tope(cola) == &elem2, "El tope de la cola es el esperado");
	pa2m_afirmar(lista_desencolar(cola) == 0, "Se pudo desenclar el elemento");
	pa2m_afirmar(lista_tope(cola) == &elem2, "El tope de la cola es el esperado");


	lista_destruir(cola);
}

void pruebas_iterador_externo(){
	lista_t* lista = lista_crear();
	lista_iterador_t* iterador = NULL;

	pa2m_afirmar((iterador = lista_iterador_crear(lista)) != NULL, "Se puede crear un iterador con una lista vacia");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == false, "El iterador de una lista vacia no tiene siguiente");
	pa2m_afirmar(lista_iterador_elemento_actual(iterador) == NULL, "El iterador con una lista vacia no posee elemento actual");
	pa2m_afirmar(lista_iterador_avanzar(iterador) == false, "El iterador de una lista vacia no puede avanzar");
	
	int elem1 = 15, elem2 = 30, elem3 = 45;
	lista_insertar(lista, &elem1);
	lista_insertar(lista, &elem2);
	lista_insertar(lista, &elem3);
	
	//Hasta aca llegue, perdon

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

int main(){
	lista_t* lista = NULL;
	pa2m_nuevo_grupo("PRUEBAS LISTA INVALIDA");
	pruebas_lista_invalida(lista);

	pa2m_nuevo_grupo("PRUEBAS LISTA");
	lista = pruebas_lista(lista);

	pa2m_nuevo_grupo("PRUEBAS LISTA INSERCION");
	lista = pruebas_insercion_lista(lista);

	pa2m_nuevo_grupo("PRUEBAS LISTA BORRAR");
	lista = prueba_lista_borrado(lista);

	lista_destruir(lista);

	pa2m_nuevo_grupo("PRUEBAS LISTA COMO PILA");
	pruebas_lista_pila();

	pa2m_nuevo_grupo("PRUEBAS LISTA COMO COLA");
	pruebas_lista_cola();

	pa2m_nuevo_grupo("PRUEBAS ITERADOR EXTERNO");
	pruebas_iterador_externo(); // Sin terminar :(

	//pa2m_nuevo_grupo("PRUEBAS ITERADOR INTERNO");

	printf("\n");
	return 0;
}
