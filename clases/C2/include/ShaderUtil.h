//Este archivo se conoce como archivo de encabezado o header file. Su propósito principal
//es declarar interfaces, clases, funciones, constantes, etc. 

//La implementacion de los métodos se escribe en otro archivo separado (ShaderUtil.cpp)

//include guards --> Evita la inclusión múltiple 

// Esta técnica consiste en envolver el contenido del archivo de encabezado con directivas de 
// preprocesador para asegurarse de que el contenido solo se procese una vez, 
// incluso si el archivo es incluido múltiples veces.

#ifndef SHADER_UTIL_H
#define SHADER_UTIL_H

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <sstream> 
//Biblioteca de flujo de cadenas -> proporciona clases y funciones para manipular 
//cadenas de texto en memoria de manera similar a cómo se manipulan flujos de entrada y salida en archivos o la consola.
#include <fstream>

class ShaderUtil {
public:
    // Constructor que toma las rutas de los archivos de shaders
    ShaderUtil(const std::string& vertexPath, const std::string& fragmentPath);

    // Método para utilizar el programa de shader
    void use();

    // Obtener el ID del programa de shader
    GLuint getProgramID() const;

private:
    // ID del programa de shader
    GLuint programID;

    // Método privado para leer el código de shader desde un archivo
    std::string readShaderSource(const std::string& filePath);

    // Método privado para compilar shaders
    GLuint compileShader(GLenum type, const std::string& source);
};

#endif // SHADER_UTIL_H
