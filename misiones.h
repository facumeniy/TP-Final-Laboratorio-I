#include <stdio.h>
#include <stdlib.h>
#include "string.h"

const char nombreArchivo3[] = "misiones";

/// ESTRUCTURA
typedef struct
{
    int ID;
    int IDnave;
    int estado;
    char destino[30];
    char cargamento[30];
    int tripulantes[30];
    char detalleMision[30];
} stMision;

/// FUNCIONES
/// AGREGAR MISION
void nuevaMision()
{
    astro astronauta;
    nave naveMision;
    stMision mision;
    int i= 0, idMision = 0, idNave = 0, idNaveEncontrada = 0, estado = 0,  tripulanteEncontrado = 0, proceder = 0;
    char opcionTripulantes = ' ';

    FILE * archi = fopen(nombreArchivo3, "ab");
    FILE * archi2 = fopen("naves", "rb");
    FILE * archi3 = fopen("astronautas", "rb");

    if(archi != NULL && archi2 != NULL && archi3 != NULL)
    {
        int id = 0;
        int idRepetido = 0;

        do
        {
            printf("ID de la mision (mayor que 0):\n");
            fflush(stdin);
            scanf("%d", &id);

            FILE *archi = fopen(nombreArchivo3, "rb");
            if (archi != NULL)
            {
                idRepetido = 0;
                stMision mision2;

                while (fread(&mision2, sizeof(stMision), 1, archi) > 0)
                {
                    if (mision2.ID == id)
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
                mision.ID = id;
            }
        }
        while (idRepetido || id < 1);

        do
        {
            printf("ID nave\n");
            fflush(stdin);
            scanf("%d", &idNave);
        }
        while(idNave < 1);

        while(fread(&naveMision, sizeof(nave), 1, archi2) > 0)
        {
            if(naveMision.ID == idNave)
            {
                idNaveEncontrada = 1;
                break;
            }
        }

        if(idNaveEncontrada == 1)
        {
            if(naveMision.estado == 1)
            {
                printf("*Nave %s asignada correctamente*\n", naveMision.nombre);
                mision.IDnave = idNave;

                do
                {
                    printf("Estado: (1: LISTO / 2: EN VUELO / 3: RETORNADA / 4: CANCELADA / 5: FALLIDA)\n");
                    fflush(stdin);
                    scanf("%d", &estado);
                }
                while(estado != 1 && estado != 2 && estado != 3 && estado != 4 && estado != 5);
                mision.estado = estado;

                printf("Destino:\n");
                fflush(stdin);
                gets(mision.destino);

                printf("Cargamento:\n");
                fflush(stdin);
                gets(mision.cargamento);

                do
                {
                    int idTripulante = 0;
                    int tripulanteEncontrado = 0;

                    printf("ID del tripulante:\n");
                    fflush(stdin);
                    scanf("%d", &idTripulante);

                    rewind(archi3);

                    while (fread(&astronauta, sizeof(astro), 1, archi3) > 0)
                    {
                        if (astronauta.ID == idTripulante)
                        {
                            tripulanteEncontrado = 1;
                            break;
                        }
                    }

                    if (tripulanteEncontrado == 1)
                    {
                        if(astronauta.estado == 2)
                        {
                            printf("*No se puede asignar el astronauta ya que se encuentra INACTIVO*\n");
                        }
                        else
                        {
                            proceder = 1;
                            printf("*Tripulante %s agregado correctamente*\n", astronauta.apellido);
                            mision.tripulantes[i] = idTripulante;
                            i++;
                        }
                    }
                    else
                    {
                        printf("*No se encontro el astronauta en la base de datos*\n");
                    }

                    printf("'s' para agregar mas tripulantes\n");
                    fflush(stdin);
                    scanf(" %c", &opcionTripulantes);
                }
                while (opcionTripulantes == 's');

                printf("Detalle de la mision\n");
                fflush(stdin);
                gets(mision.detalleMision);

                if(proceder == 1)
                {
                    fwrite(&mision, sizeof(stMision), 1, archi);
                    system("cls");
                    printf("*Mision agregada correctamente*\n");
                }
                else
                {
                    system("cls");
                    printf("*No hay tripulantes. Cancelando preparacion*\n");
                }
            }
            else
            {
                system("cls");
                printf("*La nave no se puede asignar porque se encuentra en estado %d (Debe estar LISTA)*\n", naveMision.estado);
            }
        }
        else
        {
            system("cls");
            printf("*ID de nave no encontrado. Cancelando preparacion*\n");
        }
    }
    else
    {
        printf("*No hay astronautas/naves suficientes para empezar una mision*\n");
    }
    fclose(archi);
    fclose(archi2);
    fclose(archi3);
}

/// MOSTRAR INFO
void printMision(stMision mision, int validos)
{
    astro astronauta;
    nave Nave;
    FILE * archi = fopen("naves", "rb");
    FILE * archi2 = fopen("astronautas", "rb");
    int tripulantes = 0;
    int encontrado = 0;

    if(archi != NULL && archi2 != NULL)
    {
        printf("------------------\n");
        printf("[ID mision]: %d\n", mision.ID);

        if(mision.estado == 1)
        {
            printf("[Estado mision]: LISTO\n");
        }
        else if(mision.estado == 2)
        {
            printf("[Estado mision]: EN VUELO\n");
        }
        else if(mision.estado == 3)
        {
            printf("[Estado mision]: RETORNADA\n");
        }
        else if(mision.estado == 4)
        {
            printf("[Estado mision]: CANCELADA\n");
        }
        else
        {
            printf("[Estado mision]: FALLIDA\n");
        }

        printf("[Destino mision]: %s\n", mision.destino);
        printf("[Cargamento mision]: %s\n", mision.cargamento);
        printf("[Detalle]: %s\n", mision.detalleMision);

        printf("------------------\n");
        printf("[NAVE DESIGNADA]\n");
        while(fread(&Nave, sizeof(nave), 1, archi) > 0 && encontrado == 0)
        {
            if(Nave.ID == mision.IDnave)
            {
                printNave(Nave);
                encontrado = 1;
            }
        }

        while(fread(&astronauta, sizeof(astro), 1, archi2) > 0)
        {
            for(int i = 0; i < validos; i++)
            {
                if(mision.tripulantes[i] == astronauta.ID)
                {
                    if(tripulantes == 0)
                    {
                        printf("------------------\n");
                        printf("[TRIPULANTES]\n");
                        tripulantes = 1;
                    }
                    printAstro(astronauta);
                }
            }
        }
    }
    fclose(archi);
    fclose(archi2);
}

/// MOSTRAR POR ID
void mostrarIDMision(int idMision, int validos)
{
    int encontrado = 0;
    stMision mision;
    astro astronauta;

    FILE *archi = fopen(nombreArchivo3, "rb");

    if (archi != NULL)
    {
        while (fread(&mision, sizeof(stMision), 1, archi) > 0 && encontrado == 0)
        {
            if (mision.ID == idMision)
            {
                printMision(mision, validos);
                encontrado = 1;
            }
        }
        fclose(archi);
    }

    if (encontrado == 0)
    {
        system("cls");
        printf("*No se encontro la mision en la base de datos*\n");
    }
}


/// MOSTRAR LISTADO
void mostrarListadoMision(int validos)
{
    int encontrado = 0;
    int i = 1;
    stMision mision;
    FILE * archi = fopen(nombreArchivo3, "rb");

    if(archi != NULL)
    {
        system("cls");
        while(fread(&mision, sizeof(stMision), 1, archi) > 0)
        {
            printf("------------------\n");
            printf("*** [MISION %d] ***\n", i);
            encontrado = 1;
            printMision(mision, validos);
            i++;
        }
        fclose(archi);
    }
    if(encontrado == 0)
    {
        printf("*No hay misiones en la base de datos*\n");
    }
}

/// MENU MOSTRAR
void mostrarMisiones(int validos)
{
    stMision mision;

    FILE * archi = fopen(nombreArchivo3, "rb");

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
            printf("ID de la mision a buscar:\n");
            scanf("%d", &id);
            mostrarIDMision(id, validos);
        }
        else if(opcion == 2)
        {
            mostrarListadoMision(validos);
        }
        else
        {
            system("cls");
            printf("*Opcion invalida*\n");
        }
        fclose(archi);
    }
}

