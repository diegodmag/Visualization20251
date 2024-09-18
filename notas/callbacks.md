## Callbacks 

Un `callback` es una función que se pasa como argumento a otra función y se ejecuta en un momento posterior. En el contexto de programación de eventos, un callback se utiliza para manejar eventos (como presionar una tecla o mover el mouse).

Cuando ocurre un evento, el sistema (en este caso, GLFW) llama automáticamente al callback correspondiente, permitiendo que el programa responda a la acción del usuario sin necesidad de estar constantemente revisando el estado de las entradas.

En general, un `callback` es una función que va a ser *llamada* o *ejecutada* cuando ocurra algún evento. 


### Callback de teclado 

Para configurar un `callback` para el teclado, considere el siguiente ejemplo: 
```cpp
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
```
Donde 
- `GLFWwindow* window` : Es un puntero a la ventana que recibió el evento.
- `int key` : código de la tecla que fue presionada. 
- `int scancode` : código específico de la tecla que puede ser útil para algunas configuraciones de teclado (ver después). 
- `int action` : indica a qué tipo de acción respondera el evento que puede ser : 
    - GLFW_PRESS: La tecla fue presionada.
    - GLFW_RELEASE: La tecla fue liberada.
    - GLFW_REPEAT: La tecla está siendo repetida (mantenida presionada).
- `int mods` : Indica si se estaban presionando teclas modificadoras (como Shift, Ctrl, Alt) al momento de la acción.

Después, es necesario configurar a la función `key_callback` en el programa de openGL, para lo cual se hace : 

`glfwSetKeyCallback(window, key_callback);`

Para lo anterior es necesario haber inicializado la ventana `window` y haber generado el contexto `glfwMakeContextCurrent(window);`. 


### Callback de mouse 

El `input` por mouse se recibe de distintas maneras, incluído el movimiento del cursor, presionar el botón y realizar scrolling. 

Considere la siguiente función : 

```cpp
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Acción cuando se presiona el botón izquierdo del mouse
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos); // Obtiene la posición del cursor
        std::cout << "Mouse Click at: (" << xpos << ", " << ypos << ")\n";
    }
}
```
La cual se tiene que registrar con `glfwSetMouseButtonCallback(window, mouse_button_callback);`





Para más información revisar documentación util : 

- [Guía para input](https://www.glfw.org/docs/3.3/input_guide.html)
- [Función glfwSetKeyCallback](https://www.glfw.org/docs/3.3/group__input.html#ga1caf18159767e761185e49a3be019f8d)
- [function pointer type for keyboard key callback](https://www.glfw.org/docs/3.3/group__input.html#ga5bd751b27b90f865d2ea613533f0453c)
- [Códigos de las teclas](https://www.glfw.org/docs/3.3/group__keys.html)



- [Documentación para input de mouse](https://www.glfw.org/docs/3.3/input_guide.html#input_mouse)

