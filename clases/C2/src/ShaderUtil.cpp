#include "../include/ShaderUtil.h"

// Constructor que carga y compila los shaders
ShaderUtil::ShaderUtil(const std::string& vertexPath, const std::string& fragmentPath) {
    // Leer el código fuente de los shaders
    std::string vertexCode = readShaderSource(vertexPath);
    std::string fragmentCode = readShaderSource(fragmentPath);

    // Compilar los shaders
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    // Crear el programa de shader y enlazar los shaders compilados
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    // Verificar errores de enlace
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Eliminar shaders ya que están enlazados al programa
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Método para utilizar el programa de shader
void ShaderUtil::use() {
    glUseProgram(programID);
}

// Obtener el ID del programa de shader
GLuint ShaderUtil::getProgramID() const {
    return programID;
}

// Método privado para leer el código de shader desde un archivo
std::string ShaderUtil::readShaderSource(const std::string& filePath) {
    std::ifstream file(filePath);   //Es un constructor muy parecido 
    std::stringstream buffer;

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo de shader: " << filePath << std::endl;
        return "";
    }

    buffer << file.rdbuf();
    return buffer.str();
}

// Método privado para compilar shaders
GLuint ShaderUtil::compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* shaderCode = source.c_str(); //Puntero a una cadena de caracteres (apunta a la direccion de memoria de la fuente)
    glShaderSource(shader, 1, &shaderCode, NULL); //La direccion de el puntero shaderCode
    glCompileShader(shader);

    // Verificar errores de compilación
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}
