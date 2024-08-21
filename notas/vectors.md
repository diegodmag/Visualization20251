## Vectors 

Pensamos los vectores como arrays dinámicos, que pueden crecer o disminuir en tamaño. 

*Declaración* de vectores : 

```cpp
#include <iostream>
#include <vector>

auto main()->int{

    std::vector <int> charArr ; //Arreglo de datos de tipo char vacío 
    
    std::vector <int> intArr (5); //Cinco datos de tipo entero , con el tipo de dato por defecto. En el caso de int es 0. 

    std::vector <int> records {20,30,40,50}; //Se declara explícitamente el contenido del array.  

    std::vector <char> characters {'e','+','r'};

    //Declara arreglo de tamaño específico y con un mismo dato 
    std::vector <double> someDoubles (20, 22.22); 
}
```

Los vectores crecen y decrecen indeterminadamente, por lo que para iterar un vector puede convenir hacerlo con bucles indeterminados como el `while`. 

Para iterar un vector : 

```cpp 
#include <iostream>
#include <vector>

auto main()->int{
    //Declara arreglo de tamaño específico y con un mismo dato 
    std::vector <double> someDoubles (20, 22.22); 

    //Declaramos un contador 
    int i = 0; 
    //Con size() obtenemos la longitud de vector 
    while(i<someDoubles.size()){
        std::cout<<someDoubles[i]<<std::endl; 
    }
}
```
También se puede por medio del **range-based for loop**. 
```cpp
std::vector<int> numbers {20, 30, 40, 50};

for (auto num : numbers) {
    std::cout << "-" << num << std::endl;
}
```
La palabra `auto` permite que el compilador infiera automáticamente el tipo de variable `num`, la cual en este caso será de tipo `int` ya que `numbers` es un `std::vector<int>`. El compilador deduce que `num` debe ser del mismo tipo de los elementos del vector. 

**output**
```bash
-20
-30
-40
-50
```

El método `at` accede a un elemento a través de un índice pero hace una comprobación de límites.  

```cpp
#include <iostream>
#include <vector>

auto main()->int{
    //Declara arreglo de tamaño específico y con un mismo dato 
    std::vector <char> someChars {'H','e', 'l', 'l', 'o'} ; 

    //Accediendo normalmente al índice 4 
    std::cout << someChars[4] << std::endl; 
}
```
**output**
```bash
o
```
Por otro lado, si accedemos al elemento en el índice 5 con 
```cpp
std::cout << someChars[5] << std::endl;
```
Obtendremos una salida vacía. Sin embargo, usando `at` de la siguiente manera 
```cpp
std::cout << someChars.at(5) << std::endl;
```
**output**
```bash
terminate called after throwing an instance of 'std::out_of_range'
  what():  vector::_M_range_check: __n (which is 5) >= this->size() (which is 5)
Aborted
```
Obtenemos una excepción que nos informa sobre el intento de acceso a un índice fuera del rango. Por lo que usar `at` puede ser más seguro para acceder a los elementos del arreglo. El método `at` se puede usar también para asignar comprobando límites  : 
```cpp
someChars.at(4) = 'O';
std::cout << someChars.at(4) << std::endl;
```

El método `push_back`. El cual sirve para almacenar un nuevo elemento en el vector al final de éste. 

```cpp
std::vector <int> numbers {20,30,40,50};

numbers.push_back(60); //Se declara explícitamente el contenido del array.

for(int i=0; i<numbers.size(); i++){
        std::cout<<numbers[i]<<std::endl;
    }
```
**output**
```bash
20
30
40
50
60
```
Para remover el último elemento de un vector : 
```
numbers.pop_back();
```
Ahora si imprimimos de nuevo a `numbers` : 
**output**
```bash
20
30
40
50
```
Para limpiar el vector hacemos 
```
numbers.clear();
```
Y saber si está vacío 
```
numbers.empty();
```

## Pasando vectores como argumentos 

```cpp
#include <iostream>
#include <vector>


//Prototypes 

void printVector(std::vector<int> intVector);

void sumFiveToVector(std::vector<int>& intVector); 

int main(){

    std::vector<int> numbers {5,10,15,20}; 

    printVector(numbers); 

    sumFiveToVector(numbers); 

    printVector(numbers);

    return 0; 
}

//Se imprime el vector pasándose por valor 
void printVector(std::vector<int> intVector){
    std::cout<<"---"<<std::endl; 
    for(auto num: intVector){
        std::cout<<num<<" "; 
    }
    std::cout<<"\n---"<<std::endl; 
}

//Se modifica el vector pasándose por referencia & 
void sumFiveToVector(std::vector<int>& intVector){
    for(int i=0; i<intVector.size(); i++){
        intVector[i]+=5; 
    }
}
```
Para pasar vectores como argumentos a funciones y poder modificarlos es necesario pasar la **referencia al vector "&"**. Como se puede notar en la función `sumFiveToVector` se está pasándo `std::vector<int>& intVector`, la cual es una referencia a un vector de enteros. 

En la función `printVector`, se está pasando al vector como valor.

La diferencia más importante entre el **paso de valor** y **paso por referencia**, es que en el primero se va a generar una copia del argumento y el objeto original no va a ser modificado. En el paso por referencia se modifica el objeto pasado como argumento. 

### Buena práctica 

Cuando se trabaja con vectores como argumentos, se suelen pasar por referencia ya sea que se modifique o no. De otro modo, se estarían generando copias al pasarlo por valor y podría afectar el rendimiento. 

Para re-escribir la función `printVector`, pasándo el vector como referencia : 

```cpp
void printVectorByReference(std::vector<int>& intVector){
    std::cout<<"---"<<std::endl; 
    for(auto num: intVector){
        std::cout<<num<<" "; 
    }
    std::cout<<"\n---"<<std::endl; 
}
```

Y en general, como buena práctica, si no se va a modificar el vector, se pasa como una **referencia constante**, de este modod sigue pasándose como referencia pero no permite modificarlo : 

```cpp
void printVectorByReference(const std::vector<int>& intVector){
    std::cout<<"---"<<std::endl; 
    for(auto num: intVector){
        std::cout<<num<<" "; 
    }
    std::cout<<"\n---"<<std::endl; 
}
```