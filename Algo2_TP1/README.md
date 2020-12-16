# Gran Pesca Pokemón
## *Algoritmos y Programación II - FIUBA - Cátedra Méndez* 
## Autor: Andrés Kübler

## **1. Introducción**
Los pokémon son unas criaturas que se encuentran en la naturaleza. Se clasifican en 18 tipos (planta, fuego, agua,
volador, tierra, etc). Cada pokémon tiene una cantidad determinada de movimientos o ataques que puede aprender, los
cuales se pueden clasificar por su tipo o elemento (por ejemplo, el ataque rayo burbuja es un ataque tipo agua). Además,
los pokémon cuentan con diferentes atributos que los distinguen de otros pokémon de la misma especie: Velocidad, Color,
Peso, entre otros.
Los entrenadores pokémon, tienen como meta cumplir dos objetivos: capturar a todas las especies de pokémon dis-
ponibles y completar así la información de todos los pokémon en la Pokédex (Enciclopedia Pokémon). Por otro lado,
deben entrenarlos y enfrentarlos a pokémones pertenecientes a otros entrenadores para demostrar sus habilidades,
fortalezas, talentos y así convertirse en un Maestro Pokémon.
Para cumplir la primer meta, los entrenadores viajan a lo largo y ancho de las regiones del mundo, capturando los
diferentes pokémon que encuentran en su camino. Hoy los entrenadores se encontrarán con la oportunidad de capturar
pokémon de tipo agua de una manera distinta a la usual...
## **2. Objetivo**
El presente trabajo tiene como finalidad que el alumno repase algunos de los conocimientos adquiridos en Algoritmos y
Programación I, así como también que comience a familiarizarse con las herramientas a utilizar a lo largo de la materia,
tales como el manejo de memoria dinámica y la utilización de punteros a funciones.
## **3. Enunciado**
La líder de gimnasio Misty organizó un evento de pesca que se llevará a cabo en su acuario, ubicado en Ciudad Celeste.
Para ello necesitará muchos y muy variados pokémon de tipo agua. El lugar indicado en Kanto para obtener a todos
estos pokémon es el arrecife que rodea a las Islas Espuma.
Para realizarlo, te pide que la ayudes a trasladar los pokémon seleccionados desde el arrecife a su acuario, donde será
realizado el evento.
A Misty le preocupa perjudicar la población de las especies más vulnerables, es por ello que te pide realizar una simulación
del arrecife, pudiendo ver como quedará su estado dependiendo de qué especies se elijan para el evento.
## **4. Archivos**
El trabajo practico consiste en la entrega de los siguientes archivos:
- evento_pesca.h
- evento_pesca.c
- main.c
- arrecife.txt
- Enunciado_TP1_EventodePesca.pdf
- README.md
## **5. Resultado esperado**
Se espera que el trabajo creado sea compilado sin errores con la siguiente línea:
```
gcc *.c -Wall -Werror -Wconversion -std=c99 -o evento_pesca
```
Y, ser corrido con valgrind:
```
valgrind --leak -check=full --track -origins=yes --show -reachable=yes ./evento_pesca
```
## **6. Ejercitación**
Explique brevemente y de forma concisa los siguientes conceptos:
1. Punteros
> Un **puntero** es una variable que contiene la direccion de memoria de un dato o de otra variable, es decir, que el puntero apunta al espacio fisico donde esta ese dato o variable.
2. Aritmética de punteros
>La **aritmética de punteros** se limita a suma, resta, comparación y asignación. Las operaciones aritméticas en los punteros de tipoX tienen automáticamente en cuenta el tamaño real de tipoX. Es decir, el número de bytes necesario para almacenar un objeto tipoX. Los operadores más utilizados con punteros son:
>- **Operador de Dirección [&]:** Este permite acceder a la dirección de memoria de una variable.
>- **Operador de Indirección [*]:** Además de que permite declarar un tipo de dato puntero, también permite ver el VALOR que está en la dirección asignada.
>- **Incrementos [++] y Decrementos [–]:** Se puede usar un puntero como si de un array se tratase, por eso mismo permite estos operadores.
3. Punteros a funciones
>Un **puntero a una función** no es más que la dirección de memoria donde reside una determinada función en un programa en C. Además permite ejecutar a la función desde cualquier parte del programa. Los punteros a funciones en C pueden:
>- ser elementos de un vector.
>- ser pasados como parámetros a una función.
>- ser devueltos por una función.
4. Malloc y Realloc
>- La función **malloc()** reserva size bytes y devuelve un puntero a la memoria reservada. La memoria no está inicializada. Si el valor de size es 0 ésta puede devolver, NULL o un valor a un puntero ùnico que posteriormente podrá ser pasado a la función free() para ser liberado.
>- La función **realloc()** modifica el tamaño del bloque de memoria apuntado por *ptr* en size bytes. El contenido del bloque de memoria permanecerá sin cambios desde el inicio del mismo hasta el m´ınino entre el viejo y nuevo tamaño. Si el nuevo tamaño del bloque es mayor que el tamaño anterior, la memoria añadida no se encuentra inicializada en ningùn valor. Si *ptr* es NULL, entonces la llamada es equivalente a malloc(size) para cualquier valor de size. Si size es cero y *ptr* no es NULL entonces la llamada es equivalente a free(ptr).