#include "..\e2dbase.h"
#include "..\e2dmanager.h"
#include "..\e2dtool.h"
#include "..\e2dcollider.h"


e2d::Game * e2d::Game::_instance = nullptr;

e2d::Game::Game()
	: _ended(false)
	, _paused(false)
	, _initialized(false)
{
	CoInitialize(nullptr);
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

void e2d::Game::start(bool cleanup)
{
	if (!_initialized)
	{
		throw Exception(L"��ʼ��Ϸǰδ���г�ʼ��");
	}

	auto gc = GC::getInstance();
	auto input = Input::getInstance();
	auto window = Window::getInstance();
	auto renderer = Renderer::getInstance();
	

	// ��ʼ������������
	SceneManager::__init();
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
			input->__update();			// ��ȡ�û�����
			Timer::__update();			// ���¶�ʱ��
			ActionManager::__update();	// ���¶���������
			SceneManager::__update();	// ���³�������
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
	if (_initialized && _paused)
	{
		Game::reset();
	}
	_paused = false;
}

void e2d::Game::reset()
{
	if (_initialized && !_ended)
	{
		Time::__reset();
		ActionManager::__resetAll();
		Timer::__resetAll();
	}
}

bool e2d::Game::isPaused()
{
	return _paused;
}

void e2d::Game::quit()
{
	_ended = true;	// ���������������Ϸ�Ƿ����
}

void e2d::Game::cleanup()
{
	// ɾ�����г���
	SceneManager::__uninit();
	// ɾ�����������
	Input::__clearListeners();
	// ɾ����ײ������
	Collision::__clearListeners();
	// ɾ������
	ActionManager::__uninit();
	// ���ͼƬ����
	Image::clearCache();
	// ��ն�ʱ��
	Timer::__uninit();
	// ɾ�����ж���
	GC::getInstance()->clear();
}
