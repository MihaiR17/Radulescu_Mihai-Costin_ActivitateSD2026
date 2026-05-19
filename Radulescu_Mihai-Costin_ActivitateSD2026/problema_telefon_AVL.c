#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Telefon
{
	int id;
	float pret;
	char* producator;
	char* model;
};
typedef struct Telefon Telefon;

typedef struct Nod Nod;
struct Nod
{
	Telefon info;
	int inaltime;
	Nod* stanga;
	Nod* dreapta;
};

Telefon citireTelefonDinFisier(FILE* numeFisier)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, numeFisier);
	char* aux = strtok(buffer, sep);
	Telefon t;
	t.id = atoi(aux);
	t.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	t.producator = (char*)malloc(strlen(aux) + 1);
	strcpy(t.producator, aux);
	aux = strtok(NULL, sep);
	t.model = (char*)malloc(strlen(aux) + 1);
	strcpy(t.model, aux);
	

	return t;
}

void afisareTelefon(Telefon t)
{
	printf("ID: %d\n", t.id);
	printf("Pret: %.2f\n", t.pret);
	printf("Model: %s\n", t.model);
	printf("Producator: %s\n", t.producator);
}

int maxim(int a, int b)
{
	if (a > b)
		return a;
	else return b;
}

int inaltime(Nod* radacina)
{
	if (radacina)
	{
		return radacina->inaltime;
	}
	return 0;

}

int calculEchilibru(Nod* radacina)
{
	if (radacina)
	{
		return inaltime(radacina->stanga) -
			inaltime(radacina->dreapta);
	}
	return 0;
}


void rotireDreapta(Nod** radacina)
{
	Nod* aux = (*radacina)->stanga;
	(*radacina)->stanga = aux->dreapta;
	aux->dreapta = *radacina;

	(*radacina)->inaltime = 1 + 
		maxim(inaltime((*radacina)->stanga)
		, inaltime((*radacina)->dreapta));

	aux->inaltime = 1 + maxim(inaltime(aux->stanga),
		inaltime(aux->dreapta));

	*radacina = aux;
}

void rotireStanga(Nod** radacina)
{
	Nod* aux = (*radacina)->dreapta;
	(*radacina)->dreapta = aux->stanga;
	aux->stanga = *radacina;

	(*radacina)->inaltime = 1 + maxim(
		inaltime((*radacina)->stanga),
		inaltime((*radacina)->dreapta));

	aux->inaltime = 1 + maxim
	(inaltime(aux->stanga), inaltime(aux->dreapta));

	*radacina = aux;
}

void inserareTelefonAVL(Nod** radacina, Telefon t)
{
	if (*radacina == NULL)
	{
		Nod* nou = malloc(sizeof(Nod));
		nou->info = t;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		nou->inaltime = 1;
		*radacina = nou;
		return;
	}

	if (t.id < (*radacina)->info.id)
		inserareTelefonAVL(&(*radacina)->stanga, t);
	else if (t.id > (*radacina)->info.id)
		inserareTelefonAVL(&(*radacina)->dreapta, t);
	else
		return;

	(*radacina)->inaltime =
		1 + maxim(inaltime((*radacina)->stanga),
			inaltime((*radacina)->dreapta));

	int grad = calculEchilibru(*radacina);

	// LL
	if (grad > 1 && t.id < (*radacina)->stanga->info.id)
		rotireDreapta(radacina);

	// RR
	else if (grad < -1 && t.id >(*radacina)->dreapta->info.id)
		rotireStanga(radacina);

	// LR
	else if (grad > 1 && t.id > (*radacina)->stanga->info.id)
	{
		rotireStanga(&(*radacina)->stanga);
		rotireDreapta(radacina);
	}

	// RL
	else if (grad < -1 && t.id < (*radacina)->dreapta->info.id)
	{
		rotireDreapta(&(*radacina)->dreapta);
		rotireStanga(radacina);
	}
}

Nod* citireArboreDinFisier(const char* numeFisier)
{
	FILE* f = fopen(numeFisier, "r");
	if (!f)
	{
		printf("Eroare!\n");
		return NULL;
	}
	Nod* radacina = NULL;
	while (!feof(f))
	{
		Telefon t = citireTelefonDinFisier(f);
		inserareTelefonAVL(&radacina, t);
	}
	fclose(f);
	return radacina;
}

void afisareInOrdine(Nod* radacina)
{
	if (radacina)
	{
		afisareInOrdine(radacina->stanga);
		afisareTelefon(radacina->info);
		afisareInOrdine(radacina->dreapta);
	}
}

int numaraProducator(Nod* radacina, const char* producator)
{
	if (!radacina) return 0;
	int count = 0;
	if (strcmp(radacina->info.producator, producator) == 0)
	{
		count=1;
	}
	
	return count + numaraProducator(radacina->stanga, producator)
		+ numaraProducator(radacina->dreapta, producator);
}

Telefon cautaTelefonByID(Nod* radacina, int id)
{
	Telefon t;
	t.id = -1;
	t.pret = 0;
	t.producator = NULL;
	t.model = NULL;
	if (radacina == NULL)
		return t;
	if (radacina->info.id == id)
	{
		t.id = radacina->info.id;
		t.pret = radacina->info.pret;
		t.producator = (char*)malloc(strlen(radacina->info.producator) + 1);
		strcpy(t.producator, radacina->info.producator);
		t.model = (char*)malloc(strlen(radacina->info.model) + 1);
		strcpy(t.model, radacina->info.model);
		return t;
	}
	if (radacina->info.id > id)
	{
		return cautaTelefonByID(radacina->stanga, id);
	}
	else return cautaTelefonByID(radacina->dreapta, id);

}

//Realiza?i o func?ie la alegere care s? foloseasc? arborele AVL ?i atributul nou ad?ugat.
//
//Exemplu: dac? atributul nou este ram, calcula?i memoria RAM total? a telefoanelor din arbore.

float pretulTelefoanelorAleUnuiProducator(Nod* radacina, const char* producator)
{
	if (radacina == NULL)
		return 0;
	float suma = 0;
	if (strcmp(radacina->info.producator, producator) == 0)
	{
		suma += radacina->info.pret;
	}
	suma += pretulTelefoanelorAleUnuiProducator(radacina->stanga, producator);
	suma += pretulTelefoanelorAleUnuiProducator(radacina->dreapta, producator);
	return suma;
}

int main() {

	Nod* radacina = citireArboreDinFisier("telefon.txt");
	afisareInOrdine(radacina);
	printf("%d\n", numaraProducator(radacina, "Apple"));

	Telefon t = cautaTelefonByID(radacina, 1);
	if (t.id != -1)
	{
		printf("Gasit: %s\n", t.producator);
	}
	else printf("Nu exista\n");
	printf("Pretul ale telefoanelor producatorului cautat este : %.2f\n", pretulTelefoanelorAleUnuiProducator(radacina, "Apple"));
	return 0;
	
}