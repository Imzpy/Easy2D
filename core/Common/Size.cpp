#include "..\e2dcommon.h"

e2d::Size::Size()
{
	width = 0;
	height = 0;
}

e2d::Size::Size(float width, float height)
{
	this->width = width;
	this->height = height;
}

e2d::Size::Size(const Size & other)
{
	width = other.width;
	height = other.height;
}

e2d::Size e2d::Size::operator+(Size const & size) const
{
	return Size(width + size.width, height + size.height);
}

e2d::Size e2d::Size::operator-(Size const & size) const
{
	return Size(width - size.width, height - size.height);
}

e2d::Size e2d::Size::operator*(float const & value) const
{
	return Size(width * value, height * value);
}

e2d::Size e2d::Size::operator/(float const & value) const
{
	return Size(width / value, height / value);
}

e2d::Size::operator e2d::Point() const
{
	return Point(width, height);
}

e2d::Size e2d::Size::operator-() const
{
	return Size(-width, -height);
}

bool e2d::Size::operator==(const Size & size) const
{
	return (width == size.width) && (height == size.height);
}
