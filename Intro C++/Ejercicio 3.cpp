#include <iostream>
using namespace std;
//Escriba un programa que lea la nota final de cuatro alumnos y calcule la nota final media
int main(){
    float notaPrimerAlumno, notaSegundoAlumno, notaTercerAlumno, notaCuartoAlumno, notaFinalMedia;
    cout << "Ingrese las notas de los cuatro alumnos:" << endl;
    cin >> notaPrimerAlumno >> notaSegundoAlumno >> notaTercerAlumno >> notaCuartoAlumno;
    notaFinalMedia = (notaPrimerAlumno + notaSegundoAlumno + notaTercerAlumno + notaCuartoAlumno)/4;
    cout << "La nota final media de los 4 alumnos es: " << notaFinalMedia << endl;
    return 0;
}