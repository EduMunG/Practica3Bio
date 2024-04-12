#include "individuo.hpp"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <random>
#include <vector>

//Clases globales de generacion aleatoria 
static std::random_device rd;
static std::mt19937 gen(rd());

// Implementación del constructor de individuo
individuo::individuo(int tamCuadrado)
{
    // Aquí iría la lógica para inicializar tu objeto individuo con el tamaño N
    cromosomas = *new cromosoma(tamCuadrado);
    setAptitud(0);

    std::cout << "Cuadrado generado:" << cromosomas;
}


    individuo::individuo():
    cromosomas(*new cromosoma),
    aptitud(0){}

// Implementación del destructor de individuo
individuo::~individuo()
{
    // Aquí iría la lógica para liberar los recursos utilizados por tu objeto individuo
/*     setTamCuadrado(0);
    delete &cromosomas;
    setAptitud(0); */
}



    void individuo:: setCromosoma(cromosoma cromosoma){this->cromosomas=cromosoma; }
    void individuo:: setAptitud(int aptitud){this->aptitud=aptitud;}
    //GETTERRS
    cromosoma individuo:: getCromosoma(void){return this->cromosomas;}
    int individuo:: getAptitud(void){return this->aptitud;}   




    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////METODOS/////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////

// Metodo maximizacion
int individuo::func1(std::vector<int> fil, std::vector<int> col, int diag)
{

    int numExitos=0;
    int numMagico = this->cromosomas.getNumMagico();;
   
    for (int i = 0; i < cromosomas.getTamCuadrado(); i++)
    {
        if (fil.at(i) == numMagico)
            numExitos++;
        if (col.at(i) == numMagico)
            numExitos++;
    }

    if (diag == numMagico)
        numExitos++;

    return numExitos;
}

// Metodo de minimizacion
int individuo::func2(std::vector<int> fil, std::vector<int> col, int diag)
{

    int numExitos;
    int sumafil = 0;
    int sumcol = 0;
    for (int i : fil) {sumafil += abs(this->cromosomas.getNumMagico() - i);}

    for (int i : col) {sumcol += abs(this->cromosomas.getNumMagico() - i);}

    numExitos = sumafil + sumcol + abs(this->cromosomas.getNumMagico() - diag);

    return numExitos;
}

    




int individuo::seleccionTorneoBinario(std::vector<int> &enfrentados, std::vector<individuo>& poblacion) {
    
    // Seleccionar dos índices aleatorios diferentes que no estén en el vector de enfrentamientos

    std::uniform_int_distribution<int> dist(0, poblacion.size() - 1);

    int indice1 = dist(gen);
    while (std::find(enfrentados.begin(), enfrentados.end(), indice1) != enfrentados.end()) {
        indice1 = dist(gen);
    }

    int indice2 = dist(gen);
    while (indice2 == indice1 || std::find(enfrentados.begin(), enfrentados.end(), indice2) != enfrentados.end()) {
        indice2 = dist(gen);
    }

    // Registrar los índices enfrentados
    enfrentados.push_back(indice1);
    enfrentados.push_back(indice2);

    std::cout << "\nEnfrentamientos " << indice1 << " vs " << indice2 ;
    std::cout << "\nAptitud : " << poblacion.at(indice1).getAptitud() << " vs " << poblacion.at(indice2).getAptitud() ;

    // Comparar las aptitudes de los dos individuos seleccionados
    if (poblacion.at(indice1).getAptitud()  > poblacion.at(indice2).getAptitud()) {
        return indice1;
    } else {
        return indice2;
    }
}







/*     std::ostream& operator<<(std::ostream& os, individuo indi){

    }


 */

// while (exitosGeneral!=numexitos)
//     {

//         torneobinario(miPoblacion.func1(miPoblacion.cromosomas.sumaFilas(),miPoblacion.cromosomas.sumaColumnas(),miPoblacion.cromosomas.sumaDiagonales())

//     }
