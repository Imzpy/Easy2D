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
			UINT message,
			WPARAM w_param,
			LPARAM l_param
		);

		// ��ȡ�¼�����
		KeyEvent::Type GetType() const;

		// ��ȡ������ֵ
		KeyCode GetCode() const;

		// ��ȡ��������
		int GetCount() const;

	protected:
		UINT	message_;
		WPARAM	w_param_;
		LPARAM	l_param_;
	};


	// �����Ϣ
	class MouseEvent
	{
	public:
		// �����Ϣ����
		enum class Type : int
		{
			MoveBy = 0x0200,		// ����ƶ�
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
			UINT message,
			WPARAM w_param,
			LPARAM l_param
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
	};

}