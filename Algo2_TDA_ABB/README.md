# TDA Arbol Binario de Busqueda (ABB)
## *Algoritmos y Programación II - FIUBA - Cátedra Méndez* 
### Autor: Andrés Kübler
#

## **1. Enunciado**
Se pide implementar un Arbol Binario de Búsqueda. Para ello se brindan las firmas de las funciones públicas a implementar y se deja a criterio del alumno la creación de las funciones privadas del TDA para el correcto funcionamiento del Arbol cumpliendo con las buenas prácticas de programación.
<br>Adicionalmente se pide la implementación de un iterador interno para la estructura.

## **2. Archivos** 
El trabajo practico consiste en la entrega de los siguientes archivos:
- abb.h
- abb.c
- pa2mm.h
- mis_pruebas.c
- abb_minipruebas.c
- abb_enunciado.pdf
- README.md

## **3. Resultado esperado**
El TDA entregado deberá compilar y pasar las pruebas dispuestas por la cátedra sin errores, adicionalmente estas pruebas deberán ser ejecutadas sin pérdida de memoria.

### *Linea de compilación:*
```
$ gcc *.c -o abb -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
```
### *Linea de ejecución:*
```
$ valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb
```

## **4. Ejercitación**
Un Readme.txt donde se deberá explicar qué es lo entregado, como compilarlo (línea de compilación), como ejecutarlo (línea de ejecución) y todo lo que crea necesario aclarar. 
>El funcionamiento consisite en la creacion de un Árbol Binario de Busqueda mediante nodos, con el cual vamos a realizar varias pruebas de busqueda, insercion, borrado, recorrido, etc. Ademas crearemos y utilizaremos un iterador interno para iterar(recorrer) sobre el mismo en algunas pruebas.

Adicionalmente el archivo debe poseer una sección donde se desarrollen los siguientes conceptos:

1. Explicar qué es un ABB y cómo se diferencia de un Árbol Binario.
>Un **árbol binario** es una estructura de datos formada por nodos. Los nodos son los elementos o vértices del arbol. El **Árbol Binario de Busqueda (ABB)** es un tipo de arbol binario, el cual se relaciona intimamente con las operaciones de busqueda. El mismo se destaca por tener varias formas de recorrerlo, entre las mas importantes: <br>- Preorden: Primero se visita en nodo actual luego el sub-arbol izquierdo y luego el derecho. <br> - Inorden: Primero se visita el sub-arbol izquierdo, luego el nodo actual y por último el sub-arbol derecho <br> - Postorden: Primero se visita el sub-arbol izquierdo, luego al sub-arbol derecho y por último al nodo actual.

2. Explicar cuál es el objetivo de tener una función de destrucción en el TDA y qué  implicaría para el usuario no tenerla.
>El objetivo es simplificar el manejo del TDA y a su vez las operaciones del usuario. Además, nos aseguramos que la memoria pedida (heap) sea correctamente liberada. De no tener esta posibilidad, al usuario se le complicaria la eliminacion de nodos, ya que deberia elliminarlos uno por uno manualmente.

3. ¿Cuál es la complejidad de las diferentes operaciones del ABB? Justifique.
>**Busqueda - O(log(n))**<br>En la busqueda, se va comparando el nodo actual con el que estamos buscando, y si no coincide se procede a su nodo hijo correspondiente. El acceso a un dato es proporcional a la altura del árbol, ya que su ubicación podría ser, en el peor de los casos, en una hoja. Por lo tanto, es deseable que el ABB tenga la menor altura posible <br> **Inserción - O(log(n))**<br> La inserción es similar a la búsqueda. Si tenemos inicialmente como parámetro un árbol vacío se crea un nuevo nodo raizy se insertar. Si no lo está, se comprueba si el elemento dado es menor que la raíz del árbol inicial con lo que se inserta en el subárbol izquierdo y si es mayor se inserta en el subárbol derecho.  <br>**Borrado - O(logn(n))** <br> La operación de borrado no es tan sencilla como las de búsqueda e inserción. Existen 3 casos posibles: <br>- El nodo no tenga hijos: simplemente se borra y se establece a nulo el apuntador de su padre. <br>- El  nodo tenga 1 nodo hijo: se borra el nodo y se asigna su subárbol hijo como subárbol de su padre. <br>- El nodo tenga 2 nodos hijos: se reemplaza el nodo a eliminar con el nodo de menor valor del subarbol derecho (sucesor inorden), dejando en lugar al hijo (si tiene, a lo sumo puede tener un hijo).