#include <iostream>
#include <string>


class Aninmal{
    
    private: 
    std::string name; 
    int patas; 
    
    public: 

    //Constructor 
    Aninmal(std::string name, int patas): name(name), patas(patas){}

    void setName(std::string newName){
        this->name = newName; 
    }

    void setPatas(int newPatas){
        this->patas= newPatas; 
    }

    std::string getName(){
        return name; 
    }

    void printInfo(){

        std::cout<< name << std::endl; 
        std::cout<< patas << std::endl;
    }
    
    //Método que puede ser sobre escrito en una clase derivad o hija, para hacerlo se agrega la palabra "virtual" a la firma
    virtual void respirar(){
        std::cout<< "Esta respirando" << std::endl; 
    }

    //Método estático que no requiere una instancia del objeto para ser ejecutado 
    static void existir(){
        std::cout<< "EXISTE" << std::endl; 
    }

};


class Gato : public Aninmal{

    private: 
    std::string pelaje; 

    public: 
    //Constructor que hereda de Animal 
    Gato(std::string name, int patas, std::string pelaje):Aninmal(name,patas), pelaje(pelaje){}    

    //Metodo particular de la clase Gato
    void treparArbol(){
        printInfo(); 
        std::cout<<"Esta trepando"<<std::endl;  
    }   

    //Metodo de la clase base (Animal) que es sobre escrito utilizando la palabra "override"
    void respirar() override{
        std::cout<< "Esta respirando usando los bigotes" << std::endl; 
    }


}; 


int main(){

    ///Aninmal gato("DonGato", 2); 
    Gato g("Benito",2,"Azul");

    //cout<< gato.getName() << endl; 
    
    // std::cout<< gato.getName() << std::
    g.treparArbol(); 

    g.respirar();

    //Llamada al método estático 
    Aninmal::existir(); 

    //gato.printInfo(); 

    return 0; 
}

