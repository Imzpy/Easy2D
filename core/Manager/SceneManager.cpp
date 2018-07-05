#include "..\e2dmanager.h"
#include "..\e2dbase.h"
#include "..\e2dtransition.h"


e2d::SceneManager * e2d::SceneManager::_instance = nullptr;

e2d::SceneManager * e2d::SceneManager::getInstance()
{
	if (!_instance)
		_instance = new (std::nothrow) SceneManager;
	return _instance;
}

void e2d::SceneManager::destroyInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}

e2d::SceneManager::SceneManager()
	: _saveCurrScene(true)
	, _currScene(nullptr)
	, _nextScene(nullptr)
	, _transition(nullptr)
	, _scenes()
{
}

e2d::SceneManager::~SceneManager()
{
}

void e2d::SceneManager::enter(Scene * scene, Transition * transition /* = nullptr */, bool saveCurrentScene /* = true */)
{
	if (!scene)
		return;

	// ������һ������ָ��
	_nextScene = scene;
	_nextScene->retain();
	
	// �����л���������
	if (transition)
	{
		if (_transition)
		{
			_transition->_stop();
			_transition->release();
		}
		_transition = transition;
		transition->retain();
		transition->_init(_currScene, _nextScene);
		transition->_update();
	}

	if (_currScene)
	{
		_saveCurrScene = saveCurrentScene;
	}
}

void e2d::SceneManager::back(Transition * transition /* = nullptr */)
{
	// ջΪ��ʱ�����÷��س�������ʧ��
	WARN_IF(_scenes.size() == 0, "Scene stack is empty!");
	if (_scenes.size() == 0) return;

	// ��ջ��ȡ������ָ�룬��Ϊ��һ����
	_nextScene = _scenes.top();
	_scenes.pop();

	// ������һ����ʱ�������浱ǰ����
	if (_currScene)
	{
		_saveCurrScene = false;
	}

	// �����л���������
	if (transition)
	{
		_transition = transition;
		transition->retain();
		transition->_init(_currScene, _nextScene);
		transition->_update();
	}
}

void e2d::SceneManager::clear()
{
	// ��ճ���ջ
	while (_scenes.size())
	{
		auto temp = _scenes.top();
		GC::release(temp);
		_scenes.pop();
	}
}

e2d::Scene * e2d::SceneManager::getCurrentScene()
{
	return _currScene;
}

std::stack<e2d::Scene*> e2d::SceneManager::getSceneStack()
{
	return _scenes;
}

bool e2d::SceneManager::isTransitioning()
{
	return _transition != nullptr;
}

void e2d::SceneManager::__update()
{
	if (_transition == nullptr)
	{
		// ���³�������
		if (_currScene)
		{
			_currScene->_update();
		}
	}
	else
	{
		// ���³�������
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

	// ��һ����ָ�벻Ϊ��ʱ���л�����
	if (_nextScene)
	{
		if (_currScene)
		{
			// ִ�е�ǰ������ onExit ����
			_currScene->onExit();

			// ��Ҫ���浱ǰ��������������ջ��
			if (_saveCurrScene)
			{
				_scenes.push(_currScene);
			}
			else
			{
				_currScene->release();
			}
		}

		// ִ����һ������ onEnter ����
		_nextScene->onEnter();

		_currScene = _nextScene;		// �л�����
		_nextScene = nullptr;				// ��һ�����ÿ�
	}
}

void e2d::SceneManager::__render()
{
	if (_transition)
	{
		_transition->_render();
	}
	else
	{
		// ���Ƶ�ǰ����
		if (_currScene)
		{
			_currScene->_render();
		}
	}
}
