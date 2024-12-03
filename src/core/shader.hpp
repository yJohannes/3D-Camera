#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <glad/glad.h>
#include <SFML/OpenGL.hpp>

class Shader
{
protected:
    GLuint m_program_ID = 0;
public:
    virtual ~Shader()
    {
        if (m_program_ID != 0)
        {
            glDeleteProgram(m_program_ID);
        }
    }

    void bind() const
    {
        glUseProgram(m_program_ID);
    }

    void unbind() const
    {
        glUseProgram(0);
    }

    GLuint get_ID() const
    { return m_program_ID; }

    void set_uniform_int(const std::string &variable_name, int value) const
    {
        GLint location = glGetUniformLocation(m_program_ID, variable_name.c_str());
        valid_location(location, variable_name);
        glUniform1i(location, value);
    }

    void set_uniform_float(const std::string &variable_name, float value) const
    {
        GLint location = glGetUniformLocation(m_program_ID, variable_name.c_str());
        valid_location(location, variable_name);
        glUniform1f(location, value);
    }

    void set_vec3(const std::string &variable_name, const glm::vec3 &vector) const
    {
        GLint location = glGetUniformLocation(m_program_ID, variable_name.c_str());
        valid_location(location, variable_name);
        glUniform3fv(location, 1, glm::value_ptr(vector));
    }

    void set_vec4(const std::string &variable_name, const glm::vec4 &vector) const
    {
        GLint location = glGetUniformLocation(m_program_ID, variable_name.c_str());
        valid_location(location, variable_name);
        glUniform4fv(location, 1, glm::value_ptr(vector));
    }

    void set_mat4(const std::string &variable_name, const glm::mat4 &matrix) const
    {
        GLint location = glGetUniformLocation(m_program_ID, variable_name.c_str());
        valid_location(location, variable_name);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
private:
    void valid_location(GLint location, const std::string& variable_name) const
    {
        if (location == -1) std::cerr << "Warning: Uniform '" << variable_name << "' not found or not used." << std::endl;
    }

protected:
    // Helper function to load GLSL shader files
    static std::string load_shader(const std::string& filename)
    {
        std::ifstream file(filename);
        std::stringstream buffer;

        if (!file.is_open())
        {
            std::cerr << "Failed to open shader file: " << filename << std::endl;
            return "";
        }
        buffer << file.rdbuf();
        return buffer.str();
    }

    static GLuint compile_shader(GLenum shader_type, const std::string& source)
    {
        GLuint shader = glCreateShader(shader_type);
        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);
        
        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            char log[512];
            glGetShaderInfoLog(shader, 512, nullptr, log);
            std::cerr << "Shader compilation error: " << log << std::endl;
        }
        return shader;
    }
};

class ComputeShader : public Shader
{
public:
    ComputeShader(GLenum shader_type, const std::string &shader_path)
    {
        std::string shader_source = load_shader(shader_path);
        GLuint shader = compile_shader(shader_type, shader_source);

        m_program_ID = glCreateProgram();
        glAttachShader(m_program_ID, shader);
        glLinkProgram(m_program_ID);
        glDeleteShader(shader);
    }
};

class RenderShader : public Shader
{
private:
    GLuint m_vertex_ID = 0;
    GLuint m_fragment_ID = 0;
public:
    RenderShader(const std::string &vertex_path, const std::string &fragment_path)
    {
        std::string vertex_source = load_shader(vertex_path);
        std::string fragment_source = load_shader(fragment_path);

        m_vertex_ID = compile_shader(GL_VERTEX_SHADER, vertex_source);
        m_fragment_ID = compile_shader(GL_FRAGMENT_SHADER, fragment_source);
        
        m_program_ID = glCreateProgram();
        glAttachShader(m_program_ID, m_vertex_ID);
        glAttachShader(m_program_ID, m_fragment_ID);
        glLinkProgram(m_program_ID);
        
        int success;
        glGetProgramiv(m_program_ID, GL_LINK_STATUS, &success);

        if (!success)
        {
            char log[512];
            glGetProgramInfoLog(m_program_ID, 512, nullptr, log);
            throw std::runtime_error("Program Linking Error: " + std::string(log));
        }
    }

    ~RenderShader()
    {
        glDeleteShader(m_vertex_ID);
        glDeleteShader(m_fragment_ID);
    }
};

