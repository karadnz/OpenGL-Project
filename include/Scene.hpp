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
        ~Scene();
        void addModel(Model* model);
        void addModel(const string& fileName);
        void removeModel(Model* model);
        void render();
        void renderGui();
        Camera* getActiveCamera();
        void saveScene(const string& filename);
        void loadScene(const string& filename);
    private:
        Camera*     m_activeCamera;
        std::vector<Camera*> m_cameraList;
        ModelList   m_modelList;
        int currentSelectedModel = 0;  // Track currently selected model
        int currentSelectedCamera = 0; // Track currently selected camera
        Model* m_selectionCube;  // Add this line: Model for selection indicator
        int viewportCameraIndex = 0; // Track camera used for viewport
        Model* m_cameraIndicator;  // Add this line: Model for camera position indicators
    };
}
#endif