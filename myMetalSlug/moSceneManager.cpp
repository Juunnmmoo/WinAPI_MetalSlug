#include "moSceneManager.h"
#include "moTitleScene.h"
#include "moMission1Scene.h"
#include "moSelectScene.h"


namespace mo {

	std::vector<Scene*> SceneManager::mScenes;
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::Max);
		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::SelectPlayer] = new SelectScene();
		mScenes[(UINT)eSceneType::Mission1] = new Mission1Scene();


		mActiveScene = mScenes[(UINT)eSceneType::Title];

		for (Scene* scene : mScenes) {
			if (scene == nullptr)
				continue;
			scene->Initialize();
		}
		mActiveScene->OnEnter();
	}
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}
	void SceneManager::Render(HDC mHdc)
	{
		mActiveScene->Render(mHdc);
	}
	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
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
	void SceneManager::LoadScene(eSceneType type)
	{
		// ÇöÀç¾À
		mActiveScene->OnExit();

		//´ÙÀ½¾À
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();
	}
}