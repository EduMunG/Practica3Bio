#include "./Populacion/individuo.cpp"


int main() {
    
    // Variables
    int numPoblaciones, tamCuadrado, aptitud,opcion;

    // Vectores 
    std::vector<individuo> poblacion;
    std::vector<int> aptitudes;
    std::vector<int> enfrentados;

    std::cout << "\nIngrese el numero de poblaciones que desea generar: ";
    std::cin >> numPoblaciones;
    std::cout << "Ingrese el tamano del cuadrado para la poblacion: ";
    std::cin >> tamCuadrado;

    std::cout << "\nMenu\nCuadrado Magico por:\n1. Maximizar.\n2. Minimizar.\nSeleccione una opcion: ";
    std::cin >> opcion;

    switch (opcion)
    {
    case 1:
             std::cout << "\n1. Maximizar.\n";
            // Generar población
            for (int i = 0; i < numPoblaciones; i++) {
                individuo miPoblacion(tamCuadrado);
                poblacion.push_back(miPoblacion);
                aptitud = miPoblacion.func1(miPoblacion.cromosomas.sumaFilas(), miPoblacion.cromosomas.sumaColumnas(), miPoblacion.cromosomas.sumaDiagonales());
                aptitudes.push_back(aptitud);
                std::cout << "Aptitud de la poblacion " << i + 1 << ": " << aptitud << std::endl;
            }

            // Realizar múltiples selecciones por torneo binario
            for (int i = 0; i < numPoblaciones / 2; ++i) {
                int indicePadre1 = seleccionTorneoBinario(poblacion, aptitudes, enfrentados,opcion);

                std::cout << "\nPadre "<< i + 1 <<" seleccionado: " << indicePadre1 + 1 << std::endl;
            }
        break;
    case 2:
            std::cout<<"\n2. Minimizar.\n";
            // Generar población
            for (int i = 0; i < numPoblaciones; i++) {
                individuo miPoblacion(tamCuadrado);
                poblacion.push_back(miPoblacion);
                aptitud = miPoblacion.func2(miPoblacion.cromosomas.sumaFilas(), miPoblacion.cromosomas.sumaColumnas(), miPoblacion.cromosomas.sumaDiagonales());
                aptitudes.push_back(aptitud);
                std::cout << "Aptitud de la poblacion " << i + 1 << ": " << aptitud << std::endl;
            }

            // Realizar múltiples selecciones por torneo binario
            for (int i = 0; i < numPoblaciones / 2; ++i) {
                int indicePadre1 = seleccionTorneoBinario(poblacion, aptitudes, enfrentados,opcion);

                std::cout << "\nPadre "<< i + 1 <<" seleccionado: " << indicePadre1 + 1 << std::endl;
            }
        break;
    default:
        break;
    }

    

    

    return 0;
}

