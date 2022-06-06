#include <stdio.h>
#include <stdlib.h>
#include "VDLL.h"
#include "AlgoritmosyPrint.h"


int main()
{
    VDLL* registro = VDLL_New();
    VDLL* nodobuscar = VDLL_New();
    inicializar(registro);

    Vuelo nuevo;
    Hora horaNuevo;
    Fecha fechaNuevo;
    bool repetir = true;
    while(repetir==true)
    {
        printf("\t\t==================================================\n");
        printf("\t\t== Bienvenido al registro de vuelos programados ==\n");
        printf("\t\t==================================================\n");
        printf("\n");
        printf("\t\t\t====================================\n");
        printf("\t\t\t== ¿que operación desea realizar? ==\n");
        printf("\t\t\t====================================\n");
        printf("\n");
        printf("\t=============================================================\n");
        printf("\t== 1)                programar un nuevo vuelo              ==\n");
        printf("\t== 2)               cancelar un vuelo programado           ==\n");
        printf("\t== 3) modificar la disponibilidad de boletos para un vuelo ==\n");
        printf("\t== 4)           mostrar todos los vuelos disponibles       ==\n");
        printf("\t== 5)        aplicar un filtro a la busqueda de boletos    ==\n");
        printf("\t== 6)                    salir del programa                ==\n");
        printf("\t=============================================================\n");

        int opcion;
        printf("-->");
        scanf("%d",&opcion);

        /************************variables dato*********************************/
        char destino[MAX_LEN];
        int hora;
        int minutos;
        int dia;
        char mes[MAX_LEN];
        int temporada;
        float precio;
        int cantidad;
        int nodo;
        /**********************************variables ciclo***********************/
        bool mayusculas = false;
        bool minusculas = false;
        bool filtrovalido = false;
        bool horanovalida = true;
        /********************************************************************/
        VDLL_ordenar( registro );
        switch(opcion)
        {
            case 1:

                printf("=============================================\n");
                printf("== ingrese destino del vuelo en mayusculas ==\n");
                printf("=============================================\n");
                while(mayusculas == false )
                {
                    fflush(stdin);
                    gets(destino);
                    bool error = true;
                    for(int i=0;i<strlen(destino);++i)
                    {
                        if(destino[i] >= 'A' && destino[i] <= 'Z')
                        {
                            error = false;
                        }
                        else if( destino [i] == ' ')
                        {
                            error = false;
                        }
                        else
                        {
                            error = true;
                            break;
                        }
                    }
                    if(error == false)
                    {
                        mayusculas = true;
                    }
                    else
                    {
                        printf("\t===========\n");
                        printf("\t== ERROR ==\n");
                        printf("\t===========\n");
                        printf("\n");
                        printf("=======================================================\n");
                        printf("== destino no valido, ingrese otro usando mayusculas ==\n");
                        printf("=======================================================\n");
                    }
                }

                printf("=========================================\n");
                printf("== ingrese la hora de salida del vuelo ==\n");
                printf("=========================================\n");
                printf("==========\n");
                printf("== hora ==\n");
                printf("==========\n");
                while(horanovalida == true)
                {
                    scanf("%d",&hora);
                    horanovalida = VDLL_Find(registro,hora);
                    if(horanovalida == true)
                    {
                        printf("=========================================================================\n");
                        printf("== no se puede registrar mas de un vuelo por hora,ingrese una distinta ==\n");
                        printf("=========================================================================\n");
                    }

                }
                printf("=============\n");
                printf("== minutos ==\n");
                printf("=============\n");
                scanf("%d",&minutos);

                Hora_Ctor(&horaNuevo,hora,minutos);

                printf("==========================================\n");
                printf("== ingrese la fecha de salida del vuelo ==\n");
                printf("==========================================\n");
                printf("=========\n");
                printf("== dia ==\n");
                printf("=========\n");
                scanf("%d",&dia);
                printf("==============================\n");
                printf("== mes ** use minusculas ** ==\n");
                printf("==============================\n");
                while(minusculas == false )
                {
                    fflush(stdin);
                    gets(mes);
                    bool error = true;
                    for(int i=0;i<strlen(mes);++i)
                    {
                        if(mes[i] >= 'a' && mes[i] <= 'z')
                        {
                            error = false;
                        }

                        else
                        {
                            error = true;
                            break;
                        }
                    }
                    if(error == false)
                    {
                        minusculas = true;
                    }
                    else
                    {
                        printf("\t===========\n");
                        printf("\t== ERROR ==\n");
                        printf("\t===========\n");
                        printf("\n");
                        printf("=======================================================\n");
                        printf("== mes no valido, ingrese otro usando minusculas ==\n");
                        printf("=======================================================\n");
                    }
                }
                printf("=========\n");
                printf("== año ==\n");
                printf("=========\n");
                scanf("%d",&temporada);

                Fecha_Ctor(&fechaNuevo,dia,mes,temporada);

                printf("=====================================\n");
                printf("== ingrese el costo de cada boleto ==\n");
                printf("=====================================\n");
                scanf("%f",&precio);
                printf("================================================\n");
                printf("== ingrese la cantidad de boletos disponibles ==\n");
                printf("================================================\n");
                scanf("%d",&cantidad);

                Vuelo_Ctor(&nuevo, destino, precio, cantidad,&horaNuevo,&fechaNuevo);
                VDLL_Push_back(registro,&nuevo);
                VDLL_imprimir_realizado();
                VDLL_imprimir_espera();
                break;
            case 2:
                printf("=========================================\n");
                printf("== ingrese la hora de salida del vuelo ==\n");
                printf("=========================================\n");
                printf("==========\n");
                printf("== hora ==\n");
                printf("==========\n");
                scanf("%d",&hora);


                nodo = VDLL_bbinaria(registro, hora);
                if (nodo != -1)
                {
                    VDLL_movercursor(registro,nodo);
                    VDLL_imprimir_nodobuscado(registro);
                }
                else
                {
                    printf("===============================================\n");
                    printf("== El vuelo buscado no se encuentra registrado ==");
                    printf("===============================================\n");
                }

                VDLL_Erase(registro);
                VDLL_imprimir_realizado();
                VDLL_Delete(&nodobuscar);
                VDLL_imprimir_espera();
                break;
            case 3:
                printf("=========================================\n");
                printf("== ingrese la hora de salida del vuelo ==\n");
                printf("=========================================\n");
                printf("==========\n");
                printf("== hora ==\n");
                printf("==========\n");
                scanf("%d",&hora);

                nodo = VDLL_bbinaria(registro, hora);
                if (nodo != -1)
                {
                    printf("======================================================\n");
                    printf("== ingrese la nueva cantidad de boletos disponibles ==\n");
                    printf("======================================================\n");
                    scanf("%d",&cantidad);
                    VDLL_movercursor(registro,nodo);
                    VDLL_modificar_Cantdisp(registro, cantidad);
                    VDLL_imprimir_nodobuscado(registro);
                }
                else
                {
                    printf("===============================================\n");
                    printf("== El vuelo buscado no se encuentra registrado ==");
                    printf("===============================================\n");
                }
                VDLL_imprimir_realizado();
                VDLL_imprimir_espera();
                break;
            case 4:
                VDLL_print(registro);
                VDLL_imprimir_espera();
                break;
            case 5:
                while(filtrovalido == false )
                {
                    printf("\t========================================\n");
                    printf("\t== ¿que tipo de filtro desea aplicar? ==\n");
                    printf("\t========================================\n");
                    printf("\n");
                    printf("\t================\n");
                    printf("\t== 1) precio    ==\n");
                    printf("\t== 2) destino ==\n");
                    printf("\t================\n");
                    printf("\t-->");
                    int filtro;
                    scanf("%d",&filtro);
                    switch(filtro)
                    {
                        case 1:
                            printf("\t========================================\n");
                            printf("\t== ingrese la hora de su preferencia ==\n");
                            printf("\t========================================\n");
                            int horafiltro;
                            scanf("%d", &horafiltro);
                            printf("\t=====================\n");
                            printf("\t== filtro aplicado ==\n");
                            printf("\t=====================\n");
                            VDLL_filtroprecio(registro, horafiltro);
                            filtrovalido = true;
                            break;
                        case 2:
                            printf("\t========================================================\n");
                            printf("\t== ingrese el destino de su preferencia en mayusculas ==\n");
                            printf("\t========================================================\n");
                            char destinofiltro[MAX_LEN];
                            bool mayusculas = false;
                            while(mayusculas == false )
                            {
                                fflush(stdin);
                                gets(destinofiltro);
                                bool error = true;
                                for(int i=0;i<strlen(destinofiltro);++i)
                                {
                                    if(destinofiltro[i] >= 'A' && destinofiltro[i] <= 'Z')
                                    {
                                        error = false;
                                    }
                                }
                                if(error == false)
                                {
                                    mayusculas = true;
                                }
                                else
                                {
                                    printf("\t===========\n");
                                    printf("\t== ERROR ==\n");
                                    printf("\t===========\n");
                                    printf("\n");
                                    printf("=======================================================\n");
                                    printf("== destino no valido, ingrese otro usando mayusculas ==\n");
                                    printf("=======================================================\n");
                                }
                            }
                            printf("\t=====================\n");
                            printf("\t== filtro aplicado ==\n");
                            printf("\t=====================\n");
                            VDLL_filtroDestino(registro,destinofiltro);
                            filtrovalido = true;
                            break;
                        default:
                            printf("\t===================================\n");
                            printf("\t== opcion no valida,ingresa otra ==\n");
                            printf("\t===================================\n");
                            printf("\n");
                            break;
                    }
                }
                VDLL_imprimir_espera();
                break;
            case 6:
                printf("\t========================================\n");
                printf("\t== Gracias por utilizar este programa ==\n");
                printf("\t========================================\n");
                repetir = false;
                break;
            default:
                printf("\t\t=============\n");
                printf("\t\t=== ERROR ===\n");
                printf("\t\t=============\n");
                printf("\n");
                printf("\t====================================\n");
                printf("\t== opcion no valida, ingrese otra ==\n");
                printf("\t====================================\n");
                break;
            }
    }
    VDLL_Delete( &registro );
}
