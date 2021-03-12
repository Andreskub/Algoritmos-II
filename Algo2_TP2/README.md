# Trabajo practico n2 - Aventura Pokemon
## *Algoritmos y Programación II - FIUBA - Cátedra Méndez* 
### Autor: Andrés Kübler
#

## **1. Objetivo""
El presente trabajo práctico tiene como finalidad que el alumno se familiarice con las diferentes estructuras de datos dinámicas implementadas, aplicándolas a un problema concreto y poniendo en práctica su uso integrado.

## **2. Enunciado**
Los Alto Mando de todas las regiones se han reunido en una asamblea de carácter urgente: Los líderes regionales están notando una preocupante caída de interés por parte de los jóvenes en convertirse en maestros Pokémon. Debido a las nuevas tecnologías, el interés por los nuevos videojuegos ha aumentado rotundamente, con títulos como 'PacMon' y 'Mankey Kong' que han cautivado a miles de niños y niñas en todo el mundo, han provocado que cada día hayan menos
niñxs jugando afuera con los pokémon y comenzando su camino como maestro Pokémon.
<br>Es por esto que te han contactado para que lleves a cabo el primer videojuego de aventura sobre convertirse en maestro pokémon.
<br>El objetivo del videojuego es simular el camino que se realiza para convertirse en maestro Pokémon. Para esto, es necesario obtener todas y cada una de las medallas de la región, comenzando con los gimnasios más sencillos y avanzando hacia los más difíciles.

## **3. Archivos** 
El trabajo practico consiste en la entrega de los siguientes archivos:
- main.c
- aventura_pokemon.h
- aventura_pokemon.c
- obtener_datos_archivo.h
- obtener_datos_archivos.c
- batallas.h
- batallas.c
- logica_batallas.h
- logica_batallas.c
- funciones_imprenta.h
- funciones_imprenta.c
- m_heap.h
- m_heap.c
- m_lista.h
- m_lista.c
- personaje.txt
- gimnasio.txt
- TP2_enunciado.pdf
- README.md

## **3. Resultado esperado**
El Trabajo Practico entregado deberá compilar y ser ejecutado sin pérdida de memoria.

### *Linea de compilación:*
```
$ gcc *.c -o aventura_pokemon -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
```
### *Linea de ejecución:*
```
$ valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./aventura_pokemon
```

## **4. Explicacion del trabajo practico**
El trabajo practico consiste de un videojuego en el cual el objetivo es converirse en *Maestro Pokemon*. El desarrollo del juego se puede dar de dos maneras distintas: simulando o jugando la partida segun el usuario lo desee.
<br>Para comenzar el juego es necesario que el usuario ingrese por teclado el nombre de los archivos de texto *(.txt)* donde se encontrara almacenado tanto el personaje principal *(personaje.txt)* y el/los gimnasios *(gimnasios.txt)*. Con la lectura de estos archivos se crean las estructuras a utilizar: 

1) - juego_t
>Esta estructura es la principal del juego, en ella se encuentra un heap_t que contiene los gimnasios leidos del archivo .txt y un personaje_t, tambien leido de otro archivo .txt, que corresponde al personaje principal del juego.

2) - personaje_t
>Esta estructura corresponde al personaje principal del juego. Esta compuesta por:
> - su nombre.
> - un vector dinamico puntero puntero de tipo pokemon_t, el cual corresponde a los pokemones de combate *(o Party)*. Estos punteros apuntan a los pokemones obtenidos del jugador *(o Caja)*, que se encuentran en una lista. Se ultilizo un puntero dinamico ya que es mas facil y comodo acceder a sus valores(pokemones).
> - un punero a una lista de tipo COLA, donde se almacenan como elementos de lista todos los pokemones obtenidos por el jugador. La razon de ultilizar una Cola para almacenar los elementos es que facilita los enfrentamientos de sus pokemones, siendo asi el primero de la cola el primero en batallar, donde los entrenadores suelen poner sus mejores pokemones al frente de la batalla.
> - un contador de la cantidad de pokemones obtenidos.

3) - heap_t
>Esta estructura corresponde a un heap de gimnasios, es decir donde se almacenan los gimnasios leidos del archivo de texto. El heap corresponde a un heap minimal, donde el gimnasio con menor nivel corresponde a la raiz del heap. La razon del uso del **TDA Heap** para almacenar los gimnasios es que su estructura nos facilita hallar y extraer el gimnasio "mas debil" (que se encuentra en el nodo_raiz), ya que el juego comienza enfrentando al personaje con el gimnasio mas debil al mas fuerte.

4) - gimnasio_t
>Esta estructura corresponde a un *Gimnasio Pokemon* el cual consiste de:
> - nombre.
> - nivel de dificultad del gimnasio.
> - un puntero a una lista de tipo PILA, donde se almacenan como elementos de lista todos los entrenadores pertenecientes al gimnasio. Siendo el primero el Lider del gimnasio, y el tope el ultimo ingresado. En este caso, se utilizo la estructura de pila debido a que el personaje comienza a combatir a los entrenadores mas debiles primero siendo los mas debiles el tope de la pila, y como estos vienen ordenados de mas fuerte a mas debil en el archivo de texto, al ir recorriendo las lineas del archivo, tambien se nos facilita el guardado de los mismos.
> - un contador de la cantidad total de entrenadores pertenecientes al gimnasio.
> - un id (int) que corresponde al tipo de batalla que se realiza en ese gimnasio.

5) - entrenador_t 
>Esta estructura corresponde a un Entrenador Pokemon, el cual pertenece a un gimnasio, y sus atributos son:
> - nombre
> - un puntero a una lista de tipo COLA, donde se almacenan como elementos de lista todos los pokemones obtenidos por el entrenador. Al igual que el personaje, el uso de una Cola para el almacenamiento de los pokemones es un gran opcion, debido a que los primeros pokemones del entrenador van a corresponder a los mas fuertes y los primeros en luchar. La cola al ser de tipo FIFO (First In First Out), el primero que va a salir a combatir va a corresponder al pokemon mas fuerte del entrenador.
> - un contador de la cantidad total de pokemones pertenecientes al entrenador.
> - un contador de medallas ganadas por el entrenador.

6) - pokemon_t
>Un pokemon posee: nombre, ataque, defensa, velocidad y un contador de victorias.