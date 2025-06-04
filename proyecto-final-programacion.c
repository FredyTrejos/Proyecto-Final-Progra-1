/*
Integrantes:
	- Edder Alexander Robayo Castillo
	- Jhon Fredy Trejos Morales
	- Danna Carid Velasquez Castañeda

Proyecto:
	- Manejo de Inventario y Movimientos de Librería.
	- Compras, prestamos.
*/

// ===== INCLUDE LIBRERIAS ===== //
#include <stdio.h>
// ===== END INCLUDE ===== //

// ===== Se definen Macros ===== //
#define ERROR printf("Error. Esta opcion no existe"); // Se muestra el error en opción no válida.
#define SONIDOERROR printf("\7"); // Sonido de error al seleccionar opciones no válidas.
#define DECORACION printf("====================================\n"); // Decorador para separar menús e información.
#define DECORACION2 printf("\n******************\n"); // Decorador para separar registros.
// ===== END Macros ===== //

// ===== SE DEFINEN LOS ENUMS ===== //
typedef enum{ // Enumerador para el tipo de transacción.
	Compras = 1, Prestamos, Salir
} TipoTransaccion;

typedef enum{ // Enumerador para el método de pago de la compra.
	Efectivo = 1, Tarjeta
} MetodoDePago;

typedef enum{ // Enumerador para el estado del préstamo.
	Prestado = 1, Devuelto
} EstadoPrestamo;
// ===== END ENUMS ===== //

// ===== SE DEFINEN LAS ESTRUCTURAS =====//
typedef struct { // Estructura para el cliente.
	char nombre[30];
	char apellido[30];
	int cedula;
	int edad;
	int telefono;
} Cliente;

typedef struct{ // Estructura para la fecha.
	int dia;
	int mes;
	int anyo;
} Fecha;

typedef struct{ // Estructura para el libro.
	int codigo;
	char autorLibro[30];
	char titulo[30];
	int anio;
	float precio;
	int cantidad; 
} Libro;

typedef struct{ // Estructura anidada para la compra.
	int numeroCompra;
	Cliente cliente;
	Libro libros[10];
	int cantidadLibros;
	Fecha fecha;
	MetodoDePago metodoDePago;
	float totalAPagar;
} Compra;

typedef struct{ // Estructura anidada para el prestamo.
	int numeroPrestamo;
	Cliente cliente;
	Libro libros[3];
	Fecha fechaPrestamo;
	Fecha fechaLimite;
	Fecha fechaDevolucion; 
	EstadoPrestamo estado;
	int cantidadLibros;
} Prestamo;
// ===== END ESTRUCTURAS ===== //

// ===== VALIDACIONES DATOS ===== //
int verificarCliente(int cedulaNueva, Cliente clientes[], int cantidadClientes){
	// Recibe la cedula nueva y la busca en los clientes existentes, si existe retorna 1, sino retorna 0.
	int cedulaExistente;
	int i;
    for(i = 0; i < cantidadClientes; i++){
		cedulaExistente = clientes[i].cedula;
		if(cedulaExistente == cedulaNueva){
			return 1;
		}
	}
	return 0;
}

Cliente asignarCliente(int nuevoCedula, Cliente clientes[], int cantidadClientes){
	// Recibe la cedula y la busca en la lista de clientes para retornar el cliente con esa cedula.
	int cedulaExistente, i;
	for(i = 0; i < cantidadClientes; i++){
		cedulaExistente = clientes[i].cedula;
		if(cedulaExistente == nuevoCedula){
			return clientes[i];
		}
	}
	return clientes[0];
}

int buscarUltimoCodigo(Libro libros[], int cantidadLibros){
	// Retornará el código del libro en la última posición.
	if(cantidadLibros == 0){
		return 0;
	}
	return libros[cantidadLibros-1].codigo;
}

Libro libroSeleccionado(int codigo, Libro libros[], int cantidad){
	// Recibe el codigo y lo busca en la lista de libros, sino está retorna el primer libro de la lista por defecto.
	int i;
	for(i = 0; i < cantidad; i++){
		if(libros[i].codigo == codigo){
			return libros[i];
		}
	}
	return libros[0];
}
// ===== END VALIDACIONES DATOS ===== //

// ===== CALCULAR TOTAL A PAGAR EN COMPRA ===== //
float calcularTotal(Libro libros[], int cantidad){
	// Función recursiva, recibe los libros de la compra y la cantidad (tamaño).
	if(cantidad == 1){
		return libros[cantidad-1].precio;
	}
	// El caso base será la cantidad 1, retornará el precio del libro en la primera posición.
	// Calcula el total reduciendo la cantidad y sumandolo al precio del libro en la posición actual (cantidad-1).
	return calcularTotal(libros, cantidad-1) + libros[cantidad-1].precio;
}
// ===== END TOTAL A PAGAR ===== //

// ===== CALCULAR TOTAL VENDIDO ===== //
int calcularTotalVendido(Compra compras[], int cantidadCompras){
	// Calcula con recursividad el Total vendido.
	if(cantidadCompras == 1){
		// Caso base, la cantidad es igual a 1 retorna el total a pagar de la primera compra.
		return compras[cantidadCompras-1].totalAPagar;
	}
	// Reduce la cantidad para llamar la función y se suma con el total a pagar de la compra actual (cantidad-1).
	return calcularTotalVendido(compras, cantidadCompras-1) + compras[cantidadCompras-1].totalAPagar;
}
// ===== END TOTAL VENDIDO ===== //

// ===== MANEJO DE ARCHIVOS TOTALES ===== //

