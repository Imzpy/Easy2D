#include "..\e2daction.h"
#include "..\e2dnode.h"

e2d::MoveTo::MoveTo(float duration, Point pos)
	: MoveBy(duration, Vector2())
{
	_endPos = pos;
}

e2d::MoveTo * e2d::MoveTo::clone() const
{
	return new (e2d::autorelease) MoveTo(_duration, _endPos);
}

void e2d::MoveTo::_init()
{
	MoveBy::_init();
	_deltaPos = _endPos - _startPos;
}
