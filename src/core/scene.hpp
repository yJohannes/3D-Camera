#include "renderer.hpp"
#include "camera.hpp"
#include "cube.hpp"

class Scene
{
public:
    Cube m_cube;

    Scene()
        : m_cube()
    {
        m_cube.position = glm::vec3(0.0f);
        m_cube.vertices = {
            -1.0f, -1.0f, -1.0f,   // 0: Front-bottom-left
            1.0f, -1.0f, -1.0f,   // 1: Front-bottom-right
            1.0f,  1.0f, -1.0f,   // 2: Back-bottom-right
            -1.0f,  1.0f, -1.0f,   // 3: Back-bottom-left
            -1.0f, -1.0f,  1.0f,   // 4: Front-top-left
            1.0f, -1.0f,  1.0f,   // 5: Front-top-right
            1.0f,  1.0f,  1.0f,   // 6: Back-top-right
            -1.0f,  1.0f,  1.0f    // 7: Back-top-left
        };
    }
};