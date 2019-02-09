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
#include "include-forwards.h"
#include "time.h"
#include "noncopyable.hpp"
#include "IntrusiveList.hpp"

namespace easy2d
{
	using ActionCallback = std::function<void()>;

	class ActionManager;

	class E2D_API Action
		: public virtual Object
		, protected IntrusiveListItem<ActionPtr>
	{
		friend class ActionManager;
		friend class Loop;
		friend class Sequence;
		friend class Spawn;
		friend class IntrusiveList<ActionPtr>;

	public:
		Action() : running_(false), done_(false), initialized_(false) {}

		virtual ~Action() {}

		// ��������
		void Resume() { running_ = true; }

		// ��ͣ����
		void Pause() { running_ = false; }

		// ֹͣ����
		void Stop() { if (!done_) { done_ = true; if (cb_) cb_(); } }

		// ��ȡ�����Ŀ���
		virtual ActionPtr Clone() const = 0;

		// ��ȡ�����ĵ�ת
		virtual ActionPtr Reverse() const = 0;

		// ���ö�������ʱ�Ļص�����
		void SetCallback(ActionCallback const& cb) { cb_ = cb; }

		// ���ö�����ʱ
		void SetDelay(Duration delay) { delay_ = delay; }

		// ���ö���
		virtual void Reset()
		{
			initialized_ = false;
			done_ = false;
			elapsed_ = 0;
		}

		virtual bool IsDone() const { return done_; }

		virtual bool IsRunning() { return running_; }

	protected:
		void Start()
		{
			running_ = true;
			this->Reset();
		}

		void Step(Node* target, Duration dt)
		{
			if (!initialized_)
			{
				Init(target);
				initialized_ = true;
			}

			if (elapsed_ < delay_)
				elapsed_ += dt;

			if (elapsed_ >= delay_)
				Update(target, dt);
		}

		virtual void Init(Node* target) = 0;

		virtual void Update(Node* target, Duration dt) = 0;

	protected:
		bool running_;
		bool done_;
		bool initialized_;
		Duration delay_;
		Duration elapsed_;
		ActionCallback cb_;
	};
}
