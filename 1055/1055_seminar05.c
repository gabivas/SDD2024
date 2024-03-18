#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
typedef struct Film Film;
typedef struct Nod Nod;
typedef struct LDI LDI;

struct Film {
	char* nume;
	int durata;
};

struct Nod {
	Film info;
	Nod* next;
	Nod* prev;
};

struct LDI {
	Nod* prim;
	Nod* ultim;
};

void afisareFilm(Film film) {
	printf("\n Filmul %s dureaza %d minute.", film.nume, film.durata);
}

Film initializareFilm(const char* nume, int durata) {
	Film film;
	film.durata = durata;
	film.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(film.nume, nume);

	return film;
}

void inserareLaInceput(LDI* lista, Film film) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = film;
	nou->prev = NULL;
	nou->next = lista->prim;

	if (lista->prim) {
		lista->prim->prev = nou;
		lista->prim = nou;
	}
	else {
		lista->prim = nou;
		lista->ultim = nou;
	}
}

void inserareLaSfarsit(LDI* lista, Film film) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = film;
	nou->prev = lista->ultim;
	nou->next = NULL;

	if (lista->ultim) {
		lista->ultim->next = nou;
		lista->ultim = nou;
	}
	else {
		lista->prim = nou;
		lista->ultim = nou;
	}
}

void parcurgereDeLaPrim(LDI lista, int* nrFilme) {
	while (lista.prim) {
		afisareFilm(lista.prim->info);
		(*nrFilme)++;
		lista.prim = lista.prim->next;
	}
}

void parcurgereDeLaUltim(LDI lista) {
	while (lista.ultim) {
		afisareFilm(lista.ultim->info);
		lista.ultim = lista.ultim->prev;
	}
}

void dezalocare(LDI* lista) {
	Nod* aux = lista->ultim;
	while (aux != NULL) {
		free(aux->info.nume);
		aux = aux->prev;
		if (aux) {
			free(aux->next);
		}
	}

	free(lista->prim);
	lista->prim = NULL;
	lista->ultim = NULL;
}

void conversieLaVector(Film** vectorFilme, LDI lista) {
	int nrFilme = 0;
	while (lista.prim)
	{
		(*vectorFilme)[nrFilme] = initializareFilm(lista.prim->info.nume, lista.prim->info.durata);
		nrFilme++;
		lista.prim = lista.prim->next;
	}
}

void traversareListaCirculara(LDI lista) {
	Nod* copie = lista.prim;
	do {
		afisareFilm(copie->info);
		copie = copie->next;
	} while (copie != lista.prim);
}

void main() {
	LDI lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareLaInceput(&lista, initializareFilm("Harry Poter", 400));
	inserareLaInceput(&lista, initializareFilm("Superman", 120));
	inserareLaInceput(&lista, initializareFilm("Batman", 110));

	inserareLaSfarsit(&lista, initializareFilm("Robin", 100));

	int nrFilme = 0;
	parcurgereDeLaPrim(lista, &nrFilme);
	parcurgereDeLaUltim(lista);

	Film* vectorFilme = (Film*)malloc(sizeof(Film) * nrFilme);
	conversieLaVector(&vectorFilme, lista);
	printf("\n Afisare vectorFilme:");
	for (int i = 0; i < nrFilme; i++) {
		afisareFilm(vectorFilme[i]);
		free(vectorFilme[i].nume);
	}
	free(vectorFilme);

	//transformare in lista dublu inlantuita circulara
	lista.ultim->next = lista.prim;
	lista.prim->prev = lista.ultim;

	traversareListaCirculara(lista);

	//dezalocare(&lista);
}