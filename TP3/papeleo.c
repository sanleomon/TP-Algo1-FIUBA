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

#define JUGANDO 0
#define GANADO 1
#define PERDIDO -1

#define MOVIMIENTOS_NIVEL_1 40
#define MOVIMIENTOS_NIVEL_2 30
#define MOVIMIENTOS_NIVEL_3 20
#define MARTILLOS_NIVEL_1 4
#define MARTILLOS_NIVEL_2 5
#define MARTILLOS_NIVEL_3 6
#define EXTINTORES_NIVEL_1 4
#define EXTINTORES_NIVEL_2 2
#define EXTINTORES_NIVEL_3 2
#define FUEGOS_NIVEL_1 10
#define FUEGOS_NIVEL_2 5
#define FUEGOS_NIVEL_3 3
#define MEDIAS_NIVEL_1 5
#define MEDIAS_NIVEL_2 4
#define MEDIAS_NIVEL_3 3
#define BOTELLAS_GRITOS_NIVEL_1 4
#define BOTELLAS_GRITOS_NIVEL_2 3
#define BOTELLAS_GRITOS_NIVEL_3 2
#define INTERRUPTORES_NIVEL_1 1
#define INTERRUPTORES_NIVEL_2 1
#define INTERRUPTORES_NIVEL_3 0
#define PAPELEOS_NIVEL_1 2
#define PAPELEOS_NIVEL_2 3
#define PAPELEOS_NIVEL_3 4

#define OBSEQUIO_OLAF_NIVEL_1 2
#define OBSEQUIO_OLAF_NIVEL_2 1
#define OBSEQUIO_STICH 1
#define OBSEQUIO_JASMIN 1
#define OBSEQUIO_RAYO 10

#define UTILIZAR_MARTILLO 'Z'
#define UTILIZAR_EXTINTOR 'C'
#define IZQUIERDA 'A'
#define DERECHA 'D'
#define ARRIBA 'W'
#define ABAJO 'S'
#define ROTACION_HORARIA 'E'
#define ROTACION_ANTIHORARIA 'Q'

#define TERRENO_NIVEL_1 22
#define TERRENO_NIVEL_2 17
#define TERRENO_NIVEL_3 12

void asignar_topes(int numero_nivel, int* tope_fuegos, int* tope_medias, int* tope_gritos, 
    int* tope_interruptores, int* tope_papeleos, char personaje_tp1){

    if (numero_nivel == NIVEL_1){
        *tope_fuegos = FUEGOS_NIVEL_1;
        *tope_medias = MEDIAS_NIVEL_1;
        *tope_gritos = BOTELLAS_GRITOS_NIVEL_1;
        *tope_interruptores = INTERRUPTORES_NIVEL_1;
        *tope_papeleos = PAPELEOS_NIVEL_1;

        if (personaje_tp1 == OLAF){
            tope_fuegos-=OBSEQUIO_OLAF_NIVEL_1;
        }
        
    } else if (numero_nivel == NIVEL_2){
        *tope_fuegos = FUEGOS_NIVEL_2;
        *tope_medias = MEDIAS_NIVEL_2;
        *tope_gritos = BOTELLAS_GRITOS_NIVEL_2;
        *tope_interruptores = INTERRUPTORES_NIVEL_2;
        *tope_papeleos = PAPELEOS_NIVEL_2;

        if (personaje_tp1 == OLAF){
            tope_fuegos-=OBSEQUIO_OLAF_NIVEL_2;
        }

    } else if (numero_nivel == NIVEL_3){
        *tope_fuegos = FUEGOS_NIVEL_3;
        *tope_medias = MEDIAS_NIVEL_3;
        *tope_gritos = BOTELLAS_GRITOS_NIVEL_3;
        *tope_interruptores = INTERRUPTORES_NIVEL_3;
        *tope_papeleos = PAPELEOS_NIVEL_3;

        if (personaje_tp1 == STICH){
            tope_papeleos-=OBSEQUIO_STICH;
        }
        
    }
}

int obtener_dimension_terreno(int numero_nivel){
    if (numero_nivel == NIVEL_1){
        return TERRENO_NIVEL_1;
    } else if (numero_nivel == NIVEL_2){
        return TERRENO_NIVEL_2;
    } else{
        return TERRENO_NIVEL_3;
    }
}

void recibir_obsequio(jugador_t** jugador, int nivel_actual, char personaje_tp1){
    if(personaje_tp1 == JASMIN){
        (**jugador).martillos += OBSEQUIO_JASMIN;     
    } else if(personaje_tp1 == RAYO){
        if(nivel_actual == NIVEL_1){
            (**jugador).movimientos += OBSEQUIO_RAYO;
        }
    }
}

