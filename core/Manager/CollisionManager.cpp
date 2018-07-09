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
	: _activeNode(nullptr)
	, _passiveNode(nullptr)
{
}

e2d::CollisionManager::~CollisionManager()
{
}

void e2d::CollisionManager::__remove(Node * node)
{
	if (node)
	{
		auto iter = std::find(_collisionNodes.begin(), _collisionNodes.end(), node);
		if (iter != _collisionNodes.end())
		{
			_collisionNodes.erase(iter);
		}
	}
}

void e2d::CollisionManager::updateCollider(Node * node)
{
	if (node)
	{
		if (node->getCollider()->_shape != Collider::Shape::None)
		{
			node->getCollider()->_recreate();
			_collisionNodes.insert(node);
		}
	}
}

void e2d::CollisionManager::update()
{
	// �ж���ײ�����Ƿ��
	if (Game::getInstance()->isPaused() ||
		!Game::getInstance()->getConfig()->isCollisionEnabled() ||
		SceneManager::getInstance()->isTransitioning())
	{
		_collisionNodes.clear();
		return;
	}

	for (auto iter1 = _collisionNodes.begin(); iter1 != _collisionNodes.end(); iter1++)
	{
		auto node1 = (*iter1);
		// �ж���������ײ��Ľ������
		auto iter2 = iter1;
		iter2++;
		for (; iter2 != _collisionNodes.end(); iter2++)
		{
			auto node2 = (*iter2);
			// �ж��������Ƿ����໥��ͻ������
			if (CollisionManager::isCollidable(node1, node2))
			{
				// �ж�����ײ�彻�����
				Collider::Relation relation = node1->getCollider()->getRelationWith(node2->getCollider());
				// ���� UNKNOWN �� DISJOIN ���
				if (relation != Collider::Relation::Unknown && 
					relation != Collider::Relation::Disjoin)
				{
					// ������ײ������
					CollisionManager::__update(node1, node2);
				}
			}
		}
	}
	_collisionNodes.clear();
}

void e2d::CollisionManager::addName(const String & name1, const String & name2)
{
	if (!name1.isEmpty() && !name2.isEmpty())
	{
		_collisionList.insert(HashPair(name1.getHashCode(), name2.getHashCode()));
	}
}

void e2d::CollisionManager::addName(const std::vector<std::pair<String, String> >& names)
{
	for (auto& name : names)
	{
		if (!name.first.isEmpty() && !name.second.isEmpty())
		{
			_collisionList.insert(HashPair(name.first.getHashCode(), name.second.getHashCode()));
		}
	}
}

bool e2d::CollisionManager::isCollidable(Node * node1, Node * node2)
{
	return CollisionManager::isCollidable(node1->getName(), node2->getName());
}

bool e2d::CollisionManager::isCollidable(const String & name1, const String & name2)
{
	UINT hashName1 = name1.getHashCode(), hashName2 = name2.getHashCode();
	HashPair pair1 = HashPair(hashName1, hashName2), pair2 = HashPair(hashName2, hashName1);
	for (auto& pair : _collisionList)
	{
		if (pair == pair1 || pair == pair2)
		{
			return true;
		}
	}
	return false;
}

e2d::Node * e2d::CollisionManager::getActiveNode()
{
	return _activeNode;
}

e2d::Node * e2d::CollisionManager::getPassiveNode()
{
	return _passiveNode;
}

bool e2d::CollisionManager::isCausedBy(const String & name1, const String & name2)
{
	String activeName = _activeNode->getName();
	String passiveName = _passiveNode->getName();
	return (activeName == name1 && passiveName == name2) ||
		(activeName == name2 && passiveName == name1);
}

bool e2d::CollisionManager::isCausedBy(Node * node1, Node * node2)
{
	return (_activeNode == node1 && _passiveNode == node2) ||
		(_activeNode == node2 && _passiveNode == node1);
}

e2d::Node* e2d::CollisionManager::isCausedBy(Node * node)
{
	if (_activeNode == node)
		return _passiveNode;
	if (_passiveNode == node)
		return _activeNode;
	return nullptr;
}

e2d::Node* e2d::CollisionManager::isCausedBy(const String& name)
{
	if (_activeNode->getName() == name)
		return _activeNode;
	if (_passiveNode->getName() == name)
		return _passiveNode;
	return nullptr;
}

void e2d::CollisionManager::__update(Node * active, Node * passive)
{
	if (_listeners.empty() || Game::getInstance()->isPaused())
		return;

	_activeNode = active;
	_passiveNode = passive;

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

	_activeNode = nullptr;
	_passiveNode = nullptr;
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
