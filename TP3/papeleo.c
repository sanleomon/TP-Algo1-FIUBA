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

#define VALOR_RANDALL_NIVEL_1 7
#define VALOR_RANDALL_NIVEL_2 5
#define VALOR_RANDALL_NIVEL_3 3

#define TERRENO_NIVEL_1 22
#define TERRENO_NIVEL_2 17
#define TERRENO_NIVEL_3 12

/* Pre-condiciones: El numero de nivel debe corresponder a un nivel entre (0,1,2)
 *      y los punteros recibidos deben ser validos.
 * Post-condiciones: Asigna las cantidades de fuegos, medias, botellas de gritos,
 *      interruptores y papeleos correspondientes al nivel indicado, contemplando
 *      los obsequios otorgados por el personaje obtenido en el TP1.
 */
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

/* Pre-condiciones: El numero de nivel debe corresponder a un nivel entre (0,1,2)
 * Post-condiciones: Devuelve la dimensión del terreno asociada al nivel recibido.
 */
int obtener_dimension_terreno(int numero_nivel){
    if (numero_nivel == NIVEL_1){
        return TERRENO_NIVEL_1;
    } else if (numero_nivel == NIVEL_2){
        return TERRENO_NIVEL_2;
    } else{
        return TERRENO_NIVEL_3;
    }
}

/* Pre-condiciones: El puntero al jugador debe ser valido, el nivel actual 
 *          debe ser entre (0,1,2) y el personaje recibido debe ser 
 *          entre (OLAF, STICH, JASMIN, RAYO).
 * Post-condiciones: Modifica los atributos del jugador aplicando el obsequio
 *      correspondiente al personaje obtenido en el TP1 para el nivel indicado.
 */
void recibir_obsequio(jugador_t** jugador, int nivel_actual, char personaje_tp1){
    if(personaje_tp1 == JASMIN){
        (**jugador).martillos += OBSEQUIO_JASMIN;     
    } else if(personaje_tp1 == RAYO){
        if(nivel_actual == NIVEL_1){
            (**jugador).movimientos += OBSEQUIO_RAYO;
        }
    }
}

/* Pre-condiciones: El puntero al nivel debe ser valido y la posicion recibida
 *      debe corresponder a un indice valido dentro del vector de herramientas.
 * Post-condiciones: Elimina la herramienta indicada del vector, desplazando los
 *      elementos restantes y actualizando el tope de herramientas del nivel.
 */
void eliminar_herramienta(nivel_t* nivel, int posicion){
    for (int i = posicion; i < nivel->tope_herramientas - 1; i++){
        nivel->herramientas[i] = nivel->herramientas[i + 1];
    }
    nivel->tope_herramientas--;
}

/* Pre-condiciones: -
 * Post-condiciones: Devuelve true si el caracter recibido corresponde a IZQUIERDA, 
 * DERECHA, ROTACION_HORARIA, ROTACION_ANTIHORARIA, UTILIZAR_MARTILLO o 
 * UTILIZAR_EXTINTOR. 
 * En caso contrario, devuelve false.
 */
bool es_movimiento_valido(char caracter){
    if (caracter == IZQUIERDA || caracter == DERECHA || caracter == ROTACION_HORARIA 
        || caracter == ROTACION_ANTIHORARIA || caracter == UTILIZAR_MARTILLO 
        || caracter == UTILIZAR_EXTINTOR){
        return true;
    }
    return false;
}

/* Pre-condiciones: -
 * Post-condiciones: Devuelve true si la direccion ingresada es valida para el uso
 *      del martillo (W, A, S o D). En caso contrario, devuelve false.
 */
bool es_direccion_martillo_valida(char direccion){
    return (direccion == ARRIBA || direccion == ABAJO ||
           direccion == IZQUIERDA || direccion == DERECHA);
}

/* Pre-condiciones: -
 * Post-condiciones: Devuelve true si la dirección ingresada es valida para el uso
 *      del extintor (W, A o D). En caso contrario, devuelve false.
 */
bool es_direccion_extintor_valida(char direccion){
    return (direccion == ARRIBA || direccion == IZQUIERDA 
        || direccion == DERECHA);
}

/* Pre-condiciones: El vector de paredes debe estar correctamente inicializado y
 *      el tope debe corresponder a la cantidad de paredes cargadas.
 * Post-condiciones: Devuelve true si la coordenada recibida coincide con alguna
 *      pared del vector. En caso contrario, devuelve false.
 */
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

/* Pre-condiciones: El vector de paredes debe estar correctamente inicializado y
 *      el tope debe corresponder a la cantidad de paredes cargadas.
 * Post-condiciones: Devuelve true si la coordenada recibida es adyacente en forma
 *      no diagonal a alguna pared del vector. En caso contrario, devuelve false.
 */
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

