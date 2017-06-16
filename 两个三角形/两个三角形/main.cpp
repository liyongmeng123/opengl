//
//  main.cpp
//  两个三角形
//
//  Created by 李勇猛 on 2017/6/16.
//  Copyright © 2017年 李勇猛. All rights reserved.
//

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

//片段着色器
const GLchar* towShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
"}\n\0";







GLfloat vertices[] ={
    // First triangle
    -0.9f, -0.5f, 0.0f,  // Left
    -0.0f, -0.5f, 0.0f,  // Right
    -0.45f, 0.5f, 0.0f,  // Top
  
   
};

GLfloat vertices1[] ={
    // Second triangle
    0.0f, -0.5f, 0.0f,  // Left
    0.9f, -0.5f, 0.0f,  // Right
    0.45f, 0.5f, 0.0f   // To
   
    
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
    
    GLuint VBD[2],VAO[2];
    glGenBuffers(2,VBD);
    glGenVertexArrays(2, VAO);
    
    
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER,VBD[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
        //
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBD[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices1),vertices1,GL_STATIC_DRAW);
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
    //片段着色器
    GLuint fragmentshader;
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentshader);
    
    glGetShaderiv(fragmentshader,GL_COMPILE_STATUS,&success);
    if (!success) {
        
        glGetShaderInfoLog(fragmentshader,512,nullptr,infoLog);
        
        cout<<"片段着色器出来"<<endl;
        
    }
    
    //第二个片段着色器
    GLuint towshader;
    towshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(towshader,1,&towShaderSource,NULL);
    glCompileShader(towshader);
    
    glGetShaderiv(towshader,GL_COMPILE_STATUS,&success);
    if (!success) {
        
        glGetShaderInfoLog(fragmentshader,512,nullptr,infoLog);
        
        cout<<"第二个片段着色器出来"<<endl;
        
    }

    
    
    //链接顶点和片段
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
    
    //链接第二个顶点和片段(因为顶点没有改变 所以顶点时同一个)
    GLuint shadertowprogram;
    shadertowprogram = glCreateProgram();
    glAttachShader(shadertowprogram,vertexshaderp);
    glAttachShader(shadertowprogram,towshader);
    glLinkProgram(shadertowprogram);
    glGetShaderiv(shadertowprogram,GL_COMPILE_STATUS,&success);
    if (!success) {
        
        glGetShaderInfoLog(shadertowprogram,512,nullptr,infoLog);
        
        cout<<"着色器连接器出来"<<endl;
        
    }
    
    
    //链接完成以后就可以吧着色器都释放了 节省内存
    glDeleteShader(vertexshaderp);
    glDeleteShader(fragmentshader);
    glDeleteShader(towshader);
    
    
    
    //循环
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        //双缓冲
        glfwSwapBuffers(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderprogram);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    
        
        glUseProgram(shadertowprogram);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glBindVertexArray(0);
    }
    
    glfwTerminate();
    
    return 0;
}
