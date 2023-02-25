#include <iostream>
#include<thread>
#include<chrono>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/vec2.hpp>
#include<glm/gtx/matrix_transform_2d.hpp>
#include<shaderprogram.hpp>
#include<vector>
#include"physics.hpp"

std::vector<glm::vec3> vertices;
std::vector<unsigned int> indices;

unsigned int VAO;

unsigned int VBO;

unsigned int EBO;

Universe universe;

Object obj = Object(&universe, glm::vec3(-0.5f,0.5f,0.0f), 10);
Object obj1 = Object(&universe, glm::vec3(0.0f,0.0f,0.0f), 10);

void createCircle(float radius, int vertexCount)
{
    float angle = 360.0f / vertexCount;

    int triangleCount = vertexCount - 2;

    std::vector<glm::vec3> tempVertices;

    for (int i = 0; i < vertexCount; i++)
    {
        glm::vec3 nextPos;
        float nextAngle = angle * i;
        nextPos.x = radius * glm::cos(glm::radians(nextAngle));
        nextPos.y = radius * glm::sin(glm::radians(nextAngle));
        nextPos.z = 0.0f;
        vertices.push_back(nextPos);

    }

    for (int i = 0; i < triangleCount; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }
}

void DrawObject(Object obj, ShaderProgram& program)
{
    program.setVec3("uPos",obj.getPosition());
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

int main()
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(800, 800, "Physics", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Pencere Olusturulamadi" << std::endl;

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    ShaderProgram program;

    program.attachShader("simplevs.glsl", GL_VERTEX_SHADER);
    program.attachShader("simplefs.glsl", GL_FRAGMENT_SHADER);

    program.link();
    program.addUniform("uPos");

    createCircle(.01, 36);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

    

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        program.use();
        universe.start();
        std::cout << obj.getPosition().y<<std::endl;
        DrawObject(obj, program);
        DrawObject(obj1, program);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}