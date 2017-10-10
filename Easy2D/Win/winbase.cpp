#include "winbase.h"

static steady_clock::time_point nNow;

steady_clock::time_point GetNow()
{
	return nNow;
}

void FlushSteadyClock()
{
	nNow = steady_clock::now();	// 获取当前时间
}

LONGLONG GetInterval(steady_clock::time_point nLast)
{
	return duration_cast<milliseconds>(nNow - nLast).count();
}

void WindowCenter(HWND hWnd)
{
	// 获取屏幕分辨率
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	// 获取窗口大小
	CRect rcWindow;
	GetWindowRect(hWnd, &rcWindow);
	// 设置窗口在屏幕居中
	SetWindowPos(hWnd, HWND_TOP,
		(screenWidth - rcWindow.Size().cx) / 2,
		(screenHeight - rcWindow.Size().cy) / 2,
		rcWindow.Size().cx,
		rcWindow.Size().cy,
		SWP_SHOWWINDOW | SWP_NOSIZE);
}