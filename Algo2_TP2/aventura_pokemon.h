#ifndef __AVENTURA_POKEMON__
#define __AVENTURA_POKEMON__

#define MAX_NOMBRE 50

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
    //Algo++
}gimnasio_t;

gimnasio_t* crear_gimnasio(const char* ruta_archivo);

entrenador_t* crear_entrenador();

#endif /* __AVENTURA_POKEMON__ */