#include "function.c" 
void mostrarTablero(int tamanio,char tablero[tamanio][tamanio]);
void colocarBarcosJugador(int tamanio,char tablero[tamanio][tamanio],int cantidadBarcos);
void colocarBarcosPC(int tamanio,char tablero[tamanio][tamanio],int cantidadBarcos);
void guardarDatos(struct Jugador *jugador);
void solicitarNombre(char* playerName);
void playGame(int tamanio);
void imprimirMenu(struct Jugador jugador,char option );
// void mostrarTableroJugador(char tablero[TAMANO_TABLERO][TAMANO_TABLERO]);