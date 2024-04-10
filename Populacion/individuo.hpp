#include "../Chromosoma/cromosoma.cpp"
#include <vector>

/* 
    Cada individuo tiene un cromosma. los individuos se van a 

*/

class individuo
{
    private:
        
    public:
        cromosoma cromosomas;
        int tamCuadrado;



        individuo(int tamCuadrado); 
       
        
        ~individuo();


        void cruza(individuo uno, individuo dos);

        //Metodo para la minimizacion
        bool func1(std::vector<int>,std::vector<int>,int);
        //Metodo de minimizacion
        bool func2(std::vector<int>,std::vector<int>,int);

        friend std::ostream& operator<<(std::ostream& os, individuo indi);
};

