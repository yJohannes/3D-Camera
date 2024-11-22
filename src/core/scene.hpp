#include "renderer.hpp"
#include "camera.hpp"
#include "shader.hpp"

#include "cube.hpp"

class Scene
{
public:
    Renderer m_renderer;
    Camera m_camera;
    RenderShader m_render_shader;

    Cube m_cube;

    Scene()
        : m_camera(glm::vec3(0.0f), 45.0f, 800.0f / 600.0f, 0.1f, 100.0f)
        , m_cube()
        , m_render_shader("src/shaders/cube.vert", "src/shaders/cube.frag")
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

        glGenVertexArrays()
    }

    void render()
    {

        m_render_shader.bind();
        m_render_shader.set_mat4("u_mvp", m_camera.get_mvp(glm::mat4(1.0f)));

        glBindVertexArray(quad_VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Draws the full-screen quad as two triangles
        // Unbind VAO and render shader
        glBindVertexArray(0);
        glUseProgram(0);

    }
};