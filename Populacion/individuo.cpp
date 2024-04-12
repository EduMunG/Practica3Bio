#include "individuo.hpp"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <random>
#include <vector>

//Clases globales de generacion aleatoria 
std::random_device rd;
std::mt19937 gen(rd());

// Implementación del constructor de individuo
individuo::individuo(int tamCuadrado)
{
    // Aquí iría la lógica para inicializar tu objeto individuo con el tamaño N
    setTamCuadrado(tamCuadrado);
    cromosomas = *new cromosoma(tamCuadrado);
    setAptitud(0);

    std::cout << "Cuadrado generado:" << cromosomas;
}

// Implementación del destructor de individuo
individuo::~individuo()
{
    // Aquí iría la lógica para liberar los recursos utilizados por tu objeto individuo
/*     setTamCuadrado(0);
    delete &cromosomas;
    setAptitud(0); */
}



    void individuo:: setCromosoma(cromosoma cromosoma){this->cromosomas=cromosoma;}
    void individuo:: setTamCuadrado(int tamCuadrado){this->tamCuadrado=tamCuadrado;}
    void individuo:: setAptitud(int aptitud){this->aptitud=aptitud;}
    //GETTERRS
    cromosoma individuo:: getCromosoma(void){return this->cromosomas;}
    int individuo:: getTamCuadrado(void){return this->tamCuadrado;}
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

    int numExitos = 0;
    int numMagico = this->cromosomas.getNumMagico();;
   

    for (int i = 0; i < tamCuadrado; i++)
    {
        if (fil.at(i) == numMagico)
            numExitos++;
        
        if (col.at(i) == numMagico)
            numExitos++;
        
    }

    if(diag == numMagico)
        numExitos++;
    

    return numExitos;
}

// Metodo de minimizacion
int individuo::func2(std::vector<int> fil, std::vector<int> col, int diag)
{

    int numExitos = 0;
    int sumafil = 0;
    int sumcol = 0;
    for (int i : fil) {sumafil += abs(this->cromosomas.getNumMagico() - i);}

    for (int i : col) {sumcol += abs(this->cromosomas.getNumMagico() - i);}

    numExitos = sumafil + sumcol + abs(this->cromosomas.getNumMagico() - diag);

    return numExitos;
}

// Implemntacion cruza
void individuo::cruza(std::vector<individuo> &poblacion){

    //Para escoger las distancias (escoger el segmento)
    std::uniform_int_distribution<int> dist(0, poblacion.size() - 1);
    //PAra guardar los hijos
    std::vector<individuo> hijos;
    //Un iterador que va por cada individuo en la poblacion
    std::vector<individuo>::iterator it = poblacion.begin();

    int pos1, pos2;
    //Generamos las posiciones;
    pos1= dist(gen);
    pos2= dist(gen);

    while (pos1==pos2)
        pos2=dist(gen);

    std::vector<int> seccion1;
    std::vector<int> seccion2;


}




void seleccionarPadres(std::vector<individuo>& poblacion, int numPoblaciones) {
    std::vector<individuo> nuevosPadres;
    std::vector<int> enfrentados;
    for (int i = 0; i < numPoblaciones / 2; ++i) {
        int indiceGanador = poblacion.at(i).seleccionTorneoBinario(enfrentados, poblacion);
        nuevosPadres.push_back(poblacion[indiceGanador]);

        std::cout << "\nPadre " << i <<" seleccionado:" << std::endl;
        std::cout << "Indice: " << indiceGanador  << std::endl;
        std::cout << "Cromosoma Ganador: " << poblacion[indiceGanador].getCromosoma() << std::endl;
    }
    poblacion = nuevosPadres; // Reemplaza la población antigua con los ganadores
    std::cout << std::endl << "-----------------------------------------"<< std::endl;
    std::cout << "Poblacion restante: " << poblacion.size() << std::endl;
    std::cout << std::endl << "-----------------------------------------"<< std::endl;
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

    // Comparar las aptitudes de los dos individuos seleccionados
    if (poblacion.at(indice1).getAptitud()  > poblacion.at(indice2).getAptitud()) {
        return indice1;
    } else {
        return indice2;
    }
}







    std::ostream& operator<<(std::ostream& os, individuo indi){

    }


int main() {
    int numPoblaciones, tamCuadrado;
    std::cout << "Ingrese el numero de poblaciones que desea generar: ";
    std::cin >> numPoblaciones;
    std::cout << "Ingrese el tamano del cuadrado para la poblacion: ";
    std::cin >> tamCuadrado;

    std::vector<individuo> poblacion;

    // Generar población inicial
    for (int i = 0; i < numPoblaciones; i++) {
        poblacion.push_back(*new individuo(tamCuadrado));
        poblacion.at(i).setAptitud(poblacion.at(i).func1(poblacion.at(i).getCromosoma().sumaFilas(), poblacion.at(i).getCromosoma().sumaColumnas(), poblacion.at(i).getCromosoma().sumaDiagonales()));
        std::cout << "\nAptitud de la poblacion evaluada en la Funcion 1 (Maximizar) " << i + 1 << ": " << poblacion.at(i).getAptitud() << std::endl;
    }

    std::cout << std::endl << "-----------------------------------------" << std::endl;
    std::cout << "Tamano de la poblacion inicial: " << poblacion.size();
    std::cout << std::endl << "-----------------------------------------" << std::endl;

    // Realizar múltiples selecciones por torneo binario
    seleccionarPadres(poblacion, numPoblaciones);

    

    return 0;
}
