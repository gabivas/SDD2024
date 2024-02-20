#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

void interschimbare(int* val1, int* val2) {
	//dereferentiere
	int auxiliar;
	auxiliar = *val1;
	*val1 = *val2;
	*val2 = auxiliar;
}

void citireVector(int** vector, int* dimensiune) {
	printf("\n Dimensiune:");
	scanf("%d", dimensiune);

	*vector = (int*)malloc(sizeof(int) * (*dimensiune));
	for (int i = 0; i < (*dimensiune); i++) {
		printf("\n vector[%d]=", i);
		//scanf("%d", (*vector) + i);
		scanf("%d", &(*vector)[i]);
	}
}

void afisareVector(int* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		printf("\n vector[%d]=%d", i, vector[i]);
	}
}

int main() {
	int numar;
	char caracter;
	float pret;
	numar = 5;
	caracter = 'b';
	pret = 20.7f;

	printf("%d, %c, %d, %.2f", numar, caracter, caracter, pret);

	char sirCaractere[8];
	for (int i = 0; i < 8; i++) {
		sirCaractere[i] = 98 + i;
	}
	sirCaractere[7] = '\0';
	printf("\n %s", sirCaractere);

	char* sirAlocatDinamic;
	sirAlocatDinamic = (char*)malloc(sizeof(char) * 10);
	for (int i = 0; i < 10; i++) {
		sirAlocatDinamic[i] = 65 + i;
	}
	sirAlocatDinamic[9] = '\0';
	printf("\n %s", sirAlocatDinamic);

	int nr1 = 4, nr2 = 9;
	interschimbare(&nr1, &nr2);
	printf("\n nr1=%d, nr2=%d", nr1, nr2);

	int* vector;
	int dimensiune;
	citireVector(&vector, &dimensiune);
	afisareVector(vector, dimensiune);

	//dezalocare
	free(sirAlocatDinamic);
	free(vector);
	sirAlocatDinamic = NULL;
	vector = NULL;
}