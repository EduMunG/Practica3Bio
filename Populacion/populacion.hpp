#include "../Chromosoma/cromosoma.cpp"
#include <vector>

class populacion
{
    private:
        std::vector<cromosoma> cromosomas;
        int N;
        
    public:


        populacion(int N); 
       
        
        void imprimirPoblacion();
        int consMagica(int N);
        
         ~populacion();
};

