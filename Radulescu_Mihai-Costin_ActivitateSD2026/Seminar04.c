#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct structuramasina {
	int id;
	int nrusi;
	float pret;
	char* model;
	char* numesofer;
	unsigned char serie;
};
typedef struct structuramasina masina;

struct Nod
{
	masina info;
	struct Nod* next;
};
typedef struct Nod  Nod;

//creare structura pentru un nod dintr-o lista simplu inlantuita

masina citiremasinadinfisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	if (fgets(buffer, 100, file) == NULL)
	{
		masina m = { 0,0,0,NULL,NULL,0 };
		return m;
	}
	char* aux;
	masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrusi = atoi(strtok(NULL, sep));
	m1.pret = (float)atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	m1.model = (char*)malloc(strlen(aux) + 1);
	strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	m1.numesofer = (char*)malloc(strlen(aux) + 1);
	strcpy(m1.numesofer, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisaremasina(masina masina) {
	printf("id: %d\n", masina.id);
	printf("nr. usi : %d\n", masina.nrusi);
	printf("pret: %.2f\n", masina.pret);
	printf("model: %s\n", masina.model);
	printf("nume sofer: %s\n", masina.numesofer);
	printf("serie: %c\n\n", masina.serie);
}

void afisarelistamasini(Nod* cap) {
	while (cap != NULL)
	{
		afisaremasina(cap->info);
		cap = cap->next;
	}

}

void adaugamasinainlista(Nod** cap,masina masinanoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinanoua;
	nou->next = NULL;
	if (*cap == NULL)
	{
		*cap = nou;
	}
	else
	{
		Nod* temp = *cap;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void adaugalainceputinlista(Nod** cap, masina masinanoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinanoua;
	nou->next = *cap;
	*cap = nou;
	
}

void* citirelistamasinidinfisier(const char* masini) 
{
	FILE* f = fopen(masini, "r");
	if (!f) return NULL;

	Nod* cap = NULL;
	while (!feof(f))
	{
		masina m = citiremasinadinfisier(f);
		if (m.model != NULL)
		{
			adaugamasinainlista(&cap, m);
		}
	}
	fclose(f);

	return cap;
	
}

void dezalocarelistamasini(Nod** cap) 
{
	while (*cap != NULL)
	{
		Nod* temp = *cap;
		*cap = (*cap)->next;
		free(temp->info.model);
		free(temp->info.numesofer);
		free(temp);
	}
	
}

float calculeazapretmediu(Nod* cap) 
{
	if (cap == NULL) return 0;
	float suma = 0;
	int count = 0;
	while (cap != NULL)
	{
		suma += cap->info.pret;
		count++;
		cap = cap->next;
	}

	return (count > 0) ? (suma / count) : 0;
}

void stergemasinidinseria(Nod** cap, char seriecautata) 
{
	while (*cap != NULL && (*cap)->info.serie == seriecautata)
	{
		Nod* sterge = *cap;
		*cap = (*cap)->next;
		free(sterge->info.model);
		free(sterge->info.numesofer);
		free(sterge);
	}
	if (*cap == NULL) return;

	Nod* curent = *cap;
	while (curent->next != NULL)
	{
		if (curent->next->info.serie == seriecautata)
		{
			Nod* sterge = curent->next;
			curent->next = sterge->next;
			free(sterge->info.model);
			free(sterge->info.numesofer);
			free(sterge);
		}
		else
		{
			curent = curent->next;
		}
	}

}

float calculeazapretulmasinilorunuisofer(Nod* cap, const char* numesofer) {
	float suma = 0;
	while (cap != NULL)
	{
		if (strcmp(cap->info.numesofer, numesofer) == 0)
		{
			suma += cap->info.pret;
		}
		cap = cap->next;
	}
	return suma;
}

int main() 
{
	Nod* listaMasini = (Nod*)citirelistamasinidinfisier("masini.txt");

	printf("--- Lista Initiala ---\n");
	afisarelistamasini(listaMasini);

	printf("\nPret mediu: %.2f\n", calculeazapretmediu(listaMasini));

	printf("\n--- Stergere masini seria 'A' ---\n");
	stergemasinidinseria(&listaMasini, 'A');
	afisarelistamasini(listaMasini);

	dezalocarelistamasini(&listaMasini);
	return 0;
}
