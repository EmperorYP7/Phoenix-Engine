#pragma once

#ifdef PX_PLATFORM_WINDOWS
	#ifdef PX_BUILD_DLL
		#define PX_API __declspec(dllexport)
	#else
		#define PX_API __declspec(dllimport)
	#endif
#else 
#error Phoenix is Windows only!
#endif

#define SEL(x) (1 << x)

#ifdef PX_ENABLE_ASSERTS
	#define PX_ASSERT(x, ...) { if(!(x)) { PX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PX_CORE_ASSERT(x, ...) { if(!(x)) { PX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PX_ASSERT(x, ...)
	#define PX_CORE_ASSERT(x, ...)
#endif

#define PX_BIND_EVENT(fn) std::bind(&fn, this, std::placeholders::_1)