/* Pre-condiciones: El vector de obstáculos debe estar correctamente inicializado
 *      y el tope debe corresponder a la cantidad de obstaculos cargados.
 * Post-condiciones: Devuelve true si la coordenada recibida coincide con la
 *      posicion de algun obstaculo. En caso contrario, devuelve false.
 */
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

/* Pre-condiciones: -
 * Post-condiciones: Devuelve true si la posicion del jugador coincide con la
 *      coordenada recibida. En caso contrario, devuelve false.
 */
bool superpone_con_jugador(coordenada_t pos_jugador, coordenada_t coordenada){
    return (pos_jugador.fil == coordenada.fil && pos_jugador.col == coordenada.col);
}

/* Pre-condiciones: El vector de herramientas debe estar correctamente inicializado
 *      y el tope debe corresponder a la cantidad de herramientas cargadas.
 * Post-condiciones: Devuelve true si la coordenada recibida coincide con la
 *      posicion de alguna herramienta. En caso contrario, devuelve false.
 */
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

/* Pre-condiciones: El vector de papeleos debe estar correctamente inicializado
 *      y el tope debe corresponder a la cantidad de papeleos cargados.
 * Post-condiciones: Devuelve true si la coordenada recibida coincide con la
 *      posicion de algun papeleo. En caso contrario, devuelve false.
 */
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

/* Pre-condiciones: El vector de papeleos debe estar correctamente inicializado
 *      y el id recibido debe corresponder a un papeleo valido del nivel.
 * Post-condiciones: Devuelve true si todos los papeleos con id menor al indicado
 *      ya fueron recolectados. En caso contrario, devuelve false.
 */
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

/* Pre-condiciones: La dimension debe corresponder al tamaño del terreno del nivel.
 * Post-condiciones: Devuelve true si la coordenada recibida pertenece al borde
 *      del terreno. En caso contrario, devuelve false.
 */
bool es_borde(coordenada_t coordenada, int dimension){
    return (coordenada.fil == 0 || coordenada.fil == dimension - 1 ||
            coordenada.col == 0 || coordenada.col == dimension - 1);
}

/* Pre-condiciones: El nivel actual debe corresponder a un valor entre 0,1 o 2.
 * Post-condiciones: Devuelve el valor R asociado al nivel, utilizado para
 *      determinar cada cuantos movimientos Randall transporta un papeleo.
 */
int obtener_valor_randall(int nivel_actual){
    if (nivel_actual == NIVEL_1){
        return VALOR_RANDALL_NIVEL_1;
    } else if (nivel_actual == NIVEL_2){
        return VALOR_RANDALL_NIVEL_2;
    } else {
        return VALOR_RANDALL_NIVEL_3;
    }
}

/* Pre-condiciones: El nivel actual debe corresponder a un valor entre 0,1 o 2.
 * Post-condiciones: Devuelve la cantidad maxima de movimientos durante los cuales
 *      pueden generarse paredes aleatorias en el nivel.
 */
int obtener_cantidad_paredes_random(int nivel_actual){
    if (nivel_actual == NIVEL_1){
        return MOVIMIENTOS_NIVEL_1;
    } else if (nivel_actual == NIVEL_2){
        return MOVIMIENTOS_NIVEL_2;
    } else {
        return MOVIMIENTOS_NIVEL_3;
    }
}

/* Pre-condiciones: El puntero al nivel debe ser valido, la cantidad de fuegos debe
 *      ser no negativa y el tamaño del terreno debe corresponder al nivel.
 * Post-condiciones: Genera la cantidad indicada de fuegos en posiciones aleatorias
 *      validas del terreno, evitando superposiciones con paredes, obstaculos
 *      existentes o la posicion inicial del jugador, y respetando la condicion
 *      de adyacencia a paredes.
 */
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

/* Pre-condiciones: El puntero al nivel debe ser valido, la cantidad de medias debe
 *      ser no negativa y el tamaño del terreno debe corresponder al nivel.
 * Post-condiciones: Genera la cantidad indicada de medias en posiciones aleatorias
 *      validas del terreno, evitando superposiciones con paredes, otros obstaculos
 *      o la posicion inicial del jugador.
 */
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

/* Pre-condiciones: El puntero al nivel debe ser valido, la cantidad de botellas debe
 *      ser no negativa y el tamaño del terreno debe corresponder al nivel.
 * Post-condiciones: Genera la cantidad indicada de botellas de gritos en posiciones
 *      aleatorias validas del terreno, evitando superposiciones con paredes,
 *      obstaculos, herramientas existentes o la posicion inicial del jugador.
 */
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

