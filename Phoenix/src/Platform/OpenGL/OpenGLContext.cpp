#include <PXpch.h>
#include "OpenGLContext.hpp"
#include<GLFW/glfw3.h>
#include <glad/glad.h>

namespace Phoenix
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		:m_WindowHandle(window)
	{
		PX_CORE_ASSERT(window, "Window is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PX_CORE_ASSERT(status, "Failed to load Glad!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	OpenGLContext::~OpenGLContext()
	{

	}
}