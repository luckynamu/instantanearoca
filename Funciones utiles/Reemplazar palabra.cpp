#include <iostream>
#include <cstring>
using namespace std;

struct Articulo {
    int codigo;
    char descripcion[40];
    char rubro[20];
};

int main() {
    Articulo articulos;
    FILE* archivo = fopen("C:/Users/mvpas/Documents/Universidad/Algoritmos y Estructuras de Datos/Archivos/articulos.bin", "rb+");
    if (!archivo) {
        cout << "No se pudo abrir el archivo articulos.bin\n";
        return 1;
    }

    // Mostrar archivo original
    cout << "Archivo original: " << endl;
    int i = 0;
    while (fread(&articulos, sizeof(Articulo), 1, archivo) == 1) {
        cout << i+1 << ")\t"
             << articulos.codigo << "\t"
             << articulos.descripcion << "\t"
             << articulos.rubro << endl;
        i++;
    }

    // Volver al inicio para modificar
    fseek(archivo, 0, SEEK_SET);

    while (fread(&articulos, sizeof(Articulo), 1, archivo) == 1) {
        if (strcmp(articulos.rubro, "Electronica") == 0) {
            // Cambiar rubro
            strncpy(articulos.rubro, "Digital", sizeof(articulos.rubro) - 1);
            articulos.rubro[sizeof(articulos.rubro) - 1] = '\0';

            // Retroceder y escribir
            fseek(archivo, -sizeof(Articulo), SEEK_CUR);
            fwrite(&articulos, sizeof(Articulo), 1, archivo);

            // Ahora mover puntero al final de este registro escrito
            fseek(archivo, 0, SEEK_CUR);
        }
    }

    // Volver al inicio para mostrar modificado
    fseek(archivo, 0, SEEK_SET);

    cout << "\nArchivo modificado: " << endl;
    int j = 0;
    while (fread(&articulos, sizeof(Articulo), 1, archivo) == 1) {
        cout << j+1 << ")\t"
             << articulos.codigo << "\t"
             << articulos.descripcion << "\t"
             << articulos.rubro << endl;
        j++;
    }

    fclose(archivo);
    return 0;
}