#ifndef transform_hpp
#define transform_hpp
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace graf
{
    class Transform
    {
    public:
        Transform();
        glm::vec3 getPosition();
        glm::vec3& getEuler();
        glm::mat4 getMatrix();

        glm::vec3 getLook();
        glm::vec3 getUp();
        glm::vec3 getRight();
        void moveForward();
        void moveBackward();
        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();
        void rotateLocalY(float angle);
        void rotateLocalX(float angle);
        void rotateLocalZ(float angle);
        void setPosition(const glm::vec3& position);
        void update();
        void setEuler(const glm::vec3& euler);
        glm::mat4 getRotationMatrix();

        // my stuff
        void setScale(const glm::vec3& scale);
        glm::vec3 getScale(void);
    private:
        glm::mat4 m_MtxRotation;
        glm::mat4 m_MtxWorld;
        glm::mat4 m_MtxTranslate;
        glm::vec3 m_Euler;
        glm::vec3 m_Position;

        // my stuff
        glm::vec3 m_Scale;
    };
}


#endif