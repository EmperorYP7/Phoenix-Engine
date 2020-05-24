#include "PXpch.h"
#include "Platform/Windows/WindowsWin.h"
#include "Phoenix.h"
#include "Phoenix/Events/ApplicationEvent.h"
#include "Phoenix/Events/MouseEvent.h"
#include "Phoenix/Events/KeyboardEvent.h"


namespace Phoenix
{

	static bool s_GLFWInitialized = false;
	
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWin(props);
	}

	WindowsWin::WindowsWin(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWin::~WindowsWin()
	{
		Shutdown();
	}

	void WindowsWin::Init(const WindowProps& props)
	{

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		PX_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			PX_CORE_ASSERT(success, "Couldn't initialized GLFW!");

			s_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWin::Shutdown()
	{

		glfwDestroyWindow(m_Window);
	}

	void WindowsWin::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWin::SetVSync(bool enabled)
	{

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWin::IsVSync() const
	{
		return m_Data.VSync;
	}

}