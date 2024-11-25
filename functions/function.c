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
void *ordenarJugadores();
void requestName(char nombre[]);
int playGame(int tamanioTablero);
void showTitle();
void initializeBoard(int tamanio, char tablero[tamanio][tamanio]);
void mostrarTablero(int tamanio, char tablero[tamanio][tamanio]);
void colocarBarcosJugador(int tamanio, char tablero[tamanio][tamanio], int cantidadBarcos);
void colocarBarcosPC(int tamanio, char tablero[tamanio][tamanio], int cantidadBarcos, int posicionesEnemigas[cantidadBarcos][2]);
bool turnoJugador(int tamanio, char tableroPC[tamanio][tamanio], int cantidadBarcos, int posicionesEnemigas[cantidadBarcos][2], int *barcosEnemigos);
void PCTurn(int tamanio, char tableroJugador[tamanio][tamanio], int *barcosJugador);
int cantidadJugadores();
void *getJugadores();
void guardar(struct Jugador jugador);
void actualizar(struct Jugador jugador);
void mostrarJugadores();
bool existeElJugador(struct Jugador jugador);
void mostrarMensajeGanaste();
void mostrarMensajePerdiste();

void showRules()
{
    printf("\n\n"
           "\t\t • Objetivo: Hundir todos los barcos de la computadora antes de que ella hunda los tuyos.\n"
           "\t\t • Barcos: Todos los barcos ocupan 1 casilla.\n"
           "\t\t • Colocación: Los barcos se colocan en un tablero de NxN, en posiciones horizontales o verticales.\n"
           "\t\t • Turnos: Dispara a una coordenada del tablero enemigo.\n"
           "\t\t • La computadora responderá con un disparo en tu tablero.\n"
           "\t\t • Impactos: \n\t\t\t'Agua' si no hay barco.\n\t\t\t'Tocado' si aciertas un barco.\n\t\t\t'Hundido' si destruyes todo un barco.\n\n"
           "\t\tGana: El primer jugador en hundir todos los barcos del oponente.\n\n");
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
    printf("                  BattleShip! 🚢💥\n");
    printf("\n");
    printf("\n");
}
void init()
{
    char option;
    struct Jugador jugador;
    int puntos;
    showRules();
    requestName(jugador.nombre);
    do
    {
        showTitle();
        printf("   Hola %s, por favor ingrese una opcion:\n", jugador.nombre);
        printf("   --------------------------------------------------------------------------\n");
        printf("   1. JUGAR\n");
        printf("   2. PUNTAJES\n");
        printf("   3. SALIR\n");
        printf("   --------------------------------------------------------------------------\n");
        printf("\n");

        printf("  Elija su opcion: ");
        option = getchar();

        while (getchar() != '\n')
            ;

        switch (option)
        {
        case '1':
            puntos = playGame(4);
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
            mostrarJugadores();
            break;
        case '3':
            printf("\n Saliendo del juego. Hasta luego!\n");
            break;
        default:
            printf("\033[1;31m                  Opcion invalida, por favor ingrese una opcion valida.\033[0m\n");
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
    printf("Por favor, ingrese su nombre: ");
    fgets(name, 50, stdin);           // Guarda el nombre del jugador en name
    name[strcspn(name, "\n")] = '\0'; // Se elimina el salto de linea
    while (verifyName(name))
    {
        printf("Nombre invalido, '%s'. Por favor, reingrese su nombre de nuevo: ", name);
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = '\0';
    }
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
        printf("Por favor, ingrese la columna donde quiere que se ubique a su barco %d\n", (1 + i));
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
    int margen = (80 - (tamanio * 6)) / 2;
    printf("%*s    ", margen, ""); // Espacio para centrar encabezados
    for (int i = 0; i < tamanio; i++)
    {
        printf("  %d   ", i); // Encabezado de columnas
    }
    printf("\n");

    printf("%*s   ", margen, "");
    for (int i = 0; i < tamanio; i++)
    {
        printf("──────"); // Separadores superiores
    }
    printf("\n");

    for (int i = 0; i < tamanio; i++)
    {
        printf("%*s%d  |", margen, "", i); // Etiqueta de filas
        for (int j = 0; j < tamanio; j++)
        {
            if (tablero[i][j] == 'X') // Tiro acertado
                printf("\033[1;31m  %c  \033[0m|", tablero[i][j]);
            else if (tablero[i][j] == 'O') // Tiro fallido
                printf("\033[1;34m  %c  \033[0m|", tablero[i][j]);
            else if (tablero[i][j] == 'B') // Barco
                printf("\033[1;32m  %c  \033[0m|", tablero[i][j]);
            else
                printf("  %c  |", tablero[i][j]);
        }
        printf("\n");

        printf("%*s   ", margen, "");
        for (int j = 0; j < tamanio; j++)
        {
            printf("──────");
        }
        printf("\n");
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
void mostrarMensajeGanaste()
{
    printf("\n");
    printf("   _____                            _        \n");
    printf("  / ____|                          | |       \n");
    printf(" | |  __   __ _  _ __    __ _  ___ | |_  ___ \n");
    printf(" | | |_ | / _` || '_ \\  / _` |/ __|| __|/ _ \\\n");
    printf(" | |__| || (_| || | | || (_| |\\__ \\| |_|  __/\n");
    printf("  \\_____| \\__,_||_| |_| \\__,_||___/ \\__|\\___|\n");
    printf("                                             \n");
    printf("                                             \n");
    printf("\033[1;32m                  ¡Ganaste! 🎉\033[0m\n");
    printf("\n");
}
void mostrarMensajePerdiste()
{
    printf("\n");
    printf("   _____                _  _       _        \n");
    printf("  |  __ \\              | |(_)     | |       \n");
    printf("  | |__) |___  _ __  __| | _  ___ | |_  ___ \n");
    printf("  |  ___// _ \\| '__|/ _` || |/ __|| __|/ _ \\\n");
    printf("  | |   |  __/| |  | (_| || |\\__ \\| |_|  __/\n");
    printf("  |_|    \\___||_|   \\__,_||_||___/ \\__|\\___|\n");
    printf("                                            \n");
    printf("                                            \n");
    printf("\033[1;31m                  ¡Perdiste! 😢\033[0m\n");
    printf("\n");
}

void initializeBoard(int tamanio, char tablero[tamanio][tamanio])
{
    for (int i = 0; i < tamanio; i++)
    {
        for (int j = 0; j < tamanio; j++)
        {
            tablero[i][j] = '~';
        }
    }
}
int playGame(int tamanioTablero)
{
    int puntos = 0;
    int barcosPropios = 4;
    int barcosEnemigos = 4;
    int turnos = 0;
    int tirosAcertados = 0;
    int tirosFallados = 0;

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
        turnos++;
        bool aciertoJugador = turnoJugador(tamanioTablero, tableroPcMuestra, 4, posicionesEnemigas, &barcosEnemigos);
        if (aciertoJugador)
        {
            tirosAcertados++;
            puntos += 10; // Bonificación por cada impacto acertado
        }
        else
        {
            tirosFallados++;
            puntos -= 2; // Penalización por un disparo fallido
        }
        PCTurn(tamanioTablero, tablero, &barcosPropios);
        int margen = (80 - (tamanioTablero * 6)) / 2; // Margen para centrar (aprox.)
        printf("\n%*s\033[1;36m███████████████████████████████████████████\033[0m\n", (margen - 6), "");
        printf("%*s\033[1;36m█                TU TABLERO               █\033[0m\n", (margen - 6), "");
        printf("%*s\033[1;36m███████████████████████████████████████████\033[0m\n\n", (margen - 6), "");
        mostrarTablero(tamanioTablero, tablero);

        printf("\n%*s\033[1;31m███████████████████████████████████████████\033[0m\n", (margen - 6), "");
        printf("%*s\033[1;31m█             TABLERO ENEMIGO             █\033[0m\n", (margen - 6), "");
        printf("%*s\033[1;31m███████████████████████████████████████████\033[0m\n\n", (margen - 6), "");
        mostrarTablero(tamanioTablero, tableroPcMuestra);
        printf("\n\n");
        if (barcosEnemigos == 0)
        {
            puntos += barcosPropios * 20;
            puntos += 50 - turnos;
            mostrarMensajeGanaste();
            break;
        }
        else if (barcosPropios == 0)
        {
            mostrarMensajePerdiste();
            break;
        }
    }
    if (puntos < 0)
        puntos = 0;
    printf("\n\n\033[1;34mEstadísticas del Juego:\033[0m\n");
    printf("Tiros Acertados: %d\n", tirosAcertados);
    printf("Tiros Fallidos: %d\n", tirosFallados);
    printf("Turnos Totales: %d\n", turnos);
    printf("Puntos Finales: \033[1;32m%d\033[0m\n", puntos);
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
        printf("Coordenadas invalidas. Por favor ingrese valores entre 0 y %d para ambos x e y.\n", tamanio - 1);
        return 0; // Las coordinadas son inválidas
    }
}
// Función que valida el tiro
int validateShot(int tamanio, char tablero[tamanio][tamanio], int x, int y)
{
    if (tablero[x][y] == 'O' || tablero[x][y] == 'X')
    {
        printf("La posición (%d, %d) ya ha sido atacada. Intenta con otro lugar.\n", x, y);
        return 0;
    }
    else
    {
        return 1;
    }
}

bool turnoJugador(int tamanio, char tableroPC[tamanio][tamanio], int cantidadBarcos, int posicionesEnemigas[cantidadBarcos][2], int *barcosEnemigos)
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
            printf("\033[1;32m¡Acertaste y hundiste un barco!\033[0m\n");
            tableroPC[x][y] = 'X';
            (*barcosEnemigos)--;
            return true;
        }
    }
    printf("\033[1;31mFallaste.\033[0m\n");
    tableroPC[x][y] = 'O';
    return false;
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
        printf("\033[1;33mEl enemigo ha disparado a la posición (%d, %d).\033[0m\n", randomRowPosition, randomColumnPosition);
        printf("\033[1;31mEl enemigo ha hundido uno de tus barcos.\033[0m\n");
        (*barcosJugador)--;
    }
    else
    {
        tableroJugador[randomRowPosition][randomColumnPosition] = 'O'; // Agua
        printf("\033[1;33mEl enemigo ha disparado a la posición (%d, %d).\033[0m\n", randomRowPosition, randomColumnPosition);
        printf("\033[1;32mEl enemigo ha fallado.\033[0m\n");
    }
}

