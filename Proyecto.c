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

#include <stdio.h>  // Biblioteca estándar de E/S en C. Se utiliza para funciones como printf y scanf.
#include <string.h> // Biblioteca de funciones de manejo de strings, como strcpy y strcmp.
#include <errno.h>  // Biblioteca para el manejo de errores, se utiliza para obtener información detallada sobre los errores que pueden ocurrir durante la ejecución.

#define MAX_PRODUCTOS 100  // Define una constante para el número máximo de productos que puede manejar el inventario.
#define NOMBRE_ARCHIVO "inventario.txt"  // Define una constante para el nombre del archivo donde se guardará el inventario.

char nombres[MAX_PRODUCTOS][50];  // Declara un array bidimensional de caracteres. Cada producto tiene un nombre que puede tener hasta 50 caracteres.
int cantidades[MAX_PRODUCTOS];  // Declara un array de enteros para almacenar las cantidades de cada producto.
float precios[MAX_PRODUCTOS];  // Declara un array de números flotantes para almacenar los precios de cada producto.
int num_productos = 0;  // Declara e inicializa un contador de productos. Se incrementará cada vez que se agregue un producto al inventario.

//Funciones de carga y guardado del inventario:

/* 
 `cargar_inventario()` es responsable de leer el archivo de inventario y llenar los arrays correspondientes con los datos. 
 Utiliza `fscanf()` para leer las entradas del archivo. `guardar_inventario()`, por otro lado, escribe el estado actual del 
 inventario en el archivo utilizando `fprintf()`. Este último se llama cada vez que se hace una modificación en el inventario, 
 garantizando así la persistencia de los datos.
*/

void cargar_inventario() { 
    FILE* archivo = fopen(NOMBRE_ARCHIVO, "r");  // Abre el archivo de inventario en modo de lectura. El archivo se especifica por la constante NOMBRE_ARCHIVO.
    if (archivo == NULL) {  // Si la apertura del archivo falla, fopen devuelve NULL. Aquí se comprueba ese caso.
        perror("Error abriendo el archivo de inventario");  // Muestra un mensaje de error detallado.
        exit(1);  // Termina el programa con un código de error.
    }
    // Lee del archivo una línea a la vez. El formato especificado en fscanf corresponde a un nombre de producto, seguido de una cantidad y un precio.
    // Los datos se almacenan en los arrays correspondientes. El bucle continúa hasta que se alcanza el final del archivo (EOF).
    while (fscanf(archivo, "%[^,],%d,%f\n", nombres[num_productos], &cantidades[num_productos], &precios[num_productos]) != EOF) {
        num_productos++;  // Aumenta el contador de productos después de cada producto leído exitosamente.
    }
    fclose(archivo);  // Cierra el archivo de inventario después de terminar la lectura.
}


//Funciones de pedido de información:

/* 
Las funciones `pedir_nombre()`, `pedir_cantidad()` y `pedir_precio()` son utilidades que interactúan con el usuario para obtener 
información del producto. Utilizan `printf()` para solicitar los datos y `scanf()` para leer la entrada del usuario.
*/
void guardar_inventario() {
    FILE* archivo = fopen(NOMBRE_ARCHIVO, "w");  // Abre el archivo de inventario en modo de escritura. Esto borrará el contenido existente.
    if (archivo == NULL) {  // Si la apertura del archivo falla, fopen devuelve NULL. Aquí se comprueba ese caso.
        perror("Error abriendo el archivo de inventario");  // Muestra un mensaje de error detallado.
        exit(1);  // Termina el programa con un código de error.
    }
    for (int i = 0; i < num_productos; i++) {  // Itera sobre cada producto en el inventario.
        fprintf(archivo, "%s,%d,%.2f\n", nombres[i], cantidades[i], precios[i]);  // Escribe los datos del producto en el archivo, en el formato específico.
    }
    fclose(archivo);  // Cierra el archivo después de terminar de escribir.
}

