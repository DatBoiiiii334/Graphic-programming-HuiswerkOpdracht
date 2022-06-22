#include <iostream>
#include <glad/glad.h>
#include "GLFW\glfw3.h"


int main() {
    std::cout << "hello world!\n";

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello OpenGL!", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    // triangle vertices array
    float vertices[] = {
        //position
       -1.0f, 1.0f, -1.0f,      1.0f, 0.0f, 0.0f, 1.0f, //r
       1.0f, -1.0f, 1.0f,       0.0f, 1.0f, 0.0f, 1.0f, //g
       -0.5f, 1.0f, -1.0f,      0.0f, 0.0f, 1.0f, 1.0f, //b
       0.5f, -1.0f, -1.0f,      1.0f, 0.0f, 1.0f, 1.0f, // magenta


      // 0.5f, -0.5f, 0.5f, 
       //-0.5f, 0.5f, 0.5f,   
    };

    int indices[] = {
        0,1,2,
        1,3,2,
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    //Setup Object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //END SETUP OBJECT

    //SETUP SHADER PROGRAM

    const char* vertexSource = "#version 330 core\n"
        "layout(location=0) in vec3 vPos;\n"
        "layout(location=1) in vec4 vColor; \n"
        "out vec4 color; \n"
        "void main() {\n"
        "\t gl_Position = vec4(vPos, 1.0f);\n"
        "\t color = vColor;\n"
        "}\n"
        "\0";

    const char* fragmentSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 color; \n"
        "void main() {\n"
        "\t FragColor = vec4(color.gbr, 1.0f);\n"
        //"\t FragColor = vec4(color.rgb, 1.0f);\n"
        "}\n"
        "\0";

    unsigned int vertID, fragID;
    vertID = glCreateShader(GL_VERTEX_SHADER);
    fragID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertID, 1, &vertexSource, nullptr);
    glShaderSource(fragID, 1, &fragmentSource, nullptr);

    glCompileShader(vertID);
    glCompileShader(fragID);

    unsigned int myProgram = glCreateProgram();
    glAttachShader(myProgram, vertID);
    glAttachShader(myProgram, fragID);
    glLinkProgram(myProgram);

    glDeleteShader(vertID);
    glDeleteShader(fragID);
    //END SETUP SHADER PROGRAM


    while (!glfwWindowShouldClose(window)) {

        double t = glfwGetTime();
        float r = (float)sin(t * 1.1f);
        float g = (float)sin(t * 1.3f);
        float b = (float)sin(t * 1.7f);

        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(myProgram);

        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES,0,3);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}




