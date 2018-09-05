#pragma once
#include "e2dnode.h"

namespace e2d
{


	class Button :
		public Node
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

		// ����ê��λ��
		// Ĭ��Ϊ (0, 0), ��Χ [0, 1]
		virtual void SetAnchor(
			float anchor_x,
			float anchor_y
		) override;

		// �ַ������Ϣ
		virtual bool Dispatch(
			const MouseEvent& e,
			bool handled
		) override;

		// �����ڵ�
		virtual void Visit() override;

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

		// ����ص�
		virtual void OnClick();

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


	class ToggleButton :
		public Button
	{
	public:
		ToggleButton();

		explicit ToggleButton(
			Node * normal_on,				/* ��ť��ʱ����ͨ״̬ */
			Node * normal_off,				/* ��ť�ر�ʱ����ͨ״̬ */
			const Function& func = nullptr	/* ��ť�����Ļص����� */
		);

		explicit ToggleButton(
			Node * normal_on,				/* ��ť��ʱ����ͨ״̬ */
			Node * normal_off,				/* ��ť�ر�ʱ����ͨ״̬ */
			Node * selected_on,				/* ��ť��ʱ����갴��״̬ */
			Node * selected_off,			/* ��ť�ر�ʱ����갴��״̬ */
			const Function& func = nullptr	/* ��ť�����Ļص����� */
		);

		explicit ToggleButton(
			Node * normal_on,				/* ��ť��ʱ����ͨ״̬ */
			Node * normal_off,				/* ��ť�ر�ʱ����ͨ״̬ */
			Node * mouseover_on,			/* ��ť��ʱ���������״̬ */
			Node * mouseover_off,			/* ��ť�ر�ʱ���������״̬ */
			Node * selected_on,				/* ��ť��ʱ����갴��״̬ */
			Node * selected_off,			/* ��ť�ر�ʱ����갴��״̬ */
			const Function& func = nullptr	/* ��ť�����Ļص����� */
		);

		explicit ToggleButton(
			Node * normal_on,				/* ��ť��ʱ����ͨ״̬ */
			Node * normal_off,				/* ��ť�ر�ʱ����ͨ״̬ */
			Node * mouseover_on,			/* ��ť��ʱ���������״̬ */
			Node * mouseover_off,			/* ��ť�ر�ʱ���������״̬ */
			Node * selected_on,				/* ��ť��ʱ����갴��״̬ */
			Node * selected_off,			/* ��ť�ر�ʱ����갴��״̬ */
			Node * disabled_on,				/* ��ť��ʱ������״̬ */
			Node * disabled_off,			/* ��ť�ر�ʱ������״̬ */
			const Function& func = nullptr	/* ��ť�����Ļص����� */
		);

		// ��ȡ����״̬
		bool IsChecked() const;

		// ���ÿ��ذ�ť��״̬
		void SetChecked(
			bool checked
		);

		// ���ð�ť��״̬����ʾ�İ�ť
		virtual void SetNormal(
			Node * normal
		) override;

		// ���ð�ť��״̬�£�������밴ťʱ��ʾ�İ�ť
		virtual void SetMouseOver(
			Node * mouseover
		) override;

		// ���ð�ť��״̬�£���갴�°�ťʱ��ʾ�İ�ť
		virtual void SetSelected(
			Node * selected
		) override;

		// ���ð�ť��״̬�£�������ʱ��ʾ�İ�ť
		virtual void SetDisabled(
			Node * disabled
		) override;

		// ���ð�ť�ر�״̬����ʾ�İ�ť
		void SetNormalOff(
			Node * normal
		);

		// ���ð�ť�ر�״̬�£�������밴ťʱ��ʾ�İ�ť
		void SetMouseOverOff(
			Node * mouseover
		);

		// ���ð�ť�ر�״̬�£���갴�°�ťʱ��ʾ�İ�ť
		void SetSelectedOff(
			Node * selected
		);

		// ���ð�ť�ر�״̬�£���ť������ʱ��ʾ�İ�ť
		void SetDisabledOff(
			Node * disabled
		);

		// ����ê��λ��
		// Ĭ��Ϊ (0, 0), ��Χ [0, 1]
		virtual void SetAnchor(
			float anchor_x,
			float anchor_y
		) override;

	protected:
		E2D_DISABLE_COPY(ToggleButton);

		// ˢ�°�ť����
		virtual void UpdateStatus();

		// ִ�а�ť��������
		virtual void OnClick() override;

	protected:
		Node * normal_on_;
		Node*	mouseover_on_;
		Node*	selected_on_;
		Node*	disabled_on_;
		Node*	normal_off_;
		Node*	mouseover_off_;
		Node*	selected_off_;
		Node*	disabled_off_;
		bool	checked_;
	};


	// �˵�
	class Menu :
		public Node
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
