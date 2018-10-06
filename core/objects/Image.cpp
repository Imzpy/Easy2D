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

#include "..\e2dobject.h"
#include "..\e2dmodule.h"
#include "..\e2dtool.h"

std::map<size_t, ID2D1Bitmap*> e2d::Image::bitmap_cache_;

e2d::Image::Image()
	: bitmap_(nullptr)
	, crop_rect_()
{
}

e2d::Image::Image(const Resource& res)
	: bitmap_(nullptr)
	, crop_rect_()
{
	this->Load(res);
}

e2d::Image::Image(const Resource& res, const Rect& crop_rect)
	: bitmap_(nullptr)
	, crop_rect_()
{
	this->Load(res);
	this->Crop(crop_rect);
}

e2d::Image::Image(const String & file_name)
	: bitmap_(nullptr)
	, crop_rect_()
{
	this->Load(file_name);
}

e2d::Image::Image(const String & file_name, const Rect & crop_rect)
	: bitmap_(nullptr)
	, crop_rect_()
{
	this->Load(file_name);
	this->Crop(crop_rect);
}

e2d::Image::~Image()
{
	SafeRelease(bitmap_);
}

bool e2d::Image::Load(const Resource& res)
{
	if (!Image::CacheBitmap(res))
	{
		WARN("Load Image from file failed!");
		return false;
	}

	this->SetBitmap(bitmap_cache_.at(res.id));
	return true;
}

bool e2d::Image::Load(const String & file_name)
{
	WARN_IF(file_name.IsEmpty(), "Image Load failed! Invalid file name.");

	if (file_name.IsEmpty())
		return false;

	if (!Image::CacheBitmap(file_name))
	{
		WARN("Load Image from file failed!");
		return false;
	}

	this->SetBitmap(bitmap_cache_.at(file_name.GetHash()));
	return true;
}

void e2d::Image::Crop(const Rect& crop_rect)
{
	if (bitmap_)
	{
		auto bitmap_size = bitmap_->GetSize();
		crop_rect_.origin.x = std::min(std::max(crop_rect.origin.x, 0.f), bitmap_size.width);
		crop_rect_.origin.y = std::min(std::max(crop_rect.origin.y, 0.f), bitmap_size.height);
		crop_rect_.size.width = std::min(std::max(crop_rect.size.width, 0.f), bitmap_size.width - crop_rect.origin.x);
		crop_rect_.size.height = std::min(std::max(crop_rect.size.height, 0.f), bitmap_size.height - crop_rect.origin.y);
	}
}

float e2d::Image::GetWidth() const
{
	return crop_rect_.size.width;
}

float e2d::Image::GetHeight() const
{
	return crop_rect_.size.height;
}

e2d::Size e2d::Image::GetSize() const
{
	return crop_rect_.size;
}

float e2d::Image::GetSourceWidth() const
{
	if (bitmap_)
	{
		return bitmap_->GetSize().width;
	}
	else
	{
		return 0;
	}
}

float e2d::Image::GetSourceHeight() const
{
	if (bitmap_)
	{
		return bitmap_->GetSize().height;
	}
	else
	{
		return 0;
	}
}

e2d::Size e2d::Image::GetSourceSize() const
{
	Size source_size;
	if (bitmap_)
	{
		auto bitmap_size = bitmap_->GetSize();
		source_size.width = bitmap_size.width;
		source_size.height = bitmap_size.height;
	}
	return std::move(source_size);
}

float e2d::Image::GetCropX() const
{
	return crop_rect_.origin.x;
}

float e2d::Image::GetCropY() const
{
	return crop_rect_.origin.y;
}

e2d::Point e2d::Image::GetCropPos() const
{
	return crop_rect_.origin;
}

const e2d::Rect & e2d::Image::GetCropRect() const
{
	return crop_rect_;
}

ID2D1Bitmap * e2d::Image::GetBitmap() const
{
	return bitmap_;
}