// ===== MANEJO DE ARCHIVOS CLIENTES ===== //
void guardarArchivoClientes(Cliente *vector, int tamano){
	// Declara de tipo FILE el archivo en modo escritura
    FILE *archivoClientes = fopen("clientes.bat","wb");
    if (archivoClientes == NULL){
        printf("Error al abrir el archivo\n");
        SONIDOERROR
    } else {
		// Escribe el vector en el archivo.
        fwrite(vector, sizeof(Cliente), tamano, archivoClientes);
    }
    fclose(archivoClientes);
}

int leerArchivoCliente(Cliente *vector){
	// Declara de tipo FILE el archivo en modo lectura
    FILE *archivoClientes = fopen("clientes.bat","rb");
    int cont = 0;
    if (archivoClientes == NULL){
        guardarArchivoClientes(vector, 0);
    } else {
		// Mientras se retorne algo, leerá uno a uno los registros aumentando la cantidad.
        while(fread(&vector[cont], sizeof(Cliente), 1, archivoClientes)){
            cont++;
        }
    }
    return cont; // Retorna el cont para saber cual fue la ultima posicion llena del vector
}
// ===== END MANEJO DE ARCHIVO CLIENTES ===== //

// ===== MANEJO DE ARCHIVOS LIBRO ===== //
void guardarArchivoLibros(Libro *vector, int tamano){
	// Declara de tipo FILE el archivo en modo escritura.
    FILE *archivoLibro = fopen("libros.bat","wb");
    if (archivoLibro == NULL){
        printf("Error al abrir el archivo\n");
        SONIDOERROR
    } else {
		// Escribe el vector en el archivo.
        fwrite(vector, sizeof(Libro), tamano, archivoLibro);
    	fclose(archivoLibro);
    }
}

int leerArchivoLibros(Libro *vector){
	// Declara de tipo FILE el archivo en modo lectura.
    FILE *archivoLibro = fopen("libros.bat","rb");
    int cont = 0;
    if (archivoLibro == NULL){
		guardarArchivoLibros(vector, 0);
    } else {
		// Mientras retorne algo, leerá uno a uno los registros aumentando la cantidad.
        while(fread(&vector[cont], sizeof(Libro), 1, archivoLibro)){
            cont++;
        }
    }
    return cont; // Retorna el cont para saber cual fue la ultima posicion llena del vector
}
// ===== END MANEJO DE ARCHIVOS LIBRO ===== //

// ===== MANEJO DE ARCHIVO DE COMPRAS ===== //
void guardarArchivoCompra(Compra *vector, int tamano){
	// Declara de tipo FILE el archivo en modo escritura.
    FILE *archivoCompra = fopen("compra.bat","wb");
    if (archivoCompra == NULL){
        printf("Error al abrir el archivo\n");
        SONIDOERROR
    } else {
		// Escribe el vector en el archivo.
        fwrite(vector, sizeof(Compra), tamano, archivoCompra);
    }
    fclose(archivoCompra);
}

int leerArchivoCompra(Compra *vector){
	// Declara de tipo FILE el archivo en modo lectura
    FILE *archivoCompra = fopen("compra.bat","rb");
    int cont = 0;
    if (archivoCompra == NULL){
        guardarArchivoCompra(vector, 0);
    } else {
		// Mientras retorne algo, leerá uno a uno los registros aumentando la cantidad.
        while(fread(&vector[cont], sizeof(Compra), 1, archivoCompra)){
            cont++;
        }
    }
    return cont; // Retorna el cont para saber cual fue la ultima posicion llena del vector
}
// ===== END MANEJO DE ARCHIVO COMPRAS ===== //

// ===== MANEJO DE ARCHIVO DE PRESTAMO ===== //
void guardarArchivoPrestamo(Prestamo *vector, int tamano){
	// Declara de tipo FILE el archivo en modo escritura.
    FILE *archivoPrestamo = fopen("prestamo.bat","wb");
    if (archivoPrestamo == NULL){
        printf("Error al abrir el archivo\n");
        SONIDOERROR
    } else {
		// Escribe el vector en el archivo.
        fwrite(vector, sizeof(Prestamo), tamano, archivoPrestamo);
    }
    fclose(archivoPrestamo);
}

int leerArchivoPrestamo(Prestamo *vector){
	// Declara de tipo FILE el archivo en modo lectura
    FILE *archivoPrestamo = fopen("prestamo.bat","rb");
    int cont = 0;
    if (archivoPrestamo == NULL){
        guardarArchivoPrestamo(vector, 0);
    } else {
		// Mientras retorne algo, leerá uno a uno los registros aumentando la cantidad.
        while(fread(&vector[cont], sizeof(Prestamo), 1, archivoPrestamo)){
            cont++;
        }
    }
    return cont; // Retorna el cont para saber cual fue la ultima posicion llena del vector
}
// ===== END MANEJO DE ARCHIVO PRESTAMOS ===== //

// ===== END MANEJO DE ARCHIVOS TOTALES ===== //


// ===== CRUDS PARA TODAS LAS ESTRUCTURAS ===== //

// ===== CRUD CLIENTES ===== //
Cliente crearCliente(int nuevoCedula){
	// Recibe la cédula y lee por teclado los demás datos.
	Cliente cliente;
	cliente.cedula = nuevoCedula;
	getchar();
	printf("Ingrese el nombre: ");
	fgets(cliente.nombre, sizeof(cliente.nombre), stdin);
	printf("Ingrese el apellido: ");
	fgets(cliente.apellido, sizeof(cliente.apellido), stdin);
	printf("Ingrese el telefono: ");
	scanf("%d", &cliente.telefono);
	printf("Ingrese la edad: ");
	scanf("%d", &cliente.edad);   
    return cliente;
}

void mostrarCliente(Cliente cliente){
	// Imprime por pantalla cada una de las propiedades del cliente.
	printf("Cedula: %d \n", cliente.cedula);
	printf("Nombre: %s", cliente.nombre);
	printf("Apellido: %s", cliente.apellido); 
	printf("Telefono: %d \n", cliente.telefono);
	printf("Edad: %d \n", cliente.edad);
	
}

