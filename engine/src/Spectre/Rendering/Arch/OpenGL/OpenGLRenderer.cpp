#include "Spectre/Rendering/Arch/OpenGL/OpenGLRenderer.h"

using namespace Spectre;

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

    glfwSetWindowUserPointer(m_Window, this);

    LOG_INFO("Initialised OpenGL viewport (" << m_Width << "x" << m_Height
                                             << ")");
    LOG_INFO("> GLFW v" << glfwGetVersionString() << ", OpenGL v"
                        << glGetString(GL_VERSION));
    LOG_INFO("> Graphics Card: " << glGetString(GL_RENDERER) << ", "
                                 << glGetString(GL_VENDOR));

    return true;
}

void OpenGLRenderer::update() {
    glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(m_Window);
    glfwPollEvents();

    if (glfwWindowShouldClose(m_Window)) {
        Engine::getInstance()->stop();
    }
}

void OpenGLRenderer::stop() {
    LOG_TRACE("Terminating renderer");

    glfwTerminate();
}