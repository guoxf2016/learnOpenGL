#include <iostream>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include <SOIL.h>
#include <zconf.h>
#include <cstring>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);//查看顶点属性上限
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    /*GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };*/

    /*GLfloat vertices[] = {
            0.5f, 0.5f, 0.0f,   // 右上角
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, -0.5f, 0.0f, // 左下角
            -0.5f, 0.5f, 0.0f   // 左上角
    };*/

    /*GLfloat vertices[] = {
            // 位置              // 颜色
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };*/

    GLfloat vertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };


    GLuint indices[] = { // 注意索引从0开始!
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
    };

    /*GLfloat texCoords[] = {
            0.0f, 0.0f, // 左下角
            1.0f, 0.0f, // 右下角
            0.5f, 1.0f // 上中
    };*/


    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);//创建VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//复制顶点数据到VBO

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLchar const *vertexShaderSource = "#version 330 core\n"
                                       "layout (location = 0) in vec3 aPos;\n"
                                       "layout (location = 1) in vec3 aColor;\n"
                                       "layout (location = 2) in vec2 aTexCoord;\n"
                                       "\n"
                                       "out vec3 ourColor;\n"
                                       "out vec2 TexCoord;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    gl_Position = vec4(aPos, 1.0);\n"
                                       "    ourColor = aColor;\n"
                                       "    TexCoord = aTexCoord;"
                                       "}";

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLchar const *fragmentShaderSource = "#version 330 core\n"
                                         "out vec4 FragColor;\n"
                                         "\n"
                                         "in vec3 ourColor;\n"
                                         "in vec2 TexCoord;\n"
                                         "uniform sampler2D texture1;\n"
                                         "uniform sampler2D texture2;\n"
                                         "void main()\n"
                                         "{\n"
                                         "    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);\n"
                                         "    //0.2会返回80%的第一个输入颜色和20%的第二个输入颜色，即返回两个纹理的混合色。\n"
                                         "} ";

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    GLuint texture, texture2;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //加载纹理图片
    int texWidth, texHeight, nrChannels;

    //这里的文件路径是个坑，使用./container.jpg无法打开文件
    unsigned char* data = SOIL_load_image("/home/guoxiaofei/CLionProjects/learnOpenGL/Texture/container.jpg",
            &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//生成纹理
        glGenerateMipmap(GL_TEXTURE_2D);//为当前绑定的纹理自动生成所有需要的多级渐远纹理
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    SOIL_free_image_data(data);//释放纹理图片

    glGenTextures(2, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int texWidth1, texHeight1, nrChannels1;

    unsigned char* data1 = SOIL_load_image("/home/guoxiaofei/CLionProjects/learnOpenGL/Texture/awesomeface.png",
                                          &texWidth1, &texHeight1, 0, SOIL_LOAD_RGB);
    if (data1) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth1, texHeight1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);//生成纹理
        glGenerateMipmap(GL_TEXTURE_2D);//为当前绑定的纹理自动生成所有需要的多级渐远纹理
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    SOIL_free_image_data(data1);//释放纹理图片
    glBindTexture(GL_TEXTURE_2D, 0);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//填充

    //Render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");*/
        glUseProgram(shaderProgram);
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元，GL_TEXTURE0是默认激活的
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);//解绑VAO

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

