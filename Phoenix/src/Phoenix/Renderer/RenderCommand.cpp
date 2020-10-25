#include "PXpch.h"

#include "RenderCommand.hpp"
#include "Platform\OpenGL\OpenGLRendererAPI.hpp"

namespace Phoenix
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}