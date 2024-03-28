#include <EasyGL/EasyGL.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace EasyGL;

#ifdef DEMO_SOURCE_DIR
    #define TEXTURE_FILE DEMO_SOURCE_DIR "/texture.png"
#else
    #define TEXTURE_FILE "./texture.png"
#endif 

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 inPos;\n"
    "layout (location = 1) in vec2 inCoord;\n"
    "out vec2 vertexCoord;\n"
    "out vec3 vertexPos;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * model * vec4(inPos, 1.0);\n"
    "   vertexPos = vec3(model * vec4(inPos, 1.0));\n"
    "   vertexCoord = inCoord;\n"
    "}\n";

const char *geometryShaderSource = 
    "#version 330 core\n"
    "layout (triangles) in;\n"
    "layout (triangle_strip, max_vertices = 3) out;\n"
    "in vec2 vertexCoord[];\n"
    "in vec3 vertexPos[];\n"
    "out vec2 textureCoord;\n"
    "out vec3 geometryPos;\n"
    "out vec3 normalVec;\n"
    "void main()\n"
    "{\n"
    "   vec3 v1 = vertexPos[1] - vertexPos[0];\n"
    "   vec3 v2 = vertexPos[2] - vertexPos[0];\n"
    "   vec3 norm = normalize(cross(v2, v1));\n"
    "   for (int i = 0; i < gl_in.length(); i++){\n"
    "       gl_Position = gl_in[i].gl_Position;\n"
    "       textureCoord = vertexCoord[i];\n"
    "       geometryPos = vertexPos[i];\n"
    "       normalVec = norm;\n"
    "       EmitVertex();\n"
    "   }\n"
    "   EndPrimitive();"
    "}\n";;

const char *fragmentShaderSource = 
    "#version 330 core\n"
    "in vec2 textureCoord;\n"
    "in vec3 geometryPos;\n"
    "in vec3 normalVec;\n"
    "out vec4 fragmentColor;\n"
    "uniform vec3 cameraPos;\n"
    "uniform vec3 lightPos;\n"
    "uniform vec3 lightColor;\n"
    "uniform float ambient;\n"
    "uniform sampler2D inTexture;\n"
    "void main()\n"
    "{\n"
    "   vec3 ambientColor = ambient * lightColor * vec3(texture(inTexture, textureCoord));\n"
    "   vec3 lightVec = normalize(lightPos - geometryPos);\n"
    "   float diffuse = max(dot(normalVec, lightVec), 0.0f);\n"
    "   vec3 diffuseColor = diffuse * lightColor * vec3(texture(inTexture, textureCoord));\n"
    "   vec3 cameraVec = normalize(cameraPos - geometryPos);\n"
    "   vec3 reflectVec = reflect(-lightVec, normalVec);\n"
    "   float specular = pow(max(dot(cameraVec, reflectVec), 0.0), 32);\n"
    "   vec3 specularColor = specular * lightColor * vec3(texture(inTexture, textureCoord));\n"
    "   fragmentColor = vec4(ambientColor + diffuseColor + specularColor, 1.0f);\n"
    "}\n";


const char *lightVertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 inPos;\n"
    "layout (location = 1) in vec3 inColor;\n"
    "out vec3 vertexColor;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * model * vec4(inPos, 1.0);\n"
    "   vertexColor = inColor;\n"
    "}\n";

const char *lightfragmentShaderSource = 
    "#version 330 core\n"
    "in vec3 vertexColor;\n"
    "out vec4 fragmentColor;\n"
    "void main()\n"
    "{\n"
    "   fragmentColor = vec4(vertexColor, 1.0);\n"
    "}\n";