/* Pre-condiciones: El puntero al nivel debe ser valido, la cantidad de interruptores
 *      debe ser no negativa y el tamaño del terreno debe corresponder al nivel.
 * Post-condiciones: Genera la cantidad indicada de interruptores en posiciones
 *      aleatorias validas del terreno, evitando superposiciones con paredes,
 *      obstaculos, herramientas existentes o la posicion inicial del jugador.
 */
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

/* Pre-condiciones: El puntero al nivel debe ser valido, la cantidad de papeleos debe
 *      ser no negativa y el tamaño del terreno debe corresponder al nivel.
 * Post-condiciones: Genera la cantidad indicada de papeleos en posiciones aleatorias
 *      validas del terreno, evitando superposiciones con paredes, obstaculos,
 *      herramientas, otros papeleos o la posicion inicial del jugador. Ademas,
 *      asigna a cada papeleo su id correspondiente e inicializa su estado de
 *      recoleccion en false.
 */
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

/* Pre-condiciones: El puntero al jugador debe ser valido, el nivel actual debe
 *      corresponder a un nivel valido (entre 0,1 o 2) y el vector de niveles 
 *      debe estar correctamente inicializado.
 * Post-condiciones: Inicializa los datos del jugador para el nivel indicado,
 *      asignando su posicion inicial, movimientos, herramientas, estado del
 *      interruptor ahuyenta Randall y cantidad de movimientos realizados.
 *      Tambien aplica el obsequio correspondiente al personaje obtenido en el TP1.
 */
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

/* Pre-condiciones: El puntero al nivel debe ser valido, el numero de nivel debe
 *      corresponder a un valor entre 0,1 o 2 y el personaje recibido debe ser valido.
 * Post-condiciones: Inicializa completamente el nivel indicado, cargando paredes,
 *      posicion inicial del jugador, obstaculos, herramientas y papeleos segun
 *      la configuracion correspondiente al nivel y al personaje recibido.
 */
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

/* Pre-condiciones: El terreno debe estar correctamente inicializado y el nivel
 *      recibido debe contener sus paredes cargadas.
 * Post-condiciones: Carga en la matriz del terreno todas las paredes correspondientes
 *      al nivel recibido.
 */
void cargar_paredes(char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1], nivel_t nivel){
    int fil = 0;
    int col = 0;

    for (int i = 0; i < nivel.tope_paredes; i++){
        fil = nivel.paredes[i].fil;
        col = nivel.paredes[i].col;

        terreno[fil][col] = '-';
    }
}

/* Pre-condiciones: El terreno debe estar correctamente inicializado y la posicion
 *      del jugador debe ser valida dentro de los limites del mapa.
 * Post-condiciones: Carga en la matriz del terreno la posicion actual del jugador.
 */
void cargar_posicion_jugador(char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1], 
    coordenada_t posicion_jugador){
        terreno[posicion_jugador.fil][posicion_jugador.col] = MIKE;
}

/* Pre-condiciones: El terreno debe estar correctamente inicializado y el nivel
 *      recibido debe contener sus obstaculos cargados.
 * Post-condiciones: Carga en la matriz del terreno todos los obstaculos del nivel,
 *      representando cada uno con el caracter correspondiente a su tipo.
 */
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

/* Pre-condiciones: El terreno debe estar correctamente inicializado y el nivel
 *      recibido debe contener sus herramientas cargadas.
 * Post-condiciones: Carga en la matriz del terreno todas las herramientas del nivel,
 *      representando cada una con el caracter correspondiente a su tipo.
 */
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

/* Pre-condiciones: El terreno debe estar correctamente inicializado y el nivel
 *      recibido debe contener sus papeleos cargados.
 * Post-condiciones: Carga en la matriz del terreno unicamente los papeleos que
 *      no hayan sido recolectados, representandolos con su identificador.
 */
void cargar_papeleos(char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1], nivel_t nivel){
    int fil = 0;
    int col = 0;

    for (int i = 0; i < nivel.tope_papeleos; i++){
        if (!nivel.papeleos[i].recolectado){
            fil = nivel.papeleos[i].posicion.fil;
            col = nivel.papeleos[i].posicion.col;
            
            terreno[fil][col] = (char)(i + 1 + '0');
        }
    }
}

/* Pre-condiciones: El tamaño del terreno debe corresponder a la dimension del nivel.
 * Post-condiciones: Inicializa la matriz del terreno llenando todas sus posiciones
 *      con espacios vacios.
 */