Cliente modificarCliente(Cliente cliente){
	// Con el switch se selecciona el dato que se quiere modificar, no permite modificar la cédula.
	int opc;
	while(opc != 5){
		DECORACION
		printf("Que dato desea modificar? \n");
		printf("1. Nombre \n");
		printf("2. Apellido \n");
		printf("3. Telefono \n");
		printf("4. Edad \n");
		printf("5. Salir. \n");
		DECORACION
		scanf("%d", &opc);
		getchar();
		switch (opc)
		{
			case 1:
				printf("Ingrese el nombre: ");
				fgets(cliente.nombre, sizeof(cliente.nombre), stdin);
				break;
			case 2:
				printf("Ingrese el apellido: ");
				fgets(cliente.apellido, sizeof(cliente.apellido), stdin);
				break;
			case 3:
				printf("Ingrese el telefono: ");
				scanf("%d", &cliente.telefono);
				break;
			case 4:
				printf("Ingrese la edad: ");
				scanf("%d", &cliente.edad);
				break;
			case 5: 
				printf("Saliendo del menu.");
				break;
			default:
				ERROR
				SONIDOERROR
				break;
		}
	}
    return cliente;
}

// eliminar un cliente
int eliminarCliente(Cliente clientes[], int cantidadClientes, int cedula){
	// Se buscará en la lista de clientes la cédula ingresada.
	int found = 0, i, j;
	for(i = 0; i < cantidadClientes; i++){
		if (clientes[i].cedula == cedula)
		{
			// Si la cédula coincide, modificará cada posición con la siguiente y reduce la cantidad de clientes.
			for(j = i; j < cantidadClientes; j++){
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
		printf("No se encontro un usuario con ese numero de cedula. \n");
	}

	return cantidadClientes;
}

 // ===== END CRUD CLIENTES ===== //


 // ===== CRUD FECHA ===== //
 Fecha crearFecha(){
	// Se crea el día, mes y año.
	Fecha fecha;
	printf("Ingrese el dia: ");
	scanf("%d", &fecha.dia);
	printf("Ingrese el mes: ");
	scanf("%d", &fecha.mes);
	printf("Ingrese el anio: ");
	scanf("%d", &fecha.anyo);

	return fecha;
}

void mostrarFecha(Fecha fecha){
	// Se muestran todos los datos de fecha en formato d/m/a
    printf("%d/%d/%d \n", fecha.dia, fecha.mes, fecha.anyo);
}

Fecha modificarFecha(Fecha fecha){
    // Con el switch se selecciona el dato a modificar.
    int opc;
    DECORACION
	printf("Que dato desea modificar? \n");
	printf("1.Dia \n");
	printf("2.Mes \n");
	printf("3.Anio \n");
	DECORACION
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
			printf("ingrese su anio: ");
			scanf("%d", &fecha.anyo);
			break;
		default:
			ERROR
			SONIDOERROR
			break;
	}
	return fecha;
}

Fecha eliminarFecha(Fecha fecha){
	// Para eliminar la fecha se limpiará con valores de 0.
    fecha.dia = 0;
	fecha.mes = 0;
	fecha.anyo = 0;

	return fecha;
}

// ===== END CRUD FECHA ===== //

// ===== CRUD LIBRO ===== //
int menu(){
	// Menú llamado desde la función modificar libro.
	DECORACION
    printf("Que dato sobre el libro desea modificar?\n");
    printf("1. Cambiar el  autor del libro\n");
    printf("2. Cambiar el titulo\n");
    printf("3. Cambiar el anio de publicacion\n");
    printf("4. cambiar el precio\n");
    printf("5. cambiar la cantidad\n");
    printf("6. Salir del menu\n");
    DECORACION
    printf("Elija una opcion: ");
	return 0;
}

Libro crearLibro(int nuevoCodigo){
	// Recibe el codigo del nuevo libro y lee por teclado los demás valores.
    Libro libro;
    libro.codigo = nuevoCodigo;
	getchar();
    printf("Ingrese el autor: ");
    fgets(libro.autorLibro, sizeof(libro.autorLibro), stdin);
    printf("Ingrese el titulo: ");
    fgets(libro.titulo, sizeof(libro.titulo), stdin);
    printf("Ingrese el anio: ");
    scanf("%d", &libro.anio);
	printf("Ingrese el precio: ");
    scanf("%f", &libro.precio);
    printf("Ingrese la cantidad: ");
    scanf("%d", &libro.cantidad);
    DECORACION
    return libro;
}
// en esta funcion lo mostramos
void mostrarLibro(Libro libro){
	// Se muestran todos los datos del libro.
	DECORACION2
	printf(" Codigo: %d \n", libro.codigo);
	printf(" Autor del libro: %s", libro.autorLibro);
	printf(" Titulo: %s", libro.titulo);
	printf(" Anio: %d \n", libro.anio);
	printf(" Precio: %.2f \n", libro.precio);
	printf(" Cantidad: %d \n", libro.cantidad);
	DECORACION2
}

// aca implementamos un switch para las opciones de modificar libro 
Libro modificarLibro(Libro libro){
	// Con el switch se modificará solo uno de los valores del libro.
	int opcion;
	opcion = 1;
	while(opcion !=6){
		menu();
	
		scanf("%d", &opcion);
		getchar();
		switch(opcion){
			case 1:
				printf("ingrese el nuevo autor: ");
				fgets(libro.autorLibro, sizeof(libro.autorLibro), stdin);
				break;
			case 2:
				printf("ingrese el nuevo titulo: ");
				fgets(libro.titulo, sizeof(libro.titulo), stdin);
				break;
			case 3:
				printf("ingrese el nuevo anio: ");
				scanf("%d", &libro.anio);
				break;	
			case 4:
				printf("ingrese el nuevo precio: ");
				scanf("%f", &libro.precio);
				break;	
			case 5:
				printf("ingrese la nueva cantidad: ");
				scanf("%d", &libro.cantidad);
			case 6:
				printf("Saliendo del menu...");
				break;
            default:
    			ERROR
				SONIDOERROR
                break;
		}
	}
	return libro;
}
// funcion para eliminar libro
int eliminarLibro(Libro libros[], int cantidadLibros, int codigo){
	// Se verifica si el codigo coincide con un libro existente.
	int found = 0, i, j;
	for( i = 0; i < cantidadLibros; i++){
		if (libros[i].codigo == codigo)
		{
			// Si coincide, se modifican los libros cada uno con el de la posición siguiente y reduce la cantidad.
			for(j = i; j < cantidadLibros; j++){
				libros[j] = libros[j+1];
			}
			cantidadLibros--;
			found = 1;
			break;
		}
	}

	if(found){
		printf("libro Eliminado con exito! \n");
	} else {
		printf("No se encontro un libro con ese codigo \n");
	}

	return cantidadLibros;
}
// ===== END CRUD LIBRO ===== //


// ===== CRUD COMPRA ===== //
Compra crearCompra(Libro libros[], int cantidadLibros, Cliente clientes[], int cantidadClientes){
	// Recibe los libros y clientes
	Compra compra;
	int codigo, cedula, i;
	printf("ingrese el numero de compra: ");
	scanf("%d", &compra.numeroCompra);
	printf("Ingrese el numero de cedula del cliente: ");
	scanf("%d", &cedula);
	// Verifica si el cliente existe para asignar el cliente a la compra o crear el cliente y asignarlo.
	if(verificarCliente(cedula, clientes, cantidadClientes)){
		compra.cliente = asignarCliente(cedula, clientes, cantidadClientes);
	} else {
		compra.cliente = crearCliente(cedula);
		clientes[cantidadClientes] = compra.cliente;
		// Se aumenta la cantidad de clientes y se guarda el archivo.
		cantidadClientes++;
		guardarArchivoClientes(clientes, cantidadClientes);
	}
	printf("Ingrese la cantidad de libros: ");
	scanf("%d", &compra.cantidadLibros);
	// Ingresa la cantidad de libros en la compra, y por cada uno asigna un libro según su codigo.
	for(i = 0; i < compra.cantidadLibros; i++){
		printf("Ingrese el codigo del libro %d: ", i+1);
		scanf("%d", &codigo);
		compra.libros[i] = libroSeleccionado(codigo, libros, cantidadLibros);
	}
	compra.fecha = crearFecha();
    printf("ingrese su metodo de pago: \n");
    printf("1.Efectivo\n");
    printf("2.Tarjeta\n");
	scanf("%d", &compra.metodoDePago);
	// Escanea el metodo de pago con el enumerador, si no coincide con ninguno, asigna Efectivo por defecto.
    if(compra.metodoDePago != Efectivo && compra.metodoDePago != Tarjeta){
		printf("Opcion invalida. Se asignara Efectivo por defecto.\n");
		compra.metodoDePago = Efectivo;
	}
	// Se calcula el total a pagar con la función recursiva, pasando los libros de la compra
	compra.totalAPagar = calcularTotal(compra.libros, compra.cantidadLibros);

	return compra;
}

void mostrarCompra(Compra compra){
	// Se muestran las propiedades, los datos del cliente, la lista de libros con titulo y precio, el método de pago y su total
	int i;
	DECORACION2
    printf("%d \n", compra.numeroCompra);
    mostrarCliente(compra.cliente);
	for(i = 0; i<compra.cantidadLibros; i++){
		printf("%s", compra.libros[i].titulo);
		printf("%.2f\n", compra.libros[i].precio);
	}
	switch (compra.metodoDePago) {
		case Efectivo:
			printf("Metodo de pago: Efectivo\n");
			break;
		case Tarjeta:
			printf("Metodo de pago: Tarjeta\n");
			break;
		default:
			printf("Metodo de pago: Desconocido\n");
	}
	printf("El total es: %.2f \n", compra.totalAPagar);
	mostrarFecha(compra.fecha);
	DECORACION2
}

Compra modificarCompra(Compra compra, Cliente clientes[], int cantidadClientes, Libro libros[], int cantidadLibros){
    // Con el switch se selecciona un único dato para modificar.
    int opc, cedula, numeroLibro, codigoLibro, i;
	printf("Que dato desea modificar?\n");
	printf("1.Cliente \n");
	printf("2.Libro \n");
	printf("3.Fecha \n");
    printf("4.Metodo de pago \n");
    DECORACION
	scanf("%d", &opc);
	switch (opc)
	{
		case 1:
			printf("Ingrese el numero de cedula del cliente: ");
			scanf("%d", &cedula);
			// Se verifica el cliente para asignar el existente o uno nuevo
			if(verificarCliente(cedula, clientes, cantidadClientes)){
				compra.cliente = asignarCliente(cedula, clientes, cantidadClientes);
			} else {
				compra.cliente = crearCliente(cedula);
				clientes[cantidadClientes] = compra.cliente;
				// Se aumenta la cantidad y se guarda el archivo.
				cantidadClientes++;
				guardarArchivoClientes(clientes, cantidadClientes);
			}
			break;
		case 2:
			// Se selecciona el libro a modificar para pasar el codigo del nuevo libro.
			for(i = 0; i < compra.cantidadLibros; i++){
				printf("%d. %s", i+1, compra.libros[i].titulo);
			}
			printf("Ingrese el numero del libro que desea modificar: ");
			scanf("%d", &numeroLibro);
			printf("Ingrese el codigo del libro nuevo: ");
			scanf("%d", &codigoLibro);
			compra.libros[numeroLibro-1] = libroSeleccionado(codigoLibro, libros, cantidadLibros);
			// Se calcula nuevamente el total a pagar ya que cambió el libro, por tanto su precio.
			compra.totalAPagar = calcularTotal(compra.libros, compra.cantidadLibros);
			break;	
		case 3:
			// Modificar solo un dato de la fecha.
			compra.fecha=modificarFecha(compra.fecha);
			break;
		case 4:
			// Modificar el método de pago o asignar efectivo por defecto.
			printf("1.Efectivo\n");
			printf("2.Tarjeta\n");
			printf("Ingrese el nuevo metodo de pago: ");
			scanf("%d", &compra.metodoDePago);
			if(compra.metodoDePago != Efectivo && compra.metodoDePago != Tarjeta) {
				printf("Opcion invalida. Se asignara Efectivo por defecto.\n");
				compra.metodoDePago = Efectivo;
			}
			break;
		default:
			ERROR
			SONIDOERROR
			break;
	}
	return compra;
}

int eliminarCompra(Compra compras[], int cantidadCompras, int numeroCompra){
	// Buscar la compra por su numero de compra para verificar si existe.
    int found = 0, i, j;

	for( i = 0; i < cantidadCompras; i++){
		if (compras[i].numeroCompra == numeroCompra)
		{
			// Si existe asigna en adelante la compra de la posición siguiente y reduce la cantidad de compras.
			for(j = i; j < cantidadCompras; j++){
				compras[j] = compras[j+1];
			}
			cantidadCompras--;
			found = 1;
			break;
		}
	}

	if(found){
		printf("Compra Eliminada con exito! \n");
	} else {
		printf("No se encontro una compra con ese codigo \n");
	}

	return cantidadCompras;
}
// ===== END CRUD COMPRA ===== //

// ===== CRUD PRESTAMO ===== //
Prestamo crearPrestamo(Libro libros[], int cantidadLibros, Cliente clientes[], int cantidadClientes){
	// Se reciben los libros y clientes para asignarlos al nuevo prestamo
	Prestamo prestamo;
	int cedula, codigo;
	int i;

	printf("ingrese el numero del prestamo: ");
	scanf("%d", &prestamo.numeroPrestamo);
	printf("Ingrese el numero de cedula del cliente: ");
	scanf("%d", &cedula);
	// Se verifica si el cliente existe para asignar el cliente existente o crear uno nuevo para el prestamo.
	if(verificarCliente(cedula, clientes, cantidadClientes)){
		prestamo.cliente = asignarCliente(cedula, clientes, cantidadClientes);
	} else {
		prestamo.cliente = crearCliente(cedula);
		clientes[cantidadClientes] = prestamo.cliente;
		// Se aumenta la cantidad de clientes y se guarda el archivo.
		cantidadClientes++;
		guardarArchivoClientes(clientes, cantidadClientes);
	}
	// Se ingresa la cantidad de libros para la compra y por cada uno se asignará un libro según su codigo.
	printf("ingrese la cantidad de libros: ");
	scanf("%d", &prestamo.cantidadLibros);
	for(i = 0; i < prestamo.cantidadLibros; i++){
		printf("Ingrese el codigo del libro %d: ", i+1);
		scanf("%d", &codigo);
		prestamo.libros[i] = libroSeleccionado(codigo, libros, cantidadLibros);
	}
	printf("ingrese la fecha de creacion\n");
	prestamo.fechaPrestamo = crearFecha();
	printf("ingrese la fecha limite\n");
	prestamo.fechaLimite = crearFecha();
	// Se asigna una fecha vacía o nula ya que aún no se ha devuelto.
	prestamo.fechaDevolucion = eliminarFecha(prestamo.fechaDevolucion);
	// Se ingresa el estado del prestamo según el enumerador.
    printf("1. prestado\n");
	printf("2. devuelto\n"); 
    printf("Ingrese el numero del estado del prestamo: ");
	scanf("%d", &prestamo.estado);
    if(prestamo.estado != Prestado && prestamo.estado != Devuelto) {
		printf("Opcion invalida. Se asignara Prestado por defecto.\n");
		prestamo.estado = Prestado;
	}
	return prestamo;
}

void mostrarPrestamo(Prestamo prestamo){
	// Se muestran todos los datos del prestamo, los datos del cliente, la lista de libros y el estado
    int i;
    printf("%d \n", prestamo.numeroPrestamo);
    mostrarCliente(prestamo.cliente);
	for(i = 0; i< prestamo.cantidadLibros; i++){
		printf("Libro %d: %s", i+1, prestamo.libros[i].titulo);
	}
	printf("Fecha del prestamo: ");
	mostrarFecha(prestamo.fechaPrestamo);
	printf("Fecha limite: ");
	mostrarFecha(prestamo.fechaLimite);
	printf("Fecha de devolucion: ");
	mostrarFecha(prestamo.fechaDevolucion);
	switch (prestamo.estado)
	{
		case Prestado:
			printf("Estado del prestamo: Prestado \n");
			break;
		case Devuelto:
			printf("Estado del prestamo: Devuelto \n");
		default:
			break;
	}
}

Prestamo modificarPrestamo(Prestamo prestamo, Cliente clientes[], int cantidadClientes, Libro libros[], int cantidadLibros){
    // El switch selecciona el dato a modificar del prestamo.
    int codigoLibro, numeroLibro, i, opc, cedula;
    DECORACION
	printf("que dato desea modificar? \n");
	printf("1.Cliente \n");
	printf("2.Libro \n");
	printf("3.Fecha Prestamo \n");
    printf("4.Fecha Limite \n");
    printf("5.Fecha Devolucion \n");
    printf("6.Estado \n");
    DECORACION
	scanf("%d", &opc);
	switch (opc)
	{
		case 1:
			// Se ingresa la cedula para asignar un cliente existente o uno nuevo
			printf("Ingrese el numero de cedula del cliente: ");
			scanf("%d", &cedula);
			if(verificarCliente(cedula, clientes, cantidadClientes)){
				prestamo.cliente = asignarCliente(cedula, clientes, cantidadClientes);
			} else {
				prestamo.cliente = crearCliente(cedula);
				clientes[cantidadClientes] = prestamo.cliente;
				// Si se crea un nuevo cliente se aumenta la cantidad y se guarda el archivo
				cantidadClientes++;
				guardarArchivoClientes(clientes, cantidadClientes);
			}
			break;
		case 2:
			// Se ingresa el libro del prestamo a modificar para asignar uno nuevo.
			for(i = 0; i < prestamo.cantidadLibros; i++){
				printf("%d. %s", i+1, prestamo.libros[i].titulo);
			}
			printf("Ingrese el numero del libro que desea modificar: \n");
			scanf("%d", &numeroLibro);
			printf("Ingrese el codigo del libro nuevo: ");
			scanf("%d", &codigoLibro);
			prestamo.libros[numeroLibro-1] = libroSeleccionado(codigoLibro, libros, cantidadLibros);
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
			// Con el enumerador se selecciona el nuevo estado del prestamo.
			printf("1. prestado\n");
			printf("2. devuelto\n"); 
			printf("Ingrese el estado del prestamo: ");
			scanf("%d", &prestamo.estado);
			if(prestamo.estado != Prestado && prestamo.estado != Devuelto) {
				printf("Opcion invalida. Se asignara Prestado por defecto.\n");
				prestamo.estado = Prestado;
			}
			break;
		default:
			ERROR
			SONIDOERROR
			break;
	}
	return prestamo;
}

int eliminarPrestamo(Prestamo prestamos[], int cantidadPrestamos, int numeroPrestamo){
	// Se valida si numeroPrestamo coincide con los registrados para eliminarlo.
    int found = 0, i, j;

	for( i = 0; i < cantidadPrestamos; i++){
		if (prestamos[i].numeroPrestamo == numeroPrestamo)
		{	
			// Si coincide asigna la posición siguiente a cada registro y reduce la cantidad.
			for(j = i; j < cantidadPrestamos; j++){
				prestamos[j] = prestamos[j+1];
			}
			cantidadPrestamos--;
			found = 1;
			break;
		}
	}

	if(found){
		printf("Prestamo Eliminado con exito! \n");
	} else {
		printf("No se encontro un prestamo con ese codigo \n");
	}

	return cantidadPrestamos;
}
// ===== END CRUD PRESTAMO ===== //

// ===== END CRUDS PARA TODAS LAS ESTRUCTURAS ===== //


// ===== MENU MANEJO CLIENTES ===== //
void menuManejoClientes(Cliente clientes[], int cantidadClientes){
	int opcion, cedula, i, pos;
    while(opcion != 5) {
		// En este menu se listan las opciones para el manejo de Clientes (CRUD de Clientes).
        printf("\n--- MENU CLIENTES ---\n");
        printf("1. Crear cliente\n");
        printf("2. Mostrar clientes\n");
        printf("3. Modificar cliente\n");
        printf("4. Eliminar cliente\n");
        printf("5. Guardar y salir\n");
        DECORACION
        printf("Elija una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidadClientes < 100){
					printf("Ingrese la cedula: ");
					scanf("%d", &cedula);
					// Se verifica si ese numero de cedula existe, si no existe se creará uno nuevo con la función del CRUD
					if(!verificarCliente(cedula, clientes, cantidadClientes)){
						clientes[cantidadClientes] = crearCliente(cedula);
                    	cantidadClientes++;
						guardarArchivoClientes(clientes, cantidadClientes);
					} else{
						printf("Ya existe un usuario con ese numero de cedula \n");
					}   
                } else {
                    printf("No hay mas espacio para clientes.\n");
                }
                break;
            case 2:
				// Se lee nuevamente el archivo de clientes para tener la vista actualizada.
				cantidadClientes = leerArchivoCliente(clientes);
                for (i = 0; i < cantidadClientes; i++) {
                    printf("\nCliente #%d:\n", i+1);
                    mostrarCliente(clientes[i]);
					DECORACION
                }
                break;
            case 3:
				// Se elige el cliente para modificar pasando a la función modificar el cliente especifico.
				cantidadClientes = leerArchivoCliente(clientes);
                printf("Ingrese el numero del cliente a modificar (1 a %d): ", cantidadClientes);
                scanf("%d", &pos);
                if (pos >= 1 && pos <= cantidadClientes) {
                    clientes[pos-1] = modificarCliente(clientes[pos-1]);
					// Luego de modificar se guarda nuevamente el archivo de clientes.
					guardarArchivoClientes(clientes, cantidadClientes);
                } else {
                    printf("Indice invalido.\n");
                    SONIDOERROR
                }
                break;
			case 4:
				// Se ingresa un número de cédula para ir a compararla con las cedulas registradas y luego guardar el archivo
				printf("Ingrese la cedula a eliminar: ");
				scanf("%d", &cedula);
				cantidadClientes = eliminarCliente(clientes, cantidadClientes, cedula);
				guardarArchivoClientes(clientes, cantidadClientes);
				break;
            case 5:
				// caso para salir del menú, además guarda de nuevo el archivo 
                guardarArchivoClientes(clientes, cantidadClientes);
                printf("Clientes guardados.\n");
                break;
            default:
            	ERROR
				SONIDOERROR
        }
    }
}
// ===== END MENU MANEJO CLIENTES ===== //

