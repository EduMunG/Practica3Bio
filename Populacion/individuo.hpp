#include "../Chromosoma/cromosoma.cpp"
#include <vector>

/* 
    Cada individuo tiene un cromosma. los individuos se van a 

*/

class individuo
{
    private:
        
        cromosoma cromosomas;
        int aptitud;

    public:

        individuo(int tamCuadrado); 
        individuo(); 
    
        ~individuo();


        //SETTERS

        void setCromosoma(cromosoma cromosoma);
        void setAptitud(int aptitud);


        //GETTERRS

        cromosoma getCromosoma(void);
        int getTamCuadrado(void);
        int getAptitud(void);

        //METODOS


        //Metodos para la seleccion de los padres
        int seleccionTorneoBinario(std::vector<int> &enfrentados, std::vector<individuo>& poblacion);





        //Metodo para la minimizacion
        int func1(std::vector<int>,std::vector<int>,int,int);
        //Metodo de minimizacion
        int func2(std::vector<int>,std::vector<int>,int,int);
        //Metodo de sobre carga del operador <<
        friend std::ostream& operator<<(std::ostream& os, individuo indi);
};
