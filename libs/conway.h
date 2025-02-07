#ifndef CONWAY_H_INCLUDED
#define CONWAY_H_INCLUDED

#define MINFIL      18  //minimo necesario para inicializar el oscilador
#define MINCOL      38  //minimo necesario para que funcione el cañon de planeadores

///Estados definitivos
#define MUERTA      0
#define VIVA        1

///Estados intermedios (que luego serán reemplazados por uno respectivo del primer tipo)
#define MURIENDO    2
#define NACIENDO    3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <SDL.h>

void* mamock(size_t tam);
int** crearTablero(unsigned filas, unsigned col);
void destruirTablero(int** tablero, unsigned filas);
void ponerTableroEnCero(int** tablero, unsigned filas, unsigned col);
void procesarCelulasVecinas(int** tablero, unsigned filas, unsigned col);
void actualizarEstadoCelulas(int** tablero, unsigned filas, unsigned col);
void inicializarPlaneador(int** tablero, unsigned filas, unsigned col);
void inicializarOscilador(int** tablero, unsigned filas, unsigned col);
void inicializarPulsador(int** tablero, unsigned filas, unsigned col);
void inicializarCanionDePlaneadores(int** tablero, unsigned filas, unsigned col);
void inicializarRandom(int** tablero,unsigned filas, unsigned col);
void mostrarTableroSDL(int** tablero, unsigned filas, unsigned col, SDL_Renderer** renderer);
int crearArchivosPatrones();
int levantarArchivo(int** tablero, unsigned filas, unsigned col, const char* nomArch);
int inicializarPatronesArch(int** tablero, unsigned filas, unsigned col, const char* patron);

///En desuso
int enteroMayorIgualA(int liminf);
int inicializarPatrones(int** tablero, unsigned filas, unsigned col, char* patron);
void menuIni(int** tablero, unsigned filas, unsigned col, char* patron);
void mostrarTablero(int **tablero, unsigned filas, unsigned col);
#endif // CONWAY_H_INCLUDED
