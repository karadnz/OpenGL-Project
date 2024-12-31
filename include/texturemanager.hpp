#ifndef texturemanager_hpp
#define texturemanager_hpp
#include<unordered_map>
#include<string>
using namespace std;
namespace graf
{
    class TextureManager
    {
    public:
        static void addTextureFromFile(const string& fileName);
        static void activateTexture(const string& textureFileName);

    private:

        TextureManager();

        static TextureManager* m_Instance;
        static TextureManager* getInstance();

        unordered_map<string,unsigned int> m_TextureMap;
    };
}



#endif