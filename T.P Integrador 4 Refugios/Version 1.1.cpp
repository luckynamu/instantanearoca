#include <iostream>
#include <cstring>
using namespace std;

struct RegCorredores{
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

struct CorredoresCiudad{
    int numero;
    char nombreApellido[50];
    char localidad[40];
    char ciudad[30];
};

struct CorredoresCiudadInfo{
    int numero;
    char nombreApellido[50];
    char localidad[40];
    char ciudad[30];
    char llegada[11];
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
void cargarCorredoresCiudad(FILE* archivo, CorredoresCiudadInfo vector[], int &longitud);
void cargarLlegada(CorredoresCiudadInfo vectorCiudad[], int longitudCorredoresCiudad, RegCorredores vectorCorredores[], int longitudCorredores);
void ordenarPorLocalidadCiudad(CorredoresCiudadInfo vectorCiudad[], int longitud);
int cantidadDigitos(int n);
void reporteCiudades(CorredoresCiudadInfo vector[], int longitud);

int main(){
    FILE *archivoCorredores = fopen("C:/Users/mvpas/Documents/Universidad/Algoritmos y Estructuras de Datos/Archivos de TP/Archivo corredores 4Refugios.bin", "rb+");
    if (!archivoCorredores){
        cout << "No se pudo abrir el archivo Corredores 4Refugios.bin\n";
        return 1;
    }

    FILE *archivoClasica = fopen("C:/Users/mvpas/Documents/Universidad/Algoritmos y Estructuras de Datos/Archivos de TP/clasica.bin", "wb+");
    if (!archivoClasica){
        cout << "No se pudo abrir el archivo clasica.bin\n";
        return 1;
    }

    FILE *archivoNonStop = fopen("C:/Users/mvpas/Documents/Universidad/Algoritmos y Estructuras de Datos/Archivos de TP/nonStop.bin", "wb+");
    if (!archivoNonStop){
        cout << "No se pudo abrir el archivo nonStop.bin\n";
        return 1;
    }
    
    FILE *archivoPodios = fopen("C:/Users/mvpas/Documents/Universidad/Algoritmos y Estructuras de Datos/Archivos de TP/podios.bin", "wb+");
    if (!archivoPodios){
        cout << "No se pudo abrir el archivo podios.bin\n";
        return 1;
    }

    FILE *archivoCiudades = fopen("C:/Users/mvpas/Documents/Universidad/Algoritmos y Estructuras de Datos/Archivos de TP/Ciudades.bin", "rb");
    if (!archivoCiudades){
        cout << "No se pudo abrir el archivo Ciudades.bin\n";
        return 1;
    }

    //Paso 1: Reemplazar "DNF", "DNF (NL)" y "DSQ (FE)" en el archivoCorredores por "No termino". Modificamos el campo char llegada[11].
    noTermino(archivoCorredores);

    //Paso 2: Cargar todos los corredores en un vector.
    RegCorredores vectorCorredores[2000];
    int cantidadCorredores = 0;
    cargarCorredores(archivoCorredores, vectorCorredores, cantidadCorredores);

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

    //Paso 14: Leemos el archivo Ciudades y cargamos sus datos a un vector.
    CorredoresCiudadInfo vectorCorredoresCiudad[2000];
    int cantidadCorredoresCiudades = 0;
    cargarCorredoresCiudad(archivoCiudades, vectorCorredoresCiudad, cantidadCorredoresCiudades);

    //Paso 15: Para cada corredor, buscar en el vector original utilizando su numero, el tiempo de llegada.
    cargarLlegada(vectorCorredoresCiudad, cantidadCorredoresCiudades, vectorCorredores, cantidadCorredores);

    //Paso 16: Ordenamos el vector CorredoresCiudad por localidad y luego por ciudad para agrupar a los corredores que pertenecen al mismo lugar.
    ordenarPorLocalidadCiudad(vectorCorredoresCiudad, cantidadCorredoresCiudades);
    
    //Paso 17: Mostrar el reporte de cada localidad y ciudad.
    cout << "---------- Reporte de Corredores por Ciudad ----------" << endl;
    reporteCiudades(vectorCorredoresCiudad, cantidadCorredoresCiudades);
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

int cantidadDigitos(int n){
    if (n == 0){
        return 1;
    }
    int digitos = 0;
    if (n < 0){
        digitos++;
        n = -n;
    }
    while (n > 0){
        digitos++;
        n /= 10;
    }
    return digitos;
}

void mostrarReporte(FILE* archivo){
    fseek(archivo, 0, SEEK_SET);
    ListadoCarrera carreras;
    //Establecemos los encabezados y los alineamos.
    cout << "Pos. Gral.\t";
    cout << "Pos. Gen.\t";
    cout << "Pos. Cat.\t";
    cout << "Nro.\t";
    cout << "Nombre y apellido";
    imprimirEspacios(sizeof(carreras.nombreApellido) - strlen("Nombre y apellido"));
    cout << "Categoria";
    imprimirEspacios(sizeof(carreras.categoria) - strlen("Categoria"));
    cout << "Genero\t";
    cout << "Localidad";
    imprimirEspacios(sizeof(carreras.localidad) - strlen("Localidad"));
    cout << "Total";
    imprimirEspacios(sizeof(carreras.llegada) - strlen("Total"));
    cout << "Dif. Primero";
    imprimirEspacios(sizeof(carreras.difPrimero) - strlen("Dif. Primero"));
    cout << "Dif. Anterior" << endl;

    while(fread(&carreras, sizeof(ListadoCarrera), 1, archivo) == 1){
        cout << carreras.posGeneral;
        imprimirEspacios(strlen("Pos. Gral.") - cantidadDigitos(carreras.posGeneral));
        cout << carreras.posGenero;
        imprimirEspacios(strlen("Pos. Gen.") - cantidadDigitos(carreras.posGenero));
        cout << carreras.posCat;
        imprimirEspacios(strlen("Pos. Cat.") - cantidadDigitos(carreras.posCat));
        cout << carreras.numero;
        imprimirEspacios(strlen("Nro.") - cantidadDigitos(carreras.numero));
        cout << carreras.nombreApellido;
        imprimirEspacios(sizeof(carreras.nombreApellido) - strlen(carreras.nombreApellido));
        cout << carreras.categoria;
        imprimirEspacios(sizeof(carreras.categoria) - strlen(carreras.categoria));
        cout << carreras.genero;
        imprimirEspacios(strlen("Genero") - 1);
        cout << carreras.localidad;
        imprimirEspacios(sizeof(carreras.localidad) - strlen(carreras.localidad));
        cout << carreras.llegada;
        imprimirEspacios(sizeof(carreras.llegada) - strlen(carreras.llegada));
        cout << carreras.difPrimero;
        imprimirEspacios(sizeof(carreras.difPrimero) - strlen(carreras.difPrimero));
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
    //Establecemos los encabezados y los alineamos.
    cout << "Pos.\t";
    cout << "Nro.\t";
    cout << "Nombre y apellido";
    imprimirEspacios(sizeof(podio.nombreApellido) - strlen("Nombre y apellido"));
    cout << "Categoria";
    imprimirEspacios(sizeof(podio.categoria) - strlen("Categoria"));
    cout << "Genero\t";
    cout << "Localidad";
    imprimirEspacios(sizeof(podio.localidad) - strlen("Localidad"));
    cout << "Total" << endl;

    int contador = 0;

    while(fread(&podio, sizeof(Podios), 1, archivo) == 1){
        cout << podio.posCat;
        imprimirEspacios(strlen("Pos.") - cantidadDigitos(podio.posCat));
        cout << podio.numero;
        imprimirEspacios(strlen("Nro.") - cantidadDigitos(podio.numero));
        cout << podio.nombreApellido;
        imprimirEspacios(sizeof(podio.nombreApellido) - strlen(podio.nombreApellido));
        cout << podio.categoria;
        imprimirEspacios(sizeof(podio.categoria) - strlen(podio.categoria));
        cout << podio.genero;
        imprimirEspacios(strlen("Genero") - 1);
        cout << podio.localidad;
        imprimirEspacios(sizeof(podio.localidad) - strlen(podio.localidad));
        cout << podio.llegada << endl;
        contador++;
        //Se muestra una linea separadora cada vez que se cambia de categoria.
        if(contador == 3){
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            contador = 0;
        }
    }
}

void cargarCorredoresCiudad(FILE* archivo, CorredoresCiudadInfo vector[], int &longitud){
    CorredoresCiudad corredores;
    longitud = 0;
    while(fread(&corredores, sizeof(CorredoresCiudad), 1, archivo) == 1){
        vector[longitud].numero = corredores.numero;
        strcpy(vector[longitud].localidad, corredores.localidad);
        strcpy(vector[longitud].ciudad, corredores.ciudad);
        longitud++;
    }
}

void cargarLlegada(CorredoresCiudadInfo vectorCiudad[], int longitudCorredoresCiudad, RegCorredores vectorCorredores[], int longitudCorredores){
    for(int i = 0; i < longitudCorredoresCiudad; i++){
        for(int j=0; j < longitudCorredores; j++){
            if(vectorCiudad[i].numero == vectorCorredores[j].numero){
                strcpy(vectorCiudad[i].llegada, vectorCorredores[j].llegada);  
                break;             
            }
        }
    }    
}

void ordenarPorLocalidadCiudad(CorredoresCiudadInfo vectorCiudad[], int longitud){
    for (int i = 0; i < longitud; i++ ){
        for (int j = 0; j < longitud - i - 1; j++){
            if (strcmp(vectorCiudad[j].localidad, vectorCiudad[j+1].localidad) > 0){
                CorredoresCiudadInfo auxiliar = vectorCiudad[j];
                vectorCiudad[j] = vectorCiudad[j+1];
                vectorCiudad[j+1] = auxiliar;
            }
            else if(strcmp(vectorCiudad[j].localidad, vectorCiudad[j+1].localidad) == 0){
                if (strcmp(vectorCiudad[j].ciudad, vectorCiudad[j+1].ciudad) > 0){
                    CorredoresCiudadInfo auxiliar = vectorCiudad[j];
                    vectorCiudad[j] = vectorCiudad[j+1];
                    vectorCiudad[j+1] = auxiliar;
                }
            }
        }
    }
}

void reporteCiudades(CorredoresCiudadInfo vector[], int longitud){
    cout << "Localidad";
    imprimirEspacios(sizeof(vector[0].localidad) - strlen("Localidad"));
    cout << "Ciudad";
    imprimirEspacios(sizeof(vector[0].ciudad) - strlen("Ciudad"));
    cout << "Cantidad de Corredores\t";
    cout << "Tiempo Promedio" << endl;

    char localidadActual[40];
    char ciudadActual[30];
    //Copiamos la primer ciudad y localidad del vector.
    strcpy(localidadActual, vector[0].localidad);
    strcpy(ciudadActual, vector[0].ciudad);
    //Establecemos los contadores.
    int corredoresLocalidad = 0;
    float tiempoTotalLocalidad = 0;
    int corredoresCiudad = 0;
    float tiempoTotalCiudad = 0;

    bool mostrarLocalidad = true;

    for (int i = 0; i < longitud; i++){
        float tiempo = convertirASegundos(vector[i].llegada);
        if (tiempo != -1) {
            tiempoTotalCiudad += tiempo;
            tiempoTotalLocalidad += tiempo;
        }
        corredoresCiudad++;
        corredoresLocalidad++;
        
        bool cambiaCiudad = (i == longitud - 1) || strcmp(vector[i].ciudad, vector[i + 1].ciudad) != 0;
        bool cambiaLocalidad = (i == longitud - 1) || strcmp(vector[i].localidad, vector[i + 1].localidad) != 0;

        //Si cambia la ciudad en la siguiente posicion, mostramos sus totales y promedios.
        if (cambiaCiudad){
            float promedioCiudad = tiempoTotalCiudad / corredoresCiudad;
            if (mostrarLocalidad){
                cout << localidadActual;
                imprimirEspacios(sizeof(vector[i].localidad) - strlen(localidadActual));
                mostrarLocalidad = false;
            }else{
                imprimirEspacios(sizeof(vector[i].localidad));
            }
            cout << ciudadActual;
            imprimirEspacios(sizeof(vector[i].ciudad) - strlen(ciudadActual));
            cout << corredoresCiudad;
            imprimirEspacios(strlen("Cantidad de Corredores") - cantidadDigitos(corredoresCiudad));
            char tiempoPromedioCiudad[11];
            segundosAFormato(promedioCiudad, tiempoPromedioCiudad);
            cout << tiempoPromedioCiudad << endl;

            corredoresCiudad = 0;
            tiempoTotalCiudad = 0;
            if (!cambiaLocalidad && (i + 1) < longitud){
                strcpy(ciudadActual, vector[i+1].ciudad);
            }
        }
        //Si cambia la localidad en la siguiente posicion, mostramos sus totales y promedios.
        if (cambiaLocalidad){
            float promedioLocalidad = tiempoTotalLocalidad / corredoresLocalidad;
            cout << "Total " << localidadActual;
            imprimirEspacios(sizeof(vector[i].localidad) - strlen(localidadActual) - strlen("Total "));
            imprimirEspacios(sizeof(vector[i].ciudad));
            cout << corredoresLocalidad;
            imprimirEspacios(strlen("Cantidad de Corredores") - cantidadDigitos(corredoresLocalidad));
            char tiempoPromedioLocalidad[11];
            segundosAFormato(promedioLocalidad, tiempoPromedioLocalidad);
            cout << tiempoPromedioLocalidad << endl;
            cout << "----------" << endl;

            corredoresLocalidad = 0;
            tiempoTotalLocalidad = 0;
            if (i + 1 < longitud) {
                strcpy(localidadActual, vector[i + 1].localidad);
                strcpy(ciudadActual, vector[i + 1].ciudad);
            }
            mostrarLocalidad = true;
        }
    }
}