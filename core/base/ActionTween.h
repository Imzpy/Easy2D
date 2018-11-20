// Copyright (c) 2016-2018 Easy2D - Nomango
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once
#include "ActionInterval.h"

namespace easy2d
{
	enum class TweenType
	{
		EaseExponentialIn,
		EaseExponentialOut,
		EaseExponentialInOut,
		EaseSineIn,
		EaseSineOut,
		EaseSineInOut
	};

	// ���䶯��
	class TweenAction
		: public IntervalAction
	{
	public:
		using EaseFunc = std::function<float(float)>;

		TweenAction();

		explicit TweenAction(
			spIntervalAction const& action,	/* ���� */
			TweenType type					/* ���䷽ʽ */
		);

		explicit TweenAction(
			spIntervalAction const& action,	/* ���� */
			EaseFunc const& func			/* �Զ������ */
		);

		// ��ȡ�ö����Ŀ�������
		virtual spAction Clone() const override;

		// ��ȡ�ö����ĵ�ת
		virtual spAction Reverse() const override;

	protected:
		virtual void Init(Node* target) override;

		virtual void Update(Node* target, float percent) override;

	protected:
		EaseFunc			ease_func_;
		TweenType			type_;
		spIntervalAction	inner_;
	};


	enum class EaseType
	{
		EaseIn,		// �������
		EaseOut,	// �ɿ����
		EaseInOut	// �������, ���ɿ����
	};

	// ���䶯��
	class EaseAction
		: public TweenAction
	{
	public:
		using EaseFunc = std::function<float(float, float)>;

		explicit EaseAction(
			spIntervalAction const& action,	/* ���� */
			EaseType type,					/* ���䷽ʽ */
			float rate						/* ���� */
		);

		explicit EaseAction(
			spIntervalAction const& action,	/* ���� */
			EaseFunc const& func,			/* �Զ������ */
			float rate						/* ���� */
		);

		// ��ȡ�ö����Ŀ�������
		virtual spAction Clone() const override;

		// ��ȡ�ö����ĵ�ת
		virtual spAction Reverse() const override;

	protected:
		virtual void Update(Node* target, float percent) override;

	protected:
		float				rate_;
		EaseFunc			ease_func_;
		spIntervalAction	inner_;
	};
}
