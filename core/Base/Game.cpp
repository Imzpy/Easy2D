#include "..\e2dbase.h"
#include "..\e2dnode.h"
#include "..\e2dtransition.h"
#include "..\e2dmanager.h"
#include "..\e2dtool.h"
#include <thread>


e2d::Game * e2d::Game::_instance = nullptr;

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

e2d::Game::Game()
	: _quit(true)
	, _paused(false)
	, _currScene(nullptr)
	, _nextScene(nullptr)
	, _transition(nullptr)
	, _scenes()
{
	::CoInitialize(nullptr);

	_window = Window::getInstance();
	_input = Input::getInstance();
	_renderer = Renderer::getInstance();
	_timer = Timer::getInstance();
	_actionManager = ActionManager::getInstance();
}

e2d::Game::~Game()
{
	::CoUninitialize();
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
	updateScene();
	
	while (!_quit)
	{
		auto now = Time::now();
		auto dur = now - last;

		if (dur.milliseconds() > minInterval)
		{
			last = now;
			_input->update();

			if (!_paused)
			{
				_timer->update();
				_actionManager->update();
				updateScene();
			}
			
			drawScene();
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
		_timer->updateTime();
		_actionManager->updateTime();
	}
	_paused = false;
}

bool e2d::Game::isPaused()
{
	return _paused;
}

void e2d::Game::quit()
{
	_quit = true;
}

void e2d::Game::pushScene(Scene * scene, bool saveCurrentScene)
{
	if (!scene)
		return;

	// ������һ������ָ��
	if (_nextScene) _nextScene->release();
	_nextScene = scene;
	_nextScene->retain();

	if (saveCurrentScene && _currScene)
	{
		_scenes.push(_currScene);
	}
}

void e2d::Game::pushScene(Transition * transition, bool saveCurrentScene)
{
	if (!transition)
		return;

	pushScene(transition->_inScene, saveCurrentScene);

	if (_transition)
	{
		_transition->_stop();
		_transition->release();
	}
	_transition = transition;
	_transition->retain();

	// ��ʼ�������л�����
	if (!_transition->_init(this, _currScene))
	{
		WARN("Transition initialize failed!");
		_transition->release();
		_transition = nullptr;
	}
}

e2d::Scene* e2d::Game::popScene()
{
	// ջΪ��ʱ�����÷��س�������ʧ��
	if (_scenes.size() == 0)
	{
		WARN("Scene stack is empty!");
		return nullptr;
	}

	_nextScene = _scenes.top();
	_nextScene->release();
	_scenes.pop();

	return _nextScene;
}

e2d::Scene * e2d::Game::popScene(Transition * transition)
{
	if (!transition)
		return nullptr;

	auto scene = popScene();
	if (scene)
	{
		if (_transition)
		{
			_transition->_stop();
			_transition->release();
		}
		_transition = transition;
		_transition->retain();

		_transition->_inScene = scene;
		_transition->_inScene->retain();

		// ��ʼ�������л�����
		if (!_transition->_init(this, _currScene))
		{
			WARN("Transition initialize failed!");
			_transition->release();
			_transition = nullptr;
		}
	}

	return scene;
}

void e2d::Game::clearAllScenes()
{
	while (!_scenes.empty())
	{
		_scenes.top()->release();
		_scenes.pop();
	}
}

e2d::Scene * e2d::Game::getCurrentScene()
{
	return _currScene;
}

const std::stack<e2d::Scene*>& e2d::Game::getSceneStack()
{
	return _scenes;
}

bool e2d::Game::isTransitioning() const
{
	return _transition != nullptr;
}

void e2d::Game::updateScene()
{
	if (_transition)
	{
		_transition->_update();

		if (_transition->isDone())
		{
			_transition->release();
			_transition = nullptr;
		}
		else
		{
			return;
		}
	}

	if (_nextScene)
	{
		if (_currScene)
		{
			_currScene->onExit();
			if (_scenes.empty() || _scenes.top() != _currScene)
			{
				_currScene->release();
			}
		}

		_nextScene->onEnter();

		_currScene = _nextScene;
		_nextScene = nullptr;
	}
}

void e2d::Game::drawScene()
{
	_renderer->beginDraw();
	{
		if (_transition)
		{
			_transition->_render();
		}
		else if (_currScene)
		{
			_currScene->visit();
		}
	}
	_renderer->endDraw();
}
