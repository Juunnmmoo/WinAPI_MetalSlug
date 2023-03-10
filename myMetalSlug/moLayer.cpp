#include "moLayer.h"

namespace mo {
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		for (GameObject* obj : mGameObjects) {
			delete obj;
			obj = nullptr;
		}
	}
	void Layer::Initialize()
	{
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState() != GameObject::eState::Active)
				continue;

			gameObj->Initialize();
		}
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState() != GameObject::eState::Active)
				continue;
			gameObj->Update();
		}
	}
	void Layer::Render(HDC mHdc)
	{
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr)
				continue;

			if (gameObj->GetState() != GameObject::eState::Active)
				continue;
			gameObj->Render(mHdc);
		}
	}
	void Layer::AddGameObject(GameObject* obj)
	{
		mGameObjects.push_back(obj);
	}
}