#include "papeleo.h"
#include "dia_en_la_uni.h"
#include <stdlib.h>
#include <time.h>

const char FUEGOS = 'F';
const char MEDIAS = 'M';
const char BOTELLA_GRITO = 'G';
const char INTERRUPTOR = 'I';
const char MIKE = 'W';

#define NIVEL_1 0
#define NIVEL_2 1
#define NIVEL_3 2
#define MOVIMIENTOS_EXTRA 10

#define TERRENO_NIVEL_1 22
#define TERRENO_NIVEL_2 17
#define TERRENO_NIVEL_3 12

bool superpone_con_pared(coordenada_t coordenada, coordenada_t* paredes, int tope_paredes){
    int i = 0;
    bool superpuesto = false;
    while (i < tope_paredes && !superpuesto){
        if ((paredes[i].fil == coordenada.fil) && (paredes[i].col == coordenada.col)){
            superpuesto = true;
        }
        i++;
    }
    return superpuesto;
}

bool es_adyacente_a_pared(coordenada_t coordenada, coordenada_t* paredes, int tope_paredes){
    int i = 0;
    bool adyacente = false;
    int distancia_fila = 0;
    int distancia_col = 0;
    int distancia_manhattan = 0;
    while (i < tope_paredes && !adyacente){
        distancia_fila = abs(paredes[i].fil - coordenada.fil);
        distancia_col = abs(paredes[i].col - coordenada.col);
        distancia_manhattan = distancia_fila + distancia_col;
        if (distancia_manhattan == 1){
            adyacente = true;
        }
        i++;
    }
    return adyacente;
}

bool superpone_con_obstaculo(coordenada_t coordenada, objeto_t* obstaculos, int tope_obstaculos){
    int i = 0;
    bool superpuesto = false;
    while (i < tope_obstaculos && !superpuesto){
        if ((obstaculos[i].posicion.fil == coordenada.fil) 
            && (obstaculos[i].posicion.col == coordenada.col)){
            superpuesto = true;
        }
        i++;
    }
    return superpuesto;
}

bool superpone_con_jugador(coordenada_t pos_jugador, coordenada_t coordenada){
    return (pos_jugador.fil == coordenada.fil && pos_jugador.col == coordenada.col);
}

bool superpone_con_herramienta(coordenada_t coordenada, objeto_t* herramientas, 
        int tope_herramientas){
    int i = 0;
    bool superpuesto = false;
    while (i < tope_herramientas && !superpuesto){
        if ((herramientas[i].posicion.fil == coordenada.fil) 
            && (herramientas[i].posicion.col == coordenada.col)){
            superpuesto = true;
        }
        i++;
    }
    return superpuesto;
}

bool superpone_con_papeleo(coordenada_t coordenada, papeleo_t* papeleo, 
        int tope_papeleo){
    int i = 0;
    bool superpuesto = false;
    while (i < tope_papeleo && !superpuesto){
        if ((papeleo[i].posicion.fil == coordenada.fil) 
            && (papeleo[i].posicion.col == coordenada.col)){
            superpuesto = true;
        }
        i++;
    }
    return superpuesto;
}

void generar_fuegos(int cantidad_fuegos, nivel_t* nivel, int tamanio_terreno){
    coordenada_t coordenada;

    for (int i = 0; i < cantidad_fuegos; i++){
        coordenada.fil = rand() % tamanio_terreno + 0;
        coordenada.col = rand() % tamanio_terreno + 0;
        while (superpone_con_pared(coordenada, nivel->paredes, nivel->tope_paredes) 
        || !es_adyacente_a_pared(coordenada, nivel->paredes, nivel->tope_paredes)
        || superpone_con_obstaculo(coordenada, nivel->obstaculos, nivel->tope_obstaculos) 
        || superpone_con_jugador(nivel->pos_inicial_jugador, coordenada)){
            coordenada.fil = rand() % tamanio_terreno + 0;
            coordenada.col = rand() % tamanio_terreno + 0;
        }
        nivel->obstaculos[i].posicion = coordenada;
        nivel->obstaculos[i].tipo = FUEGOS;
        nivel->tope_obstaculos++;
    }
    
}

