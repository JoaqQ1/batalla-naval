#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define PATH_ARCHIVO "jugadores.txt"
struct Jugador{
    char * nombre;
    int puntos;
};

void requestName(char nombre[]);
void mostrarTablero(int tamanio, char tablero[tamanio][tamanio]);
void initializeBoard(int tamanio,char tablero[tamanio][tamanio]);
void playGame(int tamanio);
void initializeBoard(int tamanio,char tablero[tamanio][tamanio]);
void colocarBarcosJugador(int tamanio, char tablero[tamanio][tamanio], int cantidadBarcos);
void colocarBarcosPC(int tamanio, char tablero[tamanio][tamanio], int cantidadBarcos);

void solicitarNombre(char* playerName){
    printf("Enter your name: ");
    fgets(playerName, sizeof(playerName), stdin);
}


void mostrarReglas()
{
    printf("\nREGLAS DEL JUEGO: BATALLA NAVAL\n\n"
    "Objetivo: Hundir todos los barcos de la computadora antes de que ella hunda los tuyos.\n\n"
    "Barcos:\n\n"
    "Todos los barcos ocupan 3 o 2 casillas.\n"
    "Colocación: Los barcos se colocan en un tablero de 10x10, en posiciones horizontales o verticales.\n\n"
    "Turnos:\n\n"
    "Dispara a una coordenada del tablero enemigo.\n"
    "La computadora responderá con un disparo en tu tablero.\n"
    "Impactos:\n\n"
    "'Agua' si no hay barco.\n"
    "'Tocado' si aciertas un barco.\n"
    "'Hundido' si destruyes todo un barco.\n\n"
    "Gana: El primer jugador en hundir todos los barcos del oponente.\n");

}
void imprimirMenu(struct Jugador jugador,char option ){
    mostrarReglas();
    // requestName(jugador.nombre);
    do {
        printf("\n");
        printf("================================================================================\n");
        printf("                                Welcome to the BATALLA NAVAL                           \n");
        printf("================================================================================\n");
        printf("\n");
        // printf("   Hi %s, please choose an option:\n", jugador.nombre);
        printf("   --------------------------------------------------------------------------\n");
        printf("   1. PLAY THE GAME\n");
        printf("   2. SCORES\n");
        printf("   3. EXIT\n");
        printf("   --------------------------------------------------------------------------\n");
        printf("\n");

        printf("  Enter your choice: ");
        option = getchar();

        while (getchar() != '\n');

        switch (option) {
            case '1':
                printf("\nStarting the game...\n");
                playGame(4);
                break;
            case '2':
                printf("\nOpening options menu...\n");
                break;
            case '3':
                printf("\nExiting the game. Goodbye!\n");
                break;
            default:
                printf("\nInvalid option, please try again.\n");
        }

        if (option == '3') {
            break;
        }

    } while (1);
}




void requestName(char name[])
{
    printf("Enter your name: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Hi %s!, Welcome to Battleship.\n\n", name);
}

void colocarBarcosJugador(int tamanio, char tablero[tamanio][tamanio], int cantidadBarcos)
{

    int fila;    // Posicion en X
    int columna; // Posicion en Y
    for (int i = 0; i < cantidadBarcos; i++)
    {

        printf("Por favor, ingrese la fila donde quiere que se ubique a su barco %d\n", i);
        scanf("%d", &fila);
        while (fila < 0 || fila > tamanio)
        {
            printf("Por favor, ingrese una fila que este dentro del rango [0,%d]\n", tamanio);
            scanf("%d", &fila);
        }
        printf("Por favor, ingrese la columna donde quiere que se ubique a su barco %d\n", i);
        scanf("%d", &columna);
        while (columna < 0 || columna > tamanio)
        {
            printf("Por favor, ingrese una columna que este dentro del rango [0,%d]\n", tamanio);
            scanf("%d", &columna);
        }

        for (int z = 0; z < tamanio; z++)
        {
            for (int j = 0; j < tamanio; j++)
            {
                if (z == fila && j == columna)
                {
                    if (tablero[fila][columna] != 'B')
                    {
                        tablero[fila][columna] = 'B';
                    }
                    else
                    {
                        printf("\n\n\t\tEn las coordenadas [%d,%d] ya hay un barco\n\t\tPor favor, re ingrese otras coordenadas\n\n", fila, columna);
                        i--;
                    }
                }
            }
        }

        mostrarTablero(tamanio, tablero);
    }
}

void mostrarTablero(int tamanio, char tablero[tamanio][tamanio])
{

    for (int i = 0; i < tamanio; i++)
    {
        printf("\t|");
        for (int j = 0; j < tamanio; j++)
        {
            printf("  %c  ", tablero[i][j]);
        }
        printf("|\n");
    }
}
void colocarBarcosPC(int tamanio, char tablero[tamanio][tamanio], int cantidadBarcos)
{
    srand(time(NULL));
    for (int i = 0; i < cantidadBarcos; i++)
    {
        int fila = rand() % tamanio;
        int columna = rand() % tamanio;
        for (int z = 0; z < tamanio; z++)
        {
            for (int j = 0; j < tamanio; j++)
            {
                if (z == fila && j == columna)
                {
                    if (tablero[z][j] != 'B')
                    {
                        tablero[z][j] = 'B';
                    }
                    else
                    {
                        i--;
                    }
                }
            }
        }
    }
    mostrarTablero(tamanio, tablero);
}
void limpiarBuffer()
{
    int c;
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
    {
        // Consumir y descartar caracteres del buffer
    }
}
void guardarDatos(struct Jugador *jugador)
{
    struct Jugador jugadores;
    printf("ENTRE");
    FILE *archivoLectura = fopen(PATH_ARCHIVO, "r");
    fread(&jugadores, sizeof(struct Jugador), 1, archivoLectura);
    printf("%s",jugadores.nombre);
    fclose(archivoLectura);
    // if(archivoLectura==NULL){
    //     archivoLectura = fopen(PATH_ARCHIVO, "w");
    //     fwrite(jugador,sizeof(struct Jugador),1,archivoLectura);
    //     fclose(archivoLectura);
    //     printf("Escribi con exito\n");
    //     archivoLectura = fopen(PATH_ARCHIVO, "r");
        // while (jugadores!=NULL)
        // {
        //     fread(jugadores, sizeof(struct Jugador), 1, archivoLectura);
        //     printf("%s,%d\n",jugadores->nombre,jugadores->puntos);
        // }
        
    //     fclose(archivoLectura);
    //     return;
    // }
    // FILE *archivoLectura = fopen(PATH_ARCHIVO, "r");
    // struct Jugador jug;
    // printf("NOMBRE:%s\nPUNTOS:%d\n",jug.nombre,jug.puntos);

}
void initializeBoard(int tamanio,char tablero[tamanio][tamanio])
{
    for (int i = 0; i < tamanio; i++)
    {
        for (int j = 0; j < tamanio; j++)
        {
            tablero[i][j] = '-';
        }
    }
}
void playGame(int tamanioTablero){

    char tablero[tamanioTablero][tamanioTablero];
    initializeBoard(tamanioTablero,tablero);
    mostrarTablero(tamanioTablero,tablero);
    colocarBarcosJugador(tamanioTablero,tablero,4);
    printf("\n\n");
    colocarBarcosPC(tamanioTablero,tablero,4);
}