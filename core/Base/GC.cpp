#include "..\e2dbase.h"
#include "..\e2dtool.h"
#include "..\e2dmanager.h"

// GC ���ƣ������Զ����ٵ���
e2d::GC e2d::GC::_instance;

e2d::GC::~GC()
{
	// ɾ�����е���
	Game::destroyInstance();
	Renderer::destroyInstance();
	Input::destroyInstance();
	Window::destroyInstance();
	Player::destroyInstance();
	ActionManager::destroyInstance();
}


// GC �ͷųص�ʵ�ֻ��ƣ�
// Object ���е����ü�����_refCount����һ���̶��Ϸ�ֹ���ڴ�й©
// ����¼�˶���ʹ�õĴ�����������Ϊ 0 ʱ��GC ���Զ��ͷ��������
// ���е� Object ����Ӧ�ڱ�ʹ��ʱ������ Text ��ӵ��˳����У�
// ���� retain ������֤�ö��󲻱�ɾ�������ڲ���ʹ��ʱ���� release ����
void e2d::GC::__update()
{
	if (!_notifyed) return;

	_notifyed = false;
	for (auto iter = _pool.begin(); iter != _pool.end();)
	{
		if ((*iter)->getRefCount() <= 0)
		{
			(*iter)->onDestroy();
			delete (*iter);
			iter = _pool.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void e2d::GC::clear()
{
	for (auto pObj : _pool)
	{
		delete pObj;
	}
	_pool.clear();
}

void e2d::GC::addObject(e2d::Object * pObject)
{
	if (pObject)
	{
		_pool.insert(pObject);
	}
}

e2d::GC * e2d::GC::getInstance()
{
	return &_instance;
}

void e2d::GC::notify()
{
	_notifyed = true;
}

void e2d::GC::flush()
{
	GC::notify();
	GC::__update();
}
