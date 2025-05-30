#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ===== COMENTARIOS ===== //
/*
¿QUÉ QUEREMOS HACER?


*/

// ===== Se definen las estructuras del proyecto =====//

typedef struct { //estructura del cliente
	char nombre[30];
	char apellido[30];
	int cedula;
	int edad;
	int telefono;
	
} Cliente;

typedef struct{ //estructura de la fecha
	int dia;
	int mes;
	int anyo;
} Fecha;

typedef struct{ //estructura del libro
	int codigo;
	char autorLibro[30];
	char titulo[30];
	int anio;
	float precio;
	int cantidad; // cantidad de libros de ese tipo para determinar si está agotado.
} Libro;

typedef struct{ //estructura anidada la cual usamos para la compra 
	int numeroCompra;
	Cliente cliente;
	Libro libros[10];
	Fecha fecha;
	int metodoDePago;
} Compra;

typedef struct{ //segunda estructura anidada para el prestamo, aun no terminada no se como integra la fecha de devolucion AJAJJA
	int numeroPrestamo;
	Cliente cliente;
	Libro libros[3];
	Fecha fechaPrestamo;
	Fecha fechaLimite;
	Fecha fechaDevolucion; 
	int estado;
} Prestamo;

// ===== END Estructuras ===== //

// ===== Se definen Macros ===== //
#define SALTARLINEAS(n) {int imacro; for(imacro=0;imacro<(n);imacro++){printf("\n");}}

# define SONIDOERROR printf("\7");


// ===== END Macros ===== //

// ===== Se definen Enums ===== //

typedef enum{
	Prestamos = 1, Compras
} TipoTransaccion;

typedef enum{
	Efectivo = 1, Tarjeta
} MetodoDePago;

typedef enum{
	Devuelto = 1, Prestado
} EstadoPrestamo;

// ===== END Enums ===== //

// ===== CRUD CLIENTES ===== //
Cliente crearCliente(int nuevoCliente){
	Cliente cliente;
	cliente.cedula = nuevoCliente;
	printf("Ingrese el nombre: ");
	scanf(" %s", cliente.nombre);
	printf("Ingrese el apellido: ");
	scanf(" %s", cliente.apellido);
	printf("Ingrese el telefono: ");
	scanf("%d", &cliente.telefono);
	printf("Ingrese la edad: ");
	scanf("%d", &cliente.edad);    
    return cliente;
}

void mostrarCliente(Cliente cliente){
    // code //
	printf("Cedula: %d \n", cliente.cedula);
	printf("Nombre completo: %s %s \n", cliente.nombre, cliente.apellido);
	printf("Telefono: %d \n", cliente.telefono);
	printf("Edad: %d \n", cliente.edad);
}

Cliente modificarCliente(Cliente cliente){
    // con un switch y capturar la opción le pregunta al usuario que dato quiere modificar.
	int opc;
	printf("¿Que dato desea modificar? \n");
	printf("1. Nombre \n");
	printf("2. Apellido \n");
	printf("3. Telefono \n");
	printf("4. Edad \n");
	scanf("%d", &opc);
	switch (opc)
	{
	case 1:
		printf("Ingrese el nombre: ");
    	scanf(" %s", cliente.nombre);
		break;
	case 2:
		printf("Ingrese el apellido: ");
    	scanf(" %s", cliente.apellido);
		break;
	case 3:
		printf("Ingrese el telefono: ");
    	scanf("%d", &cliente.telefono);
		break;
	case 4:
		printf("Ingrese la edad: ");
    	scanf("%d", &cliente.edad);
		break;
	default:
		break;
	}

    return cliente;
}

Cliente eliminarCliente(){
    Cliente cliente;
	return cliente;
}

 // ===== END CRUD CLIENTES ===== //


 // ===== CRUD FECHA ===== //

 Fecha crearFecha(){
	Fecha fecha;
	printf("ingrese el dia: ");
	scanf("%d", &fecha.dia);
	printf("ingrese el mes: ");
	scanf("%d", &fecha.mes);
	printf("ingrese el año: ");
	scanf("%d", &fecha.anyo);

	return fecha;
}

