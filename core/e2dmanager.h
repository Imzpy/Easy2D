#pragma once
#include "e2dmacros.h"
#include "e2dcommon.h"

namespace e2d
{

class Game;
class Input;
class Renderer;
class Node;
class Task;
class Action;
class Player;
class Collider;
class Transition;


// ����������
class SceneManager
{
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

	// ���³�������
	void update();

	// ��Ⱦ��������
	void render();

private:
	SceneManager();

	~SceneManager();

	E2D_DISABLE_COPY(SceneManager);

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

	static ActionManager * _instance;
};


class Listener;

// ��ײ�������
class CollisionManager
{
	friend class Node;

public:
	// ��ȡ��ײ�������ʵ��
	static CollisionManager * getInstance();

	// ����ʵ��
	static void destroyInstance();

	// ��ӿɻ�����ײ���������
	void addName(
		const String& name1,
		const String& name2
	);

	// ��ӿɻ�����ײ���������
	void addName(
		const std::vector<std::pair<String, String> >& names
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

	// ��ȡ��ײ����ʱ��������
	Node * getActiveNode();

	// ��ȡ��ײ����ʱ�ı�����
	Node * getPassiveNode();

	// �жϷ�����ײ�Ľڵ������Ƿ���ͬ
	bool isCausedBy(
		const String& name1,
		const String& name2
	);

	// �ж��������Ƿ�����ײ
	bool isCausedBy(
		Node * node1,
		Node * node2
	);

	// �жϷ�����ײ������һ�������Ƿ���ͬ
	// ����ͬ��������ָ�룬���򷵻ؿ�
	Node * isCausedBy(
		const String& name
	);

	// �ж������Ƿ�����ײ
	// ����ǣ�����������ײ�Ľڵ�ָ�룬���򷵻ؿ�
	Node * isCausedBy(
		Node * node
	);

	// �����ײ����
	Listener * addListener(
		const Function& func,		/* ��������ײʱ��ִ�к��� */
		const String& name = L"",	/* ���������� */
		bool paused = false			/* �Ƿ���ͣ */
	);

	// �����ײ����
	void addListener(
		Listener * listener			/* ������ */
	);

	// �Ƴ�������
	void removeListener(
		Listener * listener			/* ������ */
	);

	// ������ײ����
	void startListener(
		const String& name
	);

	// ֹͣ��ײ����
	void stopListener(
		const String& name
	);

	// �Ƴ���ײ����
	void removeListener(
		const String& name
	);

	// �������м�����
	void startAllListeners();

	// ֹͣ���м�����
	void stopAllListeners();

	// �Ƴ����м�����
	void removeAllListeners();

	// ǿ��������м�����
	void clearAllListeners();

	// ������ײ��
	void updateCollider(
		Node * node
	);

	// ������ײ�������
	void update();

private:
	CollisionManager();

	~CollisionManager();

	E2D_DISABLE_COPY(CollisionManager);

	void __remove(
		Node* node
	);

	// ���¼�����
	void __update(
		Node * active,
		Node * passive
	);

private:
	typedef std::pair<UINT, UINT> HashPair;
	
	e2d::Node * _activeNode;
	e2d::Node * _passiveNode;
	std::set<Node*> _collisionNodes;
	std::set<HashPair> _collisionList;
	std::vector<Listener*> _listeners;

	static CollisionManager * _instance;
};

}