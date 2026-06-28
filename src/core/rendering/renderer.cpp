#include "renderer.h"

#include <core/engine_context.h>

namespace PotatoEngine::Core::Rendering {
	
	void Renderer::Init() {
        m_rendererAPI = RendererAPI::Create(RendererAPI::Backend::OpenGL);
        FramebufferSpec spec;
        spec.Width = 120;
        spec.Height = 120;

        FramebufferTextureSpec colorAttachment;
        colorAttachment.Format = FramebufferTextureFormat::RGBA8;

        FramebufferTextureSpec entityAttachment;
        entityAttachment.Format = FramebufferTextureFormat::RED_INTEGER;

        FramebufferTextureSpec depthAttachment;
        depthAttachment.Format = FramebufferTextureFormat::Depth;

        spec.Attachments.Attachments = {
            colorAttachment,
            entityAttachment,
            depthAttachment
        };

        m_framebuffer = Framebuffer::Create(spec);

        // m_rendererAPI->Init();

        m_rendererAPI->SetClearColor(glm::vec4(0.2f, 0.3f, 0.6f, 1.0f));

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,
             0.5f, -0.5f, 0.0f,     1.0f, 0.0f,
             0.5f,  0.5f, 0.0f,     1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f,     0.0f, 1.0f
        };

        uint32_t indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        m_vao = VertexArray::Create();

        auto vbo = VertexBuffer::Create(vertices, sizeof(vertices));
        vbo->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoord" }
        });

        auto ibo = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

        m_vao->AddVertexBuffer(vbo);
        m_vao->SetIndexBuffer(ibo);

        const char* vertSrc = R"(
            #version 450 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Model;

            out vec2 v_TexCoord;

            void main()
            {
                v_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
            }
        )";

        const char* fragSrc = R"(
            #version 450 core

            in vec2 v_TexCoord;

            uniform sampler2D u_Texture;
            uniform vec4 u_Color;

            layout(location = 0) out vec4 FragColor;

            void main()
            {
                FragColor = texture(u_Texture, v_TexCoord) * u_Color;
            }
        )";

        auto vertex = Shader::Create(ShaderType::VERTEX, vertSrc);
        auto fragment = Shader::Create(ShaderType::FRAGMENT, fragSrc);

        vertex->Compile();
        fragment->Compile();

        if (!vertex->CompileSuccessful() || !fragment->CompileSuccessful()) {
            MEB_LOG_ERROR("Sprite shader compilation failed");
            return;
        }

        m_shaderProgram = ShaderProgram::Create();
        m_shaderProgram->AttachShader(*vertex);
        m_shaderProgram->AttachShader(*fragment);

        m_shaderProgram->LinkProgram();

        if (!m_shaderProgram->LinkSuccessful()) {
            MEB_LOG_ERROR("Sprite shader linking failed");
            return;
        }

        MEB_LOG_INFO("Renderer initialized successfully");
    }

	void Renderer::RenderScene() {

        m_framebuffer->Bind();
        m_rendererAPI->SetViewport(0, 0, m_width, m_height);
        m_rendererAPI->Clear();

        

        m_framebuffer->Unbind();
	}

	void Renderer::RenderSprite(const ECS::Components::Transform& transform, const ECS::Components::SpriteRenderer& sr) {
        m_shaderProgram->Use();
        m_shaderProgram->UniformMatrix4fv("u_ViewProjection", transform.GetMatrix());
        m_shaderProgram->Uniform4f("u_Color", sr.Color);

        if (sr.Texture)
            sr.Texture->Bind();

        m_shaderProgram->Unuse();
    }
}
