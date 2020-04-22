#ifdef linux
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#endif

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#endif

/*
Laufzeit Diagramm des Selection Sorts
https://prnt.sc/s41tvv
*/

int anzahlVergleiche = 0;

void swap(double* xp, double* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(double arr[], int n)
{
	int i, j, min_index;

	for (i = 0; i < n - 1; i++)
	{
		min_index = i;
		for (j = i + 1; j < n; j++) {
			if (arr[j] < arr[min_index]) {
				min_index = j;
			}
		}
		anzahlVergleiche++;
		swap(&arr[min_index], &arr[i]);
	}
}

void fillArrRandom(double arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = pow(2, (rand() % (17 + 1 - 10) + 10));
	}
}

void printArray(double arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%f ", arr[i]);
	}
	printf("\n");
}

int main()
{
	// random Array size
	double* randArr;

	for (int i = 10; i <= 17; i++)
	{
		int size = pow(2, i);
		randArr = (double*)malloc(size * sizeof(double));

		printf("sorting array[%d] with random numbers between 2^10-2^17..\n", size);

		fillArrRandom(randArr, size);
		//printf("Array: \n");
		//printArray(randArr, size);

#ifdef linux
		//Laufzeit relevante var
		double start;
		struct timeval tm;
		double duration;
		/////////////////////////////
		//Start der Laufzeit
		gettimeofday(&tm, NULL);
		start = (double)(tm.tv_sec) + ((double)(tm.tv_usec)) / 1.0e6;
		//////////////////////////////

		// function call
		selectionSort(randArr, size);

		printArray(randArr, size);
		printf("Laufzeit: %f\n", duration);

		//Ende der Laufzeit
		gettimeofday(&tm, NULL),
			duration = (double)(tm.tv_sec) + ((double)(tm.tv_usec)) / 1.0e6 - start;
		/////////////////////////////
#endif

#ifdef _WIN32
		clock_t t1 = clock();

		// function call
		selectionSort(randArr, size);

		clock_t t2 = clock();
		double t3 = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;

		//printf("Sorted Array: \n");
		//printArray(randArr, size);
		printf("Laufzeit: %f\n", t3);
#endif

		printf("Anzahl der Vergleiche: %d\n\n", anzahlVergleiche);
	}

	getchar();
	return 0;
}