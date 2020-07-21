/*
 * Task: Create two shader programs where the second program uses a different fragment shader that
 * outputs the color yellow; draw both triangles again where one outputs the color yellow.
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

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "}\0";

const char *fragmentShaderSource1 =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

const char *fragmentShaderSource2 =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main() {\n"
	"	FragColor = vec4(1.0f, 0.964f, 0.258f, 1.0f);\n"
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
    
    float vertices1[] = {
            0.5f, 0.0f, 0.0f,
            0.1f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.0f
        };

    float vertices2[] = {
        -0.5f, 0.0f, 0.0f,
            -0.1f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.f
    };

    unsigned int VAO[2];
    glGenVertexArrays(2, VAO);

    unsigned int VBO[2];
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    int success;
    char infoLog[512];

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
	    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader[2];
    fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader[0], 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader[0]);
    glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &success);
    if (!success) {
	    glGetShaderInfoLog(fragmentShader[0], 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::FRAGMENT_1::COMPILATION_FAILED\n" << infoLog << std::endl;	}

    unsigned int shaderProgram[2];
    shaderProgram[0] = glCreateProgram();
    glAttachShader(shaderProgram[0], vertexShader);
    glAttachShader(shaderProgram[0], fragmentShader[0]);
    glLinkProgram(shaderProgram[0]);
    glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
    if (!success) {
    	glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::PROGRAM_1::LINKING_FAILED\n" << infoLog << std::endl;
    }
       
    glDeleteShader(fragmentShader[0]);
    
    fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader[1], 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader[1]);
    glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &success);
    if (!success) {
    	glGetShaderInfoLog(fragmentShader[1], 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::FRAGMENT_2::COMPILATION_FAILED\n" << std::endl;
    }

    shaderProgram[1] = glCreateProgram();
    glAttachShader(shaderProgram[1], vertexShader);
    glAttachShader(shaderProgram[1], fragmentShader[1]);
    glLinkProgram(shaderProgram[1]);
    glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
    if (!success) {
    	glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::PROGRAM_2::LINKING_FAILED\n" << infoLog <<std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader[1]);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram[0]);
	glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
	    
        glUseProgram(shaderProgram[1]);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    glDeleteProgram(shaderProgram[0]);
    glDeleteProgram(shaderProgram[1]);
    glfwTerminate();
    
    return 0;
}
