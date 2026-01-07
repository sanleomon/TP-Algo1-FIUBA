# TP2 – Algoritmos I (FIUBA)

Segunda parte del Trabajo Práctico de Algoritmos I.

En este TP se desarrolla la **inicialización completa del juego**, preparando todas las estructuras necesarias para su posterior ejecución.

---

## 🎯 Objetivo
Inicializar correctamente el estado del juego, cargando los niveles, el jugador y todos los elementos del terreno, respetando las consignas de la cátedra y las pre y post condiciones establecidas.

---

## 🧩 Funcionalidades principales
- Inicialización de los niveles del juego
- Carga de paredes por nivel
- Posición inicial del jugador
- Inicialización de obstáculos
- Inicialización de herramientas
- Inicialización de papeleos
- Preparación del estado inicial del juego

---

## 🛠️ Conceptos trabajados
- Uso intensivo de `struct`
- Manejo de vectores con tope
- Modularización del código
- Diseño de funciones con contrato (pre y post condiciones)
- Buenas prácticas de programación en C

---

## 📌 Compilación
El proyecto se compila utilizando:

```bash
gcc *.c utiles.o -o juego -std=c99 -Wall -Wconversion -Werror -lm

---
