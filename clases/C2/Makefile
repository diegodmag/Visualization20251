# VARIABLES 
# Define el compilador que se va a utilizar, en este caso es g++ (el conjunto libre de operadores)
CC = g++  
# Variable del archivo fuente que se va a compilar 
SRC = main.cpp src/ShaderUtil.cpp
# Variable del nombre del archivo ejecutable que se va a definir 
TARGET = square
# Bibliotecas que se van a enlazar GLFW, GLEW y OpenGL
LIBS = -lglfw -lGLEW -lGL
# Banderas del compilador 
# std=c++11: Indica que el código debe ser compilado con el estándar de C++11
# -I./include : Indica que se configuro el directorio include para buscar encabezados
CFLAGS = -Wall -Wextra -std=c++11 

# -I./include
 

# REGLAS DE COMPILACION 

# Default target
# Objetivo predeterminado 
all: $(TARGET) 

# Compile the target
# Regla que definie como se compilara el archivo triangle a partir del archivo fuente main.cpp
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Clean up
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
