/* #include "cromosoma.cpp"



int main(int argc, char const *argv[])
{
    std::vector<int> fil, col;

    int diag;
    cromosoma crom(2);

    std::cout<<crom;
    crom.mutacionInsersion();
    
    std::cout<<crom;

    crom.mutacionIntercambio();
    std::cout<<crom;

    fil= crom.sumaFilas();
    col= crom.sumaColumnas();
    diag= crom.sumaDiagonales();

    std::cout<<" FIlas:\n";

    for (int i:fil){
        std::cout<<" "<<i;
    }
    
    std::cout<<"\nColumnas:\n";

    for (int i:col){
        std::cout<<" "<<i;
    }
    

    std::cout<<" Suma diag: "<<diag;

    return 0;
} */