void pedir_nombre(int indice) {
    printf("Nombre del producto: ");  // Imprime un mensaje solicitando la entrada del usuario.
    scanf("%s", nombres[indice]);  // Lee la entrada del usuario como una cadena y la almacena en el array de nombres en el índice especificado.
}

void pedir_cantidad(int indice) {
    do {
        printf("Cantidad: ");  // Imprime un mensaje solicitando la entrada del usuario.
        // Lee la entrada del usuario como un entero y la almacena en el array de cantidades en el índice especificado.
        // Repite este proceso hasta que se recibe un número válido mayor o igual a cero.
    } while (scanf("%d", &cantidades[indice]) != 1 || cantidades[indice] < 0);
}

void pedir_precio(int indice) {
    do {
        printf("Precio: ");  // Imprime un mensaje solicitando la entrada del usuario.
        // Lee la entrada del usuario como un número flotante y la almacena en el array de precios en el índice especificado.
        // Repite este proceso hasta que se recibe un número válido mayor o igual a cero.
    } while (scanf("%f", &precios[indice]) != 1 || precios[indice] < 0);
}


//Funciones de gestión del inventario:

/* 
 `agregar_producto()`, `editar_producto_por_nombre()` y `eliminar_producto_por_nombre()` son las operaciones CRUD principales. 
 `agregar_producto()` agrega un nuevo producto al final de los arrays de productos y aumenta el contador `num_productos`. 
 `editar_producto_por_nombre()` busca un producto y permite al usuario modificar sus datos. `eliminar_producto_por_nombre()` 
 busca un producto, lo elimina del inventario y reordena los arrays para mantener la continuidad.*/

void agregar_producto() {
    // Comprueba si el número de productos en el inventario ha alcanzado el límite establecido por MAX_PRODUCTOS.
    // Si se ha alcanzado el límite, imprime un mensaje de error y termina la función.
    if (num_productos >= MAX_PRODUCTOS) {
        printf("Error: El inventario esta lleno.\n");
        return;
    }

    // Llama a las funciones para pedir al usuario que ingrese el nombre, la cantidad y el precio del producto.
    // Las funciones almacenarán la información ingresada directamente en los arrays correspondientes en el índice num_productos.
    pedir_nombre(num_productos);
    pedir_cantidad(num_productos);
    pedir_precio(num_productos);

    // Una vez que se ha ingresado toda la información del producto, incrementa num_productos para reflejar el nuevo total de productos en el inventario.
    num_productos++;
    
    // Llama a la función para guardar el estado actual del inventario en el archivo.
    guardar_inventario();
    
    // Imprime un mensaje de confirmación para informar al usuario que el producto ha sido agregado con éxito.
    printf("Producto agregado con exito.\n");
}

//Función de búsqueda de productos:

/* 
`buscar_producto_por_nombre()` utiliza una búsqueda lineal simple para encontrar un producto en el inventario por su nombre. 
La función devuelve el índice del producto en el array si se encuentra, y -1 si no se encuentra.
*/


int buscar_producto_por_nombre(const char* nombre) {
    // Recorre todos los productos existentes en el inventario.
    for (int i = 0; i < num_productos; i++) {
        // Compara el nombre del producto en el índice actual con el nombre proporcionado.
        // Si coinciden (strcmp retorna 0), devuelve el índice del producto.
        if (strcmp(nombres[i], nombre) == 0) {
            return i;
        }
    }
    // Si el producto no se encuentra en el inventario, devuelve -1.
    return -1;
}