// ===== MENU MANEJO LIBROS ===== //
void menuManejoLibro(Libro libros[], int cantidadLibros){
	int opcion, ultimoCodigo, codigo, pos, i;

    while(opcion != 5) {
		// Menu para manejo de libros
        printf("\n--- MENU LIBROS ---\n");
        printf("1. Crear libros\n");
        printf("2. Mostrar libros\n");
        printf("3. Modificar libros\n");
        printf("4. Eliminar libro\n");
        printf("5. Guardar y salir\n");
        DECORACION
        printf("Elija una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidadLibros < 100) {
					// Se busca el codigo del último libro registrado, para asignar al nuevo libro el siguiente consecutivo
					ultimoCodigo = buscarUltimoCodigo(libros, cantidadLibros);
					libros[cantidadLibros] = crearLibro(ultimoCodigo+1);
                    cantidadLibros++;
					guardarArchivoLibros(libros, cantidadLibros);
                } else {
                    printf("No hay mas espacio para libros.\n");
                }
                break;
            case 2:
				// Mostrar uno por uno todos los libros registrados.
				cantidadLibros = leerArchivoLibros(libros);
                for (i = 0; i < cantidadLibros; i++) {
                    printf("\nLibro #%d:\n", i+1);
                    mostrarLibro(libros[i]);
                }
                break;
            case 3:
				// Elegir un libro para modificarlo en la función.
                printf("Ingrese el numero del libro a modificar (1 a %d): ", cantidadLibros);
                scanf("%d", &pos);
                if (pos >= 1 && pos <= cantidadLibros) {
                    libros[pos - 1] = modificarLibro(libros[pos - 1]);
					guardarArchivoLibros(libros, cantidadLibros);
                } else {
                    printf("Indice invalido.\n");
                }
                break;
            case 4:
				// se ingresa el codigo del libro para eliminar uno específico.
            	printf("Ingrese el codigo a eliminar: ");
				scanf("%d", &codigo);
				cantidadLibros = eliminarLibro(libros, cantidadLibros, codigo);
				guardarArchivoLibros(libros, cantidadLibros);
				break;
            case 5:
				// Caso para salir del menú y guardar el archivo nuevamente
                guardarArchivoLibros(libros, cantidadLibros);
                printf("Libros guardados. \n");
                break;
            default:
          		ERROR
				SONIDOERROR
				break;
        }
    }
}
// ===== END MENU MANEJO LIBROS ===== //

