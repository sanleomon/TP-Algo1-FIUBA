#include "dia_en_la_uni.h"

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

void imprimir_pregunta_transporte(){
    printf("Estas saliendo de tu casa, y te enteras que hay paro de trenes. "); 
    printf("Que otro transporte elegis?\n");
    printf("Las respuestas pueden ser: Trineo (T), Nave Espacial (N), Camion (C) o Alfombra (A).\n");
    printf("La respuesta debe ser una letra mayuscula. ");
    printf("(Ejemplo: si escribo C, estoy eligiendo Camion)\n");
}

void imprimir_pregunta_manifestacion(){
    printf("En medio del camino te encontras con una manifestacion. "); 
    printf("Que medio utilizas para deshacerte de la manifestacion?\n");
    printf("Las respuestas pueden ser: Bolas de nieve (B), Pium pium (P), Kuchau (K) o Genio (G).\n");
    printf("La respuesta debe ser una letra mayuscula. ");
    printf("(Ejemplo: si escribo K, estoy eligiendo Kuchau)\n");
}

void imprimir_pregunta_horario(){
    printf("Lograste superar la manifestacion. A que hora conseguiste llegar a la universidad?\n");
    printf("La respuesta debe ser un numero decimal. ");
    printf("La parte entera representa la hora y la parte decimal los minutos\n");
    printf("(Ejemplo: 22.35, esto seria las 22 horas y 35 minutos)\n");
}

void imprimir_pregunta_nota(){
    printf(" Por fin llego la nota del parcial! Que nota lograste sacar?\n");
    printf("(La nota puede ser de 1 a 10): ");
}

bool es_transporte_valido(char transporte){
    return (transporte == TRINEO) || (transporte == NAVE_ESPACIAL) 
        || (transporte == CAMION) || (transporte == ALFOMBRA);
}

bool es_arma_valida(char arma){
    return (arma == BOLAS_DE_NIEVE) || (arma == PIUM_PIUM) 
        || (arma == KUCHAU) || (arma == GENIO);
}

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

bool es_nota_valida(int nota){
    return (nota >= 1) && (nota <= 10); 
}

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

int obtener_puntaje_final(int puntaje_transporte, int puntaje_manifestacion, 
                          int multiplicador){
    return puntaje_transporte + (puntaje_manifestacion * multiplicador);
}

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

char hacer_cuestionario(){
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

    return personaje;
}