/// BAJA/ALTA MISION
void bajaAltaMision()
{
    nave Nave;
    stMision mision;
    FILE* archi = fopen(nombreArchivo3, "rb+");
    FILE* archi2 = fopen("naves", "rb+");

    int id = 0;
    int estado = 0;
    int encontrado = 0;

    system("cls");
    printf("ID de la mision:\n");
    scanf("%d", &id);

    if (archi != NULL && archi2 != NULL)
    {
        while (fread(&mision, sizeof(stMision), 1, archi) > 0)
        {
            if (mision.ID == id)
            {
                encontrado = 1;
                printf("\n*La mision tiene el estado de %d*\n", mision.estado);
                do
                {
                    printf("Ingrese el nuevo estado de la mision (1: LISTA / 4: DE BAJA):\n");
                    scanf("%d", &estado);
                }
                while (estado != 1 && estado != 4);

                while (fread(&Nave, sizeof(nave), 1, archi2) > 0)
                {
                    if (Nave.ID == mision.IDnave)
                    {
                        if (estado == 1)
                        {
                            if (Nave.estado == 1)
                            {
                                mision.estado = estado;
                                int pos = (int)ftell(archi) - sizeof(stMision);
                                fseek(archi, pos, SEEK_SET);
                                fwrite(&mision, sizeof(stMision), 1, archi);
                                system("cls");
                                printf("*Se actualizo correctamente el estado de la mision*\n");
                                break;
                            }
                            else
                            {
                                system("cls");
                                printf("*La nave no esta lista para despegar. Estado: %d*\n", Nave.estado);
                                break;
                            }
                        }
                        else if (estado == 4)
                        {
                            if (Nave.estado == 1)
                            {
                                mision.estado = estado;
                                int pos = (int)ftell(archi) - sizeof(stMision);
                                fseek(archi, pos, SEEK_SET);
                                fwrite(&mision, sizeof(stMision), 1, archi);
                                system("cls");
                                printf("*Se actualizo correctamente el estado de la mision*\n");
                                break;
                            }
                            else if (Nave.estado == 2)
                            {
                                mision.estado = estado;
                                int pos = (int)ftell(archi) - sizeof(stMision);
                                fseek(archi, pos, SEEK_SET);
                                fwrite(&mision, sizeof(stMision), 1, archi);
                                system("cls");
                                printf("*Se actualizo correctamente el estado de la mision*\n");
                                break;
                            }
                            else
                            {
                                system("cls");
                                printf("*ERROR: La nave no esta disponible para su uso*\n");
                                break;
                            }
                        }
                    }
                }
                break;
            }
        }
    }
    fclose(archi);
    fclose(archi2);

    if (encontrado == 0)
    {
        system("cls");
        printf("*No se encontro la mision en la base de datos*\n");
    }
}

