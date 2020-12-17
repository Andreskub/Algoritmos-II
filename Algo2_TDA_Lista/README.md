# TDA Lista
## *Algoritmos y Programación II - FIUBA - Cátedra Méndez* 
### Autor: Andrés Kübler
#

## **1. Enunciado**
Se pide implementar una Lista simplemente enlazada. Para ello se brindan las firmas de las funciones públicas a implementar y se deja a criterio del alumno la creación de las funciones privadas del TDA para el correcto funcionamiento de la Lista cumpliendo con las buenas prácticas de programación.
<br> Dentro de este TDA, se pide incluir también la implementación de las funciones básicas de los TDAs Pila y Cola, cumpliendo así que este satisfaga el comportamiento de las tres estructuras. 
<br>Adicionalmente se pide la creación de un iterador interno y uno externo para la lista.

## **2. Archivos** 
El trabajo practico consiste en la entrega de los siguientes archivos:
- lista.h
- lista.c
- pa2mm.h
- mis_pruebas.c
- lista_minipruebas.c
- tda_lista.pdf
- README.md

## **3. Resultado esperado**
El TDA entregado deberá compilar y pasar las pruebas dispuestas por la cátedra sin errores, adicionalmente estas pruebas deberán ser ejecutadas sin pérdida de memoria.

### *Linea de compilación:*
```
$ gcc *.c -o lista_se -g -std=c99 -Wall -Wconversion -Wtype -limits -pedantic -Werror -O0
```
### *Linea de ejecución:*
```
$ valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se
```

## **4. Ejercitación**
Un Readme.txt que contenga una primera sección, en donde se deberá explicar qué es lo entregado, como compilarlo (línea de compilación), como ejecutarlo (línea de  ejecución) y el funcionamiento particular de la implementación elegida(no es necesario detallar función por función, solamente explicar como funciona el código) y por qué se eligió dicha implementación. 
>El funcionamiento consisite en la creacion de una lista simplemente enlazada mediante nodos, con la cual vamos a realizar varias pruebas de insercion, borrado, listado, etc. Esta lista tambien va a hacer puesta a prueba como concepto de PILA y como COLA. Ademas crearemos y utilizaremos iteradores (uno externo y otro interno) para iterar sobre la misma en algunas pruebas.

En una segunda sección, se deberán desarrollar los siguientes conceptos teóricos:
1. ¿Qué es lo que entendés por una lista? ¿Cuáles son las diferencias entre ser simple o doblemente enlazada?
>1. Una **lista** es una estructura utilizada para almacenar datos y poder acceder sencillamente a los mismos. Una **lista simplemente enlazada** es la cual el nodo recorrido solo posee la direccion de memoria del siguiente nodo, mientras que en la **lista doblemente enlazada** el nodo recorrido posee la direccion de memoria de su nodo anterior y del siguiente.

2. ¿Cuáles son las características fundamentales de las Pilas? ¿Y de las Colas?
>2. La caracteristica principal de una **pila** es el *LIFO* (Last In First Out) mientras que el de la **cola** es de *FIFO* (Firs In First Out). 

3. ¿Qué es un iterador? ¿Cuál es su función?
>3. Un **iterador** es un puntero y su funcion es la de referenciar cierto contenido dentro del nodo recorrido.

4. ¿En qué se diferencia un iterador interno de uno externo?
>Al **iterador externo** necesitamos nosotros referenciarlo al siguiente elemento (lo controlamos nosotros), mientras que al **iteador interno** una vez que lo llamamos ya recorrio toda la lista (recorre solo y nosotros utilizamos su output).







