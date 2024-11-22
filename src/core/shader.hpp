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

class Shader;

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
public:
    RenderShader(const std::string &vertex_path, const std::string &fragment_path)
    {
        std::string vertex_source = load_shader(vertex_path);
        std::string fragment_source = load_shader(fragment_path);

        GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_source);
        GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_source);
        
        m_program_ID = glCreateProgram();
        glAttachShader(m_program_ID, vertex_shader);
        glAttachShader(m_program_ID, fragment_shader);
        glLinkProgram(m_program_ID);
        
        int success;
        glGetProgramiv(m_program_ID, GL_LINK_STATUS, &success);

        if (!success)
        {
            char log[512];
            glGetProgramInfoLog(m_program_ID, 512, nullptr, log);
            throw std::runtime_error("Program Linking Error: " + std::string(log));
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }
};

class Shader
{
protected:
    GLuint m_program_ID = 0;
public:
    ~Shader()
    {
        if (m_program_ID != 0)
        {
            glDeleteProgram(m_program_ID);
        }
    }

    void bind()
    {
        glUseProgram(m_program_ID);
    }

    void unbind()
    {
        glUseProgram(0);
    }

    void set_uniform_int(const std::string &variable_name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_program_ID, variable_name.c_str()), value);
    }

    void set_uniform_float(const std::string &variable_name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_program_ID, variable_name.c_str()), value);
    }

    void set_vec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(m_program_ID, name.c_str()), 1, glm::value_ptr(value));
    }

    void set_mat4(const std::string &name, const glm::mat4 &value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_program_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }


    GLuint get_ID() const
    { return m_program_ID; }

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