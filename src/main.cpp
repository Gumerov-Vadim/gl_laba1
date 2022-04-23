#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

GLfloat point[] = {
    0.0f,0.5f,0.0,
    0.5f,-0.5f,0.0,
    -0.5f,-0.5f,0.0
};

GLfloat colors[]{
    0.75f,0.0f,0.0f,
    0.0f,0.75f,0.0f,
    0.0f,0.0f,0.75f
};
const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main(){"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position,1.0);"
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main(){"
"   frag_color = vec4(color, 1.0);"
"}";

int WindowSizeWidth = 640;
int WindowSizeHeight = 640;

class Colorpar {
public:
    Colorpar() { i = 0; isinc = true; bottom = 0; top = 1; speed = 0.01; }
    Colorpar(float i, float bottom, float top, int speed) { this->bottom = bottom; this->top = top; if (i < top) { this->i = i; } else { this->i = 0; } isinc = true; this->speed = speed * 0.01; }
    float get() {
        this->move();
        return this->i;
    }
    void move() {
        if (isinc) {
            this->i = nexti(this->i, speed);
        }
        else {
            this->i = nexti(this->i, -speed);
        }
    }

private:
    float i;
    float bottom, top;
    float speed;
    bool isinc;
    float nexti(float l,float speed){
        float nexti = l + speed;
        if (nexti < 1&&nexti>0) {
            return nexti;
        }
        else if (nexti == 1) {
            isinc = false;
            return 1;
        }
        else if (nexti == 0) {
            isinc = true;
            return 0;
        }
        else {
            isinc = !isinc;
            return l - speed;
        }
        return l;
    }

};

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
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, nullptr);
    glCompileShader(fs);

    GLuint shader_programm = glCreateProgram();
    glAttachShader(shader_programm, vs);
    glAttachShader(shader_programm, fs);

    glLinkProgram(shader_programm);

    glDeleteShader(vs);
    glDeleteShader(fs);

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    //std::cout<<"OpenGl"<<GLVersion.major<<"."<<GLVersion.minor<<std::endl;
    /* Loop until the user closes the window */
    Colorpar* Blue = new Colorpar();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.6, 0.6, Blue->get() , 1);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_programm);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,3);
        /* Render here */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}