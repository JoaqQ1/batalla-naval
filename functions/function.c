#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#define PATH_ARCHIVO "jugadores.txt"
#define MAX_LENGTH 20
struct Jugador
{
    char nombre[MAX_LENGTH];
    int puntos;
};

void requestName(char nombre[]);
int playGame(int tamanio);
void showTitle();
void showTitleScore();
void initializeBoard(int tamanio, char tablero[tamanio][tamanio]);
void mostrarTablero(int tamanio, char tablero[tamanio][tamanio]);
void colocarBarcosJugador(int tamanio, char tablero[tamanio][tamanio], int cantidadBarcos);
void colocarBarcosPC(int tamanio, char tablero[tamanio][tamanio], int cantidadBarcos, int posicionesEnemigas[cantidadBarcos][2]);
void turnoJugador(int tamanio, char tableroPC[tamanio][tamanio], int cantidadBarcos, int posicionesEnemigas[cantidadBarcos][2], int *barcosEnemigos);
void PCTurn(int tamanio, char tableroJugador[tamanio][tamanio], int *barcosJugador);
int cantidadJugadores();
void *getJugadores();
void guardar(struct Jugador jugador);
void actualizar(struct Jugador jugador);
void mostrarJugadores();
bool existeElJugador(struct Jugador jugador);

void showRules()
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
void showTitle()
{
    printf("\n");
    printf("\n");
    printf("  ____          _    _    _          _____  _      _        \n");
    printf(" |  _ \\        | |  | |  | |        / ____|| |    (_)      \n");
    printf(" | |_) |  __ _ | |_ | |_ | |  ___  | (___  | |__   _  _ __  \n");
    printf(" |  _ <  / _` || __|| __|| | / _ \\  \\___ \\ | '_ \\ | || '_ \\ \n");
    printf(" | |_) || (_| || |_ | |_ | ||  __/  ____) || | | || || |_) |\n");
    printf(" |____/  \\__,_| \\__| \\__||_| \\___| |_____/ |_| |_||_|| .__/ \n");
    printf("                                                     | |    \n");
    printf("                                                     |_|    \n");
    printf("\n");
    printf("\n");
}
void init()
{
    char option;
    struct Jugador jugador;
    showRules();
    requestName(jugador.nombre);
    do
    {
        showTitle();
        printf("   Hi %s, please choose an option:\n", jugador.nombre);
        printf("   --------------------------------------------------------------------------\n");
        printf("   1. PLAY THE GAME\n");
        printf("   2. SCORES\n");
        printf("   3. EXIT\n");
        printf("   --------------------------------------------------------------------------\n");
        printf("\n");

        printf("  Enter your choice: ");
        option = getchar();

        while (getchar() != '\n')
            ;

        switch (option)
        {
        case '1':
            printf("\nStarting the game...\n");
            int puntos = playGame(4);
            jugador.puntos = puntos;
            if (existeElJugador(jugador))
            {
                actualizar(jugador);
            }
            else
            {
                guardar(jugador);
            }
            break;
        case '2':
            showTitleScore();
            mostrarJugadores();
            break;
        case '3':
            printf("\nExiting the game. Goodbye!\n");
            break;
        default:
            printf("\nInvalid option, please try again.\n");
        }

        if (option == '3')
        {
            break;
        }

    } while (1);
}

int verifyName(const char name[])
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isspace((unsigned char)name[i]))
        {
            return 0; // No es inválido si al menos un carácter no es espacio
        }
    }
    return 1; // Si todos los caracteres son espacios o la cadena está vacía
}
void requestName(char name[])
{
    printf("Enter your name: ");
    fgets(name, 50, stdin);           // Guarda el nombre del jugador en name
    name[strcspn(name, "\n")] = '\0'; // Se elimina el salto de linea
    while (verifyName(name))
    {
        printf("Invalid name. It cannot be empty or only spaces. Please try again: ");
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = '\0';
    }

    printf("Hi %s!, Welcome to Battleship.\n\n", name);
}

