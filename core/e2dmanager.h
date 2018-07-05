#pragma once
#include "e2dmacros.h"
#include "e2dcommon.h"

namespace e2d
{

class Game;
class Input;
class Renderer;
class Node;
class Timer;
class Action;
class Player;
class Collider;
class Transition;


// ����������
class SceneManager
{
	friend class Game;
	friend class Renderer;

public:
	// ��ȡ����������ʵ��
	static SceneManager * getInstance();

	// ����ʵ��
	static void destroyInstance();

	// �л�����
	void enter(
		Scene * scene,						/* ��һ��������ָ�� */
		Transition * transition = nullptr,	/* �����л����� */
		bool saveCurrentScene = true		/* �Ƿ񱣴浱ǰ���� */
	);

	// ������һ����
	void back(
		Transition * transition = nullptr	/* �����л����� */
	);

	// ��ձ�������г���
	void clear();

	// ��ȡ��ǰ����
	Scene * getCurrentScene();

	// ��ȡ����ջ
	std::stack<Scene*> getSceneStack();

	// �Ƿ����ڽ���ת������
	bool isTransitioning();

private:
	SceneManager();

	~SceneManager();

	E2D_DISABLE_COPY(SceneManager);

	// ���³�������
	void __update();

	// ��Ⱦ��������
	void __render();

private:
	bool				_saveCurrScene;
	Scene *				_currScene;
	Scene *				_nextScene;
	Transition *		_transition;
	std::stack<Scene*>	_scenes;

	static SceneManager * _instance;
};


// ����������
class ActionManager
{
	friend class Game;
	friend class Action;

public:
	// ��ȡ����������ʵ��
	static ActionManager * getInstance();

	// ����ʵ��
	static void destroyInstance();

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

	// �������ж���
	void resumeAll();

	// ��ͣ���ж���
	void pauseAll();

	// ֹͣ���ж���
	void stopAll();

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

	// ��հ��ڽڵ��ϵ����ж���
	void clearAllBindedWith(
		Node * target
	);

private:
	ActionManager();

	~ActionManager();

	E2D_DISABLE_COPY(ActionManager);

	// ���¶���״̬
	void __update();

	// ��Ӷ���
	void __add(
		Action * action
	);

	// ɾ������
	void __remove(
		Action * action
	);

	// �������ж���״̬
	void __resetAll();

private:
	std::vector<Action*> _actions;
	std::vector<Action*> _runningActions;

	static ActionManager * _instance;
};


// ��ײ�������
class ColliderManager
{
	friend class Node;
	friend class Collider;

public:
	// ��ȡ��ײ�������ʵ��
	static ColliderManager * getInstance();

	// ����ʵ��
	static void destroyInstance();

private:
	ColliderManager();

	~ColliderManager();

	E2D_DISABLE_COPY(ColliderManager);

	// ������ײ��
	void __updateCollider(
		Collider * pActiveCollider
	);

	// �����ײ��
	void __add(
		Collider * pCollider
	);

	// ɾ���Ѱ󶨵���ײ��
	void __remove(
		Collider * pCollider
	);

private:
	std::vector<Collider*> _colliders;

	static ColliderManager * _instance;
};

}