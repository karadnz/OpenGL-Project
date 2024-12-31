#ifndef GLWindow_hpp
#define GLWindow_hpp

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "functiontypes.hpp"

namespace graf
{
    class GLWindow
    {
    public:
        int create(unsigned int width,unsigned int height);
        void render();
        void setRenderFunction (RenderFunction function);
        void setKeyboardFunction(KeyboardFunction function);
        void setMouseFunction(MouseFunction function);
    private:
        GLFWwindow*     m_window;
        static void staticMouseFunction(GLFWwindow* window, double xpos, double ypos);
        static void statickeyboardFunction(GLFWwindow* window, int key, int scancode, int action, int mods);
        RenderFunction      m_renderFunction;
        KeyboardFunction    m_keyboardFunction;
        MouseFunction       m_mouseFunction;
    };
}


#endif