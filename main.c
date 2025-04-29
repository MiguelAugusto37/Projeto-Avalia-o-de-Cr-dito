#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bib_projeto2.c"
#include "bib_funcoes_ordenacao.c"

int main()
{

    // Nomes dos arquivos bin arios
    char *filename_cliente_dados = "clientes_dados_referencia.dat";
    char *filename_cliente_credito = "clientes_credito_referencia.dat";
    char *filename_avaliar_dados = "clientes_dados_avaliar.dat";
    char *filename_avaliar_credito = "clientes_credito_avaliar.dat";

    // Vari ́aveis para armazenar as dimens~oes
    int rows_X_ref, cols_X_ref, rows_Y_ref, cols_Y_ref;
    int rows_X_ava, cols_X_ava, rows_Y_ava, cols_Y_ava;

    // Ler a matriz de dados do arquivo referencia(float)
    float **X_ref = (float **)readDataFromFile(filename_cliente_dados, &rows_X_ref, &cols_X_ref);

    // Ler a "matriz de uma coluna" de r otulos do arquivo referencia(int)
    int **Y_ref = (int **)readDataFromFile(filename_cliente_credito, &rows_Y_ref, &cols_Y_ref);

    // Ler a matriz de dados do arquivo avaliar(float)
    float **X_ava = (float **)readDataFromFile(filename_avaliar_dados, &rows_X_ava, &cols_X_ava);

    // Ler a "matriz de uma coluna" de rotulos do arquivo referencia(int)
    int **Y_ava = (int **)readDataFromFile(filename_avaliar_credito, &rows_Y_ava, &cols_Y_ava);

    // Calcular as distâncias de todos os elementos da matriz avaliação para a matriz referência
    elemento **clientes = (elemento **)distanciaEuclidiana(X_ref, rows_X_ref, cols_X_ref, X_ava, rows_X_ava);

    // definindo k elementos, inicializando variavel op (opção) e redução da matriz avaliação
    int k = 1, op, reducao = 0;
    rows_X_ref -= reducao;

    // scanf para op
    scanf("%d", &op);

    // startando timer
    clock_t comeco = clock();

    // Opções de algoritmos de ordenação
    switch (op){
        case 1:
            for(int i = 0; i < rows_X_ava; i++){
                selectSort(clientes[i], rows_X_ref); 
            }
            break;
        case 2:
            for(int i = 0; i < rows_X_ava; i++){
                insertSort(clientes[i], rows_X_ref);
            }
            break;
        case 3:
            for(int i = 0; i < rows_X_ava; i++){
                mergeSort(clientes[i], 0, rows_X_ref - 1);
            }
            break;
        case 4:
            for(int i = 0; i < rows_X_ava; i++){
                quickSort(clientes[i], 0, rows_X_ref - 1);
            }
            break;
        case 5:
            for(int i = 0; i < rows_X_ava; i++){
                shellSort(clientes[i], rows_X_ref - 1);
            }
            break;
        default: printf("\nOpção inválida!\n"); break;
    }
    
    // Parando timer
    clock_t fim = clock();

    // Função para checar k elementos e armazenar em qtd as avaliações acertadas
    float qtd[6];
    for (int i = 0; i < 6; i++){
        qtd[i] = checarKclientes(Y_ref, Y_ava, clientes, rows_X_ava, rows_X_ref, k);
        qtd[i] = (qtd[i] / rows_X_ava) * 100;
        printf("\nPara k = %d\t%.2f%%", k, qtd[i]);
        k = k + 2;
    }

    // tempo de exec em ms
    double tempo_de_execucao = ((double)(fim - comeco) / CLOCKS_PER_SEC) * 1000;

    printf("\nTempo de Execucao: %.2f milissegundos\n", tempo_de_execucao);

    // Liberação de memória alocada
    for (int i = 0; i < rows_X_ref; i++)
        free(X_ref[i]);
    free(X_ref);

    for (int i = 0; i < rows_Y_ref; i++)
        free(Y_ref[i]);
    free(Y_ref);

    for (int i = 0; i < rows_X_ava; i++)
        free(X_ava[i]);
    free(X_ava);

    for (int i = 0; i < rows_Y_ava; i++)
        free(Y_ava[i]);
    free(Y_ava);

    for (int i = 0; i < rows_X_ava; i++)
        free(clientes[i]);
    free(clientes);

    return 0;
}
