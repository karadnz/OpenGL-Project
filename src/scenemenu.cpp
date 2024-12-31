#include "Scene.hpp"
#include<imgui/imgui.h>
#include "transform.hpp"
namespace graf
{
    const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO", "PPPP", "QQQQQQQQQQ", "RRR", "SSSS" };
    glm::vec3 euler;
    void Scene::renderGui()
    {


        ImGui::Begin("Control");
        ImGui::SliderFloat2("TextureRepeat",&m_modelList[0]->getTextureRepeat().x,0.0f,10.0f);
        if(ImGui::SliderFloat3("Rotation",&euler.x,0.0f,360.0f))
        {
            m_modelList[0]->getTransform()->setEuler(euler);
        }
        
        
        static const char* current_item = items[0];
        unsigned int index = 0;
        if (ImGui::BeginCombo("combo", current_item)) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                bool is_selected = (current_item == items[n]); 

                if (ImGui::Selectable(items[n], is_selected))
                {
                        current_item = items[n];
                        index =n ;
                }
                if(is_selected)
                    index=n;    
               
            }
            ImGui::EndCombo();

           
        }
          
        
        ImGui::End();
    }
}