void mostrarFecha(Fecha fecha){
      printf("%d/%d/%d \n", fecha.dia, fecha.mes, fecha.anyo);
}

Fecha modificarFecha(Fecha fecha){
    // con un switch y capturar la opción le pregunta al usuario que dato quiere modificar.
    int opc;
	printf("Que dato desea modificar? \n");
	printf("1.Dia \n");
	printf("2.Mes \n");
	printf("3.Año \n");
	scanf("%d", &opc);
	switch (opc)
	{
		case 1:
			printf("ingrese su dia: ");
			scanf("%d", &fecha.dia);
			break;	
		case 2:
			printf("ingrese su mes: ");
			scanf("%d", &fecha.mes);
			break;	
		case 3:
			printf("ingrese su año: ");
			scanf("%d", &fecha.anyo);
			break;
		default:
			printf("opcion no encontrada \n");
			break;
	}
	return fecha;
}

Fecha eliminarFecha(){
    Fecha fecha;
	return fecha;
}

// ===== END CRUD FECHA ===== //

// ===== CRUD LIBRO ===== //
Libro crearLibro(int nuevoLibro){
    Libro libro;
    libro.codigo = nuevoLibro;
    printf("Ingrese el autor: ");
    scanf(" %s", libro.autorLibro);
    printf("Ingrese el titulo: ");
    scanf(" %s", libro.titulo);
    printf("Ingrese el año: ");
    scanf("%d", &libro.anio);
	printf("Ingrese el precio: ");
    scanf("%f", &libro.precio);
    printf("Ingrese la cantidad: ");
    scanf("%d", &libro.cantidad);
    return libro;
}
// en esta funcion lo mostramos
void mostrarLibro(Libro libro){
	    printf(" Codigo: %d\n Autor del libro: %s\n Titulo: %s\n A�o: %d\n Precio: %.2f\n Cantidad: %d \n", libro.codigo, libro.autorLibro,libro.titulo,libro.anio, libro.precio, libro.cantidad);
}

// aca implementamos un switch para las opciones de modificar libro 
Libro modificarLibro(Libro libro){
	int opcion;
	opcion = 1;
	while(opcion !=0){
		menu();
	
		scanf("%d", &opcion);
		
		switch(opcion){
			case 1:
				printf("ingrese el nuevo autor por favor:");
				scanf(" %s", libro.autorLibro);
				break;
			case 2:
				printf("ingrese el nuevo titulo por favor:");
				scanf(" %s", libro.titulo);
				break;
			case 3:
				printf("ingrese el nuevo año por favor:");
				scanf("%d", &libro.anio);
				break;	
			case 4:
				printf("ingrese el nuevo precio por favor:");
				scanf("%f", &libro.precio);
				break;	
			case 5:
				printf("ingrese la nueva cantidad por favor:");
				scanf("%d", &libro.cantidad);
				break;
            default:
                printf("¡La opcion no es valida!");
                break;
		}
	}
	return libro;
}
// funcion para eliminar libro
Libro eliminarLibro(){
    Libro libro;
    return libro;
}

//ademas de hacer el switch para modificar libro, obviamente necesita un menu para llamarlo y ver la opcion que digite el usuario
//menu
void menu(){
    printf("¿Que dato sobre el libro desea modificar?\n");
    printf("1. Cambiar el  autor del libro\n");
    printf("2. Cambiar el titulo\n");
    printf("3. Cambiar el a�o de publicaci�n\n");
    printf("4. cambiar el precio\n");
    printf("5. cambiar la cantidad\n\n");
    printf("0. Salir del programa\n"); 
    printf("Digite un opcion: ");
}
// ===== END CRUD LIBRO ===== //

// ===== CRUD COMPRA ===== //
Compra crearCompra(){
	Compra compra;
	printf("ingrese el numero de compra");
	scanf("%d", &compra.numeroCompra);
	// compra.cliente = crearCliente();
	// compra.libros[100] = crearLibro();
	compra.fecha = crearFecha();
    printf("ingrese su metodo de pago");
    printf("1.Efectivo");
    printf("2.Tarjeta");
    scanf("%d", &compra.metodoDePago);
	return compra;
}