void *getJugadores()
{
    FILE *archivo = fopen(PATH_ARCHIVO, "r");
    struct Jugador *jugadores;
    int cantJugadores = cantidadJugadores();
    if (cantJugadores == 0)
    {
        return NULL;
    }
    else
    {
        jugadores = (struct Jugador *)malloc(cantJugadores * sizeof(struct Jugador));
        int i = 0;
        fread((jugadores + i), sizeof(struct Jugador), 1, archivo);
        while (!feof(archivo))
        {
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
    {
        printf("\033[1;33m\n----------------------------------------\033[0m\n");
        printf("\033[1;31m     No hay jugadores registrados.\033[0m\n");
        printf("\033[1;33m----------------------------------------\033[0m\n\n");
        return 0;
    }
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
            // FILE *archivo = fopen(PATH_ARCHIVO, "r+");
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
    struct Jugador *jugadoresOrdenados = ordenarJugadores();
    if (jugadoresOrdenados != NULL)
    {

        printf("\033[1;34m\n\t-----------------------------------\033[0m\n");
        printf("\033[1;36m\t       RANKING DE JUGADORES     \033[0m\n");
        printf("\033[1;34m\t-----------------------------------\033[0m\n");
        printf("\033[1;33m\t %-20s %-10s\033[0m\n", "Jugador", "Puntos");
        printf("\033[1;34m\t-----------------------------------\033[0m\n");

        for (int i = 0; i < cantidadJugadores(); i++)
        {
            printf("\033[1;32m\t %d. %-18s %-10d\033[0m\n", i + 1, (jugadoresOrdenados + i)->nombre, (jugadoresOrdenados + i)->puntos);
        }

        printf("\033[1;34m\t-----------------------------------\033[0m\n\n");
    }
}

void *ordenarJugadores()
{
    struct Jugador *jugadores = getJugadores();
    if (jugadores != NULL)
    {
        int cantJugadores = cantidadJugadores();

        for (int i = 1; i < cantJugadores; i++)
        {
            struct Jugador jugadorActual;
            strcpy(jugadorActual.nombre, (jugadores + i)->nombre);
            jugadorActual.puntos = (jugadores + i)->puntos;
            int j = i - 1;

            while (j >= 0 && (jugadores + j)->puntos < jugadorActual.puntos)
            {
                strcpy((jugadores + j + 1)->nombre, (jugadores + j)->nombre);
                (jugadores + j + 1)->puntos = (jugadores + j)->puntos;
                j--;
            }
            strcpy((jugadores + j + 1)->nombre, jugadorActual.nombre);
            (jugadores + j + 1)->puntos = jugadorActual.puntos;
        }
        return jugadores;
    }
    return NULL;
}