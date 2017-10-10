#include "..\easy2d.h"
#include "..\Win\winbase.h"
#include "..\EasyX\easyx.h"
#include <assert.h>
#include <imm.h>
#pragma comment(lib, "imm32.lib")
#include <stack>
#include <chrono>
#include <thread>

using namespace std::chrono;

// App 的唯一实例
static App * s_pInstance = nullptr;
// 场景栈
static std::stack<Scene*> s_SceneStack;

App::App() : 
	m_pCurrentScene(nullptr), 
	m_pNextScene(nullptr), 
	m_pLoadingScene(nullptr),
	m_bRunning(false), 
	m_nWindowMode(0),
	m_bSaveScene(true)
{
	assert(!s_pInstance);	// 不能同时存在两个 App 实例
	s_pInstance = this;		// 保存实例对象
}

App::~App()
{
}

App * App::get()
{
	assert(s_pInstance);	// 断言实例存在
	return s_pInstance;		// 获取 App 的唯一实例
}

int App::run()
{
	// 记录当前时间
	steady_clock::time_point nLast = steady_clock::now();
	// 帧间隔
	LONGLONG nAnimationInterval = 17LL;
	// 时间间隔
	LONGLONG nInterval = 0LL;
	// 挂起时长
	LONGLONG nWaitMS = 0LL;

	// 初始化窗口
	_initGraph();
	// 开启批量绘图
	BeginBatchDraw();
	// 绘制一次画面
	_draw();
	// 运行游戏
	m_bRunning = true;

	// 进入主循环
	while (m_bRunning)
	{
		// 刷新计时
		::FlushSteadyClock();
		// 计算时间间隔
		nInterval = GetInterval(nLast);
		// 判断间隔时间是否足够
		if (nInterval >= nAnimationInterval)
		{
			// 记录当前时间
			nLast += milliseconds(nAnimationInterval);
			// 刷新游戏画面
			_draw();
			// 执行主循环
			_mainLoop();
		}
		else
		{
			// 计算挂起时长
			nWaitMS = nAnimationInterval - nInterval - 1;
			// 挂起线程，释放 CPU 占用
			if (nWaitMS > 1LL)
			{
				std::this_thread::sleep_for(milliseconds(nWaitMS));
			}
		}
	}
	// 停止批量绘图
	EndBatchDraw();
	// 关闭窗口
	close();
	// 释放所有内存占用
	free();

	return 0;
}

void App::_initGraph()
{
	// 创建绘图环境
	initgraph(m_Size.cx, m_Size.cy, m_nWindowMode);
	// 设置窗口居中
	WindowCenter(GetHWnd());
	// 禁用输入法
	ImmAssociateContext(GetHWnd(), NULL);
	// 重置绘图环境
	reset();
	// 设置窗口标题
	if (m_sTitle.empty())
	{
		// 保存当前标题
		TCHAR title[31];
		GetWindowText(GetHWnd(), title, 30);
		m_sTitle = title;
	}
	else
	{
		setWindowTitle(m_sTitle);
	}
	// 若未设置 AppName，默认设为标题名
	if (m_sAppName.empty())
	{
		m_sAppName = m_sTitle;
	}
}

void App::_draw()
{
	// 下一场景指针不为空时，切换场景
	if (m_pNextScene)
	{
		// 进入下一场景
		_enterNextScene();
	}
	cleardevice();				// 清空画面
	m_pCurrentScene->_onDraw();	// 绘制当前场景
	FlushBatchDraw();			// 刷新画面
}

void App::_mainLoop()
{
	MouseMsg::__exec();			// 鼠标检测
	KeyMsg::__exec();			// 键盘按键检测
	Timer::__exec();			// 定时器执行程序
	ActionManager::__exec();	// 动作管理器执行程序
	FreePool::__flush();		// 刷新内存池
}

void App::createWindow(int width, int height, int mode)
{
	// 保存窗口信息
	m_Size.cx = width;
	m_Size.cy = height;
	m_nWindowMode = mode;
}

void App::createWindow(CSize size, int mode)
{
	createWindow(size.cx, size.cy, mode);
}

void App::createWindow(TString title, int width, int height, int mode)
{
	// 保存窗口信息
	m_Size.cx = width;
	m_Size.cy = height;
	m_nWindowMode = mode;
	m_sTitle = title;
}

void App::createWindow(TString title, CSize size, int mode)
{
	createWindow(title, size.cx, size.cy, mode);
}

void App::setWindowSize(int width, int height)
{
	// 修改窗口大小
	Resize(NULL, width, height);
	// 设置窗口居中
	WindowCenter(GetHWnd());
	// 重置窗口属性
	reset();
}

void App::setWindowSize(CSize size)
{
	setWindowSize(size.cx, size.cy);
}