void generar_medias(int cantidad_medias, nivel_t* nivel, int tamanio_terreno){
    coordenada_t coordenada;
    int indice_inicial = nivel->tope_obstaculos;
    int tope_obstaculos = nivel->tope_obstaculos + cantidad_medias;

    for (int i = indice_inicial; i < tope_obstaculos; i++){
        coordenada.fil = rand() % tamanio_terreno + 0;
        coordenada.col = rand() % tamanio_terreno + 0;
        while (superpone_con_pared(coordenada, nivel->paredes, nivel->tope_paredes) 
        || superpone_con_obstaculo(coordenada, nivel->obstaculos, nivel->tope_obstaculos) 
        || superpone_con_jugador(nivel->pos_inicial_jugador, coordenada)){
            coordenada.fil = rand() % tamanio_terreno + 0;
            coordenada.col = rand() % tamanio_terreno + 0;
        }
        nivel->obstaculos[i].posicion = coordenada;
        nivel->obstaculos[i].tipo = MEDIAS;
        nivel->tope_obstaculos++;
    }
}

void generar_botellas_gritos(int cantidad_botellas, nivel_t* nivel, int tamanio_terreno){
    coordenada_t coordenada;

    for (int i = 0; i < cantidad_botellas; i++){
        coordenada.fil = rand() % tamanio_terreno + 0;
        coordenada.col = rand() % tamanio_terreno + 0;
        while (superpone_con_pared(coordenada, nivel->paredes, nivel->tope_paredes) 
        || superpone_con_obstaculo(coordenada, nivel->obstaculos, nivel->tope_obstaculos) 
        || superpone_con_jugador(nivel->pos_inicial_jugador, coordenada) 
        || superpone_con_herramienta(coordenada, nivel->herramientas, nivel->tope_herramientas)){
            coordenada.fil = rand() % tamanio_terreno + 0;
            coordenada.col = rand() % tamanio_terreno + 0;
        }
        nivel->herramientas[i].posicion = coordenada;
        nivel->herramientas[i].tipo = BOTELLA_GRITO;
        nivel->tope_herramientas++;
    }
}

void generar_interruptores(int cantidad_interruptores, nivel_t* nivel, int tamanio_terreno){
    coordenada_t coordenada;
    int indice_inicial = nivel->tope_herramientas;
    int tope_herramientas = nivel->tope_herramientas + cantidad_interruptores;

    for (int i = indice_inicial; i < tope_herramientas; i++){
        coordenada.fil = rand() % tamanio_terreno + 0;
        coordenada.col = rand() % tamanio_terreno + 0;
        while (superpone_con_pared(coordenada, nivel->paredes, nivel->tope_paredes) 
        || superpone_con_obstaculo(coordenada, nivel->obstaculos, nivel->tope_obstaculos) 
        || superpone_con_jugador(nivel->pos_inicial_jugador, coordenada) 
        || superpone_con_herramienta(coordenada, nivel->herramientas, nivel->tope_herramientas)){
            coordenada.fil = rand() % tamanio_terreno + 0;
            coordenada.col = rand() % tamanio_terreno + 0;
        }
        nivel->herramientas[i].posicion = coordenada;
        nivel->herramientas[i].tipo = INTERRUPTOR;
        nivel->tope_herramientas++;
    }
}

void generar_herramientas(nivel_t* nivel, int numero_nivel, int tamanio_terreno){
    if (numero_nivel == 1){
        nivel->tope_herramientas = 0;
        generar_botellas_gritos(4, nivel, tamanio_terreno);
        generar_interruptores(1, nivel, tamanio_terreno);
    } else if (numero_nivel == 2){
        nivel->tope_herramientas = 0;
        generar_botellas_gritos(3, nivel, tamanio_terreno);
        generar_interruptores(1, nivel, tamanio_terreno);
    }else{
        nivel->tope_herramientas = 0;
        generar_botellas_gritos(2, nivel, tamanio_terreno);
        generar_interruptores(0, nivel, tamanio_terreno);
    }
}

void generar_papeleos(nivel_t* nivel, int cantidad_papeleos, int tamanio_terreno){
    nivel->tope_papeleos = 0;
    coordenada_t coordenada;

    for (int i = 0; i < cantidad_papeleos; i++){
        coordenada.fil = rand() % tamanio_terreno + 0;
        coordenada.col = rand() % tamanio_terreno + 0;
        while (superpone_con_pared(coordenada, nivel->paredes, nivel->tope_paredes) 
        || superpone_con_obstaculo(coordenada, nivel->obstaculos, nivel->tope_obstaculos) 
        || superpone_con_jugador(nivel->pos_inicial_jugador, coordenada) 
        || superpone_con_herramienta(coordenada, nivel->herramientas, nivel->tope_herramientas)
        || superpone_con_papeleo(coordenada, nivel->papeleos, nivel->tope_papeleos)){
            coordenada.fil = rand() % tamanio_terreno + 0;
            coordenada.col = rand() % tamanio_terreno + 0;
        }
        nivel->papeleos[i].posicion = coordenada;
        nivel->papeleos[i].id_papeleo = i+1;
        nivel->papeleos[i].recolectado = false;
        nivel->tope_papeleos++;
    }
}

