//
//  main.cpp
//  gltest
//
//  Created by 黄保应 on 15/12/7.
//  Copyright (c) 2015年 黄保应. All rights reserved.
//
#if defined(_MSC_VER)
// Make MS math.h define M_PI
#define _USE_MATH_DEFINES
#endif

#include <iostream>
#include <GLFW/glfw3.h>
#include <math.h>
#include <glm/glm.hpp>
#include <FreeImage.h>
//#include <linmath.h>

using namespace glm;
mat4x4 projection;



void key_callback(GLFWwindow* window,int key,int scancode,int action,int modsBit)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n" << std::endl;
    
    const char* name = " hello" " gltest";
    
    std::cout << glfwGetVersionString();
    
    GLFWwindow * window = nullptr;
    
    if (!glfwInit())
        exit(0);
    
    window = glfwCreateWindow(800, 600, name, nullptr, nullptr);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    
    for (;;)
    {
        if (glfwWindowShouldClose(window))
        {
            break;
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    exit(1);
    
    return 0;
}
