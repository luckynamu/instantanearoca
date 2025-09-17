#include <iostream>
#include <cstring>
using namespace std;

struct Articulo {
    int codigo;
    char descripcion[40];
    char rubro[20];
};

struct Indice{
    int codigoArticulo;
    int posicion;
};

void mostrarArchivo(FILE* archivo);
void cargarVectorIndices(FILE* archivo, Indice vector[], int &longitud);
void ordenarPorCodigo(Indice array[], int longitud);
void grabarIndice(FILE* archivo, Indice vector[], int longitud);
int busquedaBinariaIndice(FILE* archivo, int codigo);
void busquedaDirecta(FILE* archivo, int posicion);

int main(){
    FILE* archivoArticulos = fopen("C:/Users/mvpas/Documents/Universidad/Algoritmos y Estructuras de Datos/Archivos/articulos_deso.bin", "rb");
    if (!archivoArticulos) {
        cout << "No se pudo abrir el archivo articulos.bin\n";
        return 1;
    }
    FILE* archivoIndice = fopen("C:/Users/mvpas/Documents/Universidad/Algoritmos y Estructuras de Datos/Archivos/indicearticulos.bin", "wb+");
    int tamanioVectorIndices = 0;
    Indice vectorIndices[100];

    //Mostrar el archivo original de articulos antes de continuar
    mostrarArchivo(archivoArticulos);
    //Vuelvo al inicio de mi archivo para no tener problemas
    fseek(archivoArticulos, 0, SEEK_SET);
    cargarVectorIndices(archivoArticulos, vectorIndices, tamanioVectorIndices);
    ordenarPorCodigo(vectorIndices, tamanioVectorIndices);
    grabarIndice(archivoIndice, vectorIndices, tamanioVectorIndices);
    int codigoBuscar;
    cout << "Ingrese el codigo de articulo que quiera buscar: ";
    cin >> codigoBuscar;
    int posicionRegistro = busquedaBinariaIndice(archivoIndice, codigoBuscar);
    if (posicionRegistro != -1){
        busquedaDirecta(archivoArticulos, posicionRegistro);
    }
    else{
        cout << "Este articulo no se encuentra en el archivo.";
    }

    fclose(archivoArticulos);
    fclose(archivoIndice);
    return 0;
}

//Mostrar archivo original
void mostrarArchivo(FILE* archivo){
    Articulo articulos;
    while(fread(&articulos, sizeof(Articulo), 1, archivo) == 1){
        cout << "Codigo: " << articulos.codigo << "\t";
        cout << "Descripcion: " << articulos.descripcion;
        int diferenciaDeLongitudes = 40 - strlen(articulos.descripcion);
        for (int i = 0; i < diferenciaDeLongitudes; i++){
            cout << ' ';
        }
        cout << "\t" << articulos.rubro << endl;
    }
}

//Leer codigos y posiciones en un vector
void cargarVectorIndices(FILE* archivo, Indice vector[], int &longitud){
    Articulo articulos;
    int posicionRegistro = 0;
    while(fread(&articulos, sizeof(articulos), 1, archivo) == 1){
        vector[longitud].codigoArticulo = articulos.codigo;
        vector[longitud].posicion = posicionRegistro;
        longitud++;
        posicionRegistro++;
    }
}

//Ordenar vector por codigo de menor a mayor
void ordenarPorCodigo(Indice array[], int longitud){
    for (int i = 0; i < longitud; i++ ){
        for (int j = 0; j < longitud - i - 1; j++){
            if (array[j].codigoArticulo > array[j+1].codigoArticulo){
                Indice auxiliar = array[j];
                array[j] = array[j+1];
                array[j+1] = auxiliar;
            }
        }
    }
}

//Grabar indice en mi archivo de indices
void grabarIndice(FILE* archivo, Indice vector[], int longitud){
    fwrite(vector, sizeof(Indice), longitud, archivo);
}

//Busqueda binaria en mi archivo de indices
int busquedaBinariaIndice(FILE* archivo, int codigo){
    int posicionRegistro = -1;
    Indice indices;
    fseek(archivo, 0, SEEK_END);
    int posMin = 0;
    int posMax = (ftell(archivo)/sizeof(Indice)) - 1;

    while (posMin <= posMax){
        int mitad = (posMin + posMax)/2;
        fseek(archivo, mitad * sizeof(Indice), SEEK_SET);
        fread(&indices, sizeof(Indice), 1, archivo);
        if (indices.codigoArticulo == codigo){
            posicionRegistro = indices.posicion;
            break;
        }
        else if (codigo > indices.codigoArticulo){
            posMin = mitad + 1;
        }
        else {
            posMax = mitad - 1;
        }
    }
    return posicionRegistro;
}

//Busqueda directa en archivo de articulos. Muestra el registro
void busquedaDirecta(FILE* archivo, int posicion){
    Articulo articulos;
    fseek(archivo, sizeof(Articulo)*posicion, SEEK_SET);
    fread(&articulos, sizeof(Articulo), 1, archivo);
    cout << "Codigo: " << articulos.codigo << endl;
    cout << "Descripcion: " << articulos.descripcion << endl;
    cout << "Rubro: " << articulos.rubro << endl;
}