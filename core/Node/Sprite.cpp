#include "..\e2dnode.h"


e2d::Sprite::Sprite()
	: _image(nullptr)
{
}

e2d::Sprite::Sprite(Image * image)
	: _image(nullptr)
{
	open(image);
}

e2d::Sprite::Sprite(const Resource& res)
	: _image(nullptr)
{
	open(res);
}

e2d::Sprite::Sprite(const Resource& res, const Rect& cropRect)
	: _image(nullptr)
{
	open(res);
	crop(cropRect);
}

e2d::Sprite::Sprite(const String & fileName)
	: _image(nullptr)
{
	open(fileName);
}

e2d::Sprite::Sprite(const String & fileName, const Rect & cropRect)
	: _image(nullptr)
{
	open(fileName);
	crop(cropRect);
}

e2d::Sprite::~Sprite()
{
	GC::instance()->safeRelease(_image);
}

bool e2d::Sprite::open(Image * image)
{
	if (image)
	{
		if (_image) _image->release();
		_image = image;
		_image->retain();

		Node::size(_image->width(), _image->height());
		return true;
	}
	return false;
}

bool e2d::Sprite::open(const Resource& res)
{
	if (!_image)
	{
		_image = new (e2d::autorelease) Image();
		_image->retain();
	}

	if (_image->open(res))
	{
		Node::size(_image->width(), _image->height());
		return true;
	}
	return false;
}

bool e2d::Sprite::open(const String & fileName)
{
	if (!_image)
	{
		_image = new (e2d::autorelease) Image();
		_image->retain();
	}

	if (_image->open(fileName))
	{
		Node::size(_image->width(), _image->height());
		return true;
	}
	return false;
}

e2d::Sprite& e2d::Sprite::crop(const Rect& cropRect)
{
	_image->crop(cropRect);
	Node::size(
		std::min(std::max(cropRect.size.width, 0.f), _image->realWidth() - _image->cropX()),
		std::min(std::max(cropRect.size.height, 0.f), _image->realHeight() - _image->cropY())
	);
	return *this;
}

e2d::Image * e2d::Sprite::image() const
{
	return _image;
}

void e2d::Sprite::draw(Renderer * renderer) const
{
	if (_image && _image->bitmap())
	{
		// ��ȡͼƬ�ü�λ��
		float fCropX = _image->cropX();
		float fCropY = _image->cropY();
		// ��ȾͼƬ
		renderer->renderTarget()->DrawBitmap(
			_image->bitmap(),
			D2D1::RectF(0, 0, _size.width, _size.height),
			_displayOpacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF(
				fCropX,
				fCropY,
				fCropX + _size.width,
				fCropY + _size.height
			)
		);
	}
}
