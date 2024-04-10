#include "individuo.hpp"
#include <iostream>
#include <math.h>
// Implementación del constructor de individuo
individuo::individuo(int tamCuadrado) {
    // Aquí iría la lógica para inicializar tu objeto individuo con el tamaño N
    this->tamCuadrado=tamCuadrado;
    cromosomas = *new cromosoma(tamCuadrado);
    std::cout<<cromosomas;
}

// Implementación del destructor de individuo
individuo::~individuo() {
    // Aquí iría la lógica para liberar los recursos utilizados por tu objeto individuo
}


//Implemntacion cruza
void individuo::cruza(individuo uno, individuo dos){

}



//Metodo maximizacion
int individuo::func1(std::vector<int> fil,std::vector<int> col,int diag){

    int numExitos;
    for (int i = 0; i < tamCuadrado; i++){
        if ( fil.at(i) == this->cromosomas.getNumMagico() ) numExitos++;
        if ( col.at(i) == this->cromosomas.getNumMagico() ) numExitos++;
    }
    
    if (diag==this->cromosomas.getNumMagico()) numExitos++;
    
    return numExitos;
}
//Metodo de minimizacion
bool individuo::func2(std::vector<int> fil,std::vector<int> col,int diag){
    int exitoGeneral=2*tamCuadrado+1;
    int numExitos;
    int sumafil=0;
    int sumcol=0;
    for (int i : fil){
        sumafil += abs(this->cromosomas.getNumMagico() -i );
    }
    
    for (int i : col){
        sumcol += abs(this->cromosomas.getNumMagico() -i );
    }
    
    numExitos = sumafil + sumcol + abs(this->cromosomas.getNumMagico() -diag);
    if (numExitos==0) return true;
    else return false;
}




/* 
std::ostream& operator<<(std::ostream& os, individuo indi){

} */

int main()
{
    
    individuo miPoblacion(5); 

    if(miPoblacion.func1(miPoblacion.cromosomas.sumaFilas(),miPoblacion.cromosomas.sumaColumnas(),miPoblacion.cromosomas.sumaDiagonales()))
        std::cout<<"COOOL";
        else
        std::cout<<"NOCOOOL";
    
    
    return 0;
}
