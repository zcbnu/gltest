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
#include "Voronoi.hpp"

using namespace glm;
mat4x4 projection;

using namespace std;

static GLfloat GL_PI = 3.14159f;




//绘制场景


static
void RenderSences(GLFWwindow * window)

{
    
    GLfloat z = -50.0f;
    
    
    //清空画布
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    //设置画图使用的颜色
    
    glColor3f(1.0f, 0.0f, 0.0f);
    
    
    //保存矩阵
    
    glPushMatrix();
    
    
    //旋转, 如果不旋转，那些不同层次的点都重叠在一起，看不出3D效果了。
    static bool notFirst = false;
    if (notFirst)
        glRotatef(200.0f, 1.0f, 0.0f, 0.0f);
    notFirst = true;
    glRotatef(120.5f, 0.0f, 1.0f, 0.0f);
    
    
    //获取点的大小的范围，以及增长的步长
    
    GLfloat size[2];
    
    GLfloat sizeStep;
    
    glGetFloatv(GL_POINT_SIZE_RANGE, size);
    
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &sizeStep);
    
    GLfloat curStep = size[0];
    
    
    for (GLfloat a = 0.0; a < GL_PI * 3.0f; a += 0.1f)
        
    {
        
        GLfloat x = 50.0f * cos(a);
        
        GLfloat y = 50.0f * sin(a);
        
        
        //设置点的大小
        
        glPointSize(curStep);
        
        curStep += sizeStep;
        
        
        //设置顶点
        
        glBegin(GL_POINTS);
        
        glVertex3f(x, y, z);
        
        glEnd();
        
        
        //调整z值
        
        z += 0.5f;
        
    }
    
    glPopMatrix();
    
//    glFlush();
    
}




void ChangeSize(GLFWwindow* window, GLsizei w, GLsizei h)

{
    
    GLfloat nRange = 100.0f;
    
    
    if (h == 0)
        
    {
        
        h = 1;
        
    }
    
    
    //设置视口
    
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    
    
    
    //设置可视区域
    
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    
    
    if (w <= h)
        
    {
        
        glOrtho(-nRange, nRange, -nRange/aspect, nRange/aspect, -nRange, nRange);
        
    }
    
    
    else
        
    {
        
        glOrtho(-nRange*aspect, nRange*aspect, -nRange, nRange, -nRange, nRange);
        
    }
    
    
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
}


//初始化工作


void SetupRC()

{
    
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glShadeModel(GL_FLAT);
}

void key_callback(GLFWwindow* window,int key,int scancode,int action,int modsBit)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, const char * argv[]) {
//    Point<int> pint(0,1);
//    Point<float> pfloat(0.f,1);
//    Leaf<float> l1(Point<float>(1.0f,2.0f));
//    Leaf<float> rl1 = l1;
//    Point<float> p;
//    Leaf<float> l;
//    make_leaf(std::move(p));
//    make_leaf(p);
//    Leaf<float> l2(l);
//    cout << l2.point.x ;
//    cout << l1.point.x << l1.point.y << endl;
//    std::cout << std::is_base_of<BTreeNode, Leaf<int> >::value <<std::endl;
//    std::cout << sizeof(__is_base_of_imp::__test<decltype(l1), Leaf<int> >(0)) << std::endl;
//    std::cout << sizeof(__is_base_of_imp::_Dst<float>(std::declval<__is_base_of_imp::_Src<Leaf<int>> >())) << std::endl;
//    __is_base_of_imp::_Dst<float> a ((__is_base_of_imp::_Src<int> ()));

//    return true;
    // insert code here...
//    std::cout << "Hello, World!\n" << std::endl;
    
    const char* name = " hello" " gltest";
    
    std::cout << glfwGetVersionString();
    
    GLFWwindow * window = nullptr;
    
    if (!glfwInit())
        exit(0);
    
    window = glfwCreateWindow(800, 600, name, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, ChangeSize);
    
    int width,height;
    glfwGetFramebufferSize(window, &width, &height);
    ChangeSize(window, width, height);
    
    SetupRC();

    
    for (;;)
    {
        if (glfwWindowShouldClose(window))
        {
            break;
        }
        
        RenderSences(window);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    exit(1);
    
    return 0;
}
