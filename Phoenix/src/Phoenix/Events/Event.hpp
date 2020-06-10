#pragma once
#include "PXpch.h"
#include "Phoenix/Core.hpp"

namespace Phoenix {

	enum class EventType
	{
		None=0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None=0,
		EventCategoryApplication = SEL(0),
		EventCategoryInput       = SEL(1),
		EventCategoryKeyboard    = SEL(2),
		EventCategoryMouse       = SEL(3),
		EventCategoryMouseButton = SEL(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }



	class PX_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const 
		{ 
			return GetName(); 
		}

		inline bool IsInCategory(EventCategory c)
		{
			return GetCategoryFlags() & c;
		}

	protected:
		bool m_Handled = false;
	};

	class EventDispatcher {
		template <typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& e)
			:m_Event(e)
		{

		}

		template <typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& ae, const Event& e)
	{
		return ae << e.ToString();
	}
}