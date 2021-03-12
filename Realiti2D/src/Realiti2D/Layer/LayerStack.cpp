#include "LayerStack.h"
#include "Layer.h"

namespace Realiti2D {
	LayerStack::~LayerStack() {
		for (Layer* l : m_Layers) {
			l->Destroy();
			delete l;
		}
	}

	void LayerStack::PushLayer(Layer* _Layer) {
		m_Layers.emplace_back(_Layer);
	}

	void LayerStack::PopLayer(Layer* _Layer) {
		auto it = std::find(m_Layers.begin(), m_Layers.end(), _Layer);

		if (it != m_Layers.end()) {
			_Layer->Destroy();
			m_Layers.erase(it);
		}
	}
}