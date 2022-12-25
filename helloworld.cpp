// Defined before OpenGL and GLUT includes to avoid deprecation message in OSX
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int colorChannel = 0;
GLclampf Red = 0.0f, Green = 0.0f, Blue = 1.0f, Alpha = 1.0f;
int starttime = 0;

void renderSceneCB()
{
    // Clear Color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(Red, Green, Blue, Alpha);
}

void processNormalKeyCB(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void updateColor() {
    int time, timediff;
    //Update animations based on time increments
    time = (float)glfwGetTime() * 1000.f;
    std::cout << "time: " << time << std::endl;
    timediff=time - starttime;
    starttime=time;
    switch (colorChannel) {
        case 0:
            Red = Red + (timediff/1000.0f);
            Blue = Blue - (timediff/1000.0f);
            if (Red > 1.0f) {
                colorChannel = 1;
            }
            break;
        case 1:
            Green = Green + (timediff/1000.0f);
            Red = Red - (timediff/1000.0f);
            if (Green > 1.0f) {
                colorChannel = 2;
            }
            break;
        case 2:
            Blue = Blue + (timediff/1000.0f);
            Green = Green - (timediff/1000.0f);
            if (Blue > 1.0f) {
                colorChannel = 0;
            }
            break;
    }
}

static void error_callback(int error, const char* description)
{
    std::cerr << "Error: " << description << std::endl;
}

int main(int argc, char** argv)
{
    GLFWwindow* window;
    int width = 1920, height = 1080;

    glfwSetErrorCallback(error_callback);
    
    // Initialize GLFW
    if (!glfwInit())
        exit(EXIT_FAILURE);
        
    // Create a windowed mode window and its OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    //Initialize GLEW
    glewExperimental = GL_TRUE; 
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return 1;
    }

    // Print and test OpenGL context infos
    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;

    // Make the window's context current
    glfwSetKeyCallback(window, processNormalKeyCB);
    glfwSwapInterval(1);

    //OpenGL initializations
    glViewport(0, 0, width, height);
    glClearColor(Red, Green, Blue, Alpha);

    starttime = (float)glfwGetTime() * 1000.f;
    std::cout << "Start time: " << starttime << std::endl;

    //Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        renderSceneCB();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
        updateColor();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}