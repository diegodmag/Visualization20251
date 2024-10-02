#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

#define PI 3.141592

// Vertex Shader source code (GLSL 4.10)
const char *vertexShaderSource = R"(
    #version 410 core
    layout (location = 0) in vec3 aPos;
    uniform float aTime;
    out vec3 color;

    void main()
    {
        gl_Position = vec4(aPos.x + cos(aTime), aPos.y, aPos.z, 1.0);
        color = (aPos*cos(aTime) +1) * 0.5;
    }
)";

// Fragment Shader source code (GLSL 4.10)
const char *fragmentShaderSource = R"(
    #version 410 core
    out vec4 FragColor;
    in vec3 color;

    void main()
    {
        FragColor = vec4(color, 1.0);
    }
)";

// Función para generar un círculo con vértices en un vector
std::vector<float> creaCirculoVector(int tam, float radius) {
    std::vector<float> vertices;

    vertices.push_back(0.0f); // Centro del círculo
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);

    //Se calcula el ángulo entre cada vértice del círculo 
    //2 * PI : Circunsferencia del circulo en radianes 
    //Se divide entre tam-1 , para obtener el ángulo entre vértices consecutivos en el circulo
    float dosPI_entre_tam = 2.0f * PI / (float)(tam - 1); 
    for (int i = 1; i < tam + 1; i++) {
        vertices.push_back(radius * cosf(dosPI_entre_tam * (i - 1))); // x 
        vertices.push_back(radius * sinf(dosPI_entre_tam * (i - 1))); // y
        vertices.push_back(0.0f); // z
    }

    return vertices;
}

// Función para escribir los vértices en un archivo .obj
void escribirVerticesOBJ(const std::vector<float>& vertices, const std::string& nombreArchivo) {
    //ofstream es una clase de la biblioteca estandar de C++ que se utiliza para manejar archivos de salida.
    std::ofstream archivoOBJ(nombreArchivo);

    if (!archivoOBJ.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    // Escribir los vértices en formato .obj
    for (size_t i = 0; i < vertices.size(); i += 3) {
        archivoOBJ << "v " << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << "\n";
    }

    archivoOBJ.close();
    std::cout << "Vértices guardados en el archivo: " << nombreArchivo << std::endl;
}

// Función para cargar vértices desde un archivo .obj
std::vector<float> cargarVerticesDesdeOBJ(const std::string& rutaArchivo) {
    std::vector<float> vertices;
    std::ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << rutaArchivo << std::endl;
        return vertices;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string tipo;
        iss >> tipo;

        // Si la línea comienza con 'v', significa que contiene un vértice
        if (tipo == "v") {
            float x, y, z;
            iss >> x >> y >> z; // Leemos las coordenadas del vértice
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    archivo.close();
    return vertices;
}

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configurar la versión de OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crear una ventana
    GLFWwindow *window = glfwCreateWindow(800, 600, "Círculo OpenGL", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Inicializar GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Compilar y enlazar shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Crear el círculo y escribirlo en un archivo .obj
    int tam = 100;
    std::vector<float> vertices = creaCirculoVector(tam, 0.5);
    escribirVerticesOBJ(vertices, "circulo.obj");

    // Cargar los vértices desde el archivo .obj
    vertices = cargarVerticesDesdeOBJ("circulo.obj");

    // Preparar VAO y VBO para los vértices
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Bucle de renderizado
    GLuint timeLocation = glGetUniformLocation(shaderProgram, "aTime");
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        float time = glfwGetTime();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glUniform1f(timeLocation, time);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
