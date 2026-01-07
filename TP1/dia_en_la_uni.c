#include <stdio.h>
#include <stdbool.h>

#define TRINEO 'T'
#define NAVE_ESPACIAL 'N'
#define CAMION 'C'
#define ALFOMBRA 'A'

#define BOLAS_DE_NIEVE 'B'
#define PIUM_PIUM 'P'
#define KUCHAU 'K'
#define GENIO 'G'

#define OLAF 'O'
#define STICH 'S'
#define RAYO 'R'
#define JASMIN 'J'

/* Pre-condiciones: -
 * Post-condiciones: Imprime por pantalla el mensaje introductorio del juego,
 *       contextualizando la historia y los personajes.
 */
void imprimir_mensaje_de_inicio(){
    printf("Estudiaste semanas con nervios y estres por uno de los finales mas dificiles de la FIUBA.\n");
    printf("Repasaste todos los ejercicios, formulas y teoremas con la esperanza firme de aprobar.\n"); 
    printf("El dia del examen amaneciste con ansiedad, repasando obsesivamente los temas mientras tomabas tu cuarta taza de cafe.\n"); 
    printf("Pero, al salir de casa, una noticia arruina tus planes:\n");     
    printf("Paro de transporte en todo Buenos Aires por 48 horas. Sin trenes, parece imposible llegar a Paseo Colon, o no?\n");
    printf("Por suerte, Olaf, Stitch, Jazmin y Rayo McQueen aparecen para ayudarte.\n"); 
    printf("Cada uno, con su personalidad unica, puede ser clave para alcanzar tu objetivo: llegar y rendir el final.\n");
    printf("\n");
}

/* Pre-condiciones: -
 * Post-condiciones: Imprime por pantalla la pregunta relacionada al medio de transporte
 *       y las opciones válidas.
 */
void imprimir_pregunta_transporte(){
    printf("Estas saliendo de tu casa, y te enteras que hay paro de trenes. "); 
    printf("Que otro transporte elegis?\n");
    printf("Las respuestas pueden ser: Trineo (T), Nave Espacial (N), Camion (C) o Alfombra (A).\n");
    printf("La respuesta debe ser una letra mayuscula. ");
    printf("(Ejemplo: si escribo C, estoy eligiendo Camion)\n");
}

/* Pre-condiciones: -
 * Post-condiciones: Imprime por pantalla la pregunta relacionada a la manifestación
 *       y las opciones válidas para resolverla.
 */
void imprimir_pregunta_manifestacion(){
    printf("En medio del camino te encontras con una manifestacion. "); 
    printf("Que medio utilizas para deshacerte de la manifestacion?\n");
    printf("Las respuestas pueden ser: Bolas de nieve (B), Pium pium (P), Kuchau (K) o Genio (G).\n");
    printf("La respuesta debe ser una letra mayuscula. ");
    printf("(Ejemplo: si escribo K, estoy eligiendo Kuchau)\n");
}

/* Pre-condiciones: -
 * Post-condiciones: Imprime por pantalla la pregunta sobre el horario de llegada
 *       a la universidad y el formato esperado.
 */
void imprimir_pregunta_horario(){
    printf("Lograste superar la manifestacion. A que hora conseguiste llegar a la universidad?\n");
    printf("La respuesta debe ser un numero decimal. ");
    printf("La parte entera representa la hora y la parte decimal los minutos\n");
    printf("(Ejemplo: 22.35, esto seria las 22 horas y 35 minutos)\n");
}

/* Pre-condiciones: -
 * Post-condiciones: Imprime por pantalla la pregunta sobre la nota obtenida en el parcial.
 */
void imprimir_pregunta_nota(){
    printf(" Por fin llego la nota del parcial! Que nota lograste sacar?\n");
    printf("(La nota puede ser de 1 a 10): ");
}

/* Pre-condiciones: - 
 * Post-condiciones: Devuelve true si el carácter corresponde a una opción válida de transporte,
 *       false en caso contrario.
 */
