#include "Model.hpp"
#include "transform.hpp"
#include "shadermanager.hpp"
#include "texturemanager.hpp"
#include "shaderprogram.hpp"
#include "vertexarrayobject.hpp"
#include "shapecreator.hpp"
#include<fstream>
#include<nlohmann/json.hpp>
#include<glad/glad.h>
namespace graf
{
    Model::Model()
    {
        m_transform = new Transform();
        m_fillType = GL_FILL;
        m_textureName = "";
        m_programName = "";
        m_TextureRepeat = glm::vec2(1.0f);
    }



    Model* Model::loadModelFromFile(const string& fileName)
    {
        std::ifstream file("./models/"+fileName);

        using namespace nlohmann;
        auto data = json::parse(file);

        string ModelName=data["ModelName"].get<string>();

        string TextureName=data["TextureName"].get<string>();

        string ShaderProgramName=data["ShaderProgramName"].get<string>();

        ShapeTypes  ShapeType=(ShapeTypes) data["ShapeType"].get<int>();

        Model* model = new Model;

        model->setTextureName(TextureName);
        model->setShaderProgramName(ShaderProgramName);
        model->setVertexArrayObject(ShapeCreator::createShape(ShapeType));
        return model;
     
    }
    void Model::setShaderProgramName(const string& programFileName)
    {
        m_programName = programFileName;
    }
    string Model::getShaderProgramName()
    {
        return m_programName;
    }
    void Model::setTextureName(const string& FileName)
    {
        m_textureName = FileName;
    }
    string Model::getTextureName()
    {
        return m_textureName;
    }

    Transform* Model::getTransform()
    {
        return m_transform;
    }
    void Model::setVertexArrayObject(VertexArrayObject* vao)
    {
        m_vao = vao;
    }
    VertexArrayObject* Model::getVertexArrayObject()
    {
        return m_vao;
    }
    void Model::draw(const glm::mat4& mtxTransform)
    {
        TextureManager::activateTexture(getTextureName());

        auto program = ShaderManager::getProgram(getShaderProgramName());

        program->use();
        program->setMat4("uWorldTransform",mtxTransform*getTransform()->getMatrix());
        auto inverseRotationMatrix =glm::inverse(getTransform()->getRotationMatrix());
        
        program->setMat4("uInverseRotation",inverseRotationMatrix);
       
        program->setVec2("uTextureRepeat",m_TextureRepeat);
        glLineWidth(4.0f);
        glPolygonMode(GL_FRONT_AND_BACK,m_fillType);
        getVertexArrayObject()->bind();
        getVertexArrayObject()->draw();
        getVertexArrayObject()->unbind();
       
       
    }
    glm::vec2 &Model::getTextureRepeat()
    {
        return m_TextureRepeat;
    }
}