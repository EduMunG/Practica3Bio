#include "individuo.hpp"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <random>
#include <vector>


// Implementación del constructor de individuo
individuo::individuo(int tamCuadrado)
{
    // Aquí iría la lógica para inicializar tu objeto individuo con el tamaño N
    this->tamCuadrado = tamCuadrado;
    cromosomas = *new cromosoma(tamCuadrado);
    std::cout << cromosomas;
}

// Implementación del destructor de individuo
individuo::~individuo()
{
    // Aquí iría la lógica para liberar los recursos utilizados por tu objeto individuo
}

// Implemntacion cruza
void individuo::cruza(individuo uno, individuo dos)
{
}

// Metodo maximizacion
int individuo::func1(std::vector<int> fil, std::vector<int> col, int diag)
{

    int numExitos;
    int numMagico = this->cromosomas.getNumMagico();;
   
    for (int i = 0; i < tamCuadrado; i++)
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
    for (int i : fil)
    {
        sumafil += abs(this->cromosomas.getNumMagico() - i);
    }

    for (int i : col)
    {
        sumcol += abs(this->cromosomas.getNumMagico() - i);
    }

    numExitos = sumafil + sumcol + abs(this->cromosomas.getNumMagico() - diag);

    return numExitos;
}



int seleccionTorneoBinario(std::vector<individuo> &poblacion, std::vector<int> &aptitudes, std::vector<int> &enfrentados, int opcion) {

    // Seleccionar dos índices aleatorios diferentes que no estén en el vector de enfrentamientos
    std::random_device rd;
    std::mt19937 gen(rd());
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

    std::cout << "\nEnfrentamiento " << indice1 + 1 << " vs " << indice2 + 1;

    if (opcion == 1)
    {
        if (aptitudes[indice1] > aptitudes[indice2]) return indice1;
        else 
            return indice2;
            
    }
    else{
         if (aptitudes[indice1] < aptitudes[indice2]) return indice1;
        else 
            return indice2;
    }
    
}


