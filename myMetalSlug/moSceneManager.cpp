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
	void SceneManager::Render(HDC mHdc)
	{
		for (Scene* scene : mScenes) {
			if (scene == nullptr)
				continue;
			scene->Render(mHdc);
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