bool es_transporte_valido(char transporte){
    return (transporte == TRINEO) || (transporte == NAVE_ESPACIAL) 
        || (transporte == CAMION) || (transporte == ALFOMBRA);
}

/* Pre-condiciones: -
 * Post-condiciones: Devuelve true si el arma ingresada es una opción válida,
 *       false en caso contrario.
 */
bool es_arma_valida(char arma){
    return (arma == BOLAS_DE_NIEVE) || (arma == PIUM_PIUM) 
        || (arma == KUCHAU) || (arma == GENIO);
}

/* Pre-condiciones: El parámetro horario representa una hora en formato HH.MM 
 * Post-condiciones: Devuelve true si el horario es válido (0 a 23 horas y minutos entre 0 y 59),
 *       false en caso contrario.
 */
bool es_hora_valida(float horario){
    int hora = (int)horario;
    if ((hora < 0) || (hora > 23)){
        return false;
    }
    float parte_decimal = horario - (float)hora;
    int minutos = (int)(parte_decimal * 100);
    if (minutos > 59){
        return false;
    }
    return true;
}

/* Pre-condiciones: -
 * Post-condiciones: Devuelve true si la nota está entre 1 y 10 inclusive,
 *       false en caso contrario.
 */
bool es_nota_valida(int nota){
    return (nota >= 1) && (nota <= 10); 
}

/* Pre-condiciones: El parámetro respuesta debe ser 'T', 'N', 'C' o 'A'
 * Post-condiciones: Devuelve el puntaje asociado al transporte elegido.
 */
int obtener_puntaje_transporte(char respuesta){
    if(respuesta == TRINEO){
        return 10;
    } else if(respuesta == NAVE_ESPACIAL){
        return 10;
    } else if(respuesta == CAMION){
        return 20;
    } else {
        return 20;
    }
}

/* Pre-condiciones: El parámetro respuesta debe ser 'B', 'P', 'K' o 'G'
 * Post-condiciones: Devuelve el puntaje asociado a la opción elegida para la manifestación.
 */
int obtener_puntaje_manifestacion(char respuesta){
    if(respuesta == BOLAS_DE_NIEVE){
        return 3;
    } else if(respuesta == PIUM_PIUM){
        return 6;
    } else if(respuesta == KUCHAU){
        return 9;
    } else {
        return 12;
    }
}

/* Pre-condiciones: La nota debe estar entre 1 y 10 inclusive.
 * Post-condiciones: Devuelve el multiplicador correspondiente según la nota obtenida.
 */
int obtener_multiplicador(int nota){
    if ((nota >= 1) && (nota < 4)){
        return 1;
    }else if ((nota >= 4) && (nota < 7)){
        return 2;
    }else if ((nota == 7) || (nota == 8)){
        return 3;
    }else{
        return 4;
    }
}

/* Pre-condiciones: puntaje_transporte >= 0, puntaje_manifestacion >= 0, multiplicador > 0.
 * Post-condiciones: Devuelve el puntaje final calculado a partir de los parámetros recibidos.
 */
int obtener_puntaje_final(int puntaje_transporte, int puntaje_manifestacion, 
                          int multiplicador){
    return puntaje_transporte + (puntaje_manifestacion * multiplicador);
}

/* Pre-condiciones: puntaje >= 0 y 0.00 <= horario <= 23.59.
 * Post-condiciones: Devuelve el personaje correspondiente según el puntaje obtenido
 *       y el horario de llegada.
 */
char obtener_personaje(int puntaje, float horario){
    int hora = (int) horario;
    float parte_decimal = horario - (float)hora;
    int minutos = (int)(parte_decimal * 100);

    if (puntaje < 42){
        if (hora <= 15){
            if (minutos <= 30){
                return STICH;
            }
        }
        return OLAF;
    }

    if (hora <= 15){
        if (minutos <= 30){
            return JASMIN;
        }
    }
    return RAYO;    
}

