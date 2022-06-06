/**
  * @file VDLL.c
  * @versión 1.0
  * @date 05/06/2022
  * @authors
  * @title Adimnistración de Vuelos
  * @brief Funciones utilizadas para la lista doblemente enlazada
  */

#include "VDLL.h"

// newNode es una función privada, por eso su nombre está fuera
// del patrón y además no tiene prototipo en el archivo de encabezados.

static Node* new_node( Vuelo* info )
{
	Node* n = (Node*) malloc( sizeof( Node ) );
	if( n ){
		strncpy(n->data.destino,info->destino,MAX_LEN);
		n->data.precio = info->precio;
		n->data.cantDis = info->cantDis;
		n->data.hrsSal.hrs = info->hrsSal.hrs;
		n->data.hrsSal.min = info->hrsSal.min;
		n->data.fecha.day = info->fecha.day;
		strncpy(n->data.fecha.month,info->fecha.month,MAX_LEN);
		n->data.fecha.year = info->fecha.year;
		n->next = NULL;
		n->prev=NULL;
	}
	return n;
}

/*
 * @brief Inicializa los campos de la estructura Hora
 * @param p Referencia a la estrcutura Hora
 * @param hrs Número entero que indica las horas
 * @param min Número entero que indica los minutos
 */

void Hora_Ctor(Hora* p, int hrs, int min)
{
    p->hrs = hrs;
    p->min = min;
}

/*
 * @brief Inicializa los campos de la estructura Fecha
 * @param p Referencia a la estructura Fecha
 * @param day Número entero que indica el día
 * @param mont Cadena de caracteres que indica el mes
 * @param year Número entero que indica el año
 */

void Fecha_Ctor(Fecha* p, int day, const char* month, int year)
{
    p->day = day;
    strncpy(p->month,month,MAX_LEN);
    p->year = year;
}

/*
 * @brief Inicializa los campos de la estructura Vuelo
 * @param p Referencia a la estructura Vuelo
 * @param destino Cadena de caracteres que indica el destino a viajar
 * @param precio Número flotante (con decimales) que indica el precio
 * @param candtDis Número entero que indica la cantidad disponible de boletos
 * @param h Tipo Abstracto Hora que indica la hora dada en horas y minutos
 * @param f Tipo Abstracto Fecha que indica la fecha dada en dd/mm/aa
 */

void Vuelo_Ctor(Vuelo* p, const char* destino, float precio, int cantDis,Hora* h,Fecha* f)
{
	strncpy(p->destino,destino,MAX_LEN);
	p->precio = precio;
	p->cantDis = cantDis;
	p->hrsSal.hrs = h->hrs;
	p->hrsSal.min = h->min;
	p->fecha.day = f->day;
	strncpy(p->fecha.month,f->month,MAX_LEN);
	p->fecha.year = f->year;
}

/**
 * @brief Devuelve una copia del valor apuntado por el cursor
 * @param this Una lista
 * @return El valor apuntado por el cursor
 */

Vuelo VDLL_Cursor_Get( VDLL* this )
{
	assert(this->cursor);
	Vuelo tmp;
	tmp=this->cursor->data;
	return tmp;
}

/**
 * @brief Coloca al cursor al inicio de la lista.
 * @param this Una referencia a la lista de trabajo
 */

void VDLL_Cursor_front( VDLL* this )
{
   this->cursor = this->first;
}

/**
 * @brief Coloca al cursor al final de la lista.
 * @param this Una referencia a la lista de trabajo
 */

void VDLL_Cursor_back( VDLL* this )
{
	this->cursor=this->last;
}

/**
 * @brief Mueve al cursor al siguiente elemento a la derecha.
 * @param this Una lista.
 */

void VDLL_Cursor_next( VDLL* this )
{
	this->cursor=this->cursor->next;
}

/**
 * @brief Mueve al cursor al siguiente elemento a la izquierda.
 * @param this Una lista.
 */

void VDLL_Cursor_prev( VDLL* this )
{
   assert( this->cursor != NULL );

   Node* left = this->cursor->prev;
   this->cursor = left;
}

/**
 * @brief Indica si la lista está vacía.
 * @param this Referencia a una lista.
 * @return true si la lista está vacía; false en caso contrario.
 */

bool VDLL_IsEmpty( VDLL* this )
{
   return this->first == NULL;
}

/**
 * @brief Devuelve el número actual de elementos en la lista.
 * @param this Una lista.
 * @return Devuelve el número actual de elementos en la lista.
 */

size_t VDLL_Len( VDLL* this )
{
	return this->len;
}

/**
 * @brief Elimina el elemento al frente de la lista.
 * @param this Referencia a una lista.
 * @post El cursor se mantiene en la posición en la que estaba cuando entró la
 * función.
 */

void VDLL_Pop_front( VDLL* this )
{
	assert(this);
	assert(this->len);

	if(this->first==this->last){
		free(this->first);
		this->first=this->last=this->cursor=NULL;
	}
	else{
		Node* right=this->first->next;
		free(this->first);
		this->first=right;
		this->first->prev=NULL;
	}
	--this->len;
}

/**
 * @brief Elimina el elemento al fondo de la lista.
 * @param this Referencia a una lista.
 * @post El cursor se mantiene en la posición en la que estaba cuando entró la
 * función.
 */

