#include "vertexbuffer.hpp"
#include<glad/glad.h>


namespace graf
{
    void VertexBuffer::create(void * data,int size)
    {
        //vertex buffer object oluşuruluyor
        glGenBuffers(1,&m_id);

        glBindBuffer(GL_ARRAY_BUFFER,m_id);

        glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);

    }
    void VertexBuffer::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER,m_id);
    }
    void VertexBuffer::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }    
    void VertexBuffer::release()
    {
        glDeleteBuffers(1,&m_id);
    }
}