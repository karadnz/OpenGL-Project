#include "camera.hpp"
#include "transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace graf
{
    Camera::Camera(
                float fov,
                float aspect,
                float near ,
                float far
              )
    {
        m_Transform=  new Transform;

        m_mtxProj= glm::perspectiveLH(fov,aspect,near,far);
        m_fov = fov;
        m_aspect = aspect;
        m_near = near;
        m_far = far;
    }
    glm::mat4 Camera::getProjMatrix()
    {
        return m_mtxProj;
    }
    void Camera::turn(float angle)
    {
        auto euler = m_Transform->getEuler();
        euler.y+=angle;
        m_Transform->setEuler(euler);
    }
    void Camera::look(float angle)
    {
        auto euler = m_Transform->getEuler();
        euler.x+=angle;
        m_Transform->setEuler(euler);
    }
    Transform* Camera::getTransform()
    {
        return m_Transform;
    }
    glm::mat4 Camera::getViewMatrix()
    {
        auto mtxInvTranslate = glm::translate(glm::mat4(1),-m_Transform->getPosition());
        auto mtxInvRotation = glm::inverse(m_Transform->getRotationMatrix());

        return mtxInvRotation*mtxInvTranslate;
    }
}