void mostrarCompra(Compra compra){
      printf("%d", compra.numeroCompra);
      mostrarCliente(compra.cliente);
	  mostrarLibro(compra.libros[1]);
	  mostrarFecha(compra.fecha);
}

Compra modificarCompra(Compra compra){
    // con un switch y capturar la opción le pregunta al usuario que dato quiere modificar.
    int opc;
	printf("¿que dato desea modificar?");
	printf("1.Cliente");
	printf("2.Libro");
	printf("3.Fecha");
    printf("4.Metodo de pago");
	scanf("%d", &opc);
	switch (opc)
	{
		case 1:
			compra.cliente=modificarCliente(compra.cliente);
			break;	
		case 2:
			compra.libros[1]=modificarLibro(compra.libros[1]);
			break;	
		case 3:
			compra.fecha=modificarFecha(compra.fecha);
			break;
		case 4:
			printf("Ingrese el nuevo método de pago");
			scanf("%d", &compra.metodoDePago);
		default:
			printf("opcion no encontrada");
			break;
	}
	return compra;
}

Compra eliminarCompra(){
    Compra compra;
	return compra;
}
// ===== END CRUD COMPRA ===== //

// ===== CRUD PRESTAMO ===== //
Prestamo crearPrestamo(){
	Prestamo prestamo;
	printf("ingrese el numero de compra");
	scanf("%d", &prestamo.numeroPrestamo);
	// prestamo.cliente = crearCliente();
	// prestamo.libros[100] = crearLibro();
	prestamo.fechaPrestamo = crearFecha();
	prestamo.fechaLimite = crearFecha();
	prestamo.fechaDevolucion = crearFecha();
    printf("Ingrese el estado del prestamo");
	scanf("%d", &prestamo.estado);
	return prestamo;
	
}

void mostrarPrestamo(Prestamo prestamo){
      printf("%d", prestamo.numeroPrestamo);
      mostrarCliente(prestamo.cliente);
	  mostrarLibro(prestamo.libros[1]);
	  mostrarFecha(prestamo.fechaPrestamo);
	  mostrarFecha(prestamo.fechaLimite);
	  mostrarFecha(prestamo.fechaDevolucion);
}

Prestamo modificarPrestamo(Prestamo prestamo){
    // con un switch y capturar la opción le pregunta al usuario que dato quiere modificar.
    int opc;
	printf("¿que dato desea modificar?");
	printf("1.Cliente");
	printf("2.Libro");
	printf("3.Fecha Prestamo");
    printf("4.Fecha Limite");
    printf("5.Fecha Devolución");
    printf("6.Estado");
	scanf("%d", &opc);
	switch (opc)
	{
		case 1:
			prestamo.cliente=modificarCliente(prestamo.cliente);
			break;	
		case 2:
			prestamo.libros[1]=modificarLibro(prestamo.libros[1]);
			break;	
		case 3:
			prestamo.fechaPrestamo=modificarFecha(prestamo.fechaPrestamo);
			break;
		case 4:
			prestamo.fechaLimite=modificarFecha(prestamo.fechaLimite);
			break;
		case 5:
			prestamo.fechaDevolucion=modificarFecha(prestamo.fechaDevolucion);
			break;
		case 6: 
			printf("Ingrese el estado del prestamo");
			scanf("%d", &prestamo.estado);
		default:
			printf("opcion no encontrada");
			break;
	}
	return prestamo;
}

Prestamo eliminarPrestamo(){
    Prestamo prestamo;
	return prestamo;
}
// ===== END CRUD PRESTAMO ===== //


// ===== MANEJO DE ARCHIVOS CLIENTES ===== //
void guardarArchivoClientes(Cliente *vector, int tamano){
    FILE *archivoClientes = fopen("clientes.bat","wb");
    if (archivoClientes == NULL){
        printf("Error al abrir el archivo\n");
    } else {
        fwrite(vector, sizeof(Cliente), tamano, archivoClientes);
    }
    fclose(archivoClientes);
}

