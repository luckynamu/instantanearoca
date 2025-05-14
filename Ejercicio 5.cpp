#include <iostream>
using namespace std;
//Escriba un programa que lea tres números y determine cuál de ellos es el mayor.
int main(){
    int primerNumero, segundoNumero, tercerNumero;
    cout  << "Ingresar tres numeros: " << endl;
    cin >> primerNumero >> segundoNumero >> tercerNumero;

    int mayor = primerNumero;
        if (segundoNumero > mayor) {
        mayor = segundoNumero;
    }
        if (tercerNumero > mayor) {
        mayor = tercerNumero;
    }
    cout << "Tu numerito mayor es este nenito: " << mayor << endl;
    return 0;
}