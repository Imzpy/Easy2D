#pragma once
#include "e2dutil.h"

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
			WPARAM w_param,
			LPARAM l_param
		);

		// ��ȡ������ֵ
		KeyCode GetCode() const;

		// ��ȡ��������
		int GetCount() const;

		// ��ȡ�¼�����
		KeyEvent::Type GetType() const;

		// VK ��ֵת��
		static KeyCode ToKeyCode(
			WPARAM w_param
		);

	protected:
		int				count_;
		KeyCode			code_;
		KeyEvent::Type	type_;
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
			WPARAM w_param,
			LPARAM l_param,
			float dpi
		);

		// ��ȡ��������
		float GetX() const;

		// ��ȡ���������
		float GetY() const;

		// ��ȡ�������
		Point GetPos() const;

		// ��ȡ�¼�����
		MouseEvent::Type GetType() const;

		float GetWheelDelta() const;

		// �������Ƿ���
		bool IsLButtonDown() const;

		// ����Ҽ��Ƿ���
		bool IsRButtonDown() const;

		// ����м��Ƿ���
		bool IsMButtonDown() const;

		// Shift ���Ƿ���
		bool IsShiftDown() const;

		// Ctrl ���Ƿ���
		bool IsCtrlDown() const;

	protected:
		UINT	message_;
		WPARAM	w_param_;
		LPARAM	l_param_;
		Point	pos_;
		MouseEvent::Type type_;
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
		Node* GetNode() const;

		// ��ȡ������ϵ
		Collider::Relation GetRelation() const;

	protected:
		Node * node_;
		Collider::Relation relation_;
	};

}