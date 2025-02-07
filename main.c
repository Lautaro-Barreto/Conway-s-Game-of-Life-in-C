/*

TP Tópicos de Programación
"Conway's Game of Life"

Equipo: "Debuggers"

Integrantes                     DNI
Barreto Lautaro Agustín     45.919.951
Bentancur Suárez Ismael     45.823.439
Caccavari Franco            45.128.064
Falconi Luciano Damian      44.586.160

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL_main.h>
#endif

#include <SDL.h>
#include "libs/conway.h"

/**
Pablo Soligo. Plantilla de proyecto codeblocks para juego de la vida.
Funciona con mingw 64 bits y no requiere tener instalado SDL.
Los fuentes son multiplataforma (windows/linux Debian;Ubuntu). Para ubuntu se
requiere de diferente configuración de proyecto.
*/

int main(int argc, char *argv[])
{
    //Menu de "guía", se ejecuta aunque la cantidad de argumentos sea insuficiente
    printf("---- DEBUGGER'S GAME OF LIFE ----\n \
           \nCreacion del tablero \n \
           \nRecomendado: F=48 C=64\n\n");
    printf("La cantidad de filas no debe ser menor a 18\nLa cantidad de columnas no puede ser menor a 38\n\n");
    printf("Patrones disponibles:\n\n*Oscilador\n*Canion-de-planeadores\n*Pulsador\n*Planeador\n*Random\n\n");
    printf("Argumento 1: filas del tablero\nArgumento 2: columnas del tablero \
           \nArgumento 3: patron\nArgumento 4: delay\nArgumento 5: cantidad de generaciones\n\n");
    printf("Si no se detectan los patrones, corra el comando restaurar-archivos \n\n");

     /*
    argv[0] = ruta del ejecutable
    argv[1] = filas del tablero
    argv[2] = columnas del tablero
    argv[3] = patron de inicializacion
    argv[4] = delay del SDL
    argv[5] = ciclos / generaciones
    */

    const int screen_width      = 640;
    const int screen_height     = 480;
    unsigned char done = 0;
    int **tablero, fila, col, ciclos, delay, errIni = 1, i =0;
    char patron[22];

    ///Este es un caso especial: si faltan los archivos de patrones, los restauras de esta manera
    if( strcmpi(argv[1],"restaurar-archivos") == 0){
        crearArchivosPatrones();
        puts("Los patrones han sido restaurados. Puede volver a empezar");
        return 1;
    }

    //El programa no arranca si las medidas de la matriz no son suficientes o si exceden el tamaño de la ventana
    //tambien si la cantidad de argumentos es insuficiente
    if( atoi(argv[1]) < MINFIL || atoi(argv[2]) < MINCOL ||
        atoi(argv[1]) > (screen_height/10) || atoi(argv[2]) > (screen_width/10) || argc <6 )
        return -1;

    //asignacion de los valores de los argumentos a variables del programa
    fila                    = atoi(argv[1]);
    col                     = atoi(argv[2]);
    strcpy(patron,argv[3]);
    delay                   = atoi(argv[4]);
    ciclos                  = atoi(argv[5]);

    //Inicialización SDL
    SDL_Window* window      = NULL;
    SDL_Renderer* renderer  = NULL;
    SDL_Event e;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //inicializacion del tablero

    tablero = crearTablero(fila,col);

    if(!tablero){
            puts("No se pudo inicializar el tablero");
            return -1;
    }

    ponerTableroEnCero(tablero,fila,col);
    errIni = inicializarPatronesArch(tablero,fila,col,patron);

    if(errIni == -1){
        printf("Patron no detectado");
        destruirTablero(tablero,fila);
        return -2;
    }

    //Create window
    window = SDL_CreateWindow("Juego de la vida",
                                                SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED,
                                                screen_width,
                                                screen_height,
                                                SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        destruirTablero(tablero,fila);
        return -1;
    }

    // Creamos el lienzo
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        destruirTablero(tablero,fila);
        return -1;
    }

    //Bucle del juego
    while (!done && i<ciclos){

        while (SDL_PollEvent(&e) != 0) {
            // Salida del usuario
            if (e.type == SDL_QUIT) {
                done = 1;
            }
        }
        // Se limpia la pantalla
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        //Titulo/caption de la ventana
        SDL_SetWindowTitle(window, patron);
        SDL_Delay(delay);

        //Procesamiento de tablero
        mostrarTableroSDL(tablero,fila,col,&renderer);
        procesarCelulasVecinas(tablero,fila,col); ///Primer recorrido. Evalua si una celula continua viva, nace o muere
        actualizarEstadoCelulas(tablero,fila,col); ///Segundo recorrido. Realiza los cambios pertinentes
        i++;
    }

    //destruyo todos los elementos creados
    destruirTablero(tablero,fila);
    puts("Fin del juego.");

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}



