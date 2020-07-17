#pragma once
#include "Phoenix/Window.hpp"
#include "Phoenix/Renderer/RenderContext.hpp"

struct GLFWwindow;

namespace Phoenix
{

	class WindowsWin : public Window
	{
	private:
		GLFWwindow* m_Window;
		RendererContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	public:
		WindowsWin(const WindowProps& props);
		virtual ~WindowsWin();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		void SetEventCallback(const EventCallbackFn& callback) override 
		{ 
			m_Data.EventCallback = callback;
		}
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	};

}