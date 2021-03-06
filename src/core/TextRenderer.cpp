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

#include "TextRenderer.h"
#include "include-forwards.h"
#include "render.h"

namespace easy2d
{
	class TextRendererImpl
		: public ITextRenderer
	{
	public:
		TextRendererImpl(
			ID2D1Factory* pD2DFactory,
			ID2D1RenderTarget* pRT,
			ID2D1SolidColorBrush* pBrush
		);

		~TextRendererImpl();

		STDMETHOD_(void, SetTextStyle)(
			CONST D2D1_COLOR_F &fillColor,
			BOOL outline,
			CONST D2D1_COLOR_F &outlineColor,
			FLOAT outlineWidth,
			ID2D1StrokeStyle* outlineJoin
			);

		STDMETHOD(DrawGlyphRun)(
			__maybenull void* clientDrawingContext,
			FLOAT baselineOriginX,
			FLOAT baselineOriginY,
			DWRITE_MEASURING_MODE measuringMode,
			__in DWRITE_GLYPH_RUN const* glyphRun,
			__in DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
			IUnknown* clientDrawingEffect
			);

		STDMETHOD(DrawUnderline)(
			__maybenull void* clientDrawingContext,
			FLOAT baselineOriginX,
			FLOAT baselineOriginY,
			__in DWRITE_UNDERLINE const* underline,
			IUnknown* clientDrawingEffect
			);

		STDMETHOD(DrawStrikethrough)(
			__maybenull void* clientDrawingContext,
			FLOAT baselineOriginX,
			FLOAT baselineOriginY,
			__in DWRITE_STRIKETHROUGH const* strikethrough,
			IUnknown* clientDrawingEffect
			);

		STDMETHOD(DrawInlineObject)(
			__maybenull void* clientDrawingContext,
			FLOAT originX,
			FLOAT originY,
			IDWriteInlineObject* inlineObject,
			BOOL IsSideways,
			BOOL IsRightToLeft,
			IUnknown* clientDrawingEffect
			);

		STDMETHOD(IsPixelSnappingDisabled)(
			__maybenull void* clientDrawingContext,
			__out BOOL* isDisabled
			);

		STDMETHOD(GetCurrentTransform)(
			__maybenull void* clientDrawingContext,
			__out DWRITE_MATRIX* transform
			);

		STDMETHOD(GetPixelsPerDip)(
			__maybenull void* clientDrawingContext,
			__out FLOAT* pixelsPerDip
			);

	public:
		unsigned long STDMETHODCALLTYPE AddRef();
		unsigned long STDMETHODCALLTYPE Release();
		HRESULT STDMETHODCALLTYPE QueryInterface(
			IID const& riid,
			void** ppvObject
		);

	private:
		unsigned long			cRefCount_;
		D2D1_COLOR_F			sFillColor_;
		D2D1_COLOR_F			sOutlineColor_;
		FLOAT					fOutlineWidth;
		BOOL					bShowOutline_;
		ID2D1Factory*			pD2DFactory_;
		ID2D1RenderTarget*		pRT_;
		ID2D1SolidColorBrush*	pBrush_;
		ID2D1StrokeStyle*		pCurrStrokeStyle_;
	};

	HRESULT ITextRenderer::Create(
		ITextRenderer** ppTextRenderer,
		ID2D1Factory* pD2DFactory,
		ID2D1RenderTarget* pRT,
		ID2D1SolidColorBrush* pBrush)
	{
		*ppTextRenderer = new (std::nothrow) TextRendererImpl(pD2DFactory, pRT, pBrush);
		if (*ppTextRenderer)
		{
			(*ppTextRenderer)->AddRef();
			return S_OK;
		}
		return E_FAIL;
	}

	TextRendererImpl::TextRendererImpl(ID2D1Factory* pD2DFactory, ID2D1RenderTarget* pRT, ID2D1SolidColorBrush* pBrush)
		: cRefCount_(0)
		, pD2DFactory_(pD2DFactory)
		, pRT_(pRT)
		, pBrush_(pBrush)
		, sFillColor_()
		, sOutlineColor_()
		, fOutlineWidth(1)
		, bShowOutline_(TRUE)
		, pCurrStrokeStyle_(nullptr)
	{
		pD2DFactory->AddRef();
		pRT->AddRef();
		pBrush->AddRef();
	}

	TextRendererImpl::~TextRendererImpl()
	{
		SafeRelease(pD2DFactory_);
		SafeRelease(pRT_);
		SafeRelease(pBrush_);
	}