void editar_producto_por_nombre() {
    char nombre[50];
    // Solicita al usuario que ingrese el nombre del producto que desea editar.
    printf("Nombre del producto a editar: ");
    scanf("%s", nombre);

    // Busca el producto por el nombre ingresado.
    int indice = buscar_producto_por_nombre(nombre);

    // Si el producto no se encuentra (índice es -1), imprime un mensaje de error y termina la función.
    if (indice == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    // Si el producto se encuentra, solicita al usuario que ingrese la nueva información del producto.
    pedir_nombre(indice);
    pedir_cantidad(indice);
    pedir_precio(indice);

    // Guarda el inventario actualizado en el archivo.
    guardar_inventario();
    
    // Imprime un mensaje de confirmación para informar al usuario que el producto ha sido editado con éxito.
    printf("Producto editado con exito.\n");
}


void eliminar_producto_por_nombre() {
    char nombre[50];
    // Solicita al usuario que ingrese el nombre del producto que desea eliminar.
    printf("Nombre del producto a eliminar: ");
    scanf("%s", nombre);

    // Busca el producto por el nombre ingresado.
    int indice = buscar_producto_por_nombre(nombre);

    // Si el producto no se encuentra (índice es -1), imprime un mensaje de error y termina la función.
    if (indice == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    // Si el producto se encuentra, recorre todos los productos que vienen después de él en el inventario.
    for (int i = indice; i < num_productos - 1; i++) {
        // Desplaza cada producto una posición hacia atrás en el inventario (es decir, sobre el producto que se va a eliminar).
        strcpy(nombres[i], nombres[i + 1]);
        cantidades[i] = cantidades[i + 1];
        precios[i] = precios[i + 1];
    }
    // Reduce el número total de productos en el inventario en uno, efectivamente eliminando el último producto,
    // que ahora es una copia del penúltimo producto.
    num_productos--;

    // Guarda el inventario actualizado en el archivo.
    guardar_inventario();

    // Imprime un mensaje de confirmación para informar al usuario que el producto ha sido eliminado con éxito.
    printf("Producto eliminado con exito.\n");
}

//Función de listado de productos:

/* 
`listar_productos()` recorre los arrays de productos y utiliza `printf()` para mostrar en la consola la información de cada producto.
*/

void listar_productos() {
    // Recorre todos los productos en el inventario.
    for (int i = 0; i < num_productos; i++) {
        // Imprime la información de cada producto, incluyendo su índice,
        // nombre, cantidad en stock y precio.
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
    // Imprime el menú principal en la consola.
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
    // Lee la entrada del usuario. Si la entrada no es un número, muestra un mensaje de error y regresa.
    if (scanf("%d", &opcion) != 1) {
        printf("Error: Entrada invalida. Debe ingresar un numero.\n");
        return;
    }

    // Ejecuta la acción correspondiente en función de la entrada del usuario.
    switch (opcion) {
        case 1:  // Si el usuario selecciona "1", agrega un producto.
            agregar_producto();
            break;
        case 2:  // Si el usuario selecciona "2", edita un producto por su nombre.
            editar_producto_por_nombre();
            break;
        case 3:  // Si el usuario selecciona "3", elimina un producto por su nombre.
            eliminar_producto_por_nombre();
            break;
        case 4:  // Si el usuario selecciona "4", lista todos los productos.
            listar_productos();
            break;
        case 5:  // Si el usuario selecciona "5", termina el programa.
            printf("\nSaliendo...\n");
            exit(0);
        default:  // Si el usuario selecciona cualquier otra opción, muestra un mensaje de error.
            printf("Error: Opcion invalida.\n");
    }
}

//Función main:

/* 
 La función `main()` inicia cargando los datos del archivo de inventario en la memoria y luego entra en un bucle infinito,
  mostrando el menú principal y esperando la entrada del usuario hasta que se elige salir del programa.
*/


int main() {
    // Carga el inventario desde el archivo de texto al iniciar el programa.
    cargar_inventario();

    // Entra en un ciclo infinito, mostrando el menú principal y realizando las operaciones correspondientes.
    // El programa sólo se detendrá cuando el usuario elija la opción "Salir" en el menú principal.
    while (1) {
        menu_principal();
    }

    // Retorna 0 al sistema operativo. En la mayoría de los sistemas, un valor de retorno de 0 desde la función main indica que el programa se ejecutó con éxito.
    return 0;
}
