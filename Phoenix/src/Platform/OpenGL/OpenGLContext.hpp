#pragma once
#include "Phoenix/Renderer/RenderContext.hpp"
#include "GLFW/glfw3.h"
struct GLFWwindow;

namespace Phoenix
{
	class PX_API OpenGLContext : public RendererContext
	{
	public:
		OpenGLContext(GLFWwindow* window);
		~OpenGLContext();
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}