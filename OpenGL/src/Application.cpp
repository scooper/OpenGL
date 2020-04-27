#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "ErrorHandling.h"
#include "Shader.h"

int main(void)
{
    /*std::cout << "Hello world" << std::endl;
    std::cin.get();*/


    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // request debug context (should be some sort of debug/release defines to sort this
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (status == 0)
    {
        std::cout << "Error" << std::endl;
        return 0;
    }

    // debug for error handling
    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        // initialize debug output 
        ErrorHandling::GLErrorMessageInit();
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    {

        float positions[]{
            // vertex    // color
           -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 0
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // 1
            0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // 2
           -0.5f,  0.5f, 1.0f, 1.0f, 1.0f  // 3
        };

        unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

        // vertex array
        VertexArray va;

        // vertices
        VertexBuffer vb(positions, sizeof(positions));

        // layout
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(3);
        va.AddBuffer(vb, layout);

        // indices
        IndexBuffer ib(indices, sizeof(indices) / sizeof(*indices));

        // shaders
        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        
        // unbind as a test for vertex array
        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            // set up viewport (for correct scaling)
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            int lowest = height >= width ? width : height;
            glViewport(0, 0, lowest, lowest);

            // bind shaders
            shader.Bind();

            renderer.Clear();
            renderer.Draw(va, ib, shader);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwDestroyWindow(window);
    }
    glfwTerminate();
    return 0;
}

