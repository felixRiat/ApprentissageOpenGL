#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "lib/logger/Logger.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

Logger myLogger;

int main() {
    // Initialisation de glfw

    myLogger.info("Initialize App");
    myLogger.verbose("Initialisation de glfw");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Création d'un objet pour la fenêtre
    myLogger.verbose("Création de la fenêtre...");
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    myLogger.verbose("Fenêtre créée");
    if (window == NULL) {
        myLogger.error("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    myLogger.verbose("Ajout de la fenêtre au contexte glfw");
    glfwMakeContextCurrent(window);

    // Initialisation de GLAD
    myLogger.verbose("Initialisation de GLAD...");
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        myLogger.error("Failed to initialize GLAD");
        return -1;
    }
    myLogger.verbose("GLAD Initialisé");

    // Ce qui est affiché à l'écran
    glViewport(0, 0, 800, 600);

    // Liaison de la fonction avec glfw
    myLogger.verbose("Liaison entre glfw et la fenêtre");
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /*
     * Test création d'un triangle
     */

    float vertices[] = {
            0.5f, 0.5f, 0.0f, // top right
            0.5f, -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f // top left
    };

    unsigned int indices[] = {
            0, 1, 3, // Premier triangle
            1, 2, 3 // Second triangle
    };

    // Element buffer object
    unsigned int EBO;
    glGenBuffers(1, &EBO);


    // Création du vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // définition du vertex shader:
    const char *vertexShaderSource = "#version 330 core \n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    // Création du shader pour opengl
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // On attache le code du shader a l'objet:
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // verification de la compilation du shader :
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        myLogger.error("Erreur lors de la compilation du shader");
        myLogger.error(infoLog);
    }


    // Gestion de la couleur du triangle

    const char *fragmentShaderSource = "#version 330 core \n"
                                       "out vec4 FragColor;\n"
                                       "void main() {\n"
                                       " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    // Gestion erreur shader
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        myLogger.error("Erreur lors de la compilation du shader");
        myLogger.error(infoLog);
    }


    // Shader program (pour liéer les shaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Gestion erreur shader programme
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        myLogger.error("Erreur lors de la compilation du shader");
        myLogger.error(infoLog);
    }

    // Activation du programme :
    glUseProgram(shaderProgram);

    // Supression des shader dont on a plus besoin:
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Tell opengl how it should interpret the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Génération d'un vertex array object:
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 4. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);



    // Mainloop
    myLogger.info("Démarage de la boucle principale");
    while(!glfwWindowShouldClose(window)) {
        // Input
        processInput(window);

        // Rendering commands here
        // Wireframe mode :
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        // Desactiver pour dessiner les deux triangles
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Activer pour dessiner les deux triangles
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        // Check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    myLogger.info("Fin du programme");
    myLogger.verbose("Terminaison de glfw");
    glfwTerminate();
    return 0;
}


/**
 * Fonction pour s'occuper du resize de la fenêtre
 * @param window : La fenêtre qu'on resize
 * @param width : La nouvelle largeur de la fenêtre
 * @param height : La nouvelle hauteur de la fenêtre
 * */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    myLogger.verbose("Resize window");
    glViewport(0, 0, width, height);
}

/**
 * Fonction pour capturer les appuies sur les touches
 * @param window
 */
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        myLogger.verbose("Escape key pressed !");
        glfwSetWindowShouldClose(window, true);
    }
}