//#include <iostream>
//#include <glad/glad.h>
//#include "GLFW\glfw3.h"
//
//#include <fstream>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/quaternion.hpp>
//
//#include "model.h"
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#include "Utils.h"
//// Forward declarations
//void renderTerrain(glm::mat4 view, glm::mat4 projection);
//void renderSkybox(glm::mat4 view, glm::mat4 projection);
//void setupResources();
//void renderModel(Model* model, unsigned int shader, glm::vec3 position, glm::vec3 rotation, float scale, glm::mat4 view, glm::mat4 projection);
//void createFrameBuffer(int width, int height, unsigned int& frameBufferID, unsigned int& colorBufferID, unsigned int& depthBufferID);
//void renderToBuffer(unsigned int frameBufferTo, unsigned int colorBufferFrom, unsigned int shader);
//void renderQuad();
//
//glm::vec3 cameraPosition(100, 100, 100), cameraForward(0, 0, 1), cameraUp(0, 1, 0);
//
//
//unsigned int plane, planeSize, VAO, cubeSize;
//unsigned int myProgram, skyProgram, modelProgram, blitProgram, chrabbProgram, hdrShader;
//
//
////texture
////Model* backpack;
////Model* tank;
//Model* Pillar;
//Model* Garfield;
//
//unsigned int heightmapID;
//unsigned int heightNormalID;
//unsigned int dirtID, sandID, grassID;
//unsigned int rockID, snowID;
//
//void handleInput(GLFWwindow* window, float deltaTime) {
//    static bool w, s, a, d, space, ctrl;
//    static double cursorX = -1, cursorY = -1, lastCursorX, lastCursorY;
//    static float pitch, yaw;
//    static float speed = 100.0f;
//
//    float sensitivity = 100.0f * deltaTime;
//    float step = speed * deltaTime;
//
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)				w = true;
//    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)		w = false;
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)				s = true;
//    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)		s = false;
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)				a = true;
//    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)		a = false;
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)				d = true;
//    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)		d = false;
//
//    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)				space = true;
//    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)		space = false;
//    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)		ctrl = true;
//    else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)	ctrl = false;
//
//    if (cursorX == -1) {
//        glfwGetCursorPos(window, &cursorX, &cursorY);
//    }
//
//    lastCursorX = cursorX;
//    lastCursorY = cursorY;
//    glfwGetCursorPos(window, &cursorX, &cursorY);
//
//    glm::vec2 mouseDelta(cursorX - lastCursorX, cursorY - lastCursorY);
//
//    // TODO: calculate rotation & movement
//    yaw -= mouseDelta.x * sensitivity;
//    pitch += mouseDelta.y * sensitivity;
//
//    pitch = glm::max(glm::min(pitch, 90.0f), -90.0f);
//
//    if (pitch < -90.0f) pitch = -90.0f;
//    else if (pitch > 90.0f)pitch = 90.0f;
//
//    if (yaw < 180.0f) yaw += 360;
//    else if (yaw > 180.0f) yaw -= 360;
//
//    glm::vec3 euler(glm::radians(pitch), glm::radians(yaw), 0);
//    glm::quat q(euler);
//
//    // update camera position / forward & up
//    glm::vec3 translation(0, 0, 0);
//    
//
//
//    // movement controls
//    if (w) { 
//        translation.z += speed * deltaTime; 
//    }
//    if (a) {
//        translation.x += speed * deltaTime;
//    }
//    if (s) {
//        translation.z -= speed * deltaTime;
//    }
//    if (d) {
//        translation.x -= speed * deltaTime;
//    }
//    if (space) {
//        translation.y += speed * deltaTime;
//    }
//    if (ctrl) {
//        translation.y -= speed * deltaTime;
//    }
//
//    cameraPosition += q * translation;
//    cameraUp = q * glm::vec3(0, 1, 0);
//    cameraForward = q * glm::vec3(0, 0, 1);
//}
//
//int main() {
//
//    static double previousT = 0;
//
//    std::cout << "hello world!\n";
//
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    int width = 800;
//    int height = 600;
//    GLFWwindow* window = glfwCreateWindow(width, height, "Hello OpenGL!", NULL, nullptr);
//    glfwMakeContextCurrent(window);
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    glViewport(0, 0, width, height);
//    setupResources();
//
//    unsigned int frameBuf1, frameBuf2;
//    unsigned int colorBuf1, colorBuf2;
//    unsigned int depthBuf1, depthBuf2;
//
//    createFrameBuffer(width,height, frameBuf1, colorBuf1, depthBuf1);
//    createFrameBuffer(width, height, frameBuf2, colorBuf2, depthBuf2);
//
//    // configure floating point framebuffer
//    // ------------------------------------
//    unsigned int hdrFBO;
//    glGenFramebuffers(1, &hdrFBO);
//
//    // create floating point color buffer
//    /*unsigned int colorBuffer;
//    glBindTexture(GL_TEXTURE_2D, colorBuffer);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
//
//
//    // OPENGL SETTINGS //
//    glEnable(GL_CULL_FACE);
//    glEnable(GL_DEPTH_TEST);
//
//    while (!glfwWindowShouldClose(window)) {
//        double t = glfwGetTime();
//        float r = (float)sin(t * 1.1f);
//        float g = (float)sin(t * 1.3f);
//        float b = (float)sin(t * 1.7f);
//
//        handleInput(window, (float)(t - previousT));
//        previousT = t;
//
//        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraForward, cameraUp);
//        glm::mat4 projection = glm::perspective(glm::radians(65.0f), width/ (float)height,0.1f, 1000.0f);
//
//        //
//        glBindFramebuffer(GL_FRAMEBUFFER, frameBuf1);
//            // scherm clearen
//            glClearColor(0,0,0, 0);
//            glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
// 
//            renderSkybox(view, projection);
//            renderTerrain(view, projection);
//
//            //renderModel(backpack, modelProgram, glm::vec3(200, -25, 200), glm::vec3(0, glm::radians(45.0f), 0), 50, view, projection);
//            //renderModel(tank, modelProgram, glm::vec3(500, 25, 200), glm::vec3(0, glm::radians(45.0f), 0), 20, view, projection);
//
//            
//            renderModel(Garfield, modelProgram, glm::vec3(400, 25, 200), glm::vec3(0, glm::radians(45.0f), 0), 2, view, projection);
//            
//
//            glEnable(GL_BLEND);
//            //glBlendFunc(GL_ONE_MINUS_CONSTANT_COLOR, GL_ONE);
//            glBlendFunc(GL_SRC1_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//            renderModel(Pillar, modelProgram, glm::vec3(500, 25, 200), glm::vec3(0, glm::radians(45.0f), 0), 20, view, projection);
//            glDisable(GL_BLEND);
//        //
//        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//
//        // HDR
//            glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        // [...] render (lit) scene 
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//        // now render hdr color buffer to 2D screen-filling quad with tone mapping shader
//        //hdrShader.use();
//       // glUseProgram(skyProgram its an example);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, hdrShader);
//        void RenderQuad();
//
//        std::vector<glm::vec3> lightColors;
//        lightColors.push_back(glm::vec3(200.0f, 200.0f, 200.0f));
//        lightColors.push_back(glm::vec3(0.1f, 0.0f, 0.0f));
//        lightColors.push_back(glm::vec3(0.0f, 0.0f, 0.2f));
//        lightColors.push_back(glm::vec3(0.0f, 0.1f, 0.0f));
//
//
//        // POST PROCESSING
//        //renderToBuffer(frameBuf2, colorBuf1, chrabbProgram);
//        renderToBuffer(frameBuf2, colorBuf1, chrabbProgram);
//        renderToBuffer(0, colorBuf2, blitProgram);
//
//       // glEnable(GL_BLEND);
//       //glBlendFunc(GL_ONE, GL_ONE);
//
//        //renderModel(block, modelProgram, glm::vec3(200, 25, 200), glm::vec3(0, glm::radians(45.0f), 0), 20, view, projection);
//        
//       // glDisable(GL_BLEND);
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    
//    glfwTerminate();
//    return 0;
//}
//
//void renderTerrain(glm::mat4 view, glm::mat4 projection) {
//    // TERAIN ///
//    glUseProgram(myProgram);
//    glCullFace(GL_BACK);
//    glEnable(GL_DEPTH_TEST);
//
//    glm::mat4 world = glm::mat4(1.f);
//    world = glm::translate(world, glm::vec3(0, 0, 0));
//
//    glUniformMatrix4fv(glGetUniformLocation(myProgram, "world"), 1, GL_FALSE, glm::value_ptr(world));
//    glUniformMatrix4fv(glGetUniformLocation(myProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(glGetUniformLocation(myProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//    glUniform3fv(glGetUniformLocation(myProgram, "cameraPosition"), 1, glm::value_ptr(cameraPosition));
//
//    float t = glfwGetTime();
//    float i = glfwGetTime();
//    glUniform3f(glGetUniformLocation(myProgram, "lightDirection"), glm::cos(t), -0.5f, glm::sin(t));
//    glUniform3f(glGetUniformLocation(myProgram, "lightDirection"), glm::sin(i), 0.5f,  glm::cos(i));
//
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, heightmapID);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, heightNormalID);
//
//
//    glActiveTexture(GL_TEXTURE2);
//    glBindTexture(GL_TEXTURE_2D, dirtID);
//    glActiveTexture(GL_TEXTURE3);
//    glBindTexture(GL_TEXTURE_2D, sandID);
//    glActiveTexture(GL_TEXTURE4);
//    glBindTexture(GL_TEXTURE_2D, grassID);
//    glActiveTexture(GL_TEXTURE3);
//    glBindTexture(GL_TEXTURE_2D, rockID);
//    glActiveTexture(GL_TEXTURE3);
//    glBindTexture(GL_TEXTURE_2D, snowID);
//
//    glBindVertexArray(plane);
//    glDrawElements(GL_TRIANGLES, planeSize, GL_UNSIGNED_INT, 0);
//    glBindVertexArray(0);
//}
//
//void renderSkybox(glm::mat4 view, glm::mat4 projection) {
//    // SkyBox ///
//    glUseProgram(skyProgram);
//    glCullFace(GL_FRONT);
//    glDisable(GL_DEPTH_TEST);
//
//    glm::mat4 world = glm::mat4(1.f);
//    world = glm::translate(world, cameraPosition);
//
//    glUniformMatrix4fv(glGetUniformLocation(skyProgram, "world"), 1, GL_FALSE, glm::value_ptr(world));
//    glUniformMatrix4fv(glGetUniformLocation(skyProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(glGetUniformLocation(skyProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//    glUniform3fv(glGetUniformLocation(skyProgram, "cameraPosition"), 1, glm::value_ptr(cameraPosition));
//
//    float t = glfwGetTime();
//    float i = glfwGetTime();
//    glUniform3f(glGetUniformLocation(skyProgram, "lightDirection"), glm::cos(t), -0.5f, glm::sin(t));
//    glUniform3f(glGetUniformLocation(myProgram, "lightDirection"), glm::sin(i), 0.5f, glm::cos(i));
//
//    //glActiveTexture(GL_TEXTURE0);
//    //glBindTexture(GL_TEXTURE_2D, diffuseTextID);
//
//    glBindVertexArray(VAO);
//    //glDrawArrays(GL_TRIANGLES,0,3);
//    glDrawElements(GL_TRIANGLES, cubeSize, GL_UNSIGNED_INT, 0);
//}
//
//void setupResources() {
//
//    //backpack = new Model("backpack/backpack.obj");
//    //tank = new Model("tank/tank.obj");
//    Pillar = new Model("Pillar/obj/objPillar.obj");
//    Garfield = new Model("Garfield/garfield.obj");
//
//    /// need 24 vertices for normal/uv-mapped Cube
//    float vertices[] = {
//        // positions            //colors            // tex coords   // normals
//        0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,   1.f, 0.f,       0.f, -1.f, 0.f,
//        0.5f, -0.5f, 0.5f,      1.0f, 1.0f, 1.0f,   1.f, 1.f,       0.f, -1.f, 0.f,
//        -0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,   0.f, 1.f,       0.f, -1.f, 0.f,
//        -0.5f, -0.5f, -.5f,     1.0f, 1.0f, 1.0f,   0.f, 0.f,       0.f, -1.f, 0.f,
//
//        0.5f, 0.5f, -0.5f,      1.0f, 1.0f, 1.0f,   2.f, 0.f,       1.f, 0.f, 0.f,
//        0.5f, 0.5f, 0.5f,       1.0f, 1.0f, 1.0f,   2.f, 1.f,       1.f, 0.f, 0.f,
//
//        0.5f, 0.5f, 0.5f,       1.0f, 1.0f, 1.0f,   1.f, 2.f,       0.f, 0.f, 1.f,
//        -0.5f, 0.5f, 0.5f,      1.0f, 1.0f, 1.0f,   0.f, 2.f,       0.f, 0.f, 1.f,
//
//        -0.5f, 0.5f, 0.5f,      1.0f, 1.0f, 1.0f,   -1.f, 1.f,      -1.f, 0.f, 0.f,
//        -0.5f, 0.5f, -.5f,      1.0f, 1.0f, 1.0f,   -1.f, 0.f,      -1.f, 0.f, 0.f,
//
//        -0.5f, 0.5f, -.5f,      1.0f, 1.0f, 1.0f,   0.f, -1.f,      0.f, 0.f, -1.f,
//        0.5f, 0.5f, -0.5f,      1.0f, 1.0f, 1.0f,   1.f, -1.f,      0.f, 0.f, -1.f,
//
//        -0.5f, 0.5f, -.5f,      1.0f, 1.0f, 1.0f,   3.f, 0.f,       0.f, 1.f, 0.f,
//        -0.5f, 0.5f, 0.5f,      1.0f, 1.0f, 1.0f,   3.f, 1.f,       0.f, 1.f, 0.f,
//
//        0.5f, -0.5f, 0.5f,      1.0f, 1.0f, 1.0f,   1.f, 1.f,       0.f, 0.f, 1.f,
//        -0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,   0.f, 1.f,       0.f, 0.f, 1.f,
//
//        -0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f,   0.f, 1.f,       -1.f, 0.f, 0.f,
//        -0.5f, -0.5f, -.5f,     1.0f, 1.0f, 1.0f,   0.f, 0.f,       -1.f, 0.f, 0.f,
//
//        -0.5f, -0.5f, -.5f,     1.0f, 1.0f, 1.0f,   0.f, 0.f,       0.f, 0.f, -1.f,
//        0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,   1.f, 0.f,       0.f, 0.f, -1.f,
//
//        0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,   1.f, 0.f,       1.f, 0.f, 0.f,
//        0.5f, -0.5f, 0.5f,      1.0f, 1.0f, 1.0f,   1.f, 1.f,       1.f, 0.f, 0.f,
//
//        0.5f, 0.5f, -0.5f,      1.0f, 1.0f, 1.0f,   2.f, 0.f,       0.f, 1.f, 0.f,
//        0.5f, 0.5f, 0.5f,       1.0f, 1.0f, 1.0f,   2.f, 1.f,       0.f, 1.f, 0.f
//    };
//
//    unsigned int indices[] = {  // note that we start from 0!
//        // DOWN
//        0, 1, 2,   // first triangle
//        0, 2, 3,    // second triangle
//        // BACK
//        14, 6, 7,   // first triangle
//        14, 7, 15,    // second triangle
//        // RIGHT
//        20, 4, 5,   // first triangle
//        20, 5, 21,    // second triangle
//        // LEFT
//        16, 8, 9,   // first triangle
//        16, 9, 17,    // second triangle
//        // FRONT
//        18, 10, 11,   // first triangle
//        18, 11, 19,    // second triangle
//        // UP
//        22, 12, 13,   // first triangle
//        22, 13, 23,    // second triangle
//    };
//
//    cubeSize = sizeof(indices);
//
//    glGenVertexArrays(1, &VAO);
//
//    unsigned int VBO;
//    glGenBuffers(1, &VBO);
//
//    unsigned int EBO;
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//
//    //Setup Object
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    int stride = sizeof(float) * 11;
//
//    //posoition
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
//    glEnableVertexAttribArray(0);
//    //color
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 3));
//    glEnableVertexAttribArray(1);
//    //uv
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 60));
//    glEnableVertexAttribArray(2);
//    //normal
//    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * 8));
//    glEnableVertexAttribArray(3);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//
//    //END SETUP OBJECT
//    
//    plane = GeneratePlane("Heightmap2.png", GL_RGBA, 4, 1.0f, 1.0f, planeSize, heightmapID);
//    //plane = GeneratePlane("NepanHeightMap.png", GL_RGBA, 4, 1.0f, 1.0f, planeSize, heightmapID);
//
//    // terrain textures
//    heightNormalID = loadTexture("heightnormal.png", GL_RGBA, 4);
//    //heightNormalID = loadTexture("NepanHeightNormal.png", GL_RGBA, 4);
//    dirtID = loadTexture("dirt.jpg", GL_RGB, 3);
//    sandID = loadTexture("sand.jpg", GL_RGB, 3);
//    grassID = loadTexture("grass.png", GL_RGBA, 4);
//    rockID = loadTexture("rock.jpg", GL_RGB, 3);
//    snowID = loadTexture("snow.jpg", GL_RGB, 3);
//
//    //SETUP SHADER PROGRAM
//
//    char* vertexSource;
//    loadFromFile("vertexShader.shader", &vertexSource);
//    char* fragmentSource;
//    loadFromFile("fragmentShader.shader", &fragmentSource);
//
//    unsigned int vertSky, fragSky, vertModel, fragModel;
//    unsigned int vertImg, fragImg, fragchrabb;
//    unsigned int fragHDR;
//    CreateShader("vertexShaderSky.shader", GL_VERTEX_SHADER, vertSky);
//    CreateShader("fragmentShaderSky.shader", GL_FRAGMENT_SHADER, fragSky);
//    CreateShader("vertModel.shader", GL_VERTEX_SHADER, vertModel);
//    CreateShader("fragModel.shader", GL_FRAGMENT_SHADER, fragModel);
//    CreateShader("vertImg.shader", GL_VERTEX_SHADER, vertImg);
//    CreateShader("fragImg.shader", GL_FRAGMENT_SHADER, fragImg);
//    CreateShader("frag_chrabb.shader", GL_FRAGMENT_SHADER, fragchrabb);
//
//    CreateShader("fragShaderHDR.shader", GL_FRAGMENT_SHADER, fragHDR);
//    // load
//    unsigned int diffuseTextID = loadTexture("CoolPicture.jpg", GL_RGB, 3);
//
//    //end
//
//    unsigned int vertID, fragID;
//    vertID = glCreateShader(GL_VERTEX_SHADER);
//    fragID = glCreateShader(GL_FRAGMENT_SHADER);
//
//    glShaderSource(vertID, 1, &vertexSource, nullptr);
//    glShaderSource(fragID, 1, &fragmentSource, nullptr);
//
//    glCompileShader(vertID);
//    glCompileShader(fragID);
//
//    int success;
//    char infoLog[512];
//
//    glCompileShader(vertID);
//    glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(vertID, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//    };
//
//    glCompileShader(fragID);
//    glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragID, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//    };
//
//
//    myProgram = glCreateProgram();
//    glAttachShader(myProgram, vertID);
//    glAttachShader(myProgram, fragID);
//    glLinkProgram(myProgram);
//
//    skyProgram = glCreateProgram();
//    glAttachShader(skyProgram, vertSky);
//    glAttachShader(skyProgram, fragSky);
//    glLinkProgram(skyProgram);
//
//    modelProgram = glCreateProgram();
//    glAttachShader(modelProgram, vertModel);
//    glAttachShader(modelProgram, fragModel);
//    glLinkProgram(modelProgram);
//
//    blitProgram = glCreateProgram();
//    glAttachShader(blitProgram, vertImg);
//    glAttachShader(blitProgram, fragImg);
//    glLinkProgram(blitProgram);
//
//    chrabbProgram = glCreateProgram();
//    glAttachShader(chrabbProgram, vertImg);
//    glAttachShader(chrabbProgram, fragchrabb);
//    glLinkProgram(chrabbProgram);
//
//    hdrShader = glCreateProgram();
//    glAttachShader(hdrShader, fragHDR);
//    glLinkProgram(hdrShader);
//
//
//    glDeleteShader(vertID);
//    glDeleteShader(fragID);
//    glDeleteShader(vertSky);
//    glDeleteShader(fragSky);
//    glDeleteShader(vertModel);
//    glDeleteShader(fragModel);
//    glDeleteShader(vertImg);
//    glDeleteShader(fragchrabb);
//    glDeleteShader(fragHDR);
//    //END SETUP SHADER PROGRAM
//
//    /// MATRIX SETUP  ///
//    glUseProgram(myProgram);
//    glUniform1i(glGetUniformLocation(myProgram, "heightMap.png"), 0);
//    glUniform1i(glGetUniformLocation(myProgram, "normalMap.png"), 1);
//
//    glUniform1i(glGetUniformLocation(myProgram, "dirt"), 2);
//    glUniform1i(glGetUniformLocation(myProgram, "sand"), 3);
//    glUniform1i(glGetUniformLocation(myProgram, "grass"), 4);
//    glUniform1i(glGetUniformLocation(myProgram, "rock"), 2);
//    glUniform1i(glGetUniformLocation(myProgram, "snow"), 3);
//
//    //int worldLoc = glGetUniformLocation(myProgram, "world");
//    //int viewLoc = glGetUniformLocation(myProgram, "view");
//    //int projLoc = glGetUniformLocation(myProgram, "projection");
//
//    /// END MATRIX SETUP ////
//}
//
//void renderModel(Model * model, unsigned int shader, glm::vec3 position, glm::vec3 rotation, float scale, glm::mat4 view, glm::mat4 projection) {
//    // shader gebruiken
//    glUseProgram(shader);
//
//    glEnable(GL_DEPTH);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//
//    // world matrix bouwen
//    glm::mat4 world = glm::mat4(1);
//    // positie
//    world = glm::translate(world, position);
//    // schaal
//    world = glm::scale(world, glm::vec3(scale));
//    // rotatie
//    glm::quat q(rotation);
//    world = world * glm::toMat4(q);
//
//    //shader instellen
//    glUniformMatrix4fv(glGetUniformLocation(shader, "world"), 1, GL_FALSE, glm::value_ptr(world));
//    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//    glUniform3fv(glGetUniformLocation(shader, "cameraPosition"), 1, glm::value_ptr(cameraPosition));
//
//    float t = glfwGetTime();
//    glUniform3f(glGetUniformLocation(shader, "lightDirection"), glm::cos(t), -0.5f, glm::sin(t));
//
//    model->Draw(shader);
//}
//
//void createFrameBuffer(int width, int height, unsigned int &frameBufferID, unsigned int &colorBufferID, unsigned int &depthBufferID) {
//    
//    // Generate frame buffer
//    glGenFramebuffers(1, &frameBufferID);
//
//    // Generate Color buffer
//    glGenTextures(1, &colorBufferID);
//    glBindTexture(GL_TEXTURE_2D, colorBufferID);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
//
//    // Generate depth buffer
//    glGenRenderbuffers(1,&depthBufferID);
//    glBindRenderbuffer(GL_RENDERBUFFER, depthBufferID);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
//
//    // Attach buffers
//    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBufferID, 0);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferID);
//
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
//        std::cout << "Framebuffer not complete!!" << std::endl;
//    }
//
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//
//void renderToBuffer(unsigned int frameBufferTo, unsigned int colorBufferFrom, unsigned int shader) {
//    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferTo);
//
//    glUseProgram(shader);
//
//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, colorBufferFrom);
//
//    // render something!
//    renderQuad();
//
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//
//unsigned int quadVAO = 0;
//unsigned int quadVBO;
//void renderQuad() {
//    if (quadVAO == 0) {
//        float quadVertices[] = {
//            //positions         // texture Coords
//            -1.0f,1.0f,0.0f,0.0f,1.0f,
//            -1.0f,-1.0f,0.0f,0.0f,0.0f,
//            1.0f,1.0f,0.0f,1.0f,1.0f,
//            1.0f,-1.0f,0.0f,1.0f,0.0f,
//        };
//        // setup plane VAO
//        glGenVertexArrays(1, &quadVAO);
//        glGenBuffers(1, &quadVBO);
//        glBindVertexArray(quadVAO);
//        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//        glEnableVertexAttribArray(1);
//        //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
//    }
//    glBindVertexArray(quadVAO);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//    glBindVertexArray(0);
//}





