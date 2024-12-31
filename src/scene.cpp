#include "scene.hpp"
#include "camera.hpp"
#include "shadermanager.hpp"
#include "texturemanager.hpp"
#include<algorithm>
#include<fstream>
#include<nlohmann/json.hpp>
#include "shapecreator.hpp"
namespace graf
{
    void Scene::addModel(const string& fileName)
    {
        Model* model = Model::loadModelFromFile(fileName);
        addModel(model);

    }
    Scene::Scene()
    {
        
        m_activeCamera = new Camera();
    }
    void Scene::addModel(Model* model)
    {
        if(std::find(m_modelList.begin(),m_modelList.end(),model)==m_modelList.end())
        {
            string textureName = model->getTextureName();
            string shaderName = model->getShaderProgramName();
            TextureManager::addTextureFromFile(textureName);
            ShaderManager::addShaderFromFile(shaderName);
            m_modelList.push_back(model);
        }
    }
    Camera* Scene::getActiveCamera()
    {
        return m_activeCamera;
    }
    void Scene::removeModel(Model* model)
    {
        auto it=std::find(m_modelList.begin(),m_modelList.end(),model);
        if(it!=m_modelList.end())
        {
            m_modelList.erase(it);
        }  
    }
    void Scene::render()
    {
        
        for(auto next:m_modelList)
        {
            next->draw(m_activeCamera->getProjMatrix()*m_activeCamera->getViewMatrix());
        }
         renderGui()   ; 
       
    }
}