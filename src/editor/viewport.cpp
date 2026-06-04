#include "viewport.h"

using namespace PotatoEngine::Core::Rendering;

namespace PotatoEngine::Editor {

    Viewport::Viewport(EditorContext& ctx) : EditorPanel("Viewport", ctx)
    {
        m_api = RendererAPI::Create(RendererAPI::Backend::OpenGL);
        // m_api->Init();

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
        m_api->SetClearColor(glm::vec4(0.2f, 0.3f, 0.6f, 1.0f));

        const char* vertSrc = R"(
        #version 450 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor;
        layout (location = 2) in vec2 aTexCoord;
        
        out vec3 ourColor;
        out vec2 TexCoord;
        
        void main()
        {
            gl_Position = vec4(aPos, 1.0);
            ourColor = aColor;
            TexCoord = aTexCoord;
        }
        )";

        const char* fragSrc = R"(
        #version 450 core
        out vec4 FragColor;
  
        in vec3 ourColor;
        in vec2 TexCoord;

        uniform sampler2D ourTexture;

        void main()
        {
            FragColor = texture(ourTexture, TexCoord);
        }
        )";

        auto vertex = Shader::Create(ShaderType::VERTEX, vertSrc);
        auto fragment = Shader::Create(ShaderType::FRAGMENT, fragSrc);
        vertex->Compile();
		if (!vertex->CompileSuccessful()) {
            MEB_LOG_ERROR("Vertex shader compilation failed");
            exit(1);
        }
        fragment->Compile();
        if (!fragment->CompileSuccessful()) {
            MEB_LOG_ERROR("Fragment shader compilation failed");
            exit(1);
        }

        m_shaderProgram = ShaderProgram::Create();
        m_shaderProgram->AttachShader(*vertex);
        m_shaderProgram->AttachShader(*fragment);
        m_shaderProgram->LinkProgram();
		if (!m_shaderProgram->LinkSuccessful()) {
            MEB_LOG_ERROR("Shader program linking failed");
        }
        else {
			MEB_LOG_INFO("Shader program linked successfully!");
        }

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,  1.0, 0.0, 0.0, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f,  0.0, 1.0, 0.0, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,  0.0, 0.0, 1.0, 1.0f, 0.0f
        };

		m_texture = Texture::Create((m_editorContext.AssetsManager.GetRoot() + 
            Core::AssetsManager::Path("/assets/tests/texture.gif").c_str()));

        auto vbo = VertexBuffer::Create(vertices, sizeof(vertices));
		vbo->SetData(vertices, sizeof(vertices));
        vbo->Unbind();

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float3, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" }
        };
        vbo->SetLayout(layout);

        m_vao = VertexArray::Create();
        m_vao->AddVertexBuffer(vbo);

		MEB_ASSERT(m_vao);
        MEB_ASSERT(m_shaderProgram);
    }

    void Viewport::OnBegin() {

    }

    void Viewport::OnRender() {
        ImVec2 avail = ImGui::GetContentRegionAvail();
        uint32_t width = (uint32_t)avail.x;
        uint32_t height = (uint32_t)avail.y;

        if (width > 0 && height > 0 && (width != m_width || height != m_height)) {
            m_width = width;
            m_height = height;
            m_framebuffer->Resize(width, height);
        }

        m_framebuffer->Bind();
        m_api->SetViewport(0, 0, m_width, m_height);
        m_api->Clear();

        m_shaderProgram->Use();

		m_texture->Bind();
        m_vao->Bind();

        m_api->DrawArrays(3);

        m_vao->Unbind();
		m_shaderProgram->Unuse();
        m_framebuffer->Unbind();

        ImTextureID texId = (ImTextureID)(uintptr_t)m_framebuffer->GetColorAttachmentID(0);
        ImGui::Image(texId, avail, ImVec2(0, 1), ImVec2(1, 0));
    }

    void Viewport::OnEnd() {

    }
}