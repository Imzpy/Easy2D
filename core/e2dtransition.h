#pragma once
#include "e2dcommon.h"

namespace e2d
{


class Scene;

// ��������
class Transition :
	public Ref
{
public:
	explicit Transition(float duration);

	virtual ~Transition();

	// �������ɶ����Ƿ����
	bool isDone();

	// ��ʼ���������ɶ���
	virtual bool init(
		Scene * prev,
		Scene * next
	);

	// ���³������ɶ���
	virtual void update();

	// ��Ⱦ�������ɶ���
	virtual void render();

	// ֹͣ�������ɶ���
	virtual void stop();

	// ���ó������ɶ���
	virtual void reset() = 0;

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
		float duration	/* ��������ʱ�� */
	);

	// ���¶���
	virtual void update() override;

	virtual bool init(
		Scene * prev,
		Scene * next
	) override;

	virtual void reset() override;
};


// �������
class EmergeTransition :
	public Transition
{
public:
	explicit EmergeTransition(
		float duration	/* ���ֶ�������ʱ�� */
	);

	// ���¶���
	virtual void update() override;

	virtual bool init(
		Scene * prev,
		Scene * next
	) override;

	virtual void reset() override;
};


// ��״����
class BoxTransition :
	public Transition
{
public:
	explicit BoxTransition(
		float duration	/* ��������ʱ�� */
	);

	// ���¶���
	virtual void update() override;

	virtual bool init(
		Scene * prev,
		Scene * next
	) override;

	virtual void reset() override;
};


// �������
class MoveTransition :
	public Transition
{
public:
	explicit MoveTransition(
		float moveDuration,					/* �����ƶ���������ʱ�� */
		Direction direction = Direction::Left	/* �����ƶ����� */
	);

	// ���¶���
	virtual void update() override;

	virtual bool init(
		Scene * prev,
		Scene * next
	) override;

	virtual void reset() override;

protected:
	Direction _direction;
	Vector2 _posDelta;
	Point _startPos;
};

}