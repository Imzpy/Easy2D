#pragma once
#include "e2dobject.h"

namespace e2d
{


	class Button
		: public Node
	{
	public:
		Button();

		explicit Button(
			Node * normal,					/* ��ͨ״̬ */
			const Function& func = nullptr	/* ��ť�����Ļص����� */
		);

		explicit Button(
			Node * normal,					/* ��ͨ״̬ */
			Node * selected,				/* ��갴��״̬ */
			const Function& func = nullptr	/* ��ť�����Ļص����� */
		);

		explicit Button(
			Node * normal,					/* ��ͨ״̬ */
			Node * mouseover,				/* �������״̬ */
			Node * selected,				/* ��갴��״̬ */
			const Function& func = nullptr	/* ��ť�����Ļص����� */
		);

		explicit Button(
			Node * normal,					/* ��ͨ״̬ */
			Node * mouseover,				/* �������״̬ */
			Node * selected,				/* �������״̬ */
			Node * disabled,				/* ��ť����״̬ */
			const Function& func = nullptr	/* ��ť�����Ļص����� */
		);

		// ��ȡ��ť״̬�����û��ǽ���
		bool IsEnable() const;

		// ���ð�ť���û����
		void SetEnabled(
			bool enabled
		);

		// ����һ���������ʾ�İ�ť
		virtual void SetNormal(
			Node * normal
		);

		// ����������밴ťʱ��ʾ�İ�ť
		virtual void SetMouseOver(
			Node * mouseover
		);

		// ������갴�°�ťʱ��ʾ�İ�ť
		virtual void SetSelected(
			Node * selected
		);

		// ���ð�ť������ʱ��ʾ�İ�ť
		virtual void SetDisabled(
			Node * disabled
		);

		// ���ð�ť�����Ļص�����
		void SetCallbackOnClick(
			const Function& func
		);

		// ����֧��λ��
		// Ĭ��Ϊ (0, 0), ��Χ [0, 1]
		virtual void SetPivot(
			float pivot_x,
			float pivot_y
		) override;

	protected:
		E2D_DISABLE_COPY(Button);

		// ��ť״̬ö��
		enum class Status { Normal, Mouseover, Selected };

		// ���ð�ť״̬
		virtual void SetStatus(
			Status status
		);

		// ˢ�°�ť��ʾ
		virtual void UpdateVisible();

		// �ַ������Ϣ
		virtual bool Dispatch(
			const MouseEvent& e,
			bool handled
		) override;

		// �����ڵ�
		virtual void Visit() override;

	protected:
		Node * normal_;
		Node *		mouseover_;
		Node *		selected_;
		Node *		disabled_;
		bool		enabled_;
		bool		is_selected_;
		Status		status_;
		Function	callback_;
	};


	// �˵�
	class Menu
		: public Node
	{
	public:
		Menu();

		explicit Menu(
			const std::vector<Button*>& buttons	/* ��ť���� */
		);

		// ��ȡ�˵��Ƿ����
		bool IsEnable() const;

		// ��ȡ�˵��еİ�ť����
		size_t GetButtonCount() const;

		// ���ò˵����û����
		void SetEnabled(
			bool enabled
		);

		// ��Ӱ�ť
		void AddButton(
			Button * button
		);

		// �Ƴ���ť
		bool RemoveButton(
			Button * button
		);

		// ��ȡ���а�ť
		const std::vector<Button*>& GetAllButtons() const;

	protected:
		E2D_DISABLE_COPY(Menu);

	protected:
		bool enabled_;
		std::vector<Button*> buttons_;
	};


}
