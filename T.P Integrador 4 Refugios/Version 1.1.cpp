#include <iostream>
#include <cstring>
using namespace std;

struct RegCorredores {
    int numero;
    char nombreApellido[50];
    char categoria[50];
    char genero;
    char localidad[40];
    char llegada[11];
};

struct ListadoCarrera{
    int posGeneral;
    int posGenero;
    int posCat;
    int numero;
    char nombreApellido[50];
    char categoria[50];
    char genero;
    char localidad[40];
    char llegada[11];
    char difPrimero[11];
    char difAnterior[11];
};

struct Podios{
    int posCat;
    int numero;
    char nombreApellido[50];
    char categoria[50];
    char genero;
    char localidad[40];
    char llegada[11];
};

struct CorredoresCiudad {
    int numero;
    char nombreApellido[50];
    char localidad[40];
    char ciudad[30];
};

void noTermino(FILE* archivo);
void cargarCorredores(FILE* archivo, RegCorredores vector[], int &longitud);
void ordenarPorTiempo(RegCorredores vector[], int longitud);
void separarPorCarrera(RegCorredores vectorOriginal[], int longitudOriginal, ListadoCarrera vectorUno[], int &longitudUno, ListadoCarrera vectorDos[], int &longitudDos);
void posicionGenero(ListadoCarrera vector[], int longitud);
void determinarCategorias(ListadoCarrera vector[], int longitudVector, string vectorCategoria[], int &longitudCategoria);
void posicionCategoria(ListadoCarrera vector[], int longitudVector, string vectorCategoria[], int longitudCategoria);
float convertirASegundos(char llegada[]);
void segundosAFormato(float tiempo, char llegada[]);
void diferenciaPrimero(ListadoCarrera vector[], int longitud);
void diferenciaAnterior(ListadoCarrera vector[], int longitud);
void cargarArchivosCarrera(FILE* archivo, ListadoCarrera vector[], int longitud);
void imprimirEspacios(int cantidadEspacios);
void mostrarReporte(FILE* archivo);
void ordenarAlfabeticamente(string vector[], int longitud);
void extraerPodios(Podios vectorPodios[], int &cantidadPodios, string categorias[], int longitudCategorias, ListadoCarrera vectorCarrera[], int longitudCarrera);
void mostrarPodios(FILE* archivo);

