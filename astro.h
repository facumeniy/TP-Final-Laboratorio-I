#include <stdio.h>
#include <stdlib.h>
#include "string.h"

const char nombreArchivo[] = "astronautas";

/// ESTRUCTURA
typedef struct
{
    int ID;
    char nombre[30];
    char apellido[30];
    char apodo[30];
    int edad;
    char nacionalidad[30];
    char especialidad[30];
    int horasDeVuelo;
    int misionesRealizadas;
    int horasEnEstacion;
    int estado;
} astro;

/// FUNCIONES
/// AGREGAR ASTRONAUTA
void nuevoAstronauta()
{
    astro astronauta;
    astro nuevoAstronauta;
    int id = 0, estado = 0, edad = 0, horasVuelo = 0, misionesRealizadas = 0, horasEstacion = 0;
    FILE * archi = fopen(nombreArchivo, "ab");

    if(archi != NULL)
    {
        int idRepetido = 0;
        do
        {
            printf("ID del astronauta (mayor que 0):\n");
            fflush(stdin);
            scanf("%d", &id);

            FILE *archi = fopen(nombreArchivo, "rb");
            if (archi != NULL)
            {
                idRepetido = 0;
                astro astronauta;

                while (fread(&astronauta, sizeof(astro), 1, archi) > 0)
                {
                    if (astronauta.ID == id)
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
                nuevoAstronauta.ID = id;
            }
        }
        while (idRepetido || id < 1);


        printf("Nombre:\n");
        fflush(stdin);
        gets(nuevoAstronauta.nombre);
        printf("Apellido:\n");
        fflush(stdin);
        gets(nuevoAstronauta.apellido);
        printf("Apodo:\n");
        fflush(stdin);
        gets(nuevoAstronauta.apodo);

        do
        {
            printf("Edad (18-100):\n");
            fflush(stdin);
            scanf("%d", &edad);
        }
        while(edad < 18 || edad > 100);
        nuevoAstronauta.edad = edad;

        printf("Nacionalidad:\n");
        fflush(stdin);
        gets(nuevoAstronauta.nacionalidad);
        printf("Especialidad:\n");
        fflush(stdin);
        gets(nuevoAstronauta.especialidad);

        do
        {
            printf("Horas de vuelo (0 o mas):\n");
            fflush(stdin);
            scanf("%d", &horasVuelo);
        }
        while(horasVuelo < 0);
        nuevoAstronauta.horasDeVuelo = horasVuelo;

        do
        {
            printf("Cantidad de misiones realizadas (0 o mas):\n");
            fflush(stdin);
            scanf("%d", &misionesRealizadas);
        }
        while(misionesRealizadas < 0);
        nuevoAstronauta.misionesRealizadas = misionesRealizadas;

        do
        {
            printf("Horas acumuladas en la estacion espacial (0 o mas):\n");
            fflush(stdin);
            scanf("%d", &horasEstacion);
        }
        while(horasEstacion < 0);
        nuevoAstronauta.horasEnEstacion = horasEstacion;

        do
        {
            printf("Estado (1: ACTIVO / 2: INACTIVO):\n");
            fflush(stdin);
            scanf("%d", &estado);
        }
        while(estado != 1 && estado != 2);
        nuevoAstronauta.estado = estado;

        fwrite(&nuevoAstronauta, sizeof(astro), 1, archi);
        fclose(archi);
    }
    system("cls");
    printf("*Se agrego un nuevo astronauta a la base de datos*\n");
}

/// MOSTRAR INFO
void printAstro(astro astronauta)
{
    printf("------------------\n");
    printf("[ID astronauta]: %d\n", astronauta.ID);
    printf("[Nombre]: %s\n", astronauta.nombre);
    printf("[Apellido]: %s\n", astronauta.apellido);
    printf("[Apodo]: %s\n", astronauta.apodo);
    printf("[Edad]: %d\n", astronauta.edad);
    printf("[Nacionalidad]: %s\n", astronauta.nacionalidad);
    printf("[Especialidad]: %s\n", astronauta.especialidad);
    printf("[Horas de vuelo]: %d\n", astronauta.horasDeVuelo);
    printf("[Misiones realizadas]: %d\n", astronauta.misionesRealizadas);
    printf("[Horas en estacion]: %d\n", astronauta.horasEnEstacion);
    if(astronauta.estado == 1)
    {
        printf("[Estado]: ACTIVO\n");
    }
    else
    {
        printf("[Estado]: INACTIVO\n");
    }
}

/// MOSTRAR POR ID
void mostrarID(int idAstronauta)
{
    int encontrado = 0;
    astro astronauta;
    FILE * archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        while(fread(&astronauta, sizeof(astro), 1, archi) > 0 && encontrado == 0)
        {
            if(astronauta.ID == idAstronauta)
            {
                printAstro(astronauta);
                encontrado = 1;
            }
        }
        fclose(archi);
    }
    if(encontrado == 0)
    {
        system("cls");
        printf("*No se encontro el astronauta en la base de datos*\n");
    }
}

/// MOSTRAR LISTADO
void mostrarListado()
{
    int encontrado = 0;
    int i = 1;
    astro astronauta;
    FILE * archi = fopen(nombreArchivo, "rb");

    if(archi != NULL)
    {
        system("cls");
        while(fread(&astronauta, sizeof(astro), 1, archi) > 0)
        {
            printf("------------------\n");
            printf("*** [ASTRONAUTA %d] ***\n", i);
            encontrado = 1;
            printAstro(astronauta);
            i++;
        }
        fclose(archi);
    }
    if(encontrado == 0)
    {
        printf("*No hay astronautas en la base de datos*\n");
    }
}

