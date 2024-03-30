#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Biblioteca Biblioteca;
typedef struct HashTable HashTable;

struct Biblioteca
{
	long id;
	char* nume;
	int nrCarti;
};

struct HashTable {
	int dim;
	Biblioteca** vector;
};

Biblioteca* initializeazaBib(long id, char* nume, int nrCarti)
{
	Biblioteca* b = (Biblioteca*)malloc(sizeof(Biblioteca) * 1);
	b->id = id;
	b->nrCarti = nrCarti;
	b->nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b->nume, nume);
	return b;
}

void afisareBib(Biblioteca b)
{
	printf("Biblioteca %s are id-ul %ld si %i carti\n", b.nume, b.id, b.nrCarti);
}

HashTable initializareHashTable(int dim) {
	HashTable h;
	h.dim = dim;
	h.vector = (Biblioteca**)malloc(sizeof(Biblioteca*) * dim);
	for (int i = 0; i < dim; i++) {
		h.vector[i] = NULL;
	}
	return h;
}
int Hash(int dim, long id) {
	return id % dim;
	//return strlen(denumire) % dim;
}

void inserareLinearProbing(Biblioteca* b, HashTable tabelaH) {
	int pozitie;
	if (tabelaH.vector != NULL) {
		pozitie = Hash(tabelaH.dim, b->id);
		if (tabelaH.vector[pozitie] == NULL) {
			tabelaH.vector[pozitie] = b;
		}
		else {
			int index = 1;
			while (pozitie + index < tabelaH.dim) {
				if (tabelaH.vector[pozitie + index] == NULL) {
					tabelaH.vector[pozitie + index] = b;
					pozitie = pozitie + index;
					break;
				}
				index++;
			}
		}
	}
}

void afisareHashtable(HashTable h) {
	for (int i = 0; i < h.dim; i++) {
		if (h.vector[i] != NULL) {
			printf("pozitia din tabela %d\n", i);
			//afisareBib(((*h).vector)[i]);
			printf("%ld\n", h.vector[i]->id);
		}
		else {
			printf("pozitia %d este goala\n", i);
		}
	}
}

void main() {
	HashTable h = initializareHashTable(100);
	inserareLinearProbing(initializeazaBib(123, "Bib1", 130), h);
	inserareLinearProbing(initializeazaBib(128, "Bib2", 130), h);
	inserareLinearProbing(initializeazaBib(125, "Bib3", 130), h);
	inserareLinearProbing(initializeazaBib(228, "Bib4", 130), h);
	afisareHashtable(h);

}