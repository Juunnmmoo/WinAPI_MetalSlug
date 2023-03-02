#pragma once
#include "momoEngine.h"

namespace mo {
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hWnd);
		void Run();
		void Update();
		void Render();

	private:

		HWND mHwnd;
		HDC mHdc;

	};
}
