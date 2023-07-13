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

/*Definición de estructuras y enumeración:

Se definen dos estructuras: Producto y Usuario, que representan un producto y un usuario respectivamente. 
La estructura Producto tiene campos para el nombre, la cantidad y el precio del producto. 
La estructura Usuario tiene campos para el nombre y el tipo de usuario.
Se define una enumeración TipoUsuario que representa los tipos posibles de usuario: ADMINISTRADOR, EMPLEADO y CONTADOR.*/
typedef struct {
    char nombre[50];
    int cantidad;
    float precio;
} Producto;

typedef enum {
    ADMINISTRADOR,
    EMPLEADO,
    CONTADOR
} TipoUsuario;

typedef struct {
    char nombre[50];
    TipoUsuario tipo;
} Usuario;

/*Se declaran variables globales como usuarios, usuario_actual, inventario y 
num_productos, que son utilizadas en diferentes partes del programa.*/
Usuario usuarios[] = {
    {"admin", ADMINISTRADOR},
    {"empleado", EMPLEADO},
    {"contador", CONTADOR}
};

#define NUM_USUARIOS (sizeof(usuarios) / sizeof(Usuario))

Usuario* usuario_actual = NULL;

Producto inventario[MAX_PRODUCTOS];
int num_productos = 0;

/*La función cargar_inventario se encarga de cargar los datos del inventario desde el archivo "inventario.txt" 
al arreglo inventario. Utiliza la función fopen para abrir el archivo en modo lectura y fscanf para leer los datos.
La función guardar_inventario guarda los datos del inventario en el archivo "inventario.txt". 
Utiliza la función fopen para abrir el archivo en modo escritura y fprintf para escribir los datos.*/
// Cargar el inventario desde el archivo
void cargar_inventario() {
    FILE* archivo = fopen(NOMBRE_ARCHIVO, "r");
    if (archivo == NULL) {
        if (errno == ENOENT) {
            // El archivo no existe, lo cual esta bien porque estamos iniciando el programa
            return;
        } else {
            // Otro error ocurrio
            perror("Error abriendo el archivo de inventario");
            exit(1);
        }
    }
    while (fscanf(archivo, "%[^,],%d,%f\n", inventario[num_productos].nombre, &inventario[num_productos].cantidad, &inventario[num_productos].precio) != EOF) {
        num_productos++;
    }
    fclose(archivo);
}
// Guardar el inventario en el archivo
void guardar_inventario() {
    FILE* archivo = fopen(NOMBRE_ARCHIVO, "w");
    if (archivo == NULL) {
        perror("Error abriendo el archivo de inventario");
        exit(1);
    }
    for (int i = 0; i < num_productos; i++) {
        fprintf(archivo, "%s,%d,%.2f\n", inventario[i].nombre, inventario[i].cantidad, inventario[i].precio);
    }
    fclose(archivo);
}
/*Las funciones agregar_producto, editar_producto y eliminar_producto permiten agregar, editar y eliminar productos respectivamente. 
Solicitan al usuario ingresar los detalles del producto como nombre, cantidad y precio, validan las entradas y realizan las operaciones 
correspondientes en el arreglo inventario. Además, llaman a la función guardar_inventario para guardar los cambios en el archivo.*/
// Agregar un producto al inventario
void agregar_producto() {
    if (num_productos >= MAX_PRODUCTOS) {
        printf("Error: El inventario esta lleno.\n");
        return;
    }
    printf("Nombre del producto: ");
    while (scanf("%s", inventario[num_productos].nombre) != 1) {
        printf("Error: Entrada invalida. Intente nuevamente.\n");
        while (getchar() != '\n');  // Limpiar el buffer de entrada
        printf("Nombre del producto: ");
    }
    printf("Cantidad: ");
    while (scanf("%d", &inventario[num_productos].cantidad) != 1 || inventario[num_productos].cantidad < 0) {
        printf("Error: Entrada invalida. La cantidad debe ser un numero entero no negativo. Intente nuevamente.\n");
        while (getchar() != '\n');  // Limpiar el buffer de entrada
        printf("Cantidad: ");
    }
    printf("Precio: ");
    while (scanf("%f", &inventario[num_productos].precio) != 1 || inventario[num_productos].precio < 0) {
        printf("Error: Entrada invalida. El precio debe ser un numero no negativo. Intente nuevamente.\n");
        while (getchar() != '\n');  // Limpiar el buffer de entrada
        printf("Precio: ");
    }
    num_productos++;
    guardar_inventario();
    printf("Producto agregado con exito.\n");
}
// Editar un producto existente en el inventario
void editar_producto() {
    int indice;
    printf("Indice del producto a editar: ");
    while (scanf("%d", &indice) != 1 || indice < 0 || indice >= num_productos) {
        printf("Error: Entrada invalida. El indice debe ser un numero entre 0 y %d. Intente nuevamente.\n", num_productos - 1);
        while (getchar() != '\n');  // Limpiar el buffer de entrada
        printf("Indice del producto a editar: ");
    }
    printf("Nuevo nombre del producto: ");
    while (scanf("%s", inventario[indice].nombre) != 1) {
        printf("Error: Entrada invalida. Intente nuevamente.\n");
        while (getchar() != '\n');  // Limpiar el buffer de entrada
        printf("Nuevo nombre del producto: ");
    }
    printf("Nueva cantidad: ");
    while (scanf("%d", &inventario[indice].cantidad) != 1 || inventario[indice].cantidad < 0) {
        printf("Error: Entrada invalida. La cantidad debe ser un numero entero no negativo. Intente nuevamente.\n");
        while (getchar() != '\n');  // Limpiar el buffer de entrada
        printf("Nueva cantidad: ");
    }
    printf("Nuevo precio: ");
    while (scanf("%f", &inventario[indice].precio) != 1 || inventario[indice].precio < 0) {
        printf("Error: Entrada invalida. El precio debe ser un numero no negativo. Intente nuevamente.\n");
        while (getchar() != '\n');  // Limpiar el buffer de entrada
        printf("Nuevo precio: ");
    }
    guardar_inventario();
    printf("Producto editado con exito.\n");
}
// Eliminar un producto del inventario
void eliminar_producto() {
    int indice;
    printf("Indice del producto a eliminar: ");
    if (scanf("%d", &indice) != 1 || indice < 0 || indice >= num_productos) {
        printf("Error: Entrada invalida. El indice debe ser un numero entre 0 y %d.\n", num_productos - 1);
        while (getchar() != '\n');  // Limpiar el buffer de entrada
        return;
    }
    for (int i = indice; i < num_productos - 1; i++) {
        inventario[i] = inventario[i + 1];
    }
    num_productos--;
    guardar_inventario();
    printf("Producto eliminado con exito.\n");
}
/*La función listar_productos muestra la lista de productos en el inventario. 
Recorre el arreglo inventario e imprime los detalles de cada producto en el formato especificado.*/