	STDMETHODIMP_(void) TextRendererImpl::SetTextStyle(
		CONST D2D1_COLOR_F &fillColor,
		BOOL outline,
		CONST D2D1_COLOR_F &outlineColor,
		FLOAT outlineWidth,
		ID2D1StrokeStyle* outlineJoin)
	{
		sFillColor_ = fillColor;
		bShowOutline_ = outline;
		sOutlineColor_ = outlineColor;
		fOutlineWidth = 2 * outlineWidth;
		pCurrStrokeStyle_ = outlineJoin;
	}

	STDMETHODIMP TextRendererImpl::DrawGlyphRun(
		__maybenull void* clientDrawingContext,
		FLOAT baselineOriginX,
		FLOAT baselineOriginY,
		DWRITE_MEASURING_MODE measuringMode,
		__in DWRITE_GLYPH_RUN const* glyphRun,
		__in DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
		IUnknown* clientDrawingEffect)
	{
		E2D_NOT_USED(clientDrawingContext);
		E2D_NOT_USED(measuringMode);
		E2D_NOT_USED(glyphRunDescription);
		E2D_NOT_USED(clientDrawingEffect);

		HRESULT hr = S_OK;

		ID2D1PathGeometry* pPathGeometry = nullptr;
		hr = pD2DFactory_->CreatePathGeometry(
			&pPathGeometry
		);

		ID2D1GeometrySink* pSink = nullptr;
		if (SUCCEEDED(hr))
		{
			hr = pPathGeometry->Open(
				&pSink
			);
		}

		if (SUCCEEDED(hr))
		{
			hr = glyphRun->fontFace->GetGlyphRunOutline(
				glyphRun->fontEmSize,
				glyphRun->glyphIndices,
				glyphRun->glyphAdvances,
				glyphRun->glyphOffsets,
				glyphRun->glyphCount,
				glyphRun->isSideways,
				glyphRun->bidiLevel % 2,
				pSink
			);
		}

		if (SUCCEEDED(hr))
		{
			hr = pSink->Close();
		}

		D2D1::Matrix3x2F const matrix = D2D1::Matrix3x2F(
			1.0f, 0.0f,
			0.0f, 1.0f,
			baselineOriginX, baselineOriginY
		);

		ID2D1TransformedGeometry* pTransformedGeometry = nullptr;
		if (SUCCEEDED(hr))
		{
			hr = pD2DFactory_->CreateTransformedGeometry(
				pPathGeometry,
				&matrix,
				&pTransformedGeometry
			);
		}

		if (SUCCEEDED(hr) && bShowOutline_)
		{
			pBrush_->SetColor(sOutlineColor_);

			pRT_->DrawGeometry(
				pTransformedGeometry,
				pBrush_,
				fOutlineWidth,
				pCurrStrokeStyle_
			);
		}

		if (SUCCEEDED(hr))
		{
			pBrush_->SetColor(sFillColor_);

			pRT_->FillGeometry(
				pTransformedGeometry,
				pBrush_
			);
		}

		SafeRelease(pPathGeometry);
		SafeRelease(pSink);
		SafeRelease(pTransformedGeometry);

		return hr;
	}

	STDMETHODIMP TextRendererImpl::DrawUnderline(
		__maybenull void* clientDrawingContext,
		FLOAT baselineOriginX,
		FLOAT baselineOriginY,
		__in DWRITE_UNDERLINE const* underline,
		IUnknown* clientDrawingEffect)
	{
		E2D_NOT_USED(clientDrawingContext);
		E2D_NOT_USED(clientDrawingEffect);

		HRESULT hr;

		D2D1_RECT_F rect = D2D1::RectF(
			0,
			underline->offset,
			underline->width,
			underline->offset + underline->thickness
		);

		ID2D1RectangleGeometry* pRectangleGeometry = nullptr;
		hr = pD2DFactory_->CreateRectangleGeometry(
			&rect,
			&pRectangleGeometry
		);

		D2D1::Matrix3x2F const matrix = D2D1::Matrix3x2F(
			1.0f, 0.0f,
			0.0f, 1.0f,
			baselineOriginX, baselineOriginY
		);

		ID2D1TransformedGeometry* pTransformedGeometry = nullptr;
		if (SUCCEEDED(hr))
		{
			hr = pD2DFactory_->CreateTransformedGeometry(
				pRectangleGeometry,
				&matrix,
				&pTransformedGeometry
			);
		}

		if (SUCCEEDED(hr) && bShowOutline_)
		{
			pBrush_->SetColor(sOutlineColor_);

			pRT_->DrawGeometry(
				pTransformedGeometry,
				pBrush_,
				fOutlineWidth,
				pCurrStrokeStyle_
			);
		}

		if (SUCCEEDED(hr))
		{
			pBrush_->SetColor(sFillColor_);

			pRT_->FillGeometry(
				pTransformedGeometry,
				pBrush_
			);
		}

		SafeRelease(pRectangleGeometry);
		SafeRelease(pTransformedGeometry);

		return S_OK;
	}

