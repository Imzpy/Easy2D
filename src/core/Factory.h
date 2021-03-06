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
#include "Singleton.hpp"
#include "Font.hpp"
#include "Resource.h"
#include "TextRenderer.h"
#include "TextStyle.hpp"

namespace easy2d
{
	class E2D_API Factory
		: public ISingleton<Factory>
	{
		E2D_DECLARE_SINGLETON(Factory);

	public:
		HRESULT Init(bool debug);

		void Destroy();

		HRESULT CreateHwndRenderTarget(
			_Out_ D2DHwndRenderTargetPtr& hwnd_render_target,
			D2D1_RENDER_TARGET_PROPERTIES const& properties,
			D2D1_HWND_RENDER_TARGET_PROPERTIES const& hwnd_rt_properties
		) const;

		HRESULT CreateTextRenderer(
			_Out_ D2DTextRendererPtr& text_renderer,
			D2DRenderTargetPtr const& render_target,
			D2DSolidColorBrushPtr const& brush
		);

		HRESULT CreateBitmapFromFile(
			_Out_ D2DBitmapPtr& bitmap,
			D2DRenderTargetPtr const& rt,
			String const& file_path
		);

		HRESULT CreateBitmapFromResource(
			_Out_ D2DBitmapPtr& bitmap,
			D2DRenderTargetPtr const& rt,
			Resource const& res
		);

		HRESULT CreateRectangleGeometry(
			_Out_ D2DRectangleGeometryPtr& geo,
			Rect const& rect
		) const;

		HRESULT CreateRoundedRectangleGeometry(
			_Out_ D2DRoundedRectangleGeometryPtr& geo,
			Rect const& rect,
			float radius_x,
			float radius_y
		) const;

		HRESULT CreateEllipseGeometry(
			_Out_ D2DEllipseGeometryPtr& geo,
			Point const& center,
			float radius_x,
			float radius_y
		) const;

		HRESULT CreateTransformedGeometry(
			_Out_ D2DTransformedGeometryPtr& transformed,
			Matrix const& matrix,
			D2DGeometryPtr const& geo
		) const;

		HRESULT CreatePathGeometry(
			_Out_ D2DPathGeometryPtr& geometry
		) const;

		HRESULT CreateTextFormat(
			_Out_ D2DTextFormatPtr& text_format,
			Font const& font,
			TextStyle const& text_style
		) const;

		HRESULT CreateTextLayout(
			_Out_ D2DTextLayoutPtr& text_layout,
			_Out_ Size& layout_size,
			String const& text,
			D2DTextFormatPtr const& text_format,
			TextStyle const& text_style
		) const;

		D2DStrokeStylePtr const& GetStrokeStyle(
			StrokeStyle stroke
		) const;

	protected:
		Factory();

		~Factory();

	protected:
		D2DFactoryPtr			factory_;
		D2DImagingFactoryPtr	imaging_factory_;
		D2DWriteFactoryPtr		write_factory_;
		D2DStrokeStylePtr		miter_stroke_style_;
		D2DStrokeStylePtr		bevel_stroke_style_;
		D2DStrokeStylePtr		round_stroke_style_;
	};
}
