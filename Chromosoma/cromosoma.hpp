
#include <vector>
#include <iostream>
class cromosoma{
    private:
        std::vector<int> vectorSuma; //Vector en el cual se pondran los numeros del 1 al n^2
        int tamCuadrado;
        //Metodo que genera aleatoriamente el vector
        void generacionAleatoria(int tamCuadrados);
        float numMagico;
    public:
    //Constructor por defecto
        cromosoma(void);
        //Constructor dado un vector suma y un tamano de cuadrado hecho
        cromosoma(std::vector<int> vectorSuma, int tamCuadrado);
        //Constructor que definira un vector suma dado el tamano del cuadrado
        cromosoma(int tamCuadrado);

        //DEstructor por defecto
        ~cromosoma();
        
        
        
        //setters
        void setvectorSuma(std::vector<int> vectorSuma);
        void anadirvectorSuma(int entero);
        void setvectorSumaEnPos(int entero, int pos);
        void setTamCuadrado(int tamCuadrado);
        void setNumMagico(float numMagico);


        //GEtters
        std::vector<int> getVectorSuma(void);
        int getTamCuadrado(void);
        float getNumMagico(void);

        //Metodo que define la mutacion por insersion
        void mutacionInsersion();
        //Metodo para la mutacion por desplazamiento
        void mutacionIntercambio();
        //Metodo para Calcular el numero magico
        void nmMagico(int tamCuadrado);
        //Metodo para la sobrecarga del operador <<
        friend std::ostream& operator<< (std::ostream& os, const cromosoma& crom);

};
