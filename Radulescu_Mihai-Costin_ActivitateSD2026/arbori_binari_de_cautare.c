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

//creare structura pentru un nod dintr-un arbore binar de cautare
struct NodArbore
{
	Masina info;
	struct NodArbore* stanga;
	struct NodArbore* dreapta;

};
typedef struct NodArbore NodArbore;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
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

NodArbore* creareNod(Masina masinaNoua)
{
	NodArbore* nod = malloc(sizeof(NodArbore));
	nod->info = masinaNoua;
	nod->stanga = NULL;
	nod->dreapta = NULL;

	return nod;
}

void adaugaMasinaInArbore(NodArbore** radacina, Masina masinaNoua) {
	if (*radacina == NULL)
	{
		*radacina = creareNod(masinaNoua);
	}
	else
	{
		if (masinaNoua.id < (*radacina)->info.id)
		{
			adaugaMasinaInArbore(&((*radacina)->stanga), masinaNoua);

		}
		else
		{
			adaugaMasinaInArbore(&((*radacina)->dreapta), masinaNoua);
		}
	}
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiippile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID
}

int numaraLinii(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	if (file == NULL)
	{
		return 0;
	}

	int nrLinii = 0;
	char buffer[100];

	while (fgets(buffer, 100, file) != NULL)
	{
		if (strlen(buffer) > 1)
		{
			nrLinii++;
		}
	}
	fclose(file);
	return nrLinii;




}
NodArbore* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	NodArbore* radacina = NULL;

	int nrMasini = numaraLinii(numeFisier);
	FILE* file = fopen(numeFisier, "r");

	if (file == NULL)
	{
		printf("Eroare\n");
		return 0;
	}
	for (int i = 0;i < nrMasini;i++)
	{
		Masina masina = citireMasinaDinFisier(file);
		adaugaMasinaInArbore(&radacina, masina);
	}
	fclose(file);

	return radacina;
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void afisareInordine(NodArbore* radacina)
{
	if (radacina != NULL)
	{
		afisareInordine(radacina->stanga);
		afisareMasina(radacina->info);
		afisareInordine(radacina->dreapta);
	}
}

void afisarePreOrdine(NodArbore* radacina)
{
	if (radacina != NULL)
	{
		afisareMasina(radacina->info);
		afisarePreOrdine(radacina->stanga);
		afisarePreOrdine(radacina->dreapta);
	}
}

void afisarePostordine(NodArbore* radacina) {
	if (radacina != NULL) {
		afisarePostordine(radacina->stanga);
		afisarePostordine(radacina->dreapta);
		afisareMasina(radacina->info);
	}
}

void afisareMasiniDinArbore(NodArbore* radacina) 
{
	printf("\n--- Afisare INORDINE ---\n\n");
	afisareInordine(radacina);
	printf("\n--- Afisare PREORDINE ---\n\n");
	afisarePreOrdine(radacina);
	printf("\n--- Afisare POSTORDINE ---\n\n");
	afisarePostordine(radacina);




	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
}

void dezalocareArboreDeMasini(NodArbore** radacina) {
	if (*radacina != NULL)
	{
		dezalocareArboreDeMasini(&((*radacina)->stanga));
		dezalocareArboreDeMasini(&((*radacina)->dreapta));
	}
	free((*radacina)->info.model);
	free((*radacina)->info.numeSofer);

	free(*radacina);
	*radacina = NULL;
	//sunt dezalocate toate masinile si arborele de elemente
}
Masina masinaGoala()
{
	Masina m;
	m.id = -1;
	m.nrUsi = 0;
	m.pret = 0;
	m.model = NULL;
	m.numeSofer = NULL;
	m.serie = "-";

	return m;
}



Masina getMasinaByID(NodArbore* radacina, int id) {
	if (radacina == NULL) {
		return masinaGoala();
	}

	if (id == radacina->info.id) {
		return radacina->info;
	}
	else if (id < radacina->info.id) {
		return getMasinaByID(radacina->stanga, id);
	}
	else {
		return getMasinaByID(radacina->dreapta, id);
	}
}

int determinaNumarNoduri(NodArbore* radacina) {
	if (radacina == NULL) {
		return 0;
	}

	return 1
		+ determinaNumarNoduri(radacina->stanga)
		+ determinaNumarNoduri(radacina->dreapta);
}

int maxim(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int calculeazaInaltimeArbore(NodArbore* radacina) {
	if (radacina == NULL) {
		return 0;
	}

	int inaltimeStanga = calculeazaInaltimeArbore(radacina->stanga);
	int inaltimeDreapta = calculeazaInaltimeArbore(radacina->dreapta);

	return 1 + maxim(inaltimeStanga, inaltimeDreapta);
}

float calculeazaPretTotal(NodArbore* radacina) {
	if (radacina == NULL) {
		return 0;
	}

	return radacina->info.pret
		+ calculeazaPretTotal(radacina->stanga)
		+ calculeazaPretTotal(radacina->dreapta);
}

float calculeazaPretulMasinilorUnuiSofer(NodArbore* radacina, const char* numeSofer) {
	if (radacina == NULL) {
		return 0;
	}

	float suma = 0;

	if (strcmp(radacina->info.numeSofer, numeSofer) == 0) {
		suma += radacina->info.pret;
	}

	suma += calculeazaPretulMasinilorUnuiSofer(radacina->stanga, numeSofer);
	suma += calculeazaPretulMasinilorUnuiSofer(radacina->dreapta, numeSofer);

	return suma;
}



int main() {
	NodArbore* arbore = citireArboreDeMasiniDinFisier("masini.txt");

	afisareMasiniDinArbore(arbore);

	printf("\nNumar noduri: %d\n", determinaNumarNoduri(arbore));

	printf("Inaltime arbore: %d\n", calculeazaInaltimeArbore(arbore));

	printf("Pret total masini: %.2f\n", calculeazaPretTotal(arbore));

	printf("Pret masini pentru Ion Popescu: %.2f\n",
		calculeazaPretulMasinilorUnuiSofer(arbore, "Ion Popescu"));

	printf("\nMasina cautata dupa ID:\n\n");

	Masina masinaCautata = getMasinaByID(arbore, 3);

	if (masinaCautata.id != -1) {
		afisareMasina(masinaCautata);
	}
	else {
		printf("Nu exista masina cu acest ID.\n");
	}

	dezalocareArboreDeMasini(&arbore);

	return 0;
}