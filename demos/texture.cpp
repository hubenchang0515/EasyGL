#include <EasyGL/EasyGL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace EasyGL;

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 inPos;\n"
    "layout (location = 1) in vec3 inColor;\n"
    "layout (location = 2) in vec2 inTexCoord;\n"
    "out vec3 outColor;\n"
    "out vec2 texCoord;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(inPos, 1.0);\n"
    "    outColor = inColor;\n"
    "    texCoord = inTexCoord;\n"
    "}\n";

const char *fragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 outColor;\n"
    "in vec2 texCoord;\n"
    "uniform sampler2D outTexture;\n"
    "void main()\n"
    "{\n"
    "    FragColor = texture(outTexture, texCoord) * vec4(outColor, 1.0);\n"
    "}\n";

int main(void)
{
    Application::init();
    Application app{"EasyGL", 640, 640};
    Shader vertexShader{Shader::Type::VertexShader, vertexShaderSource};
    Shader fragmentShader{Shader::Type::FragmentShader, fragmentShaderSource};
    ShaderProgram shaderProgram;
    shaderProgram.attach(vertexShader);
    shaderProgram.attach(fragmentShader);
    shaderProgram.link();

    float vertices[] = {
        // ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
         0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,    1.0f, -1.0f,   // 右下
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,    1.0f,  1.0f,   // 右上
        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   -1.0f, -1.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   -1.0f,  1.0f    // 左上
    };

    VertexBuffer vertexBuffer;
    vertexBuffer.bind();
    vertexBuffer.setData(sizeof(vertices), vertices, VertexBuffer::Usage::StreamDraw);

    VertexArray vertexArray;
    vertexArray.bind();
    vertexArray.attribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
    vertexArray.attribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(sizeof(GLfloat) * 3));
    vertexArray.attribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(sizeof(GLfloat) * 6));

    unsigned int indices[] = {  
        0, 1, 2, // first
        1, 2, 3  // second
    };

    IndexBuffer indexBuffer;
    indexBuffer.bind();
    indexBuffer.setData(sizeof(indices), indices, IndexBuffer::Usage::StaticDraw);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true); // 图片和纹理的坐标系不同，上下反转
    stbi_uc* data = stbi_load("../res/cat.png", &width, &height, &channels, 0);
    if (data == nullptr)
    {
        ERROR("%s\n", stbi_failure_reason());
        return EXIT_FAILURE;
    }

    INFO("width: %d height: %d channels:%d\n", width, height, channels);

    Texture texture;
    texture.bind(Texture::Target::Texture2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    
    while (app.update())
    {
        app.clear();
        shaderProgram.use();
        vertexArray.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    return 0;
}