int main(){
    FILE *archivoCorredores = fopen("Archivo corredores 4Refugios.bin", "rb+");
    if (!archivoCorredores){
        cout << "No se pudo abrir el archivo Corredores 4Refugios.bin\n";
        return 1;
    }

    FILE *archivoClasica = fopen("clasica.bin", "wb+");
    if (!archivoClasica){
        cout << "No se pudo abrir el archivo clasica.bin\n";
        return 1;
    }

    FILE *archivoNonStop = fopen("nonStop.bin", "wb+");
    if (!archivoNonStop){
        cout << "No se pudo abrir el archivo nonStop.bin\n";
        return 1;
    }
    
    FILE *archivoPodios = fopen("podios.bin", "wb+");
    if (!archivoPodios){
        cout << "No se pudo abrir el archivo podios.bin\n";
        return 1;
    }

    //Paso 1: Reemplazar "DNF", "DNF (NL)" y "DSQ (FE)" en el archivoCorredores por "No termino". Modificamos el campo char llegada[11].
    noTermino(archivoCorredores);

    //Paso 2: Cargar todos los corredores en un vector.
    RegCorredores vectorCorredores[2000];
    int cantidadCorredores = 0;
    cargarCorredores(archivoCorredores, vectorCorredores, cantidadCorredores);

    //Interludio: Cerrar el archivoCorredores.
    //fclose(archivoCorredores);

    //Paso 3: Ordenar a los corredores por tiempo de llegada.
    ordenarPorTiempo(vectorCorredores, cantidadCorredores);

    //Paso 4: Crear un vector para la carrera Clasica y otro para la NonStop y cargar los corredores correspondientes a cada uno.
    //Utilizamos un nuevo struct para las carreras ya que crearemos nuevos datos.
    ListadoCarrera vectorClasica[1000];
    int cantidadCorredoresClasica = 0;
    ListadoCarrera vectorNonStop[1000];
    int cantidadCorredoresNonStop = 0;
    separarPorCarrera(vectorCorredores, cantidadCorredores, vectorClasica, cantidadCorredoresClasica, vectorNonStop, cantidadCorredoresNonStop);

    //Paso 5: Asignar la posicion de llegada por genero (M o F).
    posicionGenero(vectorClasica, cantidadCorredoresClasica);
    posicionGenero(vectorNonStop, cantidadCorredoresNonStop);

    //Paso 6: Leer los vectores de ambas carreras y a partir de ellos cargar dos nuevos con las categorias que posean.
    string categoriasClasica[cantidadCorredoresClasica];
    int cantidadCategoriasClasica = 0;
    string categoriasNonStop[cantidadCorredoresNonStop];
    int cantidadCategoriasNonStop = 0;
    determinarCategorias(vectorClasica, cantidadCorredoresClasica, categoriasClasica, cantidadCategoriasClasica);
    determinarCategorias(vectorNonStop, cantidadCorredoresNonStop, categoriasNonStop, cantidadCategoriasNonStop);

    //Paso 7: Recorremos los vectores de ambas carreras y comparamos contra los vectores de categorias para asignar la posicion.
    posicionCategoria(vectorClasica, cantidadCorredoresClasica, categoriasClasica, cantidadCategoriasClasica);
    posicionCategoria(vectorNonStop, cantidadCorredoresNonStop, categoriasNonStop, cantidadCategoriasNonStop);

    //Paso 8: Calcular la diferencia de tiempos entre el corredor del 1° puesto y el resto de corredores y asignar las diferencias. Necesitamos:
    //a) Una funcion que convierta el char llegada[11] en segundos.
    //b) Una funcion que convierta el float segundos en formato HH:MM:SS.D
    //c) Una funcion que utilice las anteriores para calcular la diferencia de tiempos y asignarsela a cada jugador en el vector.
    diferenciaPrimero(vectorClasica, cantidadCorredoresClasica);
    diferenciaPrimero(vectorNonStop, cantidadCorredoresNonStop);

    //Paso 9: Calcular las diferencias de tiempo entre un corredor y su anterior.
    diferenciaAnterior(vectorClasica, cantidadCorredoresClasica);
    diferenciaAnterior(vectorNonStop, cantidadCorredoresNonStop);

    //Paso 10: Cargar el archivo de Carrera Clásica y de Carrera NonStop con mis vectores.
    cargarArchivosCarrera(archivoClasica, vectorClasica, cantidadCorredoresClasica);
    cargarArchivosCarrera(archivoNonStop, vectorNonStop, cantidadCorredoresNonStop);

    //Paso 11: Ordenar alfabeticamente los vectores de categorias.
    ordenarAlfabeticamente(categoriasClasica, cantidadCategoriasClasica);
    ordenarAlfabeticamente(categoriasNonStop, cantidadCategoriasNonStop);

    //Paso 12: Cargar los corredores al vector de podios.
    int longitudPodios = (cantidadCategoriasClasica + cantidadCategoriasNonStop)*3;
    int contadorPodios = 0;
    Podios vectorPodios[longitudPodios];
    extraerPodios(vectorPodios, contadorPodios, categoriasClasica, cantidadCategoriasClasica, vectorClasica, cantidadCorredoresClasica);
    extraerPodios(vectorPodios, contadorPodios, categoriasNonStop, cantidadCategoriasNonStop, vectorNonStop, cantidadCorredoresNonStop);

    //Paso 13: Cargar el archivo podios.
    fwrite(vectorPodios, sizeof(Podios), contadorPodios, archivoPodios);

    //Paso X: Mostrar archivos
    cout << "---------- Reporte de Carrera Clasica ----------" << endl;
    mostrarReporte(archivoClasica);
    cout << "---------- Reporte de Carrera NonStop ----------" << endl;
    mostrarReporte(archivoNonStop);
    cout << "---------- Reporte de Podios ----------" << endl;
    mostrarPodios(archivoPodios);
    fclose(archivoClasica);
    fclose(archivoNonStop);
    fclose(archivoPodios);
    return 0;    
}

