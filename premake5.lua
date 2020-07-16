workspace "Phoenix"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Final"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Glad"] = "Phoenix/vendor/Glad/include"
IncludeDir["GLFW"] = "Phoenix/vendor/GLFW/include"
IncludeDir["ImGui"] = "Phoenix/vendor/ImGui"
IncludeDir["glm"] = "Phoenix/vendor/glm"

group "Dependencies"
	include "Phoenix/vendor/GLFW"
	include "Phoenix/vendor/Glad"
	include "Phoenix/vendor/ImGui"

group ""

project "Phoenix"
	location "Phoenix"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "PXpch.h"
	pchsource "Phoenix/src/PXpch.cpp"

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"GLAD",
		"ImGui"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PX_PLATFORM_WINDOWS",
			"PX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		filter "configurations:Debug"
			defines "PX_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "PX_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Final"
			defines "PX_FINAL"
			runtime "Release"
			optimize "on"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Phoenix/vendor/spdlog/include",
		"Phoenix/src",
		"Phoenix/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Phoenix"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"PX_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "PX_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "PX_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Final"
			defines "PX_FINAL"
			runtime "Release"
			optimize "on"
