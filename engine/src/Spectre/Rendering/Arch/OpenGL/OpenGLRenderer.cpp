#include "Spectre/Rendering/Arch/OpenGL/OpenGLRenderer.h"
#include "Spectre/Input/Keyboard.h"
#include "Spectre/Input/Mouse.h"

using namespace Spectre;

/*================================ TEMPORARY ================================*/

// Object related
float vertices[] = {
    0.5f,  0.5f,  0.0f,  // top right
    0.5f,  -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f, 0.5f,  0.0f   // top left
};

unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
};

unsigned int vao, vbo, ebo;

// Shaders
const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
unsigned int vertexShader;

const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";
unsigned int fragmentShader;

unsigned int shaderProgram;

void temp_init() {
    LOG_DEBUG("Calling #temp_init()");

#pragma region SHADERS
    // Create a new vertex shader, set `vertexShader` to that ID.
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach the shader source to the shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LOG_ERROR("Vertex", "Failed shader compliation.");
        LOG_ERROR("Vertex", infoLog);
    }

    // Do the same things for fragment
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOG_ERROR("Fragment", "Failed shader compliation.");
        LOG_ERROR("Fragment", infoLog);
    }

    // We now need to link the shaders into a program. First, we need to create
    // a program and feed its ID into `shaderProgram`.
    shaderProgram = glCreateProgram();

    // Now, we can attach the shaders to this program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Then we can link!
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        LOG_ERROR("Shader", "Failed shader compliation.");
        LOG_ERROR("Shader", infoLog);
    }

    // The shaders are now linked, so let's delete the shader objects as they're
    // now redundant.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
#pragma endregion SHADERS

#pragma region VAO, VBO, EBO
    // The generation order of VAO, VBO and EBOs doesn't really matter that much
    glGenVertexArrays(1, &vao);
    // 1 comes from how many buffer objects we'd to generate,
    // e.g. we can also feed into an array of uints.
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // Order is as follows
    // - Bind VAO
    // - Set vertex buffers
    // - Configure vertex attributes
    glBindVertexArray(vao);

    // Bind the buffer to the `GL_ARRAY_BUFFER` target.
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Feed the vertices into the buffer, which is now bound to
    // `GL_ARRAY_BUFFER`.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind the EBO and copy the indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // We can tell OpenGL how to interpret vertex data per vertex attribute as
    // follows. The first parameter specifies which attribute we want to
    // congfigure. In our case, we said in our vertex shader (line 14) that the
    // shader should expect the position to be in attribute 0 (layout = 0). The
    // second parameter is the size of the vertex attribute, 3 being a vec3 in
    // our case. Third argument specifies the type, since we're passing in
    // floats, a GL_FLOAT will do. The fourth argument is whether we want data
    // to be normalised, which currently isn't relevant for us. The fifth
    // argument is known as the stride, which is basically how much space is
    // between consecutive attributes. We know that the next set of position
    // data is located exactly three times the size of a float away, since each
    // position is three floats. The last parameter is the offset, which we do
    // not care about right now either.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);

    // Next up, we need to enable the vertex attribute.
    glEnableVertexAttribArray(0);
#pragma endregion VAO, VBO, EBO
}

/*===========================================================================*/

void OpenGLRenderer::resizeCallback(GLFWwindow* window, int width, int height) {
    LOG_TRACE("Resizing to " << width << "x" << height);
    glViewport(0, 0, width, height);
}

bool OpenGLRenderer::initialise() {
    LOG_INFO("Initialising OpenGL renderer");

    if (!glfwInit()) {
        LOG_ERROR("Failed to initialise GLFW!");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

bool OpenGLRenderer::createWindow(const std::string& title, int width,
                                  int height) {
    LOG_INFO("Creating OpenGL Window");

    m_WindowName = title;
    m_Width = width;
    m_Height = height;

    m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowName.c_str(),
                                nullptr, nullptr);

    if (m_Window == nullptr) {
        LOG_ERROR("Failed to create new window!");
        glfwTerminate();

        return false;
    }

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Failed to initialise GLAD!");
        glfwTerminate();

        return false;
    }

    // Set viewport & resize callback
    glViewport(0, 0, m_Width, m_Height);
    glfwSetFramebufferSizeCallback(
        m_Window, [](GLFWwindow* window, int width, int height) {
            OpenGLRenderer* renderer =
                static_cast<OpenGLRenderer*>(glfwGetWindowUserPointer(window));
            renderer->resizeCallback(window, width, height);
        });

    // Set input clalback
    glfwSetKeyCallback(m_Window,
                       [](GLFWwindow* window, int key, int scancode, int action,
                          int mods) { Keyboard::registerAction(key, action); });

    glfwSetMouseButtonCallback(
        m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            Mouse::registerAction(button, action);
        });
    glfwSetCursorPosCallback(m_Window,
                             [](GLFWwindow* window, double xpos, double ypos) {
                                 Mouse::registerMove(xpos, ypos);
                             });

    glfwSetWindowUserPointer(m_Window, this);

    LOG_INFO("Initialised OpenGL viewport (" << m_Width << "x" << m_Height
                                             << ")");
    LOG_INFO("> GLFW v" << glfwGetVersionString() << ", OpenGL v"
                        << glGetString(GL_VERSION));
    LOG_INFO("> Graphics Card: " << glGetString(GL_RENDERER) << ", "
                                 << glGetString(GL_VENDOR));

    temp_init();

    return true;
}

void OpenGLRenderer::update() {
    if (glfwWindowShouldClose(m_Window)) {
        Engine::getInstance()->stop();
    }

    glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // === TEMPORARY ===
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // === TEMPORARY ===

    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

void OpenGLRenderer::stop() {
    LOG_TRACE("Terminating renderer");

    glfwTerminate();
}