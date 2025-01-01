#ifndef Model_hpp
#define Model_hpp
#include <glm/glm.hpp>
#include<string>
#include<vector>
#include "shapecreator.hpp"
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
        static Model* createModel(const string& TextureName, const string& ShaderProgramName, const ShapeTypes& ShapeType);
        
        
        
        void draw(const glm::mat4& mtxTransform);

        // set
        void setShaderProgramName(const string& name);
        void setTextureName(const string& name);
        void setVertexArrayObject(VertexArrayObject* vao);

        void setShapeType(const ShapeTypes  &ShapeType);

        // get
        string getTextureName();
        string getShaderProgramName();
        Transform* getTransform();
        VertexArrayObject* getVertexArrayObject();
        glm::vec2& getTextureRepeat();

        ShapeTypes getShapeType();
    private:
        glm::vec2   m_TextureRepeat;
        unsigned int m_fillType;
        string      m_textureName;
        string      m_programName;
        Transform*  m_transform;
        VertexArrayObject* m_vao;

        ShapeTypes m_shapeType;
    };

    using ModelList = std::vector<Model*>;
}
#endif