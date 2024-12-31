#ifndef vertextypes_hpp
#define vertextypes_hpp
#include<glm/glm.hpp>
namespace graf
{

    class Vertex
    {
    public:
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texture;
    };


}
#endif