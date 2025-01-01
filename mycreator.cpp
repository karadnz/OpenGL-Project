#include "shapecreator.hpp"
#include "vertexarrayobject.hpp"
#include "indexbuffer.hpp"
#include "vertexbuffer.hpp"
#include "vertextypes.hpp"
namespace graf
{
    VertexArrayObject *ShapeCreator::create(ShapeTypes shape)
    {
        switch (shape)
        {
        case ShapeTypes::Square:
            return createSquare();

        case ShapeTypes::Circle:
            return createCircle(10);

        case ShapeTypes::Cube:
            return createCube();

        case ShapeTypes::Pyramid:
            return createPyramid();

        case ShapeTypes::Frustum:
            return createFrustum();
        default:
            return nullptr;
            break;
        }
    }
    VertexArrayObject *ShapeCreator::createCircle(int anglesInDegrees)
    {

        if (m_vaoMap.count(ShapeTypes::Circle) > 0)
            return m_vaoMap[ShapeTypes::Circle];

        graf::VertexArrayObject *va = new VertexArrayObject();
        graf::VertexBuffer *vb = new VertexBuffer();
        graf::IndexBuffer *ib = new IndexBuffer();

        int vertexCount = 360 / anglesInDegrees;
        int faceCount = vertexCount - 2;

        VertexList vertices;
        IndexList indices;

        for (int i = 0; i < vertexCount; i++)
        {
            Vertex vertex;

            double currentAngle = anglesInDegrees * i;
            vertex.position.x = glm::cos(glm::radians(currentAngle));
            vertex.position.y = glm::sin(glm::radians(currentAngle));
            vertex.position.z = 0.0f;
            vertex.texture.s = 0.5 + 0.5 * glm::cos(glm::radians(currentAngle));
            vertex.texture.t = 0.5 + 0.5 * glm::sin(glm::radians(currentAngle));
            vertices.emplace_back(vertex);
        }
        for (int i = 0; i < faceCount; i++)
        {
            indices.emplace_back(0);
            indices.emplace_back(i + 2);
            indices.emplace_back(i + 1);
        }
        va->create();
        vb->create(&vertices[0], sizeof(Vertex) * vertices.size());
        ib->create(&indices[0], sizeof(unsigned int) * indices.size());
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);
        va->addVertexAttribute(graf::VertexAttributeType::Position);
        va->addVertexAttribute(graf::VertexAttributeType::Texture);
        va->activateAttributes();

        m_vaoMap[ShapeTypes::Circle] = va;

        // va->unbind();

