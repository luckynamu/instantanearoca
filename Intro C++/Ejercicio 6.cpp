#include <iostream>
using namespace std;
//Escriba un programa para comprobar si un número digitado por el usuario es positivo o negativo.
int main(){
int numero;
cout << "Dame tu numero nenito" << endl;
cin >> numero;
if(numero < 0){
    cout << "Tu numero es negativo nenito";    
}
else if (numero == 0){
    cout << "Tu numero es cero nenito";
}
else {
    cout << "Tu numero es positivo nenito";
}
return 0;
}