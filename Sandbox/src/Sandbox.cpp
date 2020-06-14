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
		PX_CORE_INFO("ExampleLayer is updated!");
	}

	void OnEvent(Phoenix::Event& e) override
	{
		PX_TRACE("{0}", e);
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