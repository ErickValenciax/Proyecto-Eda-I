/**
  * @file AlgoritmosyPrint.c
  * @versión 1.0
  * @date 05/06/2022
  * @authors
  * @title Adimnistración de Vuelos
  * @brief Funciones que utilizan algunos algoritmos
  */
#include "AlgoritmosyPrint.h"

/***************************************imprimir*************************/

/*
 * @brief Imprime la lista con los datos del TAD Vuelo
 * @param this Referencia a la lista de trabajo
 */

void VDLL_print( VDLL* this )
{
    VDLL_Cursor_front( this );
    for(Node* it = this->first;it != NULL;it = it->next )
    {
        printf("========================================\n");
		printf("== Destino : %s \n",it->data.destino);
		printf("== Hora de salida : %d:%d \n",it->data.hrsSal.hrs,it->data.hrsSal.min);
		printf("== fecha programada : %d de %s del %d \n",it->data.fecha.day,it->data.fecha.month,it->data.fecha.year);
		printf("== Precio : %0.2f \n",it->data.precio);
		printf("== boletos disponibles : %d \n",it->data.cantDis);
		printf("========================================\n");
		printf("\n");
	}
	VDLL_Cursor_front( this );
    printf("\n");
}

/*
 * @brief Señala los cambios realizados
 */

void VDLL_imprimir_realizado()
{
    printf("\t\t============================================\n");
    printf("\t\t==   Los cambios han sido realizados      ==\n");
    printf("\t\t============================================\n");
}

/*
 * @brief Señala al usuario que presione otra tecla para continuar
 */

void VDLL_imprimir_espera()
{
    printf("\t\t============================================\n");
    printf("\t\t==presione cualquier tecla para continuar ==\n");
    printf("\t\t============================================\n");
    printf("\n");
    getch();
}

/*
 * @brief Se imprime el nodo a buscar
 * @param this Referencia a lista de trabajo
 */

void VDLL_imprimir_nodobuscado (VDLL* this)
{
    printf("Cancelando vuelo con la siguiente informacion recibida...\n");
    printf("========================================\n");
    printf("== Destino : %s \n",this->cursor->data.destino);
    printf("== Hora de salida : %d:%d \n",this->cursor->data.hrsSal.hrs,this->cursor->data.hrsSal.min);
    printf("== fecha programada : %d de %s del %d \n",this->cursor->data.fecha.day,this->cursor->data.fecha.month,this->cursor->data.fecha.year);
    printf("== Precio : %0.2f \n",this->cursor->data.precio);
    printf("== boletos disponibles : %d \n",this->cursor->data.cantDis);
    printf("========================================\n");
    printf("\n");
}

/***************************************mergesort************************/

/*
 * @brief Crea un arreglo con las horas en la lista y lo pasa a MergeSort
 * @param this Referencia a la lista de trabajo
 */

void VDLL_ordenar(VDLL* this )
{
    int tam = VDLL_Len( this );
    int hora[tam];
    VDLL_Cursor_front(this);
    int i=0;
    for(Node* it = this->first;it != NULL;it = it->next )
    {
        hora[i]= it->data.hrsSal.hrs;
        ++i;
    }
    int auxhrs[tam];
    VDLL_MergeSort ( hora, 0 , tam-1, auxhrs);

    VDLL* vueloordenado = VDLL_New();
    for(i=0;i<tam;++i)
    {
        for(Node* it = this->first;it != NULL;it = it->next )
        {
            if( it->data.hrsSal.hrs == auxhrs[i])
            {
                VDLL_Push_back(vueloordenado,&it->data);
            }
        }
    }

    VDLL_Cursor_front( vueloordenado );
    for(Node* it = this->first;it != NULL;it = it->next )
    {
        it->data = vueloordenado->cursor->data;
        VDLL_Cursor_next(vueloordenado);
    }
    VDLL_Delete( &vueloordenado );
}

/*
 * @brief Divide los arreglos que pasa VDLL_ordenar
 * @param listhrs[] Arreglo donde están registradas las horas
 * @param listmin[] Arreglo donde están registrados los minutos
 * @param first Primer índice de la lista
 * @param last Último índice de la lista
 * @param auxhrs[] Arreglo auxiliar de las horas registradas
 * @param auxmin[] Arreglo auxiliar de los minutos registrados
 */

void VDLL_Merge(int listhrs[], int first, int last, int auxhrs[])
{
	int mid=(first+last)/2;
	int x0=first;
	int x1=mid;
	int x2=mid+1;
	int x3=last;
	int index=first;

	while(x0<=x1 && x2<=x3)
    {
        if(listhrs[x0]<listhrs[x2])
        {
            auxhrs[index]=listhrs[x0];
            ++index;
            ++x0;
        }
        else
        {
            auxhrs[index]=listhrs[x2];
            ++index;
            ++x2;
        }
    }

	while(x0<=x1)
        {
            auxhrs[index]=listhrs[x0];
            ++index;
            ++x0;
        }

	while(x2<=x3)
        {
            auxhrs[index]=listhrs[x2];
            ++index;
            ++x2;
        }

	for(int i=first;i<=last;++i)
        {
            listhrs[i]=auxhrs[i];
        }
}

/*
 * @brief Funcion de ordenamiento y mezcla
 * @param listhrs[] Arreglo donde están registradas las horas
 * @param listmin[] Arreglo donde están registrados los minutos
 * @param first Primer índice de la lista
 * @param last Último índice de la lista
 * @param auxhrs[] Arreglo auxiliar de las horas registradas
 * @param auxmin[] Arreglo auxiliar de los minutos registrados
 */
