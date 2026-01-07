# TP1 – Algoritmos I (FIUBA)

Primera parte del Trabajo Práctico de Algoritmos I.

En este TP se implementa un **cuestionario interactivo en lenguaje C** que, a partir de distintas respuestas del usuario, determina un personaje final según un sistema de puntajes y reglas establecidas.

---

## 🎯 Objetivo
Evaluar los conceptos fundamentales de la programación estructurada mediante la interacción con el usuario, la validación de datos ingresados y la aplicación de lógica condicional para la toma de decisiones.

---

## 🧩 Funcionalidades principales
- Comunicación con el usuario mediante consola
- Validación estricta de entradas (caracteres, enteros y números decimales)
- Repetición de preguntas ante datos inválidos
- Cálculo de puntajes según respuestas ingresadas
- Uso de un multiplicador en base a la nota obtenida
- Determinación del personaje final según puntaje y horario de llegada

---

## 🧠 Personajes posibles
- **Olaf (O)**  
- **Stitch (S)**  
- **Jasmín (J)**  
- **Rayo McQueen (R)**  

El personaje se determina combinando el puntaje total y el horario de llegada al examen.

---

## 🛠️ Conceptos trabajados
- Validación de datos ingresados por el usuario
- Tipos de datos simples (`int`, `float`, `char`)
- Uso de estructuras de control (`if`, `while`)
- Modularización mediante funciones
- Buenas prácticas de programación en C

---

## 📌 Compilación
El programa se compila utilizando:

```bash
gcc dia_en_la_uni.c -Wall -Werror -Wconversion -std=c99 -o dia_en_la_uni
