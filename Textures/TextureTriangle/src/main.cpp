/*
 * Task: Create a triangle and apply a texture to it.
 * Author: Santiago Fernando Gomez
*/

#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
       //positions         //texture coords
        0.5f, -0.3f, 0.0f, 0.0f, 0.0f,
       -0.5f, -0.3f, 0.0f, 1.0f, 0.0f,
        0.0f,  0.8f, 0.0f, 0.5f, 1.0f,
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    

    Shader ourShader("../src/shaders/shader.vs", "../src/shaders/shader.fs");

    //Load textures
    int width_t, height_t, nrChannels;
    unsigned char *data = stbi_load("../src/textures/wall.jpg", &width_t, &height_t, &nrChannels, 0);
    if (!data) {
    	std::cout << "Failed to load texture" << std::endl;
    }
    //Generate obj for texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //Set the texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Generate textures/Mipmap
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_t, height_t, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    //After generating the texture we fee the image memory
    stbi_image_free(data);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
	ourShader.use();
	
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        
	glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

    return 0;
}
