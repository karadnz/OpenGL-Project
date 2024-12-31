#include "GLWindow.hpp"
#include <iostream>
#include<imgui/imgui.h>
#include<imgui/backends/imgui_impl_opengl3.h>
#include<imgui/backends/imgui_impl_glfw.h>
namespace graf
{
    void GLWindow::statickeyboardFunction(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        GLWindow* myWindow= (GLWindow*)glfwGetWindowUserPointer(window);
        myWindow->m_keyboardFunction(key,scancode,action);
    }
    void GLWindow::staticMouseFunction(GLFWwindow* window, double xpos, double ypos)
    {
        GLWindow* myWindow= (GLWindow*)glfwGetWindowUserPointer(window);
        myWindow->m_mouseFunction(xpos,ypos);

    }
     void GLWindow::setMouseFunction(MouseFunction function)
    {
        m_mouseFunction = function;
    }   
    void GLWindow::setKeyboardFunction(KeyboardFunction function)
    {
        m_keyboardFunction = function;
    }
    int GLWindow::create(unsigned int width,unsigned int height)
    {
          if(!glfwInit())
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
       
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(width, height, "My Title", NULL, NULL);

        if (!m_window )
        {
            // Window or OpenGL context creation failed
        }
        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        glEnable(GL_DEPTH_TEST); 
        glfwSetWindowUserPointer(m_window,this);  
        glfwSetKeyCallback(m_window,statickeyboardFunction);
        glfwSetCursorPosCallback(m_window, staticMouseFunction);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


        ImGui::CreateContext();

        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        return 1;
    }
    void GLWindow::setRenderFunction(RenderFunction render)
    {
        m_renderFunction = render;
    }
    void GLWindow::render()
    {
        while (!glfwWindowShouldClose(m_window))
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            m_renderFunction();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            ImGui::EndFrame();
            
            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }

}