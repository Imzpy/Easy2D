#include "..\e2dbase.h"
#include "..\e2dmanager.h"
#include "..\e2dtool.h"
#include <thread>

using namespace std::chrono;


e2d::Game * e2d::Game::_instance = nullptr;

e2d::Game::Game()
	: _ended(true)
	, _paused(false)
	, _config(nullptr)
{
	CoInitialize(nullptr);

	_start = _last = _now = steady_clock::now();
}

e2d::Game::~Game()
{
	GC::safeRelease(_config);

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
	auto input = Input::getInstance();
	auto window = Window::getInstance();
	auto renderer = Renderer::getInstance();
	auto timer = Timer::getInstance();
	auto sceneManager = SceneManager::getInstance();
	auto actionManager = ActionManager::getInstance();

	if (!input || !window || !renderer || !timer || !sceneManager || !actionManager)
	{
		throw SystemException(L"��ʼ��ʧ��");
	}

	HWND hWnd = window->getHWnd();
	if (hWnd == nullptr)
	{
		throw SystemException(L"�޷���������");
	}

	// ��ʾ����
	::ShowWindow(hWnd, SW_SHOWNORMAL);
	::UpdateWindow(hWnd);
	window->poll();

	// ��ʼ��Ϸ
	const milliseconds frameInterval(15LL);
	milliseconds wait, interval;
	
	_ended = false;
	_last = _now = steady_clock::now();

	while (!_ended)
	{
		_now = steady_clock::now();
		interval = duration_cast<milliseconds>(_now - _last);

		if (frameInterval < interval)
		{
			_last = _now;

			input->update();			// ��ȡ�û�����
			timer->update();			// ���¶�ʱ��
			actionManager->update();	// ���¶���������
			sceneManager->update();		// ���³�������
			_config->_update();			// ������Ϸ����
			renderer->render();			// ��Ⱦ��Ϸ����
			window->poll();				// ��������Ϣ
			GC::flush();				// ˢ���ڴ��
		}
		else
		{
			wait = frameInterval - interval;
			if (wait.count() > 1LL)
			{
				std::this_thread::sleep_for(wait - milliseconds(1LL));
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
	if (_paused && !_ended)
	{
		_last = _now = steady_clock::now();
		Timer::getInstance()->updateTime();
		ActionManager::getInstance()->updateTime();
	}
	_paused = false;
}

bool e2d::Game::isPaused()
{
	return _paused;
}

void e2d::Game::setConfig(Config* config)
{
	if (config && _config != config)
	{
		GC::release(_config);
		_config = config;
		_config->_unconfigured = true;
		GC::retain(_config);
	}
}

e2d::Config* e2d::Game::getConfig()
{
	if (!_config)
		_config = new (e2d::autorelease) Config();
	return _config;
}

double e2d::Game::getTotalTime() const
{
	return duration_cast<microseconds>(steady_clock::now() - _start).count() / 1000.0 / 1000.0;
}

void e2d::Game::quit()
{
	_ended = true;	// ���������������Ϸ�Ƿ����
}

void e2d::Game::cleanup()
{
	GC::clear();
	Image::clearCache();
	Player::getInstance()->clearCache();
}
