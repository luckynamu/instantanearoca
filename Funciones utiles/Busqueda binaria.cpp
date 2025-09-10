#include <iostream>
#include <cstring>
using namespace std;

struct Articulo {
    int codigo;
    char descripcion[40];
    char rubro[20];
};

int main() {
    FILE* archivo = fopen("C:/Users/mvpas/Documents/Universidad/Algoritmos y Estructuras de Datos/Archivos/articulos.bin", "rb");
    if (!archivo) {
        cout << "No se pudo abrir el archivo articulos.bin\n";
        return 1;
    }

    Articulo vectorArticulos;
    int codigoBuscar;
    cout << "Ingrese el codigo del producto que quiere buscar: ";
    cin >> codigoBuscar;

    fseek(archivo, 0, SEEK_END);
    int cantidadRegistros = ftell(archivo) / sizeof(Articulo);
    int posMin = 0;
    int posMax = cantidadRegistros - 1;
    bool encontrado = false;

    while (posMin <= posMax) {
        int mitad = (posMin + posMax) / 2;
        fseek(archivo, mitad * sizeof(Articulo), SEEK_SET);
        fread(&vectorArticulos, sizeof(Articulo), 1, archivo);

        if (vectorArticulos.codigo == codigoBuscar) {
            encontrado = true;
            cout << "Codigo: " << vectorArticulos.codigo << endl;
            cout << "Descripcion: " << vectorArticulos.descripcion << endl;
            cout << "Rubro: " << vectorArticulos.rubro << endl;
            break;
        } else if (codigoBuscar > vectorArticulos.codigo) {
            posMin = mitad + 1;
        } else {
            posMax = mitad - 1;
        }
    }

    if (!encontrado) {
        cout << "No se encontro ningun articulo con el codigo " << codigoBuscar << endl;
    }

    fclose(archivo);
    return 0;
}
