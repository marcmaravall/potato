#include "renderer.h"

#include <core/engine_context.h>

namespace PotatoEngine::Core::Rendering {
	
	void Renderer::Init() {
        m_rendererAPI = RendererAPI::Create(RendererAPI::Backend::OpenGL);
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
        m_rendererAPI->SetClearColor(glm::vec4(0.2f, 0.3f, 0.6f, 1.0f));

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

        m_texture = Texture2D::Create((m_engineContext.AssetsManager.GetRoot() +
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

	void Renderer::RenderScene() {
		
		/*
		std::queue<ECS::Entity> entityQueue;
		entityQueue.push(m_engineContext.RootEntity);

		// DFS traversal of the hierarchy
		while (!entityQueue.empty()) {
			size_t entityCount = entityQueue.size();

			for (int i = 0; i < entityCount; i++) {
				ECS::Entity& entity = entityQueue.front();
				for (auto& component : entity.Components) {
					if (component.Name == "Sprite Renderer") {
						// TODO: render the sprite
						exit(1);
					}
				}

				entityQueue.pop();

				for (auto& child : entity.Children) {
					entityQueue.push(child);
				}
			}
		}
		*/

        m_framebuffer->Bind();
		// TODO: set to framebuffer's dimensions
        m_rendererAPI->SetViewport(0, 0, 1000, 1000);
        m_rendererAPI->Clear();

        m_shaderProgram->Use();

        m_texture->Bind();
        m_vao->Bind();

        m_rendererAPI->DrawArrays(3);

        m_vao->Unbind();
        m_shaderProgram->Unuse();
        m_framebuffer->Unbind();
	}
}
