#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int** crearTablero(unsigned filas, unsigned col);
void destruirTablero(int** tablero, unsigned filas);
void ponerTableroEnCero(int** tablero, unsigned filas, unsigned col);
void inicializarCanionDePlaneadores(int** tablero, int filas, int col);
void mostrarTablero(int **tablero, int filas, int col);
int levantarArchivo(int** tablero, int filas, int col, const char* patron);

#define FILA 18
#define COL  38

#define MINFIL 18
#define MINCOL 38

int main(){

    int** tablero;

    tablero = crearTablero(FILA,COL);
    ponerTableroEnCero(tablero,FILA,COL);

    if(levantarArchivo(tablero,FILA,COL,"canion-de-planeadores") == -1 )
        return -1;

    mostrarTablero(tablero,FILA,COL);
    destruirTablero(tablero,FILA);

    return 0;
}

int** crearTablero(unsigned filas, unsigned col){

    int i, **ini;
    int** tablero = malloc(filas*sizeof(int*));

    if(!tablero)
        return NULL;

    ini = tablero;

    for(i=0;i<filas;i++){

        *tablero = malloc(col*sizeof(int));
        if(!(*tablero)){
            destruirTablero(ini,i);
            return NULL;
        }
        tablero++;
    }

    return ini;
}

void destruirTablero(int** tablero, unsigned filas){

    int i;
    for(i=0;i<filas;i++)
        free(tablero[i]);

    free(tablero);
}

void ponerTableroEnCero(int** tablero, unsigned filas, unsigned col){

    int i,j;
    for(i=0;i<filas;i++){
        for(j=0;j<col;j++){
            tablero[i][j] = 0;
        }
    }
}

void mostrarTablero(int** tablero, int filas, int col)
{
    int i,j;
    ///Se ocultan dos filas y dos columnas para no tocar memoria que no es nuestra durante la logica del programa
    for(i=1;i<filas-1;i++)
        {
            for(j=1;j<col-1;j++)
                {
                   // printf("%d",m[i][j]); para debug, permite ver el numero perteneciente a cada estado
                        if(!tablero[i][j])
                            printf(" ");
                        else
                            printf("O");
                }
            printf("\n");
        }
}

void inicializarCanionDePlaneadores(int** tablero, int filas, int col)
{
    //inicializado arriba de todo en una esquina así se ven caer bien a los planeadores

    tablero[5][1]++;
    tablero[5][2]++;
    tablero[6][1]++;
    tablero[6][2]++;

    tablero[3][13]++;
    tablero[3][14]++;
    tablero[4][12]++;
    tablero[5][11]++;
    tablero[6][11]++;
    tablero[7][11]++;
    tablero[8][12]++;
    tablero[9][13]++;
    tablero[9][14]++;

    tablero[6][15]++;
    tablero[4][16]++;
    tablero[5][17]++;
    tablero[7][17]++;
    tablero[6][17]++;
    tablero[6][18]++;
    tablero[8][16]++;

    tablero[3][21]++;
    tablero[4][21]++;
    tablero[5][21]++;
    tablero[3][22]++;
    tablero[4][22]++;
    tablero[5][22]++;
    tablero[6][23]++;
    tablero[2][23]++;
    tablero[2][25]++;
    tablero[1][25]++;
    tablero[6][25]++;
    tablero[7][25]++;

    tablero[4][35]++;
    tablero[3][35]++;
    tablero[3][36]++;
    tablero[4][36]++;
}

int levantarArchivo(int** tablero, int filas, int col, const char* patron){

    int i=1,j = 1;
    char nomArch[26], linea[40], aux[2],*pLinea,*pAux;
    FILE* fp;

    strcpy(nomArch,patron);
    strcat(nomArch,".txt");

    fp = fopen(nomArch, "rt");
    if(!fp){
        puts("No se pudo abrir el archivo.");
        return -1;
    }

    while(fgets(linea,MINCOL+1,fp)){

        pLinea = linea;
        puts(linea);

        //printf("%d",strlen(linea));
        //system("pause");

        for(j=1;j<MINCOL-1;j++){
            strncpy(aux,pLinea,1);
            *(aux+1) = '\0';
            //puts(aux);
            sscanf(aux,"%d",&(tablero[i][j]));
            pLinea++;
        }
        i++;
    }

    fclose(fp);
    return 1;
}
