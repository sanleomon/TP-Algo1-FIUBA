#ifndef __DIA_EN_LA_UNI_H__
#define __DIA_EN_LA_UNI_H__

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
void imprimir_mensaje_de_inicio();

/* Pre-condiciones: -
 * Post-condiciones: Imprime por pantalla la pregunta relacionada al medio de transporte
 *       y las opciones válidas.
 */
void imprimir_pregunta_transporte();

/* Pre-condiciones: -
 * Post-condiciones: Imprime por pantalla la pregunta relacionada a la manifestación
 *       y las opciones válidas para resolverla.
 */
void imprimir_pregunta_manifestacion();

/* Pre-condiciones: -
 * Post-condiciones: Imprime por pantalla la pregunta sobre el horario de llegada
 *       a la universidad y el formato esperado.
 */
void imprimir_pregunta_horario();

/* Pre-condiciones: -
 * Post-condiciones: Imprime por pantalla la pregunta sobre la nota obtenida en el parcial.
 */
void imprimir_pregunta_nota();

/* Pre-condiciones: - 
 * Post-condiciones: Devuelve true si el carácter corresponde a una opción válida de transporte,
 *       false en caso contrario.
 */
bool es_transporte_valido(char transporte);

/* Pre-condiciones: -
 * Post-condiciones: Devuelve true si el arma ingresada es una opción válida,
 *       false en caso contrario.
 */
bool es_arma_valida(char arma);

/* Pre-condiciones: El parámetro horario representa una hora en formato HH.MM 
 * Post-condiciones: Devuelve true si el horario es válido (0 a 23 horas y minutos entre 0 y 59),
 *       false en caso contrario.
 */
bool es_hora_valida(float horario);

/* Pre-condiciones: -
 * Post-condiciones: Devuelve true si la nota está entre 1 y 10 inclusive,
 *       false en caso contrario.
 */
bool es_nota_valida(int nota);

/* Pre-condiciones: El parámetro respuesta debe ser 'T', 'N', 'C' o 'A'
 * Post-condiciones: Devuelve el puntaje asociado al transporte elegido.
 */
int obtener_puntaje_transporte(char respuesta);

/* Pre-condiciones: El parámetro respuesta debe ser 'B', 'P', 'K' o 'G'
 * Post-condiciones: Devuelve el puntaje asociado a la opción elegida para la manifestación.
 */
int obtener_puntaje_manifestacion(char respuesta);

/* Pre-condiciones: La nota debe estar entre 1 y 10 inclusive.
 * Post-condiciones: Devuelve el multiplicador correspondiente según la nota obtenida.
 */
int obtener_multiplicador(int nota);

/* Pre-condiciones: puntaje_transporte >= 0, puntaje_manifestacion >= 0, multiplicador > 0.
 * Post-condiciones: Devuelve el puntaje final calculado a partir de los parámetros recibidos.
 */
int obtener_puntaje_final(int puntaje_transporte, int puntaje_manifestacion, 
                          int multiplicador);

/* Pre-condiciones: puntaje >= 0 y 0.00 <= horario <= 23.59.
 * Post-condiciones: Devuelve el personaje correspondiente según el puntaje obtenido
 *       y el horario de llegada.
 */
char obtener_personaje(int puntaje, float horario);

/* Pre-condiciones: El parámetro personaje debe ser 'S', 'O', 'J' o 'R'
 * Post-condiciones: Imprime por pantalla el personaje obtenido y la explicación del resultado.
 */
void imprimir_personaje(char personaje);

/* Pre-condiciones: -
 * Post-condiciones: Ejecuta un cuestionario solicitando datos al usuario,
 *       validando las entradas, calculando el puntaje final y
 *       devolviendo el personaje obtenido.
 */
char hacer_cuestionario();

#endif /* __DIA_EN_LA_UNI_H__ */