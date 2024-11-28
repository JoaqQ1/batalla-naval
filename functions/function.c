#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#define PATH_ARCHIVO "jugadores.txt"
#define MAX_LENGTH 20
#define CANT_BARCOS 4
#define TAM_TABLERO 4
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
void limpiarBuffer();
int obtenerEntero();
void mostrarMensajeInicio();

void showRules()
{
    printf("\n\n"
           "\033[1;34m\t\t • \033[0m\033[1;33mObjetivo:\033[0m Hundir todos los barcos de la computadora antes de que ella hunda los tuyos.\n"
           "\033[1;34m\t\t • \033[0m\033[1;33mBarcos:\033[0m Todos los barcos ocupan 1 casilla.\n"
           "\033[1;34m\t\t • \033[0m\033[1;33mColocación:\033[0m Los barcos se colocan en un tablero de NxN, en posiciones horizontales o verticales.\n"
           "\033[1;34m\t\t • \033[0m\033[1;33mTurnos:\033[0m Dispara a una coordenada del tablero enemigo.\n"
           "\033[1;34m\t\t • \033[0m\033[1;33mLa computadora responderá con un disparo en tu tablero.\n"
           "\033[1;34m\t\t • \033[0m\033[1;33mImpactos:\033[0m\n"
           "\t\t\t\033[1;34m'Agua'\033[0m si no hay barco.\n"
           "\t\t\t\033[1;32m'Tocado'\033[0m si aciertas un barco.\n"
           "\t\t\t\033[1;31m'Hundido'\033[0m si destruyes todo un barco.\n\n"
           "\033[1;34m\t\tGana:\033[0m El primer jugador en hundir todos los barcos del oponente.\n\n");
}
void showTitle()
{
    printf("\n");
    printf("\n");
    printf("\033[1;34m"); // Azul brillante para el título principal
    printf("  ____          _    _    _          _____  _      _        \n");
    printf(" |  _ \\        | |  | |  | |        / ____|| |    (_)      \n");
    printf(" | |_) |  __ _ | |_ | |_ | |  ___  | (___  | |__   _  _ __  \n");
    printf(" |  _ <  / _` || __|| __|| | / _ \\  \\___ \\ | '_ \\ | || '_ \\ \n");
    printf(" | |_) || (_| || |_ | |_ | ||  __/  ____) || | | || || |_) |\n");
    printf(" |____/  \\__,_| \\__| \\__||_| \\___| |_____/ |_| |_||_|| .__/ \n");
    printf("                                                     | |    \n");
    printf("                                                     |_|    \n");
    printf("\033[0m"); // Restablecer colores

    printf("\033[1;32m"); // Verde brillante para el subtítulo
    printf("                  BattleShip! 🚢💥\n");
    printf("\033[0m"); // Restablecer colores
    printf("\n");
    printf("\n");
}
void init()
{
    struct Jugador jugador;
    int puntos;
    requestName(jugador.nombre);
    showRules();

    do
    {
        showTitle();

        printf("   \033[1;34m--------------------------------------------------------------------------\033[0m\n");
        printf("   \033[1;33m1.\033[0m \033[1;32mJUGAR\033[0m\n");
        printf("   \033[1;33m2.\033[0m \033[1;32mPUNTAJES\033[0m\n");
        printf("   \033[1;33m3.\033[0m \033[1;32mSALIR\033[0m\n");
        printf("   \033[1;34m--------------------------------------------------------------------------\033[0m\n");
        printf("\n");

        char option;
        printf("\033[1;35m  Por favor, elija su opcion: \033[0m");
        option = getchar();

        while (getchar() != '\n')
            ;

        switch (option)
        {
        case '1':
            puntos = playGame(TAM_TABLERO);
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
            printf("\n\033[1;32m Saliendo del juego. Hasta luego!\033[0m\n");
            break;
        default:
            printf("\033[1;31m                  Opcion invalida, por favor ingrese una opcion valida.\033[0m\n");
        }
        if (option == '3')
        {
            break;
        }
        limpiarBuffer();
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
    printf("\033[1;36m   Hola \033[1;32m%s\033[0m, a continuacion veras como se juega BattleShip:\n", name);
}

void colocarBarcosJugador(int tamanio, char tablero[tamanio][tamanio], int cantidadBarcos)
{

    int fila;    // Posicion en X
    int columna; // Posicion en Y
    for (int i = 0; i < cantidadBarcos; i++)
    {

        printf("\033[1;32mPor favor, ingrese la fila donde quiere que se ubique a su barco %d\033[0m\n", (1 + i));
        // scanf("%d", &fila);
        fila = obtenerEntero();
        while (fila < 0 || fila >= tamanio)
        {
            printf("\n\t\033[1;31mError!. Por favor, ingrese una fila que este dentro del rango [0,%d]\033[0m\n", tamanio);
            while (getchar() != '\n')
                ;
            scanf("%d", &fila);
        }
        printf("\033[1;32mPor favor, ingrese la columna donde quiere que se ubique a su barco %d\033[0m\n", (1 + i));
        // scanf("%d", &columna);
        columna = obtenerEntero();
        while (columna < 0 || columna >= tamanio)
        {
            printf("\n\t\033[1;31mPor favor, ingrese una columna que este dentro del rango [0,%d]\033[0m\n", tamanio);
            while (getchar() != '\n')
                ;
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
                        printf("\n\n\t\t\033[1;31mEn las coordenadas [%d,%d] ya hay un barco\033[0m\n\t\t\033[1;33mPor favor, re ingrese otras coordenadas\033[0m\n\n", fila, columna);
                        i--;
                    }
                }
            }
        }

        mostrarTablero(tamanio, tablero);
    }
}
int obtenerEntero()
{
    int numero;
    while (scanf("%d", &numero) != 1)
    {
        // Si la entrada no es un número, mostramos un mensaje y limpiamos el buffer
        printf("\033[1;31mEntrada inválida, por favor ingrese un número entero.\033[0m\n");
        limpiarBuffer();
        printf("\033[1;32mPor favor, ingrese un número válido: \033[0m");
    }
    return numero;
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

    int posicionesEnemigas[CANT_BARCOS][2];// => 2 por las posiciones (x,y)
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

    mostrarMensajeInicio();
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

        printf("\n\n%*s\033[1;31m███████████████████████████████████████████\033[0m\n", (margen - 6), "");
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
        printf("\033[1;31mCoordenadas invalidas. Por favor ingrese valores entre 0 y %d para ambos x e y.\033[0m\n", tamanio - 1);
        return 0; // Las coordinadas son inválidas
    }
}
// Función que valida el tiro
int validateShot(int tamanio, char tablero[tamanio][tamanio], int x, int y)
{
    if (tablero[x][y] == 'O' || tablero[x][y] == 'X')
    {
        printf("\033[1;33mLa posición (%d, %d) ya ha sido atacada. Intenta con otro lugar.\033[0m\n", x, y);
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
        printf("\033[1;34mIngresa la coordenada X: \033[0m");
        x = obtenerEntero();
        printf("\033[1;34mIngresa la coordenada Y: \033[0m");
        y = obtenerEntero();
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
        if (strcmp(jugadores.nombre, jugador.nombre) == 0)
        {

            jugadores.puntos += jugador.puntos;
            int posicion = ftell(archivo) - sizeof(struct Jugador);
            fseek(archivo, posicion, SEEK_SET);
            fwrite(&jugadores, sizeof(struct Jugador), 1, archivo);
            fclose(archivo);
            return;
        }
        fread(&jugadores, sizeof(struct Jugador), 1, archivo);
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
        printf("Presione enter para continuar..");
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
void mostrarMensajeInicio() {
    // Código ANSI para el color verde
    printf("\033[1;32m");  // Establece el texto en verde brillante
    
    // Mensaje
    printf("   _____                   _                                 _     _                            \n");
    printf("  / ____|                 (_)                               | |   (_)                           \n");
    printf(" | |      ___   _ __ ___   _   ___  _ __   ____ __ _    ___ | |    _  _   _   ___   __ _   ___  \n");
    printf(" | |     / _ \\ | '_ ` _ \\ | | / _ \\| '_ \\ |_  // _` |  / _ \\| |   | || | | | / _ \\ / _` | / _ \\ \n");
    printf(" | |____| (_) || | | | | || ||  __/| | | | / /| (_| | |  __/| |   | || |_| ||  __/| (_| || (_) |\n");
    printf("  \\_____|\\___/ |_| |_| |_||_| \\___||_| |_|/___|\\__,_|  \\___||_|   | | \\__,_| \\___| \\__, | \\___/ \n");
    printf("                                                                 _/ |               __/ |       \n");
    printf("                                                                |__/               |___/        \n");
    printf("\nComienza el juego\n");
    
    // Restablecer color al predeterminado
    printf("\033[0m");
}