#include <iostream>
using namespace std;

struct palabrasRepetidas{
    string palabra;
    int repeticiones;
};

int longitudChar(char caracteres[]);
void convertirAMinuscula(char caracteres[], int longitud);
void contarPalabras(char caracteres[], int longCaracteres, string vector[], int &longitudVector);
void ordenarVectorPalabras(string vector[], int longitud);
void contarRepeticionesPalabra(string vectorOriginal[], int longitudVectorOriginal, palabrasRepetidas vector[], int &longitudVector);
void bubbleSort(palabrasRepetidas array[], int longitud);
void mostrarVector(palabrasRepetidas vec[], int cantidad);

int main(){
    char martinFierro[600] = "Aqui me pongo a cantar al compas de la viguela , que el hombre que lo desvela una pena estraordinaria, como la ave solitaria con el cantar se consuela. Pido a los Santos del Cielo que ayuden mi pensamiento, les pido en este momento que voy a cantar mi historia me refresquen la memoria, y aclaren mi entendimiento. Vengan Santos milagrosos, vengan todos en mi ayuda, que la lengua se me aniuda y se me turba la vista; pido a mi Dios que me asista en esta ocasion tan ruda.";
    
    //Calculo la longitud del Martin Fierro
    int longitudMartinFierro = longitudChar(martinFierro);

    //Convierto todas las letras en minusculas
    convertirAMinuscula(martinFierro, longitudMartinFierro);
    
    //Cargo un vector con cada palabra del Martin Fierro
    int longitudVectorPalabras;
    string vectorPalabras[longitudMartinFierro];
    contarPalabras(martinFierro, longitudMartinFierro, vectorPalabras, longitudVectorPalabras);
    
    //Ordeno el vector de palabras de A-Z para que sea mas facil buscar las repeticiones despues
    ordenarVectorPalabras(vectorPalabras, longitudVectorPalabras);
   
    //Defino un vector para almacenar la palabra y sus repeticiones, y luego calculo las repeticiones.
    int longitudVectorRepetidas;
    palabrasRepetidas vectorRepetidas[longitudVectorPalabras];
    contarRepeticionesPalabra(vectorPalabras, longitudVectorPalabras, vectorRepetidas, longitudVectorRepetidas);
    
    //Ordeno el vector de mayor a menor cantidad de repeticiones
    bubbleSort(vectorRepetidas, longitudVectorRepetidas);
    
    //Muestro el vector
    mostrarVector(vectorRepetidas, longitudVectorRepetidas);
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

//Convertir todas las letras en minusculas
void convertirAMinuscula(char caracteres[], int longitud){
    for (int i = 0; i < longitud; i++){
        if (caracteres[i] >= 65 && caracteres[i] <= 90){
            caracteres[i] += 32;
        }
    }
}

//Cargar un nuevo vector de palabras. En cada posicion va una palabra
void contarPalabras(char caracteres[], int longCaracteres, string vector[], int &longitudVector){
    char signosPuntuacion[9] = {' ', ',', '.', ':', ';', '!', '?', '(', ')'};
    longitudVector = 0;
    int r = 0;
    for (int i = 0; i < longCaracteres; i++){
        bool esSignoDePuntuacion = false;
        //Recorro el vector con los signos de puntuacion para ver si el caracter que estoy comparando lo es.
        for (int j = 0; j < 9; j++){
            if (caracteres[i] == signosPuntuacion[j]){
                esSignoDePuntuacion = true;
                break;
            }
        }
        if (!esSignoDePuntuacion){
            vector[longitudVector] += caracteres[i];
            r++;
        }
        else{
            if (r > 0){
                //vector[longitudVector] += '\0';
                longitudVector++;
                r = 0;
            }
        }
    }
}

//A-Z
void ordenarVectorPalabras(string vector[], int longitud){
    for (int i = 0; i < longitud; i++){
        for (int j = 0; j < longitud - i - 1; j++){
            if (vector[j] > vector[j+1]){
                string auxiliar = vector[j];
                vector[j] = vector[j+1];
                vector[j+1] = auxiliar;
            }
        }
    }
}

//Contar las repeticiones de la palabra y guardarla en un vector
void contarRepeticionesPalabra(string vectorOriginal[], int longitudVectorOriginal, palabrasRepetidas vector[], int &longitudVector){
    longitudVector = 0;
    int repeticiones = 1;
    for (int i = 0; i < longitudVectorOriginal; i++){
        if (i + 1 < longitudVectorOriginal && vectorOriginal[i] == vectorOriginal[i+1]){
            repeticiones++;
        }
        else{
            vector[longitudVector].palabra = vectorOriginal[i];
            vector[longitudVector].repeticiones = repeticiones;
            repeticiones = 1;
            longitudVector++;
        }
    }
}

//Ordenar el vector de repetidos de mayor a menor
void bubbleSort(palabrasRepetidas array[], int longitud){
    for (int i = 0; i < longitud; i++ ){
        for (int j = 0; j < longitud - i - 1; j++){
            if (array[j].repeticiones < array[j+1].repeticiones){
                palabrasRepetidas auxiliar = array[j];
                array[j] = array[j+1];
                array[j+1] = auxiliar;
            }
            //Si la cantidad de repeticiones es igual, ordeno alfabeticamente A-Z
            else if (array[j].repeticiones == array[j+1].repeticiones){
                if (array[j].palabra > array[j+1].palabra){
                    palabrasRepetidas auxiliar = array[j];
                    array[j] = array[j+1];
                    array[j+1] = auxiliar;
                }
            }
        }
    }
}

//Muestro el vector
void mostrarVector(palabrasRepetidas vec[], int cantidad){
    cout << "Cantidad de palabras encontradas: " << cantidad << endl;
    cout << "-----------------------------------------------------" << endl;
    for (int i = 0; i < cantidad; i++) {
        cout << "Palabra: '" << vec[i].palabra << "' - Repeticiones: " << vec[i].repeticiones << endl;
    }
}
