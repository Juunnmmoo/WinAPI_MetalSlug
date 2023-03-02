#include "moLayer.h"

namespace mo {
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
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
	void Layer::Render(HWND mHwnd)
	{
		for (GameObject* gameObj : mGameObjects) {
			gameObj->Render(mHwnd);
		}
	}
}