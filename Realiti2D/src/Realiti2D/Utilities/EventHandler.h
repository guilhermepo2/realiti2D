#pragma once
#include <functional>

namespace Realiti2D {

	#define R2D_EVENT(x) std::bind(x, this, std::placeholders::_1, std::placeholders::_2)

	template <typename T>
	class EventHandler {
	public:
		typedef std::function<void(void*, T)> FunctionSignature;

		struct Event {
			FunctionSignature	callback;
			int					HandleID;
		};

		int Register(FunctionSignature callback) {
			m_callbacks.emplace_front( Event { callback, m_LastHandlerID } );
			return m_LastHandlerID++;
		}

		bool Unregister(int HandlerID) {
			for (std::list<Event>::iterator it = m_callbacks.begin(); it != m_callbacks.end();) {
				if ((*it).HandleID == HandlerID) {
					m_callbacks.erase(it);
					return true;
				}
			}

			return false;
		}

		void Invoke(void* sender, T data) {
			for (auto& callbackStruct : m_callbacks) {
				callbackStruct.callback(sender, data);
			}
		}

	private:
		std::list<Event> m_callbacks;
		int m_LastHandlerID = 0;
	};
}