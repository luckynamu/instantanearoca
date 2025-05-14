#include <iostream>
using namespace std;
/*Escriba un programa que lea la entrada de un carácter
e indique en la salida si el carácter es una vocal minúscula o no.*/
int main(){
    char caracter;
    cout << "Ingresa un caracter: ";
    cin >> caracter;
    if(caracter == 'a' || caracter == 'e'|| caracter == 'i'|| caracter == 'o'||caracter == 'u'){
        cout << "Tu caracter es vocal minuscula yupiii";
    }
    else{
        cout << "Tu caracter es cualquier cosa nenito";
    }
    return 0;
}