	STDMETHODIMP TextRendererImpl::DrawStrikethrough(
		__maybenull void* clientDrawingContext,
		FLOAT baselineOriginX,
		FLOAT baselineOriginY,
		__in DWRITE_STRIKETHROUGH const* strikethrough,
		IUnknown* clientDrawingEffect)
	{
		E2D_NOT_USED(clientDrawingContext);
		E2D_NOT_USED(clientDrawingEffect);

		HRESULT hr;

		D2D1_RECT_F rect = D2D1::RectF(
			0,
			strikethrough->offset,
			strikethrough->width,
			strikethrough->offset + strikethrough->thickness
		);

		ID2D1RectangleGeometry* pRectangleGeometry = nullptr;
		hr = pD2DFactory_->CreateRectangleGeometry(
			&rect,
			&pRectangleGeometry
		);

		D2D1::Matrix3x2F const matrix = D2D1::Matrix3x2F(
			1.0f, 0.0f,
			0.0f, 1.0f,
			baselineOriginX, baselineOriginY
		);

		ID2D1TransformedGeometry* pTransformedGeometry = nullptr;
		if (SUCCEEDED(hr))
		{
			hr = pD2DFactory_->CreateTransformedGeometry(
				pRectangleGeometry,
				&matrix,
				&pTransformedGeometry
			);
		}

		if (SUCCEEDED(hr) && bShowOutline_)
		{
			pBrush_->SetColor(sOutlineColor_);

			pRT_->DrawGeometry(
				pTransformedGeometry,
				pBrush_,
				fOutlineWidth,
				pCurrStrokeStyle_
			);
		}

		if (SUCCEEDED(hr))
		{
			pBrush_->SetColor(sFillColor_);

			pRT_->FillGeometry(
				pTransformedGeometry,
				pBrush_
			);
		}

		SafeRelease(pRectangleGeometry);
		SafeRelease(pTransformedGeometry);

		return S_OK;
	}

	STDMETHODIMP TextRendererImpl::DrawInlineObject(
		__maybenull void* clientDrawingContext,
		FLOAT originX,
		FLOAT originY,
		IDWriteInlineObject* inlineObject,
		BOOL IsSideways,
		BOOL IsRightToLeft,
		IUnknown* clientDrawingEffect)
	{
		E2D_NOT_USED(clientDrawingContext);
		E2D_NOT_USED(originX);
		E2D_NOT_USED(originY);
		E2D_NOT_USED(inlineObject);
		E2D_NOT_USED(IsSideways);
		E2D_NOT_USED(IsRightToLeft);
		E2D_NOT_USED(clientDrawingEffect);
		return E_NOTIMPL;
	}

	STDMETHODIMP_(unsigned long) TextRendererImpl::AddRef()
	{
		return InterlockedIncrement(&cRefCount_);
	}

	STDMETHODIMP_(unsigned long) TextRendererImpl::Release()
	{
		unsigned long newCount = InterlockedDecrement(&cRefCount_);

		if (newCount == 0)
		{
			delete this;
			return 0;
		}

		return newCount;
	}

	STDMETHODIMP TextRendererImpl::IsPixelSnappingDisabled(
		__maybenull void* clientDrawingContext,
		__out BOOL* isDisabled)
	{
		E2D_NOT_USED(clientDrawingContext);

		*isDisabled = FALSE;
		return S_OK;
	}

	STDMETHODIMP TextRendererImpl::GetCurrentTransform(
		__maybenull void* clientDrawingContext,
		__out DWRITE_MATRIX* transform)
	{
		E2D_NOT_USED(clientDrawingContext);

		pRT_->GetTransform(reinterpret_cast<D2D1_MATRIX_3X2_F*>(transform));
		return S_OK;
	}

	STDMETHODIMP TextRendererImpl::GetPixelsPerDip(
		__maybenull void* clientDrawingContext,
		__out FLOAT* pixelsPerDip)
	{
		E2D_NOT_USED(clientDrawingContext);

		float x, yUnused;

		pRT_->GetDpi(&x, &yUnused);
		*pixelsPerDip = x / 96;

		return S_OK;
	}

	STDMETHODIMP TextRendererImpl::QueryInterface(
		IID const& riid,
		void** ppvObject)
	{
		if (__uuidof(IDWriteTextRenderer) == riid)
		{
			*ppvObject = this;
		}
		else if (__uuidof(IDWritePixelSnapping) == riid)
		{
			*ppvObject = this;
		}
		else if (__uuidof(IUnknown) == riid)
		{
			*ppvObject = this;
		}
		else
		{
			*ppvObject = nullptr;
			return E_FAIL;
		}

		AddRef();

		return S_OK;
	}
}
