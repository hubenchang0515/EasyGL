#include <EasyGL/EasyGL.h>

using namespace EasyGL;

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 inPos;\n"
    "layout (location = 1) in vec3 inColor;\n"
    "out vec3 outColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);\n"
    "   outColor = inColor;\n"
    "}\n\0";

const char *fragmentShaderSource = 
    "#version 330 core\n"
    "in vec3 outColor;"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(outColor, 1.0);\n"
    "}\n\0";

int main(void)
{
    Application::init();
    Application app{"EasyGL", 640, 480};
    Shader vertexShader{Shader::Type::VertexShader, vertexShaderSource};
    Shader fragmentShader{Shader::Type::FragmentShader, fragmentShaderSource};
    ShaderProgram shaderProgram;
    shaderProgram.attach(vertexShader);
    shaderProgram.attach(fragmentShader);
    shaderProgram.link();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// left  
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// right 
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// top   
    };

    VertexBuffer vertexBuffer;
    vertexBuffer.bind();
    vertexBuffer.setData(sizeof(vertices), vertices, Buffer::Usage::StreamDraw);

    VertexArray vertexArray;
    vertexArray.bind();
    vertexArray.attribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
    vertexArray.attribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(sizeof(GLfloat) * 3));

    while (app.update())
    {
        app.clear();
        shaderProgram.use();
        vertexArray.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    return 0;
}