#include <iostream>
using namespace std;

struct caracteresRepetidos{
    char caracter;
    int repeticiones;
};

int longitudChar(char caracteres[]);
void ordenarChar(char caracter[], int longitud);
void contarRepeticiones(char caracter[], int longitud, caracteresRepetidos vector[], int &longVectorRepetidos);
void bubbleSort(caracteresRepetidos array[], int longitud);
void mostrarVector(caracteresRepetidos vec[], int cantidad);

int main(){
    char martinFierro[600] = "Aqui me pongo a cantar al compas de la viguela , que el hombre que lo desvela una pena estraordinaria, como la ave solitaria con el cantar se consuela. Pido a los Santos del Cielo que ayuden mi pensamiento, les pido en este momento que voy a cantar mi historia me refresquen la memoria, y aclaren mi entendimiento. Vengan Santos milagrosos, vengan todos en mi ayuda, que la lengua se me aniuda y se me turba la vista; pido a mi Dios que me asista en esta ocasion tan ruda.";
    int longitudMF = longitudChar(martinFierro);
    ordenarChar(martinFierro, longitudMF);
    int longitudRepetidos;
    caracteresRepetidos vectorRepetidos[longitudMF];
    contarRepeticiones(martinFierro, longitudMF, vectorRepetidos, longitudRepetidos);
    bubbleSort(vectorRepetidos, longitudRepetidos);
    mostrarVector(vectorRepetidos, longitudRepetidos);
    return 0;
}

//Contar la longitud del Martin Fierro
int longitudChar(char caracteres[]){
    int longChar = 0;
    for (int i = 0; caracteres[i] != '\0'; i++){
        longChar++;
    }
    return longChar;
}

//A-Z
void ordenarChar(char caracter[], int longitud){
    for (int i = 0; i < longitud; i++){
        for (int j = 0; j < longitud - i - 1; j++){
            if (caracter[j] > caracter[j+1]){
                char auxiliar = caracter[j];
                caracter[j] = caracter[j+1];
                caracter[j+1] = auxiliar;
            }
        }
    }
}

//Contar las repeticiones de la letra y guardarla en un vector
void contarRepeticiones(char caracter[], int longitud, caracteresRepetidos vector[], int &longVectorRepetidos){
    int contador = 1;
    int i = 0;
    longVectorRepetidos = 0;
    while (i < longitud){
        if (caracter[i] == caracter[i+1]){
            contador++;
        }
        else{
            vector[longVectorRepetidos].caracter = caracter[i];
            vector[longVectorRepetidos].repeticiones = contador;
            longVectorRepetidos++;
            contador = 1;
        }
        i++;
    }
}

//Ordenar el vector de repetidos de mayor a menor
void bubbleSort(caracteresRepetidos array[], int longitud){
    for (int i = 0; i < longitud; i++ ){
        for (int j = 0; j < longitud - i - 1; j++){
            if (array[j].repeticiones < array[j+1].repeticiones){
                caracteresRepetidos auxiliar = array[j];
                array[j] = array[j+1];
                array[j+1] = auxiliar;
            }
        }
    }
}

//Muestro el vector
void mostrarVector(caracteresRepetidos vec[], int cantidad){
    for (int i = 0; i < cantidad; i++) {
        cout << "Hay " << vec[i].repeticiones << " repeticiones de '" << vec[i].caracter << "'" << endl;
    }
}
