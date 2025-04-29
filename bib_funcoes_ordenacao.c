#include "bib_funcoes_ordenacao.h"
#include <math.h>

void selectSort(elemento arr[], int n)
{  
    int i, j, min_idx;
    elemento temp;

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j].distancia < arr[min_idx].distancia)
            {
                min_idx = j;
            }
        }

        temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

void insertSort(elemento arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        elemento key = arr[i];
        int j = i - 1;

        // Move os elementos do vetor que são maiores que key uma posição a frente
        while (j >= 0 && arr[j].distancia > key.distancia)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(elemento arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    elemento *L = (elemento *)malloc(n1 * sizeof(elemento));
    elemento *R = (elemento *)malloc(n2 * sizeof(elemento));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].distancia <= R[j].distancia) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(elemento arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int intercala(elemento arr[], int low, int high) {
    elemento pivot = arr[high]; // Escolhe o último elemento como pivô
    int n = high - low + 1;
    elemento *aux = (elemento *)malloc(n * sizeof(elemento)); 

    int left = 0, right = n - 1;

    // Particiona o array mantendo estabilidade
    for (int i = low; i < high; i++) {
        if (arr[i].distancia < pivot.distancia) {
            aux[left++] = arr[i];
        } else if (arr[i].distancia > pivot.distancia) {
            aux[right--] = arr[i];
        } else { // Para valores iguais mantém ordem original
            if (arr[i].indice < pivot.indice) {
                aux[left++] = arr[i];
            } else {
                aux[right--] = arr[i];
            }
        }
    }

    // Adiciona o pivô na posição correta
    aux[left] = pivot;

    // Copia de volta para o array original
    for (int i = 0; i < n; i++) {
        arr[low + i] = aux[i];
    }

    free(aux);
    return low + left;
}

void quickSort(elemento arr[], int low, int high) {
    if (low < high) {
        int pi = intercala(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void shellSort(elemento arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            elemento temp = arr[i];
            int j = i;
            
            while (j >= gap && (arr[j - gap].distancia > temp.distancia || (arr[j - gap].distancia == temp.distancia && arr[j - gap].indice > temp.indice))) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