void generar_terreno(char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1], int tamanio_terreno){
    for (int i = 0; i < tamanio_terreno; i++){
        for (int j = 0; j < tamanio_terreno; j++){
            terreno[i][j] = ' ';
        }
    }
}

/* Pre-condiciones: El terreno debe estar correctamente inicializado y el juego
 *      debe contener sus estructuras validas.
 * Post-condiciones: Carga en la matriz del terreno todos los elementos del nivel
 *      actual (paredes, jugador, obstaculos, herramientas y papeleos).
 */
void cargar_terreno(char terreno[TERRENO_NIVEL_1][TERRENO_NIVEL_1], juego_t juego){
    cargar_paredes(terreno, juego.niveles[juego.nivel_actual]);
    cargar_posicion_jugador(terreno, juego.jugador.posicion);
    cargar_obstaculos(terreno, juego.niveles[juego.nivel_actual]);
    cargar_herramientas(terreno, juego.niveles[juego.nivel_actual]);
    cargar_papeleos(terreno, juego.niveles[juego.nivel_actual]);
}

/* Pre-condiciones: El terreno debe estar correctamente inicializado y el tamaño
 *      debe corresponder a la dimension del nivel.
 * Post-condiciones: Imprime por pantalla la representacion del terreno recibido.
 */
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
    printf("Teclas para moverse: A (izquierda), D (derecha)\n");
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

/* Pre-condiciones: El puntero al juego debe ser valido.
 * Post-condiciones: Avanza al siguiente nivel si el actual no es el ultimo,
 *      reinicializando los datos del jugador para el nuevo nivel.
 */