void noTermino(FILE* archivo){
    RegCorredores corredores;
    //Posicionamos el puntero al inicio del archivo.
    fseek(archivo, 0, SEEK_SET);
    while(fread(&corredores, sizeof(RegCorredores), 1, archivo) == 1){
        //Comparamos hasta 3 caracteres ya que lo que le siga a DNF o DSQ es indistinto.
        if(strncmp(corredores.llegada, "DNF", 3) == 0 || strncmp(corredores.llegada, "DSQ", 3) == 0){
            strncpy(corredores.llegada, "No termino", sizeof(corredores.llegada) - 1);
            //Finalizamos con '\0' en la ultima posicion.
            corredores.llegada[sizeof(corredores.llegada) - 1] = '\0';
            //Posicionamos el puntero al inicio del registro y grabamos la llegada modificada.
            fseek(archivo, -sizeof(RegCorredores), SEEK_CUR);
            fwrite(&corredores, sizeof(RegCorredores), 1, archivo);
            //Posicionamos el puntero al inicio del registro que acabamos de grabar para continuar leyendo con normalidad.
            fseek(archivo, 0, SEEK_CUR);
        }      
    }
}

void cargarCorredores(FILE* archivo, RegCorredores vector[], int &longitud){
    //Posicionamos el puntero al inicio del archivo.
    fseek(archivo, 0, SEEK_SET);
    RegCorredores corredores;
    while(fread(&corredores, sizeof(RegCorredores), 1, archivo) == 1){
        vector[longitud].numero = corredores.numero;
        strcpy(vector[longitud].nombreApellido, corredores.nombreApellido);
        strcpy(vector[longitud].categoria, corredores.categoria);
        vector[longitud].genero = corredores.genero;
        strcpy(vector[longitud].localidad, corredores.localidad);
        strcpy(vector[longitud].llegada, corredores.llegada);
        longitud++;
    }
}

void ordenarPorTiempo(RegCorredores vector[], int longitud){
    for(int i = 0; i < longitud; i++){
        for(int j = 0; j < longitud - i - 1; j++){
            if(strcmp(vector[j].llegada, "No termino") == 0){
                RegCorredores aux = vector[j];
                vector[j] = vector[j+1];
                vector[j+1] = aux;
            }
            else{
                if (strcmp(vector[j].llegada, vector[j+1].llegada) > 0){
                RegCorredores aux = vector[j];
                vector[j] = vector[j+1];
                vector[j+1] = aux;
                } 
            }
        }
    }
}

void separarPorCarrera(RegCorredores vectorOriginal[], int longitudOriginal, ListadoCarrera vectorUno[], int &longitudUno, ListadoCarrera vectorDos[], int &longitudDos){
    for(int i = 0; i < longitudOriginal; i++){
        if(strncmp(vectorOriginal[i].categoria, "4 Refugios C", 12) == 0){
            vectorUno[longitudUno].posGeneral = longitudUno + 1;
            vectorUno[longitudUno].numero = vectorOriginal[i].numero;
            strcpy(vectorUno[longitudUno].nombreApellido, vectorOriginal[i].nombreApellido);
            strcpy(vectorUno[longitudUno].categoria, vectorOriginal[i].categoria);
            vectorUno[longitudUno].genero = vectorOriginal[i].genero;
            strcpy(vectorUno[longitudUno].localidad, vectorOriginal[i].localidad);
            strcpy(vectorUno[longitudUno].llegada, vectorOriginal[i].llegada);
            longitudUno++;
        } else{
            vectorDos[longitudDos].posGeneral = longitudDos + 1;
            vectorDos[longitudDos].numero = vectorOriginal[i].numero;
            strcpy(vectorDos[longitudDos].nombreApellido, vectorOriginal[i].nombreApellido);
            strcpy(vectorDos[longitudDos].categoria, vectorOriginal[i].categoria);
            vectorDos[longitudDos].genero = vectorOriginal[i].genero;
            strcpy(vectorDos[longitudDos].localidad, vectorOriginal[i].localidad);
            strcpy(vectorDos[longitudDos].llegada, vectorOriginal[i].llegada);
            longitudDos++;
        }       
    }
}

