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
#include "IntrusiveList.hpp"
#include "Event.hpp"

namespace easy2d
{
	using EventCallback = std::function<void(Event const&)>;

	class EventDispatcher;

	class E2D_API EventListener
		: public virtual Object
		, protected IntrusiveListItem<EventListenerPtr>
	{
		friend class EventDispatcher;
		friend class IntrusiveList<EventListenerPtr>;

	public:
		EventListener(
			EventType type,
			EventCallback const& callback,
			String const& name = L""
		);

		virtual ~EventListener();

		void Start();

		void Stop();

		bool IsRunning() const;

	protected:
		bool			running_;
		EventType		type_;
		EventCallback	callback_;
	};
}
