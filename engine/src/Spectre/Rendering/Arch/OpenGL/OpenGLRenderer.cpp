#include "Spectre/Rendering/Arch/OpenGL/OpenGLRenderer.h"
#include "Spectre/Input/Keyboard.h"
#include "Spectre/Input/Mouse.h"
#include "Spectre/Rendering/Arch/OpenGL/OpenGLMesh.h"

using namespace Spectre;

/*================================ TEMPORARY ================================*/

// Object related
std::vector<Vertex> vertices = {
    // top right
    {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
    // bottom right
    {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
    // bottom left
    {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
    // top left
    {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f)}};

std::vector<int> indices = {
    // note that we start from 0!
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
};

OpenGLShader* shader = nullptr;
OpenGLMesh* mesh = nullptr;

void temp_init() {
    LOG_DEBUG("Calling #temp_init()");

    shader = new OpenGLShader("assets/shaders/Default.vert",
                              "assets/shaders/Default.frag");
    mesh = new OpenGLMesh(vertices, indices);
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
    // glUseProgram(shaderProgram);
    shader->use();
    mesh->bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // === TEMPORARY ===

    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

void OpenGLRenderer::stop() {
    LOG_TRACE("Terminating renderer");

    glfwTerminate();
}