void inicalizar_datos_jugador(jugador_t* jugador, int cantidad_movimientos, int cantidad_martillos, 
    int cantidad_extintores, bool interruptor){
        jugador->movimientos = cantidad_movimientos;
        jugador->martillos = cantidad_martillos;
        jugador->extintores = cantidad_extintores;
        jugador->ahuyenta_randall = interruptor;
}

void inicializar_nivel(nivel_t* nivel, int numero_nivel, char amigo_pide_favor){
    if (numero_nivel == 0){
        
        obtener_paredes(numero_nivel+1, nivel->paredes, 
            &nivel->tope_paredes, &nivel->pos_inicial_jugador);
        
        nivel->tope_obstaculos = 0;
        int cantidad_fuegos = 10;
        int cantidad_medias = 5;
        if (amigo_pide_favor == OLAF){
            generar_fuegos(cantidad_fuegos - 2, nivel, TERRENO_NIVEL_1);
        } else{
            generar_fuegos(cantidad_fuegos, nivel, TERRENO_NIVEL_1);
        }
        generar_medias(cantidad_medias, nivel, TERRENO_NIVEL_1);
        generar_herramientas(nivel, numero_nivel + 1, TERRENO_NIVEL_1);

        int cantidad_papeleos = 2;
        generar_papeleos(nivel, cantidad_papeleos, TERRENO_NIVEL_1);
    } else if (numero_nivel == 1){
        obtener_paredes(numero_nivel + 1, nivel->paredes, 
            &nivel->tope_paredes, &nivel->pos_inicial_jugador);

        nivel->tope_obstaculos = 0;
        int cantidad_fuegos = 5;
        int cantidad_medias = 4;
        if (amigo_pide_favor == OLAF){
            generar_fuegos(cantidad_fuegos - 1, nivel, TERRENO_NIVEL_2);;
        } else{
            generar_fuegos(cantidad_fuegos, nivel, TERRENO_NIVEL_2);;
        }
        generar_medias(cantidad_medias, nivel, TERRENO_NIVEL_2);
        generar_herramientas(nivel, numero_nivel + 1, TERRENO_NIVEL_2);

        int cantidad_papeleos = 3;
        generar_papeleos(nivel, cantidad_papeleos, TERRENO_NIVEL_2);
    }else{
        obtener_paredes(numero_nivel + 1, nivel->paredes, 
            &nivel->tope_paredes, &nivel->pos_inicial_jugador);

        nivel->tope_obstaculos = 0;
        int cantidad_fuegos = 3;
        int cantidad_medias = 3;
        generar_fuegos(cantidad_fuegos, nivel, TERRENO_NIVEL_3);
        generar_medias(cantidad_medias, nivel, TERRENO_NIVEL_3);
        generar_herramientas(nivel, numero_nivel + 1, TERRENO_NIVEL_3);

        int cantidad_papeleos = 4;
        if (amigo_pide_favor == STICH){
            generar_papeleos(nivel, cantidad_papeleos - 1, TERRENO_NIVEL_3);
        }else{
            generar_papeleos(nivel, cantidad_papeleos, TERRENO_NIVEL_3);
        }        
    }
}

void inicializar_juego(juego_t* juego, char amigo_pide_favor){
    juego->personaje_tp1 = amigo_pide_favor;
    int martillos = 4;
    int extintores = 4;
    int movimientos = 40;
    
    if (juego->nivel_actual == NIVEL_1){
        inicalizar_datos_jugador(&juego->jugador, movimientos, 
            martillos, extintores, false);

        if (amigo_pide_favor == JASMIN){
            juego->jugador.martillos+=1;
        }

        if (amigo_pide_favor == RAYO){
           juego->jugador.movimientos +=MOVIMIENTOS_EXTRA; 
        }
        
        inicializar_nivel(&juego->niveles[NIVEL_1], NIVEL_1, amigo_pide_favor);
    } else if (juego->nivel_actual == NIVEL_2){
        inicalizar_datos_jugador(&juego->jugador, movimientos - 10, 
            martillos + 1, extintores - 2, false);

        if (amigo_pide_favor == JASMIN){
            juego->jugador.martillos+=1;
        }
        inicializar_nivel(&juego->niveles[NIVEL_2], NIVEL_2, amigo_pide_favor);
    } else{
        inicalizar_datos_jugador(&juego->jugador, movimientos - 20, 
            martillos + 2, extintores - 2, false);

        if (amigo_pide_favor == JASMIN){
            juego->jugador.martillos+=1;
        }
        inicializar_nivel(&juego->niveles[NIVEL_3], NIVEL_3, amigo_pide_favor);
    }
}

