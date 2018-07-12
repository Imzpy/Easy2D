#include "..\e2dbase.h"
#include "..\e2dmanager.h"
#include "..\e2dtool.h"


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

void e2d::Game::start(bool cleanup)
{
	auto input = Input::getInstance();
	auto window = Window::getInstance();
	auto renderer = Renderer::getInstance();
	auto timer = Timer::getInstance();
	auto sceneManager = SceneManager::getInstance();
	auto actionManager = ActionManager::getInstance();
	auto inputManager = InputManager::getInstance();

	// ��ʾ����
	::ShowWindow(window->getHWnd(), SW_SHOWNORMAL);
	// ˢ�´�������
	::UpdateWindow(window->getHWnd());
	// ��������Ϣ
	window->poll();
	// ��ʼ����ʱ
	Time::__init();

	_ended = false;

	while (!_ended)
	{
		// ��������Ϣ
		window->poll();
		// ˢ��ʱ��
		Time::__updateNow();

		// �ж��Ƿ�ﵽ��ˢ��״̬
		if (Time::__isReady())
		{
			if (_config->_unconfigured)
			{
				_config->_update();
			}

			input->update();			// ��ȡ�û�����
			timer->update();			// ���¶�ʱ��
			actionManager->update();	// ���¶���������
			inputManager->update();		// �������������
			sceneManager->update();		// ���³�������
			renderer->render();			// ��Ⱦ��Ϸ����
			GC::flush();				// ˢ���ڴ��

			Time::__updateLast();		// ˢ��ʱ����Ϣ
		}
		else
		{
			Time::__sleep();			// �����߳�
		}
	}

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

void e2d::Game::quit()
{
	_ended = true;	// ���������������Ϸ�Ƿ����
}

void e2d::Game::cleanup()
{
	// ɾ�����г���
	SceneManager::getInstance()->clear();
	// ��ն�ʱ��
	Timer::getInstance()->clearAllTasks();
	// ������ж���
	ActionManager::getInstance()->clearAll();
	// ɾ����ײ������
	CollisionManager::getInstance()->clearAllListeners();
	// ɾ�����������
	InputManager::getInstance()->clearAllListeners();
	// ���ͼƬ����
	Image::clearCache();
	// ������ֻ���
	Player::getInstance()->clearCache();
	// ɾ�����ж���
	GC::clear();
}
