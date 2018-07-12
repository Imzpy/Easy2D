#include "..\e2dmanager.h"
#include "..\e2dnode.h"
#include "..\e2dtool.h"


e2d::CollisionManager * e2d::CollisionManager::_instance = nullptr;

e2d::CollisionManager * e2d::CollisionManager::getInstance()
{
	if (!_instance)
		_instance = new (std::nothrow) CollisionManager;
	return _instance;
}

void e2d::CollisionManager::destroyInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}

e2d::CollisionManager::CollisionManager()
{
}

e2d::CollisionManager::~CollisionManager()
{
}

void e2d::CollisionManager::__addCollider(Collider * collider)
{
	_colliders.push_back(collider);
}

void e2d::CollisionManager::__removeCollider(Collider * collider)
{
	auto iter = std::find(_colliders.begin(), _colliders.end(), collider);
	if (iter != _colliders.end())
	{
		_colliders.erase(iter);
	}
}

void e2d::CollisionManager::__updateCollider(Collider* collider)
{
	if (Game::getInstance()->isPaused() ||
		!Game::getInstance()->getConfig()->isCollisionEnabled() ||
		SceneManager::getInstance()->isTransitioning() ||
		!collider->isCollisionNotify())
		return;

	for (size_t i = 0; i < _colliders.size(); i++)
	{
		// �ж���������ײ��Ľ������
		auto active = collider->getNode();
		auto passive = _colliders[i]->getNode();
		// �ж��������Ƿ����໥��ͻ������
		if (active == passive ||
			active->getParentScene() != passive->getParentScene() ||
			!CollisionManager::isCollidable(active, passive))
		{
			continue;
		}

		// �ж�����ײ�彻�����
		Collider::Relation relation = active->getCollider()->getRelationWith(passive->getCollider());
		// ���� UNKNOWN �� DISJOIN ���
		if (relation != Collider::Relation::Unknown &&
			relation != Collider::Relation::Disjoin)
		{
			_collision = Collision(active, passive, relation);
			active->onCollision(_collision);
			// ������ײ������
			CollisionManager::__updateListeners();
		}
	}
	_collision = Collision();
}

void e2d::CollisionManager::addName(const String & name1, const String & name2)
{
	if (!name1.isEmpty() && !name2.isEmpty())
	{
		_collisionList.insert(std::make_pair(name1.getHashCode(), name2.getHashCode()));
	}
}

void e2d::CollisionManager::addName(const std::vector<std::pair<String, String> >& names)
{
	for (auto& name : names)
	{
		if (!name.first.isEmpty() && !name.second.isEmpty())
		{
			_collisionList.insert(std::make_pair(name.first.getHashCode(), name.second.getHashCode()));
		}
	}
}

bool e2d::CollisionManager::isCollidable(Node * node1, Node * node2)
{
	return CollisionManager::isCollidable(node1->getName(), node2->getName());
}

bool e2d::CollisionManager::isCollidable(const String & name1, const String & name2)
{
	UINT hashName1 = name1.getHashCode(), 
		hashName2 = name2.getHashCode();
	auto pair1 = std::make_pair(hashName1, hashName2), 
		pair2 = std::make_pair(hashName2, hashName1);
	for (auto& pair : _collisionList)
	{
		if (pair == pair1 || pair == pair2)
		{
			return true;
		}
	}
	return false;
}

e2d::Collision e2d::CollisionManager::getCollision() const
{
	return _collision;
}

void e2d::CollisionManager::__updateListeners()
{
	if (_listeners.empty() || Game::getInstance()->isPaused())
		return;

	for (size_t i = 0; i < _listeners.size(); ++i)
	{
		auto listener = _listeners[i];
		// �����ֹͣ�ļ�����
		if (listener->_stopped)
		{
			GC::safeRelease(listener);
			_listeners.erase(_listeners.begin() + i);
		}
		else
		{
			// ���¼�����
			listener->_update();
			++i;
		}
	}
}

e2d::Listener * e2d::CollisionManager::addListener(const Function& func, const String& name, bool paused)
{
	auto listener = new (e2d::autorelease) Listener(func, name, paused);
	GC::retain(listener);
	_listeners.push_back(listener);
	return listener;
}

void e2d::CollisionManager::addListener(Listener * listener)
{
	if (listener)
	{
		auto iter = std::find(_listeners.begin(), _listeners.end(), listener);
		if (iter == _listeners.end())
		{
			GC::retain(listener);
			_listeners.push_back(listener);
		}
	}
}

void e2d::CollisionManager::removeListener(Listener * listener)
{
	if (listener)
	{
		auto iter = std::find(_listeners.begin(), _listeners.end(), listener);
		if (iter != _listeners.end())
		{
			GC::safeRelease(listener);
			_listeners.erase(iter);
		}
	}
}

void e2d::CollisionManager::stopListener(const String& name)
{
	if (_listeners.empty() || name.isEmpty())
		return;

	for (auto listener : _listeners)
	{
		if (listener->_name == name)
		{
			listener->stop();
		}
	}
}

void e2d::CollisionManager::startListener(const String& name)
{
	if (_listeners.empty() || name.isEmpty())
		return;

	for (auto listener : _listeners)
	{
		if (listener->_name == name)
		{
			listener->start();
		}
	}
}

void e2d::CollisionManager::removeListener(const String& name)
{
	if (_listeners.empty() || name.isEmpty())
		return;

	for (auto listener : _listeners)
	{
		if (listener->_name == name)
		{
			listener->_stopped = true;
		}
	}
}

void e2d::CollisionManager::stopAllListeners()
{
	for (auto listener : _listeners)
	{
		listener->stop();
	}
}

void e2d::CollisionManager::startAllListeners()
{
	for (auto listener : _listeners)
	{
		listener->start();
	}
}

void e2d::CollisionManager::removeAllListeners()
{
	for (auto listener : _listeners)
	{
		listener->_stopped = true;
	}
}

void e2d::CollisionManager::clearAllListeners()
{
	for (auto listener : _listeners)
	{
		GC::release(listener);
	}
	_listeners.clear();
}
