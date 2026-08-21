#include "game.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "rendering/renderer_api.h"
#include "windowing/window.h"

namespace PotatoEngine::Core {

#define WIDTH 1980
#define HEIGHT 1080

Game::Game() {}

void Game::OnStart() {
    Rendering::RendererAPI::s_Backend = Rendering::RendererAPI::Backend::OpenGL;

    Windowing::Window::Init(Windowing::WindowBackend::GLFW);
    m_window = Windowing::Window::Create("Game", WIDTH, HEIGHT);
    m_window->MakeContextCurrent();

    // The same TODO from EditorApplication
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        MEB_LOG_ERROR("Failed to initialize GLAD");
        exit(1);
    }

    m_engineContext.Start();
    m_engineContext.Renderer.Init();

    // calls start
    m_engineContext.Registry.Start();
}

void Game::OnUpdate() {
    m_window->MakeContextCurrent();

    m_engineContext.InputState.Update();
    m_window->PollEvents(m_engineContext.InputState);

    m_engineContext.Registry.Update();

    auto* fbo = m_engineContext.Renderer.GetFramebufferPtr();
    const auto& spec = fbo->GetSpec();

    // TODO: show the framebuffer

    m_window->SwapBuffers();

    if (m_window->ShouldClose()) m_running = false;
}

void Game::OnDestroy() { m_engineContext.Registry.Destroy(); }

}  // namespace PotatoEngine::Core
