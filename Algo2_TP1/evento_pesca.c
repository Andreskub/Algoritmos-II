#include "evento_pesca.h"

#include <stdlib.h>
#include <string.h>

#define FORMATO_LECTURA "%100[^;];%i;%i;%50[^\n]\n"
#define FORMATO_ESCRITURA "%s;%i;%i;%s\n" 

//Funcion que agrega el pokemon recorrido al arrecife
//INPUT: struct pointer arrecife; struct pokemon/OUTPUT: struct arrecife
arrecife_t* agregar_pokemon_recorrido(arrecife_t *arrecife, pokemon_t pokemon_recorrido){
	
	if (arrecife->cantidad_pokemon >= 0){
		//Extiende el espacio de memoria
		void* aux = realloc(arrecife->pokemon, (size_t)(arrecife->cantidad_pokemon + 1) * sizeof(pokemon_t));
		//Verifica que no falle el realloc
		if (!aux)
			return NULL;
		
		arrecife->pokemon = aux;
		
	}

	//Le asigna los valores 
	arrecife->pokemon[arrecife->cantidad_pokemon] = pokemon_recorrido;

	//Suma un pokemon al total de pokemones en el arrecife
	arrecife->cantidad_pokemon++;

	return arrecife;
}

//Funcion que crea un struct de arrecife  y lo llena a partir de un archivo de texto
//INPUT: cont char/OUTPUT: struct arrecife
arrecife_t* crear_arrecife(const char* ruta_archivo){

	//Si no es el primer pokemon del arrecife
	FILE* info_pokemons_arrecife = fopen(ruta_archivo,"r");
	//Verifica que no me devuelva NULL, de ser asi devuelvo error
	if(!info_pokemons_arrecife)
   		return NULL;

	//Crea un puntero a un espacio de memoria (que tambien pido)
	arrecife_t* arrecife = malloc( sizeof(arrecife_t) );
	//Verifica si falla el malloc
	if(!arrecife){
		fclose(info_pokemons_arrecife);
		return NULL;
	}

	//Pide memoria para el pokemo n
	arrecife->pokemon = malloc( sizeof(pokemon_t) );
	//Verifica si falla el malloc
	if(!arrecife->pokemon){
		fclose(info_pokemons_arrecife);
		free(arrecife);
		return NULL;
	}

	//Inicializa el contador total de pokemones en 0
	arrecife->cantidad_pokemon = 0;

	//Declara un struct donde va a ir guardando los datos que lee
	pokemon_t pokemon_recorrido;
	//Lee la primera linea del archivo
	int leer_linea = fscanf(info_pokemons_arrecife, FORMATO_LECTURA, pokemon_recorrido.especie, &(pokemon_recorrido.velocidad), &(pokemon_recorrido.peso), pokemon_recorrido.color);

	if (leer_linea != 4){
		liberar_arrecife(arrecife);
		fclose(info_pokemons_arrecife);
		return NULL;
	}

	//Recorre las lineas del archivo
	while(leer_linea == 4){
		//Agrega pokemon al array de pokemones
		arrecife = agregar_pokemon_recorrido(arrecife, pokemon_recorrido);
		//Lee la n linea del archivo
		leer_linea = fscanf(info_pokemons_arrecife, FORMATO_LECTURA, pokemon_recorrido.especie, &(pokemon_recorrido.velocidad), &(pokemon_recorrido.peso), pokemon_recorrido.color);		
	}

	//Cierra el archivo
	fclose(info_pokemons_arrecife);

	return arrecife;
}

//Funcion que crea un struct acuario vacio
//INPUT None:/OUTPUT: struct acuario
acuario_t* crear_acuario(){
	//Crea una variable puntero
	acuario_t* acuario = malloc( sizeof(acuario_t) );
	//Verifica que no falle el malloc
	if (!acuario)
		return NULL;

	acuario->pokemon = malloc( sizeof(pokemon_t) );
	//Verifica que no falle el malloc
	if (!acuario->pokemon)
		return NULL;

	//Inicializa la cantidad total de pokemones en el acuario en 0
	acuario->cantidad_pokemon = 0;

	return acuario;
}

//Funcion que agrega un pokemon que no existe al acuario
//INPUT: struct pointer acuario; struct pokemon/OUTPUT: struct acuario
acuario_t* agregar_pokemon_al_acuario(acuario_t *acuario, pokemon_t pokemon_para_agregar){
	//Si no es el primer pokemon del acuario
	if (acuario->cantidad_pokemon > 0){
		//Extiende el espacio de memoria
		void* aux_acuario = realloc(acuario->pokemon, (size_t)(acuario->cantidad_pokemon + 1) * sizeof(pokemon_t));
		//Verifica que no falle el realloc
		if (!aux_acuario)
			return NULL;
		//Iguala el vector del realloc al que ya tenia
		acuario->pokemon = aux_acuario;
	}

	//Le asigna los valores 
	acuario->pokemon[acuario->cantidad_pokemon] = pokemon_para_agregar;
	//Incrementa la cantidad total de pokemones en el acuario en 1
	acuario->cantidad_pokemon++;

	return acuario;
}

