#pragma once
#include "e2dmacros.h"
#include "e2dutil.h"

namespace e2d
{


class Node;


// ��ײ�������
class CollisionManager
{
	friend class Node;
	friend class Collider;

public:
	// ��ȡ��ײ�������ʵ��
	static CollisionManager * GetInstance();

	// �򿪻�ر���ײ����
	// Ĭ�ϣ��ر�
	void SetCollisionEnabled(
		bool enabled
	);

	// ��ӿɻ�����ײ���������
	void AddName(
		const String& name1,
		const String& name2
	);

	// ��ӿɻ�����ײ���������
	void AddName(
		const std::vector<std::pair<String, String>>& names
	);

	// �ж����������Ƿ��ǿ���ײ��
	bool IsCollidable(
		Node * node1,
		Node * node2
	);

	// �ж����������Ƿ��ǿ���ײ��
	bool IsCollidable(
		const String& name1,
		const String& name2
	);

private:
	CollisionManager();

	~CollisionManager();

	E2D_DISABLE_COPY(CollisionManager);

	// �����ײ��
	void AddCollider(
		Collider* collider
	);

	// �Ƴ���ײ��
	void RemoveCollider(
		Collider* collider
	);

	// ������ײ��
	void UpdateCollider(
		Collider* collider
	);

private:
	bool collision_enabled_;
	std::vector<Collider*> colliders_;
	std::set<std::pair<size_t, size_t>> collision_list_;
};

}