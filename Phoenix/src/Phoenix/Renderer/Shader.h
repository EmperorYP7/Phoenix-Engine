#pragma once
#include <string>

namespace Phoenix
{
	class Shader
	{
	public:
		Shader(const std::string& Vertexsrc, const std::string& Fragsrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID;
	};
}