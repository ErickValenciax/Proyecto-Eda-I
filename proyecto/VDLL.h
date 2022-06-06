#ifndef  VDLL_INC
#define  VDLL_INC
#define MAX_LEN 40


#include <string.h>
// para strcmp y strncpy

#include <stdlib.h>
// para malloc and friends y size_t

#include <stdbool.h>
// para bool and friends

#include <assert.h>
// para las aserciones: assert()

#include <stdio.h>
// para fprintf()

typedef struct Hora
{
	int hrs;
	int min;
}Hora;

typedef struct Fecha
{
	int day;
	char month[MAX_LEN];
	int year;
}Fecha;

typedef struct Vuelo
{
	Hora hrsSal;
	char destino[MAX_LEN];
	float precio;
	int cantDis;
	Fecha fecha;
}Vuelo;

typedef struct Node
{
	Vuelo data;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct VDLL
{
	Node* first;
	Node* last;
	Node* cursor;
	size_t len;
} VDLL;

VDLL* VDLL_New();
void VDLL_Delete( VDLL** this );


void Vuelo_Ctor(Vuelo* p, const char* destino, float precio, int cantDis, Hora* h,Fecha* f);
void Hora_Ctor(Hora* p, int hrs, int min);
void Fecha_Ctor(Fecha* p, int day, const char* month, int year);

Vuelo VDLL_Front( VDLL* this );
Vuelo vDLL_Back( VDLL* this );

void VDLL_Push_front( VDLL* this, Vuelo* item );
void VDLL_Push_back( VDLL* this, Vuelo* data );
void VDLL_Insert( VDLL* this, Vuelo* data );

void VDLL_Pop_front( VDLL* this );
void VDLL_Pop_back( VDLL* this );

void VDLL_Erase( VDLL* this );
void VDLL_Remove( VDLL* this, int key );

void VDLL_MakeEmpty( VDLL* this );

bool VDLL_Find( VDLL* this, int key );

Vuelo VDLL_Cursor_Get( VDLL* this );
void VDLL_Cursor_front( VDLL* this );
void VDLL_Cursor_back( VDLL* this );
void VDLL_Cursor_next( VDLL* this );
void VDLL_Cursor_prev( VDLL* this );

bool VDLL_IsEmpty( VDLL* this );
size_t VDLL_Len( VDLL* this );




#endif
