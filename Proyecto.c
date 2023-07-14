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

//Definición de constantes y variables globales:

/* 
 Se definen las constantes `MAX_PRODUCTOS` y `NOMBRE_ARCHIVO` que representan la capacidad máxima de almacenamiento del 
 inventario y el archivo de texto donde se persisten los datos, respectivamente. Además, se definen arrays globales 
 `nombres`, `cantidades` y `precios` que actúan como almacenamiento en memoria para el nombre, la cantidad y el precio de los 
 productos en el inventario. La variable global `num_productos` mantiene un conteo en tiempo real del número de productos en el inventario.
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_PRODUCTOS 100
#define NOMBRE_ARCHIVO "inventario.txt"

char nombres[MAX_PRODUCTOS][50];
int cantidades[MAX_PRODUCTOS];
float precios[MAX_PRODUCTOS];
int num_productos = 0;

//Funciones de carga y guardado del inventario:

/* 
 `cargar_inventario()` es responsable de leer el archivo de inventario y llenar los arrays correspondientes con los datos. 
 Utiliza `fscanf()` para leer las entradas del archivo. `guardar_inventario()`, por otro lado, escribe el estado actual del 
 inventario en el archivo utilizando `fprintf()`. Este último se llama cada vez que se hace una modificación en el inventario, 
 garantizando así la persistencia de los datos.
*/

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

//Funciones de pedido de información:

/* 
Las funciones `pedir_nombre()`, `pedir_cantidad()` y `pedir_precio()` son utilidades que interactúan con el usuario para obtener 
información del producto. Utilizan `printf()` para solicitar los datos y `scanf()` para leer la entrada del usuario.
*/

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

//Funciones de gestión del inventario:

/* 
 `agregar_producto()`, `editar_producto_por_nombre()` y `eliminar_producto_por_nombre()` son las operaciones CRUD principales. 
 `agregar_producto()` agrega un nuevo producto al final de los arrays de productos y aumenta el contador `num_productos`. 
 `editar_producto_por_nombre()` busca un producto y permite al usuario modificar sus datos. `eliminar_producto_por_nombre()` 
 busca un producto, lo elimina del inventario y reordena los arrays para mantener la continuidad.*/

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

//Función de búsqueda de productos:

/* 
`buscar_producto_por_nombre()` utiliza una búsqueda lineal simple para encontrar un producto en el inventario por su nombre. 
La función devuelve el índice del producto en el array si se encuentra, y -1 si no se encuentra.
*/


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

//Función de listado de productos:

/* 
`listar_productos()` recorre los arrays de productos y utiliza `printf()` para mostrar en la consola la información de cada producto.
*/

void listar_productos() {
    for (int i = 0; i < num_productos; i++) {
        printf("Producto %d: %s, Cantidad: %d, Precio: %.2f\n", i, nombres[i], cantidades[i], precios[i]);
    }
}

//Función del menú principal:

/* 
`menu_principal()` es una función de control de flujo que presenta al usuario un menú de opciones y dirige la ejecución del programa a 
la función correspondiente basándose en la entrada del usuario.
*/

void menu_principal() {
    int opcion;
    printf("\n--               PROYECTO_INTEGRADOR                --\n");
    printf("\n-Camila Torres, Alejandro Paqui y Katherinn Hernandez-\n");
    printf("\n-- Sistema de Inventario Electronica --\n");
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

//Función main:

/* 
 La función `main()` inicia cargando los datos del archivo de inventario en la memoria y luego entra en un bucle infinito,
  mostrando el menú principal y esperando la entrada del usuario hasta que se elige salir del programa.
*/


int main() {
    cargar_inventario();

    while (1) {
        menu_principal();
    }

    return 0;
}
