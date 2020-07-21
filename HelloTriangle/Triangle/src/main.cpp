#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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


void parameters_window(const int major, const int minor) {
/**
 * With windowHint we can configure the parameters of the window,
 * we can select many options. The first argument is the option
 * that we want to configure. The second argument is an integer
 * that sets the value of our option.
*/
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
/**
 * Here with GLFW_CONTEXT_VERSION_MAJOR we set the maximum version
 * that can support our program, and win MINOR, the minimum version
*/
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
/**
 * Here we select the option GLFW_OPENGL_PROFILE, and with that
 * we select which profile we want to use, in this case we've
 * selected the core profile. The Core profile means the most
 * basic features of OpenGL.
*/
}

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
    
    glfwInit(); //if in main we have argc and argv in main -> glfwInit(&argc,argv)
    
    /**
     * Hints that we set BEFORE the creation of a window and context
    **/
    parameters_window(3, 3); 

    GLFWwindow* window = glfwCreateWindow(width, height,"Hello, baby", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize Glad" << std::endl;
        return -1;
    }    
    /* We set a size callback to be notified when the framebuffer of a
    windows is resized, whether by the user or the system. Por ejemplo
    si en un juego cambian de resolucion o achican la ventana, el size
    del framebuffer va a ser menor, entonces esta funcion va a llamar a
    la funcion framebuffer_size_callback y va a recibir el new size del
    framebuffer.
    */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        
//VERTEX SHADER
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
//VERTEX SHADER

//FRAGMENT SHADER
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int success2;
    char infoLog2[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);

    if (!success2) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog2 << std::endl;
    }
//FRAGMENT SHADER

//SHADER PROGRAM
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success3;
    char infoLog3[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success3);
    if (!success3) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog3);
        std::cout << "ERROR::PROGRAM::SHADER::COMPILATION_FAILED\n" << infoLog3 << std::endl;
    }

//SHADER PROGRAM

    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
    };
    
    unsigned int indices[] = {0, 1, 3, 1, 2, 3};
    
//Vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    /**
     * glBindVertexArray binds the vertex array object 
     * with name array. array is the name of a vertex array 
     * object previously returned from a call to glGenVertexArrays,
     * or zero to break the existing vertex array object binding.
    */
    glBindVertexArray(VAO);
//Vertex array object

//VertexBuffer OBJ  PAN
    unsigned int VBO;
    glGenBuffers(1, &VBO); //creamos un buffer object, it is sort of like malloc()

    /**
     * The glBindBuffer function binds the 
     * newly-created buffer object to the 
     * GL_ARRAY_BUFFER binding target. As 
     * mentioned in the introduction, objects 
     * in OpenGL usually have to be bound to 
     * the context in order for them to do anything, 
     * and buffer objects are no exception.
    */
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //especificamos el uso del buffer object asignandole su target, en este caso el target GL_ARRAY_BUFFEr lo convierte en un Vertex buffer obj
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //le pasamos la data al "currently bound buffer"(en este caso VBO) y indicamos la frecuencia del uso
    /**
     * It allocates memory for the buffer currently bound to GL_ARRAY_BUFFER,
     * which is the one we just created and bound.
    */
//VertexBufer OBJ

//Element Buffer Obj
    unsigned EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//Element Buffer Obj



//LINKING VERTEX ATTRIBUTES 
/**
 * Here we tell OpenGl how he has to interpret our data that is in the VertexBuffer and creates a pointer to the attributes
 * The state set by glVertexAttribPointer is stored in the currently VAO
 * 1 parameter: location of the vertex attribute in the vertex shader (layout (location = 0))
 * 2 parameter: size of the vertex attribute (it is a vec3, so 3)
 * 3 parameter: type of data
 * 4 parameter: specifies if we want the data to be normalized
 * 5 parameter: the space between consecutive vertex attributes(the stride). In this case x,y,z...(3).
 * 6 parameter; Where the position data begins in the buffer(the offset).
*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
//LINKING VERTEX ATTRIBUTES


//RENDER LOOP
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0 , 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        process_input(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
//RENDER LOOP


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    
    glfwTerminate();
    return 0;
}