// Listar todos los productos en el inventario
void listar_productos() {
    for (int i = 0; i < num_productos; i++) {
        printf("Producto %d: %s, Cantidad: %d, Precio: %.2f\n", i, inventario[i].nombre, inventario[i].cantidad, inventario[i].precio);
    }
}
/*La función iniciar_sesion solicita al usuario ingresar su nombre y valida el inicio de sesión comparando el nombre con los usuarios predefinidos en el arreglo usuarios. 
Retorna un puntero al usuario actual o NULL si el inicio de sesión es incorrecto.
La función menu_principal muestra el menú principal y maneja las opciones seleccionadas por el usuario. 
Dependiendo de la opción seleccionada, llama a las funciones correspondientes para agregar, editar, eliminar o listar productos.*/
// Iniciar sesión de usuario
Usuario* iniciar_sesion() {
    char nombre[50];
    printf("\n-- Usuarios 1.admin 2.empleado 3.contador --\n");
    printf("\n-- Inicio de sesion --\n");
    printf("Nombre de usuario: ");
    scanf("%s", nombre);
    for (int i = 0; i < NUM_USUARIOS; i++) {
        if (strcmp(nombre, usuarios[i].nombre) == 0) {
            printf("Inicio de sesion exitoso.\n");
            return &usuarios[i];
        }
    }
    printf("Error: Nombre de usuario incorrecto.\n");
    return NULL;
}
// Menú principal del programa
void menu_principal() {
    int opcion;
    while (1) {
        printf("\n--    PROYECTO_INTEGRADOR    --\n");
        printf("\n-Camila Torres, Alejandro Paqui Katherinn Hernandez-\n");
        printf("\n-- Menu Principal --\n");
        printf("1. Agregar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Listar productos\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            printf("Error: Entrada invalida. Debe ingresar un numero.\n");
            while (getchar() != '\n');  // Limpiar el buffer de entrada
            continue;
        }

        switch (opcion) {
            case 1:
                agregar_producto();
                break;
            case 2:
                editar_producto();
                break;
            case 3:
                eliminar_producto();
                break;
            case 4:
                listar_productos();
                break;
            case 5:
                printf("\nSaliendo...\n");
                return;
            default:
                printf("Error: Opcion invalida.\n");
        }
    }
}
/*La función main es la función principal del programa. 
Primero se llama a cargar_inventario para cargar los datos del inventario desde el archivo. Luego, en un bucle infinito, se llama a iniciar_sesion para que el usuario inicie sesión.
Si el inicio de sesión es exitoso, se llama a menu_principal para mostrar el menú principal. El bucle continúa hasta que el programa se cierre.*/
int main() {
    cargar_inventario();

    while (1) {
        usuario_actual = iniciar_sesion();
        if (usuario_actual != NULL) {
            menu_principal();
        }
    }
}
