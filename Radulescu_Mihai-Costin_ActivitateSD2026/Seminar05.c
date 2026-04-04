//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//// nod lista dubla
//typedef struct Nod {
//	Masina info;
//	struct Nod* next;
//	struct Nod* prev;
//} Nod;
//
//// lista dubla
//typedef struct ListaDubla {
//	Nod* head;
//	Nod* tail;
//} ListaDubla;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//
//	aux = strtok(NULL, sep);
//	m1.model = (char*)malloc(strlen(aux) + 1);
//	strcpy(m1.model, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = (char*)malloc(strlen(aux) + 1);
//	strcpy(m1.numeSofer, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//// afisare inversa
//void afisareInversaListaMasini(ListaDubla lista) {
//	Nod* p = lista.tail;
//	while (p) {
//		afisareMasina(p->info);
//		p = p->prev;
//	}
//}
//
//// adaugare la final
//void adaugaMasinaInLista(ListaDubla* lista, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = NULL;
//	nou->prev = lista->tail;
//
//	if (lista->tail) {
//		lista->tail->next = nou;
//	}
//	else {
//		lista->head = nou;
//	}
//
//	lista->tail = nou;
//}
//
//// adaugare la inceput
//void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->prev = NULL;
//	nou->next = lista->head;
//
//	if (lista->head) {
//		lista->head->prev = nou;
//	}
//	else {
//		lista->tail = nou;
//	}
//
//	lista->head = nou;
//}
//
//// citire lista din fisier
//ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	ListaDubla lista;
//	lista.head = NULL;
//	lista.tail = NULL;
//
//	while (!feof(f)) {
//		Masina m = citireMasinaDinFisier(f);
//		adaugaMasinaInLista(&lista, m);
//	}
//
//	fclose(f);
//	return lista;
//}
//
//// dezalocare
//void dezalocareLDMasini(ListaDubla* lista) {
//	Nod* p = lista->head;
//	while (p) {
//		Nod* temp = p;
//		p = p->next;
//
//		free(temp->info.model);
//		free(temp->info.numeSofer);
//		free(temp);
//	}
//
//	lista->head = NULL;
//	lista->tail = NULL;
//}
//
//// pret mediu
//float calculeazaPretMediu(ListaDubla lista) {
//	float suma = 0;
//	int count = 0;
//
//	Nod* p = lista.head;
//	while (p) {
//		suma += p->info.pret;
//		count++;
//		p = p->next;
//	}
//
//	if (count == 0) return 0;
//	return suma / count;
//}
//
//// stergere dupa id
//void stergeMasinaDupaID(ListaDubla* lista, int id) {
//	Nod* p = lista->head;
//
//	while (p) {
//		if (p->info.id == id) {
//
//			if (p->prev)
//				p->prev->next = p->next;
//			else
//				lista->head = p->next;
//
//			if (p->next)
//				p->next->prev = p->prev;
//			else
//				lista->tail = p->prev;
//
//			free(p->info.model);
//			free(p->info.numeSofer);
//			free(p);
//			return;
//		}
//		p = p->next;
//	}
//}
//
//// nume sofer masina cea mai scumpa
//char* getNumeSoferMasinaScumpa(ListaDubla lista) {
//	if (!lista.head) return NULL;
//
//	Nod* p = lista.head;
//	Nod* max = p;
//
//	while (p) {
//		if (p->info.pret > max->info.pret) {
//			max = p;
//		}
//		p = p->next;
//	}
//
//	return max->info.numeSofer;
//}
//
//int main() {
//	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
//
//	printf("Lista inversa:\n");
//	afisareInversaListaMasini(lista);
//
//	printf("Pret mediu: %.2f\n", calculeazaPretMediu(lista));
//
//	char* nume = getNumeSoferMasinaScumpa(lista);
//	if (nume) {
//		printf("Sofer masina cea mai scumpa: %s\n", nume);
//	}
//
//	stergeMasinaDupaID(&lista, 1);
//
//	printf("\nDupa stergere:\n");
//	afisareInversaListaMasini(lista);
//
//	dezalocareLDMasini(&lista);
//
//	return 0;
//}