#include <Phoenix.hpp>

class ExampleLayer : public Phoenix::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Phoenix::Input::IsKeyPressed(PX_KEY_TAB))
			PX_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Phoenix::Event& e) override
	{
		if (e.GetEventType() == Phoenix::EventType::KeyPressed)
		{
			Phoenix::KeyPressedEvent& event = (Phoenix::KeyPressedEvent&)e;
			if (event.GetKeyCode() == PX_KEY_TAB)
				PX_TRACE("Tab key is pressed (event)!");
			PX_TRACE("{0}", (char)event.GetKeyCode());
		}
	}
};

class Sandbox : public Phoenix::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Phoenix::Application* Phoenix::CreateApplication()
{
	return new Sandbox();
}