void cambiar_nivel(juego_t* juego){
    if (juego->nivel_actual < NIVEL_3){
        juego->nivel_actual++;
        inicializar_datos_jugador(&juego->jugador, juego->nivel_actual,
            juego->niveles, juego->personaje_tp1);
    }
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

/* Pre-condiciones: La coordenada debe ser valida y la dimension debe corresponder
 *      al tamanio del terreno.
 * Post-condiciones: Devuelve una nueva coordenada resultante de rotar la coordenada
 *      original 90 grados en sentido horario dentro del terreno.
 */
coordenada_t rotar_coordenada_horaria(coordenada_t coordenada, int dimension){
    coordenada_t nueva_coordenada;

    nueva_coordenada.fil = coordenada.col;
    nueva_coordenada.col = dimension - 1 - coordenada.fil;

    return nueva_coordenada;
}

/* Pre-condiciones: La coordenada debe ser valida y la dimension debe corresponder
 *      al tamanio del terreno.
 * Post-condiciones: Devuelve una nueva coordenada resultante de rotar la coordenada
 *      original 90 grados en sentido antihorario dentro del terreno.
 */
coordenada_t rotar_coordenada_antihoraria(coordenada_t coordenada, int dimension){
    coordenada_t nueva_coordenada;

    nueva_coordenada.fil = dimension - 1 - coordenada.col;
    nueva_coordenada.col = coordenada.fil;

    return nueva_coordenada;
}

/* Pre-condiciones: El puntero al nivel debe ser valido y la dimension debe
 *      corresponder al tamanio del terreno.
 * Post-condiciones: Rota todas las paredes del nivel 90 grados en sentido horario.
 */
void rotar_paredes_horario(nivel_t* nivel, int dimension){
    for (int i = 0; i < nivel->tope_paredes; i++){
        nivel->paredes[i] = rotar_coordenada_horaria(nivel->paredes[i], dimension);
    }
}

/* Pre-condiciones: El puntero al nivel debe ser valido y la dimension debe
 *      corresponder al tamanio del terreno.
 * Post-condiciones: Rota todas las paredes del nivel 90 grados en sentido antihorario.
 */
void rotar_paredes_antihorario(nivel_t* nivel, int dimension){
    for (int i = 0; i < nivel->tope_paredes; i++){
        nivel->paredes[i] = rotar_coordenada_antihoraria(nivel->paredes[i], dimension);
    }
}

/* Pre-condiciones: El puntero al nivel debe ser valido y la dimension debe
 *      corresponder al tamanio del terreno.
 * Post-condiciones: Rota todas las posiciones de los obstaculos del nivel
 *      90 grados en sentido horario.
 */
void rotar_obstaculos_horario(nivel_t* nivel, int dimension){
    for (int i = 0; i < nivel->tope_obstaculos; i++){
        nivel->obstaculos[i].posicion =
            rotar_coordenada_horaria(nivel->obstaculos[i].posicion, dimension);
    }
}

/* Pre-condiciones: El puntero al nivel debe ser valido y la dimension debe
 *      corresponder al tamanio del terreno.
 * Post-condiciones: Rota todas las posiciones de los obstaculos del nivel
 *      90 grados en sentido antihorario.
 */
void rotar_obstaculos_antihorario(nivel_t* nivel, int dimension){
    for (int i = 0; i < nivel->tope_obstaculos; i++){
        nivel->obstaculos[i].posicion =
            rotar_coordenada_antihoraria(nivel->obstaculos[i].posicion, dimension);
    }
}

/* Pre-condiciones: El puntero al nivel debe ser valido y la dimension debe
 *      corresponder al tamanio del terreno.
 * Post-condiciones: Rota todas las posiciones de las herramientas del nivel
 *      90 grados en sentido horario.
 */
void rotar_herramientas_horario(nivel_t* nivel, int dimension){
    for (int i = 0; i < nivel->tope_herramientas; i++){
        nivel->herramientas[i].posicion =
            rotar_coordenada_horaria(nivel->herramientas[i].posicion, dimension);
    }
}

/* Pre-condiciones: El puntero al nivel debe ser valido y la dimension debe
 *      corresponder al tamanio del terreno.
 * Post-condiciones: Rota todas las posiciones de las herramientas del nivel
 *      90 grados en sentido antihorario.
 */
void rotar_herramientas_antihorario(nivel_t* nivel, int dimension){
    for (int i = 0; i < nivel->tope_herramientas; i++){
        nivel->herramientas[i].posicion =
            rotar_coordenada_antihoraria(nivel->herramientas[i].posicion, dimension);
    }
}

/* Pre-condiciones: El puntero al nivel debe ser valido y la dimension debe
 *      corresponder al tamanio del terreno.
 * Post-condiciones: Rota todas las posiciones de los papeleos del nivel
 *      90 grados en sentido horario.
 */
void rotar_papeleos_horario(nivel_t* nivel, int dimension){
    for (int i = 0; i < nivel->tope_papeleos; i++){
        nivel->papeleos[i].posicion =
            rotar_coordenada_horaria(nivel->papeleos[i].posicion, dimension);
    }
}

/* Pre-condiciones: El puntero al nivel debe ser valido y la dimension debe
 *      corresponder al tamanio del terreno.
 * Post-condiciones: Rota todas las posiciones de los papeleos del nivel
 *      90 grados en sentido antihorario.
 */
void rotar_papeleos_antihorario(nivel_t* nivel, int dimension){
    for (int i = 0; i < nivel->tope_papeleos; i++){
        nivel->papeleos[i].posicion =
            rotar_coordenada_antihoraria(nivel->papeleos[i].posicion, dimension);
    }
}

/* Pre-condiciones: La posicion del jugador debe ser valida y la direccion debe
 *      corresponder a una direccion valida para usar el martillo.
 * Post-condiciones: Devuelve la coordenada adyacente al jugador en la direccion
 *      indicada.
 */
coordenada_t obtener_posicion_martillo(coordenada_t posicion_jugador, char direccion){
    coordenada_t objetivo = posicion_jugador;

    if (direccion == ARRIBA){
        objetivo.fil--;
    } else if (direccion == ABAJO){
        objetivo.fil++;
    } else if (direccion == IZQUIERDA){
        objetivo.col--;
    } else if (direccion == DERECHA){
        objetivo.col++;
    }

    return objetivo;
}

/* Pre-condiciones: La posicion del jugador debe ser valida y la direccion debe
 *      corresponder a una direccion valida para usar el extintor.
 * Post-condiciones: Devuelve la coordenada adyacente al jugador en la direccion
 *      indicada.
 */
coordenada_t obtener_posicion_extintor(coordenada_t posicion_jugador, char direccion){
    coordenada_t objetivo = posicion_jugador;

    if (direccion == ARRIBA){
        objetivo.fil--;
    } else if (direccion == IZQUIERDA){
        objetivo.col--;
    } else if (direccion == DERECHA){
        objetivo.col++;
    }

    return objetivo;
}

/* Pre-condiciones: El puntero al nivel debe ser valido y el indice recibido debe
 *      corresponder a una pared existente dentro del vector de paredes.
 * Post-condiciones: Elimina la pared indicada del vector, desplazando los elementos
 *      restantes y actualizando el tope de paredes.
 */
void eliminar_pared(nivel_t* nivel, int indice){
    for (int i = indice; i < nivel->tope_paredes - 1; i++){
        nivel->paredes[i] = nivel->paredes[i + 1];
    }

    nivel->tope_paredes--;
}

/* Pre-condiciones: El puntero al nivel debe ser valido y el indice recibido debe
 *      corresponder a un obstaculo de tipo fuego existente dentro del vector de obstaculos.
 * Post-condiciones: Elimina el fuego indicado del vector de obstaculos, desplazando los elementos
 *      restantes y actualizando el tope de obstaculos.
 */
void eliminar_fuego(nivel_t* nivel, int indice){
    for (int i = indice; i < nivel->tope_obstaculos - 1; i++){
        nivel->obstaculos[i] = nivel->obstaculos[i + 1];
    }

    nivel->tope_obstaculos--;
}

/* Pre-condiciones: El puntero al nivel debe ser valido y el vector de papeleos
 *      debe estar correctamente inicializado.
 * Post-condiciones: Devuelve el indice de un papeleo no recolectado elegido al azar.
 *      Si no quedan papeleos disponibles, devuelve -1.
 */
int obtener_indice_papeleo_random(nivel_t* nivel){
    int indices[MAX_PAPELEOS];
    int cantidad = 0;

    int i = 0;
    while (i < nivel->tope_papeleos){
        if (!nivel->papeleos[i].recolectado){
            indices[cantidad] = i;
            cantidad++;
        }
        i++;
    }

    if (cantidad == 0){
        return -1;
    }

    int elegido = rand() % cantidad;

    return indices[elegido];
}

/* Pre-condiciones: El puntero al nivel debe ser valido, el nivel actual debe ser
 *      valido.
 * Post-condiciones: Si corresponde, segun la logica de Randall, y el interruptor
 *      ahuyenta Randall no esta activado, mueve aleatoriamente un papeleo no
 *      recolectado a una nueva posicion valida del terreno.
 */
void mover_papeleo_random(nivel_t* nivel, int nivel_actual, jugador_t jugador){
    int r = obtener_valor_randall(nivel_actual);

    if (!jugador.ahuyenta_randall &&
        jugador.movimientos_realizados % r == 0){

        int indice_papeleo = obtener_indice_papeleo_random(nivel);

        if (indice_papeleo != -1){
            int dimension = obtener_dimension_terreno(nivel_actual);
            coordenada_t nueva_posicion;

            nueva_posicion.fil = rand() % dimension;
            nueva_posicion.col = rand() % dimension;

            while (superpone_con_pared(nueva_posicion, nivel->paredes, nivel->tope_paredes) ||
                   superpone_con_obstaculo(nueva_posicion, nivel->obstaculos, nivel->tope_obstaculos) ||
                   superpone_con_herramienta(nueva_posicion, nivel->herramientas, nivel->tope_herramientas) ||
                   superpone_con_papeleo(nueva_posicion, nivel->papeleos, nivel->tope_papeleos) ||
                   superpone_con_jugador(jugador.posicion, nueva_posicion)){

                nueva_posicion.fil = rand() % dimension;
                nueva_posicion.col = rand() % dimension;
            }

            nivel->papeleos[indice_papeleo].posicion = nueva_posicion;
        }
    }
}

/* Pre-condiciones: El nivel actual debe corresponder a un nivel valido del juego.
 * Post-condiciones: Devuelve la cantidad maxima de movimientos durante los cuales
 *      se pueden generar paredes aleatorias en el nivel indicado.
 */
int obtener_limite_paredes_random(int nivel_actual){
    if (nivel_actual == NIVEL_1){
        return MOVIMIENTOS_NIVEL_1;
    } else if (nivel_actual == NIVEL_2){
        return MOVIMIENTOS_NIVEL_2;
    } else {
        return MOVIMIENTOS_NIVEL_3;
    }
}

/* Pre-condiciones: El puntero al nivel debe ser valido, el nivel actual debe ser
 *      valido y el jugador debe contener una posicion valida.
 * Post-condiciones: Genera una nueva pared en una posicion aleatoria valida y libre
 *      del terreno, evitando superposiciones con paredes, obstaculos, herramientas,
 *      papeleos o el jugador.
 */
void generar_pared_random(nivel_t* nivel, int nivel_actual, jugador_t jugador){
    int dimension = obtener_dimension_terreno(nivel_actual);

    coordenada_t nueva;

    nueva.fil = rand() % dimension;
    nueva.col = rand() % dimension;

    while (superpone_con_pared(nueva, nivel->paredes, nivel->tope_paredes) ||
           superpone_con_obstaculo(nueva, nivel->obstaculos, nivel->tope_obstaculos) ||
           superpone_con_herramienta(nueva, nivel->herramientas, nivel->tope_herramientas) ||
           superpone_con_papeleo(nueva, nivel->papeleos, nivel->tope_papeleos) ||
           superpone_con_jugador(jugador.posicion, nueva)){

        nueva.fil = rand() % dimension;
        nueva.col = rand() % dimension;
    }

    nivel->paredes[nivel->tope_paredes] = nueva;
    nivel->tope_paredes++;
}

/* Pre-condiciones: El puntero al nivel y al jugador deben ser validos, y el nivel
 *      actual debe corresponder a un nivel valido del juego.
 * Post-condiciones: Solicita una direccion valida al usuario. Si en la posicion
 *      indicada hay un fuego, lo elimina del vector de obstaculos y descuenta un
 *      extintor al jugador.
 */
void usar_extintor(nivel_t * nivel, int nivel_actual, jugador_t* jugador){

    char direccion;

    printf("\n");
    printf("Elegi hacia donde queres usar el extintor:\n");
    printf("W: arriba\n");
    printf("A: izquierda\n");
    printf("D: derecha\n");
    scanf(" %c", &direccion);

    while (!es_direccion_extintor_valida(direccion)){
        printf("Direccion invalida. Elegi W, A o D.\n");
        scanf(" %c", &direccion);
    }

    coordenada_t objetivo = obtener_posicion_extintor(jugador->posicion, direccion);

    int i = 0;
    bool encontrado = false;

    while (i < nivel->tope_obstaculos && !encontrado){
        if (nivel->obstaculos[i].posicion.fil == objetivo.fil &&
            nivel->obstaculos[i].posicion.col == objetivo.col &&
            nivel->obstaculos[i].tipo == FUEGOS){

            eliminar_fuego(nivel, i);
            jugador->extintores--;
            encontrado = true;
        } else {
            i++;
        }
    }
}

/* Pre-condiciones: El puntero al nivel y al jugador deben ser validos, y el nivel
 *      actual debe corresponder a un nivel valido del juego.
 * Post-condiciones: Solicita una direccion valida al usuario. Si en la posicion
 *      indicada hay una pared que no pertenece al borde del terreno, la elimina
 *      del vector de paredes y descuenta un martillo al jugador.
 */
void usar_martillo(nivel_t * nivel, int nivel_actual, jugador_t* jugador){

    int dimension = obtener_dimension_terreno(nivel_actual);
    char direccion;

    printf("\n");
    printf("Elegi hacia donde queres usar el martillo:\n");
    printf("W: arriba\n");
    printf("S: abajo\n");
    printf("A: izquierda\n");
    printf("D: derecha\n");
    scanf(" %c", &direccion);

    while (!es_direccion_martillo_valida(direccion)){
        printf("Direccion invalida. Elegi W, S, A o D.\n");
        scanf(" %c", &direccion);
    }

    coordenada_t objetivo = obtener_posicion_martillo(jugador->posicion, direccion);

    int i = 0;
    bool encontrada = false;

    while (i < nivel->tope_paredes && !encontrada){
        if (nivel->paredes[i].fil == objetivo.fil &&
            nivel->paredes[i].col == objetivo.col &&
            !es_borde(nivel->paredes[i], dimension)){

            eliminar_pared(nivel, i);
            jugador->martillos--;
            encontrada = true;
        } else {
            i++;
        }
    }
}

/* Pre-condiciones: El puntero al juego debe ser valido y el nivel actual debe
 *      contener sus obstaculos cargados correctamente.
 * Post-condiciones: Si el jugador se encuentra sobre un fuego, pierde todos sus
 *      movimientos. Si se encuentra sobre una media, pierde 10 movimientos.
 */
void aplicar_colision_obstaculos(juego_t* juego){
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
}

/* Pre-condiciones: El puntero al juego debe ser valido y el nivel actual debe
 *      contener sus herramientas cargadas correctamente.
 * Post-condiciones: Si el jugador se encuentra sobre una botella de gritos, gana
 *      7 movimientos y la herramienta se elimina. Si se encuentra sobre un interruptor,
 *      cambia el estado del ahuyenta Randall.
 */
void aplicar_colision_herramientas(juego_t* juego){
    nivel_t nivel_actual = juego->niveles[juego->nivel_actual];
    coordenada_t posicion_jugador = juego->jugador.posicion;

    int i = 0;
    bool encontrado = false;

    while (i < nivel_actual.tope_herramientas && !encontrado){
        if (superpone_con_jugador(posicion_jugador,
            nivel_actual.herramientas[i].posicion)){

            encontrado = true;

            if (nivel_actual.herramientas[i].tipo == BOTELLA_GRITO){
                juego->jugador.movimientos += 7;
                eliminar_herramienta(&juego->niveles[juego->nivel_actual], i);
            } else if (nivel_actual.herramientas[i].tipo == INTERRUPTOR){
                juego->jugador.ahuyenta_randall = !juego->jugador.ahuyenta_randall;
            }
        }
        i++;
    }
}

/* Pre-condiciones: El puntero al juego debe ser valido y el nivel actual debe
 *      contener sus papeleos cargados correctamente.
 * Post-condiciones: Si el jugador se encuentra sobre un papeleo no recolectado,
 *      lo marca como recolectado unicamente si todos los papeleos con id menor
 *      ya fueron recolectados.
 */
void aplicar_colision_papeleos(juego_t* juego){
    nivel_t nivel_actual = juego->niveles[juego->nivel_actual];
    coordenada_t posicion_jugador = juego->jugador.posicion;

    int i = 0;
    bool encontrado = false;

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

/* Pre-condiciones: El puntero al juego debe ser valido.
 * Post-condiciones: Aplica las interacciones correspondientes entre el jugador
 *      y los elementos ubicados en su posicion actual: obstaculos, herramientas
 *      y papeleos.
 */
void aplicar_colision(juego_t* juego){
    aplicar_colision_obstaculos(juego);
    aplicar_colision_herramientas(juego);
    aplicar_colision_papeleos(juego);
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
            detener_el_tiempo(0.6f);
        }

        abajo = juego->jugador.posicion;
        abajo.fil++;
    }
}

