#pragma once

#include "Phoenix/Layer.hpp"
#include "Phoenix/Events/KeyboardEvent.hpp"
#include "Phoenix/Events/MouseEvent.hpp"

namespace Phoenix {

	class PX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate();
		void OnEvent(Event& e);
		void OnAttach();
		void OnDetach();
	private:
		void OnEvent(Event& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		//bool OnKeyTypedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseScrollEvent(MouseScrollEvent& e);
		float m_Time;
	};

}