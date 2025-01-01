#ifndef Camera_hpp
#define Camera_hpp
#include<glm/glm.hpp>
namespace graf
{
    class Transform;
    class Camera
    {
    public:
        Camera(
                float fov=90.0f,
                float aspect=1.0f,
                float near = 1.0f,
                float far = 100.0f
                
              );
        void turn(float angle);
        
        void look(float angle);
        Transform* getTransform();
        glm::mat4 getViewMatrix();
        glm::mat4 getProjMatrix();

        // Add getters/setters
        float getFov() const { return m_fov; }
        float getAspect() const { return m_aspect; }
        float getNear() const { return m_near; }
        float getFar() const { return m_far; }
        
        void setFov(float fov);
        void setAspect(float aspect);
        void setNear(float near_plane);
        void setFar(float far_plane);

    private:
        float m_fov;
        float m_aspect;
        float m_near;
        float m_far;
        glm::mat4 m_mtxProj;
        Transform* m_Transform;
    };
}

#endif