#pragma once
#include "Core.hpp"
#include "Events/Event.hpp"
#include "LayerStack.hpp"
#include "Phoenix/Events/ApplicationEvent.hpp"
#include "Window.hpp"
#include "Phoenix/ImGui/ImGui.hpp"
#include "Phoenix/Renderer/Shader.hpp"

namespace Phoenix 
{
	class PX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *m_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		static Application* m_Instance;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

		std::unique_ptr<Shader> m_Shader;
	};

	Application* CreateApplication();
}