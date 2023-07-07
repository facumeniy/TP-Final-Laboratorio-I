#include <stdio.h>
#include <stdlib.h>
#include "string.h"

const char nombreArchivo2[] = "naves";

/// ESTRUCTURA
typedef struct
{
    int ID;
    char nombre[30];
    int tipo;
    int cantVuelos;
    int horasDeVuelo;
    int estado;
} nave;

/// FUNCIONES
/// AGREGAR NAVE
void cargarNave()
{
    nave Nave;
    int id = 0, tipoNave = 0, cantVuelos = 0, horasVuelo = 0, estado = 0;
    FILE * archi = fopen(nombreArchivo2, "ab");

    if(archi != NULL)
    {
        int idRepetido = 0;
        do
        {
            printf("ID de la nave (mayor que 0):\n");
            fflush(stdin);
            scanf("%d", &id);

            FILE *archi = fopen("naves", "rb");
            if (archi != NULL)
            {
                idRepetido = 0;
                nave nave2;

                while (fread(&nave2, sizeof(nave), 1, archi) > 0)
                {
                    if (nave2.ID == id)
                    {
                        idRepetido = 1;
                        break;
                    }
                }

                fclose(archi);
            }

            if(idRepetido == 1)
            {
                system("cls");
                printf("*ID ya registrado. Ingrese otro ID*\n");
            }
            else if(id < 1)
            {
                system("cls");
                printf("*El ID debe ser mayor que 0*\n");
            }
            else
            {
                Nave.ID = id;
            }
        }
        while (idRepetido || id < 1);

        printf("Nombre de la nave:\n");
        fflush(stdin);
        gets(Nave.nombre);

        do
        {
            printf("Tipo de nave (1: STARSHIP / 2: FALCON-9 / 3: FALCON-HEAVY):\n");
            fflush(stdin);
            scanf("%d", &tipoNave);
        }
        while(tipoNave != 1 && tipoNave != 2 && tipoNave != 3);
        Nave.tipo = tipoNave;

        do
        {
            printf("Cantidad de vuelos (0 o mas):\n");
            fflush(stdin);
            scanf("%d", &cantVuelos);
        }
        while(cantVuelos < 0);
        Nave.cantVuelos = cantVuelos;

        do
        {
            printf("Horas de vuelos (0 o mas):\n");
            fflush(stdin);
            scanf("%d", &horasVuelo);
        }
        while(horasVuelo < 0);
        Nave.horasDeVuelo = horasVuelo;

        do
        {
            printf("Estado (0: EN MANTENIMIENTO / 1: LISTA / 2: EN MISION / 3: DE BAJA):\n");
            fflush(stdin);
            scanf("%d", &estado);
        }
        while(estado != 0 && estado != 1 && estado != 2 && estado != 3);
        Nave.estado = estado;

        fwrite(&Nave, sizeof(nave), 1, archi);
        fclose(archi);
    }
    system("cls");
    printf("*Se agrego una nueva nave a la base de datos*\n");
}

/// MOSTRAR INFO
void printNave(nave Nave)
{
    printf("------------------\n");
    printf("[ID nave]: %d\n", Nave.ID);
    printf("[Nombre nave]: %s\n", Nave.nombre);
    if(Nave.tipo == 1)
    {
        printf("[Tipo]: STARSHIP\n");
    }
    else if(Nave.tipo == 2)
    {
        printf("[Tipo]: FALCON-9\n");
    }
    else
    {
        printf("[Tipo]: FALCON-HEAVY\n");
    }
    printf("[Vuelos realizados]: %d\n", Nave.cantVuelos);
    printf("[Horas de vuelo]: %d\n", Nave.horasDeVuelo);
    if(Nave.estado == 0)
    {
        printf("[Estado]: EN MANTENIMIENTO\n");
    }
    else if(Nave.estado == 1)
    {
        printf("[Estado]: LISTA PARA USO\n");
    }
    else if(Nave.estado == 2)
    {
        printf("[Estado]: EN MISION\n");
    }
    else
    {
        printf("[Estado]: DE BAJA\n");
    }
}

/// MOSTRAR POR ID
void mostrarIDNave(int idNave)
{
    int encontrado = 0;
    nave Nave;
    FILE * archi = fopen(nombreArchivo2, "rb");

    if(archi != NULL)
    {
        while(fread(&Nave, sizeof(nave), 1, archi) > 0 && encontrado == 0)
        {
            if(Nave.ID == idNave)
            {
                printNave(Nave);
                encontrado = 1;
            }
        }
        fclose(archi);
    }
    if(encontrado == 0)
    {
        system("cls");
        printf("*No se encontro la nave en la base de datos*\n");
    }
}

/// MOSTRAR LISTADO
void mostrarListadoNaves()
{
    int encontrado = 0;
    int i = 1;
    nave Nave;
    FILE * archi = fopen(nombreArchivo2, "rb");

    if(archi != NULL)
    {
        system("cls");
        while(fread(&Nave, sizeof(nave), 1, archi) > 0)
        {
            printf("------------------\n");
            printf("*** [NAVE %d] ***\n", i);
            encontrado = 1;
            printNave(Nave);
            i++;
        }
        fclose(archi);
    }
    if(encontrado == 0)
    {
        printf("*No hay naves en la base de datos*\n");
    }
}

