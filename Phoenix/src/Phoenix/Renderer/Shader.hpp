#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Phoenix
{
	class Shader
	{
	public:
		Shader(const std::string& Vertexsrc, const std::string& Fragsrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
		void UploadMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;
	};
}