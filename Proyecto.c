/*Nombre del sistema: Sistema de Inventario para Tienda de Electrónica

Usuarios: 
1. Administrador de la tienda
2. Empleados de la tienda
3. Contador

Objetivos:
1. Mantener un registro actualizado de los productos electrónicos disponibles en la tienda.
2. Facilitar la entrada, edición y eliminación de productos.
3. Proporcionar una lista de productos ingresados para una fácil referencia.
4. Ayudar en la gestión eficiente del inventario y evitar la escasez o el exceso de stock.

Contexto del problema:
Económico: En el sector de la electrónica, la gestión eficiente del inventario es crucial debido a la rápida obsolescencia de los productos. Un sistema de inventario bien implementado puede ayudar a reducir los costos de almacenamiento y evitar la pérdida de ventas debido a la falta de stock.
Social: Un sistema de inventario eficiente puede mejorar la satisfacción del cliente al asegurar que los productos electrónicos necesarios estén disponibles cuando se necesiten.
Ambiental: Al evitar el exceso de stock, el sistema de inventario puede contribuir a reducir el desperdicio y el impacto ambiental asociado con la producción y eliminación de productos electrónicos.

Restricciones:
1. Cumplimiento de las regulaciones fiscales y contables en la gestión del inventario.
2. Necesidad de integrar el sistema de inventario con otros sistemas de la tienda, como el sistema de ventas y contabilidad.
3. Necesidad de proteger la información del inventario contra el acceso no autorizado.

Limitaciones:
1. El sistema debe ser desarrollado en el lenguaje de programación C.
2. El sistema debe ser capaz de funcionar en un entorno de hardware y software limitado, como una computadora de escritorio de gama baja.
3. El sistema debe ser fácil de usar para los empleados de la tienda, que pueden no tener una formación técnica avanzada.*/
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_PRODUCTOS 100
#define NOMBRE_ARCHIVO "inventario.txt"

char nombres[MAX_PRODUCTOS][50];
int cantidades[MAX_PRODUCTOS];
float precios[MAX_PRODUCTOS];
int num_productos = 0;

void cargar_inventario() {
    FILE* archivo = fopen(NOMBRE_ARCHIVO, "r");
    if (archivo == NULL) {
        perror("Error abriendo el archivo de inventario");
        exit(1);
    }
    while (fscanf(archivo, "%[^,],%d,%f\n", nombres[num_productos], &cantidades[num_productos], &precios[num_productos]) != EOF) {
        num_productos++;
    }
    fclose(archivo);
}

void guardar_inventario() {
    FILE* archivo = fopen(NOMBRE_ARCHIVO, "w");
    if (archivo == NULL) {
        perror("Error abriendo el archivo de inventario");
        exit(1);
    }
    for (int i = 0; i < num_productos; i++) {
        fprintf(archivo, "%s,%d,%.2f\n", nombres[i], cantidades[i], precios[i]);
    }
    fclose(archivo);
}

void pedir_nombre(int indice) {
    printf("Nombre del producto: ");
    scanf("%s", nombres[indice]);
}

void pedir_cantidad(int indice) {
    do {
        printf("Cantidad: ");
    } while (scanf("%d", &cantidades[indice]) != 1 || cantidades[indice] < 0);
}

void pedir_precio(int indice) {
    do {
        printf("Precio: ");
    } while (scanf("%f", &precios[indice]) != 1 || precios[indice] < 0);
}

void agregar_producto() {
    if (num_productos >= MAX_PRODUCTOS) {
        printf("Error: El inventario esta lleno.\n");
        return;
    }

    pedir_nombre(num_productos);
    pedir_cantidad(num_productos);
    pedir_precio(num_productos);

    num_productos++;
    guardar_inventario();
    printf("Producto agregado con exito.\n");
}

int buscar_producto_por_nombre(const char* nombre) {
    for (int i = 0; i < num_productos; i++) {
        if (strcmp(nombres[i], nombre) == 0) {
            return i;
        }
    }
    return -1;
}

void editar_producto_por_nombre() {
    char nombre[50];
    printf("Nombre del producto a editar: ");
    scanf("%s", nombre);
    int indice = buscar_producto_por_nombre(nombre);

    if (indice == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    pedir_nombre(indice);
    pedir_cantidad(indice);
    pedir_precio(indice);

    guardar_inventario();
    printf("Producto editado con exito.\n");
}

void eliminar_producto_por_nombre() {
    char nombre[50];
    printf("Nombre del producto a eliminar: ");
    scanf("%s", nombre);
    int indice = buscar_producto_por_nombre(nombre);

    if (indice == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    for (int i = indice; i < num_productos - 1; i++) {
        strcpy(nombres[i], nombres[i + 1]);
        cantidades[i] = cantidades[i + 1];
        precios[i] = precios[i + 1];
    }
    num_productos--;
    guardar_inventario();
    printf("Producto eliminado con exito.\n");
}

void listar_productos() {
    for (int i = 0; i < num_productos; i++) {
        printf("Producto %d: %s, Cantidad: %d, Precio: %.2f\n", i, nombres[i], cantidades[i], precios[i]);
    }
}

void menu_principal() {
    int opcion;
    printf("\n--               PROYECTO_INTEGRADOR                --\n");
    printf("\n-Camila Torres, Alejandro Paqui y Katherinn Hernandez-\n");
    printf("\n-- Sistema de Inventario para Tienda de Electronica --\n");
    printf("\n-- Menu Principal --\n");
    printf("1. Agregar producto\n");
    printf("2. Editar producto por nombre\n");
    printf("3. Eliminar producto por nombre\n");
    printf("4. Listar productos\n");
    printf("5. Salir\n");
    printf("Seleccione una opcion: ");
    if (scanf("%d", &opcion) != 1) {
        printf("Error: Entrada invalida. Debe ingresar un numero.\n");
        return;
    }

    switch (opcion) {
        case 1:
            agregar_producto();
            break;
        case 2:
            editar_producto_por_nombre();
            break;
        case 3:
            eliminar_producto_por_nombre();
            break;
        case 4:
            listar_productos();
            break;
        case 5:
            printf("\nSaliendo...\n");
            exit(0);
        default:
            printf("Error: Opcion invalida.\n");
    }
}

int main() {
    cargar_inventario();

    while (1) {
        menu_principal();
    }

    return 0;
}
