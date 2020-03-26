#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <conio.h>

using namespace std;

// estructura para encapsular los datos y manejarlos mas facil
struct dato
{
    char *nit = NULL;
    char *fecha = NULL;
    double total;
};

int main()
{
    string cadena;
    ifstream leer("proye.csv");
    vector<dato> cadenas;
    vector<dato> cadenas2;
    vector<dato> sumaPorNit;

    // lleno los vectores con todos los datos del csv
    while(!leer.eof())
    {
        leer>>cadena;

        // puntero char, el tamanio debe ser el numero de caracteres que contiene cada linea del archivo csv
        char * cstr = new char[cadena.length() + 1]; // mas uno por el caracter de escape (\n)
        strcpy(cstr, cadena.c_str()); // copio la cadena al puntero char

        // me creo una variable de tipo dato (el que acabo de crear arriba)
        dato d;
        d.nit = strtok(cstr, ","); // ahora divido la cadena y me aseguro de capturar el NIT
        d.fecha = strtok(NULL, ","); // saco la fecha
        d.total = strtod(strtok(NULL, ","), NULL); // ahora extraigo el total y al mismo tiempo lo convierto a float

        // agrego el dato a cada vector
        cadenas.push_back(d);
        cadenas2.push_back(d);

    }
    leer.close();// me aseguro de cerrar el archivo, porque ya no lo necesito

    /*posteriormente itero un doble for (uno para cada vector), para ir comparando de uno
     * en uno cada NIT en busca de alguno repetido, de ser asi, se va sumando
     * cada total si y solo si el NIT es repetido. Uso dos vectores porque no se puede
     * tener abierto el archivo dos veces al mismo tiempo
     */
    // variables auxiliares
    char * nit, * nit2; // para obtener los nit y compararlos
    double total = 0.00D, total2 = 0.0D; // para obtener los totales del csv y sumarlos
    int vecesRetido = 0; // servira para contar cuantas veces se repiten los Nits

    for(int it = 0; it < cadenas.size(); it++)// primer vector de cadenas
    {
        // salvo el nit y el total
        nit = cadenas[it].nit;
        char *fecha = cadenas[it].fecha; // tambien saco la fecha solo para mostrarla despues
        total = cadenas[it].total;

        for(int it2 = 0; it2 < cadenas2.size(); it2++)// segundo vector
        {

            // ACA HAGO LO MISMO QUE ARRIBA
            nit2 = cadenas2[it2].nit;
            total2 = cadenas2[it2].total;

            // compruebo si son iguales
            if( strcmp(nit, nit2) == 0)
            {
                vecesRetido++; // aumento en uno

                // elimino el repetido porque ya lo conte, esto para evitar que se vuelva a contar
                cadenas2.erase(cadenas2.begin()+it2);

                // si se repite mas de una vez lo sumamos
                if (vecesRetido > 1)
                {
                    //sumar
                    total += total2; // poner '+=' es igual a 'total = total + total2'

                }
            }
        }// for uno


        // validar que se agregar solo los que se contaron al menos una vez
        if(vecesRetido > 0)
        {
            dato d;
            d.nit = nit; // asigno el nit que acabo de contar
            d.fecha = fecha; // la fecha
            d.total = total; // asigno el total, el cual puede tener o no acumulada la suma, dependiendo si habian nit repetidos...
            sumaPorNit.push_back(d); // agrego el dato al vector
        }

        vecesRetido = 0; // reiniciamos el contador

    }// for dos

    // ahora toca presentar el resultado
    cout << "\tNIT\t\t\t" << "FECHA\t\t\t" << "TOTAL VENDIDO"<< endl;
    for(vector<dato>::iterator x = sumaPorNit.begin(); x != sumaPorNit.end(); x++)
    {
        cout<<"\t"<< x->nit <<"\t\t" << x->fecha << "\t\t" << x->total << endl;
    }

    getch();
    return 0;

}