void posicionGenero(ListadoCarrera vector[], int longitud){
    int posMasculino = 1;
    int posFemenino = 1;
    for (int i = 0; i < longitud; i++){
        if(vector[i].genero == 'M'){
            vector[i].posGenero = posMasculino;
            posMasculino++;
        }
        else{
            vector[i].posGenero = posFemenino;
            posFemenino++;
        }
    }
}

void determinarCategorias(ListadoCarrera vector[], int longitudVector, string vectorCategoria[], int &longitudCategoria){
    for(int i = 0; i < longitudVector; i++){
        string categoriaActual = string(vector[i].categoria);
        bool existe = false;
        for(int j = 0; j < longitudCategoria; j++){
            if(categoriaActual == vectorCategoria[j]){
                existe = true;
                break;
            }
        }
        if (!existe){
            vectorCategoria[longitudCategoria] = categoriaActual;
            longitudCategoria++;
        }
    }
}

void posicionCategoria(ListadoCarrera vector[], int longitudVector, string vectorCategoria[], int longitudCategoria){
    for(int i = 0; i < longitudCategoria; i++){
        int posicion = 1;
        //Recorremos el listado de carrera i veces, siendo i la cantidad de categorias que posea la carrera.
        for (int j = 0; j < longitudVector; j++){
            string categoriaActual = string(vector[j].categoria);
            if(categoriaActual == vectorCategoria[i]){
                vector[j].posCat = posicion;
                posicion++;
            }
        }
    }
}

float convertirASegundos(char llegada[]){
    if (strcmp(llegada, "No termino") == 0){
        return -1;
    }
    //Se resta '0' a cada carácter numérico para convertirlo en su valor entero real. (ASCII)
    int horas = ((llegada[0] - '0')*10 + (llegada[1] - '0'))*3600;
    int minutos = ((llegada[3] - '0')*10 + (llegada[4] - '0'))*60;
    int segundos = (llegada[6] - '0')*10 + (llegada[7] - '0');
    float decimas = ((llegada[9] - '0'))/10.0;
    return horas + minutos + segundos + decimas;
}

void segundosAFormato(float tiempo, char llegada[]){
    int horas = tiempo/3600;
    tiempo -= horas*3600;
    int minutos = tiempo/60;
    tiempo -= minutos*60;
    int segundos = tiempo;
    int decimas = (tiempo - segundos)*10;
    //Limpiamos la llegada.
    for (int i = 0; i < 11; i++){
        llegada[i] = '\0';
    } 
    llegada[0] = horas / 10 + '0';
    llegada[1] = horas % 10 + '0';
    llegada[2] = ':';
    llegada[3] = minutos / 10 + '0';
    llegada[4] = minutos % 10 + '0';
    llegada[5] = ':';
    llegada[6] = segundos / 10 + '0';
    llegada[7] = segundos % 10 + '0';
    llegada[8] = '.';
    llegada[9] = decimas + '0';
    llegada[10] = '\0';
}

void diferenciaPrimero(ListadoCarrera vector[], int longitud){
    //Le asignamos "-" a todos los campos para que aquellos que no terminaron ya queden establecidos sin diferencias de tiempo.
    for (int i = 0; i < longitud; i++) {
        strcpy(vector[i].difPrimero, "-");
    }
    //Asignamos al #1 sus datos de diferencia de tiempo.
    float tiempoPrimero = convertirASegundos(vector[0].llegada);
    for(int i = 1; i < longitud; i++){
        float tiempoActual = convertirASegundos(vector[i].llegada);
        if (tiempoActual == -1){
            //Si el corredor no termino, no hago nada.
            continue;
        }
        float diferencia = tiempoActual - tiempoPrimero;
        segundosAFormato(diferencia, vector[i].difPrimero);
    }
}

void diferenciaAnterior(ListadoCarrera vector[], int longitud){
    //Le asignamos "-" a todos los campos para que aquellos que no terminaron ya queden establecidos sin diferencias de tiempo.
    for (int i = 0; i < longitud; i++) {
        strcpy(vector[i].difAnterior, "-");
    }
    for(int i = 1; i < longitud; i++){
        float tiempoAnterior = convertirASegundos(vector[i-1].llegada);
        float tiempoActual = convertirASegundos(vector[i].llegada);
        if(tiempoAnterior == -1 || tiempoActual == -1){
            continue;
        }
        float diferencia = tiempoActual - tiempoAnterior;
        segundosAFormato(diferencia, vector[i].difAnterior);
    }
}

