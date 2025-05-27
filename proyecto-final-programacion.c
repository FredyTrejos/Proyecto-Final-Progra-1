#include <stdio.h>

// ===== ===== //

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
	Fecha fechaDevolucion; 
	int estado;
} Prestamo;

// ===== END Estructuras ===== //

// ===== Se definen Macros ===== //

// ===== END Macros ===== //

// ===== Se definen Enums ===== //

typedef enum{
	Prestamos = 1, Compras
} TipoTransaccion;

typedef enum{
	Efectivo = 1, Tarjeta, Transferencia
} MetodoDePago;

typedef enum{
	Devuelto = 1, Prestado
} EstadoPrestamo;

// ===== END Enums ===== //

 // ===== CRUD CLIENTES ===== //
 Cliente crearFecha(){
    Cliente cliente;
    printf("Ingrese la cédula: ");
    scanf("%d", &cliente.cedula);
    printf("Ingrese el nombre: ");
    scanf("%s", &cliente.nombre);
    printf("Ingrese el apellido: ");
    scanf("%s", &cliente.apellido);
    printf("Ingrese el teléfono: ");
    scanf("%d", &cliente.telefono);
	printf("Ingrese la edad: ");
    scanf("%d", &cliente.edad);
    return cliente;
}

void mostrarFecha(Cliente cliente){
    // code //
}

Cliente modificarFecha(Cliente cliente){
    // con un switch y capturar la opción le pregunta al usuario que dato quiere modificar.
    // code //
	return cliente;
}

Cliente eliminarFecha(){
    Cliente cliente;
	return cliente;
}

