#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Masina {
	char* producator;
	int serie;
};

struct Nod {
	Masina inf;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dimensiune;
};

void afisareMasina(Masina masina) {
	printf("\n Masina %s are seria %d.", masina.producator, masina.serie);
}

Masina initMasina(const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.serie = serie;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

void inserareLaFinal(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->next = NULL;
	if ((*cap) != NULL) {
		Nod* aux = *cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

HashTable initHashTable(int dim) {
	HashTable hashTable;
	hashTable.dimensiune = dim;
	hashTable.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++) {
		hashTable.vector[i] = NULL;
	}
	return hashTable;
}

int hash(int serie, int dim) {
	return serie % dim;
}

void inserareInHT(HashTable ht, Masina masina) {
	if (ht.dimensiune > 0) {
		int pozitie = hash(masina.serie, ht.dimensiune);
		if (pozitie >= 0 && pozitie < ht.dimensiune) {
			inserareLaFinal(&(ht.vector[pozitie]), masina);
		}
	}
}

void traversareHT(HashTable hashT) {
	for (int i = 0; i < hashT.dimensiune; i++) {
		printf("\n Pozitie: %d", i);
		Nod* copie = hashT.vector[i];
		while (copie != NULL) {
			afisareMasina(copie->inf);
			copie = copie->next;
		}
	}
}

void main() {
	HashTable hashT = initHashTable(10);
	inserareInHT(hashT, initMasina("Renault", 1234));
	inserareInHT(hashT, initMasina("Ford", 5678));
	inserareInHT(hashT, initMasina("Ford", 5679));
	inserareInHT(hashT, initMasina("Ford", 5677));
	inserareInHT(hashT, initMasina("Ford", 5677));
	inserareInHT(hashT, initMasina("Peugeot", 9101));
	inserareInHT(hashT, initMasina("Ford", 5677));
	inserareInHT(hashT, initMasina("Bmw", 1213));

	traversareHT(hashT);
}