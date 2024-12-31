#ifndef vertexarrayobject_hpp
#define vertexarrayobject_hpp
#include<vector>
namespace graf
{
    using namespace std;

    enum class VertexAttributeType
    {
        Position,
        Color,
        Normal,
        Texture
    };

    using AttributeList = vector<VertexAttributeType>;

    class VertexBuffer;
    class IndexBuffer;
    class VertexArrayObject
    {
    public:
        void create();
        void setVertexBuffer(VertexBuffer* vb );
         void setIndexBuffer(IndexBuffer* ib );
        void addVertexAttribute(VertexAttributeType type);
        void activateAttributes();
        void bind();
        void unbind();
        void release();
        void draw();
    private:
        int getTypeSize(VertexAttributeType type);
     
        unsigned int m_id;

        VertexBuffer* m_vb;
        IndexBuffer* m_ib;
        unsigned int m_stride;
        AttributeList m_attributes;

    };
}

#endif



