#include <Phoenix.hpp>

class Sandbox : public Phoenix::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Phoenix::Application* Phoenix::CreateApplication()
{
	return new Sandbox();
}