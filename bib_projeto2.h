/* Cabeçalho */

#ifndef bib_projeto2_h
#define bib_projeto2_h

typedef struct{
    float distancia;
    int indice;
}elemento;

elemento **distanciaEuclidiana(float **matriz_ref, int linhas_ref, int cols_ref, float **matriz_ava, int linhas_ava);
float calculaDistanciaEuclidiana(float *vetor1, float *vetor2);
int checarKclientes(int **Y_ref, int **Y_ava, elemento **distancias, int rows_X_ava, int rows_X_ref, int k);
void *readDataFromFile(const char *filename, int *rows, int *cols);




#endif /*bib_projeto2.h*/