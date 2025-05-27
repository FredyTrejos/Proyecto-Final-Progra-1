#include <stdio.h>
#include <string.h>
// Macros

# define SALTARLINEA printf("\n");

// Enumeradores

typedef enum{
    Enero = 1, Febrero, Marzo // se debe poner número al primero para saber dónde empieza
} Meses;
// Estructuras
typedef struct
{
    int dia;
    int mes;
    int anio;
} Date;


typedef struct
{
	int codigo;
	char descripcion[50];
	float precio;
    int cantidad;
} ProductoVenta;

typedef struct
{
    char cedula[20];
    char nombre[50];
    char apellido[50];
    char telefono[20];
} Cliente;

typedef struct
{
    int numeroFactura;
    Date fecha;
    Cliente cliente;
    ProductoVenta productos[100];
    float totalFactura;

} Factura;

// Funciones
Date crearFecha(){
    Date date;
    printf("Ingrese el dia: ");
    scanf("%d", &date.dia);
    printf("Ingrese el mes: ");
    scanf("%d", &date.mes);
    printf("Ingrese el anio: ");
    scanf("%d", &date.anio);

    return date;
}

void mostrarFecha(Date date){
    printf("%d-%d-%d \n", date.dia, date.mes, date.anio);
}

Date modificarFecha(Date date){
    // con un switch y capturar la opción le pregunta al usuario que dato quiere modificar, día, mes o anio
    int opc;
    printf("Ingrese la opción que desea modificar \n");
    printf("1. Dia \n");
    printf("2. Dia \n");
    printf("3. Dia \n");
    scanf("%d", &opc);

    switch (opc)
    {
    case 1:
        printf("Ingrese el dia: ");
        scanf("%d", &date.dia);
        break;
    case 2:
        printf("Ingrese el mes: ");
        scanf("%d", &date.mes);
        break;
    case 3: 
        printf("Ingrese el anio: ");
        scanf("%d", &date.anio);
        break;
    default:
        printf("La opción no es correcta");
        break;
    }

    return date;
}

Date eliminarFecha(){
    Date date;
    return date;
}

// Este CRUD se va a repetir para todas las estructuras, como por ejemplo producto, cliente, factura.



void main(){
    Meses meses;
    meses = Enero;
    printf("%d", meses);
    scanf("%d", &meses);

    switch (meses)
    {
        case Enero:
            printf("Eligió 1");
            break;
        case Febrero: 
            printf("No existe");
            break;
        default:
            break;
    }

    // Date date;
    // date = crearFecha();
    // mostrarFecha(date);
    // date = modificarFecha(date);
    // mostrarFecha(date);
}