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
		void SetObject(GameObject* obj) { weaponObj.push_back(obj); }

		bool checkCrash();
	private:
		class Image* main;
		class Image* ground;
		class Image* sky;
		class Marco* mPlayer;
	
		bool stopOnce;
		Scene* curScene;
		UINT TopDiff;
		std::vector<eLayerType> weaponLayers;
		std::vector<eLayerType> charLayers;

		std::vector<GameObject*> weaponObj;
		std::vector<GameObject*> charObj;

	};
}
