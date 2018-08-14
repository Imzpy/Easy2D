#include "..\e2dbase.h"
#include "..\e2dmanager.h"
#include "..\e2dtool.h"
#include <thread>


e2d::Game::Game()
	: _quit(true)
	, _paused(false)
	, _config()
	, _window(nullptr)
	, _input(nullptr)
	, _renderer(nullptr)
{
	CoInitialize(nullptr);

	_input = new (std::nothrow) Input;
	_renderer = new (std::nothrow) Renderer;
}

e2d::Game::~Game()
{
	if (_renderer)
		delete _renderer;

	if (_input)
		delete _input;

	if (_window)
		delete _window;

	CoUninitialize();
}

e2d::Game * e2d::Game::getInstance()
{
	static Game instance;
	return &instance;
}

void e2d::Game::start()
{
	_quit = false;

	const int minInterval = 5;
	Time last = Time::now();
	HWND hWnd = _window->getHWnd();
	
	::ShowWindow(hWnd, SW_SHOWNORMAL);
	::UpdateWindow(hWnd);
	_window->poll();
	SceneManager::getInstance()->update();
	
	while (!_quit)
	{
		auto now = Time::now();
		auto dur = now - last;

		if (dur.milliseconds() > minInterval)
		{
			last = now;
			_input->update();
			Timer::getInstance()->update();
			ActionManager::getInstance()->update();
			SceneManager::getInstance()->update();
			_renderer->render();
			_window->poll();
			GC::getInstance()->flush();
		}
		else
		{
			// ID2D1HwndRenderTarget �����˴�ֱͬ��������Ⱦʱ��ȴ���ʾ��ˢ�£�
			// �����˷ǳ��ȶ�����ʱ���ã����Դ󲿷�ʱ����Ҫ�ֶ������߳̽�����ʱ��
			// ����Ĵ������һЩ����£����細����С��ʱ�������̣߳���ֹռ�ù��� CPU ��
			int wait = minInterval - dur.milliseconds();
			if (wait > 1)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(wait));
			}
		}
	}
}

void e2d::Game::pause()
{
	_paused = true;
}

void e2d::Game::resume()
{
	if (_paused && !_quit)
	{
		Timer::getInstance()->updateTime();
		ActionManager::getInstance()->updateTime();
	}
	_paused = false;
}

bool e2d::Game::isPaused()
{
	return _paused;
}

void e2d::Game::setConfig(const Config& config)
{
	_config = config;
}

const e2d::Config& e2d::Game::getConfig() const
{
	return _config;
}

void e2d::Game::setWindow(Window * window)
{
	_window = window;
	_renderer->init(_window);
	_input->init(_window);
}

void e2d::Game::quit()
{
	_quit = true;
}

void e2d::Game::cleanup()
{
	GC::getInstance()->clear();
	Image::clearCache();
}
