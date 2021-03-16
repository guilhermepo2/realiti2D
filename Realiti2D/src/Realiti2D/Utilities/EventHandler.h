#pragma once
#include <functional>

namespace Realiti2D {
	template <typename T>
	class EventHandler {
	public:
		typedef std::function<void(void*, T)> signature_t;
		typedef std::list<signature_t> functionList_t;

		typename functionList_t::iterator operator +=(signature_t callback) {
			m_callbacks.emplace_front(callback);
			return m_callbacks.begin();
		}

		void operator -=(typename functionList_t::iterator& it) {
			m_callbacks.erase(it);
		}

		void Invoke(void* sender, T data) {
			for (auto& callback : m_callbacks) {
				callback(sender, data);
			}
		}

	private:
		functionList_t m_callbacks;
	};
}