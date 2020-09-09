#pragma once

namespace Phoenix
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1, Direct3D = 2, Vulcan = 3
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}