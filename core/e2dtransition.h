#pragma once
#include "e2dutil.h"

namespace e2d
{


	class Game;
	class Scene;

	// ��������
	class Transition :
		public Ref
	{
		friend class Game;

	public:
		explicit Transition(
			Scene* scene,
			float duration
		);

		virtual ~Transition();

		// �������ɶ����Ƿ����
		bool IsDone();

	protected:
		// ��ʼ���������ɶ���
		virtual bool Init(
			Game * game,
			Scene * prev
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
		Scene*	out_scene_;
		Scene*	in_scene_;
		ID2D1Layer * out_layer_;
		ID2D1Layer * in_layer_;
		D2D1_LAYER_PARAMETERS out_layer_param_;
		D2D1_LAYER_PARAMETERS in_layer_param_;
	};


	// ���뵭������
	class FadeTransition :
		public Transition
	{
	public:
		explicit FadeTransition(
			Scene* scene,		/* �л��ĳ��� */
			float duration		/* ��������ʱ�� */
		);

	protected:
		// ���¶���
		virtual void Update() override;

		virtual bool Init(
			Game * game,
			Scene * prev
		) override;
	};


	// �������
	class EmergeTransition :
		public Transition
	{
	public:
		explicit EmergeTransition(
			Scene* scene,		/* �л��ĳ��� */
			float duration		/* ���ֶ�������ʱ�� */
		);

	protected:
		virtual void Update() override;

		virtual bool Init(
			Game * game,
			Scene * prev
		) override;
	};


	// ��״����
	class BoxTransition :
		public Transition
	{
	public:
		explicit BoxTransition(
			Scene* scene,		/* �л��ĳ��� */
			float duration		/* ��������ʱ�� */
		);

	protected:
		virtual void Update() override;

		virtual bool Init(
			Game * game,
			Scene * prev
		) override;
	};


	// �������
	class MoveTransition :
		public Transition
	{
	public:
		explicit MoveTransition(
			Scene* scene,							/* �л��ĳ��� */
			float moveDuration,						/* �����ƶ���������ʱ�� */
			Direction direction = Direction::Left	/* �����ƶ����� */
		);

	protected:
		virtual void Update() override;

		virtual bool Init(
			Game * game,
			Scene * prev
		) override;

		virtual void Reset() override;

	protected:
		Direction	direction_;
		Point		pos_delta_;
		Point		start_pos_;
	};

}