#ifndef shaderprogram_hpp
#define shaderprogram_hpp
#include<string>
#include<glm/glm.hpp>
#include<unordered_map>
using namespace std;
namespace graf
{
    class ShaderProgram
    {
    public:
        
        void create();
        void attachShader(const string& fileName,unsigned int shadertype);
        void link();
        void use();
        void unuse();
        void addUniform(const string& varName);
        void setVec3(const string& varname,const glm::vec3& value);
        void setVec2(const string& varname,const glm::vec2& value);
        void setVec4(const string& varname,const glm::vec4& value);
        void setMat4(const string& varname,const glm::mat4& value);
        void setFloat(const string& varname,float value);
    private:

        string getShaderFromFile(const string& fileName);
        unsigned int m_id;
        unordered_map<string,int> m_Uniforms;
    };
}


#endif