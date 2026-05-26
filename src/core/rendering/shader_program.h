#ifndef POTATO_SHADER_PROGRAM_H
#define POTATO_SHADER_PROGRAM_H

namespace PotatoEngine::Core::Rendering {

	class ShaderProgram {

	public:
		virtual ~ShaderProgram();

		virtual void Bind();
		virtual void Unbind();
	};
}

#endif // POTATO_SHADER_PROGRAM_H