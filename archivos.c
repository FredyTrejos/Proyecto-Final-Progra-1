#include <stdio.h>

typedef struct { //estructura del cliente
	char nombre[30];
	char apellido[30];
	int cedula;
	int edad;
	int telefono;
	
} Cliente;

void guardarArchivoClientes(Cliente *vector, int tamano){
    FILE *archivoClientes = fopen("clientes.bat","wb");
    if (archivoClientes == NULL){
        printf("Error al abrir el archivo");
    } else {
        fwrite(vector, sizeof(Cliente), tamano, archivoClientes);
    }
    fclose(archivoClientes);
}

int leerArchivoCliente(Cliente *vector){
    FILE *archivoClientes = fopen("clientes.bat","rb");
    int cont = 0;
    if (archivoClientes == NULL){
        printf("Error al abrir el archivo");
    } else {
        while(fread(&vector[cont], sizeof(Cliente), 1, archivoClientes)){
            cont++;
        }
    }
    return cont; // Retorna el cont para saber cual fue la ultima posicion llena del vector
}
