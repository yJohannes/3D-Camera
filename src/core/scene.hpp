#include "renderer.hpp"
#include "camera.hpp"
#include "shader.hpp"

#include "cube.hpp"

class Scene
{
private:
    Renderer m_renderer;
    Camera m_camera;
    RenderShader m_render_shader;

    Cube m_cube;
    

public:
    Scene(float aspect_ratio)
        : m_camera(glm::vec3(0.0f, 0.0f, 3.0f), 45.0f, aspect_ratio, 0.1f, 100.0f)
        , m_render_shader("src/shaders/cube.vert", "src/shaders/cube.frag")
    {
        glEnable(GL_DEPTH_TEST);

        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        std::vector<float> vertices = {
            -0.5f, -0.5f, -0.5f, // Bottom-left-back
             0.5f, -0.5f, -0.5f, // Bottom-right-back
             0.5f,  0.5f, -0.5f, // Top-right-back
            -0.5f,  0.5f, -0.5f, // Top-left-back
            -0.5f, -0.5f,  0.5f, // Bottom-left-front
             0.5f, -0.5f,  0.5f, // Bottom-right-front
             0.5f,  0.5f,  0.5f, // Top-right-front
            -0.5f,  0.5f,  0.5f  // Top-left-front
        };

        std::vector<unsigned int> indices = {
            0, 1, 2, 2, 3, 0,   // Front face
            4, 5, 6, 6, 7, 4,   // Back face
            4, 5, 1, 1, 0, 4,   // Bottom face
            7, 6, 2, 2, 3, 7,   // Top face
            4, 0, 3, 3, 7, 4,   // Left face
            1, 5, 6, 6, 2, 1    // Right face
        };

        m_cube = Cube(position, vertices, indices);
        m_cube.init();
    }

    Camera* camera()
    {
        return &m_camera;
    }

    void render(float time)
    {
        static GLfloat m_ground_vertices[] = {
            -50.0f, 0.0f, -50.0f,  // bottom-left corner
            50.0f, 0.0f, -50.0f,  // bottom-right corner
            50.0f, 0.0f,  50.0f,  // top-right corner
            -50.0f, 0.0f,  50.0f   // top-left corner
        };

static GLfloat axis_vertices[] = {
    // X axis (Red)
    0.0f, 0.0f, 0.0f,  10.0f, 0.0f, 0.0f,

    // Y axis (Green)
    0.0f, 0.0f, 0.0f,  0.0f, 10.0f, 0.0f,

    // Z axis (Blue)
    0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 10.0f   // Fixed Z-axis line
};

        m_render_shader.bind();

        glm::mat4 mvp = m_camera.get_mvp(glm::mat4(1.0f));
        m_render_shader.set_mat4("u_mvp", mvp);
        m_render_shader.set_vec4("u_frag_color", glm::vec4(1.0f, 1.0f, 1.0f, 0.4f));


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Standard alpha blending

        // Disable depth writes for the transparent ground
        // glDepthMask(GL_FALSE);
        // glDepthMask(GL_TRUE);

        // glBegin(GL_QUADS);
        // for (int i = 0; i < 12; i += 3) {
        //     glVertex3f(m_ground_vertices[i], m_ground_vertices[i+1], m_ground_vertices[i+2]);
        // }
        // glEnd();


        m_render_shader.set_vec4("u_frag_color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
glBegin(GL_LINES);
for (int i = 0; i < 18; i += 6) {
    glVertex3f(axis_vertices[i], axis_vertices[i + 1], axis_vertices[i + 2]);
    glVertex3f(axis_vertices[i + 3], axis_vertices[i + 4], axis_vertices[i + 5]);
}
glEnd();


        glm::mat4 model = glm::rotate(glm::mat4(1.0f), time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        mvp = m_camera.get_mvp(model);
        m_render_shader.set_mat4("u_mvp", mvp);
        // m_render_shader.set_vec3("u_camera_position", m_camera.get_position());
        m_render_shader.set_vec4("u_frag_color", glm::vec4(0.0f, 0.0f, 0.93f, 1.0f));


        m_cube.bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        m_cube.unbind();

        m_render_shader.unbind();
    }
};