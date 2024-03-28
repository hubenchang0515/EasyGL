#include <EasyGL/EasyGL.h>

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
    "layout (location = 1) in vec3 inColor;\n"
    "layout (location = 2) in vec2 inTextureCoord;\n"
    "out vec3 vertexColor;\n"
    "out vec2 textureCoord;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(inPos, 1.0);\n"
    "    vertexColor = inColor;\n"
    "    textureCoord = inTextureCoord;\n"
    "}\n";

const char *fragmentShaderSource = 
    "#version 330 core\n"
    "in vec3 vertexColor;\n"
    "in vec2 textureCoord;\n"
    "out vec4 fragmentColor;\n"
    "uniform sampler2D inTexture;\n"
    "void main()\n"
    "{\n"
    "    fragmentColor = texture(inTexture, textureCoord) * vec4(vertexColor, 1.0);\n"
    "}\n";

int main(void)
{
    Window window{"EasyGL", 640, 640};
    VertexShader vertexShader{vertexShaderSource};
    FragmentShader fragmentShader{fragmentShaderSource};
    ShaderProgram shaderProgram;
    shaderProgram.attach(vertexShader);
    shaderProgram.attach(fragmentShader);
    shaderProgram.link();
    shaderProgram.use();

    float vertices[] = {
        // ---- 位置 ----       ---- 颜色 ----       - 纹理坐标 -
         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,    1.0f, 0.0f,   // 右下
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,    1.0f, 1.0f,   // 右上
        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,    0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,    0.0f, 1.0f    // 左上
    };

    VertexBuffer vertexBuffer;
    vertexBuffer.setData(sizeof(vertices), vertices, VertexBuffer::Usage::StreamDraw);

    VertexArray vertexArray;
    vertexArray.attribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
    vertexArray.attribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(sizeof(GLfloat) * 3));
    vertexArray.attribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(sizeof(GLfloat) * 6));

    unsigned int indices[] = {  
        0, 1, 2, // first triangle
        1, 2, 3  // second triangle
    };

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
    texture.setImage2D(width, height, Texture::PixelFormat::RGBA, Texture::PixelType::UByte, data);
    stbi_image_free(data);
    
    while (!window.shouldClose())
    {
        window.clear();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        window.update();
    }

    return 0;
}