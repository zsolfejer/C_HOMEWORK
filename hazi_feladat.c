#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef enum
{
	GYORS_50,
	PILLANGÓ_50,
	HÁT_100,
	MELL_100,
	HÁT_200,
	VEGYES_200,
	VEGYES_400
}Uszasnemek;

typedef struct
{
	int cs_id;
	char csapatnev[51];
	int pontszam;
} Csapat;

typedef struct
{
	int cs_id, v_id;
	char nev[71];
	int pontszam;
} Versenyzo;

typedef struct
{
	int cs_id, v_id;
	Uszasnemek uszasnem;
	double sec;
	int helyezes;
} Eredmeny;

typedef struct E_listaelem
{
	Eredmeny data;
	struct E_listaelem*next;
} E_listaelem;

typedef struct V_listaelem
{
	Versenyzo data;
	struct V_listaelem*next;
	E_listaelem*e_head;
} V_listaelem;

typedef struct CS_listaelem
{
	Csapat data;
	struct CS_listaelem*next;
	V_listaelem*v_head;
} CS_listaelem;

//csapatok listáját felépítő függvény
CS_listaelem * cs_lista(CS_listaelem *p, Csapat cs)
{
	CS_listaelem *team = (CS_listaelem*)malloc(sizeof(CS_listaelem));
	team->data = cs;
	p->next = team;
	team->next = NULL;
	return team;
}

//versenyzok listaelemeit létrehozó függvény
V_listaelem * v_lista(CS_listaelem* csapat, Versenyzo seged)
{
	V_listaelem *uszo = (V_listaelem*)malloc(sizeof(V_listaelem));

	if (csapat->v_head != NULL)
	{
		if (seged.cs_id == csapat->data.cs_id)
		{
			uszo->data = seged;
			csapat->v_head = uszo;
			uszo->next = NULL;
		}
	}
	else
	{
		if (seged.cs_id == csapat->data.cs_id)
		{
			uszo->data = seged;
			uszo->next = csapat->v_head;
			csapat->v_head = uszo;
		}
	}

	return uszo;
}

//versenyzők listáját létrehozó függvény
void versenyzo_beolvaso(CS_listaelem* assistant)
{
	FILE *swimmers;
	swimmers = fopen("versenyzok.txt", "r");

	if (swimmers == NULL)
	{
		printf("Nem sikerult megnyitni a fajlt.");
	}

	V_listaelem*seged = (V_listaelem*)malloc(sizeof(V_listaelem));

	while (fscanf(swimmers, "%d %d\n%s\n", &seged->data.cs_id, &seged->data.v_id, seged->data.nev) == 3)
	{
		CS_listaelem* i;
		for (i = assistant; i != NULL; i=i->next)
		{
			if (assistant->data.cs_id == seged->data.cs_id)
			{
				if (assistant->v_head != NULL)
				{
					assistant->v_head = seged;
					seged->next = NULL;
				}
				else
				{
					seged->next = assistant->v_head;
					assistant->v_head = seged;
				}
			}
		}
	}
}


int main(void)
{
	//Csapatok listájának létrehozása

	Csapat csapat0 = { 1, "IRON", 0 }, csapat1 = { 2, "LA CURRENT", 0 }, csapat2 = { 3, "LONDON ROAR", 0 }, csapat3 = { 4, "NY BREAKERS", 0 };
	CS_listaelem *t1, *t2, *t3;

	CS_listaelem *t0 = (CS_listaelem*)malloc(sizeof(CS_listaelem));
	if (t0 != NULL)
	{
		t0->data = csapat0;
		t0->next = NULL;
		t1 = cs_lista(t0, csapat1);
		t2 = cs_lista(t1, csapat2);
		t3 = cs_lista(t2, csapat3);
	}
	
	CS_listaelem* temp;
	for(temp=t0; temp!= NULL; temp=temp->next)
	{
		printf("%d, %s, %d\n", temp->data.cs_id, temp->data.csapatnev, temp->data.pontszam);
	}

	//Versenyzők listájának létrehozása
	versenyzo_beolvaso(t0);
	printf("\n%d, %d, %s, %d\n", t0->v_head->data.cs_id, t0->v_head->data.v_id, t0->v_head->data.nev, t0->v_head->data.pontszam);
	

	/*V_listaelem *swimmer = (V_listaelem*)malloc(sizeof(V_listaelem));
	Versenyzo versenyzo_seged = { 0 };
	V_listaelem *v_seged = (V_listaelem*)malloc(sizeof(V_listaelem));

	FILE *swimmers;

	swimmers = fopen("versenyzok.txt", "r");

	if (swimmers == NULL)
	{
		printf("Nem sikerult megnyitni a fajlt.");
		return 1;
	}

	while (t0 != NULL)
	{
		while (fscanf(swimmers, "%d %d %s", &versenyzo_seged.cs_id, &versenyzo_seged.v_id, &versenyzo_seged.nev) == 3)
		{
			v_seged->data = versenyzo_seged;
			v_seged->next = NULL;
		}
		t0 = t0->next;
	}

	swimmer = v_lista(t0, versenyzo_seged);

	printf("%d, %d, %s", swimmer->data.cs_id, swimmer->data.v_id, swimmer->data.nev);*/

	//Versenyzok listájának létrehozása
	//Segédstruktúra létrehozása, a beolvasáshoz
	/*Versenyzo versenyzo_seged = {0, 0, "semmi"};
	V_listaelem *v_seged = (V_listaelem*)malloc(sizeof(V_listaelem));

	FILE *swimmers;
	
	swimmers = fopen("versenyzok.txt", "r");
	
	if (swimmers == NULL)
	{
		printf("Nem sikerult megnyitni a fajlt.");
		return 1;
	}

		fscanf(swimmers, "%d %d %s", &versenyzo_seged.cs_id, &versenyzo_seged.v_id, &versenyzo_seged.nev);
		v_seged->data = versenyzo_seged;
		v_seged->next = NULL;
		printf("\n%d, %d, %s\n", v_seged->data.cs_id, v_seged->data.v_id, v_seged->data.nev);

		if (v_seged->data.cs_id == t0->data.cs_id)
		{
			t0->v_head = v_seged;
			v_seged->next = NULL;
		}
		printf("\n%d, %s, %d, %d, %s\n", t0->data.cs_id, t0->data.csapatnev, v_seged->data.cs_id, v_seged->data.v_id, v_seged->data.nev);*/
	
	return 0;
}