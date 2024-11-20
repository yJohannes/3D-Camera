#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <SFML/OpenGL.hpp>

class Shader
{
// add bind, unding etc

public:
    // Helper function to load GLSL shader files
    static std::string load_shader(const std::string& filename) {
        std::ifstream file(filename);
        std::stringstream buffer;
        if (!file.is_open()) {
            std::cerr << "Failed to open shader file: " << filename << std::endl;
            return "";
        }
        buffer << file.rdbuf();
        return buffer.str();
    }

    static GLuint compile_shader(GLenum type, const std::string& source) {
        GLuint shader = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);
        
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char log[512];
            glGetShaderInfoLog(shader, 512, nullptr, log);
            std::cerr << "Shader compilation error: " << log << std::endl;
        }
        return shader;
    }

    // Create compute shader from file
    static GLuint create_compute_shader(const std::string &path) {
        std::string computeSource = load_shader(path);
        GLuint computeShader = compile_shader(GL_COMPUTE_SHADER, computeSource);
        GLuint program = glCreateProgram();
        glAttachShader(program, computeShader);
        glLinkProgram(program);
        glDeleteShader(computeShader);
        return program;
    }

    // Create render shader from vertex and fragment shader files
    static GLuint create_render_shader(const std::string &vert_path, const std::string &frag_path) {
        std::string vertexSource = load_shader(vert_path);
        std::string fragmentSource = load_shader(frag_path);

        GLuint vertexShader = compile_shader(GL_VERTEX_SHADER, vertexSource);
        GLuint fragmentShader = compile_shader(GL_FRAGMENT_SHADER, fragmentSource);
        
        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
        return program;
    }
};