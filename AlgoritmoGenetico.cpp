#include "./Populacion/individuo.cpp"


void mutar(std::vector<individuo> &poblacion){
    if (poblacion.size() < 2) {
        std::cout << "Poblacion no es suficiente para mutar";
        return;
    }
    
    for (int i = 0; i < poblacion.size(); i++)
    {
        poblacion.at(i).getCromosoma().mutacionInsersion();
    }
    

}

// Implemntacion cruza
void cruzaPMX(std::vector<individuo> &poblacion) {
    if (poblacion.size() < 2) {
        std::cout << "Poblacion no es suficiente para cruce";
        return;
    }

    std::cout << std::endl << "-----------------------------------------" << std::endl;
    std::cout << "Cruza con poblacion: " << poblacion.size() << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<individuo> hijos;

    // Un iterador que va por cada individuo en la poblacion
    std::vector<individuo>::iterator itDePoblacion = poblacion.begin();
    while (itDePoblacion != poblacion.end() - 1) {
        cromosoma cromo1 = itDePoblacion->getCromosoma();
        cromosoma cromo2 = (itDePoblacion + 1)->getCromosoma();
        std::cout<<"\nCromosoma 1: "<<cromo1;
        std::cout<<"\nCromosoma 2: "<<cromo2;

        std::vector<int> cromosoma1 = cromo1.getVectorSuma();
        std::vector<int> cromosoma2 = cromo2.getVectorSuma();
        int tamCuad = cromo1.getTamCuadrado();

        int maxIndex = cromosoma1.size() - 1;
        std::uniform_int_distribution<int> dist(1, maxIndex);
        int pos1 = dist(gen);
        int pos2 = dist(gen);

        if (pos1 > pos2) std::swap(pos1, pos2);  // Asegurar que pos1 es menor que pos2
        std::cout<<std::endl<<"Posicion 1: "<<pos1<<std::endl<<"Posicion 2: "<<pos2;
        // Crear cromosomas hijos inicializados con -1 para representar posiciones no asignadas
        std::vector<int> hijo1(cromosoma1.size(), -1), hijo2(cromosoma2.size(), -1);
        
        std::cout<<std::endl<<"Hijo 1 : "<<std::endl;
        for (int i : hijo1)
            std::cout<<i<<" ";
        std::cout<<std::endl<<"Hijo 2 : "<<std::endl;
        for (int i : hijo2)
            std::cout<<i<<" ";

        //Guardar las secciones
        std::vector<int> seccion1;
        std::vector<int> seccion2;

        // Mapear secciones entre pos1 y pos2
        for (int i = pos1; i <= pos2; ++i) {
            hijo1[i] = cromosoma2[i];
            hijo2[i] = cromosoma1[i];
            seccion1.push_back(cromosoma2[i]); //Elementos del cromosoma 2 en hijo 1
            seccion2.push_back(cromosoma1[i]); //Elementos del comromsa 1 en hijo 2
        }   

        std::cout<<std::endl<<"seccion 1 : "<<std::endl;
        for (int i : seccion1)
            std::cout<<i<<" ";
        std::cout<<std::endl<<"seccion 2 : "<<std::endl;
        for (int i : seccion2)
            std::cout<<i<<" ";


        std::cout<<std::endl<<"Hijo 1 despues de mapeo : "<<std::endl;
        for (int i : hijo1)
            std::cout<<i<<" ";
        std::cout<<std::endl<<"Hijo 2 despues de mapeo: "<<std::endl;
        for (int i : hijo2)
            std::cout<<i<<" ";

        // Rellenar los elementos restantes del cromosoma
/*         for (int i = 0; i < cromosoma1.size(); ++i) {
            if (i < pos1 || i > pos2 ) {
                hijo1[i] = cromosoma2[i];
                hijo2[i] = cromosoma1[i];
            }
        } */
for (int i = 0; i < cromosoma1.size(); i++) {
    if ((i < pos1 || i > pos2) && std::find(seccion1.begin(), seccion1.end(), cromosoma2[i]) == seccion1.end()) {
        hijo1[i] = cromosoma2[i];
    }
    if ((i < pos1 || i > pos2) && std::find(seccion2.begin(), seccion2.end(), cromosoma1[i]) == seccion2.end()) {
        hijo2[i] = cromosoma1[i];
    }
}

// Ciclo para llenar los huecos con valores no duplicados
for (int i = 0; i < hijo1.size(); i++) {
    if (hijo1[i] == -1) { // Si el lugar está sin llenar
        for (int val = 1; val <= cromosoma1.size(); val++) { // Intenta encontrar un valor no usado
            if (std::find(hijo1.begin(), hijo1.end(), val) == hijo1.end()) {
                hijo1[i] = val;
                break;
            }
        }
    }
    if (hijo2[i] == -1) { // Repite para hijo2
        for (int val = 1; val <= cromosoma2.size(); val++) {
            if (std::find(hijo2.begin(), hijo2.end(), val) == hijo2.end()) {
                hijo2[i] = val;
                break;
            }
        }
    }
}

        std::cout<<std::endl<<"Hijo 1 despues de relleno : "<<std::endl;
        for (int i : hijo1)
            std::cout<<i<<" ";
        std::cout<<std::endl<<"Hijo 2 despues de relleno: "<<std::endl;
        for (int i : hijo2)
            std::cout<<i<<" ";

        // Crear nuevos individuos con los cromosomas cruzados
        individuo nuevoHijo1, nuevoHijo2;
        nuevoHijo1.setCromosoma(cromosoma(hijo1, tamCuad));
        std::cout<<std::endl<<" Nuevo Hijo: "<<nuevoHijo1.getCromosoma();
        nuevoHijo2.setCromosoma(cromosoma(hijo2, tamCuad));
        std::cout<<std::endl<<" Nuevo Hijo: "<<nuevoHijo2.getCromosoma();

        // Añadir los hijos a la lista de hijos
        hijos.push_back(nuevoHijo1);
        hijos.push_back(nuevoHijo2);

        itDePoblacion ++; // Avanzar al siguiente par de individuos
    }
/*     for( individuo hijo: hijos)
        poblacion.push_back(hijo); // Anadimos los hijos
 */
    poblacion= hijos;
     std::cout << std::endl << "-----------------------------------------" << std::endl;
    std::cout << "Tamano de la nueva poblacion " << poblacion.size() << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
}

