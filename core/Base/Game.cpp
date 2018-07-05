#include "..\e2dbase.h"
#include "..\e2dmanager.h"
#include "..\e2dtool.h"
#include "..\e2dcollider.h"


e2d::Game * e2d::Game::_instance = nullptr;

e2d::Game::Game()
	: _ended(false)
	, _paused(false)
	, _config(nullptr)
{
	CoInitialize(nullptr);
}

e2d::Game::~Game()
{
	GC::release(_config);

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

void e2d::Game::start(bool cleanup)
{
	auto gc = GC::getInstance();
	auto input = Input::getInstance();
	auto window = Window::getInstance();
	auto renderer = Renderer::getInstance();
	auto actionManager = ActionManager::getInstance();
	auto sceneManager = SceneManager::getInstance();

	// ��ʾ����
	::ShowWindow(window->getHWnd(), SW_SHOWNORMAL);
	// ˢ�´�������
	::UpdateWindow(window->getHWnd());
	// ��������Ϣ
	window->__poll();
	// ��ʼ����ʱ
	Time::__init();

	_ended = false;

	while (!_ended)
	{
		// ��������Ϣ
		window->__poll();
		// ˢ��ʱ��
		Time::__updateNow();

		// �ж��Ƿ�ﵽ��ˢ��״̬
		if (Time::__isReady())
		{
			// ��������
			if (_config && _config->_unconfigured)
			{
				_config->_update();
			}

			input->__update();			// ��ȡ�û�����
			Timer::__update();			// ���¶�ʱ��
			actionManager->__update();	// ���¶���������
			sceneManager->__update();	// ���³�������
			renderer->__render();		// ��Ⱦ��Ϸ����

			Time::__updateLast();		// ˢ��ʱ����Ϣ
		}
		else
		{
			Time::__sleep();			// �����߳�
			gc->__update();				// ˢ���ڴ��
		}
	}

	_ended = true;

	if (cleanup)
	{
		Game::cleanup();
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
		Time::__reset();
		Timer::__resetAll();
		ActionManager::getInstance()->__resetAll();
	}
	_paused = false;
}

bool e2d::Game::isPaused()
{
	return _paused;
}

void e2d::Game::setConfig(Config * config)
{
	if (_config != config && config)
	{
		GC::release(_config);
		_config = config;
		_config->_unconfigured = true;
		GC::retain(_config);
	}
}

e2d::Config * e2d::Game::getConfig()
{
	if (!_config)
	{
		_config = Create<Config>();
		GC::retain(_config);
	}
	return _config;
}

void e2d::Game::quit()
{
	_ended = true;	// ���������������Ϸ�Ƿ����
}

void e2d::Game::cleanup()
{
	// ɾ�����г���
	SceneManager::getInstance()->clear();
	// ɾ����ײ������
	Collision::removeAllListeners();
	// ɾ�����������
	Input::removeAllListeners();
	// ���ͼƬ����
	Image::clearCache();
	// ��ն�ʱ��
	Timer::removeAll();
	// ɾ�����ж���
	GC::getInstance()->clear();
}