// ===== MENU MANEJO DE COMPRAS ===== //
void menuManejoCompra(Compra compras[], int cantidadCompras, Libro libros[], int cantidadLibros, Cliente clientes[], int cantidadClientes){
	int opcion, numeroCompra, i, pos;
    while(opcion != 5) {
		// Menu para manejar las acciones en las compras
        printf("\n--- MENU COMPRAS ---\n");
        printf("1. Crear compra\n");
        printf("2. Mostrar compras\n");
        printf("3. Modificar compras\n");
        printf("4. Eliminar compras\n");
        printf("5. Guardar y salir\n");
        DECORACION
        printf("Elija una opcion: \n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidadCompras < 100) {
					// Se lee el archivo de libros para tener la cantidad de libros actualizada, para luego crear la compra.
					cantidadLibros = leerArchivoLibros(libros);
					// Se pasan los libros y clientes a crear Compra ya que la compra tiene asociada estos datos. 
                    compras[cantidadCompras] = crearCompra(libros, cantidadLibros, clientes, cantidadClientes);
                    cantidadCompras++;
					guardarArchivoCompra(compras, cantidadCompras);
                } else {
                    printf("No hay mas espacio para compras.\n");
                }
                break;
            case 2:
				// Mostrar una a una las compras registradas.
				cantidadCompras = leerArchivoCompra(compras);
                for (i = 0; i < cantidadCompras; i++) {
                    printf("\ncompra #%d:\n", i+1);
                    mostrarCompra(compras[i]);
                }
                break;
            case 3:
				// Se leen los libros para tener actualizada la cantidad.
				cantidadLibros = leerArchivoLibros(libros);
				cantidadCompras = leerArchivoCompra(compras);
                printf("Ingrese el numero de la compra a modificar (1 a %d): ", cantidadCompras);
                scanf("%d", &pos);
                if (pos >= 1 && pos <= cantidadCompras) {
					// Eligiendo una compra específica se modificará esta pasando la compra, clientes y libros para asociarlos.
                    compras[pos - 1] = modificarCompra(compras[pos - 1], clientes, cantidadClientes, libros, cantidadLibros);
                } else {
                    printf("Indice invalido.\n");
                    SONIDOERROR
                }
				guardarArchivoCompra(compras, cantidadCompras);
                break;
			case 4:
				// Eliminar una compra por su numero de compra.
				cantidadCompras = leerArchivoCompra(compras);
				printf("Ingrese el numero de compra a eliminar: ");
				scanf("%d", &numeroCompra);
				cantidadCompras = eliminarCompra(compras, cantidadCompras, numeroCompra);
				guardarArchivoCompra(compras, cantidadCompras);
            case 5:
				// Caso para salir del menú y guardar el archivo.
                guardarArchivoCompra(compras, cantidadCompras);
                printf("Compras guardadas.\n");
                break;
            default:
                ERROR
				SONIDOERROR
				break;
        }
    }
}
// ===== END MENU MANEJO DE COMPRAS ===== //

