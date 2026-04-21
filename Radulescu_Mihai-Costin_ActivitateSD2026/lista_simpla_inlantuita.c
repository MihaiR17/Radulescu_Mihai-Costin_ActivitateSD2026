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

typedef struct Nod Nod;

masina citiremasinadinfisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrusi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numesofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numesofer, strlen(aux) + 1, aux);

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

void adaugamasinainlista(Nod* *cap,masina masinanoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinanoua; //shallow copy
	nou->next = NULL;
	if (*cap)
	{
		Nod* p = *cap;
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
	}
	else
	{
		*cap = nou;
	}


}

void adaugalainceputinlista(Nod* *cap, masina masinanoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinanoua;
	nou->next = *cap;
	*cap = nou;

}

void* citirelistamasinidinfisier(const char* numefisier) {
	Nod* cap = NULL;
	FILE* f = fopen(numefisier, "r");
	if (f)
	{
		while (!feof(f))
		{
			adaugamasinainlista(&cap, citiremasinadinfisier(f));
			
		}
		fclose(f);
	}
	return cap;


	
}

void dezalocarelistamasini(Nod* *cap) {
	while (*cap)
	{
		Nod* p = *cap;
		(*cap) = p->next;
		if (p->info.model)
		{
			free(p->info.model);
		}
		if (p->info.numesofer)
		{
			free(p->info.numesofer);
		}
		free(p);
	}
	
}

float calculeazapretmediu(Nod* cap) {
	float suma = 0;
	int contor = 0;
	while (cap)
	{
		suma += cap->info.pret;
		contor++;
		cap = cap->next;
	}
	if (contor > 0)
	{
		return suma / contor;
	}
	return 0;
	
}

void stergemasinidinseria(Nod** cap, char seriecautata) {
	
		while ((*cap) && (*cap)->info.serie == seriecautata)
		{
			Nod* aux = *cap;
			(*cap) = aux->next;
			if (aux->info.numesofer)
			{
				free(aux->info.numesofer);
			}
			if (aux->info.model)
			{
				free(aux->info.model);
			}
			free(aux);
		}
		if ((*cap))
		{

			Nod* p = *cap;
			while (p)
			{

				while (p->next && p->next->info.serie != seriecautata)
				{
					p = p->next;
				}
				if (p->next)
				{
					Nod* aux = p->next;
					p->next = aux->next;
					if (aux->info.numesofer)
					{
						free(aux->info.numesofer);
					}
					if (aux->info.model)
					{
						free(aux->info.model);
					}
					free(aux);
				}
				else
				{
					p = NULL;
				}
			}
		}
	
}

float calculeazapretulmasinilorunuisofer(Nod* cap, const char* numesofer) {
	float suma = 0;
	while (cap)
	{
		if (strcmp(cap->info.numesofer, numesofer) == 0)
		{
			suma += cap->info.pret;
		}

		cap = cap->next;


	}
	return suma;
}

int main() {
	Nod* cap = citirelistamasinidinfisier("masini.txt");
	afisarelistamasini(cap);
	printf("Pretul mediu este : %.2f\n", calculeazapretmediu(cap));
	printf("Pretul masinilor unui sofer este : %.2f\n", calculeazapretulmasinilorunuisofer(cap,"Gigel"));
	printf("Stergere serie A\n");
	stergemasinidinseria(&cap, 'A');
	afisarelistamasini(cap);
	printf("Stergere serie B\n");
	stergemasinidinseria(&cap, 'B');
	afisarelistamasini(cap);
	
	dezalocarelistamasini(&cap);
	return 0;
}