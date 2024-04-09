#include "cromosoma.hpp"
#include <ctime>
#include <random>

static std::default_random_engine generador(time(NULL));

//Constructores


    cromosoma::cromosoma():
    vectorSuma(),
    tamCuadrado(){}
    cromosoma::cromosoma(std::vector<int> vectorSuma, int tamCuadrado):
    vectorSuma(vectorSuma),
    tamCuadrado(tamCuadrado){}

    cromosoma::cromosoma(int tamCuadrado){
        setTamCuadrado(tamCuadrado);
        for(int i=0; i<tamCuadrado*tamCuadrado;i++)
            anadirvectorSuma(i+1);
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

    /* 
        GETTERS


    */

    std::vector<int> cromosoma::getVectorSuma(){
        return this->vectorSuma;
    }

    int cromosoma::getTamCuadrado(void){
        return this->tamCuadrado;
    }
    //METODOOOOS

    void cromosoma::mutacionInsersion(cromosoma &crom, float porMuta){
        std::uniform_int_distribution<int> pos(0,this->tamCuadrado);
        int pos1=pos(generador);
        int pos2=pos(generador);
        while (pos2==pos1)
            pos2=pos(generador);
        
        if (pos1<pos2){
            int valor2;
            int aux;
            while (pos2!=pos1)
            {
                valor2=getVectorSuma().at(pos2);
                aux=getVectorSuma().at(pos2-1);
                setvectorSumaEnPos(aux,pos2);
                pos2--;
                setvectorSumaEnPos(valor2,pos2);
            }
            
        }else{

        }
        

    }


    void cromosoma::mutacionDesplazamiento(cromosoma &crom, float porMuta){

    }