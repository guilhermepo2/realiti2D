#pragma once
#include <vector>

namespace Realiti2D {

	class Layer;

	class LayerStack {
	public:
		LayerStack() {}
		~LayerStack();

		void PushLayer(Layer* _Layer);
		void PopLayer(Layer* _Layer);

		const std::vector<Layer*>& GetLayers() { return m_Layers; }
	private:
		std::vector<Layer*> m_Layers;
	};
}