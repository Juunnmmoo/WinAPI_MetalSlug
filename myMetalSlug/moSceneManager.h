#pragma once
#include "moScene.h"

namespace mo {
	class SceneManager
	{
	public:
		
		static void Initialize();
		static void Update();
		static void Render(HWND mHwnd);
		static void Release();

	private:

		static std::vector<Scene*> mScenes;
		
	};
}
