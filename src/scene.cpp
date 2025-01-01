#include "Scene.hpp"
#include "camera.hpp"
#include "shadermanager.hpp"
#include "texturemanager.hpp"
#include<algorithm>
#include<fstream>
#include<nlohmann/json.hpp>
#include "shapecreator.hpp"
#include "transform.hpp"
#include<imgui/imgui.h>
#include<glad/glad.h>  // Add this line to get OpenGL function declarations

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
        m_cameraList.push_back(m_activeCamera);  // Add default camera to list
        
        // Create selection indicator as pyramid instead of cube
        m_selectionCube = Model::createModel("indicator.jpg", "LightTextureShader", ShapeTypes::Pyramid);
        m_selectionCube->getTransform()->setScale(glm::vec3(1.5f));

        // Change camera indicator to use Frustum shape and set wireframe mode
        m_cameraIndicator = Model::createModel("camera_indicator.jpg", "LightTextureShader", ShapeTypes::Frustum);
        m_cameraIndicator->getTransform()->setScale(glm::vec3(2.0f));
        m_cameraIndicator->getTransform()->setEuler(glm::vec3(90.0f, 0.0f, 0.0f)); // Rotate base 90 degrees so top points forward
        m_cameraIndicator->setFillType(GL_LINE); // Set wireframe mode
    }
    Scene::~Scene() {
        delete m_selectionCube;
        delete m_cameraIndicator;
        // ...existing cleanup code...
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
        // Set viewport to main window size
        glViewport(0, 0, 1400, 1400);
        
        // Draw camera indicators first (with wireframe)
        for(auto cam : m_cameraList) {
            if(cam != m_activeCamera) { // Don't show indicator for active camera
                // Update position AND rotation of the camera indicator
                m_cameraIndicator->getTransform()->setPosition(cam->getTransform()->getPosition());
                glm::vec3 camRot = cam->getTransform()->getEuler();
                m_cameraIndicator->getTransform()->setEuler(camRot + glm::vec3(90.0f, 0.0f, 0.0f));
                
                // Store current polygon mode
                GLint polygonMode[2];
                glGetIntegerv(GL_POLYGON_MODE, polygonMode);
                
                // Draw camera indicator
                m_cameraIndicator->draw(m_activeCamera->getProjMatrix() * m_activeCamera->getViewMatrix());
                
                // Restore previous polygon mode
                glPolygonMode(GL_FRONT_AND_BACK, polygonMode[0]);
            }
        }

        // Main viewport render
        for(auto next:m_modelList)
        {
            next->draw(m_activeCamera->getProjMatrix()*m_activeCamera->getViewMatrix());
            
            // If this is selected model, draw selection pyramid above it
            if (next == m_modelList[currentSelectedModel]) {
                // Get position of current model and position pyramid above it
                glm::vec3 pos = next->getTransform()->getPosition();
                pos.y += (next->getTransform()->getScale().y + 0.5f); // Changed from -= to +=
                
                // Update selection pyramid position
                m_selectionCube->getTransform()->setPosition(pos);
                
                // Rotate the pyramid around Y axis and point down
                static float rotation = 0.0f;
                rotation += 0.5f;
                m_selectionCube->getTransform()->setEuler(glm::vec3(180.0f, rotation, 0.0f)); // Added 180 degrees X rotation
                
                // Draw selection pyramid
                m_selectionCube->draw(m_activeCamera->getProjMatrix()*m_activeCamera->getViewMatrix());
            }
        }

        // Small viewport in top-right corner
        if (m_cameraList.size() > viewportCameraIndex) {
            // Set viewport to top-right corner, 1/4 of the window size
            glViewport(900, 900, 500, 500);
            
            // Clear depth buffer for new viewport
            glClear(GL_DEPTH_BUFFER_BIT);
            
            Camera* viewportCam = m_cameraList[viewportCameraIndex];

            // Draw camera indicators in viewport
            for(auto cam : m_cameraList) {
                if(cam != viewportCam) { // Don't show indicator for viewport camera
                    // Update position AND rotation of the camera indicator
                    m_cameraIndicator->getTransform()->setPosition(cam->getTransform()->getPosition());
                    glm::vec3 camRot = cam->getTransform()->getEuler();
                    m_cameraIndicator->getTransform()->setEuler(camRot + glm::vec3(90.0f, 0.0f, 0.0f));
                    m_cameraIndicator->draw(viewportCam->getProjMatrix() * viewportCam->getViewMatrix());
                }
            }
            
            // Render rest of scene from viewport camera perspective
            for(auto next:m_modelList) {
                next->draw(viewportCam->getProjMatrix() * viewportCam->getViewMatrix());
            }
        }
        
        renderGui();
    }
    void Scene::saveScene(const string& filename) {
        nlohmann::json j;

        // Save cameras
        j["cameras"] = nlohmann::json::array();
        for (auto camera : m_cameraList) {
            nlohmann::json cam;
            cam["fov"] = camera->getFov();
            cam["aspect"] = camera->getAspect();
            cam["near"] = camera->getNear();
            cam["far"] = camera->getFar();
            
            auto pos = camera->getTransform()->getPosition();
            cam["position"] = {pos.x, pos.y, pos.z};
            
            auto rot = camera->getTransform()->getEuler();
            cam["rotation"] = {rot.x, rot.y, rot.z};
            
            j["cameras"].push_back(cam);
        }
        
        // Save models
        j["models"] = nlohmann::json::array();
        for (auto model : m_modelList) {
            nlohmann::json mdl;
            mdl["shapeType"] = (int)model->getShapeType();
            mdl["textureName"] = model->getTextureName();
            mdl["shaderName"] = model->getShaderProgramName();
            
            auto pos = model->getTransform()->getPosition();
            mdl["position"] = {pos.x, pos.y, pos.z};
            
            auto rot = model->getTransform()->getEuler();
            mdl["rotation"] = {rot.x, rot.y, rot.z};
            
            auto scale = model->getTransform()->getScale();
            mdl["scale"] = {scale.x, scale.y, scale.z};
            
            auto texRepeat = model->getTextureRepeat();
            mdl["textureRepeat"] = {texRepeat.x, texRepeat.y};
            
            j["models"].push_back(mdl);
        }

        // Save selection states
        auto activeModelIt = std::find(m_modelList.begin(), m_modelList.end(), m_modelList[currentSelectedModel]);
        j["selectedModelIndex"] = activeModelIt - m_modelList.begin();
        
        auto activeCameraIt = std::find(m_cameraList.begin(), m_cameraList.end(), m_activeCamera);
        j["activeCameraIndex"] = activeCameraIt - m_cameraList.begin();
        j["selectedCameraIndex"] = currentSelectedCamera;
        j["viewportCameraIndex"] = viewportCameraIndex; // Add this line

        // Write to file
        std::ofstream file(filename);
        file << j.dump(4);
    }

    void Scene::loadScene(const string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        nlohmann::json j = nlohmann::json::parse(file);

        // Clear existing data
        m_modelList.clear();
        for (auto cam : m_cameraList) delete cam;
        m_cameraList.clear();

        // Load cameras
        for (auto& cam : j["cameras"]) {
            Camera* camera = new Camera(
                cam["fov"], 
                cam["aspect"],
                cam["near"],
                cam["far"]
            );
            
            camera->getTransform()->setPosition(glm::vec3(
                cam["position"][0], 
                cam["position"][1], 
                cam["position"][2]
            ));
            
            camera->getTransform()->setEuler(glm::vec3(
                cam["rotation"][0],
                cam["rotation"][1], 
                cam["rotation"][2]
            ));
            
            m_cameraList.push_back(camera);
        }

        // Load models
        for (auto& mdl : j["models"]) {
            Model* model = Model::createModel(
                mdl["textureName"],
                mdl["shaderName"],
                (ShapeTypes)(int)mdl["shapeType"]
            );
            
            model->getTransform()->setPosition(glm::vec3(
                mdl["position"][0],
                mdl["position"][1],
                mdl["position"][2]
            ));
            
            model->getTransform()->setEuler(glm::vec3(
                mdl["rotation"][0],
                mdl["rotation"][1],
                mdl["rotation"][2]
            ));
            
            model->getTransform()->setScale(glm::vec3(
                mdl["scale"][0],
                mdl["scale"][1],
                mdl["scale"][2]
            ));
            
            model->getTextureRepeat() = glm::vec2(
                mdl["textureRepeat"][0],
                mdl["textureRepeat"][1]
            );
            
            addModel(model);
        }

        // Restore selection states 
        if (!m_modelList.empty() && j.contains("selectedModelIndex")) {
            currentSelectedModel = j["selectedModelIndex"];
            currentSelectedModel = glm::clamp(currentSelectedModel, 0, (int)m_modelList.size() - 1);
        }

        if (!m_cameraList.empty()) {
            if (j.contains("activeCameraIndex")) {
                int activeIdx = j["activeCameraIndex"]; 
                m_activeCamera = m_cameraList[activeIdx];
            }
            if (j.contains("selectedCameraIndex")) {
                currentSelectedCamera = j["selectedCameraIndex"];
                currentSelectedCamera = glm::clamp(currentSelectedCamera, 0, (int)m_cameraList.size() - 1);
            }
            if (j.contains("viewportCameraIndex")) {
                viewportCameraIndex = j["viewportCameraIndex"];
                viewportCameraIndex = glm::clamp(viewportCameraIndex, 0, (int)m_cameraList.size() - 1);
            }
        }
    }
}