int leerArchivoCliente(Cliente *vector){
    FILE *archivoClientes = fopen("clientes.bat","rb");
    int cont = 0;
    if (archivoClientes == NULL){
        guardarArchivoClientes(vector, 0);
    } else {
        while(fread(&vector[cont], sizeof(Cliente), 1, archivoClientes)){
            cont++;
        }
    }
    return cont; // Retorna el cont para saber cual fue la ultima posicion llena del vector
}

void menuManejoClientes(Cliente clientes[], int cantidadClientes){
	int opcion;
	int clienteAccion;
    while(opcion != 5) {
        printf("\n--- MENU CLIENTES ---\n");
        printf("1. Crear cliente\n");
        printf("2. Mostrar clientes\n");
        printf("3. Modificar cliente\n");
        printf("4. Eliminar cliente\n");
        printf("5. Guardar y salir\n");
        printf("Elija una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidadClientes < 100) {
					printf("Ingrese la cedula: ");
					scanf("%d", &clienteAccion);
					if(verificarCliente(clienteAccion, clientes, cantidadClientes)){
						clientes[cantidadClientes] = crearCliente(clienteAccion);
                    	cantidadClientes++;
						guardarArchivoClientes(clientes, cantidadClientes);
					}    
                } else {
                    printf("No hay más espacio para clientes.\n");
                }
                break;
            case 2:
                for (int i = 0; i < cantidadClientes; i++) {
                    printf("\nCliente #%d:\n", i+1);
                    mostrarCliente(clientes[i]);
                }
                break;
            case 3:
                printf("Ingrese el número del cliente a modificar (1 a %d): ", cantidadClientes);
                int pos;
                scanf("%d", &pos);
                if (pos >= 1 && pos <= cantidadClientes) {
                    clientes[pos - 1] = modificarCliente(clientes[pos - 1]);
                } else {
                    printf("Índice inválido.\n");
                }
                break;
			case 4:
				printf("Ingrese la cedula a eliminar: ");
				scanf("%d", &clienteAccion);
				cantidadClientes = eliminarClienteVector(clientes, cantidadClientes, clienteAccion);
				break;
            case 5:
                guardarArchivoClientes(clientes, cantidadClientes);
                printf("Clientes guardados. ¡Hasta luego!\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    }
}
// ===== END MANEJO ARCHIVO CLIENTES ===== //

// eliminar un cliente

int eliminarClienteVector(Cliente clientes[], int cantidadClientes, int clienteAccion){
	int found = 0;
	for(int i = 0; i < cantidadClientes; i++){
		if (clientes[i].cedula == clienteAccion)
		{
			for(int j = i; j < cantidadClientes; j++){
				clientes[j] = clientes[j+1];
			}
			cantidadClientes--;
			found = 1;
			break;
		}
	}

	if(found){
		printf("Cliente Eliminado con exito! \n");
	} else {
		printf("No se encontró un usuario con ese numero de cedula. \n");
	}

	return cantidadClientes;
}

// ===== MANEJO DE ARCHIVOS LIBRO ===== //
void guardarArchivoLibros(Libro *vector, int tamano){
    FILE *archivoLibro = fopen("libros.bat","wb");
    if (archivoLibro == NULL){
        printf("Error al abrir el archivo\n");
    } else {
        fwrite(vector, sizeof(Libro), tamano, archivoLibro);
    }
    fclose(archivoLibro);
}

int leerArchivoLibros(Libro *vector){
    FILE *archivoLibro = fopen("libros.bat","rb");
    int cont = 0;
    if (archivoLibro == NULL){
		guardarArchivoLibros(vector, 0);
    } else {
        while(fread(&vector[cont], sizeof(Libro), 1, archivoLibro)){
            cont++;
        }
    }
    return cont; // Retorna el cont para saber cual fue la ultima posicion llena del vector
}

void menuManejoLibro(Libro libros[], int cantidadLibros){
	int opcion;
    while(opcion != 4) {
        printf("\n--- MENU LIBROS ---\n");
        printf("1. Crear libros\n");
        printf("2. Mostrar libros\n");
        printf("3. Modificar libros\n");
        printf("4. Guardar y salir\n");
        printf("Elija una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidadLibros < 100) {
					libros[cantidadLibros] = crearLibro(cantidadLibros+1);
                    cantidadLibros++;
					guardarArchivoLibros(libros, cantidadLibros);
					
                } else {
                    printf("No hay más espacio para libros.\n");
                }
                break;
            case 2:
                for (int i = 0; i < cantidadLibros; i++) {
                    printf("\nLibro #%d:\n", i+1);
                    mostrarLibro(libros[i]);
                }
                break;
            case 3:
                printf("Ingrese el número del libro a modificar (1 a %d): ", cantidadLibros);
                int pos;
                scanf("%d", &pos);
                if (pos >= 1 && pos <= cantidadLibros) {
                    libros[pos - 1] = modificarLibro(libros[pos - 1]);
                } else {
                    printf("Índice inválido.\n");
                }
                break;
            case 4:
                guardarArchivoLibros(libros, cantidadLibros);
                printf("Libros guardados. ¡Hasta luego!\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    }
}
// ===== END MANEJO ARCHIVO LIBRO ===== //

// ===== MANEJO DE ARCHIVO DE COMPRAS ===== //
void guardarArchivoCompra(Compra *vector, int tamano){
    FILE *archivoCompra = fopen("compra.bat","wb");
    if (archivoCompra == NULL){
        printf("Error al abrir el archivo\n");
    } else {
        fwrite(vector, sizeof(Cliente), tamano, archivoCompra);
    }
    fclose(archivoCompra);
}

int leerArchivoCompra(Compra *vector){
    FILE *archivoCompra = fopen("compra.bat","rb");
    int cont = 0;
    if (archivoCompra == NULL){
        guardarArchivoCompra(vector, 0);
    } else {
        while(fread(&vector[cont], sizeof(Cliente), 1, archivoCompra)){
            cont++;
        }
    }
    return cont; // Retorna el cont para saber cual fue la ultima posicion llena del vector
}

void menuManejoCompra(Compra compras[], int cantidadCompras){
	int opcion;
    while(opcion != 4) {
        printf("\n--- MENU COMPRAS ---\n");
        printf("1. Crear compra\n");
        printf("2. Mostrar compras\n");
        printf("3. Modificar compras\n");
        printf("4. Guardar y salir\n");
        printf("Elija una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidadCompras < 100) {
                    compras[cantidadCompras] = crearCompra();
                    cantidadCompras++;
					guardarArchivoCompra(compras, cantidadCompras);
                } else {
                    printf("No hay más espacio para compras.\n");
                }
                break;
            case 2:
                for (int i = 0; i < cantidadCompras; i++) {
                    printf("\ncompra #%d:\n", i+1);
                    mostrarCompra(compras[i]);
                }
                break;
            case 3:
                printf("Ingrese el número de la compra a modificar (1 a %d): ", cantidadCompras);
                int pos;
                scanf("%d", &pos);
                if (pos >= 1 && pos <= cantidadCompras) {
                    compras[pos - 1] = modificarCompra(compras[pos - 1]);
                } else {
                    printf("Índice inválido.\n");
                }
                break;
            case 4:
                guardarArchivoCompra(compras, cantidadCompras);
                printf("compras guardados. ¡Hasta luego!\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    }
}
// ===== END MANEJO ARCHIVO COMPRAS ===== //


// ===== MANEJO DE ARCHIVO DE PRESTAMO ===== //
void guardarArchivoPrestamo(Prestamo *vector, int tamano){
    FILE *archivoPrestamo = fopen("prestamo.bat","wb");
    if (archivoPrestamo == NULL){
        printf("Error al abrir el archivo\n");
    } else {
        fwrite(vector, sizeof(Prestamo), tamano, archivoPrestamo);
    }
    fclose(archivoPrestamo);
}

int leerArchivoPrestamo(Prestamo *vector){
    FILE *archivoPrestamo = fopen("prestamo.bat","rb");
    int cont = 0;
    if (archivoPrestamo == NULL){
        guardarArchivoPrestamo(vector, 0);
    } else {
        while(fread(&vector[cont], sizeof(Prestamo), 1, archivoPrestamo)){
            cont++;
        }
    }
    return cont; // Retorna el cont para saber cual fue la ultima posicion llena del vector
}

void menuManejoPrestamo(Prestamo prestamo[], int cantidadPrestamo){
	int opcion;
    while(opcion != 4) {
        printf("\n--- MENU PRESTAMOS ---\n");
        printf("1. Crear prestamo\n");
        printf("2. Mostrar prestamo\n");
        printf("3. Modificar prestamo\n");
        printf("4. Guardar y salir\n");
        printf("Elija una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidadPrestamo < 100) {
                    prestamo[cantidadPrestamo] = crearPrestamo();
                    cantidadPrestamo++;
					guardarArchivoPrestamo(prestamo, cantidadPrestamo);
                } else {
                    printf("No hay más espacio para prestamos.\n");
                }
                break;
            case 2:
                for (int i = 0; i < cantidadPrestamo; i++) {
                    printf("\nPrestamo #%d:\n", i+1);
                    mostrarPrestamo(prestamo[i]);
                }
                break;
            case 3:
                printf("Ingrese el número del prestamo a modificar (1 a %d): ", cantidadPrestamo);
                int pos;
                scanf("%d", &pos);
                if (pos >= 1 && pos <= cantidadPrestamo) {
                    prestamo[pos - 1] = modificarPrestamo(prestamo[pos - 1]);
                } else {
                    printf("Índice inválido.\n");
                }
                break;
            case 4:
                guardarArchivoPrestamo(prestamo, cantidadPrestamo);
                printf("prestamos guardados. ¡Hasta luego!\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    }
}
// ===== END MANEJO ARCHIVO COMPRAS ===== //

// ===== MANEJO DE MOVIMIENTO ===== //
void menuMovimientos(Compra compras[], int cantidadCompras, Prestamo prestamos[], int cantidadPrestamos){
	int opcMovimiento;
	printf("1. Administrar Compras \n");
	printf("2. Administrar Ventas \n");
	printf("Qué movimiento desea realizar? \n");
	scanf("%d", &opcMovimiento);
	switch (opcMovimiento)
	{
	case 1:
		menuManejoCompra(compras, cantidadCompras);
		break;
	case 2:
		menuManejoPrestamo(prestamos, cantidadPrestamos);
		break;	
	default:
		break;
	}
}
// ===== END MANEJO DE MOVIMIENTO ===== //

// ===== VALIDACIONES DATOS ===== //
int verificarCliente(int nuevoCliente, Cliente clientes[], int cantidadClientes){
	int cedulaExistente;
    
	for(int i = 0; i<= cantidadClientes; i++){
		cedulaExistente = clientes[i].cedula;
		if(cedulaExistente == nuevoCliente){
			printf("Ya existe un cliente con ese numero de cedula\n");
			return 0;
		}
	}
	return 1;
}
// ===== END VALIDACIONES DATOS ===== //

// ===== MAIN FUNCIÓN PRINCIPAL ===== //
int main() {
    Cliente clientes[100];
	int opcMain;
    int cantidadClientes = leerArchivoCliente(clientes);
	Libro libros[100];
	Compra compras[100];
	Prestamo prestamos[100];
	int cantidadPrestamos=leerArchivoPrestamo(prestamos);
	int cantidadLibros = leerArchivoLibros(libros);
	int cantidadCompras = leerArchivoCompra(compras);

	while (opcMain != 4)
	{
		printf("\n========== MENU PRINCIPAL ==========\n");
		printf("1. Administrar Clientes.\n");
		printf("2. Administrar Libros.\n");
		printf("3. Adminitrar Movimiento.\n");
		printf("4. Cerrar Programa.\n");
		printf("Elija la opción: ");
		scanf("%d", &opcMain);
		switch(opcMain)
		{
			case 1:
				menuManejoClientes(clientes, cantidadClientes);
				break;
			case 2:
				menuManejoLibro(libros, cantidadLibros);
				break;
			case 3:
				menuMovimientos(compras, cantidadCompras, prestamos, cantidadPrestamos);
				break;
			case 4:
				printf("Se ha cerrado el programa, vuelva pronto.");
				break;
			default:
				printf("La opción no es válida");
				break;
		}
	}
	return 0;
    
}