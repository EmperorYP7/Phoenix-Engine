#pragma once

#include "Phoenix/Layer.hpp"
#include "Phoenix/Events/KeyboardEvent.hpp"
#include "Phoenix/Events/ApplicationEvent.hpp"
#include "Phoenix/Events/MouseEvent.hpp"

namespace Phoenix {

	class PX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	private:
		
		float m_Time;
	};

}