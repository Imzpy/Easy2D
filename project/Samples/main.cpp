// Copyright (C) 2019 Nomango

#include "include-forwards.h"

namespace
{
	struct Demo
	{
		String title;
		ScenePtr(*Create)();
	};

	Demo s_Demos[] = {
		{ L"动画示例", Demo1::Create },
		{ L"输入示例", Demo2::Create },
		{ L"音频播放示例", Demo3::Create },
	};
	int s_DemoIndex = 0;
	int s_DemoNum = sizeof(s_Demos) / sizeof(Demo);
}

class DemoApp
	: public Application
{
public:
	DemoApp()
	{
		Options options;
		options.title = L"Easy2D示例程序";
		options.width = WINDOW_WIDTH;
		options.height = WINDOW_HEIGHT;

		Init(options);
	}

	void OnStart() override
	{
		ChangeDemoScene();
	}

	void ChangeDemoScene()
	{
		Window::Instance()->SetTitle(s_Demos[s_DemoIndex].title);

		ScenePtr scene = s_Demos[s_DemoIndex].Create();
		EnterScene(scene);

		// 添加按键监听
		scene->AddListener(KeyboardEvent::Up, Closure(this, &DemoApp::KeyPressed));

		// 显示提示文字
		TextPtr intro = new Text(L"Key 1~3 to select demo");
		intro->SetFontSize(16.f);
		scene->AddChild(intro);
	}

	void KeyPressed(Event const& evt)
	{
		E2D_ASSERT(evt.type == KeyboardEvent::Up);

		if (evt.key.code > KeyCode::Num0 &&
			evt.key.code <= (KeyCode::Num0 + s_DemoNum))
		{
			s_DemoIndex = evt.key.code - KeyCode::Num1;
			ChangeDemoScene();
		}
	}
};

int main()
{
	try
	{
		DemoApp app;
		app.Run();
	}
	catch (std::exception& e)
	{
		::MessageBoxA(nullptr, e.what(), "An exception has occurred!", MB_ICONERROR | MB_TASKMODAL);
	}
	return 0;
}
