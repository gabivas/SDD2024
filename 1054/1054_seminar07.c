#include<stdio.h>
#include<malloc.h>

typedef struct Angajat Angajat;
typedef struct Nod Nod;
typedef struct TabelaDispersie TabelaDispersie;

struct Angajat {
    char* nume;
    int varsta;
};

struct Nod {
    Angajat info;
    Nod* next;
};
struct TabelaDispersie {
    int dimensiune;
    Nod** vector;
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

void inserareLaSfarsit(Nod** cap, Angajat angajat) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = angajat;
    nou->next = NULL;

    if ((*cap) == NULL) {
        *cap = nou;
    }
    else {
        Nod* temp = *cap;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = nou;
    }
}

TabelaDispersie initTabelaDispersie(int dim) {
    TabelaDispersie tabela;
    tabela.dimensiune = dim;
    tabela.vector = (Nod**)malloc(sizeof(Nod*) * dim);
    for (int i = 0; i < dim; i++) {
        tabela.vector[i] = NULL;
    }

    return tabela;

}

int hash(const char* numeAngajat, int dim) {
    return strlen(numeAngajat) % dim;
}

void inserareInTD(TabelaDispersie tabela, Angajat angajat) {
    if (tabela.dimensiune > 0) {
        int pozitie = hash(angajat.nume, tabela.dimensiune);
        if (pozitie >= 0 && pozitie < tabela.dimensiune) {
            inserareLaSfarsit(&(tabela.vector[pozitie]), angajat);
        }
    }
}

void parcurgereLista(Nod* cap) {
    while (cap) {
        afisareAngajat(cap->info);
        cap = cap->next;
    }
}

void traversareTD(TabelaDispersie tabela) {
    for (int i = 0; i < tabela.dimensiune; i++) {
        printf("\n Pozitia: %d", i);
        /*while (tabela.vector[i]) {
            afisareAngajat(tabela.vector[i]->info);
            tabela.vector[i] = tabela.vector[i]->next;
        }*/
        parcurgereLista(tabela.vector[i]);
    }
}

void dezalocare(TabelaDispersie tabela) {
    for (int i = 0; i < tabela.dimensiune; i++) {
        while ((*tabela.vector) != NULL) {
            Nod* cap = tabela.vector[i];
            tabela.vector[i] = tabela.vector[i]->next;
            free(cap->info.nume);
            free(cap);
        }
    }
}

void main() {
    TabelaDispersie tabela = initTabelaDispersie(10);

    inserareInTD(tabela, initAngajat("Mihai", 30));
    inserareInTD(tabela, initAngajat("Andrei", 28));
    inserareInTD(tabela, initAngajat("Ana", 29));
    inserareInTD(tabela, initAngajat("Ana", 29));
    inserareInTD(tabela, initAngajat("Ana", 29));

    inserareInTD(tabela, initAngajat("Diana", 27));

    traversareTD(tabela);
    dezalocare(tabela);
    free(tabela.vector);
}