void VDLL_Pop_back( VDLL* this )
{
   assert( this->len );

   if( this->last != this->first )
   {
      Node* x = this->last->prev;
      free( this->last );
      x->next = NULL;
      this->last = x;
   } else{
      free( this->last );
      this->first = this->last = this->cursor = NULL;
   }
   --this->len;
}

/**
 * @brief Elimina el elemento apuntado por el cursor.
 * @param this Una lista.
 * @post El cursor se mueve a la derecha.
 */

void VDLL_Erase( VDLL* this )
{
	if(this->cursor==this->first){
		VDLL_Pop_front(this);
		this->cursor=this->first;
	}
	else if(this->cursor==this->last){
		VDLL_Pop_back(this);
		this->cursor=this->last;
	}
	else{
		Node* left=this->cursor->prev;
		Node* right=this->cursor->next;
		free(this->cursor);
		left->next=right;
		right->prev=left;
		--this->len;
		this->cursor=right;
	}
}

/**
 * @brief Elimina todos los elementos de la lista sin eliminar la lista.
 * @param this Una lista
 */

void VDLL_MakeEmpty( VDLL* this )
{
	VDLL_Cursor_front(this);

	while(VDLL_IsEmpty(this)==false){
		VDLL_Erase(this);
	}

	assert(this->len==0);

	this->first=this->last=this->cursor=NULL;
	this->len=0;
}

/**
 * @brief Busca un valor en la lista. Si lo encuentra coloca ahí al cursor.
 * @param this Una lista.
 * @param key El valor que se está buscando.
 * @post Si se encontró una coincidencia coloca al cursor en ese nodo; en caso contrario el cursor es NULL.
 * @code
 * if( DLL_Find( list, x ) )
 * {
 *    y = DLL_Cursor_Get( list );
 *
 *    // ...
 * }
 * @endcode
 */

bool VDLL_Find( VDLL* this, int key )
{
   for( this->cursor = this->first; this->cursor != NULL; this->cursor = this->cursor->next )
   {
      if( this->cursor->data.hrsSal.hrs == key )
      {
         return true;
      }
   }
   return false;
}

/**
 * @brief Elimina el primer nodo que coincida con la llave.
 * @param this Una lista
 * @param key  Valor buscado
 */

void VDLL_Remove( VDLL* this, int key )
{
    if(VDLL_Find( this, key )== true)
    {
        VDLL_Erase( this );
    }
}

/**
 * @brief Crea una lista doblemente enlazada
 * @return Una referencia a la nueva lista
 * @post Una lista existente en el heap
 */

VDLL* VDLL_New()
{
	VDLL* list=(VDLL*)malloc(sizeof(VDLL));

	if(list!=NULL){
		list->first=list->last=list->cursor=NULL;
		list->len=0;
	}

	return list;
}

/**
 * @brief Destruye una lista.
 * @param this Una lista.
 */

void VDLL_Delete( VDLL** this )
{
	assert(*this);
	VDLL_MakeEmpty(*this);
	free(*this);
	*this=NULL;
}

/**
 * @brief Inserta un elemento en el fondo de la lista.
 * @param this Una lista.
 * @param item El elemento a insertar
 */

void VDLL_Push_back( VDLL* this, Vuelo* data )
{
   Node* n = new_node( data );
   assert( n );

   if( this->first != NULL ){

      this->last->next = n;
      n->prev = this->last;
      this->last = n;
   } else{
      this->first = this->last = this->cursor = n;
   }
   ++this->len;
}

/**
 * @brief Inserta un elemento a la derecha del cursor
 * @param lista Una referencia a la lista de trabajo
 * @param item El elemento a insertar
 * @post Coloca al cursor en el nuevo nodo
 */

void VDLL_Insert( VDLL* this, Vuelo* data )
{
	assert(this);
	assert(this->cursor);

	if(VDLL_IsEmpty(this)==true){
		Node* n=new_node(data);
		this->first=this->last=this->cursor=n;
		++this->len;
	}
	else if(this->cursor==this->last){
		VDLL_Push_back(this,data);
	}
	else{
		Node* n=new_node(data);
		Node* right=this->cursor->next;
		n->next=right;
		this->cursor->next=n;
		right->prev=n;
		n->prev=this->cursor;
		this->cursor=n;
		++this->len;

	}
}

/**
 * @brief Inserta un elemento en el frente de la lista.
 * @param this Una lista.
 * @param item El elemento a insertar
 */

void VDLL_Push_front( VDLL* this, Vuelo* item )
{
	Node* n=new_node(item);
	assert(n);

	if(this->first!=NULL){
		n->next=this->first;
		this->first->prev=n;
		this->first=n;
	}
	else{
		this->first=this->last=this->cursor=n;
	}
	++this->len;
}

/**
 * @brief Devuelve una copia del elemento en el frente de la lista
 * @param this Una lista
 * @return La copia del elemento en el frente de la lista
 * @pre La lista NO debe estar vacía
 */

Vuelo VDLL_Front( VDLL* this )
{
   assert( this->first != NULL );

   return this->first->data;
}

/**
 * @brief Devuelve una copia del elemento en la parte trasera de la lista.
 * @param this Una lista.
 * @return La copia del elemento en la parte trasera de la lista.
 * @pre La lista NO debe estar vacía
 */

Vuelo VDLL_Back( VDLL* this )
{
	assert(this->last!=NULL);

	return this->last->data;
}
