#include <stdio.h>

typedef struct{ // Estructura para el libro.
	int codigo;
	char autorLibro[30];
	char titulo[30];
	int anio;
	float precio;
	int cantidad; 
} Libro;

void guardarArchivoLibros(Libro *vector, int tamano){
	// Declara de tipo FILE el archivo en modo escritura.
    FILE *archivoLibro = fopen("libros.bat","wb");
    if (archivoLibro == NULL){
        printf("Error al abrir el archivo\n");
    } else {
		// Escribe el vector en el archivo.
        fwrite(vector, sizeof(Libro), tamano, archivoLibro);
    	fclose(archivoLibro);
    }
}

void main(){
    Libro libros[100];

    libros[0] = (Libro){1, "Homero", "La Odisea", 800, 35000, 11};
    libros[1] = (Libro){2, "Gabriel Garcia Marquez", "Cien anios de soledad", 1967, 42000, 7};
    libros[2] = (Libro){3, "Miguel de Cervantes", "Don Quijote de la Mancha", 1605, 50000, 5};
    libros[3] = (Libro){4, "J.K. Rowling", "Harry Potter y la piedra", 1997, 29000, 5};
    libros[4] = (Libro){5, "J.R.R. Tolkien", "El Señor de los Anillos", 1954, 55000, 8};
    libros[5] = (Libro){6, "George Orwell", "1984", 1949, 33.00, 6};
    libros[6] = (Libro){7, "Jane Austen", "Orgullo y prejuicio", 1813, 28000, 12};
    libros[7] = (Libro){8, "F. Scott Fitzgerald", "El Gran Gatsby", 1925, 31000, 9};
    libros[8] = (Libro){9, "Antoine de Saint-Exupery", "El Principito", 1943, 27000, 20};
    libros[9] = (Libro){10, "Harper Lee", "Matar a un ruisenior", 1960, 19000, 11};

	guardarArchivoLibros(libros, 10);
}