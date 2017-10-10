#pragma once
#include <Windows.h>
#include <atltypes.h>
#include <chrono>
using namespace std::chrono;

// 获取当前时刻
steady_clock::time_point GetNow();

// 刷新时钟
void FlushSteadyClock();

// 计算时间点与当前时间的间隔（毫秒）
LONGLONG GetInterval(steady_clock::time_point nLast);

// 设置窗口居中
void WindowCenter(HWND hWnd);