void cargar_paredes(char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1], nivel_t nivel){
    int fil = 0;
    int col = 0;

    for (int i = 0; i < nivel.tope_paredes; i++){
        fil = nivel.paredes[i].fil;
        col = nivel.paredes[i].col;

        terreno[fil][col] = '-';
    }
}

void cargar_posicion_jugador(char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1], 
    coordenada_t posicion_jugador){
        terreno[posicion_jugador.fil][posicion_jugador.col] = MIKE;
}

void cargar_obstaculos(char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1], nivel_t nivel){
    int fil = 0;
    int col = 0;

    for (int i = 0; i < nivel.tope_obstaculos; i++){
        fil = nivel.obstaculos[i].posicion.fil;
        col = nivel.obstaculos[i].posicion.col;

        if (nivel.obstaculos[i].tipo == FUEGOS){
            terreno[fil][col] = FUEGOS;
        }else{
            terreno[fil][col] = MEDIAS;
        }
    }
}

void cargar_herramientas(char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1], nivel_t nivel){
    int fil = 0;
    int col = 0;

    for (int i = 0; i < nivel.tope_herramientas; i++){
        fil = nivel.herramientas[i].posicion.fil;
        col = nivel.herramientas[i].posicion.col;

        if (nivel.herramientas[i].tipo == BOTELLA_GRITO){
            terreno[fil][col] = BOTELLA_GRITO;
        }else{
            terreno[fil][col] = INTERRUPTOR;
        }
    }
}

void cargar_papeleos(char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1], nivel_t nivel){
    int fil = 0;
    int col = 0;

    for (int i = 0; i < nivel.tope_papeleos; i++){
        fil = nivel.papeleos[i].posicion.fil;
        col = nivel.papeleos[i].posicion.col;

        terreno[fil][col] = (char)(i + 1 + '0');
    }
}

void generar_terreno(char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1], int tamanio_terreno){
    for (int i = 0; i < tamanio_terreno; i++){
        for (int j = 0; j < tamanio_terreno; j++){
            terreno[i][j] = ' ';
        }
    }
}

void cargar_terreno(char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1], juego_t juego){
    cargar_paredes(terreno, juego.niveles[juego.nivel_actual]);
    cargar_posicion_jugador(terreno, juego.niveles[juego.nivel_actual].pos_inicial_jugador);
    cargar_obstaculos(terreno, juego.niveles[juego.nivel_actual]);
    cargar_herramientas(terreno, juego.niveles[juego.nivel_actual]);
    cargar_papeleos(terreno, juego.niveles[juego.nivel_actual]);
}

void imprimir_mapa(char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1], int tamanio_terreno){
    for (int i = 0; i < tamanio_terreno; i++){
        for (int j = 0; j < tamanio_terreno; j++){
            printf("%c ", terreno[i][j]);
        }
        printf("\n");
    }
}

void imprimir_terreno(juego_t juego){

    printf("Movimientos: %d\n", juego.jugador.movimientos);
    printf("Martillos: %d\n", juego.jugador.martillos);
    printf("Extintores: %d\n", juego.jugador.extintores);
    printf("Personaje obtenido: %c", juego.personaje_tp1);
    printf("\n");

    char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1];

    if (juego.nivel_actual == NIVEL_1){
        generar_terreno(terreno, TERRENO_NIVEL_1);
        cargar_terreno(terreno, juego);
        printf("\n");
        imprimir_mapa(terreno, TERRENO_NIVEL_1);
    } else if (juego.nivel_actual == NIVEL_2){
        generar_terreno(terreno, TERRENO_NIVEL_2);
        cargar_terreno(terreno, juego);
        printf("\n");
        imprimir_mapa(terreno, TERRENO_NIVEL_2);
    } else{
        generar_terreno(terreno, TERRENO_NIVEL_3);
        cargar_terreno(terreno, juego);
        printf("\n");
        imprimir_mapa(terreno, TERRENO_NIVEL_3);
    }
}

int main(int argc, char const *argv[]){
    char personaje_obtenido = hacer_cuestionario();
    srand ((unsigned)time(NULL));
    juego_t juego;
    juego.nivel_actual = 0;
    inicializar_juego(&juego, personaje_obtenido);
    imprimir_terreno(juego);

    return 0;
}
