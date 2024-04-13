#include "./Populacion/individuo.cpp"
#include <climits>
#include <fstream>

bool encontradosec(std::vector<int>& seccion, int num){

    bool encontrado = false;

    while(!encontrado){
        for(int i:seccion){
            if (i==num) encontrado = true;
        }
    }
return encontrado;
}

void mutar(std::vector<individuo> &poblacion, float probabilidadMutacion) {
    
    if (poblacion.size()<2)
    {
        std::cout<<std::endl<<"Poblacion insuficiente para la mutacion"<<std::endl;
        return;
    }
    

    std::cout << std::endl << "-----------------------------------------" << std::endl;
    std::cout << "Mutar con poblacion: " << poblacion.size() << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    std::uniform_real_distribution<float> chance(0, 1);
    for (int i = 0; i < poblacion.size(); i++)
    {
        float prob=chance(gen);
        if (prob<probabilidadMutacion)
        {
/*             std::cout<<std::endl<<"Chance de mutacion: "<<prob<<std::endl;
            std::cout<<std::endl<<"Cromosoma sin mutar: "<<poblacion.at(i).getCromosoma();  */
            cromosoma crom= poblacion.at(i).getCromosoma();
            crom.mutacionInsersion();
            poblacion.at(i).setCromosoma(crom);
/*             std::cout<<std::endl<<"Cromosoma despues de mutar: "<<poblacion.at(i).getCromosoma(); */
        }
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
        //std::cout<<"\nCromosoma 1: "<<cromo1;
        //std::cout<<"\nCromosoma 2: "<<cromo2; 
 
        std::vector<int> padre1 = cromo1.getVectorSuma();
        std::vector<int> padre2 = cromo2.getVectorSuma();
        int tamCuad = cromo1.getTamCuadrado();

        int maxIndex = padre1.size() - 1;
        std::uniform_int_distribution<int> dist(1, maxIndex);
        int pos1 = dist(gen);
        int pos2 = dist(gen);

        if (pos1 > pos2) std::swap(pos1, pos2);  // Asegurar que pos1 es menor que pos2
       // std::cout<<std::endl<<"Posicion 1: "<<pos1<<std::endl<<"Posicion 2: "<<pos2;
        // Crear cromosomas hijos inicializados con -1 para representar posiciones no asignadas
        std::vector<int> hijo1(padre1.size(), -1), hijo2(padre2.size(), -1);
        
/*          std::cout<<std::endl<<"Hijo 1 : "<<std::endl;
        for (int i : hijo1)
            std::cout<<i<<" ";
        std::cout<<std::endl<<"Hijo 2 : "<<std::endl;
        for (int i : hijo2)
            std::cout<<i<<" ";
  */
        //Guardar las secciones
        std::vector<int> seccion1;
        std::vector<int> seccion2;

        // Mapear secciones entre pos1 y pos2
        for (int i = pos1; i <= pos2; ++i) {
            hijo1[i] = padre2[i];
            hijo2[i] = padre1[i];
            seccion1.push_back(padre2[i]); //Elementos del padre 2 en hijo 1
            seccion2.push_back(padre1[i]); //Elementos del padre1 1 en hijo 2
        }   
 
/*         std::cout<<std::endl<<"seccion 1 del padre2 : "<<std::endl;
        for (int i : seccion1)
            std::cout<<i<<" ";
        std::cout<<std::endl<<"seccion 2 del padre 1 : "<<std::endl;
        for (int i : seccion2)
            std::cout<<i<<" ";


        std::cout<<std::endl<<"Hijo 1 despues de mapeo : "<<std::endl;
        for (int i : hijo1)
            std::cout<<i<<" ";
        std::cout<<std::endl<<"Hijo 2 despues de mapeo: "<<std::endl;
        for (int i : hijo2)
            std::cout<<i<<" ";  */

        //Para el hijo 1 con genetica del padre 2
    for (int i = 0; i < padre1.size(); i++) {
        if ((i < pos1 || i > pos2) && std::find(seccion1.begin(), seccion1.end(), padre2[i]) == seccion1.end()) {
            hijo1[i] = padre2[i];
        }
        if ((i < pos1 || i > pos2) && std::find(seccion2.begin(), seccion2.end(), padre1[i]) == seccion2.end()) {
            hijo2[i] = padre1[i];
        }
    }

/*          std::cout<<std::endl<<"Hijo 1 despues de relleno : "<<std::endl;
        for (int i : hijo1)
            std::cout<<i<<" ";
        std::cout<<std::endl<<"Hijo 2 despues de relleno: "<<std::endl;
        for (int i : hijo2)
            std::cout<<i<<" ";  */

        // Crear nuevos individuos con los cromosomas cruzados
        individuo nuevoHijo1, nuevoHijo2;
        nuevoHijo1.setCromosoma(cromosoma(hijo1, tamCuad));
        //std::cout<<std::endl<<" Nuevo Hijo: "<<nuevoHijo1.getCromosoma();
        nuevoHijo2.setCromosoma(cromosoma(hijo2, tamCuad));
        //std::cout<<std::endl<<" Nuevo Hijo: "<<nuevoHijo2.getCromosoma();


        // Añadir los hijos a la lista de hijos
        hijos.push_back(nuevoHijo1);
        hijos.push_back(nuevoHijo2);

        itDePoblacion ++; // Avanzar al siguiente par de individuos
    }
    hijos.pop_back();
    hijos.pop_back();
    for(individuo hijo : hijos)
        poblacion.push_back(hijo);
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
/*         std::cout << "\nPadre " << i <<" seleccionado:" << std::endl;
        std::cout << "Indice: " << indiceGanador  << std::endl;
        std::cout << "Aptitud Ganadora: " << poblacion.at(indiceGanador).getAptitud() << std::endl; */
        if (  poblacion.at(indiceGanador).getAptitud()>2  )
            nuevosPadres.push_back(poblacion.at(indiceGanador));    
    }
    poblacion=nuevosPadres; // Reemplaza la población antigua con los ganadores
    std::cout << std::endl << "-----------------------------------------"<< std::endl;
    std::cout << "Poblacion restante: " << poblacion.size() << std::endl;
    std::cout <<  "-----------------------------------------"<< std::endl;
}


