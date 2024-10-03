#include "Spectre/Rendering/Arch/OpenGL/OpenGLRenderer.h"

using namespace Spectre;

bool OpenGLRenderer::initialise() {
    LOG_INFO("OpenGL", "Initialising OpenGL renderer");

    if (!glfwInit()) {
        LOG_ERROR("OpenGL", "Failed to initialise GLFW!");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

bool OpenGLRenderer::createWindow(const std::string& title, int width,
                                  int height) {
    LOG_INFO("OpenGL", "Creating OpenGL Window");

    m_WindowName = title;
    m_Width = width;
    m_Height = height;

    m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowName.c_str(),
                                nullptr, nullptr);

    if (m_Window == nullptr) {
        LOG_ERROR("OpenGL", "Failed to create new window!");
        glfwTerminate();

        return false;
    }

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("OpenGL", "Failed to initialise GLAD!");
        glfwTerminate();

        return false;
    }

    glViewport(0, 0, m_Width, m_Height);

    LOG_INFO("OpenGL", "Initialised OpenGL viewport (" << m_Width << "x"
                                                       << m_Height << ")");
    LOG_INFO("OpenGL", "> GLFW v" << glfwGetVersionString() << ", OpenGL v"
                                  << glGetString(GL_VERSION));
    LOG_INFO("OpenGL", "> Graphics Card: " << glGetString(GL_RENDERER) << ", "
                                           << glGetString(GL_VENDOR));

    return true;
}

void OpenGLRenderer::render() {
    glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(m_Window);
    glfwPollEvents();

    if (glfwWindowShouldClose(m_Window)) {
        Engine::getInstance()->stop();
    }
}

void OpenGLRenderer::stop() {
    LOG_TRACE("OpenGL", "Terminating renderer");

    glfwTerminate();
}