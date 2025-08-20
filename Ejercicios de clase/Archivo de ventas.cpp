#include <iostream>
#include <cstring>
using namespace std;

struct Venta {
    char fecha[11];         // "YYYY-MM-DD" + '\0'
    char codigo[8];         // Ej: "ART001" + '\0'
    char descripcion[30];   // Nombre del producto
    char local[6];          // Ej: "LOC01" + '\0'
    float precio;
    int cantidad;
};

struct VentaImportes{
    char localcito[6];
    float importe;
};

void localesCta(char [][6],char [],int&);
void localesCuenta(VentaImportes vector[], char local[], float importe, int&cantLocales);
void bubbleSort(Venta array[], int longitud);

int main() {
    Venta ventas;
    VentaImportes vectorVentas[20]; //20 para que no se rompa
    int cantLocales = 0;

    char anioIngresado[5];
    cout << "Ingrese el anio (YYYY): ";
    cin >> anioIngresado;
    char mesIngresado[3];
    cout << "Ingrese el mes (MM): ";
    cin >> mesIngresado;
    char anioMes[8];

    strcpy(anioMes, anioIngresado);
    strcat(anioMes, "-");           
    strcat(anioMes, mesIngresado); 
    //Cambiar la direccion del archivo para trabajar localmente
    FILE* archivo = fopen("C:/Users/mvpas/Documents/Universidad/Algoritmos y Estructuras de Datos/Archivos/ventas.bin", "rb");
    if (!archivo) {
        cout << "No se pudo abrir el archivo ventas.bin\n";
        return 1;
    }
    int i = 0;
    while (fread(&ventas, sizeof(Venta), 1, archivo) == 1) {
        //localesCuenta(vectorVentas, ventas.local, ventas.precio*ventas.cantidad, cantLocales);
        bool esIgual = true;
        for (int j = 0; j < 7; j++){
            if(ventas.fecha[j] != anioMes[j]){
                esIgual = false;
                break;
            }
        }
        if (esIgual){
            /*cout << "Fecha: " << ventas.fecha << " ";
            cout << "Codigo: " << ventas.codigo << "\t";
            cout << "Precio: " << ventas.precio << "\t";
            cout << "Cantidad: " << ventas.cantidad << "\t";
            cout << "Descripcion: " << ventas.descripcion << "\t";
            cout << "Local: " << ventas.local << "\n";*/
            localesCuenta(vectorVentas, ventas.local, ventas.precio*ventas.cantidad,cantLocales);
        }
        i++; 
    }
    fclose(archivo);
    cout << "Ventas del " << anioIngresado << "/" << mesIngresado << endl;
    for (int j = 0; j < cantLocales; j++){
        cout << "---------------------------" << endl;
        cout << "Local: " << vectorVentas[j].localcito << " - Ventas: $" << vectorVentas[j].importe << endl; 
    }
    return 0;
}

void localesCuenta(VentaImportes vector[], char local[], float importe, int&cantLocales){
    bool esta = false;
    for (int i = 0; i < cantLocales; i++){
        if (strcmp(vector[i].localcito, local) == 0){
            esta = true;
            vector[i].importe += importe; 
        }
    }
    if (!esta){
        strcpy(vector[cantLocales].localcito, local);
        vector[cantLocales].importe = importe;
        cantLocales++;
    }
}
