#include <stdio.h>
#include <stdlib.h>
#include "astro.h"
#include "naves.h"
#include "misiones.h"

/// PROTOTIPADOS
/// MENUS
void menuPrincipal();
void menuAstro();
void menuNaves();
void menuMisiones();
/// ASTRONAUTAS
void nuevoAstronauta();
void printAstro(astro);
void mostrarID(int);
void mostrarListado();
void mostrarAstronautas();
void bajaAlta();
void editAstro();
void editarAstronautas();
/// NAVES
void cargarNave();
void printNave(nave);
void mostrarIDNave(int);
void mostrarListadoNaves();
void mostrarNaves();
void bajaAltaNaves();
void editNave();
void editarNaves();
/// MISIONES
void nuevaMision();
void printMision(stMision, int);
void mostrarIDMision(int, int);
void mostrarListadoMision(int);
void mostrarMisiones(int);
void bajaAltaMision();
void lanzarMision();
void editarMision();

int main()
{
    /// SWITCH
    int opcion;

    /// OPCIONES CASE
    int opcionAstro;
    int opcionNaves;
    int opcionMisiones;

    while(1)
    {
        menuPrincipal();
        fflush(stdin);
        scanf("%d", &opcion);

        switch (opcion)
        {
        /// MENU ASTRONAUTAS
        case 1:
            system("cls");
            menuAstro();
            opcionAstro = 0;

            while(opcionAstro != 4)
            {
                fflush(stdin);
                scanf("%d", &opcionAstro);

                if(opcionAstro == 1)
                {
                    system("cls");
                    nuevoAstronauta();
                    menuAstro();
                }
                else if(opcionAstro == 2)
                {
                    system("cls");
                    mostrarAstronautas();
                    fflush(stdin);
                    menuAstro();
                }
                else if(opcionAstro == 3)
                {
                    system("cls");
                    editarAstronautas();
                    fflush(stdin);
                    menuAstro();
                }
                else
                {
                    system("cls");
                    menuAstro();
                }
            }
            break;

        /// MENU NAVES
        case 2:
            system("cls");
            menuNaves();
            opcionNaves = 0;

            while(opcionNaves != 4)
            {
                fflush(stdin);
                scanf("%d", &opcionNaves);

                if(opcionNaves == 1)
                {
                    system("cls");
                    cargarNave();
                    menuNaves();
                }
                else if(opcionNaves == 2)
                {
                    system("cls");
                    mostrarNaves();
                    fflush(stdin);
                    menuNaves();
                }
                else if(opcionNaves == 3)
                {
                    system("cls");
                    editarNaves();
                    fflush(stdin);
                    menuNaves();
                }
                else
                {
                    system("cls");
                    menuNaves();
                }
            }
            break;

        /// MENU MISIONES
        case 3:
            system("cls");
            menuMisiones();
            opcionMisiones = 0;

            while(opcionMisiones != 4)
            {
                fflush(stdin);
                scanf("%d", &opcionMisiones);

                if(opcionMisiones == 1)
                {
                    system("cls");
                    nuevaMision();
                    menuMisiones();
                }
                else if(opcionMisiones == 2)
                {
                    system("cls");
                    mostrarMisiones(10);
                    fflush(stdin);
                    menuMisiones();
                }
                else if(opcionMisiones == 3)
                {
                    system("cls");
                    editarMision();
                    fflush(stdin);
                    menuMisiones();
                }
                else
                {
                    system("cls");
                    menuMisiones();
                }
            }
            break;

        case 4:
            printf("\n*Saliendo del programa*\n");
            return 0;

        default:
            break;
        }
    }
    return 0;
}

/// FUNCIONES MENU
void menuPrincipal()
{
    system("cls");
    printf("   Sistema de registros de spaceX\n");
    printf("\n          MENU DE OPCIONES          ");
    printf("\n          ----------------          \n\n");
    printf(" 1. [ASTRONAUTAS]\n");
    printf(" 2. [NAVES]\n");
    printf(" 3. [MISIONES]\n");
    printf(" 4. [SALIR]\n\n");
}

void menuAstro()
{
    printf("\n         MENU DE ASTRONAUTAS    ");
    printf("\n         -------------------\n\n");
    printf(" 1. [NUEVO ASTRONAUTA]\n");
    printf(" 2. [MOSTRAR ASTRONAUTAS] (debe haber astronautas registrados para acceder)\n");
    printf(" 3. [EDITAR ASTRONAUTAS]\n");
    printf(" 4. [VOLVER]\n\n");
}

void menuNaves()
{
    printf("\n           MENU DE NAVES     ");
    printf("\n           ------------- \n\n");
    printf(" 1. [NUEVA NAVE]\n");
    printf(" 2. [MOSTRAR NAVES] (debe haber naves registradas para acceder)\n");
    printf(" 3. [EDITAR NAVES]\n");
    printf(" 4. [VOLVER]\n\n");
}

void menuMisiones()
{
    printf("\n          MENU DE MISIONES        ");
    printf("\n          ----------------    \n\n");
    printf(" 1. [NUEVA MISION]\n");
    printf(" 2. [MOSTRAR MISIONES] (debe haber misiones registradas para acceder)\n");
    printf(" 3. [ACTUALIZAR MISION]\n");
    printf(" 4. [VOLVER]\n\n");
}
