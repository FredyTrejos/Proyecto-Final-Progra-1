#include <stdio.h>

// Estructuras
typedef struct{
    int dia;
    int mes;
    int anyo;
} Fecha;

typedef struct{
    int codigo;
    char descripcion[50];
    float precio;
    int cantidad;
} ProductoVenta;

typedef struct{
    char cedula[20];
    char nombre[50];
    char apellido[50];
    char telefono[20];
} Cliente;

typedef struct{
    int numeroFactura;
    Fecha fechaVenta;
    Cliente cliente;
    ProductoVenta productos[100];
    float valorTotal;
} Factura;

// Funciones

//CRUD Fecha
Fecha crearFecha(){
    Fecha fecha;
    printf("Ingrese dia: ");
    scanf("%d", &fecha.dia);
    printf("Ingrese mes: ");
    scanf("%d", &fecha.mes);
    printf("Ingrese año: ");
    scanf("%d", &fecha.anyo);
    return fecha;
}

void mostrarFecha(Fecha fecha){
    printf("%d/%d/%d", fecha.dia, fecha.mes, fecha.anyo);
}

Fecha modificarFechar(Fecha fecha){
    printf("Ingrese dia: ");
    scanf("%d", &fecha.dia);
    printf("Ingrese mes: ");
    scanf("%d", &fecha.mes);
    printf("Ingrese año: ");
    scanf("%d", &fecha.anyo);
    return fecha;
}

Fecha eliminarFecha(){
    Fecha fecha;
    return fecha;
}

// CRUD ProductoVenta
ProductoVenta crearProductoVenta(){
    ProductoVenta producto;
    printf("Ingrese codigo: ");
    scanf("%d", &producto.codigo);
    printf("Ingrese descripcion: ");
    scanf("%s", &producto.descripcion);
    printf("Ingrese precio: ");
    scanf("%f", &producto.precio);
    printf("Ingrese cantidad: ");
    scanf("%d", &producto.cantidad);
    return producto;
}

void mostrarProductoVenta(ProductoVenta producto){
    printf("Codigo: %d\n Descripcion: %s\n Precio: %f\n Cantidad: %d\n",
            producto.codigo, producto.descripcion, producto.precio, producto.cantidad);
}

ProductoVenta llenarProductoVenta(ProductoVenta productos[]){
    printf("Ingrese la cantidad de productos a registrar: ");
    int cantidad;
    scanf("%d", &cantidad);
    for(int cont=0; cont < cantidad; cont++){
        productos[cont] = crearProductoVenta();
    }

    // return productos;

}

// CRUD Cliente
Cliente crearCliente(){
    Cliente cliente;
    printf("Ingrese cedula: ");
    scanf("%s", &cliente.cedula);
    printf("Ingrese nombre: ");
    scanf("%s", &cliente.nombre);
    printf("Ingrese apellido: ");
    scanf("%s", &cliente.apellido);
    printf("Ingrese telefono: ");
    scanf("%s", &cliente.telefono);
    return cliente;
}

void mostrarCliente(Cliente cliente){
    printf("Cedula: %s\n Nombre: %s\n Apellido: %s\n Telefono: %s\n",
            cliente.cedula, cliente.nombre, cliente.apellido, cliente.telefono);
}

Factura crearFactura(){
    Factura factura;
    printf("Ingrese codigo: ");
    scanf("%d", &factura.numeroFactura);
    factura.fechaVenta = crearFecha();
    factura.cliente = crearCliente();
    factura.productos[100] = llenarProductoVenta(factura.productos);
    // factura.valorTotal = calcularPrecioTotal(factura.productos);

    return factura;
}


// float calcularPrecioTotal(ProductoVenta productos[]){
//     float num = 10.2;
//     return num;
// }


int main()
{
    printf("Hello World");
    Factura factura;
    factura = crearFactura();
    printf("%d", factura.numeroFactura);
    return 0;
}