void cargarArchivosCarrera(FILE* archivo, ListadoCarrera vector[], int longitud){
    fwrite(vector, sizeof(ListadoCarrera), longitud, archivo);
}

void imprimirEspacios(int cantidadEspacios){
    for(int i = 0; i < cantidadEspacios; i++){
        cout << " ";
    }
    cout << "\t";
}

void mostrarReporte(FILE* archivo){
    fseek(archivo, 0, SEEK_SET);
    ListadoCarrera carreras;
    int diferenciaEspacios = 0;
    while(fread(&carreras, sizeof(ListadoCarrera), 1, archivo) == 1){
        cout << carreras.posGeneral << "\t";
        cout << carreras.posGenero << "\t";
        cout << carreras.posCat << "\t";
        cout << carreras.numero << "\t";
        cout << carreras.nombreApellido;
        diferenciaEspacios = (sizeof(carreras.nombreApellido) - 1) - strlen(carreras.nombreApellido);
        imprimirEspacios(diferenciaEspacios);
        cout << carreras.categoria;
        diferenciaEspacios = (sizeof(carreras.categoria) - 1) - strlen(carreras.categoria);
        imprimirEspacios(diferenciaEspacios);
        cout << carreras.genero << "\t";
        cout << carreras.localidad;
        diferenciaEspacios = (sizeof(carreras.localidad) - 1) - strlen(carreras.localidad);
        imprimirEspacios(diferenciaEspacios);
        cout << carreras.llegada;
        diferenciaEspacios = (sizeof(carreras.llegada) - 1) - strlen(carreras.llegada);
        imprimirEspacios(diferenciaEspacios);
        cout << carreras.difPrimero;
        diferenciaEspacios = (sizeof(carreras.difPrimero) - 1) - strlen(carreras.difPrimero);
        imprimirEspacios(diferenciaEspacios);
        cout << carreras.difAnterior << endl;
    }
}

void ordenarAlfabeticamente(string vector[], int longitud){
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

void extraerPodios(Podios vectorPodios[], int &cantidadPodios, string categorias[], int longitudCategorias, ListadoCarrera vectorCarrera[], int longitudCarrera){
    for (int i = 0; i < longitudCategorias; i++){
        int contador = 0;
        for(int j = 0; j < longitudCarrera; j++){
            if(string(vectorCarrera[j].categoria) == categorias[i]){
                vectorPodios[cantidadPodios].posCat = vectorCarrera[j].posCat;
                vectorPodios[cantidadPodios].numero = vectorCarrera[j].numero;
                strcpy(vectorPodios[cantidadPodios].nombreApellido, vectorCarrera[j].nombreApellido);
                strcpy(vectorPodios[cantidadPodios].categoria, vectorCarrera[j].categoria);
                vectorPodios[cantidadPodios].genero = vectorCarrera[j].genero;
                strcpy(vectorPodios[cantidadPodios].localidad, vectorCarrera[j].localidad);
                strcpy(vectorPodios[cantidadPodios].llegada, vectorCarrera[j].llegada);
                cantidadPodios++;
                contador++;
                if(contador == 3){
                    break;
                }
            }
        }
    }

}

void mostrarPodios(FILE* archivo){
    fseek(archivo, 0, SEEK_SET);
    Podios podio;
    int diferenciaEspacios = 0;
    while(fread(&podio, sizeof(Podios), 1, archivo) == 1){
        cout << podio.posCat << "\t";
        cout << podio.numero << "\t";
        cout << podio.nombreApellido;
        diferenciaEspacios = (sizeof(podio.nombreApellido) - 1) - strlen(podio.nombreApellido);
        imprimirEspacios(diferenciaEspacios);
        cout << podio.categoria;
        diferenciaEspacios = (sizeof(podio.categoria) - 1) - strlen(podio.categoria);
        imprimirEspacios(diferenciaEspacios);
        cout << podio.genero << "\t";
        cout << podio.localidad;
        diferenciaEspacios = (sizeof(podio.localidad) - 1) - strlen(podio.localidad);
        imprimirEspacios(diferenciaEspacios);
        cout << podio.llegada << endl;
    }

}

