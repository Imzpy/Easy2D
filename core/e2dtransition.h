#pragma once
#include "e2dcommon.h"

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
	bool done();

protected:
	// ��ʼ���������ɶ���
	virtual bool _init(
		Game * game,
		Scene * prev
	);

	// ���³������ɶ���
	virtual void _update();

	// ��Ⱦ�������ɶ���
	virtual void _render(
		Game * game
	);

	// ֹͣ�������ɶ���
	virtual void _stop();

	// ���ó������ɶ���
	virtual void _reset() { };

protected:
	bool	_end;
	float	_duration;
	float	_delta;
	Time	_started;
	Size	_windowSize;
	Scene*	_outScene;
	Scene*	_inScene;
	ID2D1Layer * _outLayer;
	ID2D1Layer * _inLayer;
	D2D1_LAYER_PARAMETERS _outLayerParam;
	D2D1_LAYER_PARAMETERS _inLayerParam;
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
	virtual void _update() override;

	virtual bool _init(
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
	virtual void _update() override;

	virtual bool _init(
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
	virtual void _update() override;

	virtual bool _init(
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
	virtual void _update() override;

	virtual bool _init(
		Game * game,
		Scene * prev
	) override;

	virtual void _reset() override;

protected:
	Direction _direction;
	Vector2 _posDelta;
	Point _startPos;
};

}