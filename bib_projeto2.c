#include "bib_projeto2.h"
#include <math.h>

elemento **distanciaEuclidiana(float **matriz_ref, int linhas_ref, int cols_ref, float **matriz_ava, int linhas_ava){

    // Aloca memória para a matriz de distâncias
    elemento **distancias = (elemento **)malloc(linhas_ava * sizeof(elemento *));
    for (int i = 0; i < linhas_ava; i++)
    {
        distancias[i] = (elemento *)malloc(linhas_ref * sizeof(elemento));
    }

    // Calcula a distância euclidiana de cada elemento da matriz de avaliação para todos os elementos da matriz de referência
    for (int i = 0; i < linhas_ava; i++)
    {
        for (int j = 0; j < linhas_ref; j++)
        {
            distancias[i][j].distancia = calculaDistanciaEuclidiana(matriz_ava[i], matriz_ref[j]);
            distancias[i][j].indice = j;
        }
    }

    return distancias;
}

float calculaDistanciaEuclidiana(float *vetor1, float *vetor2)
{
    float soma = 0.0;
    for (int i = 0; i < 6; i++)
    {
        soma += (vetor1[i] - vetor2[i]) * (vetor1[i] - vetor2[i]);
    }
    return sqrt(soma);
}

int checarKclientes(int **Y_ref, int **Y_ava, elemento **distancias, int rows_X_ava, int rows_X_ref, int k) {
    int qtd_correto = 0;

    for (int i = 0; i < rows_X_ava; i++) {
        int correto = 0;
        int incorreto = 0;

        // Percorre os k primeiros clientes mais similares
        for (int j = 0; j < k && j < rows_X_ref; j++){
            int indice_ref = distancias[i][j].indice;

            // Verifica se o valor do cliente similar de referencia é igual o valor do cliente avaliado
            if (Y_ref[indice_ref][0] == Y_ava[i][0]){
                correto++;
            } else {
                incorreto++;
            }
        }

        // Determina o resultado com base na maioria
        if (correto > incorreto){
            qtd_correto++;
        }
    }

    return qtd_correto;
}

void *readDataFromFile(const char *filename, int *rows, int *cols)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("N~ao foi poss ́ıvel abrir o arquivo %s\n", filename);
        return NULL;
    }

    void *data = NULL;

    // Le o cabe calho: n umero de linhas e colunas
    fread(rows, sizeof(int), 1, file);
    fread(cols, sizeof(int), 1, file);
    printf("Matriz %s - Linhas: %d, Colunas: %d\n", filename, *rows, *cols);

    // Verifica se  ́e uma matriz com uma coluna (nesse caso, trata como int) ou uma matriz com m ́ultiplas colunas (trata como float)
    if (*cols == 1)
    {
        // Tratar como matriz de uma coluna de inteiros
        data = (int **)malloc(*rows * sizeof(int *));
        for (int i = 0; i < *rows; i++)
        {
            ((int **)data)[i] = (int *)malloc(sizeof(int));
            fread(((int **)data)[i], sizeof(int), 1, file); // Ler cada elemento como int
        }
    }
    else
    {
        // Tratar como matriz de m ́ultiplas colunas de floats
        data = (float **)malloc(*rows * sizeof(float *));
        for (int i = 0; i < *rows; i++)
        {
            ((float **)data)[i] = (float *)malloc(*cols * sizeof(float));
            fread(((float **)data)[i], sizeof(float), *cols, file); // Ler linha por linha como float
        }
    }
    fclose(file);
    return data;
}