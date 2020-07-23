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

#include "Model.h"


using namespace glm;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void processInput(GLFWwindow *window);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

vec3 cameraPos = vec3(0.0f, 15.0f, 3.0f);
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
                                            "layout (location = 2) in vec2 aTexCoords;\n"
                                            "\n"
                                            "out vec2 TexCoords;\n"
                                            "\n"
                                            "uniform mat4 model;\n"
                                            "uniform mat4 view;\n"
                                            "uniform mat4 projection;\n"
                                            "\n"
                                            "out vec3 Normal;\n"
                                            "out vec3 FragPos;\n"
                                            "void main()\n"
                                            "{\n"
                                            "    FragPos = vec3(model * vec4(aPos, 1.0));\n"
                                            "    Normal = mat3(transpose(inverse(model))) * aNormal;\n"
                                            "    TexCoords = aTexCoords;    \n"
                                            "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
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
                                           "    sampler2D diffuse;\n"
                                           "    sampler2D specular;\n"
                                           "    float shininess;\n"
                                           "}; \n"
                                           "\n"
                                           "uniform Material material;\n"
                                           "struct Light {\n"
                                           "    vec3 position;\n"
                                           "    vec3 direction;\n"
                                           "    float cutOff;\n"
                                           "    float outerCutOff;\n"
                                           "\n"
                                           "    vec3 ambient;\n"
                                           "    vec3 diffuse;\n"
                                           "    vec3 specular;\n"
                                           "    float constant;\n"
                                           "    float linear;\n"
                                           "    float quadratic;\n"
                                           "};\n"
                                           "\n"
                                           "uniform Light light;\n"
                                           "out vec4 FragColor;\n"
                                           "\n"
                                           "uniform vec3 lightPos;\n"
                                           "in vec3 Normal;\n"
                                           "in vec3 FragPos;\n"
                                           "uniform vec3 viewPos;\n"
                                           "in vec2 TexCoords;\n"
                                           "void main()\n"
                                           "{\n"
                                           "    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;\n"
                                           "\n"
                                           "    vec3 norm = normalize(Normal);\n"
                                           "    vec3 lightDir = normalize(light.position - FragPos);\n"
                                           "    float theta = dot(lightDir, normalize(-light.direction));\n"
                                           "    float epsilon   = light.cutOff - light.outerCutOff;\n"
                                           "    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);\n"
                                           "    if(true /*|| theta > light.cutOff*/)\n"
                                           "    {\n"
                                           "        float diff = max(dot(norm, lightDir), 0.0);\n"
                                           "        vec3 diffuse = vec3(texture(material.diffuse, TexCoords)) * diff * light.diffuse;\n"
                                           "        vec3 viewDir = normalize(viewPos - FragPos);\n"
                                           "        vec3 reflectDir = reflect(-lightDir, norm);\n"
                                           "        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
                                           "        vec3 specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;\n"
                                           "        float distance    = length(light.position - FragPos);\n"
                                           "        float attenuation = 1.0 / (light.constant + light.linear * distance + \n"
                                           "                light.quadratic * (distance * distance));\n"
                                           "        vec3 result = ambient * attenuation * intensity + diffuse * attenuation * intensity + specular * attenuation * intensity;\n"
                                           "        FragColor = vec4(result, 1.0);\n"
                                           "    }\n"
                                           "    //else \n"
                                           "        //FragColor = vec4(light.ambient * vec3(texture(material.diffuse, TexCoords)), 1.0);\n"
                                           "}";


    GLchar const *fragmentShaderSourceLight = "#version 330 core\n"
                                              "out vec4 FragColor;\n"
                                              "\n"
                                              "void main()\n"
                                              "{\n"
                                              "    FragColor = vec4(1.0); // 将向量的四个分量全部设置为1.0\n"
                                              "}";

    GLchar const *fragmentShaderSourceModel = "#version 330 core\n"
                                              "struct Light {\n"
                                              "    vec3 position;\n"
                                              "    vec3 direction;\n"
                                              "    float cutOff;\n"
                                              "    float outerCutOff;\n"
                                              "\n"
                                              "    vec3 ambient;\n"
                                              "    vec3 diffuse;\n"
                                              "    vec3 specular;\n"
                                              "    float constant;\n"
                                              "    float linear;\n"
                                              "    float quadratic;\n"
                                              "};\n"
                                              "\n"
                                              "uniform Light light;\n"
                                              "in vec3 Normal;\n"
                                              "in vec3 FragPos;\n"
                                              "out vec4 FragColor;\n"
                                              "\n"
                                              "in vec2 TexCoords;\n"
                                              "\n"
                                              "uniform sampler2D texture_diffuse1;\n"
                                              "uniform vec3 viewPos;\n"
                                              "\n"
                                              "void main()\n"
                                              "{    \n"
                                              "    vec3 color = vec3(texture(texture_diffuse1, TexCoords));\n"
                                              "    vec3 ambient = color * light.ambient;\n"
                                              "    vec3 norm = normalize(Normal);\n"
                                              "    vec3 lightDir = normalize(light.position - FragPos);\n"
                                              "    float theta = dot(lightDir, normalize(-light.direction));\n"
                                              "    float epsilon   = light.cutOff - light.outerCutOff;\n"
                                              "    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);\n"
                                              "    if(theta > light.cutOff)\n"
                                              "    {\n"
                                              "        float diff = max(dot(norm, lightDir), 0.0);\n"
                                              "        vec3 diffuse = color * diff * light.diffuse;\n"
                                              "        vec3 viewDir = normalize(viewPos - FragPos);\n"
                                              "        vec3 reflectDir = reflect(-lightDir, norm);\n"
                                              "        vec3 specular = color * light.specular;\n"
                                              "        float distance    = length(light.position - FragPos);\n"
                                              "        float attenuation = 1.0 / (light.constant + light.linear * distance + \n"
                                              "                light.quadratic * (distance * distance));\n"
                                              "        vec3 result = ambient * attenuation * intensity + diffuse * attenuation * intensity + specular * attenuation * intensity;\n"
                                              "        FragColor = vec4(result, 1.0);\n"
                                              "    }\n"
                                              "    else \n"
                                              "        FragColor = vec4(ambient, 1.0);\n"
                                              "}";

    glm::vec3 lightPos(1.2f, 5.0f, 10.0f);

    Shader cubeShader = Shader(vertexShaderSimpleCube, fragmentShaderSourceModel, false);
    Shader lightShader = Shader(vertexShaderSimpleCube, fragmentShaderSourceLight, false);
    cubeShader.use();
    cubeShader.setVec3("light.ambient",  vec3(0.2f, 0.2f, 0.2f));
    cubeShader.setVec3("light.diffuse",  vec3(0.5f, 0.5f, 0.5f)); // 将光照调暗了一些以搭配场景
    cubeShader.setVec3("light.specular", vec3(1.0f, 1.0f, 1.0f));
    cubeShader.setVec3("lightPos", lightPos);
    cubeShader.setVec3("light.position",  cameraPos);
    cubeShader.setVec3("light.direction", -cameraPos);
    cubeShader.setFloat("light.cutOff",   glm::cos(glm::radians(22.5f)));
    cubeShader.setFloat("light.outerCutOff",   glm::cos(glm::radians(37.5f)));
    cubeShader.setFloat("light.constant",  1.0f);
    cubeShader.setFloat("light.linear",    0.09f);
    cubeShader.setFloat("light.quadratic", 0.032f);
    cubeShader.setVec3("viewPos", cameraPos);
    glEnable(GL_DEPTH_TEST);//开启深度测试




    Model ourModel("../nanosuit/nanosuit.obj");

    //立方体
    float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };


    GLuint indices[] = { // 注意索引从0开始!
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);//创建VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//复制顶点数据到VBO

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    //Render loop
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除深度缓冲


        lightShader.use();
        // view/projection transformations
        glm::mat4 projection1 = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);
        glm::mat4 view2 = mat4(1.0f);
        view2 = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view2);

        // render the loaded model
        glm::mat4 mode2 = glm::mat4(1.0f);
        mode2 = glm::translate(mode2, cameraPos); // translate it down so it's at the center of the scene
        mode2 = glm::scale(mode2, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
        cubeShader.setMat4("model", mode2);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);//解绑VAO



        // don't forget to enable shader before setting uniforms
        cubeShader.use();
        cubeShader.setVec3("light.direction", cameraFront);
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);
        glm::mat4 view1 = mat4(1.0f);
        view1 = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view1);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        cubeShader.setMat4("model", model);
        ourModel.Draw(cubeShader);

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