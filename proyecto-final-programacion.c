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

void mostrarCliente(Cliente cliente){
    // code //
}

Cliente modificarCliente(Cliente cliente){
    // con un switch y capturar la opción le pregunta al usuario que dato quiere modificar.
    // code //
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
	printf("ingrese el dia");
	scanf("%d", &fecha.dia);
	printf("ingrese el mes");
	scanf("%d", &fecha.mes);
	printf("ingrese el año");
	scanf("%d", &fecha.anyo);
}

void mostrarFecha(Fecha fecha){
      printf("%d/%d/%d", fecha.dia, fecha.mes, fecha.anyo);
}

Fecha modificarFecha(Fecha fecha){
    // con un switch y capturar la opción le pregunta al usuario que dato quiere modificar.
    int opc;
	printf("¿que dato desea modificar?");
	printf("1.Dia");
	printf("2.Mes");
	printf("3.Año");
	scanf("%d", &opc);
	switch (opc)
	{
		case 1:
			printf("ingrese su dia");
			scanf("%d", &fecha.dia);
			break;
			
		case 2:
			printf("ingrese su mes");
			scanf("%d", &fecha.mes);
			break;
			
		case 3:
			printf("ingrese su año");
			scanf("%d", &fecha.anyo);
			break;
		default:
			printf("opcion no encontrada");
			break;
	}
	return fecha;
}

Fecha eliminarFecha(){
    Fecha fecha;
	return fecha;
}

// ===== END CRUD FECHA ===== //