void App::setWindowTitle(TString title)
{
	// 设置窗口标题
	SetWindowText(GetHWnd(), title.c_str());
	// 保存当前标题，用于修改窗口大小时恢复标题
	s_pInstance->m_sTitle = title;
}

TString App::getWindowTitle()
{
	return s_pInstance->m_sTitle;
}

void App::close()
{
	closegraph();	// 关闭绘图环境
}

void App::enterScene(Scene * scene, bool save)
{
	// 保存下一场景的指针
	s_pInstance->m_pNextScene = scene;
	// 切换场景时，是否保存当前场景
	s_pInstance->m_bSaveScene = save;
}

void App::backScene()
{
	// 从栈顶取出场景指针，作为下一场景
	s_pInstance->m_pNextScene = s_SceneStack.top();
	// 不保存当前场景
	s_pInstance->m_bSaveScene = false;
}

void App::clearScene()
{
	// 清空场景栈
	while (s_SceneStack.size())
	{
		auto temp = s_SceneStack.top();
		SafeDelete(temp);
		s_SceneStack.pop();
	}
}

void App::setAppName(TString appname)
{
	s_pInstance->m_sAppName = appname;
}

TString App::getAppName()
{
	return s_pInstance->m_sAppName;
}

void App::setBkColor(COLORREF color)
{
	setbkcolor(color);
}

void App::_enterNextScene()
{
	bool bBackScene = false;

	// 若下一场景处于栈顶，说明正在返回上一场景
	if (s_SceneStack.size() && m_pNextScene == s_SceneStack.top())
	{
		bBackScene = true;
		// 删除栈顶场景
		s_SceneStack.pop();
	}

	// 执行当前场景的 onExit 函数
	if (m_pCurrentScene)
	{
		m_pCurrentScene->onExit();
		if (m_bSaveScene)
		{
			// 若要保存当前场景，把它放入栈中
			s_SceneStack.push(m_pCurrentScene);
			// 暂停当前场景上运行的所有定时器
			Timer::waitAllSceneTimers(m_pCurrentScene);
			MouseMsg::waitAllSceneListeners(m_pCurrentScene);
			KeyMsg::waitAllSceneListeners(m_pCurrentScene);
			ActionManager::waitAllSceneActions(m_pCurrentScene);
		}
		else
		{
			// 不保存场景时，停止当前场景上运行的所有定时器，并删除当前场景
			Timer::clearAllSceneTimers(m_pCurrentScene);
			MouseMsg::clearAllSceneListeners(m_pCurrentScene);
			KeyMsg::clearAllSceneListeners(m_pCurrentScene);
			ActionManager::stopAllSceneActions(m_pCurrentScene);
			SafeDelete(m_pCurrentScene);
		}
	}

	m_pCurrentScene = m_pNextScene;		// 切换场景
	m_pNextScene = nullptr;				// 下一场景置空

	if (bBackScene)
	{
		// 返回上一场景时，恢复场景上的定时器
		Timer::notifyAllSceneTimers(m_pCurrentScene);
		MouseMsg::notifyAllSceneListeners(m_pCurrentScene);
		KeyMsg::notifyAllSceneListeners(m_pCurrentScene);
		ActionManager::notifyAllSceneActions(m_pCurrentScene);
	}
	else
	{
		m_pCurrentScene->init();		// 进入一个新场景时，执行它的 init 函数
	}

	m_pCurrentScene->onEnter();			// 执行下一场景的 onEnter 函数
}

void App::quit()
{
	s_pInstance->m_bRunning = false;
}

void App::end()
{
	s_pInstance->m_bRunning = false;
}

void App::reset()
{
	// 重置绘图环境
	graphdefaults();
	setbkmode(TRANSPARENT);
	setbkcolor(Color::black);
}

Scene * App::getCurrentScene()
{
	// 获取当前场景的指针
	return s_pInstance->m_pCurrentScene;
}

Scene * App::getLoadingScene()
{
	return s_pInstance->m_pLoadingScene;
}

int App::getWidth()
{
	return s_pInstance->m_Size.cx;
}

int App::getHeight()
{
	return s_pInstance->m_Size.cy;
}

void App::free()
{
	// 释放场景内存
	SafeDelete(m_pCurrentScene);
	SafeDelete(m_pNextScene);
	// 清空场景栈
	while (s_SceneStack.size())
	{
		auto temp = s_SceneStack.top();
		SafeDelete(temp);
		s_SceneStack.pop();
	}
	// 删除所有定时器
	Timer::clearAllTimers();
	MouseMsg::clearAllListeners();
	KeyMsg::clearAllListeners();
	ActionManager::clearAllActions();
	// 删除所有对象
	FreePool::__clearAllObjects();
}
