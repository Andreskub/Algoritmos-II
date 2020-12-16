# Algoritmos y Programacion - TDA Lista

## *Autor: Andrés Kübler* 

## **Enunciado**
Un Readme.txt que contenga una primera sección, en donde se deberá explicar qué es lo entregado, como compilarlo (línea de compilación), como ejecutarlo (línea de ejecución) y el funcionamiento particular de la implementación elegida(no es necesario detallar función por función, solamente explicar como funciona el código) y por qué se eligió dicha implementación. En una segunda sección, se deberán desarrollar los siguientes conceptos teóricos:
1. ¿Qué es lo que entendés por una lista? ¿Cuáles son las diferencias entre ser simple o doblemente enlazada?
2. ¿Cuáles son las características fundamentales de las Pilas? ¿Y de las Colas?
3. ¿Qué es un iterador? ¿Cuál es su función?
4. ¿En qué se diferencia un iterador interno de uno externo?

## **Devolución** 
El trabajo practico consiste en la entrega de los siguientes archivos:
- lista.h
- lista.c
- pa2mm.h
- mis_pruebas.c
- lista_minipruebas.c
- tda_lista.pdf
- README.md

### *Linea de compilación:*
```
$ gcc -g *.c -o main
```
### *Linea de ejecución:*
```
$ valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./main
```

## Funcionamiento del programa:
El funcionamiento consisite en la creacion de una lista simplemente enlazada mediante nodos, con la cual vamos a realizar varias pruebas de insercion, borrado, listado, etc. Esta lista tambien va a hacer puesta a prueba como concepto de PILA y como COLA. Ademas crearemos y utilizaremos iteradores (uno externo y otro interno) para iterar sobre la misma en algunas pruebas.

1. Una lista es una estructura utilizada para almacenar datos y poder acceder sencillamente a los mismos. Una lista simplemente enlazada es la cual el nodo recorrido solo posee la direccion de memoria del siguiente nodo, mientras que la doblemente enlazada el nodo recorrido posee la direccion de memoria de su nodo anterior y del siguiente.
2. La caracteristica principal de una pila es el LIFO (Last In First Out) mientras que el de la cola es de FIFO(Firs In First Out). 
3. Un iterador es un puntero y su funcion es la de referenciar cierto contenido dentro del nodo recorrido.
4. Al iterador externo necesitamos nosotros referenciarlo al siguiente elemento (lo controlamos nosotros), mientras que al iteador interno una vez que lo llamamos ya recorrio toda la lista (recorre solo y nosotros utilizamos su output).
