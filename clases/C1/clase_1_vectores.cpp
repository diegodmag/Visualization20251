#include <iostream>
#include <vector>


auto main()->int{

    std::vector <int> charInt ; //Arreglo de datos de tipo int vacío 
    
    std::vector <int> intArr (5); //Cinco datos de tipo entero , con el tipo de dato por defecto. En el caso de int es 0. 

    //Al inicializar el arreglo intArr de tamaño 5, cada elemento se inicializa con el valor mínimo del tipo de dato
    //Para el caso de int es 0
    for(auto num : intArr){
        std::cout << num <<  std::endl; 
    }
    std::cout<<"----------"<<std::endl;

    std::vector <int> records {20,30,40,50}; //Se declara explícitamente el contenido del array.  

    std::vector <char> characters {'e','+','r'};

    //Declara arreglo de tamaño específico y con un mismo dato 
    std::vector <double> someDoubles (20, 22.22); 


    //Una forma de recorrer el vector
    int cont = 0; 
    while (cont<someDoubles.size())
    {
        std::cout<<someDoubles[cont]<<std::endl;
        cont+=1; 
    }
    
    //Usando el for range-based for loop (muy parecido a un foreach)

    std::cout<<"----------"<<std::endl;
    
    for (auto num : someDoubles) {
        std::cout << "-" << num << std::endl;
    }

}