UWU.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>

struct paciente
{
    char apellido[50];
    char nombre[50];
    int edad;
    float altura;
    float peso;
    float presion;
};

void ingresoDatos(char *archivo, struct paciente nuevo)
{
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    FILE *archivoP;
    archivoP = fopen(archivo, "a+");
    if (archivoP == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    else
    {
        strftime(output, 128, "%d/%m/%y %H:%M:%S", tlocal);
        fprintf(archivoP, "%s;%s;%d;%.2f;%.2f;%.2f;%s\n", nuevo.apellido, nuevo.nombre, nuevo.edad, nuevo.altura, nuevo.peso, nuevo.presion, output);
    }

    fclose(archivoP);
}

int cambiarDatos(char *archivo, char *apellido)
{
    int posicion;
    char apellidoEncontrado[50];
    char nombre[50];
    int edad;
    float altura, peso, presion;
    FILE *archivoP;
    archivoP = fopen(archivo, "a+");
    if (archivoP == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return 0;
    }
    else
    {
        while (!feof(archivoP))
        {

            posicion = ftell(archivoP);
            fscanf(archivoP, "%s;%s;%d;%f;%f;%f", &apellidoEncontrado, &nombre, &edad, &altura, &peso, &presion);
            if (strcmp(apellido, apellidoEncontrado) == 0)
            {
                printf("Los datos encontrados son:\n %s;%s;%d;%f;%f;%f", apellidoEncontrado, nombre, edad, altura, altura, peso, presion);
                break;
            }
        }
        return posicion;
    }

    fclose(archivoP);
}



int main()
{
    char apellido [50];
    int menu, menu1, posicion;
    struct paciente nuevo;
    char nombreArchivo[40] = "Registros medicos.txt";

    puts("Bienvenido a su sistema de registros medicos\n");

    do
    {
        puts("Elija una de las siguientes opciones:\n");
        puts("1. Ingresar nuevo paciente\n");
        puts("2. Encontrar paciente\n");
        puts("3. Salir\n");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            do
            {
                puts("\nApellido:");
                scanf("%s", nuevo.apellido);
                fflush(stdin);
                puts("\nNombre:");
                scanf("%s", nuevo.nombre);
                fflush(stdin);
                puts("\nEdad:");
                scanf("%d", &nuevo.edad);
                fflush(stdin);
                puts("\nAltura:");
                scanf("%f", &nuevo.altura);
                fflush(stdin);
                puts("\nPeso:");
                scanf("%f", &nuevo.peso);
                fflush(stdin);
                puts("\nPresion:");
                scanf(" %f", &nuevo.presion);
                fflush(stdin);
                puts("\nDatos guardados\n");
                ingresoDatos(nombreArchivo, nuevo);

                puts("Desea ingresar otro paciente\n1.Si\n2.No");
                scanf("%d", &menu1);
                while (menu1 != 1 && menu1 != 2)
                {
                    puts("Esa no es una opcion valida elija:\n1.Si\n2.No");
                    scanf("%d", &menu1);
                }

            } while (menu1 == 1);
            break;
        case 2:
            printf("Ingrese el apellido del paciente que desea encontrar\n");
            scanf("%s", &apellido);
            posicion=cambiarDatos(nombreArchivo, apellido);
            printf("Listo %d\n", posicion);
            break;
        case 3:
            /* code */
            break;
        default:
            printf("Lo siento, esa no es una opcion\n");
            break;
        }

    } while (menu != 3);

    puts("Gracias por usar nuestro servicio\nAdios");
    return 0;
}