// ===== MENU MANEJO DE PRESTAMOS ===== //
void menuManejoPrestamo(Prestamo prestamos[], int cantidadPrestamo, Libro libros[], int cantidadLibros, Cliente clientes[], int cantidadClientes){
	int opcion, numeroPrestamo;
	int i;
    while(opcion != 5) {
		// Menu para el manejo de prestamos.
        printf("\n--- MENU PRESTAMOS ---\n");
        printf("1. Crear prestamo\n");
        printf("2. Mostrar prestamo\n");
        printf("3. Modificar prestamo\n");
        printf("4. Eliminar prestamo\n");
        printf("5. Guardar y salir\n");
        DECORACION
        printf("Elija una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidadPrestamo < 100) {
					// Se lee el archivo de libros para tener la cantidad actualizada
					cantidadLibros = leerArchivoLibros(libros);
					// Se pasa a la función crear los libros y clientes para asociarlos.
                    prestamos[cantidadPrestamo] = crearPrestamo(libros, cantidadLibros, clientes, cantidadClientes);
                    cantidadPrestamo++;
					guardarArchivoPrestamo(prestamos, cantidadPrestamo);
                } else {
                    printf("No hay mas espacio para prestamos.\n");
                }
                break;
            case 2:
				// Mostrar uno a uno los prestamos registrados.
				cantidadPrestamo = leerArchivoPrestamo(prestamos);
                for (i = 0; i < cantidadPrestamo; i++) {
    				DECORACION2
                    printf("Prestamo #%d:\n", i+1);
                    mostrarPrestamo(prestamos[i]);
                }
                break;
            case 3:
				// Leer los libros para tener la cantidad actualizada.
				cantidadLibros = leerArchivoLibros(libros);
				cantidadPrestamo = leerArchivoPrestamo(prestamos);
                printf("Ingrese el numero del prestamo a modificar (1 a %d): ", cantidadPrestamo);
                int pos;
                scanf("%d", &pos);
                if (pos >= 1 && pos <= cantidadPrestamo) {
					// Llamar a modificar el prestamo específico seleccionado.
                    prestamos[pos - 1] = modificarPrestamo(prestamos[pos - 1], clientes, cantidadClientes, libros, cantidadLibros);
                } else {
                    printf("Indice invalido.\n");
                    SONIDOERROR
                }
				guardarArchivoPrestamo(prestamos, cantidadPrestamo);
                break;
			case 4:
				// Eliminar un prestamo específico a partir del numeroPrestamo.
				cantidadPrestamo = leerArchivoPrestamo(prestamos);
				printf("Ingrese el numero de prestamo a eliminar: ");
				scanf("%d", &numeroPrestamo);
				cantidadPrestamo = eliminarPrestamo(prestamos, cantidadPrestamo, numeroPrestamo);
				guardarArchivoPrestamo(prestamos, cantidadPrestamo);
            case 5:
				// Caso para salir del menú y guardar el archivo.
                guardarArchivoPrestamo(prestamos, cantidadPrestamo);
                printf("Prestamos guardados\n");
                break;
            default:
               	ERROR
				SONIDOERROR
        }
    }
}
// ===== END MENU MANEJO DE PPRESTAMOS ===== //

