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
    "layout (location = 1) in vec2 inTextureCoord;\n"
    "out vec2 textureCoord;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = projection * view * model * vec4(inPos, 1.0);\n"
    "    textureCoord = inTextureCoord;\n"
    "}\n";

const char *fragmentShaderSource = 
    "#version 330 core\n"
    "in vec2 textureCoord;\n"
    "out vec4 fragmentColor;\n"
    "uniform sampler2D inTexture;\n"
    "void main()\n"
    "{\n"
    "    fragmentColor = texture(inTexture, textureCoord);\n"
    "}\n";

int main(void)
{
    Window window{"EasyGL", 640, 640};
    Application::enable(GL_DEPTH_TEST);
    Shader vertexShader{Shader::Type::VertexShader, vertexShaderSource};
    Shader fragmentShader{Shader::Type::FragmentShader, fragmentShaderSource};
    ShaderProgram shaderProgram;
    shaderProgram.attach(vertexShader);
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
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    };

    unsigned int indices[] = {  
        0, 1, 2, // first triangle
        0, 2, 3,  // second triangle

        4, 5, 6,
        4, 6, 7,

        1, 5, 6,
        1, 6, 2,

        4, 0, 3,
        4, 3, 7,
    
        4, 5, 1,
        4, 1, 0,

        7, 6, 2,
        7, 2, 3,
    };

    VertexBuffer vertexBuffer;
    vertexBuffer.bind();
    vertexBuffer.setData(sizeof(vertices), vertices, VertexBuffer::Usage::StreamDraw);

    VertexArray vertexArray;
    vertexArray.bind();
    vertexArray.attribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)0);
    vertexArray.attribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(sizeof(GLfloat) * 3));

    IndexBuffer indexBuffer;
    indexBuffer.bind();
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

    // 设置视角
    glm::mat4 view{1.0f};
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
    shaderProgram.setMatrix<4>("view", glm::value_ptr(view));

    while (!window.shouldClose())
    {
        window.clear();
        for (size_t i = 0; i < cubePositions.size(); i++)
        {
            glm::mat4 model{1.0f};
            model = glm::translate(model, cubePositions[i]); // 移动到世界坐标
            model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f)); // 随便加点角度
            model = glm::rotate(model, static_cast<float>(Application::getTime()), glm::vec3(0.5f, 1.0f, 0.0f)); // 动画
            shaderProgram.setMatrix<4>("model", glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        // 投影
        float aspect = static_cast<float>(window.width()) / static_cast<float>(window.height());
        glm::mat4 projection{1.0f};
        projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
        shaderProgram.setMatrix<4>("projection", glm::value_ptr(projection));

        window.update();
    }

    return 0;
}