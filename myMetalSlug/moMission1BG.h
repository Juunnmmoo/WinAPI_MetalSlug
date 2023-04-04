#pragma once
#include "moGameObject.h"

namespace mo {
	class Scene;
	class Mission1BG : public GameObject
	{
	public:

		Mission1BG(Scene* scene);
		~Mission1BG();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

		void SetPlayer(class Marco* marco) { mPlayer = marco; }
		void SetObject(GameObject* obj) { mObjects.push_back(obj); }

	private:
		class Image* main;
		class Image* ground;
		class Marco* mPlayer;
		Scene* curScene;
		std::vector<eLayerType> layers;
		UINT TopDiff;
		std::vector<GameObject*> mObjects;
	};
}
