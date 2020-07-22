#pragma once
#include "Phoenix/Core.hpp"


namespace Phoenix
{
	class PX_API RenderContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}