#include <stdio.h>
#include <stdbool.h>
#include "functions/function.h"
#define CANT_BARCOS 3
#define TAMANIO_TABLERO 5



int main() {
    struct Jugador jugadores[] = {
        {"Joaquin",100},
        {"Luis",100},
        {"Ezequiel",200}
    };
    printf("%s",jugadores[0].nombre);
    guardarDatos(jugadores);
    // char option;
    // imprimirMenu(jugador,option);

    return 0;
}

