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
		
		virtual void OnEnter();
		virtual void OnExit();

		void addGameObject(GameObject* obj, eLayerType layerType) {
			mLayers[(UINT)layerType].addGameObject(obj);
		}

	private:

		std::vector<Layer> mLayers;
	};
}

