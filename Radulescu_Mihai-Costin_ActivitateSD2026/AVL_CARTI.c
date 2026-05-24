#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Carte {
	int id;
	char* titlu;
	float pret;
};

typedef struct Carte Carte;

typedef struct Nod Nod;

struct Nod {
	Carte info;
	Nod* stanga;
	Nod* dreapta;
	int inaltime;
};

Carte creareCarte(int id, const char* titlu, float pret)
{
	Carte c;

	c.id = id;
	c.pret = pret;

	c.titlu = (char*)malloc(strlen(titlu) + 1);
	strcpy(c.titlu, titlu);

	return c;
}

void afisareCarte(Carte c)
{
	printf("ID: %d\n", c.id);
	printf("Titlu: %s\n", c.titlu);
	printf("Pret: %.2f\n\n", c.pret);
}

int maxim(int a, int b)
{
	return (a > b) ? a : b;
}

int inaltime(Nod* nod)
{
	if (nod == NULL)
	{
		return 0;
	}

	return nod->inaltime;
}

Nod* creareNod(Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = c;
	nou->stanga = NULL;
	nou->dreapta = NULL;
	nou->inaltime = 1;

	return nou;
}

Nod* rotireDreapta(Nod* y)
{
	Nod* x = y->stanga;
	Nod* T2 = x->dreapta;

	x->dreapta = y;
	y->stanga = T2;

	y->inaltime = 1 + maxim(inaltime(y->stanga),
		inaltime(y->dreapta));

	x->inaltime = 1 + maxim(inaltime(x->stanga),
		inaltime(x->dreapta));

	return x;
}

Nod* rotireStanga(Nod* x)
{
	Nod* y = x->dreapta;
	Nod* T2 = y->stanga;

	y->stanga = x;
	x->dreapta = T2;

	x->inaltime = 1 + maxim(inaltime(x->stanga),
		inaltime(x->dreapta));

	y->inaltime = 1 + maxim(inaltime(y->stanga),
		inaltime(y->dreapta));

	return y;
}

int gradEchilibru(Nod* nod)
{
	if (nod == NULL)
	{
		return 0;
	}

	return inaltime(nod->stanga) -
		inaltime(nod->dreapta);
}

Nod* inserareAVL(Nod* nod, Carte c)
{
	if (nod == NULL)
	{
		return creareNod(c);
	}

	if (c.id < nod->info.id)
	{
		nod->stanga = inserareAVL(nod->stanga, c);
	}
	else if (c.id > nod->info.id)
	{
		nod->dreapta = inserareAVL(nod->dreapta, c);
	}
	else
	{
		return nod;
	}

	nod->inaltime = 1 + maxim(
		inaltime(nod->stanga),
		inaltime(nod->dreapta));

	int echilibru = gradEchilibru(nod);

	if (echilibru > 1 &&
		c.id < nod->stanga->info.id)
	{
		return rotireDreapta(nod);
	}

	if (echilibru < -1 &&
		c.id > nod->dreapta->info.id)
	{
		return rotireStanga(nod);
	}

	if (echilibru > 1 &&
		c.id > nod->stanga->info.id)
	{
		nod->stanga = rotireStanga(nod->stanga);
		return rotireDreapta(nod);
	}

	if (echilibru < -1 &&
		c.id < nod->dreapta->info.id)
	{
		nod->dreapta = rotireDreapta(nod->dreapta);
		return rotireStanga(nod);
	}

	return nod;
}

void afisareInOrdine(Nod* radacina)
{
	if (radacina)
	{
		afisareInOrdine(radacina->stanga);
		afisareCarte(radacina->info);
		afisareInOrdine(radacina->dreapta);
	}
}

void afisarePreOrdine(Nod* radacina)
{
	if (radacina)
	{
		afisareCarte(radacina->info);
		afisarePreOrdine(radacina->stanga);
		afisarePreOrdine(radacina->dreapta);
	}
}

void afisarePostOrdine(Nod* radacina)
{
	if (radacina)
	{
		afisarePostOrdine(radacina->stanga);
		afisarePostOrdine(radacina->dreapta);
		afisareCarte(radacina->info);
	}
}

void dezalocareAVL(Nod** radacina)
{
	if (*radacina)
	{
		dezalocareAVL(&(*radacina)->stanga);
		dezalocareAVL(&(*radacina)->dreapta);

		free((*radacina)->info.titlu);
		free(*radacina);

		*radacina = NULL;
	}
}

int main()
{
	Nod* radacina = NULL;

	radacina = inserareAVL(radacina,
		creareCarte(30, "C Programming", 120));

	radacina = inserareAVL(radacina,
		creareCarte(20, "Algoritmi", 95));

	radacina = inserareAVL(radacina,
		creareCarte(40, "Structuri de Date", 150));

	radacina = inserareAVL(radacina,
		creareCarte(10, "POO", 87));

	radacina = inserareAVL(radacina,
		creareCarte(25, "Java", 110));

	radacina = inserareAVL(radacina,
		creareCarte(50, "Python", 99));

	printf("===== INORDINE =====\n\n");
	afisareInOrdine(radacina);

	printf("===== PREORDINE =====\n\n");
	afisarePreOrdine(radacina);

	printf("===== POSTORDINE =====\n\n");
	afisarePostOrdine(radacina);

	dezalocareAVL(&radacina);

	return 0;
}