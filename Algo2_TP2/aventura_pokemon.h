#ifndef __AVENTURA_POKEMON__
#define __AVENTURA_POKEMON__



#define MAX_NOMBRE 5050

typedef struct pokemon{
    char especie[MAX_NOMBRE];
    int velocidad;
    int defensa;
    int ataque;
}pokemon_t;

typedef struct entrenador{
    char nombre[MAX_NOMBRE];
    //Algo++
}entrenador_t;

typedef struct gimnasio{
    char nombre[MAX_NOMBRE];
    int dificultad;
    int id_puntero_funcion;
    //Algo++
}gimnasio_t;


#endif /* __AVENTURA_POKEMON__ */