void colocarBarcosJugador(int tamanio, char tablero[tamanio][tamanio], int cantidadBarcos)
{

    int fila;    // Posicion en X
    int columna; // Posicion en Y
    for (int i = 0; i < cantidadBarcos; i++)
    {

        printf("Por favor, ingrese la fila donde quiere que se ubique a su barco %d\n", (1 + i));
        scanf("%d", &fila);
        while (fila < 0 || fila >= tamanio)
        {
            printf("\n\tError!. Por favor, ingrese una fila que este dentro del rango [0,%d]\n", tamanio);
            scanf("%d", &fila);
        }
        printf("Por favor, ingrese la columna donde quiere que se ubique a su barco %d\n", i);
        scanf("%d", &columna);
        while (columna < 0 || columna >= tamanio)
        {
            printf("\n\tPor favor, ingrese una columna que este dentro del rango [0,%d]\n", tamanio);
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
void colocarBarcosPC(int tamanio, char tablero[tamanio][tamanio], int cantidadBarcos, int posicionesEnemigas[cantidadBarcos][2])
{

    srand(time(NULL));
    for (int i = 0; i < cantidadBarcos; i++)
    {
        int fila = rand() % tamanio;
        int columna = rand() % tamanio;
        for (int x = 0; x < tamanio; x++)
        {
            for (int y = 0; y < tamanio; y++)
            {
                if (x == fila && y == columna)
                {
                    if (tablero[x][y] != 'B')
                    {
                        posicionesEnemigas[i][0] = x;
                        posicionesEnemigas[i][1] = y;
                        tablero[x][y] = 'B';
                        printf("[%d][%d]", x, y);
                    }
                    else
                    {
                        i--;
                    }
                }
            }
        }
    }
}
void limpiarBuffer()
{
    int c;
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
    {
        // Consumir y descartar caracteres del buffer
    }
}

void initializeBoard(int tamanio, char tablero[tamanio][tamanio])
{
    for (int i = 0; i < tamanio; i++)
    {
        for (int j = 0; j < tamanio; j++)
        {
            tablero[i][j] = '-';
        }
    }
}
int playGame(int tamanioTablero)
{
    int puntos = 0;
    int barcosPropios = 4;
    int barcosEnemigos = 4;

    int posicionesEnemigas[4][2];
    char tablero[tamanioTablero][tamanioTablero];
    char tableroPcOculto[tamanioTablero][tamanioTablero];
    char tableroPcMuestra[tamanioTablero][tamanioTablero];
    initializeBoard(tamanioTablero, tablero);
    initializeBoard(tamanioTablero, tableroPcOculto);
    initializeBoard(tamanioTablero, tableroPcMuestra);
    printf("\n\n");
    colocarBarcosJugador(tamanioTablero, tablero, 4);
    printf("\n\n");
    colocarBarcosPC(tamanioTablero, tableroPcOculto, 4, posicionesEnemigas);

    showTitle();
    while (barcosEnemigos > 0 && barcosPropios > 0)
    {
        turnoJugador(tamanioTablero, tableroPcMuestra, 4, posicionesEnemigas, &barcosEnemigos);
        PCTurn(tamanioTablero, tablero, &barcosPropios);
        printf("\n\tTABLERO");
        printf("\n\n");
        mostrarTablero(tamanioTablero, tablero);
        printf("\n\tTABLERO ENEMIGO");
        printf("\n\n");
        mostrarTablero(tamanioTablero, tableroPcMuestra);
        printf("\n\n");
        if (barcosEnemigos == 0)
        {
            puntos += 100;
            printf("GANASTE");
            break;
        }
        else if (barcosPropios == 0)
        {

            printf("PERDISTE");
        }
    }
    return puntos;
}
int validateCoordinates(int tamanio, int x, int y)
{
    if (x >= 0 && x < tamanio && y >= 0 && y < tamanio)
    {
        return 1; // Las coordenadas son válidas
    }
    else
    {
        printf("Invalid coordinates. Please enter values between 0 and %d for both x and y.\n", tamanio - 1);
        return 0; // Las coordinadas son inválidas
    }
}
// Función que valida el tiro
int validateShot(int tamanio, char tablero[tamanio][tamanio], int x, int y)
{
    if (tablero[x][y] == 'O' || tablero[x][y] == 'X')
    {
        printf("Position (%d, %d) has already been shot at. Try a different spot.\n", x, y);
        return 0;
    }
    else
    {
        return 1;
    }
}

void turnoJugador(int tamanio, char tableroPC[tamanio][tamanio], int cantidadBarcos, int posicionesEnemigas[cantidadBarcos][2], int *barcosEnemigos)
{
    int x, y;
    do
    {
        printf("Ingresa la coordenada X: ");
        scanf("%d", &x);
        printf("Ingresa la coordenada Y: ");
        scanf("%d", &y);
    } while (!validateCoordinates(tamanio, x, y) || !validateShot(tamanio, tableroPC, x, y));

    for (int i = 0; i < tamanio; i++)
    {
        if (posicionesEnemigas[i][0] == x && posicionesEnemigas[i][1] == y)
        {
            printf("¡Acertaste y hundiste un barco!\n");
            tableroPC[x][y] = 'X';
            (*barcosEnemigos)--;
            return;
        }
    }
    printf("Fallaste.\n");
    tableroPC[x][y] = 'O';
}
void PCTurn(int tamanio, char tableroJugador[tamanio][tamanio], int *barcosJugador)
{
    // Genero 2 numero aleatorios para la fila y columna
    int randomRowPosition = rand() % tamanio;
    int randomColumnPosition = rand() % tamanio;

    // Mientras la posición ya haya sido disparada, se genera nuevas coordenadas
    while (validateShot(tamanio, tableroJugador, randomRowPosition, randomColumnPosition) == 0)
    {
        randomRowPosition = rand() % tamanio;
        randomColumnPosition = rand() % tamanio;
    }

    // Se verifica si acertó en un barco
    if (tableroJugador[randomRowPosition][randomColumnPosition] == 'B')
    {
        tableroJugador[randomRowPosition][randomColumnPosition] = 'X'; // Barco hundido
        printf("PC has fired at (%d, %d)\n", randomRowPosition, randomColumnPosition);
        printf("The PC has sunk one of your ships.\n");
        (*barcosJugador)--;
    }
    else
    {
        tableroJugador[randomRowPosition][randomColumnPosition] = 'O'; // Agua
        printf("PC has fired at (%d, %d)\n", randomRowPosition, randomColumnPosition);
        printf("The PC has failed.\n");
    }
}

void *getJugadores()
{
    FILE *archivo = fopen(PATH_ARCHIVO, "r");
    struct Jugador *jugadores;
    jugadores = (struct Jugador *)malloc(cantidadJugadores() * sizeof(struct Jugador));
    if (jugadores == NULL)
    {
        printf("No se pudo reservar espacio en memoria\n");
        return NULL;
    }
    else
    {
        int i = 0;
        fread((jugadores + i), sizeof(struct Jugador), 1, archivo);
        while (!feof(archivo))
        {
            printf("%s", (jugadores + i)->nombre);
            printf(" - %d\n", (jugadores + i)->puntos);
            i++;
            fread((jugadores + i), sizeof(struct Jugador), 1, archivo);
        }

        return jugadores;
    }
}

bool existeElJugador(struct Jugador jugador)
{
    struct Jugador ju;
    FILE *archivo = fopen(PATH_ARCHIVO, "r");
    if (archivo == NULL)
        return 0;
    fread(&ju, sizeof(struct Jugador), 1, archivo);
    while (!feof(archivo))
    {
        if (strcmp(ju.nombre, jugador.nombre) == 0)
            return true;
        fread(&ju, sizeof(struct Jugador), 1, archivo);
    }
    fclose(archivo);
    return false;
}
int cantidadJugadores()
{
    int contadorJugadores = 0;
    struct Jugador ju;
    FILE *archivo = fopen(PATH_ARCHIVO, "r");
    if (archivo == NULL)
        return 0;
    fread(&ju, sizeof(struct Jugador), 1, archivo);
    while (!feof(archivo))
    {
        fread(&ju, sizeof(struct Jugador), 1, archivo);
        contadorJugadores++;
    }
    fclose(archivo);
    return contadorJugadores;
}

void guardar(struct Jugador jugador)
{
    FILE *archivo = fopen(PATH_ARCHIVO, "ab+");
    if (archivo == NULL)
        return;
    struct Jugador jugadores;
    strcpy(jugadores.nombre, jugador.nombre);
    jugadores.puntos = jugador.puntos;
    fwrite(&jugadores, sizeof(struct Jugador), 1, archivo);
    fclose(archivo);
}
void actualizar(struct Jugador jugador)
{
    FILE *archivo = fopen(PATH_ARCHIVO, "r+");
    if (archivo == NULL)
        return;
    struct Jugador jugadores;
    fread(&jugadores, sizeof(struct Jugador), 1, archivo);
    while (!feof(archivo))
    {
        fread(&jugadores, sizeof(struct Jugador), 1, archivo);
        if (strcmp(jugadores.nombre, jugador.nombre) == 0)
        {
            FILE *archivo = fopen(PATH_ARCHIVO, "r+");
            jugadores.puntos += jugador.puntos;
            int posicion = ftell(archivo) - sizeof(struct Jugador);
            fseek(archivo, posicion, SEEK_SET);
            fwrite(&jugadores, sizeof(struct Jugador), 1, archivo);
            printf("Se modifico con exito");
            fclose(archivo);
            return;
        }
    }
}
void mostrarJugadores()
{
    struct Jugador ju;
    FILE *archivo = fopen(PATH_ARCHIVO, "r");
    if (archivo == NULL)
    {
        printf("No se ingresaron jugadores aun");
        return;
    }
    fread(&ju, sizeof(struct Jugador), 1, archivo);
    printf("\n\n\tJugador\tPuntos");
    while (!feof(archivo))
    {
        printf("\n\n\t%s\t%d", ju.nombre, ju.puntos);
        fread(&ju, sizeof(struct Jugador), 1, archivo);
    }
    fclose(archivo);
}
void showTitleScore() {
    printf("   _____                              \n");
    printf("  / ____|                             \n");
    printf(" | (___    ___  ___   _ __  ___  ___  \n");
    printf("  \\___ \\  / __|/ _ \\ | '__|/ _ \\/ __| \n");
    printf("  ____) || (__| (_) || |  |  __/\\__ \\ \n");
    printf(" |_____/  \\___|\\___/ |_|   \\___||___/ \n");
    printf("                                       \n");
    printf("                                       \n");
}