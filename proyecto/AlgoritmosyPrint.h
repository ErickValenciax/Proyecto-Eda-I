#ifndef  AlgoritmosyPrint_INC
#define  Algoritmosyprint_INC

#include <conio.h>
#include "VDLL.h"


/********************print**************************/

void VDLL_print( VDLL* this );
void VDLL_imprimir_realizado();
void VDLL_imprimir_espera();
void VDLL_imprimir_nodobuscado (VDLL* this);

/***************************** mergesort ***********************/

void VDLL_ordenar(VDLL* this);
void VDLL_Merge(int listhrs[], int first, int last, int auxhrs[]);
void VDLL_MergeSort(int listhrs[], int first, int last, int auxhrs[]);

/****************************filtro**************************/

void VDLL_filtroprecio(VDLL* this, float key);
void VDLL_filtroDestino(VDLL* this,const char* key);

/***************************boleto especifico****************************/

int VDLL_bbinaria(VDLL* this, int key);
void VDLL_movercursor(VDLL* this, int mover);
void VDLL_modificar_Cantdisp(VDLL* this, int cant);

/*****************************Vuelos iniciales*********************/
void inicializar(VDLL* this);


#endif
