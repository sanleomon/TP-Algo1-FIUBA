#include "papeleo.h"
#include "dia_en_la_uni.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]){
    char personaje_obtenido = hacer_cuestionario();
    srand ((unsigned)time(NULL));
    juego_t juego;
    juego.nivel_actual = 0;
    inicializar_juego(&juego, personaje_obtenido);
    imprimir_terreno(juego);
    while (estado_juego(juego) == 0){
        realizar_jugada(&juego);
        imprimir_terreno(juego);
    }
    if (estado_juego(juego) == 1){
        printf("Ganaste\n");
    } else{
        printf("Perdiste");
    }
    
    return 0;
}