void aplicar_eventos_post_movimiento(juego_t* juego){
    mover_papeleo_random(&juego->niveles[juego->nivel_actual],
        juego->nivel_actual, juego->jugador);

    int limite = obtener_limite_paredes_random(juego->nivel_actual);
    if (juego->jugador.movimientos_realizados <= limite){
        generar_pared_random(&juego->niveles[juego->nivel_actual],
            juego->nivel_actual, juego->jugador);
    }
}

void procesar_movimiento_lateral(juego_t* juego, char respuesta){
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

        aplicar_eventos_post_movimiento(juego);
    }
}

void procesar_rotacion(juego_t* juego, char respuesta){
    int dimension = obtener_dimension_terreno(juego->nivel_actual);

    if (respuesta == ROTACION_HORARIA){
        rotar_paredes_horario(&juego->niveles[juego->nivel_actual], dimension);
        rotar_obstaculos_horario(&juego->niveles[juego->nivel_actual], dimension);
        rotar_herramientas_horario(&juego->niveles[juego->nivel_actual], dimension);
        rotar_papeleos_horario(&juego->niveles[juego->nivel_actual], dimension);

        juego->jugador.posicion =
            rotar_coordenada_horaria(juego->jugador.posicion, dimension);

    } else {
        rotar_paredes_antihorario(&juego->niveles[juego->nivel_actual], dimension);
        rotar_obstaculos_antihorario(&juego->niveles[juego->nivel_actual], dimension);
        rotar_herramientas_antihorario(&juego->niveles[juego->nivel_actual], dimension);
        rotar_papeleos_antihorario(&juego->niveles[juego->nivel_actual], dimension);

        juego->jugador.posicion =
            rotar_coordenada_antihoraria(juego->jugador.posicion, dimension);
    }

    juego->jugador.movimientos--;
    juego->jugador.movimientos_realizados++;

    if (juego->jugador.movimientos > 0){
        aplicar_gravedad(juego);
    }

    aplicar_eventos_post_movimiento(juego);
}

