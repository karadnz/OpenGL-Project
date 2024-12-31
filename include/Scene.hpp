#ifndef scene_hpp
#define scene_hpp
#include "Model.hpp"
namespace graf
{
    class ShapeCreator;
    class Camera;
    class Scene
    {
    public:
        Scene();
        void addModel(Model* model);
        void addModel(const string& fileName);
        void removeModel(Model* model);
        void render();
        void renderGui();
        Camera* getActiveCamera();
    private:
        Camera*     m_activeCamera;
        ModelList   m_modelList;
    };
}
#endif