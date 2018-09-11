#pragma once
#include "e2dutil.h"

namespace e2d
{


	class Game;
	class Scene;

	// ��������
	class Transition
		: public Ref
	{
		friend class Game;

	public:
		explicit Transition(
			float duration
		);

		virtual ~Transition();

		// �������ɶ����Ƿ����
		bool IsDone();

	protected:
		// ��ʼ���������ɶ���
		virtual void Init(
			Scene * prev,
			Scene * next
		);

		// ���³������ɶ���
		virtual void Update();

		// ��Ⱦ�������ɶ���
		virtual void Draw();

		// ֹͣ�������ɶ���
		virtual void Stop();

		// ���ó������ɶ���
		virtual void Reset() { };

	protected:
		bool	done_;
		float	duration_;
		float	delta_;
		Time	started_;
		Size	window_size_;
		Scene*	out_scene_;
		Scene*	in_scene_;
		ID2D1Layer * out_layer_;
		ID2D1Layer * in_layer_;
		D2D1_LAYER_PARAMETERS out_layer_param_;
		D2D1_LAYER_PARAMETERS in_layer_param_;
	};


	// ���뵭������
	class FadeTransition
		: public Transition
	{
	public:
		explicit FadeTransition(
			float duration		/* ��������ʱ�� */
		);

	protected:
		// ���¶���
		virtual void Update() override;

		virtual void Init(
			Scene * prev,
			Scene * next
		) override;
	};


	// �������
	class EmergeTransition
		: public Transition
	{
	public:
		explicit EmergeTransition(
			float duration		/* ��������ʱ�� */
		);

	protected:
		virtual void Update() override;

		virtual void Init(
			Scene * prev,
			Scene * next
		) override;
	};


	// ��״����
	class BoxTransition
		: public Transition
	{
	public:
		explicit BoxTransition(
			float duration		/* ��������ʱ�� */
		);

	protected:
		virtual void Update() override;

		virtual void Init(
			Scene * prev,
			Scene * next
		) override;
	};


	// λ�ƹ���
	class MoveTransition
		: public Transition
	{
	public:
		explicit MoveTransition(
			float moveDuration,						/* ��������ʱ�� */
			Direction direction = Direction::Left	/* �ƶ����� */
		);

	protected:
		virtual void Update() override;

		virtual void Init(
			Scene * prev,
			Scene * next
		) override;

		virtual void Reset() override;

	protected:
		Direction	direction_;
		Point		pos_delta_;
		Point		start_pos_;
	};


	// ��ת����
	class RotationTransition
		: public Transition
	{
	public:
		explicit MoveTransition(
			float moveDuration,		/* ��������ʱ�� */
			float rotation = 360	/* ��ת���� */
		);

	protected:
		virtual void Update() override;

		virtual void Init(
			Scene * prev,
			Scene * next
		) override;

		virtual void Reset() override;

	protected:
		float	rotation_;
	}

}