int main(void)
{
    Window window{"EasyGL", 640, 640};
    Application::enable(GL_DEPTH_TEST);

    // 光源
    VertexShader lightVertexShader{lightVertexShaderSource};
    FragmentShader lightFragmentShader{lightfragmentShaderSource};
    ShaderProgram lightShaderProgram;
    lightShaderProgram.attach(lightVertexShader);
    lightShaderProgram.attach(lightFragmentShader);
    lightShaderProgram.link();
    lightShaderProgram.use();

    float lightVertices[] = {
        // ---- 位置 ----    ---   颜色   ---
        -0.1f,  0.0f,  0.0f,    1.0f, 1.0f, 1.0f,
         0.1f,  0.0f,  0.0f,    1.0f, 1.0f, 1.0f,

         0.0f, -0.1f,  0.0f,    1.0f, 1.0f, 1.0f,
         0.0f,  0.1f,  0.0f,    1.0f, 1.0f, 1.0f,

         0.0f,  0.0f, -0.1f,    1.0f, 1.0f, 1.0f,
         0.0f,  0.0f,  0.1f,    1.0f, 1.0f, 1.0f,
    };

    VertexBuffer lightVertexBuffer;
    lightVertexBuffer.setData(sizeof(lightVertices), lightVertices, VertexBuffer::Usage::StreamDraw);

    VertexArray lightVertexArray;
    lightVertexArray.attribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
    lightVertexArray.attribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(sizeof(float) * 3));

    // 图形
    VertexShader vertexShader{vertexShaderSource};
    GeometryShader geometryShader{geometryShaderSource};
    FragmentShader fragmentShader{fragmentShaderSource};
    ShaderProgram shaderProgram;
    shaderProgram.attach(vertexShader);
    shaderProgram.attach(geometryShader);
    shaderProgram.attach(fragmentShader);
    shaderProgram.link();
    shaderProgram.use();

    //   4 --- 5
    //  /|    /|
    // 0 --- 1 |  
    // | 7 --| 6
    // |/    |/
    // 3 --- 2

    float vertices[] = {
        // ---- 位置 ----      - 纹理坐标 -
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    };

    unsigned int indices[] = {  
        0, 1, 2, // first triangle
        0, 2, 3,  // second triangle

        5, 4, 7,
        5, 7, 6,

        1, 5, 6,
        1, 6, 2,

        4, 0, 3,
        4, 3, 7,
    
        4, 5, 1,
        4, 1, 0,

        3, 2, 6,
        3, 6, 7,
    };

    VertexBuffer vertexBuffer;
    vertexBuffer.setData(sizeof(vertices), vertices, VertexBuffer::Usage::StreamDraw);

    VertexArray vertexArray;
    vertexArray.attribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)0);
    vertexArray.attribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(sizeof(float) * 3));

    IndexBuffer indexBuffer;
    indexBuffer.setData(sizeof(indices), indices, IndexBuffer::Usage::StaticDraw);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true); // 图片和纹理的坐标系不同，上下反转
    INFO("file: %s\n", TEXTURE_FILE);
    stbi_uc* data = stbi_load(TEXTURE_FILE, &width, &height, &channels, 0);
    if (data == nullptr)
    {
        ERROR("%s\n", stbi_failure_reason());
        return EXIT_FAILURE;
    }
    INFO("width: %d height: %d channels:%d\n", width, height, channels);

    Texture texture;
    texture.setWrapMethod2D(Texture::WrapAxis::X, Texture::WrapMethod::ClampToEdge);
    texture.setWrapMethod2D(Texture::WrapAxis::Y, Texture::WrapMethod::ClampToEdge);
    texture.setImage2D(width, height, Texture::PixelFormat::RGBA, Texture::PixelType::UByte, data);
    stbi_image_free(data);

    // 世界坐标
    std::vector<glm::vec3> cubePositions = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f),
    };

    // 摄像机
    Camera camera{glm::vec3{0.0f, 0.0f, 10.0f}};
    camera.setMoveSpeed(3.0f);
    window.setUserData(&camera);
    window.setMouseMoveCallback([](Window& window, double x, double y){
        Camera* camera = static_cast<Camera*>(window.userData());
        camera->handleMouseMove(x, y);
    });
    window.setMouseScrollCallback([](Window& window, double dx, double dy){
        Camera* camera = static_cast<Camera*>(window.userData());
        camera->handleMouseScroll(dx, dy);
    });
    
    // 主循环
    while (!window.shouldClose())
    {
        camera.handleKeyInput(window);
        float aspect = static_cast<float>(window.width()) / static_cast<float>(window.height());
        glm::mat4 projection = camera.projection(aspect);

        window.clear();

        // 绘制光源
        lightShaderProgram.use();
        lightVertexArray.bind();
        lightShaderProgram.setMatrix<4>("view", glm::value_ptr(camera.view())); // 摄像机 View
        lightShaderProgram.setMatrix<4>("projection", glm::value_ptr(projection));  // 摄像机投影
        float radius = 3.0f;
        glm::vec3 lightPos{
            radius*glm::sin(static_cast<float>(Application::getTime())), 
            0.0f, 
            radius*glm::cos(static_cast<float>(Application::getTime()))
        };
        glm::mat4 lightModel{1.0f};
        lightModel = glm::translate(lightModel, lightPos); // 移动到世界坐标
        lightShaderProgram.setMatrix<4>("model", glm::value_ptr(lightModel));
        glDrawArrays(GL_LINES, 0, 6);

        // 绘制图形
        shaderProgram.use();
        vertexArray.bind();
        shaderProgram.setValue("ambient", 0.1f);                                // 设置环境光系数
        shaderProgram.setMatrix<4>("view", glm::value_ptr(camera.view()));      // 摄像机 View
        shaderProgram.setMatrix<4>("projection", glm::value_ptr(projection));   // 摄像机投影
        shaderProgram.setVector<3>("cameraPos", glm::value_ptr(camera.pos()));  // 设置 view 坐标计算镜面光照
        shaderProgram.setVector<3>("lightPos", glm::value_ptr(lightPos));
        shaderProgram.setVector<3>("lightColor", &lightVertices[3]); // 设置光源颜色
        for (size_t i = 0; i < cubePositions.size(); i++)
        {
            glm::mat4 model{1.0f};
            model = glm::translate(model, cubePositions[i]); // 移动到世界坐标
            model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f)); // 随便加点角度
            model = glm::rotate(model, static_cast<float>(Application::getTime()), glm::vec3(0.5f, 1.0f, 0.0f)); // 动画
            shaderProgram.setMatrix<4>("model", glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        window.update();
    }

    return 0;
}