/// MENU MOSTRAR
void mostrarNaves()
{
    nave Nave;

    FILE * archi = fopen(nombreArchivo2, "rb");

    if(archi != NULL)
    {
        int opcion = 0;

        printf(" 1. [BUSCAR POR ID]\n");
        printf(" 2. [MOSTRAR LISTADO]\n");
        printf(" 3. [VOLVER]\n");
        scanf("%d", &opcion);

        if(opcion == 1)
        {
            int id = 0;
            system("cls");
            printf("ID de la nave a buscar:\n");
            scanf("%d", &id);
            mostrarIDNave(id);
        }
        else if(opcion == 2)
        {
            mostrarListadoNaves();
        }
        else
        {
            system("cls");
            printf("*Opcion invalida*\n");
        }
        fclose(archi);
    }
}

/// ESTADO NAVES
void bajaAltaNaves()
{
    nave Nave;
    FILE* archi = fopen(nombreArchivo2, "rb+");

    int id = 0;
    int estado = 0;
    int encontrado = 0;

    printf("ID de la nave:\n");
    scanf("%d", &id);

    if(archi != NULL)
    {
        while (fread(&Nave, sizeof(nave), 1, archi) > 0)
        {
            if(Nave.ID == id)
            {
                encontrado = 1;
                system("cls");
                printf("*La nave tiene el estado de %d*\n", Nave.estado);
                do
                {
                    printf("\nIngrese el nuevo estado de la nave (0: EN MANTENIMIENTO / 1: LISTA / 2: EN MISION / 3: DE BAJA):\n");
                    scanf("%d", &estado);
                }
                while (estado != 0 && estado != 1 && estado != 2 && estado != 3);
                Nave.estado = estado;
                int pos = (int)ftell(archi) - sizeof(nave);
                fseek(archi, pos, SEEK_SET);
                fwrite(&Nave, sizeof(nave), 1, archi);
                system("cls");
                printf("*El estado de la nave %s cambio a %d*\n", Nave.nombre, estado);
                break;
            }
        }
    }
    fclose(archi);

    if(encontrado == 0)
    {
        system("cls");
        printf("*No se encontro la nave en la base de datos*\n");
    }
}

/// EDITAR TODOS LOS DATOS
void editNave()
{
    nave Nave;
    FILE* archi = fopen(nombreArchivo2, "rb+");
    int idNave = 0, tipoNave = 0, cantVuelos = 0, horasVuelo = 0, estado = 0;

    int encontrado = 0;
    int id = 0;
    printf("ID de la nave:\n");
    scanf("%d", &id);

    if (archi != NULL)
    {
        while (fread(&Nave, sizeof(nave), 1, archi) > 0)
        {
            if (Nave.ID == id)
            {
                encontrado = 1;

                system("cls");
                printf("*Editando datos de la nave de ID: %d*\n", id);

                printf("Nombre de la nave:\n");
                fflush(stdin);
                gets(Nave.nombre);

                do
                {
                    printf("Tipo de nave (1: STARSHIP / 2: FALCON-9 / 3: FALCON-HEAVY):\n");
                    fflush(stdin);
                    scanf("%d", &tipoNave);
                }
                while(tipoNave != 1 && tipoNave != 2 && tipoNave != 3);
                Nave.tipo = tipoNave;

                do
                {
                    printf("Cantidad de vuelos (0 o mas):\n");
                    fflush(stdin);
                    scanf("%d", &cantVuelos);
                }
                while(cantVuelos < 0);
                Nave.cantVuelos = cantVuelos;

                do
                {
                    printf("Horas de vuelos (0 o mas):\n");
                    fflush(stdin);
                    scanf("%d", &horasVuelo);
                }
                while(horasVuelo < 0);
                Nave.horasDeVuelo = horasVuelo;

                do
                {
                    printf("Estado (0: EN MANTENIMIENTO / 1: LISTA / 2: EN MISION / 3: DE BAJA):\n");
                    fflush(stdin);
                    scanf("%d", &estado);
                }
                while(estado != 0 && estado != 1 && estado != 2 && estado != 3);
                Nave.estado = estado;

                int pos = ftell(archi) - sizeof(nave);
                fseek(archi, pos, SEEK_SET);
                fwrite(&Nave, sizeof(nave), 1, archi);
                system("cls");
                printf("*Los datos de la nave se sobrescribieron correctamente*\n");
                break;
            }
        }
    }
    fclose(archi);
    if (encontrado == 0)
    {
        system("cls");
        printf("*No se encontro la nave en la base de datos*\n");
    }
}

/// MENU EDICION NAVES
void editarNaves()
{
    int opcion = 0;

    printf(" 1. [CAMBIAR ESTADO]\n");
    printf(" 2. [EDITAR DATOS]\n");
    printf(" 3. [VOLVER]\n");
    scanf("%d", &opcion);

    if(opcion == 1)
    {
        system("cls");
        bajaAltaNaves();
    }
    else if(opcion == 2)
    {
        system("cls");
        editNave();
    }
    else
    {
        system("cls");
        printf("*Opcion invalida*\n");
    }
}
