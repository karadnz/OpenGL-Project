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
        // Left Control Panel
        {
            ImGui::SetNextWindowSize(ImVec2(600, 1200), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
            ImGui::Begin("Control", nullptr, ImGuiWindowFlags_NoCollapse);

            // Camera Selection
            __section("Active Camera");
            if (ImGui::SliderInt("Selected Camera", &currentSelectedCamera, 0, (int)m_cameraList.size() - 1)) {
                currentSelectedCamera = glm::clamp(currentSelectedCamera, 0, (int)m_cameraList.size() - 1);
                m_activeCamera = m_cameraList[currentSelectedCamera];
            }
            
            // Add viewport camera selection
            if (ImGui::SliderInt("Viewport Camera", &viewportCameraIndex, 0, (int)m_cameraList.size() - 1)) {
                viewportCameraIndex = glm::clamp(viewportCameraIndex, 0, (int)m_cameraList.size() - 1);
            }

            // Model Selection
            __section("Model Selection");
            
            if (ImGui::SliderInt("Selected Model", &currentSelectedModel, 0, (int)m_modelList.size() - 1)) {
                currentSelectedModel = glm::clamp(currentSelectedModel, 0, (int)m_modelList.size() - 1);
            }

            if (currentSelectedModel < m_modelList.size() && m_modelList[currentSelectedModel]) {
                Model* currentModel = m_modelList[currentSelectedModel];

                // Model Shape Type
                const char* shapeTypes[] = { "Circle", "Square", "Cube", "Pyramid", "Frustum" };
                int currentShape = (int)currentModel->getShapeType();
                if (ImGui::Combo("Shape Type", &currentShape, shapeTypes, IM_ARRAYSIZE(shapeTypes))) {
                    currentModel->setShapeType((ShapeTypes)currentShape);
                }

                // Texture Controls
                __section("Textures");
                const char* textureNames[] = { "container.jpg", "container2.jpg", "container3.jpg", "wall.jpg" };
                static int currentTexture = 0;
                if (ImGui::Combo("Texture", &currentTexture, textureNames, IM_ARRAYSIZE(textureNames))) {
                    currentModel->setTextureName(textureNames[currentTexture]);
                }

                // Texture Repeat
                ImGui::SliderFloat2("Texture Repeat", &currentModel->getTextureRepeat().x, 0.0f, 20.0f);

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
                if (ImGui::SliderFloat3("Scale", &scale.x, 0.1f, 100.0f)) {
                    currentModel->getTransform()->setScale(scale);
                }
            }

            // Camera Controls
            __section("Camera");
            
            // Camera Position
            glm::vec3 camPos = m_activeCamera->getTransform()->getPosition();
            if (ImGui::SliderFloat3("Camera Position", &camPos.x, -70.0f, 70.0f)) {
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

            // Add save/load buttons at bottom of Control window
            ImGui::SetCursorPos(ImVec2(10, ImGui::GetWindowSize().y - 40));
            if (ImGui::Button("Save Scene", ImVec2((ImGui::GetWindowSize().x - 30)/2, 30))) {
                saveScene("scene.json");
            }
            ImGui::SameLine();
            if (ImGui::Button("Load Scene", ImVec2((ImGui::GetWindowSize().x - 30)/2, 30))) {
                loadScene("scene.json"); 
            }

            ImGui::End();
        }

        // Right Creation Panel
        {
            ImGui::SetNextWindowSize(ImVec2(400, 600), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 420, ImGui::GetIO().DisplaySize.y - 620), ImGuiCond_FirstUseEver);
            ImGui::Begin("Creation", nullptr, ImGuiWindowFlags_NoCollapse);

            __section("Model Creation");
            
            static int selectedShape = 0;
            const char* shapeTypes[] = { "Circle", "Square", "Cube", "Pyramid", "Frustum" };
            ImGui::Combo("Shape Type", &selectedShape, shapeTypes, IM_ARRAYSIZE(shapeTypes));

            static int selectedTexture = 0;
            const char* textureNames[] = { "container.jpg", "container2.jpg", "container3.jpg" };
            ImGui::Combo("Texture", &selectedTexture, textureNames, IM_ARRAYSIZE(textureNames));

            static glm::vec2 textureRepeat(1.0f, 1.0f);
            ImGui::SliderFloat2("Texture Repeat", &textureRepeat.x, 0.0f, 10.0f);

            if (ImGui::Button("Create Model", ImVec2(-1, 0))) {
                Model* model = Model::createModel(textureNames[selectedTexture],
                                                    "LightTextureShader",
                                                    (ShapeTypes)selectedShape);
                model->getTextureRepeat() = textureRepeat;
                addModel(model);
            }

            __section("Camera Creation");
            
            static float fov = 90.0f;
            static float nearPlane = 0.1f;
            static float farPlane = 100.0f;
            static float width = 800.0f;
            static float height = 800.0f;

            ImGui::SliderFloat("Field of View", &fov, 30.0f, 120.0f);
            ImGui::SliderFloat("Near Plane", &nearPlane, 0.1f, 10.0f);
            ImGui::SliderFloat("Far Plane", &farPlane, 10.0f, 1000.0f);
            ImGui::SliderFloat("Width", &width, 100.0f, 3000.0f);
            ImGui::SliderFloat("Height", &height, 100.0f, 3000.0f);

            if (ImGui::Button("Create Camera", ImVec2(-1, 0))) {
                Camera* camera = new Camera(fov, width/height, nearPlane, farPlane);
                m_cameraList.push_back(camera);
            }

            ImGui::End();
        }
    }
}