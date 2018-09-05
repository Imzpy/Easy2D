#pragma once
#include "e2dcommon.h"
#include "e2dmodule.h"

namespace e2d
{


class Node;
class Loop;
class Sequence;
class Spawn;
class ActionManager;


// ��������
class Action :
	public Ref
{
	friend class ActionManager;
	friend class Loop;
	friend class Sequence;
	friend class Spawn;

public:
	Action();

	virtual ~Action();

	// ��ȡ��������״̬
	virtual bool IsRunning();

	// ��������
	virtual void Resume();

	// ��ͣ����
	virtual void Pause();

	// ֹͣ����
	virtual void Stop();

	// ��ȡ��������
	virtual const String& GetName() const;

	// ���ö�������
	virtual void SetName(
		const String& name
	);

	// ��ȡ�����Ŀ���
	virtual Action * Clone() const = 0;

	// ��ȡ�����ĵ�ת
	virtual Action * Reverse() const = 0;

	// ���ö���
	virtual void Reset();

	// ��ȡ�ö�����ִ��Ŀ��
	virtual Node * GetTarget();

	// ��ʼ����
	virtual void StartWithTarget(
		Node* target
	);

	// ��ʼ������
	virtual void Init();

	// ���¶���
	virtual void Update();

	// ���ö���ʱ��
	virtual void ResetTime();

	// ��ȡ��������״̬
	virtual bool IsDone() const;

protected:
	E2D_DISABLE_COPY(Action);

protected:
	String	name_;
	bool	running_;
	bool	done_;
	bool	initialized_;
	Node *	target_;
	Time	started_;
};


// ��������
class FiniteTimeAction :
	public Action
{
public:
	// �����ض�ʱ���ĳ�������
	explicit FiniteTimeAction(
		float duration
	);

	// ���ö���
	virtual void Reset() override;

protected:
	E2D_DISABLE_COPY(FiniteTimeAction);

	// ��ʼ������
	virtual void Init() override;

	// ���¶���
	virtual void Update() override;

	// ���ö���ʱ��
	virtual void ResetTime() override;

protected:
	float duration_;
	float delta_;
};


// ���λ�ƶ���
class MoveBy :
	public FiniteTimeAction
{
public:
	explicit MoveBy(
		float duration,		/* ����ʱ�� */
		Point vector		/* �ƶ����� */
	);

	// ��ȡ�ö����Ŀ�������
	virtual MoveBy * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual MoveBy * Reverse() const override;

protected:
	E2D_DISABLE_COPY(MoveBy);

	// ��ʼ������
	virtual void Init() override;

	// ���¶���
	virtual void Update() override;

protected:
	Point	start_pos_;
	Point	prev_pos_;
	Point	delta_pos_;
};


// λ�ƶ���
class MoveTo :
	public MoveBy
{
public:
	explicit MoveTo(
		float duration,		/* ����ʱ�� */
		Point pos			/* Ŀ������ */
	);

	// ��ȡ�ö����Ŀ�������
	virtual MoveTo * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual MoveTo * Reverse() const override
	{
		WARN("Reverse() not supported in MoveTo");
		return nullptr;
	}

protected:
	E2D_DISABLE_COPY(MoveTo);

	// ��ʼ������
	virtual void Init() override;

protected:
	Point end_pos_;
};


// �����Ծ����
class JumpBy :
	public FiniteTimeAction
{
public:
	explicit JumpBy(
		float duration,			/* ����ʱ�� */
		const Point& vec,		/* ��Ծ���� */
		float height,			/* ��Ծ�߶� */
		int jumps = 1			/* ��Ծ���� */
	);

	// ��ȡ�ö����Ŀ�������
	virtual JumpBy * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual JumpBy * Reverse() const override;

protected:
	E2D_DISABLE_COPY(JumpBy);

	// ��ʼ������
	virtual void Init() override;

	// ���¶���
	virtual void Update() override;

protected:
	Point	start_pos_;
	Point	delta_pos_;
	float	height_;
	int		jumps_;
	Point	prev_pos_;
};


// ��Ծ����
class JumpTo :
	public JumpBy
{
public:
	explicit JumpTo(
		float duration,			/* ����ʱ�� */
		const Point& pos,		/* Ŀ������ */
		float height,			/* ��Ծ�߶� */
		int jumps = 1			/* ��Ծ���� */
	);

	// ��ȡ�ö����Ŀ�������
	virtual JumpTo * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual JumpTo * Reverse() const override
	{
		WARN("Reverse() not supported in JumpTo");
		return nullptr;
	}

protected:
	E2D_DISABLE_COPY(JumpTo);

	// ��ʼ������
	virtual void Init() override;

protected:
	Point end_pos_;
};


// ������Ŷ���
class ScaleBy :
	public FiniteTimeAction
{
public:
	explicit ScaleBy(
		float duration,		/* ����ʱ�� */
		float scale			/* ��Ա仯ֵ */
	);

	explicit ScaleBy(
		float duration,		/* ����ʱ�� */
		float scale_x,		/* ����������Ա仯ֵ */
		float scale_y		/* ����������Ա仯ֵ */
	);

	// ��ȡ�ö����Ŀ�������
	virtual ScaleBy * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual ScaleBy * Reverse() const override;

protected:
	E2D_DISABLE_COPY(ScaleBy);

	// ��ʼ������
	virtual void Init() override;

	// ���¶���
	virtual void Update() override;

protected:
	float	start_scale_x_;
	float	start_scale_y_;
	float	delta_x_;
	float	delta_y_;
};


// ���Ŷ���
class ScaleTo :
	public ScaleBy
{
public:
	explicit ScaleTo(
		float duration,		/* ����ʱ�� */
		float scale			/* Ŀ��ֵ */
	);

	explicit ScaleTo(
		float duration,		/* ����ʱ�� */
		float scale_x,		/* ��������Ŀ��ֵ */
		float scale_y		/* ��������Ŀ��ֵ */
	);

	// ��ȡ�ö����Ŀ�������
	virtual ScaleTo * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual ScaleTo * Reverse() const override
	{
		WARN("Reverse() not supported in ScaleTo");
		return nullptr;
	}

protected:
	E2D_DISABLE_COPY(ScaleTo);

	// ��ʼ������
	virtual void Init() override;

protected:
	float	end_scale_x_;
	float	end_scale_y_;
};


// ͸������Խ��䶯��
class OpacityBy :
	public FiniteTimeAction
{
public:
	explicit OpacityBy(
		float duration,		/* ����ʱ�� */
		float opacity		/* ��Ա仯ֵ */
	);

	// ��ȡ�ö����Ŀ�������
	virtual OpacityBy * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual OpacityBy * Reverse() const override;

protected:
	E2D_DISABLE_COPY(OpacityBy);

	// ��ʼ������
	virtual void Init() override;

	// ���¶���
	virtual void Update() override;

protected:
	float start_val_;
	float delta_val_;
};


// ͸���Ƚ��䶯��
class OpacityTo :
	public OpacityBy
{
public:
	explicit OpacityTo(
		float duration,		/* ����ʱ�� */
		float opacity		/* Ŀ��ֵ */
	);

	// ��ȡ�ö����Ŀ�������
	virtual OpacityTo * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual OpacityTo * Reverse() const override
	{
		WARN("Reverse() not supported in OpacityTo");
		return nullptr;
	}

protected:
	E2D_DISABLE_COPY(OpacityTo);

	// ��ʼ������
	virtual void Init() override;

protected:
	float end_val_;
};


// ���붯��
class FadeIn :
	public OpacityTo
{
public:
	// �������붯��
	explicit FadeIn(
		float duration		/* ����ʱ�� */
	);

protected:
	E2D_DISABLE_COPY(FadeIn);
};


// ��������
class FadeOut :
	public OpacityTo
{
public:
	// ������������
	explicit FadeOut(
		float duration		/* ����ʱ�� */
	);

protected:
	E2D_DISABLE_COPY(FadeOut);
};


// �����ת����
class RotateBy :
	public FiniteTimeAction
{
public:
	explicit RotateBy(
		float duration,		/* ����ʱ�� */
		float rotation		/* ��Ա仯ֵ */
	);

	// ��ȡ�ö����Ŀ�������
	virtual RotateBy * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual RotateBy * Reverse() const override;

protected:
	E2D_DISABLE_COPY(RotateBy);

	// ��ʼ������
	virtual void Init() override;

	// ���¶���
	virtual void Update() override;

protected:
	float start_val_;
	float delta_val_;
};


// ��ת����
class RotateTo :
	public RotateBy
{
public:
	explicit RotateTo(
		float duration,		/* ����ʱ�� */
		float rotation		/* Ŀ��ֵ */
	);

	// ��ȡ�ö����Ŀ�������
	virtual RotateTo * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual RotateTo * Reverse() const override
	{
		WARN("Reverse() not supported in RotateTo");
		return nullptr;
	}

protected:
	E2D_DISABLE_COPY(RotateTo);

	// ��ʼ������
	virtual void Init() override;

protected:
	float end_val_;
};


// ��ʱ����
class Delay :
	public Action
{
public:
	explicit Delay(
		float duration	/* �ӳ�ʱ�����룩 */
	);

	// ��ȡ�ö����Ŀ�������
	virtual Delay * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual Delay * Reverse() const override;

	// ���ö���
	virtual void Reset() override;

protected:
	E2D_DISABLE_COPY(Delay);

	// ��ʼ������
	virtual void Init() override;

	// ���¶���
	virtual void Update() override;

	// ���ö���ʱ��
	virtual void ResetTime() override;

protected:
	float delay_;
	float delta_;
};


// ѭ������
class Loop :
	public Action
{
public:
	explicit Loop(
		Action * action,	/* ִ��ѭ���Ķ��� */
		int times = -1		/* ѭ������ */
	);

	virtual ~Loop();

	// ��ȡ�ö����Ŀ�������
	virtual Loop * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual Loop * Reverse() const override;

	// ���ö���
	virtual void Reset() override;

protected:
	E2D_DISABLE_COPY(Loop);

	// ��ʼ������
	virtual void Init() override;

	// ���¶���
	virtual void Update() override;

	// ���ö���ʱ��
	virtual void ResetTime() override;

protected:
	Action * action_;
	int times_;
	int total_times_;
};


// �ص�����
class Callback :
	public Action
{
public:
	explicit Callback(
		const Function& func /* �������� */
	);

	// ��ȡ�ö����Ŀ�������
	virtual Callback * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual Callback * Reverse() const override;

protected:
	E2D_DISABLE_COPY(Callback);

	// ��ʼ������
	virtual void Init() override;

	// ���¶���
	virtual void Update() override;

protected:
	Function callback_;
};


// ˳����
class Sequence :
	public Action
{
public:
	typedef std::vector<Action*> Actions;

	Sequence();

	explicit Sequence(
		const Actions& actions	/* �����б� */
	);

	virtual ~Sequence();

	// �ڽ�β��Ӷ���
	void Add(
		Action * action
	);

	// �ڽ�β��Ӷ������
	void Add(
		const Actions& actions	/* �����б� */
	);

	// ��ȡ�ö����Ŀ�������
	virtual Sequence * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual Sequence * Reverse() const;

	// ���ö���
	virtual void Reset() override;

protected:
	E2D_DISABLE_COPY(Sequence);

	// ��ʼ������
	virtual void Init() override;

	// ���¶���
	virtual void Update() override;

	// ���ö���ʱ��
	virtual void ResetTime() override;

protected:
	UINT action_index_;
	Actions actions_;
};


// ͬ������
class Spawn :
	public Action
{
public:
	typedef std::vector<Action*> Actions;

	Spawn();

	explicit Spawn(
		const Actions& actions	/* �����б� */
	);

	virtual ~Spawn();

	// �ڽ�β��Ӷ���
	void Add(
		Action * action
	);

	// �ڽ�β��Ӷ������
	void Add(
		const Actions& actions	/* �����б� */
	);

	// ��ȡ�ö����Ŀ�������
	virtual Spawn * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual Spawn * Reverse() const;

	// ���ö���
	virtual void Reset() override;

protected:
	E2D_DISABLE_COPY(Spawn);

	// ��ʼ������
	virtual void Init() override;

	// ���¶���
	virtual void Update() override;

	// ���ö���ʱ��
	virtual void ResetTime() override;

protected:
	Actions actions_;
};


// ֡����
class Animation :
	public Ref
{
public:
	typedef std::vector<Image*> Images;

	Animation();

	explicit Animation(
		const Images& frames	/* �ؼ�֡���� */
	);

	explicit Animation(
		float interval			/* ֡������룩 */
	);

	explicit Animation(
		float interval,			/* ֡������룩 */
		const Images& frames	/* �ؼ�֡���� */
	);

	virtual ~Animation();

	// ��ӹؼ�֡
	void Add(
		Image * frame			/* �ؼ�֡ */
	);

	// ��Ӷ���ؼ�֡
	void Add(
		const Images& frames	/* �ؼ�֡���� */
	);

	// ��ȡ֡���
	float GetInterval() const;

	// ��ȡ�ؼ�֡
	const Images& GetFrames() const;

	// ����ÿһ֡��ʱ����
	void SetInterval(
		float interval		/* ֡������룩 */
	);

	// ��ȡ֡�����Ŀ�������
	Animation * Clone() const;

	// ��ȡ֡�����ĵ�ת
	Animation * Reverse() const;

protected:
	E2D_DISABLE_COPY(Animation);

protected:
	float	interval_;
	Images	frames_;
};


// ���鶯��
class Animate :
	public Action
{
public:
	Animate();

	explicit Animate(
		Animation * animation
	);

	virtual ~Animate();

	// ��ȡ����
	virtual Animation * GetAnimation() const;

	// ���ö���
	virtual void SetAnimation(
		Animation * animation
	);

	// ��ȡ�ö����Ŀ�������
	virtual Animate * Clone() const override;

	// ��ȡ�ö����ĵ�ת
	virtual Animate * Reverse() const override;

	// ���ö���
	virtual void Reset() override;

protected:
	E2D_DISABLE_COPY(Animate);

	// ��ʼ������
	virtual void Init() override;

	// ���¶���
	virtual void Update() override;

	// ���ö���ʱ��
	virtual void ResetTime() override;

protected:
	UINT frame_index_;
	Animation * animation_;
};


}