/// MENU MOSTRAR
void mostrarAstronautas()
{
    astro astronauta;

    FILE * archi = fopen(nombreArchivo, "rb");

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
            printf("ID del astronauta a buscar:\n");
            scanf("%d", &id);
            mostrarID(id);
        }
        else if(opcion == 2)
        {
            mostrarListado();
        }
        else
        {
            system("cls");
            printf("*Opcion invalida*\n");
        }
        fclose(archi);
    }
}

/// ESTADO ASTRONAUTAS
void bajaAlta()
{
    astro astronauta;
    FILE* archi = fopen(nombreArchivo, "rb+");

    int id = 0;
    int estado = 0;
    int encontrado = 0;

    printf("ID del astronauta:\n");
    scanf("%d", &id);

    if(archi != NULL)
    {
        while (fread(&astronauta, sizeof(astro), 1, archi) > 0)
        {
            if(astronauta.ID == id)
            {
                encontrado = 1;
                printf("\n*El astronauta tiene el estado de %d*\n", astronauta.estado);
                do
                {
                    printf("\nIngrese el nuevo estado del astronauta (1: ACTIVO / 2: INACTIVO):\n");
                    scanf("%d", &estado);
                }
                while (estado != 1 && estado != 2);
                astronauta.estado = estado;
                int pos = (int)ftell(archi) - sizeof(astro);
                fseek(archi, pos, SEEK_SET);
                fwrite(&astronauta, sizeof(astro), 1, archi);
                system("cls");
                printf("*El estado del astronauta %s cambio a %d*\n", astronauta.apellido, estado);
                break;
            }
        }
    }
    fclose(archi);

    if(encontrado == 0)
    {
        system("cls");
        printf("*No se encontro el astronauta en la base de datos*\n");
    }
}

/// EDITAR TODOS LOS DATOS
void editAstro()
{
    astro astronauta;
    FILE* archi = fopen(nombreArchivo, "rb+");
    int idAstro = 0, estado = 0, edad = 0, horasVuelo = 0, misionesRealizadas = 0, horasEstacion = 0;

    int encontrado = 0;
    int id = 0;
    printf("ID del astronauta:\n");
    scanf("%d", &id);

    if (archi != NULL)
    {
        while (fread(&astronauta, sizeof(astro), 1, archi) > 0)
        {
            if (astronauta.ID == id)
            {
                encontrado = 1;

                system("cls");
                printf("*Editando datos del astronauta de ID: %d*\n", id);

                printf("Nombre:\n");
                fflush(stdin);
                gets(astronauta.nombre);
                printf("Apellido:\n");
                fflush(stdin);
                gets(astronauta.apellido);
                printf("Apodo:\n");
                fflush(stdin);
                gets(astronauta.apodo);

                do
                {
                    printf("Edad (18-100)\n");
                    fflush(stdin);
                    scanf("%d", &edad);
                }
                while(edad < 18 || edad > 100);
                astronauta.edad = edad;

                printf("Nacionalidad:\n");
                fflush(stdin);
                gets(astronauta.nacionalidad);
                printf("Especialidad:\n");
                fflush(stdin);
                gets(astronauta.especialidad);

                do
                {
                    printf("Horas de vuelo (0 o mas):\n");
                    fflush(stdin);
                    scanf("%d", &horasVuelo);
                }
                while(horasVuelo < 0);
                astronauta.horasDeVuelo = horasVuelo;

                do
                {
                    printf("Cantidad de misiones realizadas (0 o mas):\n");
                    fflush(stdin);
                    scanf("%d", &misionesRealizadas);
                }
                while(misionesRealizadas < 0);
                astronauta.misionesRealizadas = misionesRealizadas;

                do
                {
                    printf("Horas acumuladas en la estacion espacial (0 o mas):\n");
                    fflush(stdin);
                    scanf("%d", &horasEstacion);
                }
                while(horasEstacion < 0);
                astronauta.horasEnEstacion = horasEstacion;

                do
                {
                    printf("Estado (1: ACTIVO / 2: INACTIVO):\n");
                    fflush(stdin);
                    scanf("%d", &estado);
                }
                while(estado != 1 && estado != 2);
                astronauta.estado = estado;

                int pos = ftell(archi) - sizeof(astro);
                fseek(archi, pos, SEEK_SET);
                fwrite(&astronauta, sizeof(astro), 1, archi);
                system("cls");
                printf("*Los datos del astronauta se sobrescribieron correctamente*\n");
                break;
            }
        }
    }
    fclose(archi);
    if (encontrado == 0)
    {
        system("cls");
        printf("*No se encontro el astronauta en la base de datos*\n");
    }
}

/// MENU EDICION ASTRO
void editarAstronautas()
{
    int opcion = 0;

    printf(" 1. [DAR DE BAJA/ALTA]\n");
    printf(" 2. [EDITAR DATOS]\n");
    printf(" 3. [VOLVER]\n");
    scanf("%d", &opcion);


    if(opcion == 1)
    {
        system("cls");
        bajaAlta();
    }
    else if(opcion == 2)
    {
        system("cls");
        editAstro();
    }
    else
    {
        system("cls");
        printf("*Opcion invalida*\n");
    }
}
