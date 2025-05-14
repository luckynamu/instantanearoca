 #include <iostream>
using namespace std;
//Escriba el fragmento de programa que intercambie los valores de dos variables
int main(){
    int a = 5;
    int b = 18;
    int auxiliar = a;
    a = b;
    b = auxiliar;
    cout << "La variable b deberia ser: " << b << " (cinco), ¿esta correcto?"<< endl;
    return 0;
}