// ===== MENU MANEJO DE MOVIMIENTO ===== //
void menuMovimientos(Compra compras[], int cantidadCompras, Prestamo prestamos[], int cantidadPrestamos, Libro libros[], int cantidadLibros, Cliente clientes[], int cantidadClientes){
	TipoTransaccion opcMovimiento = 0;

	while(opcMovimiento != 3)
	{	
		// Menu para el manejo de movimientos = Compras y Prestamos.
		DECORACION
		printf("1. Administrar Compras \n");
		printf("2. Administrar Prestamos \n");
		printf("3. Salir del menu. \n");
		printf("Que movimiento desea realizar? \n");
		scanf("%d", &opcMovimiento);

		DECORACION
		// Para este switch case se utiliza el enumerador TipoTransaccion para compras, prestamos o salir del menú.
		switch (opcMovimiento)
		{
			case Compras:
				menuManejoCompra(compras, cantidadCompras, libros, cantidadLibros, clientes, cantidadClientes);
				break;
			case Prestamos:
				menuManejoPrestamo(prestamos, cantidadPrestamos, libros, cantidadLibros, clientes, cantidadClientes);
				break;	
			case Salir: 
				printf("Saliendo del menu.");
				break;
			default:
				ERROR
				SONIDOERROR
				break;
		}	
	}
}
// ===== END MENU MANEJO DE MOVIMIENTO ===== //


