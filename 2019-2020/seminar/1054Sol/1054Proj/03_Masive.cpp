#include <stdio.h>
#include <malloc.h>



int* allocVector(int n) {
	int *z = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
		z[i] = 0;

	return z;
}


void main() {
	int m, v[20], *pv;
	m = 13;

	for (int i = 0; i < 20; i++)
		v[i] = i * 10 + i;

	pv = allocVector(m);
	for (int i = 0; i < m; i++)
		pv[i] = v[i] + i;

	int mat[10][20], ** pMat; // mat[i][j], pMat[i][j]

	pMat = (int**)malloc(sizeof(int*) * 10); // alocare vector de pointeri la linii - structura intermediara
	for (int i = 0; i < 10; i++)
		pMat[i] = (int*)malloc(sizeof(int) * 20);

	// intializare cu valori a matricei pMat
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 20; j++)
			pMat[i][j] = i * 10 + j;

	// dezalocare matrice pMat - invers alocarii
	for (int i = 0; i < 10; i++)
		free(pMat[i]);
	free(pMat);

	free(pv);
}