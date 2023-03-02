#pragma once
#include "moEntity.h"
#include "moLayer.h"

namespace mo {
	class Scene : public Entity
	{
	public:

		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC mHdc);

	private:

		std::vector<Layer> mLayers;
	};
}
