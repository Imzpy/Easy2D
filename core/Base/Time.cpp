#include "..\e2dbase.h"
#include "..\e2dtool.h"
#include "..\e2dmanager.h"
#include <thread>

using namespace std::chrono;


// ��Ϸ��ʼʱ��
steady_clock::time_point e2d::Time::_start;
// ��ǰʱ��
steady_clock::time_point e2d::Time::_now;
// ��һ֡ˢ��ʱ��
steady_clock::time_point e2d::Time::_last;
// �̶���ˢ��ʱ��
steady_clock::time_point e2d::Time::_fixedLast;
// ÿһ֡���
milliseconds e2d::Time::_interval;


double e2d::Time::getTotalTime()
{
	return duration_cast<microseconds>(_now - _start).count() / 1000.0 / 1000.0;
}

double e2d::Time::getDeltaTime()
{
	return duration_cast<microseconds>(_now - _last).count() / 1000.0 / 1000.0;
}

bool e2d::Time::__init()
{
	_start = _fixedLast = _last = _now = steady_clock::now();
	_interval = milliseconds(15);
	return true;
}

bool e2d::Time::__isReady()
{
	return _interval < duration_cast<milliseconds>(_now - _fixedLast);
}

void e2d::Time::__updateNow()
{
	_now = steady_clock::now();
}

void e2d::Time::__updateLast()
{
	_fixedLast += _interval;

	_last = _now;
	_now = steady_clock::now();
}

void e2d::Time::__reset()
{
	_last = _fixedLast = _now = steady_clock::now();
	Timer::getInstance()->updateTime();
	ActionManager::getInstance()->updateTime();
}

void e2d::Time::__sleep()
{
	// �������ʱ��
	int nWaitMS = 16 - static_cast<int>(duration_cast<milliseconds>(_now - _fixedLast).count());
	
	if (nWaitMS > 1)
	{
		// �����̣߳��ͷ� CPU ռ��
		std::this_thread::sleep_for(milliseconds(nWaitMS));
	}
}
