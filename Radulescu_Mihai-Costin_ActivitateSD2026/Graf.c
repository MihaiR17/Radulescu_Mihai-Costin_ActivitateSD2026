#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraOras {
	int id;
	char* nume;
	int populatie;
};

typedef struct StructuraOras Oras;

typedef struct NodPrincipal NodP;
typedef struct NodSecundar NodS;

struct NodPrincipal {
	Oras info;
	NodP* next;
	NodS* vecini;
};

struct NodSecundar {
	NodP* info;
	NodS* next;
};

Oras creareOras(int id, const char* nume, int populatie)
{
	Oras o;

	o.id = id;
	o.populatie = populatie;

	o.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(o.nume, nume);

	return o;
}

void afisareOras(Oras o)
{
	printf("ID: %d\n", o.id);
	printf("Nume: %s\n", o.nume);
	printf("Populatie: %d\n\n", o.populatie);
}

void inserareListaPrincipala(NodP** graf, Oras orasNou)
{
	NodP* nou = (NodP*)malloc(sizeof(NodP));

	nou->info = orasNou;
	nou->next = NULL;
	nou->vecini = NULL;

	if (*graf)
	{
		NodP* aux = *graf;

		while (aux->next)
		{
			aux = aux->next;
		}

		aux->next = nou;
	}
	else
	{
		*graf = nou;
	}
}

void inserareListaSecundara(NodS** listaSec, NodP* vecin)
{
	NodS* nou = (NodS*)malloc(sizeof(NodS));

	nou->info = vecin;
	nou->next = NULL;

	if (*listaSec)
	{
		NodS* aux = *listaSec;

		while (aux->next)
		{
			aux = aux->next;
		}

		aux->next = nou;
	}
	else
	{
		*listaSec = nou;
	}
}

NodP* cautaOrasDupaID(NodP* graf, int id)
{
	while (graf)
	{
		if (graf->info.id == id)
		{
			return graf;
		}

		graf = graf->next;
	}

	return NULL;
}

void inserareMuchie(NodP* graf, int idStart, int idStop)
{
	NodP* start = cautaOrasDupaID(graf, idStart);
	NodP* stop = cautaOrasDupaID(graf, idStop);

	if (start && stop)
	{
		inserareListaSecundara(&(start->vecini), stop);
		inserareListaSecundara(&(stop->vecini), start);
	}
}

void afisareGraf(NodP* graf)
{
	while (graf)
	{
		printf("Orasul %s este conectat cu: ",
			graf->info.nume);

		NodS* aux = graf->vecini;

		while (aux)
		{
			printf("%s ",
				aux->info->info.nume);

			aux = aux->next;
		}

		printf("\n");

		graf = graf->next;
	}
}

void dezalocareGraf(NodP** graf)
{
	while (*graf)
	{
		NodP* temp = *graf;

		NodS* vec = temp->vecini;

		while (vec)
		{
			NodS* aux = vec;
			vec = vec->next;
			free(aux);
		}

		free(temp->info.nume);

		*graf = (*graf)->next;

		free(temp);
	}
}

int main()
{
	NodP* graf = NULL;

	inserareListaPrincipala(&graf,
		creareOras(1, "Bucuresti", 2000000));

	inserareListaPrincipala(&graf,
		creareOras(2, "Ploiesti", 180000));

	inserareListaPrincipala(&graf,
		creareOras(3, "Brasov", 250000));

	inserareListaPrincipala(&graf,
		creareOras(4, "Cluj", 320000));

	inserareListaPrincipala(&graf,
		creareOras(5, "Constanta", 300000));

	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 1, 3);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 5);

	printf("===== GRAF ORASE =====\n\n");

	afisareGraf(graf);

	dezalocareGraf(&graf);

	return 0;
}