#include "moApplication.h"
#include "moSceneManager.h"
#include "moTime.h"
#include "moInput.h"

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

		mWidth = 1080;
		mHeight = 600;

		// 원하는크기로 RECT만들고 rect 윈도우 정보창의 크기를 더해줌?
		RECT rect = { 0, 0, mWidth, mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// 윈도우 크기 변경및 출력설정
		SetWindowPos(mHwnd
			, nullptr, 100, 50
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mHwnd, true);


		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP defaultBitmap
			= (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(defaultBitmap);


		Input::Initialize();
		Time::Initizlize();
		SceneManager::Initialize();
	}
	void Application::Run()
	{
		Update();
		Render();
	}
	void Application::Update()
	{

		Input::Update();
		Time::Update();
		SceneManager::Update();
		
		// 백버퍼에 있는 그림을 원본버퍼에 그려줘야한다.
		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
	}
	void Application::Render()
	{
		clear();

		Input::Render(mHdc);
		Time::Render(mHdc);
		SceneManager::Render(mHdc);
	}

	void Application::clear()
	{
		HBRUSH grayBrush = CreateSolidBrush(RGB(121, 121, 121));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, grayBrush);
		Rectangle(mBackHdc, -1, -1, 1082, 602);
		SelectObject(mBackHdc, oldBrush);
		DeleteObject(grayBrush);
	}
	
}