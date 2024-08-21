## Clases en C++ 

Podemos ver a una clase como un tipo definido por el usuario. Contiene *atributos(data members)* los cuales describen las propiedades de la clase, y *métodos(member functions)*, que describen las capcidades de los objetos. 

**Clase persona**
```cpp
#include <iostream>
#include <string>

class Person{
    public: 
    std::string name; 
    std::string last; 

    void printFullName() {
        std::cout<<name<<" "<<last<<std::endl;    
    }
}; 
```
La directiva `public` indica que lo que sigue después es accesible fuera de la clase. Para poder instanciar la clase se hace : 
```cpp
auto main()->int{

    Person p; 
    p.name = "Fulano";
    p.last = "Mengano";
}
```
Siguiendo el fundamento de encapsulamiento, nos interesa hacer visible los datos de las clases sólo a través de métodos o interfaces. 
```cpp
#include <iostream>
#include <string>

class Person{
    private: 
    std::string name; 
    std::string last; 

    public:

    void setFirstName(std:s:tring newName){
        this->name = newName;  
    }        

    void setFirstName(std::string newLast){
        this->last = newLast;  
    }
    
    std::string getName(){
        return name + " " + last;  
    }

    void printFullName() {
        std::cout<<name<<" "<<last<<std::endl;    
    }
}; 
```

Declarar un constructor, básicamente un método que determina las instancias de la clase. 


```cpp
class Person{
    private: 
    std::string name; 
    std::string last; 

    public:

    Person(std::string name, std::string last): name(name), last(last){} // initializer list constructor 

    // Constructor clasico
    // Person(std::string name, std::string last){
    //     this-> name = name; 
    //     this-> last = last; 
    // }

    void setName(std::string newName){
        this->name = newName;  
    }        

    void setLastName(std::string newLast){
        this->last = newLast;  
    }
    
    std::string getName(){
        return name + " " + last;  
    }

    void printFullName() {
        std::cout<<name<<" "<<last<<std::endl;    
    }
}; 
```

Por lo que ahora, para instanciar un objeto de la clase `Persona`, hacemos 

```cpp 

auto main()->int{
  
   Person p("Fulano", "Mengano"); 
   
   std::cout << p.getName() << std::endl; 
    
   p.setName("Sutano"); 

   std::cout << p.getName() << std::endl;
   
}

```
**output :**
```bash
Fulano Mengano
Sutano Mengano
```


En caso de que se desee sólo declarar una instancia sin asignar su data members, ser puede usar la directiva `default` para agregar un constructor por defecto. 
```cpp
class Person{
    private: 
    std::string name; 
    std::string last; 

    public:

    Person(std::string name, std::string last): name(name), last(last){} // initializer list constructor 

    Person() = default; // Constructor por defecto 

    void setName(std::string newName){
        this->name = newName;  
    }        

    void setLastName(std::string newLast){
        this->last = newLast;  
    }
    
    std::string getName(){
        return name + " " + last;  
    }

    void printFullName() {
        std::cout<<name<<" "<<last<<std::endl;    
    }
}; 
```

Instanciando el constructor `default` : 

```cpp 

auto main()->int{

   Person p("Fulano", "Mengano"); 
   
   std::cout << p.getName() << std::endl; 
    
   p.setName("Sutano"); 

   std::cout << p.getName() << std::endl;

   Person agenteP2;

   agenteP2.setName("Agente"); 

   agenteP2.setLastName("P2");

   agenteP2.printFullName(); 
   
}
```
**output :**
```bash 
Fulano Mengano
Sutano Mengano
Agente P2
```

### Herencia 

Para indicar la herencia de clase : 

```cpp

class Student : public Person {

   private: 
      std::string major; 

   public: 
      Student(std::string name, std::string last, std::string major): Person(name, last), major(major){}

      void printStudent(){

         std::cout << getName() << " " << major << std::endl; 
      }

};
```

```cpp 

auto main()->int{

   //Declaramos un estudiante 

   Student std("Pedro", "Picapiedra", "Computer Science"); 

   std.printFullName(); 

   std.printStudent(); 
}
```

**output**

```bash
Pedro Picapiedra
Pedro Picapiedra Computer Science
```

Si se desea acceder a un data member de la clase padre desde una clase hijo, es necesario cambiar el modificador de acceso a `protected`.   

### Override 

Function overrding es una re-definición de la función de la clase base en una clase derivada o hija con la misma firma, y por lo tanto mismos parámetros y valor de retorno. 
Por ejemplo, considerando a nuestras clases `Person` y `Student`. Agregamos una función general `display`, que opera distinto en ambas clases .

```cpp
class Person{
   protected: 
      std::string name; 
      std::string last; 

   public:

      Person(std::string name, std::string last): name(name), last(last){} // initializer list constructor 

      Person() = default; 
      
      // Constructor clasico
      // Person(std::string name, std::string last){
      //     this-> name = name; 
      //     this-> last = last; 
      // }

      void setName(std::string newName){
         this->name = newName;  
      }        

      void setLastName(std::string newLast){
         this->last = newLast;  
      }
      
      std::string getName(){
         return name + " " + last;  
      }

      void printFullName() {
         std::cout<<name<<" "<<last<<std::endl;    
      }


      //Agregamos el nuevo método 
      virtual void display(){
         std::cout<<"-----------"<<"\n"; 
         std::cout<<"Person name"<<"\n"; 
         std::cout<<name<<"\n"; 
         std::cout<<last<<"\n"; 
         std::cout<<"-----------"<<"\n"; 

      }


}; 
```

La directiva para sobreescribir un método de una clase base es `virtual` en la clase padre, indicando que puede ser re-definido. Mientras, que en la clase derivada se agrega la directiva `override`.

```cpp 
class Student : public Person {

   private: 
      std::string major; 

   public: 
      Student(std::string name, std::string last, std::string major): Person(name, last), major(major){}

      void printStudent(){

         std::cout << name << " " << last << " " << major << std::endl; 

         std::cout << this->getName() << " " << major << std::endl; 
      }

   //Se indica que es un método que se sobreescribe 
   void display() override{

      std::cout<<"-----------"<<"\n"; 
      std::cout<<"Studen"<<"\n"; 
      std::cout<<name<<"\n"; 
      std::cout<<last<<"\n"; 
      std::cout<<major<<"\n"; 
      std::cout<<"-----------"<<"\n";
   }

};
```

Para utilizar métodos estáticos (no necesitan una instancia de la clase para ser ejecutados), utilizamos la directiva `static`. 

```cpp 
static void specificStudentBehavior(){
      std::cout<<"I am the STUDENT STRING ENTITY, the static representation of all students"<<std::endl; 
   }
```
Y para llamar al método, hacemos : 

```cpp
auto main()->int{
    Student::specificStudentBehavior(); 
}
```
**output**
```bash
I am the STUDENT STRING ENTITY, the static representation of all students
```
