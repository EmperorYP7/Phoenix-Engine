#pragma once

#ifdef PX_PLATFORM_WINDOWS

extern Phoenix::Application* Phoenix::CreateApplication();

int main(int argc, char** argv)
{
	Phoenix::Log::Init();

	PX_CORE_ERROR("Initialised Log!");
	PX_INFO("Hello");

	auto app = Phoenix::CreateApplication();
	app->Run();
	delete app;
}


#endif