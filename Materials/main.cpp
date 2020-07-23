#include <iostream>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "SOIL/SOIL.h"
#include <zconf.h>
#include <cstring>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.h"

using namespace glm;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void processInput(GLFWwindow *window);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

float lastX = 400, lastY = 300;//存储鼠标位置

double yaw1;
double pitch1;

bool firstMouse = true;

float fov = 45.0f;

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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //在调用这个函数之后，无论我们怎么去移动鼠标，光标都不会显示了，它也不会离开窗口。对于FPS摄像机系统来说非常完美。


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

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

    /* GLfloat vertices[] = {
 //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
             0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // 右上
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // 右下
             -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // 左下
             -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // 左上
     };*/

    //立方体
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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

    mat4 trans = mat4(1.0f);
    trans = translate(trans, vec3(0.5f, -0.5f, 0.0f));
    mat4 model = mat4(1.0f);
    model = rotate(model, radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));
    mat4 view = mat4(1.0f);
    view = translate(view, vec3(0.0f, 0.0f, -3.0f));
    mat4 projection = mat4(1.0f);
    projection = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    /*trans = rotate(trans, radians(90.0f), vec3(0.0f, 0.0f, 1.0f));
    trans = scale(trans, vec3(0.5f, 0.5f, 0.5f));*/


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
                                       "uniform mat4 transform;\n"
                                       "uniform mat4 model;\n"
                                       "uniform mat4 view;\n"
                                       "uniform mat4 projection;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
                                       "    ourColor = aColor;\n"
                                       "    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);\n"
                                       "}";


    GLchar  const *vertexShaderSimpleCube = "#version 330 core\n"
                                            "layout (location = 0) in vec3 aPos;\n"
                                            "layout (location = 1) in vec3 aNormal;\n"
                                            "uniform mat4 model;\n"
                                            "uniform mat4 view;\n"
                                            "uniform mat4 projection;\n"
                                            "out vec3 Normal;\n"
                                            "out vec3 FragPos;\n"
                                            "void main()\n"
                                            "{\n"
                                            "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
                                            "    FragPos = vec3(model * vec4(aPos, 1.0));\n"
                                            "    Normal = mat3(transpose(inverse(model))) * aNormal;;\n"
                                            "}";



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

    GLchar const * fragmentShaderSource2 = "#version 330 core\n"
                                           "struct Material {\n"
                                           "    vec3 ambient;\n"
                                           "    vec3 diffuse;\n"
                                           "    vec3 specular;\n"
                                           "    float shininess;\n"
                                           "}; \n"
                                           "\n"
                                           "uniform Material material;\n"
                                           "struct Light {\n"
                                           "    vec3 position;\n"
                                           "\n"
                                           "    vec3 ambient;\n"
                                           "    vec3 diffuse;\n"
                                           "    vec3 specular;\n"
                                           "};\n"
                                           "\n"
                                           "uniform Light light;\n"
                                           "out vec4 FragColor;\n"
                                           "\n"
                                           "uniform vec3 lightPos;\n"
                                           "in vec3 Normal;\n"
                                           "in vec3 FragPos;\n"
                                           "uniform vec3 viewPos;\n"
                                           "void main()\n"
                                           "{\n"
                                           "    vec3 ambient =  material.ambient * light.ambient;\n"
                                           "\n"
                                           "    vec3 norm = normalize(Normal);\n"
                                           "    vec3 lightDir = normalize(lightPos - FragPos);\n"
                                           "    float diff = max(dot(norm, lightDir), 0.0);\n"
                                           "    vec3 diffuse = material.diffuse * diff * light.diffuse;\n"
                                           "    vec3 viewDir = normalize(viewPos - FragPos);\n"
                                           "    vec3 reflectDir = reflect(-lightDir, norm);\n"
                                           "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
                                           "    vec3 specular = material.specular * spec * light.specular;\n"
                                           "    vec3 result = ambient + diffuse + specular;\n"
                                           "    FragColor = vec4(result, 1.0);\n"
                                           "}";

    GLchar const *fragmentShaderSourceLight = "#version 330 core\n"
                                              "out vec4 FragColor;\n"
                                              "\n"
                                              "void main()\n"
                                              "{\n"
                                              "    FragColor = vec4(1.0); // 将向量的四个分量全部设置为1.0\n"
                                              "}";


    Shader cubeShader = Shader(vertexShaderSimpleCube, fragmentShaderSource2, false);
    Shader lightShader = Shader(vertexShaderSimpleCube, fragmentShaderSourceLight, false);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);


    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