void eliminar_herramienta(nivel_t* nivel, int posicion){
    for (int i = posicion; i < nivel->tope_herramientas - 1; i++){
        nivel->herramientas[i] = nivel->herramientas[i + 1];
    }
    nivel->tope_herramientas--;
}

bool es_movimiento_valido(char caracter){
    if (caracter == IZQUIERDA || caracter == DERECHA || caracter == ROTACION_HORARIA 
        || caracter == ROTACION_ANTIHORARIA || caracter == UTILIZAR_MARTILLO 
        || caracter == UTILIZAR_EXTINTOR){
        return true;
    }
    return false;
}

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

bool se_puede_recolectar(papeleo_t* papeleos, int tope_papeleos, int id_actual){
    int i = 0;
    bool se_puede = true;

    while (i < tope_papeleos && se_puede){
        if (papeleos[i].id_papeleo < id_actual &&
            !papeleos[i].recolectado){

            se_puede = false;
        }
        i++;
    }

    return se_puede;
}

void generar_fuegos(nivel_t* nivel, int cantidad_fuegos, int tamanio_terreno){
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

void generar_medias(nivel_t* nivel, int cantidad_medias, int tamanio_terreno){
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

void generar_botellas_gritos(nivel_t* nivel, int cantidad_botellas, int tamanio_terreno){
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

void generar_interruptores(nivel_t* nivel, int cantidad_interruptores, int tamanio_terreno){
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

void inicializar_datos_jugador(jugador_t* jugador, int nivel_actual, 
    nivel_t* niveles, char personaje_tp_1){
    jugador->posicion = niveles[nivel_actual].pos_inicial_jugador;
    jugador->ahuyenta_randall = false;
    jugador->movimientos_realizados = 0;

    if((nivel_actual == NIVEL_1)){
        jugador->movimientos = MOVIMIENTOS_NIVEL_1;
        jugador->martillos = MARTILLOS_NIVEL_1;
        jugador->extintores = EXTINTORES_NIVEL_1;
        recibir_obsequio(&jugador, nivel_actual, personaje_tp_1);
        
    } else if(nivel_actual == NIVEL_2){
        jugador->movimientos = jugador->movimientos + MOVIMIENTOS_NIVEL_2;
        jugador->martillos = MARTILLOS_NIVEL_2;
        jugador->extintores = EXTINTORES_NIVEL_3;
        recibir_obsequio(&jugador, nivel_actual, personaje_tp_1);

    } else if((nivel_actual == NIVEL_3)){
        jugador->movimientos = jugador->movimientos + MOVIMIENTOS_NIVEL_3;
        jugador->martillos = MARTILLOS_NIVEL_3;
        jugador->extintores = EXTINTORES_NIVEL_3;
        recibir_obsequio(&jugador, nivel_actual, personaje_tp_1);

    }
}

void inicializar_nivel(nivel_t* nivel, int numero_nivel, char amigo_pide_favor){

    int dimension = obtener_dimension_terreno(numero_nivel);
        
    obtener_paredes(numero_nivel+1, nivel->paredes, &nivel->tope_paredes, 
        &nivel->pos_inicial_jugador);
    
    nivel->tope_obstaculos = 0;
    nivel->tope_herramientas = 0;
    nivel->tope_papeleos = 0;
    int tope_fuegos = 0;
    int tope_medias = 0;
    int tope_gritos = 0;
    int tope_interruptores = 0;
    int tope_papeleos = 0;
    asignar_topes(numero_nivel, &tope_fuegos, &tope_medias, &tope_gritos, 
        &tope_interruptores, &tope_papeleos, amigo_pide_favor);
            
    generar_fuegos(nivel, tope_fuegos, dimension);
    generar_medias(nivel, tope_medias, dimension);
    generar_botellas_gritos(nivel, tope_gritos, dimension);
    generar_interruptores(nivel, tope_interruptores, dimension);
    generar_papeleos(nivel, tope_papeleos, dimension);        
}

void inicializar_juego(juego_t* juego, char personaje_tp1){
    juego->personaje_tp1 = personaje_tp1;

    for (int i = 0; i < MAX_NIVELES; i++){
        inicializar_nivel(&juego->niveles[i], i, personaje_tp1);
    }
    inicializar_datos_jugador(&juego->jugador, juego->nivel_actual, juego->niveles,personaje_tp1);
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
    cargar_posicion_jugador(terreno, juego.jugador.posicion);
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
    printf("Teclas para moverse: W (arriba), S (abajo), A (izquierda), D (derecha)\n");
    printf("Tecla para usar un martillo: Z\n");
    printf("Tecla para usar un extintor: C\n");

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

int estado_nivel(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos){
    int cantidad_recolectados = 0;
    for (int i = 0; i < tope_papeleos; i++){
        if (papeleos[i].recolectado == true){
            cantidad_recolectados++;
        }
        
    }

    if (cantidad_recolectados == tope_papeleos){
        return GANADO;
    }
    return JUGANDO;
}

int estado_juego(juego_t juego){
    if (juego.jugador.movimientos <= 0){
        return PERDIDO;
    } else if (juego.nivel_actual == NIVEL_3){
        if (estado_nivel(juego.niveles[juego.nivel_actual].papeleos, 
            juego.niveles[juego.nivel_actual].tope_papeleos) == GANADO){
            return GANADO;
        }
    }
    return 0;
}

void aplicar_colision(juego_t* juego){

    nivel_t nivel_actual = juego->niveles[juego->nivel_actual];
    coordenada_t posicion_jugador = juego->jugador.posicion;
    
    int i = 0;
    bool encontrado = false;
    
    while (i < nivel_actual.tope_obstaculos && !encontrado){
        
        if (superpone_con_jugador(posicion_jugador, 
            nivel_actual.obstaculos[i].posicion)){
                
            encontrado = true;
            
            if (nivel_actual.obstaculos[i].tipo == FUEGOS){
                juego->jugador.movimientos = 0;
            } else if (nivel_actual.obstaculos[i].tipo == MEDIAS){
                juego->jugador.movimientos -= 10;
            }
        }
        i++;
    }

    i = 0;
    encontrado = false;

    while (i < nivel_actual.tope_herramientas && !encontrado){
        if (superpone_con_jugador(posicion_jugador,
            nivel_actual.herramientas[i].posicion)){

            encontrado = true;

            if (nivel_actual.herramientas[i].tipo == BOTELLA_GRITO){
                juego->jugador.movimientos += 7;
                eliminar_herramienta(&juego->niveles[juego->nivel_actual], i);
            }
            else if (nivel_actual.herramientas[i].tipo == INTERRUPTOR){
                juego->jugador.ahuyenta_randall = !juego->jugador.ahuyenta_randall;
            }
        }
        i++;
    }

    i = 0;
    encontrado = false;
    
    while (i < nivel_actual.tope_papeleos && !encontrado){
        if (superpone_con_jugador(posicion_jugador, 
            nivel_actual.papeleos[i].posicion)){
                
            encontrado = true;
            
            if (!nivel_actual.papeleos[i].recolectado && 
                se_puede_recolectar(nivel_actual.papeleos, 
                    nivel_actual.tope_papeleos, 
                    nivel_actual.papeleos[i].id_papeleo)){

                juego->niveles[juego->nivel_actual].papeleos[i].recolectado = true;
            }
        }
        i++;
    }
}

void aplicar_gravedad(juego_t* juego){
    nivel_t nivel_actual = juego->niveles[juego->nivel_actual];
    coordenada_t abajo = juego->jugador.posicion;
    abajo.fil++;

    while (!superpone_con_pared(abajo, nivel_actual.paredes, nivel_actual.tope_paredes)
           && juego->jugador.movimientos > 0){

        juego->jugador.posicion.fil++;
        aplicar_colision(juego);

        if (juego->jugador.movimientos > 0){
            system("clear");
            imprimir_terreno(*juego);
            detener_el_tiempo(1.0f);
        }

        abajo = juego->jugador.posicion;
        abajo.fil++;
    }
}

void realizar_jugada(juego_t* juego){
    char respuesta;
    scanf(" %c", &respuesta);

    while (!es_movimiento_valido(respuesta)){
        printf("Esa no es una opcion valida!\n");
        scanf(" %c", &respuesta);
    }

    if (respuesta == IZQUIERDA || respuesta == DERECHA){
        coordenada_t destino = juego->jugador.posicion;
        
        if (respuesta == IZQUIERDA){
            destino.col--;
        } else {
            destino.col++;
        }
        
        nivel_t nivel_actual = juego->niveles[juego->nivel_actual];
        
        if (!superpone_con_pared(destino, nivel_actual.paredes, nivel_actual.tope_paredes)){
            juego->jugador.posicion = destino;
            juego->jugador.movimientos--;
            juego->jugador.movimientos_realizados++;

            aplicar_colision(juego);   

            if (juego->jugador.movimientos > 0){
                aplicar_gravedad(juego);   
            }
        }
    }
}