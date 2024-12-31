#include "shadermanager.hpp"
#include "shaderprogram.hpp"
#include <fstream>
#include<iostream>
#include<nlohmann/json.hpp>
#include<glad/glad.h>
using namespace std;
namespace graf
{
    ShaderManager* ShaderManager::m_Instance =nullptr;

    ShaderManager::ShaderManager()
    {

    }
    ShaderManager* ShaderManager::getInstance()
    {
        if(m_Instance==nullptr)
        {
            m_Instance = new ShaderManager();
        }
        return m_Instance;
    }
    ShaderProgram* ShaderManager::getProgram(const string& fileName)
    {
        auto manager= getInstance();
        if(manager->m_shaderMap.count(fileName)>0)
            return manager->m_shaderMap[fileName];
        return nullptr;
    }
     void ShaderManager::addShaderFromFile(const string& fileName)
    {

        auto manager= getInstance();
        if(manager->m_shaderMap.count(fileName)==0)
        {
            //./shader/TextureShader/TextureShader.json
            string path = "./shaders/"+fileName+"/";
            std::ifstream file(path+"settings.json");

            using namespace nlohmann;
            auto data = json::parse(file);

            string programName = data["ProgramName"].get<string>();
            string vertexShader = data["VertexShader"].get<string>();
            string fragmentShader = data["FragmentShader"].get<string>();
            
            ShaderProgram* program = new ShaderProgram();
            program->create();
            program->attachShader(path+vertexShader,GL_VERTEX_SHADER);
            program->attachShader(path+fragmentShader,GL_FRAGMENT_SHADER);
            program->link();

            auto uniform = data["Uniforms"];

            for(auto siradaki:uniform)
            {
                string varName = siradaki["Name"].get<string>();
                program->addUniform(varName);
                
            }

            manager->m_shaderMap[fileName] = program;

        }


    }

}