//    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    /*GLuint texture, texture2;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //加载纹理图片
    int texWidth, texHeight, nrChannels;

    //这里的文件路径是个坑，使用./container.jpg无法打开文件
    unsigned char *data = SOIL_load_image("../container.jpg",
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

    unsigned char *data1 = SOIL_load_image("../awesomeface.png",
                                           &texWidth1, &texHeight1, 0, SOIL_LOAD_RGB);
    if (data1) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth1, texHeight1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);//生成纹理
        glGenerateMipmap(GL_TEXTURE_2D);//为当前绑定的纹理自动生成所有需要的多级渐远纹理
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    SOIL_free_image_data(data1);//释放纹理图片
    glBindTexture(GL_TEXTURE_2D, 0);*/

//    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
//    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

    cubeShader.use();
    cubeShader.setVec3("material.ambient",  vec3(1.0f, 0.5f, 0.31f));
    cubeShader.setVec3("material.diffuse",  vec3(1.0f, 0.5f, 0.31f));
    cubeShader.setVec3("material.specular", vec3(0.5f, 0.5f, 0.5f));
    cubeShader.setFloat("material.shininess", 32.0f);
    cubeShader.setVec3("light.ambient",  vec3(0.2f, 0.2f, 0.2f));
    cubeShader.setVec3("light.diffuse",  vec3(0.5f, 0.5f, 0.5f)); // 将光照调暗了一些以搭配场景
    cubeShader.setVec3("light.specular", vec3(1.0f, 1.0f, 1.0f));
    cubeShader.setVec3("lightPos", vec3(1.2f, 1.0f, 2.0f));

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//填充

    glEnable(GL_DEPTH_TEST);//开启深度测试

    //10个立方体
    vec3 cubePositions[] = {
            vec3(0.0f, 0.0f, 0.0f),
            vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    //Render loop
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除深度缓冲


        /* trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
         GLint transformLoc = glGetUniformLocation(shaderProgram, "transform");
         glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(trans));*/
        /*model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));*/
        float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;

        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);

        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // 降低影响
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

        cubeShader.use();
        cubeShader.setVec3("light.ambient", ambientColor);
        cubeShader.setVec3("light.diffuse", diffuseColor);

        glm::mat4 view1 = mat4(1.0f);
        view1 = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        cubeShader.setMat4("view", view1);

        projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

        cubeShader.setMat4("projection", projection);


        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        /*glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元，GL_TEXTURE0是默认激活的
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);*/

        glm::mat4 model1 = mat4(1.0f);
//        model1 = glm::translate(model1,  glm::vec3 (1.0f, 1.2f, 2.0f));
        cubeShader.setMat4("model", model1);

        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glDrawArrays(GL_TRIANGLES, 0, 36);


        lightShader.use();

        lightShader.setMat4("view", view1);

        lightShader.setMat4("projection", projection);

        glm::mat4 model2 = mat4(1.0f);
        model2 = glm::translate(model2, lightPos);
        model2 = glm::scale(model2, glm::vec3(0.2f));

        lightShader.setMat4("model", model2);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        /*for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model1 = mat4(1.0f);
            model1 = glm::translate(model1, cubePositions[i]);
            float angle = 20.0f * i;
            model1 = glm::rotate(model1, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model1));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }*/
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

    float cameraSpeed = 1.0f * deltaTime; // adjust accordingly
    /**
     * 目前我们的移动速度是个常量。理论上没什么问题，但是实际情况下根据处理器的能力不同，有些人可能会比其他人每秒绘制更多帧，
     * 也就是以更高的频率调用processInput函数。结果就是，根据配置的不同，有些人可能移动很快，而有些人会移动很慢。
     * 当你发布你的程序的时候，你必须确保它在所有硬件上移动速度都一样。

      图形程序和游戏通常会跟踪一个时间差(Deltatime)变量，它储存了渲染上一帧所用的时间。我们把所有速度都去乘以deltaTime值。结果就是，
     如果我们的deltaTime很大，就意味着上一帧的渲染花费了更多时间，所以这一帧的速度需要变得更高来平衡渲染所花去的时间。使用这种方法时，
     无论你的电脑快还是慢，摄像机的速度都会相应平衡，这样每个用户的体验就都一样了。
     */

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraFront * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraFront * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse) // 这个bool变量初始时是设定为true的
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw1  += xoffset;
    pitch1 += yoffset;
    if(pitch1 > 89.0f)
        pitch1 =  89.0f;
    if(pitch1 <= -89.0f)
        pitch1 = -89.0f;
    glm::vec3 front = vec3(0.0f, 0.0f, 0.0f);
    front.x = cos(glm::radians(pitch1)) * cos(glm::radians(yaw1));
    front.y = sin(glm::radians(pitch1));
    front.z = cos(glm::radians(pitch1)) * sin(glm::radians(yaw1));
    cameraFront = glm::normalize(front);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if(fov <= 1.0f)
        fov = 1.0f;
    if(fov >= 45.0f)
        fov = 45.0f;
}