void procesar_martillo(juego_t* juego){
    if (juego->jugador.martillos > 0){
        usar_martillo(&juego->niveles[juego->nivel_actual],
            juego->nivel_actual, &juego->jugador);

        if (juego->jugador.movimientos > 0){
            aplicar_gravedad(juego);
        }
    } else {
        printf("\n");
        printf("No te quedan martillos.\n");
        detener_el_tiempo(0.6f);
    }
}

void procesar_extintor(juego_t* juego){
    if (juego->jugador.extintores > 0){
        usar_extintor(&juego->niveles[juego->nivel_actual],
            juego->nivel_actual, &juego->jugador);
    } else {
        printf("\n");
        printf("No te quedan extintores.\n");
        detener_el_tiempo(0.6f);
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
        procesar_movimiento_lateral(juego, respuesta);

    } else if (respuesta == ROTACION_HORARIA || respuesta == ROTACION_ANTIHORARIA){
        procesar_rotacion(juego, respuesta);

    } else if (respuesta == UTILIZAR_MARTILLO){
        procesar_martillo(juego);

    } else if (respuesta == UTILIZAR_EXTINTOR){
        procesar_extintor(juego);
   
    }
    
    if (estado_nivel(juego->niveles[juego->nivel_actual].papeleos, 
        juego->niveles[juego->nivel_actual].tope_papeleos) == GANADO &&
        juego->nivel_actual < NIVEL_3){
        cambiar_nivel(juego);
    }
}