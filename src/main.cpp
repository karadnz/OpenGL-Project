#define GLFW_INCLUDE_NONE

#include "GLWindow.hpp"
#include "shaderprogram.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "texturemanager.hpp"
#include "vertexarrayobject.hpp"
#include "camera.hpp"
#include "shapecreator.hpp"
#include "Transform.hpp"
#include<imgui/imgui.h>
#include "shadermanager.hpp"
#include "Model.hpp"
#include "Scene.hpp"
#include<iostream>
using namespace std;

void printMatrix(const glm::mat4& mtx);
void testModels(std::vector<std::string> &modelFiles,  graf::Scene &scene);



int main(int arc, char** argv)
{
    graf::GLWindow glwindow;
    glwindow.create(800, 800);

    graf::Scene scene;

    // Create models
    std::vector<std::string> modelFiles =
    {
        "LightTextureCube.json",        
        "TextureSquare.json"            
    };

    testModels(modelFiles, scene);

    // Define positions for walls and ground
    std::vector<glm::vec3> positions = {
        glm::vec3(-5.0f, 0.0f, 0.0f),   // Left wall
        glm::vec3(5.0f, 0.0f, 0.0f),    // Right wall
        glm::vec3(0.0f, -2.5f, 0.0f)    // Ground
    };

    // Define scales for walls and ground
    std::vector<glm::vec3> scales = {
        glm::vec3(0.1f, 5.0f, 10.0f),   // Left wall
        glm::vec3(0.1f, 5.0f, 10.0f),   // Right wall
        glm::vec3(10.0f, 0.1f, 10.0f)   // Ground
    };

    // Create and configure models
    for (size_t i = 0; i < 3; ++i)
    {
        graf::Model* model = graf::Model::loadModelFromFile(modelFiles[0]);
        model->getTransform()->setPosition(positions[i]);
        model->getTransform()->setScale(scales[i]);
        scene.addModel(model);
    }

    double oldMouseX = -1.0f;
    double oldMouseY = -1.0f;
    double dx = 0.0f;
    double dy = 0.0f;

    graf::Camera* camera = scene.getActiveCamera();
    camera->getTransform()->setPosition(glm::vec3(0.0f, 2.0f, -10.0f)); // Position camera to view the scene

    glwindow.setKeyboardFunction([&](int key, int scancode, int action)
    {
        if(key == GLFW_KEY_LEFT); // scene.removeModel(&model);

        if(key == GLFW_KEY_RIGHT);// scene.addModel(&model);//           transform.moveBackward();

        if(key == GLFW_KEY_A) camera->getTransform()->moveLeft();

        if(key == GLFW_KEY_D) camera->getTransform()->moveRight();


        if(key == GLFW_KEY_W)  camera->getTransform()->moveForward();

        if(key == GLFW_KEY_S) camera->getTransform()->moveBackward();
 
        if(key == GLFW_KEY_KP_4)
        {
           
        }
        if(key == GLFW_KEY_KP_6)
        {
            
        }

        
    });
    glwindow.setMouseFunction([&](double xpos,double ypos){

        if(oldMouseX==-1)
        {
            oldMouseX = xpos;
            oldMouseY = ypos;
        }
        camera->turn(dx*.1f);
        camera->look(dy*.1f);
        dx = xpos-oldMouseX;
        dy = ypos-oldMouseY;

        oldMouseX= xpos;
        oldMouseY=ypos;

        //cout << "x: " << oldMouseX << "| y: " << oldMouseY << "\n";
        //camera->getProjMatrix
      
    });

    
    glwindow.setRenderFunction([&]()
    {
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
        
        scene.render();
    });
    
    glwindow.render();

    exit(EXIT_SUCCESS);
}


void testModels(std::vector<std::string> &modelFiles,  graf::Scene &scene)
{
    for (size_t i = 0; i < modelFiles.size(); ++i)
    {
        graf::Model* model = graf::Model::loadModelFromFile(modelFiles[i]);
        model->getTransform()->setPosition(glm::vec3(-2.0f * i, 1.0f, 1.0f));
        scene.addModel(model);
        //"LightTextureSquare.json",      
        //"TextureCube.json", 
    }
}

void printMatrix(const glm::mat4& mtx)
{
    if (ImGui::BeginTable("Matrix", 4, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
    {
                
                
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("%-.3f",mtx[0][0]);
        ImGui::TableNextColumn(); ImGui::Text("%-.3f",mtx[1][0]);
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[2][0]);
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[3][0]);
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[0][1]);
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[1][1]);
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[2][1]);
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[3][1]);
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[0][2]);
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[1][2]);
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[2][2]);
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[3][2]);
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[0][3]);
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[1][3]);
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[2][3]);
        ImGui::TableNextColumn(); ImGui::Text("%.3f",mtx[3][3]);
        ImGui::EndTable();
    }
}