/* Pre-condiciones: El parámetro personaje debe ser 'S', 'O', 'J' o 'R'
 * Post-condiciones: Imprime por pantalla el personaje obtenido y la explicación del resultado.
 */
void imprimir_personaje(char personaje){
    if (personaje == STICH){
        printf("Como el examen es a las 15.30 y llego antes del examen tenemos como resultado ");
        printf("que el personaje es Stitch.\n");
    }else if (personaje == OLAF){
        printf("Como el examen es a las 15.30 y llego despues del examen tenemos como resultado ");
        printf("que el personaje es Olaf.\n");
    }else if (personaje == JASMIN){
        printf("Como el examen es a las 15.30 y llego antes del examen tenemos como resultado ");
        printf("que el personaje es Jasmin.\n");
    }else{
        printf("Como el examen es a las 15.30 y llego despues del examen tenemos como resultado ");
        printf("que el personaje es el Rayo McQueen.\n");
    }
}

int main(int argc, char const *argv[]){

    imprimir_mensaje_de_inicio();

    int puntaje_transporte = 0;
    char respuesta_transporte;
    imprimir_pregunta_transporte();
    scanf(" %c", &respuesta_transporte);
    while (!es_transporte_valido(respuesta_transporte)){
        printf("Esa no es una opcion valida!\n");
        printf("Las opciones son: Trineo (T), Nave Espacial (N), Camion (C) o Alfombra (A).\n");
        printf("La respuesta debe ser una letra mayuscula. ");
        printf("(Ejemplo: si escribo C, estoy eligiendo Camion)\n");
        scanf(" %c", &respuesta_transporte);
    }

    puntaje_transporte = obtener_puntaje_transporte(respuesta_transporte);
    printf("\n");

    int puntaje_manifestacion = 0;
    char respuesta_manifestacion;
    imprimir_pregunta_manifestacion();
    scanf(" %c", &respuesta_manifestacion);
    while (!es_arma_valida(respuesta_manifestacion)){
        printf("Esa no es una opcion valida!\n");
        printf("Las opciones son: Bolas de nieve (B), Pium pium (P), Kuchau (K) o Genio (G).\n");
        printf("La respuesta debe ser una letra mayuscula. ");
        printf("(Ejemplo: si escribo K, estoy eligiendo Kuchau)\n");
        scanf(" %c", &respuesta_manifestacion);
    }
    
    puntaje_manifestacion = obtener_puntaje_manifestacion(respuesta_manifestacion);
    printf("\n");

    float hora_llegada = 0.00f;
    imprimir_pregunta_horario();
    scanf(" %f", &hora_llegada);
    while (!es_hora_valida(hora_llegada)){
        printf("Eso no es un horario valido!\n");
        printf("La respuesta debe ser un numero decimal.\n");
        printf("Las horas no pueden ser mayor a 23, ni menor a 0.");
        printf("Los minutos no pueden ser mayores a 59.\n");
        printf("(Ejemplo: 22.35, esto seria las 22 horas y 35 minutos)\n");
        scanf(" %f", &hora_llegada);
    }

    printf("\n");
    int nota_parcial = 0;
    imprimir_pregunta_nota();
    scanf(" %d", &nota_parcial);
    while (!es_nota_valida(nota_parcial)){
        printf("Esa no es una nota valida!\n");
        printf("La nota puede ser de 1 a 10): ");
        scanf(" %d", &nota_parcial);
    }

    int multiplicador = obtener_multiplicador(nota_parcial);
    int puntaje_final = obtener_puntaje_final(puntaje_transporte, puntaje_manifestacion, multiplicador);
    printf("El puntaje obtenido es: %d.\n", puntaje_final);
    char personaje = obtener_personaje(puntaje_final, hora_llegada);
    printf("\n");
    imprimir_personaje(personaje);
    
    return 0;
}