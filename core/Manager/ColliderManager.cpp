#include "..\e2dmanager.h"
#include "..\e2dnode.h"
#include "..\e2dcollider.h"
#include "..\e2dtool.h"


e2d::ColliderManager * e2d::ColliderManager::_instance = nullptr;

e2d::ColliderManager * e2d::ColliderManager::getInstance()
{
	if (!_instance)
		_instance = new (std::nothrow) ColliderManager;
	return _instance;
}

void e2d::ColliderManager::destroyInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}

e2d::ColliderManager::ColliderManager()
	: _colliders()
{
}

e2d::ColliderManager::~ColliderManager()
{
}

void e2d::ColliderManager::clearAll()
{
	for (auto collder : _colliders)
	{
		collder->release();
	}
	_colliders.clear();
}

void e2d::ColliderManager::__updateCollider(e2d::Collider * pActiveCollider)
{
	// �ж���ײ�����Ƿ��
	if (!Game::getInstance()->getConfig().isCollisionEnabled())
		return;

	Node* pActiveNode = pActiveCollider->_parentNode;
	if (pActiveNode)
	{
		// ��ȡ�ڵ����ڳ���
		Scene* pCurrentScene = pActiveNode->getParentScene();

		// �ж���������ײ��Ľ������
		for (size_t i = 0; i < _colliders.size(); ++i)
		{
			auto pPassiveCollider = _colliders[i];
			// �ж�������ײ���Ƿ���ͬһ������
			if (pActiveCollider == pPassiveCollider)
				continue;

			// ��ȡ����ײ�ڵ�
			Node* pPassiveNode = pPassiveCollider->_parentNode;
			// �ж����ڵ��Ƿ���ͬһ������
			if (pPassiveNode &&
				pPassiveNode->getParentScene() == pCurrentScene)
			{
				// �ж��������Ƿ����໥��ͻ������
				if (Collision::isCollidable(pActiveNode, pPassiveNode))
				{
					// �ж�����ײ�彻�����
					Collider::Relation relation = pActiveCollider->getRelationWith(pPassiveCollider);
					// ���� UNKNOWN �� DISJOIN ���
					if (relation != Collider::Relation::Unknown && relation != Collider::Relation::Disjoin)
					{
						// ������ײ������
						Collision::__update(pActiveNode, pPassiveNode);
					}
				}
			}
		}
	}
}

void e2d::ColliderManager::__add(Collider * pCollider)
{
	if (pCollider)
	{
		pCollider->retain();
		_colliders.push_back(pCollider);
	}
}

void e2d::ColliderManager::__remove(Collider * pCollider)
{
	if (pCollider)
	{
		for (size_t i = 0; i < _colliders.size(); ++i)
		{
			if (_colliders[i] == pCollider)
			{
				GC::safeRelease(pCollider);
				_colliders.erase(_colliders.begin() + i);
				return;
			}
		}
	}
}
