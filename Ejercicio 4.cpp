#include <iostream>
using namespace std;
/*La calificación final de un estudiante de Algoritmos y Estructura de Datos
es la media ponderada de tres notas:
• la nota del Trabajo práctico que cuenta con un 30% del total
• la nota teórica que cuenta con un 60%
• la nota de participación que cuenta el 10% restante.
Escribir un programa que lea de la entrada estándar las tres notas de un alumno y escriba en la salida su nota final.*/
int main (){
    float notaTP, notaTeorica, notaParticipacion, promedioAlumno;
    cout << "Ingrese la nota del trabajo practico: "<< endl;
    cin >> notaTP;
    cout << "Ingrese la nota del Teorico" << endl;
    cin >> notaTeorica;
    cout << "Ingrese la nota de la participacion en clase: " << endl;
    cin >> notaParticipacion;
    promedioAlumno = (notaTP * 0.30) + (notaTeorica * 0.60) + (notaParticipacion * 0.10);
    cout << "La nota es: " << promedioAlumno;       
    return 0;
}