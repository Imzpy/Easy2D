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
#include "base.hpp"
#include "Singleton.hpp"

namespace easy2d
{
	namespace devices
	{
		class InputDevice
			: protected Noncopyable
		{
			E2D_DECLARE_SINGLETON(InputDevice);

		public:
			HRESULT Init(HWND hwnd, float scale_x, float scale_y, bool debug);

			// 检测键盘某按键是否正被按下
			bool IsDown(
				KeyCode code
			);

			// 检测鼠标按键是否正被按下
			bool IsDown(
				MouseCode code
			);

			// 检测键盘某按键是否点击
			bool WasPressed(
				KeyCode code
			);

			// 检测鼠标按键是否点击
			bool WasPressed(
				MouseCode code
			);

			// 获得鼠标X轴坐标值
			float GetMouseX();

			// 获得鼠标Y轴坐标值
			float GetMouseY();

			// 获得鼠标坐标值
			Point GetMousePos();

			void Update();

		protected:
			InputDevice();

			~InputDevice();

		protected:
			HWND	hwnd_;
			float	scale_x_;
			float	scale_y_;
			BYTE	keys_[256];
			BYTE	keys_cache_[256];
			Point	mouse_pos_;
		};

		E2D_DECLARE_SINGLETON_TYPE(InputDevice, Input);
	}
}