        return va;
    }
    VertexArrayObject *ShapeCreator::createSquare()
    {
        if (m_vaoMap.count(ShapeTypes::Square) > 0)
            return m_vaoMap[ShapeTypes::Square];

        float vertices[] = {
            /*   x     y     z     s    t */
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

        unsigned int indices[] = {
            0, 1, 2, 3, 4, 5};
        VertexArrayObject *va = new VertexArrayObject;
        VertexBuffer *vb = new VertexBuffer;
        IndexBuffer *ib = new IndexBuffer;

        vb->create(vertices, sizeof(vertices));
        ib->create(indices, sizeof(indices));
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);

        va->addVertexAttribute(VertexAttributeType::Position);
        va->addVertexAttribute(VertexAttributeType::Texture);
        va->activateAttributes();
        m_vaoMap[ShapeTypes::Square] = va;

        // va->unbind();

        return va;
    }
    VertexArrayObject *ShapeCreator::createCube()
    {
        if (m_vaoMap.count(ShapeTypes::Cube) > 0)
            return m_vaoMap[ShapeTypes::Cube];

        glm::vec3 positions[] = {
            {-0.5f, 0.5f, 0.5f},
            {0.5f, 0.5f, 0.5f},
            {0.5f, -0.5f, 0.5f},
            {-0.5f, -0.5f, 0.5f},

            {-0.5f, 0.5f, -0.5f},
            {0.5f, 0.5f, -0.5f},
            {0.5f, -0.5f, -0.5f},
            {-0.5f, -0.5f, -0.5f}};

        int vertexCount = 24;
        Vertex *vertices = new Vertex[vertexCount];
        std::vector<unsigned int> indices;

        // Ön Yüz
        vertices[0].position = positions[0];
        vertices[1].position = positions[1];
        vertices[2].position = positions[2];
        vertices[3].position = positions[3];

        vertices[0].texture = glm::vec2(0.0f, 1.0f);
        vertices[1].texture = glm::vec2(1.0f, 1.0f);
        vertices[2].texture = glm::vec2(1.0f, 0.0f);
        vertices[3].texture = glm::vec2(0.0f, 0.0f);

        // Sağ Yüz
        vertices[4].position = positions[1];
        vertices[5].position = positions[5];
        vertices[6].position = positions[6];
        vertices[7].position = positions[2];

        vertices[4].texture = glm::vec2(0.0f, 1.0f);
        vertices[5].texture = glm::vec2(1.0f, 1.0f);
        vertices[6].texture = glm::vec2(1.0f, 0.0f);
        vertices[7].texture = glm::vec2(0.0f, 0.0f);

        // Üst Yüz
        vertices[8].position = positions[4];
        vertices[9].position = positions[5];
        vertices[10].position = positions[1];
        vertices[11].position = positions[0];

        vertices[8].texture = glm::vec2(0.0f, 1.0f);
        vertices[9].texture = glm::vec2(1.0f, 1.0f);
        vertices[10].texture = glm::vec2(1.0f, 0.0f);
        vertices[11].texture = glm::vec2(0.0f, 0.0f);

        // Sol Yüz
        vertices[12].position = positions[4];
        vertices[13].position = positions[0];
        vertices[14].position = positions[3];
        vertices[15].position = positions[7];

        vertices[12].texture = glm::vec2(0.0f, 1.0f);
        vertices[13].texture = glm::vec2(1.0f, 1.0f);
        vertices[14].texture = glm::vec2(1.0f, 0.0f);
        vertices[15].texture = glm::vec2(0.0f, 0.0f);

        // Arka Yüz
        vertices[16].position = positions[5];
        vertices[17].position = positions[4];
        vertices[18].position = positions[7];
        vertices[19].position = positions[6];

        vertices[16].texture = glm::vec2(0.0f, 1.0f);
        vertices[17].texture = glm::vec2(1.0f, 1.0f);
        vertices[18].texture = glm::vec2(1.0f, 0.0f);
        vertices[19].texture = glm::vec2(0.0f, 0.0f);

        // Alt Yüz
        vertices[20].position = positions[3];
        vertices[21].position = positions[2];
        vertices[22].position = positions[6];
        vertices[23].position = positions[7];

        vertices[20].texture = glm::vec2(0.0f, 1.0f);
        vertices[21].texture = glm::vec2(1.0f, 1.0f);
        vertices[22].texture = glm::vec2(1.0f, 0.0f);
        vertices[23].texture = glm::vec2(0.0f, 0.0f);
        for (int i = 0; i < 6; i++)
        {
            indices.push_back(i * 4);
            indices.push_back(i * 4 + 2);
            indices.push_back(i * 4 + 1);

            indices.push_back(i * 4);
            indices.push_back(i * 4 + 3);
            indices.push_back(i * 4 + 2);
        }

        VertexArrayObject *va = new VertexArrayObject;
        VertexBuffer *vb = new VertexBuffer;
        IndexBuffer *ib = new IndexBuffer;

        vb->create(vertices, sizeof(Vertex) * vertexCount);
        ib->create(indices.data(), indices.size() * sizeof(unsigned int));
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);

        va->addVertexAttribute(VertexAttributeType::Position);
        va->addVertexAttribute(VertexAttributeType::Texture);
        va->activateAttributes();
        m_vaoMap[ShapeTypes::Cube] = va;

        // va->unbind();
        return va;
    }

    // Implement the createPyramid function
    VertexArrayObject *ShapeCreator::createPyramid()
    {
        if (m_vaoMap.count(ShapeTypes::Pyramid) > 0)
            return m_vaoMap[ShapeTypes::Pyramid];

        // Vertex positions for a square-based pyramid
        glm::vec3 positions[] = {
            // Base vertices
            {-0.5f, -0.5f, 0.5f},  // front-left
            {0.5f, -0.5f, 0.5f},   // front-right
            {0.5f, -0.5f, -0.5f},  // back-right
            {-0.5f, -0.5f, -0.5f}, // back-left
            {0.0f, 0.5f, 0.0f}     // top vertex
        };

        int vertexCount = 18; // 3 vertices per triangle * (4 side faces + 2 triangles for base)
        Vertex *vertices = new Vertex[vertexCount];
        std::vector<unsigned int> indices;

        // Front face
        vertices[0].position = positions[0];
        vertices[1].position = positions[1];
        vertices[2].position = positions[4];

        vertices[0].texture = glm::vec2(0.0f, 0.0f);
        vertices[1].texture = glm::vec2(1.0f, 0.0f);
        vertices[2].texture = glm::vec2(0.5f, 1.0f);

        // Right face
        vertices[3].position = positions[1];
        vertices[4].position = positions[2];
        vertices[5].position = positions[4];

        vertices[3].texture = glm::vec2(0.0f, 0.0f);
        vertices[4].texture = glm::vec2(1.0f, 0.0f);
        vertices[5].texture = glm::vec2(0.5f, 1.0f);

        // Back face
        vertices[6].position = positions[2];
        vertices[7].position = positions[3];
        vertices[8].position = positions[4];

        vertices[6].texture = glm::vec2(0.0f, 0.0f);
        vertices[7].texture = glm::vec2(1.0f, 0.0f);
        vertices[8].texture = glm::vec2(0.5f, 1.0f);

        // Left face
        vertices[9].position = positions[3];
        vertices[10].position = positions[0];
        vertices[11].position = positions[4];

        vertices[9].texture = glm::vec2(0.0f, 0.0f);
        vertices[10].texture = glm::vec2(1.0f, 0.0f);
        vertices[11].texture = glm::vec2(0.5f, 1.0f);

        // Base (two triangles)
        vertices[12].position = positions[0];
        vertices[13].position = positions[1];
        vertices[14].position = positions[2];

        vertices[12].texture = glm::vec2(0.0f, 0.0f);
        vertices[13].texture = glm::vec2(1.0f, 0.0f);
        vertices[14].texture = glm::vec2(1.0f, 1.0f);

        vertices[15].position = positions[0];
        vertices[16].position = positions[2];
        vertices[17].position = positions[3];

        vertices[15].texture = glm::vec2(0.0f, 0.0f);
        vertices[16].texture = glm::vec2(1.0f, 1.0f);
        vertices[17].texture = glm::vec2(0.0f, 1.0f);

        // Generate indices
        for (int i = 0; i < vertexCount; i++)
        {
            indices.push_back(i);
        }

        VertexArrayObject *va = new VertexArrayObject;
        VertexBuffer *vb = new VertexBuffer;
        IndexBuffer *ib = new IndexBuffer;

        vb->create(vertices, sizeof(Vertex) * vertexCount);
        ib->create(indices.data(), indices.size() * sizeof(unsigned int));
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);

        va->addVertexAttribute(VertexAttributeType::Position);
        va->addVertexAttribute(VertexAttributeType::Texture);
        va->activateAttributes();
        m_vaoMap[ShapeTypes::Pyramid] = va;

        va->unbind();
        delete[] vertices;
        return va;
    }

    VertexArrayObject *ShapeCreator::createFrustum()
    {
        if (m_vaoMap.count(ShapeTypes::Frustum) > 0)
            return m_vaoMap[ShapeTypes::Frustum];

        float topScale = 0.5f;

        glm::vec3 positions[] = {
            // Bottom vertices
            {-0.5f, -0.5f, 0.5f},  // front-left
            {0.5f, -0.5f, 0.5f},   // front-right
            {0.5f, -0.5f, -0.5f},  // back-right
            {-0.5f, -0.5f, -0.5f}, // back-left

            // Top vertices (scaled)
            {-0.5f * topScale, 0.5f, 0.5f * topScale}, // front-left
            {0.5f * topScale, 0.5f, 0.5f * topScale},  // front-right
            {0.5f * topScale, 0.5f, -0.5f * topScale}, // back-right
            {-0.5f * topScale, 0.5f, -0.5f * topScale} // back-left
        };

        int vertexCount = 24;
        Vertex *vertices = new Vertex[vertexCount];
        std::vector<unsigned int> indices;

        // Front face - adjust texture coords to match trapezoidal shape
        vertices[0].position = positions[0];
        vertices[1].position = positions[1];
        vertices[2].position = positions[5];
        vertices[3].position = positions[4];

        vertices[0].texture = glm::vec2(0.0f, 0.0f);
        vertices[1].texture = glm::vec2(1.0f, 0.0f);
        vertices[2].texture = glm::vec2(0.5f + topScale / 2, 1.0f); // Adjusted for top scale
        vertices[3].texture = glm::vec2(0.5f - topScale / 2, 1.0f); // Adjusted for top scale

        // Right face
        vertices[4].position = positions[1];
        vertices[5].position = positions[2];
        vertices[6].position = positions[6];
        vertices[7].position = positions[5];

        vertices[4].texture = glm::vec2(0.0f, 0.0f);
        vertices[5].texture = glm::vec2(1.0f, 0.0f);
        vertices[6].texture = glm::vec2(0.5f + topScale / 2, 1.0f);
        vertices[7].texture = glm::vec2(0.5f - topScale / 2, 1.0f);

        // Back face
        vertices[8].position = positions[2];
        vertices[9].position = positions[3];
        vertices[10].position = positions[7];
        vertices[11].position = positions[6];

        vertices[8].texture = glm::vec2(0.0f, 0.0f);
        vertices[9].texture = glm::vec2(1.0f, 0.0f);
        vertices[10].texture = glm::vec2(0.5f + topScale / 2, 1.0f);
        vertices[11].texture = glm::vec2(0.5f - topScale / 2, 1.0f);

        // Left face
        vertices[12].position = positions[3];
        vertices[13].position = positions[0];
        vertices[14].position = positions[4];
        vertices[15].position = positions[7];

        vertices[12].texture = glm::vec2(0.0f, 0.0f);
        vertices[13].texture = glm::vec2(1.0f, 0.0f);
        vertices[14].texture = glm::vec2(0.5f + topScale / 2, 1.0f);
        vertices[15].texture = glm::vec2(0.5f - topScale / 2, 1.0f);

        // Top face - scaled UV coordinates to match smaller size
        vertices[16].position = positions[4];
        vertices[17].position = positions[5];
        vertices[18].position = positions[6];
        vertices[19].position = positions[7];

        vertices[16].texture = glm::vec2(0.25f, 0.25f); // Scaled and centered UVs
        vertices[17].texture = glm::vec2(0.75f, 0.25f);
        vertices[18].texture = glm::vec2(0.75f, 0.75f);
        vertices[19].texture = glm::vec2(0.25f, 0.75f);

        // Bottom face - full UV coordinates
        vertices[20].position = positions[0];
        vertices[21].position = positions[1];
        vertices[22].position = positions[2];
        vertices[23].position = positions[3];

        vertices[20].texture = glm::vec2(0.0f, 0.0f);
        vertices[21].texture = glm::vec2(1.0f, 0.0f);
        vertices[22].texture = glm::vec2(1.0f, 1.0f);
        vertices[23].texture = glm::vec2(0.0f, 1.0f);

        // Generate indices (same as before)
        for (int i = 0; i < 6; i++)
        {
            int baseIndex = i * 4;
            indices.push_back(baseIndex);
            indices.push_back(baseIndex + 1);
            indices.push_back(baseIndex + 2);
            indices.push_back(baseIndex);
            indices.push_back(baseIndex + 2);
            indices.push_back(baseIndex + 3);
        }

        VertexArrayObject *va = new VertexArrayObject;
        VertexBuffer *vb = new VertexBuffer;
        IndexBuffer *ib = new IndexBuffer;

        vb->create(vertices, sizeof(Vertex) * vertexCount);
        ib->create(indices.data(), indices.size() * sizeof(unsigned int));
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);

        va->addVertexAttribute(VertexAttributeType::Position);
        va->addVertexAttribute(VertexAttributeType::Texture);
        va->activateAttributes();
        m_vaoMap[ShapeTypes::Frustum] = va;

        va->unbind();
        delete[] vertices;
        return va;
    }
}