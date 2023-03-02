#include "moSceneManager.h"

namespace mo {

	std::vector<Scene*> SceneManager::mScenes;

	void SceneManager::Initialize()
	{
		for (Scene* scene : mScenes) {
			if (scene == nullptr)
				continue;
			scene->Initialize();
		}
	}
	void SceneManager::Update()
	{
		for (Scene* scene : mScenes) {
			if (scene == nullptr)
				continue;
			scene->Update();
		}
	}
	void SceneManager::Render(HWND mHwnd)
	{
		for (Scene* scene : mScenes) {
			if (scene == nullptr)
				continue;
			scene->Render(mHwnd);
		}
	}
	void SceneManager::Release()
	{
		for (Scene* scene : mScenes) {
			if (scene == nullptr)
				continue;
			delete scene;
			scene = nullptr;
		}
	}
}