/// LANZAR MISION
void lanzarMision()
{
    stMision mision;
    FILE* archi = fopen(nombreArchivo3, "rb+");
    int idNave = 0, tipoNave = 0, cantVuelos = 0, horasVuelo = 0, estado = 0;

    int encontrado = 0;
    int id = 0;
    char opcion = ' ';
    printf("ID de la mision:\n");
    scanf("%d", &id);

    if (archi != NULL)
    {
        while (fread(&mision, sizeof(stMision), 1, archi) > 0)
        {
            if (mision.ID == id)
            {
                encontrado = 1;

                if (mision.estado == 1)
                {
                    system("cls");
                    printf("Estado de la mision: LISTO\n");
                    printf("Presione 's' si desea actualizar el estado de la mision a: EN VUELO\n");
                    fflush(stdin);
                    scanf(" %c", &opcion);
                    if (opcion == 's')
                    {
                        system("cls");
                        printf("*El estado de la mision cambio a: EN VUELO*\n");
                        mision.estado = 2;
                        int pos = (int)ftell(archi) - sizeof(stMision);
                        fseek(archi, pos, SEEK_SET);
                        fwrite(&mision, sizeof(stMision), 1, archi);
                        break;
                    }
                    else
                    {
                        printf("*ERROR. Opcion invalida*\n");
                        break;
                    }
                }
                else if (mision.estado == 2)
                {
                    system("cls");
                    printf("Estado de la mision: EN VUELO\n");
                    printf("Presione 'r' si desea actualizar el estado de la mision a: RETORNADA\nPresione 'f' si desea actualizar el estado de la mision a: FALLIDA\n");
                    fflush(stdin);
                    scanf(" %c", &opcion);
                    if (opcion == 'r')
                    {
                        system("cls");
                        printf("*El estado de la mision cambio a: RETORNADA*\n");
                        mision.estado = 3;
                        int pos = (int)ftell(archi) - sizeof(stMision);
                        fseek(archi, pos, SEEK_SET);
                        fwrite(&mision, sizeof(stMision), 1, archi);
                        break;
                    }
                    else if (opcion == 'f')
                    {
                        system("cls");
                        printf("*El estado de la mision cambio a: FALLIDA*\n");
                        mision.estado = 5;
                        int pos = (int)ftell(archi) - sizeof(stMision);
                        fseek(archi, pos, SEEK_SET);
                        fwrite(&mision, sizeof(stMision), 1, archi);
                        break;
                    }
                    else
                    {
                        printf("*ERROR. Opcion invalida*\n");
                        break;
                    }
                }
                else
                {
                    system("cls");
                    printf("*La mision no se puede actualizar porque se encuentra en estado %d*\n", mision.estado);
                    break;
                }
            }
        }
    }
    fclose(archi);

    if (encontrado == 0)
    {
        system("cls");
        printf("*No se encontro la mision en la base de datos*\n");
    }
}

/// MENU LANZAR MISIONES
void editarMision()
{
    int opcion = 0;

    printf(" 1. [DAR DE BAJA/ALTA MISION]\n");
    printf(" 2. [ACTUALIZAR MISION]\n");
    printf(" 3. [VOLVER]\n");
    scanf("%d", &opcion);

    if(opcion == 1)
    {
        system("cls");
        bajaAltaMision();
    }
    else if(opcion == 2)
    {
        system("cls");
        lanzarMision();
    }
    else
    {
        system("cls");
        printf("*Opcion invalida*\n");
    }
}
