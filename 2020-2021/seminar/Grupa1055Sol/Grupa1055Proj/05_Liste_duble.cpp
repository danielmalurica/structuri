#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char *nume;
	char nrGrupa[5]; 
};

struct NodD {
	Student *st; // adresa locatie de tip Student
	NodD *next, *prev;
};

struct ListaDbl {
	NodD *p, *u;
};


ListaDbl inserareListaDubla(ListaDbl lstD, Student * pStd) {
	NodD * nou;
	nou = (NodD*)malloc(sizeof(NodD));
	nou->st = pStd;
	nou->next = 0;
	nou->prev = lstD.u;

	if (!lstD.p) // nu exista nici un nod in lista dubla (empty)
		lstD.p = lstD.u = nou; // lista dubla empty
	else { // exista cel putin un nod in lista dubla
		lstD.u->next = nou;
		lstD.u = nou;
	}

	return lstD;
}

void parseListDblInvers(ListaDbl lstD) {
	NodD *tmp = lstD.u;
	while (tmp) {
		printf("%d %s %s\n", tmp->st->id, tmp->st->nume, tmp->st->nrGrupa);

		tmp = tmp->prev; // se rescrie locatia de stack seg a var locale tmp
	}
}

ListaDbl stergereStudentDbl(ListaDbl lstD) { // stergere primul nod din lista dubla (fara salvare/extragere student)
	NodD * tmp = lstD.p;

	if (tmp) { // exista cel putin un nod in lista dubla
		lstD.p = lstD.p->next;
		if (lstD.p)
			lstD.p->prev = 0;
		else {
			// exista un singur nod in lista
			lstD.u = 0;
		}

		free(tmp->st->nume); // dezalocare nume student (nivel 3 de indirectare)
		free(tmp->st);		// dezalocare locatie de tip Student (nivel 2 de indirectare)
		free(tmp);			// dealocare nod lista dubla (nivel 1 de indirectare)
	}

	return lstD;
}

// inserare nod/Student in lista dubla pe pozitie specificata
// I/ --> lista dubla in care se insereaza student, date de intrare student (adresa de heap), pozitie destinatie in lista dbl
// /O --> 
ListaDbl inserareListaDubla(ListaDbl lstD, Student * pStd, int pozitie) // 1, 2, ...., n, n+1
{
	if (pozitie > 0) // pozitie este strict pozitiva
	{
		NodD* nou = (NodD*)malloc(sizeof(NodD));
		nou->st = pStd;

		if (pozitie == 1)
		{
			// inserare la inceput in lista dubla
			nou->next = lstD.p;
			nou->prev = NULL;

			lstD.p = nou; // inserare nod pe prima pozitie
			if (lstD.u == NULL) // inserare nod in lista empty pe prima pozitie
				lstD.u = nou;

		}
		else
		{
			NodD* tmp = lstD.p;
			int i = 1;
			while (tmp && i < pozitie)
			{
				tmp = tmp->next;
				i += 1;
			}

			if (tmp != NULL)
			{
				NodD *p;
				p = tmp->prev;

				nou->next = tmp;
				nou->prev = p;
				p->next = nou;
				tmp->prev = nou;
			}
			else
			{
				// pozitie este mai mare decat nr de noduri din lista dubla
				// inserare se face pe n+1 daca i == pozitie
				if (i == pozitie)
				{
					// inserare nod pe n+1; n este nr de noduri din lista dubla
					lstD = inserareListaDubla(lstD, pStd); // inserare la sfarsit
				}
				else { // tmp == NULL; pozitie > n+1
					; // pozitie mai mare decat n+1; nu se face inserare in lista dubla
				}
			}
		}
	}

	return lstD;
}

// stergere nod de pe pozitie data (cu extragere de date Student)
// in - lista dubla, pozitie nodului
// out - lista dubla actualizata (prim, ultim nod), date Student
ListaDbl stergere_nod_lista_dubla(ListaDbl lst, int pozitie, Student &s)
{

}

int main()
{
	ListaDbl lstStuds; // variabila locala
	lstStuds.p = lstStuds.u = 0; // lista dubla empty

	Student* pStud;

	FILE * f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		pStud = (Student*)malloc(sizeof(Student));
		pStud->id = atoi(token);

		token = strtok(NULL, sep_list);
		pStud->nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(pStud->nume, token);

		token = strtok(NULL, sep_list);
		strcpy(pStud->nrGrupa, token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		// inserare nod la inceputul listei
		lstStuds = inserareListaDubla(lstStuds, pStud);
	}

	printf("Lista dubla dupa creare:\n");
	parseListDblInvers(lstStuds);

	// dezalocare lista dubla prin stergere repetata a primului nod
	while (lstStuds.p)
	{
		lstStuds = stergereStudentDbl(lstStuds);
	}

	printf("Lista dubla dupa dezalocare:\n");
	parseListDblInvers(lstStuds);

	fclose(f);

	return 0;
}