# TP3 – Algoritmos I (FIUBA)

Tercera y última parte del Trabajo Práctico de Algoritmos I.

En este TP se implementa la **lógica completa del juego**, incluyendo la interacción del jugador con el entorno, el manejo de movimientos, rotaciones, herramientas y condiciones de victoria o derrota.

## 🎯 Objetivo
Ayudar a Mike Wazowski a recolectar todos los papeleos en el orden correcto a lo largo de **tres niveles**, evitando obstáculos y gestionando correctamente los movimientos disponibles.

## 🧩 Funcionalidades principales
- Movimiento lateral y rotacional del jugador
- Gravedad y caídas
- Uso de martillos y extintores
- Interacción con obstáculos y herramientas
- Recolección ordenada de papeleos
- Aparición de obstáculos dinámicos (Randall y paredes aleatorias)
- Manejo de estados del juego (jugando, ganado, perdido)

## 🛠️ Conceptos trabajados
- Validación de entradas del usuario
- Uso de estructuras de datos (`struct`)  
- Modularización y separación de responsabilidades  
- Gestión de estados del juego  
- Uso de bibliotecas externas (`utiles.o`)  
- Refactorización y reducción de duplicación  
- Buenas prácticas en C  


## 📌 Compilación
El proyecto se compila utilizando:

```bash
gcc *.c utiles.o -o juego -std=c99 -Wall -Wconversion -Werror -lm
```
## ▶️ Ejecución 
```bash
./juego
```