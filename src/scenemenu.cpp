#include "Scene.hpp"
#include<imgui/imgui.h>
#include "transform.hpp"
#include "camera.hpp"
namespace graf
{   
    void static inline __section(const char *msg)
    {
        ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Text(msg);
        ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

    }

    const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO", "PPPP", "QQQQQQQQQQ", "RRR", "SSSS" };
    glm::vec3 euler;
    void Scene::renderGui() {
        // Set window size and position
        ImGui::SetNextWindowSize(ImVec2(600, 1200), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);

        ImGui::Begin("Control", nullptr, ImGuiWindowFlags_NoCollapse);

        // Model Selection
        __section("Model Selection");
        
        static int selectedModelIndex = 0;
        if (ImGui::SliderInt("Selected Model", &selectedModelIndex, 0, (int)m_modelList.size() - 1)) {
            selectedModelIndex = glm::clamp(selectedModelIndex, 0, (int)m_modelList.size() - 1);
        }

        if (selectedModelIndex < m_modelList.size() && m_modelList[selectedModelIndex]) {
            Model* currentModel = m_modelList[selectedModelIndex];

            // Model Shape Type
            const char* shapeTypes[] = { "Circle", "Square", "Cube", "Pyramid", "Frustum" };
            int currentShape = (int)currentModel->getShapeType();
            if (ImGui::Combo("Shape Type", &currentShape, shapeTypes, IM_ARRAYSIZE(shapeTypes))) {
                currentModel->setShapeType((ShapeTypes)currentShape);
            }

            // Texture Controls
            __section("Textures");
            const char* textureNames[] = { "container.jpg", "container2.jpg", "container3.jpg" };
            static int currentTexture = 0;
            if (ImGui::Combo("Texture", &currentTexture, textureNames, IM_ARRAYSIZE(textureNames))) {
                currentModel->setTextureName(textureNames[currentTexture]);
            }

            // Texture Repeat
            ImGui::SliderFloat2("Texture Repeat", &currentModel->getTextureRepeat().x, 0.0f, 10.0f);

            // Transform Controls
            __section("Model Transform");
            
            // Position
            glm::vec3 position = currentModel->getTransform()->getPosition();
            if (ImGui::SliderFloat3("Position", &position.x, -10.0f, 10.0f)) {
                currentModel->getTransform()->setPosition(position);
            }

            // Rotation
            glm::vec3 rotation = currentModel->getTransform()->getEuler();
            if (ImGui::SliderFloat3("Rotation", &rotation.x, 0.0f, 360.0f)) {
                currentModel->getTransform()->setEuler(rotation);
            }

            // Scale
            glm::vec3 scale = currentModel->getTransform()->getScale();
            if (ImGui::SliderFloat3("Scale", &scale.x, 0.1f, 5.0f)) {
                currentModel->getTransform()->setScale(scale);
            }
        }

        // Camera Controls
        __section("Camera");
        
        // Camera Position
        glm::vec3 camPos = m_activeCamera->getTransform()->getPosition();
        if (ImGui::SliderFloat3("Camera Position", &camPos.x, -20.0f, 20.0f)) {
            m_activeCamera->getTransform()->setPosition(camPos);
        }

        // Camera Rotation
        glm::vec3 camRot = m_activeCamera->getTransform()->getEuler();
        if (ImGui::SliderFloat3("Camera Rotation", &camRot.x, -180.0f, 180.0f)) {
            m_activeCamera->getTransform()->setEuler(camRot);
        }

        // Camera Projection Parameters
        __section("Camera Projection"); 
        
        float fov = m_activeCamera->getFov();
        if (ImGui::SliderFloat("Field of View", &fov, 30.0f, 120.0f)) {
            m_activeCamera->setFov(fov);
        }

        float aspect = m_activeCamera->getAspect();
        if (ImGui::SliderFloat("Aspect Ratio", &aspect, 0.1f, 2.0f)) {
            m_activeCamera->setAspect(aspect);
        }

        float near_plane = m_activeCamera->getNear();
        if (ImGui::SliderFloat("Near Plane", &near_plane, 0.1f, 10.0f)) {
            m_activeCamera->setNear(near_plane);
        }

        float far_plane = m_activeCamera->getFar();
        if (ImGui::SliderFloat("Far Plane", &far_plane, 10.0f, 1000.0f)) {
            m_activeCamera->setFar(far_plane);
        }

        ImGui::End();
    }
}