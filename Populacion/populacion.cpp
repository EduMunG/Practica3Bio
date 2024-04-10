#include "populacion.hpp"
#include <iostream>

// Implementación del constructor de populacion
populacion::populacion(int N) {
    // Aquí iría la lógica para inicializar tu objeto populacion con el tamaño N
}

// Implementación del destructor de populacion
populacion::~populacion() {
    // Aquí iría la lógica para liberar los recursos utilizados por tu objeto populacion
}


int main()
{
    int n;
    std::cout << "Ingresa la dimensión de la población: ";
    std::cin >> n;

    populacion miPoblacion(n); 
    
    return 0;
}
