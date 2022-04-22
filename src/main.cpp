#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int WindowSizeWidth = 640;
int WindowSizeHeight = 640;

void glfwWindowSizeCallback(GLFWwindow* pw, int w, int h) {
    WindowSizeHeight = h;
    WindowSizeWidth = w;
    glViewport(0, 0, WindowSizeWidth, WindowSizeHeight);
}

void glfwKeyCallback(GLFWwindow* pw, int key, int scancode,int action,int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pw, GL_TRUE);
        glfwTerminate();
    }

}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "glfw init failed!" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WindowSizeWidth,WindowSizeHeight, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "glfw Create Window failed!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(!gladLoadGL()){
        std::cout<<"Can't load GLAD!"<<std::endl;
        return -1;
    }
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;
    
    glClearColor(0.6,0.6,0.9,1);

    std::cout<<"OpenGl"<<GLVersion.major<<"."<<GLVersion.minor<<std::endl;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}