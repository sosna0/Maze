#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "maze/GraphAsMatrix.h"
#include "maze/graph_gen.h"
#include "maze/KruskalAlghoritm.h"


void lines(std::vector<std::pair<GLfloat, GLfloat>> const& vert) {
    glLineWidth(2.0f);
    for (int i = 0; i < vert.size(); i+=2) {
        glBegin(GL_LINES);
        glVertex2f(vert[i].first, vert[i].second);
        glVertex2f(vert[i+1].first, vert[i+1].second);
        glEnd();
    }
}

int main(){

    int rows = 0, cols = 0;

    std::cout << "Enter number of rows: ";
    std::cin >> rows;

    std::cout << "Enter number of cols: ";
    std::cin >> cols;
    std::cout << std::endl;

    auto graph = generateGraph(rows, cols);
    //std::cout << "Number of Edges: " << graph.NumberOfEdges() << std::endl;
    auto vert = kruskal_maze(graph, rows, cols);


    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1200, 900, "Maze", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //points(vert);
        lines(vert);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}