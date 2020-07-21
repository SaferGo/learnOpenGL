/*
 * Task: Draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data.
 * Author: Santiago Fernando Gomez
*/

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } 
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void success(const unsigned int &shader, const int &opc) {
    int succ;
    char infoLog[512];
    
    if (opc == 1 || opc == 2) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &succ);
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &succ);
    }

    if (!succ) {
        std::cout << "ERROR::";
        if (opc == 1) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "SHADER::VERTEX";
        } else if (opc == 2) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "SHADER::FRAGMENT";
        } else {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cout << "PROGRAM::SHADER";
        }
        std::cout << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main () {\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main() {
    
    uint16_t width = 800;
    uint16_t height = 600;
    
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(width, height,"Learning", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize Glad" << std::endl;
        return -1;
    }
    
    float vertices[] = {
        0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.f
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    success(vertexShader, 1);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    success(fragmentShader, 2);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    success(shaderProgram, 3);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
	    glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
	    glDrawArrays(GL_TRIANGLES, 3, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VBO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    
    return 0;
}
