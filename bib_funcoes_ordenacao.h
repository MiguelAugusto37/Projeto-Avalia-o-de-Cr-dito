/* Cabeçalho */

#ifndef bib_funcoes_ordenacao_h
#define bib_funcoes_ordenacao_h
#include "bib_projeto2.h"

void selectSort(elemento arr[], int n);
void insertSort(elemento arr[], int n);
void merge(elemento arr[], int left, int mid, int right);
void mergeSort(elemento arr[], int left, int right);
int intercala(elemento arr[], int low, int high);
void quickSort(elemento arr[], int low, int high);
void shellSort(elemento arr[], int n);



#endif /*bib_funcoes_ordenacao.h*/