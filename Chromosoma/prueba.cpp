#include "cromosoma.cpp"



int main(int argc, char const *argv[])
{

    cromosoma crom(4);

    std::cout<<crom;
    crom.mutacionInsersion();
    
    std::cout<<crom;

    return 0;
}