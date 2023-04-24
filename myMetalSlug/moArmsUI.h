#pragma once
#include "moGameObject.h"

namespace mo {
	class Image;
	class Animator;
	class Scene;
	class Marco;
	class CharUI;
	class ArmsUI : public GameObject
	{
	public:

		ArmsUI(Marco* marco, Scene* scene);
		~ArmsUI();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC mHdc)override;

	private:
		float mTime;
		int charNum;
		Scene* curScene;
		Marco* mPlayer;
		CharUI* units;
		CharUI* tens;
		CharUI* hundreds;
		CharUI* units_bomb;
		CharUI* tens_bomb;
		Image* armsImage;
		Image* bombImage;

		int unitsNum;
		int tensNum;
		int hundredsNum;
		int unitsNum_bomb;
		int tensNum_bomb;
	};
}
