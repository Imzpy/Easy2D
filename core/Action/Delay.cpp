#include "..\e2daction.h"

e2d::Delay::Delay(float duration)
	: _delta(0)
	, _delay(std::max(duration, 0.f))
{
}

e2d::Delay * e2d::Delay::clone() const
{
	return new (e2d::autorelease) Delay(_delay);
}

e2d::Delay * e2d::Delay::reverse() const
{
	return new (e2d::autorelease) Delay(_delay);
}

void e2d::Delay::reset()
{
	Action::reset();
	_delta = 0;
}

void e2d::Delay::_init()
{
	Action::_init();
}

void e2d::Delay::_update()
{
	Action::_update();

	_delta = Game::getInstance()->getTotalDuration().seconds() - _last;

	if (_delta >= _delay)
	{
		this->stop();
	}
}

void e2d::Delay::_resetTime()
{
	Action::_resetTime();
	_last = Game::getInstance()->getTotalDuration().seconds() - _delta;
}
