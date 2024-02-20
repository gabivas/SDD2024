#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

//transmitere prin valoare
void interschimbare(int nr1, int nr2) {
	int aux;
	aux = nr1;
	nr1 = nr2;
	nr2 = aux;
}

//transmitere prin adresa
void interschimbarePrinPointer(int* nr1, int* nr2) {
	//dereferentiere
	int aux;
	aux = *nr1;
	*nr1 = *nr2;
	*nr2 = aux;
}

void citireDeLaTastatura(int** vector, int* dimensiune) {
	printf("\n Dimensiune: ");
	scanf("%d", dimensiune);

	*vector = (int*)malloc((*dimensiune) * sizeof(int));

	for (int i = 0; i < (*dimensiune); i++) {
		printf("vector[%i]=", i);
		scanf("%d", &(*vector)[i]);
		//scanf("%d", *vector + i);
	}
}

void afisare(int* vector, int dimensiune) {
	for (int i = 0; i < dimensiune; i++) {
		printf("\n vector[%d]=%d", i, vector[i]);
	}
}

int main() {
	int numarIntreg;
	char caracter;
	float numarReal;
	numarIntreg = 7;
	caracter = 'A';
	numarReal = 70.5f;

	printf("%d \n", numarIntreg);
	printf("%c \n", caracter);
	printf("%d \n", caracter);
	printf("%.2f \n", numarReal);

	char sirCaractere[8];
	for (int i = 0; i < 8; i++) {
		sirCaractere[i] = 97 + i;
	}
	sirCaractere[7] = '\0';
	printf("%s \n", sirCaractere);

	char* sirAlocatDinamic;
	sirAlocatDinamic = (char*)malloc(6 * sizeof(char));
	for (int i = 0; i < 6; i++) {
		sirAlocatDinamic[i] = 65 + i;
	}
	sirAlocatDinamic[5] = '\0';
	printf("%s \n", sirAlocatDinamic);

	int var1 = 1, var2 = 10;
	interschimbare(var1, var2);
	printf("\n var1 = %d, var2 = %d", var1, var2);

	interschimbarePrinPointer(&var1, &var2);
	printf("\n var1 = %d, var2 = %d", var1, var2);

	int* vector;
	int dimensiune;
	citireDeLaTastatura(&vector, &dimensiune);
	afisare(vector, dimensiune);
}