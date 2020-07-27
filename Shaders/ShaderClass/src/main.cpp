/*
 * Task: Create a class that loads shaders.
 * Author: Santiago Fernando Gomez
*/

#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } 
}

int main() {

    uint16_t width = 800;
    uint16_t height = 600;
    
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height,"Learining", NULL, NULL);
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
        0.5f, -0.3f, 0.0f,
        -0.5f, -0.3f, 0.0f,
        0.0f, 0.8f, 0.0f,
    };
    
    unsigned int indices[] = {0, 1, 2};
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader ourShader("../shaders/shader.vs", "../shaders/shader.fs");

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
	ourShader.use();
	
	float timeValue = glfwGetTime();
	float colorValues[4];
	colorValues[0] = sin(timeValue) / 2.0f + 0.5f;
	colorValues[1] = sin(timeValue) / 2.0f + 0.3f;
	colorValues[2] = cos(timeValue) / 2.0f + 0.7;
	colorValues[3] = 1.0f;
	ourShader.set4Float("ourColor", colorValues);
        
	glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(vertices), GL_UNSIGNED_INT, 0);
        
	glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

    return 0;
}
