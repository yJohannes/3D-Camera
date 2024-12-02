


#define ___DB

#ifdef ___DB
#include "application/window.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main()
{
    sf::ContextSettings context;
    context.depthBits = 24;
    context.stencilBits = 8;
    context.antialiasingLevel = 4;

    MainWindow window(1200, 800, "3D Camera", context, sf::Style::Default);
    window.run();
    return 0;
}

#else

#include <glad/glad.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Vertex Shader
const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexColor = aColor;
}
)";

// Fragment Shader
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor;

out vec4 fragColor;

void main() {
    fragColor = vec4(vertexColor, 1.0);
}
)";

// Cube vertices and colors
float vertices[] = {
    // Positions         // Colors
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // Bottom-left-back
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // Bottom-right-back
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // Top-right-back
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, // Top-left-back
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // Bottom-left-front
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // Bottom-right-front
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // Top-right-front
    -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f  // Top-left-front
};

// Cube indices
unsigned int indices[] = {
    0, 1, 2, 2, 3, 0, // Back face
    4, 5, 6, 6, 7, 4, // Front face
    0, 4, 7, 7, 3, 0, // Left face
    1, 5, 6, 6, 2, 1, // Right face
    0, 1, 5, 5, 4, 0, // Bottom face
    3, 2, 6, 6, 7, 3  // Top face
};

void processInput(sf::Window& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }
}

int main() {
    // Create SFML window
    sf::Window window(sf::VideoMode(800, 600), "3D Cube", sf::Style::Default, sf::ContextSettings(24, 8, 4));
    window.setVerticalSyncEnabled(true);

    if (!gladLoadGL())
    {
        std::cerr << "Failed to initialize GLAD\n";
    } 

    glEnable(GL_DEPTH_TEST);

    // Compile shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Create shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Setup VAO, VBO, and EBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Projection and view matrices
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

    // Time variables for rotation
    sf::Clock clock;

    // Main loop
    while (window.isOpen()) {
        // Poll events and process input
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        processInput(window);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Get elapsed time and create a rotation matrix
        float time = clock.getElapsedTime().asSeconds();
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        // glm::mat4 model = glm::mat4(1.0f);

        // Send the matrices to the shader
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the cube
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glUseProgram(0);

        // Swap buffers and display the result
        window.display();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    return 0;
}

#endif