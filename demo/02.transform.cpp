#include <EasyGL/EasyGL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace EasyGL;

const char* vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 inPos;\n"
    "layout (location = 1) in vec3 inColor;\n"
    "out vec3 vertexColor;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = transform * vec4(inPos, 1.0);\n"
    "   vertexColor = inColor;\n"
    "}\n";

const char* fragmentShaderSource = 
    "#version 330 core\n"
    "in vec3 vertexColor;\n"
    "out vec4 fragmentColor;\n"
    "void main()\n"
    "{\n"
    "   fragmentColor = vec4(vertexColor, 1.0);\n"
    "}\n";

int main(void)
{
    Window window{"EasyGL Demo", 640, 640};
    VertexShader vertexShader{vertexShaderSource};
    FragmentShader fragmentShader{fragmentShaderSource};
    ShaderProgram shaderProgram;
    shaderProgram.attach(vertexShader);
    shaderProgram.attach(fragmentShader);
    shaderProgram.link();
    shaderProgram.use();

    float vertices[] = {
    //  --      坐标      --     --  颜色(RGB)  --
         0.0f,  0.5f,  0.0f,    1.0f, 0.0f, 0.0f,     // P1 点的坐标和颜色 
        -0.5f, -0.5f,  0.0f,    0.0f, 1.0f, 0.0f,     // P2
         0.5f, -0.5f,  0.0f,    0.0f, 0.0f, 1.0f,     // ...  
    };

    VertexBuffer vertexBuffer;
    vertexBuffer.setData(sizeof(vertices), vertices, Buffer::Usage::StreamDraw);

    VertexArray vertexArray;
    vertexArray.attribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
    vertexArray.attribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(sizeof(float) * 3));

    unsigned int indices[] = {  
        0, 1, 2,    // 第一个三角形的顶点索引  
    };

    IndexBuffer indexBuffer;
    indexBuffer.setData(sizeof(indices), indices, IndexBuffer::Usage::StaticDraw);
    
    glm::mat4 transform{1.0f};
    transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));         // 缩放
    transform = glm::translate(transform, glm::vec3(-0.5f, -0.5f, 0.5f));   // 平移

    window.makeCurrent();
    while (!window.shouldClose())
    {
        transform = glm::rotate(transform, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 1.0f));   // 旋转
        shaderProgram.setMatrix<4>("transform", glm::value_ptr(transform));

        window.clear();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        window.update();
    }

    return 0;
}