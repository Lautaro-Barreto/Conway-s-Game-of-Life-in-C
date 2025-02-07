#include "conway.h"

//#define malloc mamock //para debugear la funcion destruirTablero

void* mamock(size_t tam){

    if(rand()%5 == 3)
        return NULL;

    return malloc(tam);
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

void procesarCelulasVecinas(int** tablero, unsigned filas, unsigned col)
{
    int i, j, k, l, cont = 0;

    ///Se ocultan dos filas y dos columnas para no tocar memoria que no es nuestra cuando se toca un borde/esquina
    for(i=1;i<filas-1;i++)
        {
            for(j=1;j<col-1;j++)
                {
                    ///Ciclo interno donde se recorren las posiciones aledañas a cada celula
                    k=i-1;
                    while(k<=i+1){
                        l=j-1;
                        while(l<=j+1){

                            cont += tablero[k][l] == VIVA || tablero[k][l]== MURIENDO ? 1:0;
                            l++;
                        }
                        k++;
                    }
                    ///Para que se saltee la posición de la célula en el conteo
                            cont -= tablero[i][j];

                    ///Una vez fuera del ciclo, evaluamos el contador de celulas vecinas y
                    ///Actualizamos el estado de una celula a uno intermedio

                                 ///soledad                                ///Sobrepoblacion
                    if( (cont < 2 && tablero[i][j] != MUERTA ) || (cont > 3 && tablero[i][j] != MUERTA)  )
                        tablero[i][j] = MURIENDO;
                    if(cont == 3 && tablero[i][j]!= VIVA )
                        tablero[i][j] = NACIENDO;
                    cont = 0;
                }
        }
}

void actualizarEstadoCelulas(int** tablero, unsigned filas, unsigned col)
{
    int i,j;

    for(i=0;i<filas;i++)
        {
            for(j=0;j<col;j++)
                {
                    switch(tablero[i][j])
                    {
                        case MURIENDO:
                            tablero[i][j] = MUERTA;
                            break;
                        case NACIENDO:
                            tablero[i][j] = VIVA;
                            break;
                        default:
                            break;
                    }
                }
        }
}

void mostrarTableroSDL(int** tablero, unsigned filas, unsigned col, SDL_Renderer** renderer){

    int i,j,ancho=10,alto=10;

    SDL_Rect celula;

     SDL_SetRenderDrawColor(*renderer, 0x00, 0xFF, 0x00, 0xFF);
            for(i=0;i<filas;i++){
                for( j=0;j<col;j++){

                if( tablero[i][j] == 1){
                    //se multiplica la posicion por el ancho para que no se solapen las celulas
                    celula.x = j*ancho; //Pos X
                    celula.y = i*ancho; //Pos Y (el render tiene (x,y) invertido)
                    celula.h = alto;
                    celula.w = ancho;
                    SDL_RenderFillRect(*renderer,&celula); //funciona como buffer
                }
            }
            SDL_RenderPresent(*renderer); //recien acá se dibuja sobre el lienzo
        }
}

int crearArchivosPatrones(){

    int i,j, **provisional;
    FILE* pfPatron;

    provisional = crearTablero(MINFIL,MINCOL);

    if(!provisional){
            puts("No se pudo inicializar el tablero");
            return -1;
    }

    ///Creamos el archivo de texto del cañon de planeadores
    ponerTableroEnCero(provisional,MINFIL,MINCOL);
    inicializarCanionDePlaneadores(provisional,MINFIL,MINCOL);
        pfPatron = fopen("canion-de-planeadores.txt", "wt");
        if(!pfPatron){
            puts("No se pudo abrir el archivo.");
            return -1;
        }
        for(i=1;i<MINFIL-1;i++){
            for(j=1;j<MINCOL-1;j++){
                fprintf(pfPatron,"%d",provisional[i][j]);
            }
            fprintf(pfPatron,"\n");
        }
        fclose(pfPatron);

    ///Ahora lo mismo para el oscilador
    ponerTableroEnCero(provisional,MINFIL,MINCOL);
    inicializarOscilador(provisional,MINFIL,MINCOL);
        pfPatron = fopen("oscilador.txt", "wt");
        if(!pfPatron){
            puts("No se pudo abrir el archivo.");
            return -1;
        }
        for(i=1;i<MINFIL-1;i++){
            for(j=1;j<MINCOL-1;j++){
                fprintf(pfPatron,"%d",provisional[i][j]);
            }
            fprintf(pfPatron,"\n");
        }
        fclose(pfPatron);

    ///Igual para el pulsador
    ponerTableroEnCero(provisional,MINFIL,MINCOL);
    inicializarPulsador(provisional,MINFIL,MINCOL);
        pfPatron = fopen("pulsador.txt", "wt");
        if(!pfPatron){
            puts("No se pudo abrir el archivo.");
            return -1;
        }
        for(i=1;i<MINFIL-1;i++){
            for(j=1;j<MINCOL-1;j++){
                fprintf(pfPatron,"%d",provisional[i][j]);
            }
            fprintf(pfPatron,"\n");
        }
        fclose(pfPatron);

    ///y para el planeador
    ponerTableroEnCero(provisional,MINFIL,MINCOL);
    inicializarPlaneador(provisional,MINFIL,MINCOL);
        pfPatron = fopen("planeador.txt", "wt");
        if(!pfPatron){
            puts("No se pudo abrir el archivo.");
            return -1;
        }
        for(i=1;i<MINFIL-1;i++){
            for(j=1;j<MINCOL-1;j++){
                fprintf(pfPatron,"%d",provisional[i][j]);
            }
            fprintf(pfPatron,"\n");
        }
        fclose(pfPatron);

    destruirTablero(provisional,MINFIL);
    return 1;
}

int levantarArchivo(int** tablero, unsigned filas, unsigned col, const char* nomArch){

    int i=1,j = 1;
    char linea[40], aux[2],*pLinea;
    FILE* fp;

    fp = fopen(nomArch, "rt");
    if(!fp){
        puts("No se pudo abrir el archivo.");
        return -1;
    }

    while(fgets(linea,MINCOL+1,fp)){

        pLinea = linea;

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

int inicializarPatronesArch(int** tablero, unsigned filas, unsigned col, const char* patron){

    char nomArch[26];

    if( strcmpi(patron,"random") == 0 )
    {
        inicializarRandom(tablero,filas,col);
        return 1;
    }

    strcpy(nomArch,patron);
    strcat(nomArch,".txt");

    if(levantarArchivo(tablero,filas,col,nomArch) == -1)
        return -1;

    return 1;
}


////////////////////////////////////////INICIALIZACION DE PATRONES///////////////////////////////////////////////////////////
void inicializarPlaneador(int** tablero, unsigned filas, unsigned col)
{
    tablero[1][1]++;
    tablero[1][3]++;
    tablero[2][2]++;
    tablero[2][3]++;
    tablero[3][2]++;
}

void inicializarOscilador(int** tablero, unsigned filas, unsigned col)
{
    int mediof = (filas-2)/2, medioc = (col-2)/2;

    tablero[mediof-1][medioc-2]++;
    tablero[mediof-1][medioc-3]++;
    tablero[mediof-1][medioc-4]++;
    tablero[mediof-2][medioc-1]++;
    tablero[mediof-3][medioc-1]++;
    tablero[mediof-4][medioc-1]++;
    tablero[mediof-2][medioc-6]++;
    tablero[mediof-3][medioc-6]++;
    tablero[mediof-4][medioc-6]++;
    tablero[mediof-6][medioc-2]++;
    tablero[mediof-6][medioc-3]++;
    tablero[mediof-6][medioc-4]++;

    tablero[mediof-1][medioc+2]++;
    tablero[mediof-1][medioc+3]++;
    tablero[mediof-1][medioc+4]++;
    tablero[mediof-2][medioc+1]++;
    tablero[mediof-3][medioc+1]++;
    tablero[mediof-4][medioc+1]++;
    tablero[mediof-2][medioc+6]++;
    tablero[mediof-3][medioc+6]++;
    tablero[mediof-4][medioc+6]++;
    tablero[mediof-6][medioc+2]++;
    tablero[mediof-6][medioc+3]++;
    tablero[mediof-6][medioc+4]++;

    tablero[mediof+1][medioc-2]++;
    tablero[mediof+1][medioc-3]++;
    tablero[mediof+1][medioc-4]++;
    tablero[mediof+2][medioc-1]++;
    tablero[mediof+3][medioc-1]++;
    tablero[mediof+4][medioc-1]++;
    tablero[mediof+2][medioc-6]++;
    tablero[mediof+3][medioc-6]++;
    tablero[mediof+4][medioc-6]++;
    tablero[mediof+6][medioc-2]++;
    tablero[mediof+6][medioc-3]++;
    tablero[mediof+6][medioc-4]++;

    tablero[mediof+1][medioc+2]++;
    tablero[mediof+1][medioc+3]++;
    tablero[mediof+1][medioc+4]++;
    tablero[mediof+2][medioc+1]++;
    tablero[mediof+3][medioc+1]++;
    tablero[mediof+4][medioc+1]++;
    tablero[mediof+2][medioc+6]++;
    tablero[mediof+3][medioc+6]++;
    tablero[mediof+4][medioc+6]++;
    tablero[mediof+6][medioc+2]++;
    tablero[mediof+6][medioc+3]++;
    tablero[mediof+6][medioc+4]++;
}

void inicializarPulsador(int** tablero, unsigned filas, unsigned col)
{
    int mediof = (filas-2)/2, medioc = (col-2)/2;
    tablero[mediof][medioc-1]++;
    tablero[mediof][medioc]++;
    tablero[mediof][medioc+1]++;
    tablero[mediof-1][medioc]++;

}

void inicializarCanionDePlaneadores(int** tablero, unsigned filas, unsigned col)
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

void inicializarRandom(int** tablero,unsigned filas, unsigned col)
{
    int i,j;

    //seed
    srand(time(NULL));

    for(i=1;i<filas-1;i++)
        {
            for(j=1;j<col-1;j++)
                {
                    tablero[i][j] = rand()%2;
                }
        }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            /** FUNCIONES EN DESUSO DE ETAPAS PREVIAS DEL PROGRAMA **/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//inicializacion del tablero
        //printf("Cantidad de filas (mayor o igual a 18): ");
        //fila = enteroMayorIgualA(MINFIL);
        //printf("Cantidad de columnas (mayor o igual a 38): ");
        //col = enteroMayorIgualA(MINCOL);
        //crearTablero(tablero,fila,col);
        //ponerTableroEnCero(tablero,fila,col);
        //menuIni(tablero,fila,col,patron); ///Menú para inicializar patrones

int enteroMayorIgualA(int liminf){

    int data;

    do{
            fflush(stdin);
            scanf("%d",&data);

    }while(data<liminf);

    return data;
}

//En desuso
int inicializarPatrones(int** tablero, unsigned filas, unsigned col, char* patron){

    if( strcmpi(patron,"canion-de-planeadores") == 0 || strcmpi(patron,"canion de planeadores") == 0 ){
        inicializarCanionDePlaneadores(tablero, filas, col);
        return 0;
    }
    if( strcmpi(patron,"planeador") == 0 ){
        inicializarPlaneador(tablero, filas, col);
        return 0;
    }
    if(strcmpi(patron,"oscilador") == 0){
        inicializarOscilador(tablero, filas, col);
        return 0;
    }
    if(strcmpi(patron,"pulsador") == 0){
        inicializarPulsador(tablero, filas, col);
        return 0;
    }
    if(strcmpi(patron,"random") == 0){
        inicializarRandom(tablero,filas,col);
        return 0;
    }

    return -1;
}

void menuIni(int** tablero, unsigned filas, unsigned col, char* patron){
    int opcion;
    printf("---- DEBUGGER'S GAME OF LIFE ----\n\nPatrones para inicializar: \n\n");
    printf("(1) Planeador\n(2) Oscilador\n(3) Pulsador\n(4) Canion de planeadores\n(5) Random\n\nSeleccione una opcion: ");
    scanf("%d",&opcion);

    switch(opcion)
    {
        case 1:
            inicializarPlaneador(tablero, filas, col);
            strcpy(patron,"Planeador");
            break;
        case 2:
            inicializarOscilador(tablero, filas, col);
            strcpy(patron,"Oscilador");
            break;
        case 3:
            inicializarPulsador(tablero, filas, col);
            strcpy(patron,"Pulsadores");
            break;
        case 4:
            inicializarCanionDePlaneadores(tablero, filas, col);
            strcpy(patron,"Canion de planeadores");
            break;
        case 5:
            inicializarRandom(tablero,filas,col);
            strcpy(patron,"Random");
            break;
        default:
            printf("\nOpcion invalida. Intente nuevamente\n");
            system("pause");
            system("cls");
            menuIni(tablero,filas,col,patron);
    }
}

//En desuso
void mostrarTablero(int** tablero, unsigned filas, unsigned col)
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
