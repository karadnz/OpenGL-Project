#include "transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/euler_angles.hpp>

namespace graf
{
    Transform::Transform()
    {
        m_Position = glm::vec3(0.0f);
        m_Euler = glm::vec3(0.0f);
        m_MtxWorld = glm::mat4(1.0f);
        m_MtxRotation = glm::mat4(1.0f);
        m_MtxTranslate = glm::mat4(1.0f);

        //my stuff
        m_Scale = glm::vec3(1.0f);
    }
    glm::vec3 Transform::getPosition()
    {
        return m_Position;
    }
    void Transform::moveForward()
    {
        m_Position+=glm::normalize(getLook());

        update();
    }
        void Transform::moveRight()
    {
        m_Position+=glm::normalize(getRight());

        update();
    }
        void Transform::moveLeft()
    {
        m_Position+=glm::normalize(-getRight());

        update();
    }
    void Transform::moveBackward()
    {
        m_Position-=glm::normalize(getLook());
        update();
    }
    glm::vec3 Transform::getLook()
    {
        return glm::vec3(m_MtxRotation[2][0],m_MtxRotation[2][1],m_MtxRotation[2][2]);
    }
    glm::vec3 Transform::getUp()
    {
        return glm::vec3(m_MtxRotation[1][0],m_MtxRotation[1][1],m_MtxRotation[1][2]);
    }
    glm::vec3 Transform::getRight()
    {
        return glm::vec3(m_MtxRotation[0][0],m_MtxRotation[0][1],m_MtxRotation[0][2]);
    }    
    void Transform::update()
    {
        m_MtxTranslate = glm::translate(glm::mat4(1), m_Position);
        glm::mat4 mtxScale = glm::scale(glm::mat4(1), m_Scale);
        m_MtxWorld = m_MtxTranslate * m_MtxRotation * mtxScale;
    }
    glm::vec3& Transform::getEuler()
    {
        return m_Euler;
    }
    void Transform::setEuler(const glm::vec3& euler)
    {
            m_Euler = euler;
        m_MtxRotation = glm::mat4(1);
        float radX =  glm::radians(euler.x);
        float radY =  glm::radians(euler.y);
        float radZ =  glm::radians(euler.z);

        auto vecRight   = glm::vec3(1.0f,0.0f,0.0f);
        auto vecUp      = glm::vec3(0.0f,1.0f,0.0f);
        auto vecLook    = glm::vec3(0.0f,0.0f,1.0f);

        glm::mat4 mtxRotZ = glm::rotate(glm::mat4(1),radZ,vecLook);

        vecRight      = mtxRotZ*glm::vec4(vecRight,0.0f);
        vecUp         = mtxRotZ*glm::vec4(vecUp,0.0f);
      
        if(radY)
        {
            glm::mat4 mtxRotY = glm::rotate(glm::mat4(1),radY,vecUp);

            vecRight    = mtxRotY*glm::vec4(vecRight,0.0f);
            vecLook     = mtxRotY*glm::vec4(vecLook,0.0f);
        }

        if(radX)
        {
            glm::mat4 mtxRotX = glm::rotate(glm::mat4(1),radX,vecRight);

            vecLook    = mtxRotX*glm::vec4(vecLook,0.0f);
            vecUp       = mtxRotX*glm::vec4(vecUp,0.0f);

        }
        vecRight    = glm::normalize(vecRight);
        vecUp       = glm::normalize(vecUp);
        vecLook     = glm::normalize(vecLook);
        
        m_MtxRotation[0] = glm::vec4(vecRight,0.0f);
        m_MtxRotation[1] = glm::vec4(vecUp,0.0f);
        m_MtxRotation[2] = glm::vec4(vecLook,0.0f);
        
        update();
    
        
    }
    void Transform::rotateLocalY(float angle)
    {
        float radY = glm::radians(angle);
        glm::vec3 normY = glm::normalize(getUp());
        glm::mat4 rotY = glm::rotate(glm::mat4(1.0f),radY,normY);

        glm::vec3 look = glm::normalize(getLook());
        glm::vec3 right = glm::normalize(getRight());

        look = rotY*glm::vec4(look,0.0f);
        right = rotY*glm::vec4(right,0.0f);

        look = glm::normalize(look);
        right = glm::normalize(right);

        m_MtxRotation[2][0] = look.x;
        m_MtxRotation[2][1] = look.y;
        m_MtxRotation[2][2] = look.z;
        m_MtxRotation[0][0] = right.x;
        m_MtxRotation[0][1] = right.y;
        m_MtxRotation[0][2] = right.z;
        update();
    }

    void Transform::rotateLocalX(float angle)
    {
        float radX = glm::radians(angle);
        glm::vec3 normX = glm::normalize(getRight());
        glm::mat4 rotX = glm::rotate(glm::mat4(1.0f),radX,normX);

        glm::vec3 up = glm::normalize(getUp());
        glm::vec3 look = glm::normalize(getLook());

        look = rotX*glm::vec4(look,0.0f);
        up = rotX*glm::vec4(up,0.0f);

        look = glm::normalize(look);
        up = glm::normalize(up);

        m_MtxRotation[2][0] = look.x;
        m_MtxRotation[2][1] = look.y;
        m_MtxRotation[2][2] = look.z;
        m_MtxRotation[1][0] = up.x;
        m_MtxRotation[1][1] = up.y;
        m_MtxRotation[1][2] = up.z;
        update();
    }
    glm::mat4 Transform::getRotationMatrix()
    {
        return m_MtxRotation;
    }
    glm::mat4 Transform::getMatrix()
    {
        return m_MtxWorld;
    }
    void Transform::setPosition(const glm::vec3& position)
    {
        m_Position = position;
        m_MtxTranslate = glm::translate(glm::mat4(1.0f),m_Position);
        update();
    }
    void Transform::setScale(const glm::vec3& scale)
    {
        m_Scale = scale;
        update();
    }
}