#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

//transmitere prin valoare
void interschimbare(int var1, int var2) {
	int aux;
	aux = var1;
	var1 = var2;
	var2 = aux;
}

//transmitere prin adresa
void interschimbarePrinAdresa(int *var1, int *var2) {
	int aux;
	//dereferentiere
	aux = *var1;
	*var1 = *var2;
	*var2 = aux;
}

void citireDeLaTastatura(int** vector, int* dimensiune) {
	printf("Dimensiune: ");
	scanf("%d", dimensiune);

	(*vector) = (int*)malloc((*dimensiune) * sizeof(int));
	for (int i = 0; i < (*dimensiune); i++) {
		printf("vector[%i]=", i);
		scanf("%d", &(*vector)[i]);
		//scanf("%d", (*vector)+i);
	}
}

void afisareVector(int* vector, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		printf("\n vector[%i] = %d", i, vector[i]);
	}
}

int main() {
	int numar;
	char caracter;
	float medie;
	numar = 12;
	caracter = 'a';
	medie = 10.2f;
	printf("%d \n", numar);
	printf("%c \n", caracter);
	printf("%d \n", caracter);
	printf("%.2f \n", medie);
	//cout <<endl<< numar;

	char sir[10];
	for (int i = 0; i < 9; i++) {
		sir[i] = 97 + i;
	}

	sir[9] = '\0';
	printf("%s \n", sir);

	char* sirAlocatDinamic;
	sirAlocatDinamic = (char*)malloc(sizeof(char)*10);
	for (int i = 0; i < 9; i++) {
		sirAlocatDinamic[i] = 100 + i;
	}
	sirAlocatDinamic[9] = '\0';
	printf("%s \n", sirAlocatDinamic);

	int nr1 = 7, nr2 = 10;
	interschimbarePrinAdresa(&nr1, &nr2);
	printf("%d \n", nr1);
	printf("%d \n", nr2);

	int* vector;
	int dimensiune;
	citireDeLaTastatura(&vector, &dimensiune);
	afisareVector(vector, dimensiune);
}