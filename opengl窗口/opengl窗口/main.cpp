//
//  main.cpp
//  opengl窗口
//
//  Created by 李勇猛 on 2017/6/7.
//  Copyright © 2017年 李勇猛. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
int main(int argc, const char * argv[]) {
    
    //创建glfw
    glfwInit();
    //告诉编译器我们用的3的版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //不允许用户调整窗口大小
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    //如果是苹果需要加这句话
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //创建窗口
    GLFWwindow * window =glfwCreateWindow(800, 600, "chuangkou", nullptr, nullptr);
    if (window ==nullptr) {
        glfwTerminate();
        std::cout<<"窗口都没出来 你玩个屁"<<std::endl;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    
    //创建glew
    glewExperimental = GL_TRUE;
    if (glewInit()!=GLEW_OK) {
        std::cout<<"glew都创建不出来了吗"<<std::endl;
        return -1;
    }
    //显示数据
    int width ,height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    //循环
    while(!glfwWindowShouldClose(window))
    {
//       检查有没有什么输入键盘鼠标什么的
        glfwPollEvents();
//        双缓冲
        glfwSwapBuffers(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    //释放glfw
    glfwTerminate();
    
    
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
    // 关闭应用程序
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
