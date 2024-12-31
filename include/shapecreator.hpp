#ifndef shapecreator_hpp
#define shapecreator_hpp
#include<unordered_map>
namespace graf
{
    enum class ShapeTypes
    {
        Circle,
        Square,
        Cube,
        Pyramid,    // Added
        Frustum     // Added
    };

    class VertexArrayObject;
    class ShapeCreator
    {
    public:
        static VertexArrayObject* createShape(ShapeTypes type);
       
    private:
        ShapeCreator();
        static ShapeCreator* m_Instance;
        VertexArrayObject* createSquare();
        VertexArrayObject* createCircle(int anglesInDegree=10);
        VertexArrayObject* createCube();
        VertexArrayObject* createPyramid();
        VertexArrayObject* createFrustum();
        
        std::unordered_map<ShapeTypes,VertexArrayObject*> m_vaoMap;
    };
}

#endif