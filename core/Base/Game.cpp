#include "..\e2dbase.h"
#include "..\e2dmanager.h"
#include "..\e2dtool.h"
#include <thread>


e2d::Game * e2d::Game::_instance = nullptr;

e2d::Game::Game()
	: _quit(true)
	, _paused(false)
	, _config()
{
	CoInitialize(nullptr);

	_start = _last = _now = Time::now();
}

e2d::Game::~Game()
{
	CoUninitialize();
}

e2d::Game * e2d::Game::getInstance()
{
	if (!_instance)
		_instance = new (std::nothrow) Game;
	return _instance;
}

void e2d::Game::destroyInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}

void e2d::Game::start()
{
	SceneManager::getInstance()->update();

	HWND hWnd = Window::getInstance()->getHWnd();
	::ShowWindow(hWnd, SW_SHOWNORMAL);
	::UpdateWindow(hWnd);
	Window::getInstance()->poll();

	_quit = false;
	_last = _now = Time::now();

	const Duration minInterval(15);
	
	while (!_quit)
	{
		_now = Time::now();
		Duration interval = _now - _last;

		if (minInterval < interval)
		{
			_last = _now;
			Input::getInstance()->update();
			Timer::getInstance()->update();
			ActionManager::getInstance()->update();
			SceneManager::getInstance()->update();
			Renderer::getInstance()->render();
			Window::getInstance()->poll();
			GC::getInstance()->flush();
		}
		else
		{
			// ID2D1HwndRenderTarget ����Ⱦʱ��ȴ���ʾ��ˢ�£��������˴�ֱͬ����
			// �����˷ǳ��ȶ�����ʱ���ã����Դ󲿷�ʱ����Ҫ�ֶ������߳̽�����ʱ��
			// ����Ĵ������һЩ����£����細����С��ʱ�������̣߳���ֹռ�ù��� CPU ��
			int wait = (minInterval - interval).milliseconds();
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
		_last = _now = Time::now();
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
	if (_config.isSoundEnabled() != config.isSoundEnabled())
	{
		if (config.isSoundEnabled())
			Player::getInstance()->getXAudio2()->StartEngine();
		else
			Player::getInstance()->getXAudio2()->StopEngine();
	}

	_config = config;
}

const e2d::Config& e2d::Game::getConfig()
{
	return _config;
}

e2d::Duration e2d::Game::getTotalDuration() const
{
	return std::move(_now - _start);
}

void e2d::Game::quit()
{
	_quit = true;
}

void e2d::Game::cleanup()
{
	GC::getInstance()->clear();
	Image::clearCache();
	Player::getInstance()->clearCache();
}
