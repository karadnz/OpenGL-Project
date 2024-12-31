#include "shaderprogram.hpp"
#include<glad/glad.h>
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
namespace graf
{
    void ShaderProgram::create()
    {
        m_id = glCreateProgram();
    }

    void ShaderProgram::addUniform(const string& varName)
    {

            m_Uniforms[varName]= glGetUniformLocation(m_id,varName.data());
        
    }
    void ShaderProgram::setVec4(const string& varName,const glm::vec4& value)
    {
        if(m_Uniforms.count(varName)>0)
        {
            glUniform4f( m_Uniforms[varName],value.r,value.g,value.b,value.a);
        }
    }
    void ShaderProgram::setMat4(const string& varName,const glm::mat4& value)
    {
        if(m_Uniforms.count(varName)>0)
        {
            glUniformMatrix4fv( m_Uniforms[varName],1,false,&value[0][0]);
        }
    }
    void ShaderProgram::setVec3(const string& varName,const glm::vec3& value)
    {
        if(m_Uniforms.count(varName)>0)
        {
            glUniform3f( m_Uniforms[varName],value.r,value.g,value.b);
        }
    }
    void ShaderProgram::setVec2(const string &varName, const glm::vec2 &value)
    {
        if(m_Uniforms.count(varName)>0)
        {
            glUniform2f( m_Uniforms[varName],value.x,value.y);
        }
    }
    void ShaderProgram::setFloat(const string &varName, float value)
    {
        if(m_Uniforms.count(varName)>0)
        {
            glUniform1f( m_Uniforms[varName],value);
        }
    }
    void ShaderProgram::link()
    {
        glLinkProgram(m_id);
    }
    void ShaderProgram::use()
    {
        glUseProgram(m_id);
    }
    void ShaderProgram::unuse()
    {
        glUseProgram(0);
    }
    void ShaderProgram::attachShader(
        const string &fileName,
        unsigned int shaderType)
    {
        unsigned int shaderId = glCreateShader(shaderType);

        string source = getShaderFromFile(fileName);

        const char* sourceTemp = &source[0];
        glShaderSource(shaderId, 1, &sourceTemp, NULL);
        glCompileShader(shaderId);
        
        GLint isCompiled = 0;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

            char*  errorLog = new char[maxLength];
            glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
            cout<<"shaderError:"<<errorLog<<endl;
            
            glDeleteShader(shaderId); 
            delete[] errorLog;
            return;
        }


        glAttachShader(m_id,shaderId);
    }

    string ShaderProgram::getShaderFromFile(const string& fileName)
    {
        std::ifstream file(fileName);

        std::string data;

        if(file.is_open())
        {
            
            char readChar;

            while((readChar=file.get())!=EOF)
            {
                data+=readChar;
            }
        
            file.close();
        }
    
        return data;

    }
}