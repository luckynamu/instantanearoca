#include <iostream>
using namespace std;
//Escriba un programa donde el usuario digite un número del 1 al 12 y que diga a que mes pertenece ese número.
int main(){
    string mesesDelAnio [] = {"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre", "Diciembre"};
    int numero = 0;
    while(numero < 1 || numero > 12){
        cout << "Ingrese un numero del 1 al 12 o explota todo: ";
        cin >> numero;
    }  
    cout << "El mes correspondiente al numero ingresado es: " << mesesDelAnio[numero-1];
    return 0;   
}