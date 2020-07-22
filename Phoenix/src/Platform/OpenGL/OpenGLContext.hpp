#pragma once

#include "Phoenix/Renderer/RenderContext.hpp"

struct GLFWwindow;

namespace Phoenix {

	class OpenGLContext : public RenderContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}