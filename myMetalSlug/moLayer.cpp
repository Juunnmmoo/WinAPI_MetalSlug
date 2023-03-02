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
			gameObj->Initialize();
		}
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects) {
			gameObj->Update();
		}
	}
	void Layer::Render(HDC mHdc)
	{
		for (GameObject* gameObj : mGameObjects) {
			gameObj->Render(mHdc);
		}
	}
}