// ===== MAIN FUNCIÓN PRINCIPAL ===== //
int main() {
	int opcMain, totalVendido;
	// Se crean las listas de estructuras
    Cliente clientes[100];
	Libro libros[100];
	Compra compras[100];
	Prestamo prestamos[100];
	// Se determina la cantidad en cada una de las listas leyendo sus archivos.
    int cantidadClientes = leerArchivoCliente(clientes);
	int cantidadLibros = leerArchivoLibros(libros);
	int cantidadCompras = leerArchivoCompra(compras);
	int cantidadPrestamos=leerArchivoPrestamo(prestamos);

	while(opcMain != 5)
	{
		// Menu principal, aquí empieza la lógica para elegir que tipos de movimientos se realizan.
		printf("\n========== MENU PRINCIPAL ==========\n");
		printf("1. Administrar Clientes.\n");
		printf("2. Administrar Libros.\n");
		printf("3. Adminitrar Movimiento.\n");
		printf("4. Mostrar Total Vendido.\n");
		printf("5. Cerrar Programa.\n");
		DECORACION
		printf("Elija una opcion: \n");
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
				menuMovimientos(compras, cantidadCompras, prestamos, cantidadPrestamos, libros, cantidadLibros, clientes, cantidadClientes);
				break;
			case 4:
				totalVendido = calcularTotalVendido(compras, cantidadCompras);
				printf("El valor total de las ventas fue de: %d", totalVendido);
				break;
			case 5:
				DECORACION
				printf("Se ha cerrado el programa, vuelva pronto. \n");
				DECORACION
				break;
			default:
				ERROR
				SONIDOERROR
				break;
		}
	}
	return 0;   
}
// ===== END MAIN FUNCION PRINCIPAL ===== //