

# Biblioteca iostream 

## Introducción 

La biblioteca estándar de entrada y salida de datos `iostream` proporciona las instrucciones para la lectura de datos via teclado usando la terminal e impresión de datos igualmente por terminal. Para informar al compilador que deseamos utilizar las funcionalidades de dicha biblioteca, es necesario incluir su **archivo de cabecera (header file)** asociado, típicamente al principio del archvo 
```cpp
#include <iostream>
```
Todas las funcionalidades de la *biblioteca estándar* y, por lo tanto, las de `iostream` están englobadas dentro de un  **espacio de nombres(namespace)** denominado `std`. Los espacios de nombres proporcionan un ámbito único a un grupo de identificadores. 
- Permite **organizar** el código en grupos lógicos. 
- **Evita conflictos de nombres** que pueden producirse cuando el programa utiliza varias bibliotecas. 

Para poder usar cualquiera de los identificadores de un `namespace` (espacio de nombres) debemos utilizar el espacio de nombres seguido del **operador de resolución de ámbito (scope resolution operator)** `::`.   

## La salida estándar `std::cout`

Se conoce a un **flujo(stream)** como un canal a través del cual fluyen en **serie** bytes desde un origen a un destino. Un flujo se implementa internamente con el concurso de un **búfer(buffer)**, una zona de memoria donde se almacenan *temporalmente* los datos siguiendo una estructura tipo **cola(queue)**, es decir, primero en llegar, primero en salir.   

```cpp
#include <iostream> //Agregamos el header para usar la biblioteca iostream

auto main()->{
    std::cout<<"Hola mundo"<<std::endl;
}
```
La variable `cout`**(character output)** pertenece al `namespace` conocido como `std` y a esa variable se le concatena el flujo de entrada por medio del operador de inserción `cout`. El operador `cout` concatena de izquierda a derecha las cadenas de caracteres. 

```cpp
#include <iostream> 
auto main()->{
    std::cout<<"Hola" << " mundo" <<std::endl;
}
```
Puede ser tedioso utilizar el `scope resolution operator` aunque se recomienda utilizar ya que es la manera más clara y legible. Una alternativa es declarar el uso del `namespace` de la siguiente forma : 

```cpp 

#include <iostream>

using namespace std; 

auto main()->{
    cout << "Hola" << "mundo." endl; 
}

```

La directiva `using`, le informa al compilador que, si algún identficador no está declarado, entonces debe buscarlo en el espacio de nombres `std`. 

### Transformando representaciones numéricas a cadenas de caracteres 

Una de las funcionalidades de la biblioteca `iostream` es que permite insertar en el **flujo de caracters de salida** `cout` datos numéricos y transformarlos, de forma transparente al usuario, a una representación como cadena de caracteres. 

```cpp 
#include <iostream>

int main(){
    int x = 2; 
    double y = 8.13; 

    std::cout<<x << ", " << y <<  std::endl; 
     
}
```

Se ha podido notar que se utiliza el identificador `std::endl`, su función es 
- Insertar en el flujo de caracteres de salida a el caracter `\n`
- **Vaciar(flush)** el flujo de caracteres, forzándolo a ser mostrado en consola.  

### La entrada estándar 

La biblioteca `iostream` tiene una variable predefinida para un **flujo(stream)** de caracteres de **entrada** llamada `cin` **(character input)**, lo que permite transformar secuencias de caracteres a la representación binaria de datos en memoria. 

```cpp
#include <iostream>

int main(){

    std::cout<<"Introduce un entero"<<std::endl;
    int x; 
    std::cin>>x; 
    std::cout<<"x="<<x<<std::endl;   
}
```
La variable `cin` pertenece al espacio de nombres `std`. Y el operador de extracción `cin` permite extraer characteres del flujo de entrada y transformarlos a su representación binaria entera. 


#### TIP NEMOTÉCNICO

- `cin` **(character input)** utiliza el operador de flujo de entrada `>>`
- `cout`  **(character output)** utiliza el operador de salida de datos `<<`

Algunas características del operador de extracción `>>` : 

- Todos los **espacios en blanco** al inicio del búfer son ignorados, incluidos tabuladores y retornos de línea. 
- Se transforman los caracteres hasta el siguiente **espacio en blanco**.


#### Ejemplo interesante 

Consideremos el siguiente código 

```cpp
#include <iostream>

int main()
{
   std::cout << "Introduce un entero: ";
   int x;
   std::cin >> x;
   std::cout << "Introduce otro entero: ";
   int y;
   std::cin >> y;
   std::cout << "x=" << x << "\ny=" << y << '\n';
} 
```

El usuario introduce en consola : 

```bash
Introduce un entero 3 5 
```
Es decir, el usuario introdujo `3` + `' '` + `5` + `\n`. Por lo que el búfer de entrada tiene la información `3 5\n`. Qué ocurre? Se regresa : 

```bash 
Introduce un entero: 5 7 
Introduce otro entero: x=5
y=7
```

En una sólo ejecución, por que el búfer de entrada ya tenía guardado `5\n` después de habérlo liberado con el primer `cout`. 