void inicializarPoblacion(std::vector<individuo>& poblacion, int numPoblaciones, int tamCuadrado) {
    for (int i = 0; i < numPoblaciones; i++) {
        individuo ind(tamCuadrado);
        ind.setAptitud(ind.func1(ind.getCromosoma().sumaFilas(), ind.getCromosoma().sumaColumnas(), ind.getCromosoma().sumaDiagonales()));
        std::cout<<"Aptitud: "<<ind.getAptitud();
        poblacion.push_back(ind);
        std::cout << "\nAptitud de la poblacion evaluada en la Funcion 2 (Maximizar) " << i  << ": " << poblacion.back().getAptitud()<< std::endl;
    }
}


void escribir(std::ofstream& archivo, std::vector<int> mejores, std::vector<int> peores, std::vector<float> promedios){
    // Escribir las estadísticas en el archivo
    archivo << "mejores: ";
    for (int apt : mejores) {
        archivo << apt << ", ";
    }
    archivo << "\n";

    archivo << "promedio: ";
    for (double apt : promedios) {
        archivo << apt << ", ";
    }
    archivo << "\n";

    archivo << "peores: ";
    for (int apt : peores) {
        archivo << apt << ", ";
    }
    archivo << "\n";

    archivo.close();  // No olvides cerrar el archivo al terminar
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

    std::ofstream archivo("estadisticas.txt");
    if (!archivo.is_open())
    {        
        std::cerr << "Error al abrir el archivo para escribir las estadísticas." << std::endl;
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

    int generacion = 0;
    int solucion=0;
    std::vector<int> mejores, peores;
    std::vector<float> promedio;
    std::vector<int> numExitos;
    for(individuo& individuo: poblacion){
        mejores.push_back(individuo.getAptitud());
        peores.push_back(individuo.getAptitud());
        promedio.push_back(individuo.getAptitud());
    }
    individuo* individuoSolucionado= nullptr;
    while (generacion <1000000) {

        if (poblacion.size()<2)
        {
            std::cout<<"Muy poca poblacion, saliendo del programa"<<std::endl;
            return 0;
        }
        
        seleccionarPadres(poblacion, poblacion.size());
    
        cruzaPMX(poblacion);
        mutar(poblacion, .8);
        /* 
        mutar(poblacion, 1);
        numPoblaciones=poblacion.size();
        cruzaPMX(poblacion);
        numPoblaciones=poblacion.size(); */
        
        bool solEncontrada=false;
        int mejorAptitud = INT_MIN;// Inicializa con el mínimo posible para encontrar el máximo
        int peorAptitud= INT_MAX;//Peor aptitud
        float aptprom=0.0;
        numExitos.clear();
        for(individuo &individuo: poblacion){
            int nuevaAptitud = individuo.func1(individuo.getCromosoma().sumaFilas(), individuo.getCromosoma().sumaColumnas(),individuo.getCromosoma().sumaDiagonales());
            individuo.setAptitud(nuevaAptitud);
            aptprom+=nuevaAptitud;
            
            if (nuevaAptitud > mejorAptitud) { mejorAptitud=nuevaAptitud; }else {peorAptitud=nuevaAptitud;}

            if (nuevaAptitud == 2*tamCuadrado+2) {solEncontrada=true;  individuoSolucionado=&individuo;}
        }

        if (solEncontrada)
        {
            std::cout << "Función objetivo encontrada!" << std::endl;
            std::cout << "Generación " << generacion + 1 << ": Mejor aptitud = " << mejorAptitud << std::endl;
            std::cout << "Detalle del individuo con la solución:" << std::endl;
            std::cout << *individuoSolucionado;  // Usar el operador sobrecargado para imprimir el individuo
            aptprom/=poblacion.size();
            mejores.at(generacion+1)=mejorAptitud;
            peores.at(generacion+1)=peorAptitud;
            promedio.at(generacion+1)=aptprom;
            escribir(archivo,mejores,peores,promedio);
            return 0;
        }
        
        std::cout << "Generacion " << generacion + 1 << ": Mejor aptitud: " << mejorAptitud<< " Peor Aptitud: "<<peorAptitud << std::endl << "Tam Poblacion: " << poblacion.size() << std::endl;

        generacion++;
        aptprom/=poblacion.size();

        mejores.at(generacion)=mejorAptitud;
        peores.at(generacion)=peorAptitud;
        promedio.at(generacion)=aptprom;
    }
    archivo.close();
    return 0;
}

