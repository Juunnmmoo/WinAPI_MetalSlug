#include "moApplication.h"
#include "moSceneManager.h"

namespace mo {
	Application::Application()
		: mHdc(NULL)
		, mHwnd(NULL)
	{
	}
	Application::~Application()
	{
	}
	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);
		SceneManager::Initialize();
	}
	void Application::Run()
	{
		Update();
		Render();
	}
	void Application::Update()
	{
		SceneManager::Update();
		
	}
	void Application::Render()
	{

		SceneManager::Render(mHwnd);
	}
	
}