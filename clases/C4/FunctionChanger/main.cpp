#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>

#define PI 3.141592

// Vertex Shader source code (GLSL 4.10)
const char *vertexShaderSource = R"(
    #version 410 core
    layout (location = 0) in vec3 aPos;
    out vec3 color;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        color = (aPos * 0.5 + 0.5); // Normaliza el color
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

// Funciones para generar vértices
std::vector<float> creaCirculoVector(int tam, float radius);
std::vector<float> creaElipsoideVector(float a, float b, float c, int segmentos, int anillos);

// Variables globales
//Se hacen globales para poder configurarlos fuera del ámbito del main 
GLuint VBO, VAO; 
std::vector<float> vertices;
bool useCircle = true; // Controla qué figura se está utilizando

// Callback para el mouse
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Alternar entre círculo y elipsoide
        if (useCircle) {
            vertices = creaCirculoVector(100, 0.5f);
        } else {
            vertices = creaElipsoideVector(0.8f, 0.8f, 0.4f, 50, 25);
        }
        useCircle = !useCircle; // Cambiar el estado
        // Actualizar el VBO con los nuevos vértices
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

// Función para crear un círculo
std::vector<float> creaCirculoVector(int tam, float radius) {
    std::vector<float> vertices;
    for (int i = 0; i <= tam; i++) {
        float angle = (2.0f * M_PI / tam) * i;
        vertices.push_back(radius * cosf(angle)); // x
        vertices.push_back(radius * sinf(angle)); // y
        vertices.push_back(0.0f); // z
    }
    return vertices;
}

// Función para crear un elipsoide
std::vector<float> creaElipsoideVector(float a, float b, float c, int segmentos, int anillos) {
    std::vector<float> vertices;
    for (int i = 0; i <= anillos; i++) {
        float phi = i * M_PI / anillos; // Ángulo polar
        for (int j = 0; j <= segmentos; j++) {
            float theta = j * 2 * M_PI / segmentos; // Ángulo azimutal
            float x = a * cos(theta) * sin(phi);
            float y = b * sin(theta) * sin(phi);
            float z = c * cos(phi);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }
    return vertices;
}

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configurar la ventana
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Shapes", NULL, NULL);
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

    // Compilar y configurar shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Eliminar shaders después de enlazar
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Crear VBO y VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Establecer los vértices iniciales
    vertices = creaCirculoVector(100, 0.5f);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Registrar callbacks
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Bucle de renderizado
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 3); // Dibuja la figura
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Liberar recursos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
