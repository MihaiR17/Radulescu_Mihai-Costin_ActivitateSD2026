#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-o lista simplu inlantuita
struct Nod
{
	Masina masina;
	struct Nod* next;
};
typedef struct Nod Nod;
 
struct HashTable {
	int dim;
	Nod** tabela;
};
typedef struct HashTable HashTable;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* cap) {
	while (cap)
	{
		afisareMasina(cap->masina);
		cap = cap->next;
	}

}

void adaugaMasinaInLista(Nod* cap,Masina masinaNoua) {
	Nod* p = cap;
	while (p->next)
	{
		p = p->next;
	}
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->masina = masinaNoua;
	nou->next = NULL;
	p->next = nou;

	
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));
	for (int i = 0;i < dimensiune;i++)
	{
		ht.tabela[i] = NULL;
	}
	
	return ht;
}

int calculeazaHash(const char* nume, int dimensiune) {
	int suma = 0;
	for (int i = 0;i < strlen(nume);i++)
	{
		suma += nume[i];
	}
	return suma % dimensiune;
}

void inserareMasinaInTabela(HashTable hash, Masina masina) 
{
	int pozitie = calculeazaHash(masina.numeSofer, hash.dim);
	if (hash.tabela[pozitie] == NULL)
	{
		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->masina = masina;
		hash.tabela[pozitie]->next = NULL;
	}
	else
	{
		adaugaMasinaInLista(hash.tabela[pozitie], masina);
	}
	
}

HashTable citireMasiniDinFisier(const char* numeFisier,int dimensiune) {
	HashTable hash = initializareHashTable(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f))
	{
		Masina masina = citireMasinaDinFisier(f);
		inserareMasinaInTabela(hash, masina);
	}
	fclose(f);
	return hash;
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	// aceste masini sunt inserate intr-o tabela de dispersie initializata aici
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void afisareTabelaDeMasini(HashTable ht) {
	for (int i = 0;i < ht.dim;i++)
	{
		if (ht.tabela[i] != NULL)
		{
			printf("\nMasinile de pe pozitia %d sunt: \n", i);
			afisareListaMasini(ht.tabela[i]);
		}
		else
		{
			printf("Pe pozitia %d nu sunt masini\n");
		}
	}


	
}

void dezalocareListaMasini(Nod** cap)
{
	Nod* p = *cap;
	while (p)
	{
		Nod* temp = p;
		p = p->next;
		if (temp->masina.model != NULL)
		{
			free(temp->masina.model);
		}
		if (temp->masina.numeSofer != NULL)
		{
			free(temp->masina.numeSofer);
		}
		free(temp);
	}
	*cap = NULL;
}

void dezalocareTabelaDeMasini(HashTable *ht) {
	for (int i = 0;i < ht->dim;i++)
	{
		dezalocareListaMasini(&(ht->tabela[i]));
	}
	free(ht->tabela);
	ht->tabela = NULL;
	ht->dim = 0;

}
float calculeazaMedieLista(Nod* cap)
{
	float suma = 0;
	int nrElemente = 0;
	while (cap != NULL)
	{
		suma += cap->masina.pret;
		nrElemente++;
		cap = cap->next;
	}
	return (nrElemente > 0 ? (suma / nrElemente) : 0);
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	float* preturi = NULL;
	*nrClustere = 0;
	for (int i = 0;i < ht.dim;i++)
	{
		if (ht.tabela != NULL)
		{
			(*nrClustere)++;
		}
	}
	preturi = (float*)malloc(sizeof(float) * (*nrClustere));
	int contor = 0;
	for (int i = 0;i < ht.dim;i++)
	{
		if (ht.tabela[i] != NULL)
		{
			preturi[contor] = calculeazaMedieLista(ht.tabela[i]);
			contor++;
		}
	}


	
	return preturi;
}

Masina getMasinaDinLista(Nod* cap, const char* nume)
{
	Masina m;
	m.id = -1;
	while (cap && strcmp(cap->masina.numeSofer, nume) != 0)
	{
		cap = cap->next;
	}
	if (cap)
	{
		m = cap->masina;
		m.model = (char*)malloc(sizeof(char) * strlen(cap->masina.model) + 1);
		strcpy_s(m.model, strlen(cap->masina.model), cap->masina.model);
		m.numeSofer = (char*)malloc(sizeof(char) * strlen(cap->masina.numeSofer) + 1);
		strcpy_s(m.numeSofer, strlen(cap->masina.numeSofer), cap->masina.numeSofer);
	}
	return m;
}

Masina getMasinaDupaNumeSofer(HashTable ht, const char* numeCautat) {
	Masina m;
	int poz = calculeazaHash(numeCautat, ht.dim);
	if (poz >= 0 && poz < ht.dim)
	{
		return getMasinaDinLista(ht.tabela[poz], numeCautat);
	}
	return m;
}

int main() {
	HashTable ht = citireMasiniDinFisier("masini.txt", 7);
	afisareTabelaDeMasini(ht);
	int nrClustere = 0;
	float *preturi = calculeazaPreturiMediiPerClustere(ht, &nrClustere);
	printf("Preturile medii per clustere sunt : \n");
	for (int i = 0;i < nrClustere;i++)
	{
		printf("%.2f ", preturi[i]);
	}
	printf("\n");

	Masina m = getMasinaDupaNumeSofer(ht, "Popescu Gigel");
	printf("Masina cautata:\n");
	afisareMasina(m);
	if (m.model != NULL)
	{
		free(m.model);
	}
	if (m.numeSofer != NULL)
	{
		free(m.numeSofer);
	}
	

	dezalocareTabelaDeMasini(&ht);
	return 0;
}