#pragma once
#include "e2dmacros.h"
#include "e2dcommon.h"

namespace e2d
{


class Node;
class Action;

// ����������
class ActionManager
{
	friend class Action;

public:
	// ��ȡ����������ʵ��
	static ActionManager * GetInstance();

	// ��ȡ����������ͬ�Ķ���
	std::vector<Action *> Get(
		const String& name
	);

	// ��ȡ���ж���
	const std::vector<Action*>& GetAll();

	// ִ�ж���
	void Start(
		Action * action,
		Node * target,
		bool paused
	);

	// ����������ͬ�����ж���
	void Resume(
		const String& name
	);

	// ��ͣ������ͬ�����ж���
	void Pause(
		const String& name
	);

	// ֹͣ������ͬ�����ж���
	void Stop(
		const String& name
	);

	// �������ڽڵ��ϵ����ж���
	void ResumeAllBindedWith(
		Node * target
	);

	// ��ͣ���ڽڵ��ϵ����ж���
	void PauseAllBindedWith(
		Node * target
	);

	// ֹͣ���ڽڵ��ϵ����ж���
	void StopAllBindedWith(
		Node * target
	);

	// ǿ��������ڽڵ��ϵ����ж���
	void ClearAllBindedWith(
		Node * target
	);

	// ǿ��������ж���
	void ClearAll();

	// ���¶���������״̬
	void Update();

	// ˢ�����ж�����ʱ
	void UpdateTime();

private:
	ActionManager();

	~ActionManager();

	E2D_DISABLE_COPY(ActionManager);

	// ��Ӷ���
	void Add(
		Action * action
	);

	// ɾ������
	void Remove(
		Action * action
	);

private:
	std::vector<Action*> actions_;
	std::vector<Action*> running_actions_;
};


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