#ifndef shadermanager_hpp
#define shadermanager_hpp
#include <string>
#include <unordered_map>
using namespace std;
namespace graf
{
    class ShaderProgram;
    class ShaderManager
    {
    public:
        static void addShaderFromFile(const string& fileName);
        static ShaderProgram* getProgram(const string& textureFileName);

    private:

        ShaderManager();

        static ShaderManager* m_Instance;
        static ShaderManager* getInstance();

        unordered_map<string,ShaderProgram*> m_shaderMap;
    };
}

#endif