//Funcion que elimina un pokemon del arrecife 
//INPUT: struct pointer arrecife; entero posicion/OUTPUT: struct arrecife
arrecife_t* eliminar_pokemon_del_arrecife(arrecife_t* arrecife, int pos_pokemon){

	//Reacomoda la lista sin el pokemon actual a trasladar
	while(pos_pokemon < ((arrecife->cantidad_pokemon)-1) ){
		arrecife->pokemon[pos_pokemon] = arrecife->pokemon[pos_pokemon+1];
		pos_pokemon++;
	}

	//Mientras existan mas de un pokemon en el arrecife
	if (arrecife->cantidad_pokemon > 1){
		//Achico el espacio de memoria
		void* aux_arrecife = realloc(arrecife->pokemon, (size_t)(arrecife->cantidad_pokemon - 1) * sizeof(pokemon_t));
		//Verifica que no falle el realloc
		if (!aux_arrecife)
			return NULL;
				
		arrecife->pokemon = aux_arrecife;
	}

	//Resta 1 a la cantidad total de pokemones en el arrecife
	arrecife->cantidad_pokemon--;

	return arrecife;
}

//Funcion que verifica si existen los pokemones necesarios que cumplan con la condicion pedida y
//lo/los traslada del arrecife al acuario
//INPUT: struct pointer arrecife, struct pointer acuario; funcion tipo bool; entero cantidad/OUTPUT: entero
int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){
	//Verifica que los datos pasados son correctos
	if (!arrecife || !acuario || cant_seleccion < 0 || arrecife->cantidad_pokemon < cant_seleccion){
		return -1;
	} else if (cant_seleccion == 0){
		return 0;
	}
	
	//Define un vector donde me voy a guardar las posiciones (del pokemon en el arrecife) que cumplan con la condicion
	int vector_posiciones_pokemones_a_trasladar[cant_seleccion];
	//Inicializa contadores
	int cont_pokemones_validados = 0;
	int pos_pokemon_recorrido = 0;
	while (cont_pokemones_validados < cant_seleccion && arrecife->cantidad_pokemon != pos_pokemon_recorrido){
		//Verifica si el pokemon recorrido pasa las pruebas
		if (seleccionar_pokemon(arrecife->pokemon+pos_pokemon_recorrido)){
			//Guarda la posicion del pokemon recorrido en el arrecife en el vector
			vector_posiciones_pokemones_a_trasladar[cont_pokemones_validados] = pos_pokemon_recorrido;
			//Incrementa el valor de los pokemones validos en 1
			cont_pokemones_validados++;
		}
		//Incrementa la posicion del pokemon recorrido en 1
		pos_pokemon_recorrido++;
	}

	//Verifica que existan la suficiente cantidad de pokemones para trasladar
	if (cont_pokemones_validados < cant_seleccion){
		return -1;
	}

	//Recorre los n pokemones a trasladar
	for (int i = 0; i < cont_pokemones_validados; i++){
		//Agrega pokemon recorrido al acuario
		acuario = agregar_pokemon_al_acuario(acuario, arrecife->pokemon[vector_posiciones_pokemones_a_trasladar[i]-i]);
		
		//Elimina el pokemon recorrido del arrecife
		arrecife = eliminar_pokemon_del_arrecife(arrecife, vector_posiciones_pokemones_a_trasladar[i]-i);
	}
	
	return 0;

}

//Funcion que imprime los pokemones en el arrecife por pantalla mediante la funcion pasada por parametro
//INPUT:struct pointer arrecife; funcion void/OUTPUT: None
void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){
	//Si existe el arrecife (distinto de NULL)
	if (arrecife){
		//Declara contador de posicion
		int posicion = 0;
		printf("\n");
		//Recorre el vector pokemones y lo va imprimiendo
	    while(posicion < arrecife->cantidad_pokemon){
	    	//Imprime el pokemon recorrido
	        mostrar_pokemon(arrecife->pokemon+posicion);
	        //Incrementa en 1 el contador
	        posicion++;
	    }
	}
}

//Funcion que recibe un acuario y guarda los pokemones del mismo en un archivo .txt
//INPUT:struct puntero acuario; char archivo/OUTPUT:entero
int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){
	//Abre el archivo
	FILE* guardar_pokemones = fopen(nombre_archivo,"w");
	//Verifica que no devuelva NULL, de ser asi devuelve -1
	if(!guardar_pokemones)
   		return -1;

   	//Declara un contador posicion
	int i = 0;
	//Cicla los pokemones hasta quedarse sin
	while(i < acuario->cantidad_pokemon){
		//Imprime el pokemon y sus caracteristicas en el .txt
		fprintf(guardar_pokemones, FORMATO_ESCRITURA, acuario->pokemon[i].especie, acuario->pokemon[i].velocidad, acuario->pokemon[i].peso, acuario->pokemon[i].color);
		//Incrementa la posicion en 1
		i++;
	}

	//Cierra el archivo
	fclose(guardar_pokemones);
	//Si todo salio OK, retorna 0
	return 0;
}

//Funcion que libera la memoria reservada del acuario
//INPUT:struct puntero acuario/OUTPUT: None
void liberar_acuario(acuario_t* acuario){
	//Primero libera el vector que contiene a los structs pokemon dento del struct acuario
	if (acuario->pokemon != NULL)
		free(acuario->pokemon);

	//Luego libera el struct acuario
	if(acuario != NULL)
		free(acuario);
}

//Funcion que libera la memoria reservada del arrecife
//INPUT:struct puntero arrecife/OUTPUT: None
void liberar_arrecife(arrecife_t* arrecife){
	//Primero libera el vector que contiene a los structs pokemon dentro del struct arrecife
	if(arrecife->pokemon != NULL)
		free(arrecife->pokemon);

	//Luego libera el struct arrecife
	if(arrecife != NULL)
		free(arrecife);
}
