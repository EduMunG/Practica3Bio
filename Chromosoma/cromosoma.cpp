#include "cromosoma.hpp"
#include <ctime>
#include <random>

static std::default_random_engine generador(time(NULL));

//Constructores


    cromosoma::cromosoma():
    vectorSuma(),
    tamCuadrado(),
    numMagico(){}

    cromosoma::cromosoma(std::vector<int> vectorSuma, int tamCuadrado):
    vectorSuma(vectorSuma),
    tamCuadrado(tamCuadrado){}

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



    //METODOOOOS

    void cromosoma::mutacionInsersion(){
        static std::uniform_int_distribution<int> pos(0,this->tamCuadrado*this->tamCuadrado-1);
        int pos1=pos(generador);
        int pos2=pos(generador);
        int valor2;
        int aux;
        while (pos2==pos1)
            pos2=pos(generador);
        while (pos1==2)
            pos1=pos(generador);
        
        
        std::cout<<std::endl<<pos1;
        std::cout<<std::endl<<pos2;
        
        if (pos1<pos2){
            while (pos2!=pos1)
            {
                valor2=getVectorSuma().at(pos2);
                aux=getVectorSuma().at(pos2-1);
                setvectorSumaEnPos(aux,pos2);
                pos2--;
                setvectorSumaEnPos(valor2,pos2);
            }
            
        }else{
            while (pos2!=pos1)
            {
                valor2=getVectorSuma().at(pos1);
                aux=getVectorSuma().at(pos1-1);
                setvectorSumaEnPos(aux,pos1);
                pos1--;
                setvectorSumaEnPos(valor2,pos1);
            }
            
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
        std::cout<<std::endl<<pos1;
        std::cout<<std::endl<<pos2;
        
        //Intercambio
        valor1=getVectorSuma().at(pos1);
        valor2=getVectorSuma().at(pos2);
        aux=valor1;
        valor1=valor2;
        valor2=aux;
    }




    std::ostream& operator<< (std::ostream& os, const cromosoma& crom){
        
        os<<std::endl<<"Tamano Cuadrado: "<<crom.tamCuadrado<<" Numero Magico: "<<crom.numMagico<<std::endl<<"[";
        for (int i : crom.vectorSuma)
        {
            std::cout<<i<<",";
        }
        os<<"]"<<std::endl;
        return os;
    }



    void cromosoma::generacionAleatoria(int tamCuadrados){
        std::vector<int> generados;
        static std::uniform_int_distribution<int> n(1,this->tamCuadrado*this->tamCuadrado);
        int num=n(generador);
        generados.push_back(num);
        anadirvectorSuma(num);

        do
        {
            while (num==generados.)
                num=n(generador);
            anadirvectorSuma(num);
            generados.push_back(num);
            for (int i : generados)
            {
                std::cout<<" "<<i;
            }
            std::cout<<std::endl;
            
        } while ( getVectorSuma().size() < this->tamCuadrado*this->tamCuadrado-1);
    }



    void cromosoma::nmMagico(int tamCuadrado){
        float num = tamCuadrado*(tamCuadrado*tamCuadrado+1)/2;
        setNumMagico(num);
    }


    bool encontrado(std::vector<int>& visitados, int num){

        

    }