bool e2d::Image::CacheBitmap(const Resource& res)
{
	if (bitmap_cache_.find(res.id) != bitmap_cache_.end())
	{
		return true;
	}

	IWICImagingFactory *imaging_factory = Device::GetGraphics()->GetImagingFactory();
	ID2D1HwndRenderTarget* render_target = Device::GetGraphics()->GetRenderTarget();
	IWICBitmapDecoder *decoder = nullptr;
	IWICBitmapFrameDecode *source = nullptr;
	IWICStream *stream = nullptr;
	IWICFormatConverter *converter = nullptr;
	ID2D1Bitmap *bitmap = nullptr;
	HRSRC res_handle = nullptr;
	HGLOBAL res_data_handle = nullptr;
	void *image_file = nullptr;
	DWORD image_file_size = 0;

	// ��λ��Դ
	res_handle = ::FindResourceW(
		HINST_THISCOMPONENT,
		MAKEINTRESOURCE(res.id),
		(LPCWSTR)res.type
	);

	HRESULT hr = res_handle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		// ������Դ
		res_data_handle = ::LoadResource(HINST_THISCOMPONENT, res_handle);

		hr = res_data_handle ? S_OK : E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		// ��ȡ�ļ�ָ�룬��������Դ
		image_file = ::LockResource(res_data_handle);

		hr = image_file ? S_OK : E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		// �����С
		image_file_size = ::SizeofResource(HINST_THISCOMPONENT, res_handle);

		hr = image_file_size ? S_OK : E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		// ���� WIC ��
		hr = imaging_factory->CreateStream(&stream);
	}

	if (SUCCEEDED(hr))
	{
		// ��ʼ����
		hr = stream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(image_file),
			image_file_size
		);
	}

	if (SUCCEEDED(hr))
	{
		// �������Ľ�����
		hr = imaging_factory->CreateDecoderFromStream(
			stream,
			nullptr,
			WICDecodeMetadataCacheOnLoad,
			&decoder
		);
	}

	if (SUCCEEDED(hr))
	{
		// ������ʼ�����
		hr = decoder->GetFrame(0, &source);
	}

	if (SUCCEEDED(hr))
	{
		// ����ͼƬ��ʽת����
		hr = imaging_factory->CreateFormatConverter(&converter);
	}

	if (SUCCEEDED(hr))
	{
		// ͼƬ��ʽת���� 32bppPBGRA
		hr = converter->Initialize(
			source,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	if (SUCCEEDED(hr))
	{
		// �� WIC λͼ����һ�� Direct2D λͼ
		hr = render_target->CreateBitmapFromWicBitmap(
			converter,
			nullptr,
			&bitmap
		);
	}

	if (SUCCEEDED(hr))
	{
		bitmap_cache_.insert(std::make_pair(res.id, bitmap));
	}

	// �ͷ������Դ
	SafeRelease(decoder);
	SafeRelease(source);
	SafeRelease(stream);
	SafeRelease(converter);

	return SUCCEEDED(hr);
}

bool e2d::Image::CacheBitmap(const String & file_name)
{
	size_t hash = file_name.GetHash();
	if (bitmap_cache_.find(hash) != bitmap_cache_.end())
		return true;

	File image_file;
	if (!image_file.Open(file_name))
		return false;

	// �û������·����һ��������·������Ϊ�û�����ͨ�� File::AddSearchPath ���
	// Ĭ������·����������Ҫͨ�� File::GetPath ��ȡ����·��
	String image_file_path = image_file.GetPath();

	Graphics * graphics_device = Device::GetGraphics();
	IWICImagingFactory *imaging_factory = graphics_device->GetImagingFactory();
	ID2D1HwndRenderTarget* render_target = graphics_device->GetRenderTarget();
	IWICBitmapDecoder *decoder = nullptr;
	IWICBitmapFrameDecode *source = nullptr;
	IWICStream *stream = nullptr;
	IWICFormatConverter *converter = nullptr;
	ID2D1Bitmap *bitmap = nullptr;

	// ����������
	HRESULT hr = imaging_factory->CreateDecoderFromFilename(
		(LPCWSTR)image_file_path,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&decoder
	);

	if (SUCCEEDED(hr))
	{
		// ������ʼ�����
		hr = decoder->GetFrame(0, &source);
	}

	if (SUCCEEDED(hr))
	{
		// ����ͼƬ��ʽת����
		hr = imaging_factory->CreateFormatConverter(&converter);
	}

	if (SUCCEEDED(hr))
	{
		// ͼƬ��ʽת���� 32bppPBGRA
		hr = converter->Initialize(
			source,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	if (SUCCEEDED(hr))
	{
		// �� WIC λͼ����һ�� Direct2D λͼ
		hr = render_target->CreateBitmapFromWicBitmap(
			converter,
			nullptr,
			&bitmap
		);
	}

	if (SUCCEEDED(hr))
	{
		bitmap_cache_.insert(std::make_pair(hash, bitmap));
	}

	// �ͷ������Դ
	SafeRelease(decoder);
	SafeRelease(source);
	SafeRelease(stream);
	SafeRelease(converter);

	return SUCCEEDED(hr);
}

void e2d::Image::ClearCache()
{
	if (bitmap_cache_.empty())
		return;

	for (const auto& bitmap : bitmap_cache_)
	{
		bitmap.second->Release();
	}
	bitmap_cache_.clear();
}

void e2d::Image::SetBitmap(ID2D1Bitmap * bitmap)
{
	if (bitmap_ == bitmap)
		return;

	if (bitmap_)
	{
		bitmap_->Release();
	}

	if (bitmap)
	{
		bitmap->AddRef();

		bitmap_ = bitmap;
		crop_rect_.origin.x = crop_rect_.origin.y = 0;
		crop_rect_.size.width = bitmap_->GetSize().width;
		crop_rect_.size.height = bitmap_->GetSize().height;
	}
}