void VDLL_MergeSort(int listhrs[],int first, int last, int auxhrs[])
{
	//fprintf(stderr,"Llegando con first=%d y last=%d.....\n",first,last);

	if(first<last)
        {
            //fprintf(stderr,"Utilizando dividir y vencer con (%d+%d)/2=%d.....\n",first,last,(first+last)/2);
            int mid=(first+last)/2;
            //fprintf(stderr,"A punto de llamar a MergeSort con first=%d y last=%d.....\n",first,mid);
            VDLL_MergeSort(listhrs,first,mid,auxhrs);
            //fprintf(stderr,"A punto de llamar a MergeSort con first=%d+1 y last=%d.....\n",mid,last);
            VDLL_MergeSort(listhrs,mid+1,last,auxhrs);
            VDLL_Merge(listhrs,first,last,auxhrs);
		}
}

/************************************filtros***************************/

/*
 * @brief Filtra os diferentes precios de una lista
 * @param this Referencia a la lista de trabajo
 * @param key precio que se busca filtrar
 */

void VDLL_filtroprecio(VDLL* this,float key)
{
    VDLL* filtro = VDLL_New();
    for(Node* it = this->first;it != NULL;it = it->next )
        {
            if( it->data.precio == key )
            {
                VDLL_Push_back(filtro,&it->data);
            }
        }
    VDLL_print(filtro);
    VDLL_Delete( &filtro );
}

/*
 * @brief Filtra los diferentes destinos de una lista
 * @param this Referencia a la lista de trabajo
 * @param key Destino que se busca filtrar
 */

void VDLL_filtroDestino(VDLL* this,const char* key)
{
    VDLL* filtro = VDLL_New();
    for(Node* it = this->first;it != NULL;it = it->next )
        {
            if( strcmp(it->data.destino, key ) == 0 )
            {
                VDLL_Push_back(filtro,&it->data);
            }
        }
    VDLL_ordenar( filtro );
    VDLL_print(filtro);
    VDLL_Delete( &filtro );

}

/***************************boleto especifico****************************/

/*
 * @brief Búsqueda Binaria. Encuentra un vuelo especifico entre la lista ordenada
 * @param this Referencia a la lista de trabajo
 * @param key Refrencia al vuelo que se busca en la lista
 * @return El valor donde se encontro key
 */

int VDLL_bbinaria(VDLL* this, int key)
{
    int inf = 0;
    int sup = VDLL_Len( this )-1;
    while( inf <= sup )
    {
        int centro = (sup+inf) / 2;
        fprintf(stderr, "centro: %d\n", centro );
        VDLL_movercursor(this, centro );
        if ( key == this->cursor->data.hrsSal.hrs )
        {
            fprintf(stderr, "la encontre en: %d\n", centro );
            return centro;
        }
        else if (key < this->cursor->data.hrsSal.hrs)
        {
            if( sup == inf )
            {
                fprintf(stderr, "no la encontré (inf=%d):\n", inf );
                return -1;

            }

            fprintf(stderr, "voy por la izquierda (%d,%d)\n", inf, sup );
            sup = centro - 1;
        }
        else
        {
            inf = centro + 1;
            fprintf(stderr, "voy por la derecha (%d,%d)\n", inf, sup );
        }
    }
    return -1;
}

/*
 * @brief Mueve al cursor
 * @param this Referencia a la lista de trabajo
 * @param mover Mueve el cursor cierto número de veces
 */

void VDLL_movercursor(VDLL* this, int mover)
{
    VDLL_Cursor_front( this );
    for (int i=0; i < mover - 1; ++i)
    {
        VDLL_Cursor_next( this );
    }
}

/*
 * @brief Modifica la cantidad disponible de vuelos
 * @param this Referencia a la lista de trabajo
 * @param cant Número de cantidad disponible de vuelos
 */

void VDLL_modificar_Cantdisp(VDLL* this, int cant)
{
    this->cursor->data.cantDis = cant;
}

/***************************Vuelos iniciales***********************/

/*
 * @brief Inicialización de vuelos iniciales
 * @param this Referencia a la lista de trabajo
 */

void inicializar(VDLL* this)
{
    Vuelo p1;
    Hora h1;
    Hora_Ctor(&h1,15,30);
    Fecha f1;
    Fecha_Ctor(&f1,12,"abril",2022);

    Vuelo_Ctor(&p1,"NUEVA YORK", 3000.00, 50,&h1,&f1);
    VDLL_Push_back(this,&p1);

    Vuelo p2;
    Hora h2;
    Hora_Ctor(&h2,12,10);
    Fecha f2;
    Fecha_Ctor(&f2,23,"marzo",2022);

    Vuelo_Ctor(&p2,"MEXICO", 2400.00, 32,&h2,&f2);
    VDLL_Push_back(this,&p2);

    Vuelo p3;
    Hora h3;
    Hora_Ctor(&h3,10,30);
    Fecha f3;
    Fecha_Ctor(&f3,15,"junio",2022);

    Vuelo_Ctor(&p3,"NUEVA YORK", 3100, 12,&h3,&f3);
    VDLL_Push_back(this,&p3);

    Vuelo p4;
    Hora h4;
    Hora_Ctor(&h4,17,15);
    Fecha f4;
    Fecha_Ctor(&f4,23,"enero",2022);

    Vuelo_Ctor(&p4,"TIJUANA", 2300, 38,&h4,&f4);
    VDLL_Push_back(this,&p4);

    Vuelo p5;
    Hora h5;
    Hora_Ctor(&h5,6,30);
    Fecha f5;
    Fecha_Ctor(&f5,11,"abril",2022);

    Vuelo_Ctor(&p5,"GUADALAJARA", 2400, 25,&h5,&f5);
    VDLL_Push_back(this,&p5);
}

