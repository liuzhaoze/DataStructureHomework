#ifndef __SORT_H__
#define __SORT_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(a, b)   \
        do           \
        {            \
            int temp;\
            temp = a; a = b; b = temp;\
        } while (0)

void Test(char *prompt, int R[], int answer[], int n, void (*Sort)(int R[], int n));
void SelectSort(int R[], int n);
void HeapSort(int R[], int n);
void BubbleSort(int R[], int n);
void QuickSort(int R[], int n);
void DirectInsertionSort(int R[], int n);
void ShellSort(int R[], int n);
void MergeSort(int R[], int n);

#endif /* __SORT_H__ */