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
	static ActionManager * getInstance();

	// ��ȡ����������ͬ�Ķ���
	std::vector<Action *> get(
		const String& name
	);

	// ��ȡ���ж���
	const std::vector<Action*>& getAll();

	// ִ�ж���
	void start(
		Action * action,
		Node * target,
		bool paused
	);

	// ����������ͬ�����ж���
	void resume(
		const String& name
	);

	// ��ͣ������ͬ�����ж���
	void pause(
		const String& name
	);

	// ֹͣ������ͬ�����ж���
	void stop(
		const String& name
	);

	// �������ڽڵ��ϵ����ж���
	void resumeAllBindedWith(
		Node * target
	);

	// ��ͣ���ڽڵ��ϵ����ж���
	void pauseAllBindedWith(
		Node * target
	);

	// ֹͣ���ڽڵ��ϵ����ж���
	void stopAllBindedWith(
		Node * target
	);

	// ǿ��������ڽڵ��ϵ����ж���
	void clearAllBindedWith(
		Node * target
	);

	// ǿ��������ж���
	void clearAll();

	// ���¶���������״̬
	void update();

	// ˢ�����ж�����ʱ
	void updateTime();

private:
	ActionManager();

	~ActionManager();

	E2D_DISABLE_COPY(ActionManager);

	// ��Ӷ���
	void __add(
		Action * action
	);

	// ɾ������
	void __remove(
		Action * action
	);

private:
	std::vector<Action*> _actions;
	std::vector<Action*> _runningActions;
};


// ��ײ�������
class CollisionManager
{
	friend class Node;
	friend class Collider;

public:
	// ��ȡ��ײ�������ʵ��
	static CollisionManager * getInstance();

	// �򿪻�ر���ײ����
	// Ĭ�ϣ��ر�
	void setCollisionEnabled(
		bool enabled
	);

	// ��ӿɻ�����ײ���������
	void addName(
		const String& name1,
		const String& name2
	);

	// ��ӿɻ�����ײ���������
	void addName(
		const std::vector<std::pair<String, String>>& names
	);

	// �ж����������Ƿ��ǿ���ײ��
	bool isCollidable(
		Node * node1,
		Node * node2
	);

	// �ж����������Ƿ��ǿ���ײ��
	bool isCollidable(
		const String& name1,
		const String& name2
	);

private:
	CollisionManager();

	~CollisionManager();

	E2D_DISABLE_COPY(CollisionManager);

	// �����ײ��
	void __addCollider(
		Collider* collider
	);

	// �Ƴ���ײ��
	void __removeCollider(
		Collider* collider
	);

	// ������ײ��
	void __updateCollider(
		Collider* collider
	);

private:
	bool _collisionEnabled;
	std::vector<Collider*> _colliders;
	std::set<std::pair<size_t, size_t>> _collisionList;
};

}