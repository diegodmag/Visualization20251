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
    uniform float aTime;
    out vec3 color;

    void main()
    {
        // gl_Position = vec4(aPos.x + cos(aTime), aPos.y, aPos.z, 1.0);
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
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



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_B && action == GLFW_RELEASE) {
        glfwSetWindowShouldClose(window, true); // Cerrar la ventana si se presiona ESC
    }
    // Agrega aquí más controles según sea necesario
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Acción cuando se presiona el botón izquierdo del mouse
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos); // Obtiene la posición del cursor
        std::cout << "Mouse Click at: (" << xpos << ", " << ypos << ")\n";
    }
    // Agrega aquí más controles según sea necesario
}

void enter_exit_cursor(GLFWwindow* window, int entered) {
    if (entered) {
        std::cout << "Cursor ha entrado en la ventana." << std::endl;
    } else {
        std::cout << "Cursor ha salido de la ventana." << std::endl;
    }
}


std::vector<float> creaCirculoVector(int tam, float radius)
{

    std::vector<float> vertices;

    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);

    for (int i = 1; i < tam + 1; i++)
    {

        vertices.push_back(radius * cosf((2.0f * M_PI / (tam - 1)) * (i - 1))); // x
        vertices.push_back(radius * sinf((2.0f * M_PI / (tam - 1)) * (i - 1))); // y
        vertices.push_back(0.0f);                                               // z
    }

    return vertices;
}

int main(int argc, char *argv[])
{

    /***************************************************************************************************************
     * Con los parámetros de entrada en el main, podemos obtener información al ejecutar la linea de comandos
     * En este ejemplo queremos obtener el método de pintado "1: float* Apuntador " o "2: Vector<float>"
     ****************************************************************************************************************/

    std::cout << argc << " : Número argumentos" << std::endl; // no indica cuantos argumentos está en la línea de comandos
    std::cout << argv[0];
    if (argc > 1)
        for (int i = 1; i < argc; i++)
            std::cout << "," << argv[i];

    std::cout << " : Valor argumentos" << std::endl; // siempre está el ejecutable y si hay más los podemos imprimir

    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL version to 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Triangle", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //Se registran las callbacks
    //De teclado  
    glfwSetKeyCallback(window, key_callback);
    //De mouse 
    //>> Presionar boton del mouse 
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    //>> Entrar y salir de pantall 
    glfwSetCursorEnterCallback(window, enter_exit_cursor);


    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Build and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    //>> los parámetros de glShaderSource 
    //0 : El objeto en donde se almacena el shader (en este caso vertexShader) 
    //1 : número de strings el el codigo fuente del shader (en este caso es 1 )
    //2 : El puntero o la referencia a las cadenas que contienen el codigo fuente 

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for shader compile errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Build and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Link shaders to a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data and buffers and configure vertex attributes
    int tam = 100;

    /*****************************************************************************************************************************
     * Crea un circulo con N (tam) puntos utilizando la clase vector
     * llama la función creaCirculo
     *****************************************************************************************************************************/
    std::vector<float> vertices = creaCirculoVector(tam, 0.5);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    //Habilitamos que Array queremos dibujar
    glBindVertexArray(VAO);
    
    GLuint VBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW); // utilizando Clase vector

    /**
     * Variables para mandar iformación del CPU -> GPU (shader)
     */
    GLuint timeLocation = -1;
    float time = -1.0;

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        time = glfwGetTime(); // obtiene el valor en segundos desde que se inicializó GLFW

        // Render
        // Esto es clear color por que limpia todos los buffers de colores y luego aplica un color 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        
        //Es importante notar que glUseProgram no ejecuta los shaders, sólo los carga en el hardware 
        glUseProgram(shaderProgram);
        
        
        
        /**
         * Inicializaciín de variables para mandar iformación del CPU -> GPU (shader)
         * Mandamos una variable de tiempo para actuzalizar datos en el shader
         * En estes caso la variable se llama aTime
         */
        timeLocation = glGetUniformLocation(shaderProgram, "aTime"); // Obtenemos una
        glUniform1f(timeLocation, time);

        //Habilitamos que Array queremos dibujar
        glBindVertexArray(VAO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        

        //>> En cuanto a los parametros de glVertexAttribPointer
        //0 : indice del atributo de vértice (la posición) 
        //1 : Indica el numero de componente por atributo de vértice 
        //2 : El tipo de data del atributo 
        //3 : specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
        //4 : Especifica el stride o la cantidad de bytes necesarios para leer un nuevo vértice
             
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //0: tipo de primitiva a dibujar 
        //1: Indíce del vértice inicial 
        //2: El total de vértices a ser pintado 
        glDrawArrays(GL_TRIANGLE_FAN, 0, tam + 1);

        glDisableVertexAttribArray(0);

        //  Unbind the VAO
        glBindVertexArray(0);
        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Deallocate resources
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    //  Terminate GLFW
    glfwTerminate();
    return 0;
}