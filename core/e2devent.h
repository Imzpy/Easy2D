#pragma once
#include "e2dcommon.h"

namespace e2d
{


// ������Ϣ
class KeyEvent
{
public:
	// ������Ϣ����
	enum class Type : int
	{
		Down = 0x0100,	// ����
		Up				// ̧��
	};

public:
	explicit KeyEvent(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

	// ��ȡ������ֵ
	KeyCode code() const;

	// ��ȡ��������
	int count() const;

	// ��ȡ�¼�����
	KeyEvent::Type type() const;

	// VK ��ֵת��
	static KeyCode convertKeyCode(
		WPARAM wParam
	);

protected:
	int _count;
	KeyCode _code;
	KeyEvent::Type _type;
};


// �����Ϣ
class MouseEvent
{
public:
	// �����Ϣ����
	enum class Type : int
	{
		Move = 0x0200,		// ����ƶ�
		LeftDown,			// ����������
		LeftUp,				// ������̧��
		LeftDoubleClick,	// ������˫��
		RightDown,			// ����Ҽ�����
		RightUp,			// ����Ҽ�̧��
		RightDoubleClick,	// ����Ҽ�˫��
		MiddleDown,			// ����м�����
		MiddleUp,			// ����м�̧��
		MiddleDoubleClick,	// ����м�˫��
		Wheel				// ��������
	};

public:
	explicit MouseEvent(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam,
		float dpi
	);

	// ��ȡ��������
	float positionX() const;

	// ��ȡ���������
	float positionY() const;

	// ��ȡ�������
	Point position() const;

	// ��ȡ�¼�����
	MouseEvent::Type type() const;

	float wheelDelta() const;

	// �������Ƿ���
	bool isLButtonDown() const;

	// ����Ҽ��Ƿ���
	bool isRButtonDown() const;

	// ����м��Ƿ���
	bool isMButtonDown() const;

	// Shift ���Ƿ���
	bool isShiftDown() const;

	// Ctrl ���Ƿ���
	bool isCtrlDown() const;

protected:
	UINT _message;
	WPARAM _wParam;
	LPARAM _lParam;
	Point _pos;
	MouseEvent::Type _type;
};


// ��ײ�¼�
class Collision
{
public:
	Collision();

	explicit Collision(
		Node* node,
		Collider::Relation relation
	);

	~Collision();

	// ��ȡ������ײ�ڵ�
	Node* node() const;

	// ��ȡ������ϵ
	Collider::Relation relation() const;

protected:
	Node * _node;
	Collider::Relation _relation;
};

}