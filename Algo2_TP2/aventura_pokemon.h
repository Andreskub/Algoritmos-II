#ifndef __AVENTURA_POKEMON__
#define __AVENTURA_POKEMON__

"%100[^;];%i;%i;%50[^\n]\n"
#define FORMATO_PRELECTURA 
#define FORMATO_LECTURA_GIMANSIO
#define FORMATO_LECTURA_ENTRENADOR ";%50[^;];%i;%i;%i\n"

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
    //Algo++
}gimnasio_t;

gimnasio_t* crear_gimnasio(const char* ruta_archivo);

entrenador_t* crear_entrenador();

#endif /* __AVENTURA_POKEMON__ */