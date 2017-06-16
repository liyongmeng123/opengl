//
//  main.cpp
//  三角形
//
//  Created by 李勇猛 on 2017/6/8.
//  Copyright © 2017年 李勇猛. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

//定点着色器
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
//片段着色器
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";






GLfloat vertices[] ={
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f,  // 左上角
     -0.2f, 0.8f, 0.0f   // 左上角
};

GLuint indices[] = { // 注意索引从0开始!
    0, 1, 3,4, // 第一个三角形
    1, 2, 3,4  // 第二个三角形
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //创建窗口
    
    GLFWwindow * window = glfwCreateWindow(800, 800, "sanjiaoxing", nullptr, nullptr);
    
    if (window ==nullptr) {
        glfwTerminate();
        std::cout<<"窗口都出不来"<<std::endl;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    if (glewInit()!=GLEW_OK) {
        
        std::cout<<"glew都创建不出来了吗"<<std::endl;
        return -1;
    }
    
    //显示数据
    int width,height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    GLuint VBD,VAO,EBO;
    glGenBuffers(1,&VBD);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBD);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    //顶点着色器
    GLuint vertexshaderp;
    vertexshaderp = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshaderp, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexshaderp);
    
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexshaderp,GL_COMPILE_STATUS,&success);
    if (!success) {
        
        glGetShaderInfoLog(vertexshaderp,512,nullptr,infoLog);
        
        cout<<"顶点着色器出来"<<endl;
        
    }
    
    GLuint fragmentshader;
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentshader);
    
    glGetShaderiv(fragmentshader,GL_COMPILE_STATUS,&success);
    if (!success) {
        
        glGetShaderInfoLog(fragmentshader,512,nullptr,infoLog);
        
        cout<<"片段着色器出来"<<endl;
        
    }
    
    GLuint shaderprogram;
    shaderprogram = glCreateProgram();
    glAttachShader(shaderprogram,vertexshaderp);
    glAttachShader(shaderprogram,fragmentshader);
    glLinkProgram(shaderprogram);
    glGetShaderiv(shaderprogram,GL_COMPILE_STATUS,&success);
    if (!success) {
        
        glGetShaderInfoLog(shaderprogram,512,nullptr,infoLog);
        
        cout<<"着色器连接器出来"<<endl;
        
    }
    
    glDeleteShader(vertexshaderp);
    glDeleteShader(fragmentshader);
    

    
    //循环
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        //双缓冲
        glfwSwapBuffers(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderprogram);
        glBindVertexArray(VAO);
       // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    
    glfwTerminate();
    
    return 0;
}
