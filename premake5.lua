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

group "Dependencies"
	include "Phoenix/vendor/GLFW"
	include "Phoenix/vendor/Glad"

include "Phoenix/vendor/GLFW"
include "Phoenix/vendor/Glad"

project "Phoenix"
	location "Phoenix"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "PXpch.h"
	pchsource "Phoenix/src/PXpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"GLAD"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PX_PLATFORM_WINDOWS",
			"PX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "PX_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "PX_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Final"
			defines "PX_FINAL"
			buildoptions "/MD"
			optimize "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Phoenix/vendor/spdlog/include",
		"Phoenix/src",
		"Phoenix/vendor"
	}

	links
	{
		"Phoenix"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PX_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "PX_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "PX_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Final"
			defines "PX_FINAL"
			buildoptions "/MD"
			optimize "On"