void seleccionarPadres(std::vector<individuo>& poblacion, int numPoblaciones) {
    if (poblacion.size()<2){
        std::cout<<" Poblacion no es suficiente para la seleccion ";
        return;
    }
    
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
    std::cout <<  "-----------------------------------------"<< std::endl;
}


void inicializarPoblacion(std::vector<individuo>& poblacion, int numPoblaciones, int tamCuadrado) {
    for (int i = 0; i < numPoblaciones; i++) {
        individuo ind(tamCuadrado);
        ind.setAptitud(ind.func1(ind.getCromosoma().sumaFilas(), ind.getCromosoma().sumaColumnas(), ind.getCromosoma().sumaDiagonales()));
        poblacion.push_back(ind);
        std::cout << "\nAptitud de la poblacion evaluada en la Funcion 2 (Maximizar) " << i + 1 << ": " << ind.getAptitud() << std::endl;
    }
}





int main() {
    int numPoblaciones, tamCuadrado;
    std::cout << "Ingrese el numero de poblaciones que desea generar: ";
    std::cin >> numPoblaciones;
    int numintentos=0;
    while (numPoblaciones<2)
    {
        numintentos++;
        std::cout<<" Poblacion no es suficiente para algoritmo genetico. Escoga otra: ";
        std::cin>>numPoblaciones;
        if (numintentos>3){
        std::cout<<" Muchos intentos fallidos. Saliendo de aplicacion";
            exit(1);
        }
        
    } 
    
    std::cout << "Ingrese el tamano del cuadrado para la poblacion: ";
    std::cin >> tamCuadrado;

    std::vector<individuo> poblacion;
    //Inizializamso lapoblacion
    inicializarPoblacion(poblacion, numPoblaciones,tamCuadrado);


    std::cout << std::endl << "-----------------------------------------"<< std::endl;
    std::cout << "Tamano de la poblacion inicial: "<< poblacion.size();
    std::cout << std::endl << "-----------------------------------------"<< std::endl;

    // Realizar múltiples selecciones por torneo binario

/*  
    do
    {
    } while ();
    
 */
    seleccionarPadres(poblacion,numPoblaciones);

    std::vector<int> numexitos;
    cruzaPMX(poblacion);
    mutar(poblacion);
    for (int i = 0; i < poblacion.size(); i++) { 
        poblacion.at(i).setAptitud(poblacion.at(i).func1( poblacion.at(i).getCromosoma().sumaFilas(),poblacion.at(i).getCromosoma().sumaColumnas(),poblacion.at(i).getCromosoma().sumaDiagonales()  ));
        numexitos.push_back(poblacion.at(i).getAptitud());
    }
    
    
    return 0;
}

