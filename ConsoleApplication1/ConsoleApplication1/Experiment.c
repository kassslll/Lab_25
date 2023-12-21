#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
#include "SortString.h"

char filename[] = "D:\\Учёба\\1 курс\\Основы алгоримизации и программирование (Власенко)\\лабораторная_28\\lab_28\\Лаб работа 28\\dict4b.txt";

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	long t0 = clock();
	printf("t0 = %.3f sec \n", t0 / (float)CLOCKS_PER_SEC);

	LoadWords(filename);

	printf("Experiment with array lenth = %d, file = %s\n", n, filename);

	int t1 = clock();
	printf("t1 = %.3f sec \n", t1 / (float)CLOCKS_PER_SEC);
	for (int i = 0; i < 1; i++) {
		fillArrayStrings();

		//SelectionSortStrings();
		//BubbleSortStrings();
		//InsertSortStrings();
		//QuickSortStrings();
		MergeSortStrings(0, n-1);

		if (!isSortedStrings()) {
			printf("Array is not sorted!!!\n");
		}
	}


	long t2 = clock();
	printf("t2 = %.3f sec \n", t2 / (float)CLOCKS_PER_SEC);

	printf("t1 - t0 = %.3f sec (Run time of array loading)\n",
		(t1 - t0) / (float)CLOCKS_PER_SEC);
	printf("t2 - t1 = %.10f sec (Run time of sorting)\n",
		(t2 - t1) / (float)CLOCKS_PER_SEC);
}