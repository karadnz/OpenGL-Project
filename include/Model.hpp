#ifndef Model_hpp
#define Model_hpp
#include <glm/glm.hpp>
#include<string>
#include<vector>
namespace graf
{
    using namespace std;

    class Transform;
    class VertexArrayObject;
    class ShaderProgram;
    class Model
    {
    public:
        Model();
        static Model* loadModelFromFile(const string& name);
        Transform* getTransform();
        void setShaderProgramName(const string& name);
        string getShaderProgramName();
        void setTextureName(const string& name);
        string getTextureName();
        void setVertexArrayObject(VertexArrayObject* vao);
        VertexArrayObject* getVertexArrayObject();
        void draw(const glm::mat4& mtxTransform);


        glm::vec2& getTextureRepeat();
    private:
        glm::vec2   m_TextureRepeat;
        unsigned int m_fillType;
        string      m_textureName;
        string      m_programName;
        Transform*  m_transform;
        VertexArrayObject* m_vao;
    };

    using ModelList = std::vector<Model*>;
}
#endif