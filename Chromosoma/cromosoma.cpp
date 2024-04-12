#include "cromosoma.hpp"
#include <ctime>
#include <random>

static std::default_random_engine generador(time(NULL));
//Constructores


    cromosoma::cromosoma():
    vectorSuma(),
    tamCuadrado(),
    numMagico(){}

    cromosoma::cromosoma(std::vector<int> vectorSuma, int tamCuadrado){        
        this->vectorSuma=vectorSuma;
        setTamCuadrado(tamCuadrado);
        nmMagico(tamCuadrado);
    }

    cromosoma::cromosoma(int tamCuadrado){
        setTamCuadrado(tamCuadrado);
        generacionAleatoria(tamCuadrado);
        nmMagico(tamCuadrado);
    }


    cromosoma::~cromosoma(){
        tamCuadrado=0;
        vectorSuma.clear();
    }
    /* 
        SETTERS         
    */
   
    void cromosoma::setvectorSuma(std::vector<int> vectorSuma){
        this->vectorSuma=vectorSuma;
    }
    
    void cromosoma::anadirvectorSuma(int entero){
        vectorSuma.push_back(entero);
    }
    void cromosoma::setvectorSumaEnPos(int entero, int pos){
        vectorSuma.at(pos)=entero;
    }

    void cromosoma::setTamCuadrado(int tamCuadrado){
        this->tamCuadrado=tamCuadrado;
    }

    void cromosoma::setNumMagico(float numMagico){
        this->numMagico=numMagico;
    }


    /* 
        GETTERS


    */

    std::vector<int> cromosoma::getVectorSuma(){
        return this->vectorSuma;
    }

    int cromosoma::getTamCuadrado(void){
        return this->tamCuadrado;
    }



    float cromosoma::getNumMagico(void){
        return this->numMagico;
    }



    
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////METODOS/////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
void cromosoma::mutacionInsersion() {
    std::uniform_int_distribution<int> pos(0, this->tamCuadrado*this->tamCuadrado - 1);
    int pos1 = pos(generador);
    int pos2 = pos(generador);

    // Asegurarse que pos1 es menor que pos2
    if (pos1 > pos2) {
        std::swap(pos1, pos2);
    }

    if (pos1 != pos2) {
        // Extraer el valor en pos2
        int valor = getVectorSuma().at(pos2);

        // Desplazar todos los elementos desde pos2 hasta pos1+1 hacia la derecha
        for (int i = pos2; i > pos1; --i) {
            //getVectorSuma()[i] = getVectorSuma()[i - 1];
            setvectorSumaEnPos( getVectorSuma().at(i-1),i );
        }

        // Insertar el valor extraído en pos1
        setvectorSumaEnPos(valor,pos1);
        //getVectorSuma()[pos1] = valor;
    }
}


    void cromosoma::mutacionIntercambio(){
        static std::uniform_int_distribution<int> pos(0,this->tamCuadrado*this->tamCuadrado-1);
        int pos1=pos(generador);
        int pos2=pos(generador);
        int valor2, valor1, aux;
        while (pos2==pos1)
            pos2=pos(generador);
        while (pos1==2)
            pos1=pos(generador);     
/*         std::cout<<std::endl<<pos1;
        std::cout<<std::endl<<pos2;
         */
        //Intercambio
        valor1=getVectorSuma().at(pos1);
        valor2=getVectorSuma().at(pos2);
        aux=valor1;
        valor1=valor2;
        setvectorSumaEnPos(valor1,pos1);
        valor2=aux;
        setvectorSumaEnPos(valor2,pos2);
    }




    std::ostream& operator<< (std::ostream& os, const cromosoma& crom){
        
        os<<std::endl<<"Tamano Cuadrado: "<<crom.tamCuadrado;
        os<<" Numero Magico: "<<crom.numMagico;
        os<<" Tamano Vector: "<<crom.vectorSuma.size()<<std::endl;
        int indices=0;

        for (int i = 0; i < crom.vectorSuma.size(); i+=crom.tamCuadrado)
        {
            os<<std::endl<<"[ ";
            for (int j = 0; j < crom.tamCuadrado;j++ )
            {
                os<<crom.vectorSuma.at(indices++)<<" ";
            }
            os<<"]";
        }
    
        return os;
    }



    bool encontrado(std::vector<int>& visitados, int num){

        std::vector<int>::iterator it= visitados.begin();

        while (it!=visitados.end())
        {
            if ( (*it) == num  )
                return true; 
            it++;
        }
        return false;
    }

    void cromosoma::generacionAleatoria(int tamCuadrados){
        std::vector<int> generados;
        static std::uniform_int_distribution<int> n(1,this->tamCuadrado*this->tamCuadrado);
        int num=n(generador);
        generados.push_back(num);
        anadirvectorSuma(num);

        do
        {
            while (encontrado(generados,num))
                num=n(generador);
            anadirvectorSuma(num);
            generados.push_back(num);
        } while ( getVectorSuma().size() < this->tamCuadrado*this->tamCuadrado);
    }



    int cromosoma::nmMagico(int tamCuadrado){
        float num = tamCuadrado*(tamCuadrado*tamCuadrado+1)/2;
        setNumMagico(num);
        return num;
    }



        //Metodo de suma de filas
        std::vector<int> cromosoma::sumaFilas(){
            std::vector<int> col(tamCuadrado,0);
            int index=0;
            for (int i = 0; i < this->tamCuadrado; i++){
                for (int j = 0; j < this->tamCuadrado ; j++){
                    col.at(i)+=vectorSuma.at(index++);
                }   
            }
            return col;
        }
        //Metodo de suma de columnas 
        std::vector<int> cromosoma::sumaColumnas(){
            std::vector<int> col(tamCuadrado,0);
            for (int i = 0; i < this->tamCuadrado; i++){
                for (int j = i; j < vectorSuma.size() ; j+=tamCuadrado){
                    col.at(i)+=vectorSuma.at(j);
                }   
            }
            return col;
        }
        //Metodo de suma de diagonales
        int cromosoma::sumaDiagonales(){
            int diag=0;
            for (int j = 0; j < vectorSuma.size() ; j+=tamCuadrado+1)
                diag+=vectorSuma.at(j);            
        return diag;
        }