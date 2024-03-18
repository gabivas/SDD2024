#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct Angajat Angajat;
typedef struct Nod Nod;
typedef struct LDI LDI;

struct Angajat {
    char* nume;
    int varsta;
};

struct Nod {
    Angajat info;
    Nod* next;
    Nod* prev;
};

struct LDI {
    Nod* prim;
    Nod* ultim;
};

void afisareAngajat(Angajat angajat) {
    printf("\n Angajatul %s are %d ani.", angajat.nume, angajat.varsta);
}

Angajat initAngajat(const char* nume, int varsta) {
    Angajat angajat;
    angajat.varsta = varsta;
    angajat.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(angajat.nume, nume);

    return angajat;
}

void inserareLaInceput(Angajat angajat, LDI* lista) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = angajat;
    nou->next = lista->prim;
    nou->prev = NULL;

    if (lista->prim) {
        lista->prim->prev = nou;
        lista->prim = nou;
    }
    else {
        lista->prim = lista->ultim = nou;
    }
}

void inserareLaFinal(Angajat angajat, LDI* lista) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = angajat;
    nou->next = NULL;
    nou->prev = lista->ultim;

    if (lista->ultim) {
        lista->ultim->next = nou;
        lista->ultim = nou;
    }
    else {
        lista->prim = lista->ultim = nou;
    }
}

void traversareLista(LDI lista, int* nrAngajati) {
    while (lista.prim) {
        afisareAngajat(lista.prim->info);
        (*nrAngajati)++;
        lista.prim = lista.prim->next;
}
}

void traversareListaCirculara(LDI lista) {
    if (!lista.prim) return;

    Nod* it = lista.prim;
    do {
        afisareAngajat(lista.prim->info);
        lista.prim = lista.prim->next;
    } while (lista.prim != it);
}

char* getAngajatCuVarstaCeaMaiRidicata(LDI listaCirculara) {
    if (!listaCirculara.prim) return NULL;

    Nod* it = listaCirculara.prim;
    int varstaMax = INT_MIN;
    char* numeMax = NULL;
    char buffer[20];
    do {
        if (listaCirculara.prim->info.varsta > varstaMax) {
            varstaMax = listaCirculara.prim->info.varsta;
            strcpy(buffer, listaCirculara.prim->info.nume);
        }
        listaCirculara.prim = listaCirculara.prim->next;
    } while (listaCirculara.prim != it);
    numeMax = (char*)malloc(strlen(buffer) + 1);
    strcpy(numeMax, buffer);
    return numeMax;
}

void conversieListaLaVector(LDI lista, Angajat** vectorAngajati) {
    int nrAngajati = 0;
    while (lista.prim) {
        (*vectorAngajati)[nrAngajati] = initAngajat(lista.prim->info.nume, lista.prim->info.varsta);
        nrAngajati++;
        lista.prim = lista.prim->next;
    }
}

void dezalocare(LDI* lista) {
    Nod* copie = lista->prim;
    while (copie) {
        free(copie->info.nume);
        copie = copie->next;
        if (copie) {
            free(copie->prev);
        }
    }
    free(lista->ultim);
    lista->prim = lista->ultim = NULL;
}

void main() {
    LDI lista;
    lista.prim = NULL;
    lista.ultim = NULL;
    inserareLaInceput(initAngajat("Matei", 28), &lista);
    inserareLaInceput(initAngajat("Anca", 29), &lista);
    inserareLaInceput(initAngajat("Maria", 27), &lista);

    inserareLaFinal(initAngajat("Andrei", 30), &lista);

    int nrAngajati = 0;
    traversareLista(lista, &nrAngajati);

    Angajat* vectorAngajati = (Angajat*)malloc(sizeof(Angajat) * nrAngajati);
    conversieListaLaVector(lista, &vectorAngajati);
    printf("\n Afisare angajati din vectorul de angajati:");
    for (int i = 0; i < nrAngajati; i++) {
        afisareAngajat(vectorAngajati[i]);
        free(vectorAngajati[i].nume);
    }
    free(vectorAngajati);

    lista.prim->prev = lista.ultim;
    lista.ultim->next = lista.prim;

    printf("\n\n\nLista circulara:\n");
    traversareListaCirculara(lista);

    char* nume = getAngajatCuVarstaCeaMaiRidicata(lista);
    printf("\nAngajatul %s are varsta cea mai ridicata!", nume);
    if (nume) {
        free(nume);
    }
    // dezalocare(&lista);
}