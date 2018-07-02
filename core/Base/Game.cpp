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
}

e2d::Game * e2d::Game::getInstance()
{
	if (!_instance)
		_instance = new (std::nothrow) Game;
	return _instance;
}

bool e2d::Game::init(const String& mutexName)
{
	if (_initialized)
	{
		WARN("The game has been initialized!");
		return false;
	}

	if (!mutexName.isEmpty())
	{
		// �������̻�����
		String fullMutexName = L"Easy2DApp-" + mutexName;
		HANDLE hMutex = ::CreateMutex(nullptr, TRUE, (LPCWSTR)fullMutexName);

		if (hMutex == nullptr)
		{
			WARN("CreateMutex Failed!");
		}
		else if (::GetLastError() == ERROR_ALREADY_EXISTS)
		{
			// ��������Ѿ����ڲ����������У�������ʾ
			Window::info(L"��Ϸ�������������д򿪣�", L"��ʾ");
			// �رս��̻�����
			::CloseHandle(hMutex);
			return false;
		}
	}

	// ��ʼ�� COM ���
	CoInitialize(nullptr);

	bool bRendererDevIndResInit = false,
		bWindowInit = false,
		bRendererDevResInit = false,
		bInputInit = false,
		bMusicInit = false;

	auto DestroyResources = [&]()
	{
		if (bRendererDevIndResInit) Renderer::__discardResources();
		if (bWindowInit) Window::__init();
		if (bRendererDevResInit) Renderer::__discardDeviceResources();
		if (bInputInit) Input::__uninit();
		if (bMusicInit) Music::__uninit();
	};

	// �����豸�޹���Դ
	if (Renderer::__createDeviceIndependentResources())
	{
		bRendererDevIndResInit = true;
	}
	else
	{
		DestroyResources();
		throw SystemException(L"��Ⱦ���豸�޹���Դ����ʧ��");
	}

	// ��ʼ������
	if (Window::__init())
	{
		bWindowInit = true;
	}
	else
	{
		DestroyResources();
		throw SystemException(L"��ʼ������ʧ��");
	}

	// �����豸�����Դ
	if (Renderer::__createDeviceResources())
	{
		bRendererDevResInit = true;
	}
	else
	{
		DestroyResources();
		throw SystemException(L"��Ⱦ���豸�����Դ����ʧ��");
	}

	// ��ʼ�� DirectInput
	if (Input::__init())
	{
		bInputInit = true;
	}
	else
	{
		DestroyResources();
		throw SystemException(L"��ʼ�� DirectInput ���ʧ��");
	}

	// ��ʼ��������
	if (Music::__init())
	{
		bMusicInit = true;
	}
	else
	{
		DestroyResources();
		throw SystemException(L"��ʼ�� XAudio2 ���ʧ��");
	}

	// ��ʼ��·��
	if (!Path::__init())
	{
		DestroyResources();
		throw SystemException(L"��Ҫϵͳ·������ʧ��");
	}

	// ��ʼ���ɹ�
	_initialized = true;

	return _initialized;
}

void e2d::Game::start(bool cleanup)
{
	if (!_initialized)
	{
		throw Exception(L"��ʼ��Ϸǰδ���г�ʼ��");
	}

	// ��ʼ������������
	SceneManager::__init();
	// ��ʾ����
	::ShowWindow(Window::getHWnd(), SW_SHOWNORMAL);
	// ˢ�´�������
	::UpdateWindow(Window::getHWnd());
	// ��������Ϣ
	Window::__poll();
	// ��ʼ����ʱ
	Time::__init();

	_ended = false;

	while (!_ended)
	{
		// ��������Ϣ
		Window::__poll();
		// ˢ��ʱ��
		Time::__updateNow();

		// �ж��Ƿ�ﵽ��ˢ��״̬
		if (Time::__isReady())
		{
			Input::__update();			// ��ȡ�û�����
			Timer::__update();			// ���¶�ʱ��
			ActionManager::__update();	// ���¶���������
			SceneManager::__update();	// ���³�������
			Renderer::__render();		// ��Ⱦ��Ϸ����

			Time::__updateLast();		// ˢ��ʱ����Ϣ
		}
		else
		{
			Time::__sleep();			// �����߳�
			GC::__update();				// ˢ���ڴ��
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
	if (!_initialized)
		return;

	// ɾ�����г���
	SceneManager::__uninit();
	// ɾ�����������
	Input::__clearListeners();
	// ɾ����ײ������
	Collision::__clearListeners();
	// ɾ������
	ActionManager::__uninit();
	// �������ֲ�������Դ
	Player::__uninit();
	// ɾ�����ж���
	GC::__clear();
	// ���ͼƬ����
	Image::clearCache();
	// �������������Դ
	Music::__uninit();
	// ��ն�ʱ��
	Timer::__uninit();
	// �ر�����
	Input::__uninit();
	// ������Ⱦ�����Դ
	Renderer::__discardResources();
	// ���ٴ���
	Window::__uninit();

	CoUninitialize();

	_initialized = false;
}

void e2d::Game::destroy()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}
