#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "lib/logger/Logger.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


int main() {
    // Initialisation de glfw
    Logger myLogger;
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

    // Mainloop
    myLogger.info("Démarage de la boucle principale");
    while(!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    myLogger.info("Fin du programme");
    myLogger.verbose("Terminaison de glfw");
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
