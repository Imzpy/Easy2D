#pragma once
#include "e2dbase.h"


namespace e2d
{

class Node;
class Listener;
class ColliderManager;

// ��ײ�¼�
class Collision
{
	friend class ColliderManager;

public:
	// ��ӿɻ�����ײ���������
	static void addName(
		const String& name1,
		const String& name2
	);

	// ��ӿɻ�����ײ���������
	static void addName(
		const std::vector<std::pair<String, String> >& names
	);

	// �ж����������Ƿ��ǿ���ײ��
	static bool isCollidable(
		Node * node1,
		Node * node2
	);

	// �ж����������Ƿ��ǿ���ײ��
	static bool isCollidable(
		const String& name1,
		const String& name2
	);

	// ��ȡ��ײ����ʱ��������
	static Node * getActiveNode();

	// ��ȡ��ײ����ʱ�ı�����
	static Node * getPassiveNode();

	// �жϷ�����ײ�Ľڵ������Ƿ���ͬ
	static bool isCausedBy(
		const String& name1,
		const String& name2
	);

	// �ж��������Ƿ�����ײ
	static bool isCausedBy(
		Node * node1,
		Node * node2
	);

	// �жϷ�����ײ������һ�������Ƿ���ͬ
	// ����ͬ��������ָ�룬���򷵻ؿ�
	static Node * isCausedBy(
		const String& name
	);

	// �ж������Ƿ�����ײ
	// ����ǣ�����������ײ�Ľڵ�ָ�룬���򷵻ؿ�
	static Node * isCausedBy(
		Node * node
	);

	// �����ײ����
	static Listener * addListener(
		const Function& func,		/* ��������ײʱ��ִ�к��� */
		const String& name = L"",	/* ���������� */
		bool paused = false			/* �Ƿ���ͣ */
	);

	// �����ײ����
	static void addListener(
		Listener * listener			/* ������ */
	);

	// �Ƴ�������
	static void removeListener(
		Listener * listener			/* ������ */
	);

	// ������ײ����
	static void startListener(
		const String& name
	);

	// ֹͣ��ײ����
	static void stopListener(
		const String& name
	);

	// �Ƴ���ײ����
	static void removeListener(
		const String& name
	);

	// �������м�����
	static void startAllListeners();

	// ֹͣ���м�����
	static void stopAllListeners();

	// �Ƴ����м�����
	static void removeAllListeners();

private:
	// ���¼�����
	static void __update(
		Node * active,
		Node * passive
	);
};

}