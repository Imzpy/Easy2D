#pragma once
#include "e2dmacros.h"
#include "e2dcommon.h"
#include "e2dcustom.h"


// Base Classes

namespace e2d
{


// ��Ϸ����
class Game
{
public:
	// ��ȡ��Ϸʵ��
	static Game * getInstance();

	// ����ʵ��
	static void destroyInstance();

	// ������Ϸ
	void start(
		bool cleanup = true		/* �Զ�������Դ */
	);

	// ��ͣ��Ϸ
	void pause();

	// ������Ϸ
	void resume();

	// ������Ϸ
	void quit();

	// ������Դ
	void cleanup();

	// ������Ϸ�ڲ���ʱ
	void reset();

	// ��Ϸ�Ƿ���ͣ
	bool isPaused();

private:
	Game();

	~Game();

	E2D_DISABLE_COPY(Game);

private:
	bool	_ended;
	bool	_paused;
	bool	_initialized;
	static Game * _instance;
};


// ���ڿ���
class Window
{
	friend class Game;

public:
	// ���ָ����ʽ
	enum class Cursor : int
	{
		Normal,		/* Ĭ��ָ����ʽ */
		Hand,		/* ��״ָ�� */
		No,			/* ��ָֹ�� */
		Wait,		/* ɳ©ָ�� */
		ArrowWait	/* Ĭ��ָ���Сɳ© */
	};

public:
	// ��ȡ����ʵ��
	static Window * getInstance();

	// ���ٴ���ʵ��
	static void destroyInstance();

	// �������ڻ�����
	bool createMutex(
		const String& mutex = L""	/* ���̻��������� */
	);

	// �޸Ĵ��ڴ�С
	void setSize(
		int width,			/* ���ڿ�� */
		int height			/* ���ڸ߶� */
	);

	// ���ô��ڱ���
	void setTitle(
		const String& title	/* ���ڱ��� */
	);

	// ���ô���ͼ��
	void setIcon(
		int iconID
	);

	// �������ָ����ʽ
	void setCursor(
		Cursor cursor
	);

	// ��ȡ���ڱ���
	String getTitle();

	// ��ȡ���ڿ��
	double getWidth();

	// ��ȡ���ڸ߶�
	double getHeight();

	// ��ȡ���ڴ�С
	Size getSize();

	// ��ȡ���ھ��
	HWND getHWnd();

	// ��/���ؿ���̨
	void showConsole(
		bool show = true
	);

	// �Ƿ�������Ӧ���뷨
	void setTypewritingEnable(
		bool enable
	);

	// ������ʾ����
	void info(
		const String& text,					/* ���� */
		const String& title = L"Infomation"	/* ���ڱ��� */
	);

	// �������洰��
	void warning(
		const String& text,					/* ���� */
		const String& title = L"Warning"	/* ���ڱ��� */
	);

	// �������󴰿�
	void error(
		const String& text,					/* ���� */
		const String& title = L"Error"		/* ���ڱ��� */
	);

private:
	Window();

	~Window();

	E2D_DISABLE_COPY(Window);

	// ע�ᴰ��
	HWND __create();

	// ��������Ϣ
	void __poll();

	// Win32 ������Ϣ�ص�����
	static LRESULT CALLBACK WndProc(
		HWND hWnd, 
		UINT message, 
		WPARAM wParam, 
		LPARAM lParam
	);

private:
	HWND	_hWnd;
	Size	_size;
	String	_title;
	int		_iconID;

	static Window * _instance;
};


// ʱ�����
class Time
{
	friend class Game;

public:
	// ��ȡ��һ֡��ʱ�������룩
	static double getDeltaTime();

	// ��ȡ��Ϸ��ʱ�����룩
	static double getTotalTime();

private:
	// ��ʼ����ʱ����
	static bool __init();

	// �Ƿ�ﵽ����ʱ��
	static bool __isReady();

	// ���µ�ǰʱ��
	static void __updateNow();

	// ����ʱ����Ϣ
	static void __updateLast();

	// ����ʱ����Ϣ
	static void __reset();

	// �����߳�
	static void __sleep();

private:
	static std::chrono::steady_clock::time_point _start;
	static std::chrono::steady_clock::time_point _now;
	static std::chrono::steady_clock::time_point _last;
	static std::chrono::steady_clock::time_point _fixedLast;
	static std::chrono::milliseconds _interval;
};


class Listener;

// �����豸
class Input
{
	friend class Game;

public:
	// ����ֵ
	enum class Mouse : int
	{
		Left,		/* ������ */
		Right,		/* ����Ҽ� */
		Middle		/* ����м� */
	};


	// ���̼�ֵ
	enum class Key : int
	{
		Up = 0xC8,
		Left = 0xCB,
		Right = 0xCD,
		Down = 0xD0,
		Enter = 0x1C,
		Space = 0x39,
		Esc = 0x01,
		Q = 0x10,
		W = 0x11,
		E = 0x12,
		R = 0x13,
		T = 0x14,
		Y = 0x15,
		U = 0x16,
		I = 0x17,
		O = 0x18,
		P = 0x19,
		A = 0x1E,
		S = 0x1F,
		D = 0x20,
		F = 0x21,
		G = 0x22,
		H = 0x23,
		J = 0x24,
		K = 0x25,
		L = 0x26,
		Z = 0x2C,
		X = 0x2D,
		C = 0x2E,
		V = 0x2F,
		B = 0x30,
		N = 0x31,
		M = 0x32,
		Num1 = 0x02,
		Num2 = 0x03,
		Num3 = 0x04,
		Num4 = 0x05,
		Num5 = 0x06,
		Num6 = 0x07,
		Num7 = 0x08,
		Num8 = 0x09,
		Num9 = 0x0A,
		Num0 = 0x0B,
		Numpad7 = 0x47,
		Numpad8 = 0x48,
		Numpad9 = 0x49,
		Numpad4 = 0x4B,
		Numpad5 = 0x4C,
		Numpad6 = 0x4D,
		Numpad1 = 0x4F,
		Numpad2 = 0x50,
		Numpad3 = 0x51,
		Numpad0 = 0x52
	};

public:
	// ��ȡ�����豸ʵ��
	static Input * getInstance();

	// ���������豸ʵ��
	static void destroyInstance();

	// ������ĳ�����Ƿ���������
	bool isDown(
		Key key
	);

	// ������ĳ�����Ƿ񱻵��
	bool isPress(
		Key key
	);

	// ������ĳ�����Ƿ������ɿ�
	bool isRelease(
		Key key
	);

	// �����갴���Ƿ���������
	bool isDown(
		Mouse code
	);

	// �����갴���Ƿ񱻵��
	bool isPress(
		Mouse code
	);

	// �����갴���Ƿ������ɿ�
	bool isRelease(
		Mouse code
	);

	// ������X������ֵ
	double getMouseX();

	// ������Y������ֵ
	double getMouseY();

	// ����������ֵ
	Point getMousePos();

	// ������X����������
	double getMouseDeltaX();

	// ������Y����������
	double getMouseDeltaY();

	// ������Z�ᣨ�����֣���������
	double getMouseDeltaZ();

	// ����������
	static Listener * addListener(
		const Function& func,		/* �������û�����ʱ��ִ�к��� */
		const String& name = L"",	/* ���������� */
		bool paused = false			/* �Ƿ���ͣ */
	);

	// �����ײ����
	static void addListener(
		Listener * listener			/* ������ */
	);

	// �Ƴ�������
	static void removeListener(
		Listener * listener			/* ������ */
	);

	// �����������
	static void startListener(
		const String& name
	);

	// ֹͣ�������
	static void stopListener(
		const String& name
	);

	// �Ƴ��������
	static void removeListener(
		const String& name
	);

	// �������м�����
	static void startAllListeners();

	// ֹͣ���м�����
	static void stopAllListeners();

	// �Ƴ����м�����
	static void removeAllListeners();

private:
	Input();

	~Input();

	E2D_DISABLE_COPY(Input);

	// ˢ��������Ϣ
	void __update();

	// ˢ���豸״̬
	void __updateDeviceState();

	// ���¼�����
	static void __updateListeners();

	// ��ռ�����
	static void __clearListeners();

private:
	IDirectInput8* _directInput;
	IDirectInputDevice8* _keyboardDevice;
	IDirectInputDevice8* _mouseDevice;
	DIMOUSESTATE _mouseState;
	DIMOUSESTATE _mouseStateRecord;
	POINT _mousePos;

	static Input * _instance;
};


// ��Ⱦ��
class Renderer
{
	friend class Game;
	friend class Window;

public:
	// ��ȡ��Ⱦ��ʵ��
	static Renderer * getInstance();

	// ����ʵ��
	static void destroyInstance();

	// ��ȡ����ɫ
	Color getBackgroundColor();

	// �޸ı���ɫ
	void setBackgroundColor(
		Color color
	);

	// ��ʾ FPS
	void showFps(
		bool show = true
	);

	// ��ȡ������Ⱦ��
	TextRenderer * getTextRenderer();

	// ��ȡ ID2D1HwndRenderTarget ����
	ID2D1HwndRenderTarget * getRenderTarget();

	// ��ȡ ID2D1SolidColorBrush ����
	ID2D1SolidColorBrush * getSolidColorBrush();

	// ��ȡ ID2D1Factory ����
	static ID2D1Factory * getFactory();

	// ��ȡ IWICImagingFactory ����
	static IWICImagingFactory * getImagingFactory();

	// ��ȡ IDWriteFactory ����
	static IDWriteFactory * getWriteFactory();

	// ��ȡ FPS �ı���ʽ������
	static IDWriteTextFormat * getFpsTextFormat();

	// ��ȡ Miter ��ʽ�� ID2D1StrokeStyle
	static ID2D1StrokeStyle * getMiterStrokeStyle();

	// ��ȡ Bevel ��ʽ�� ID2D1StrokeStyle
	static ID2D1StrokeStyle * getBevelStrokeStyle();

	// ��ȡ Round ��ʽ�� ID2D1StrokeStyle
	static ID2D1StrokeStyle * getRoundStrokeStyle();

private:
	Renderer();

	~Renderer();

	E2D_DISABLE_COPY(Renderer);

	// ��Ⱦ��Ϸ����
	void __render();

	// �����豸�����Դ
	bool __createDeviceResources();

	// ɾ���豸�����Դ
	void __discardDeviceResources();

private:
	bool					_showFps;
	D2D1_COLOR_F			_clearColor;
	ID2D1HwndRenderTarget*	_renderTarget;
	ID2D1SolidColorBrush*	_solidBrush;
	TextRenderer*			_textRenderer;

	static ID2D1Factory*		_d2dFactory;
	static IWICImagingFactory*	_imagingFactory;
	static IDWriteFactory*		_writeFactory;
	static IDWriteTextFormat*	_textFormat;
	static ID2D1StrokeStyle*	_miterStrokeStyle;
	static ID2D1StrokeStyle*	_bevelStrokeStyle;
	static ID2D1StrokeStyle*	_roundStrokeStyle;
	static Renderer *			_instance;
};


// ��������װ��
class GC
{
	friend class Game;

public:
	//  ��ȡ GC ʵ��
	static GC* getInstance();

	// ��������
	template <typename Type>
	static inline void retain(Type*& p)
	{
		if (p != nullptr)
		{
			p->retain();
		}
	}

	// �ͷŶ���
	template <typename Type>
	static inline void release(Type*& p)
	{
		if (p != nullptr)
		{
			p->release();
			p = nullptr;
		}
	}

	// ֪ͨ GC ���������ڴ�
	void notify();

	// �ֶ����������ڴ�
	void flush();

	// ��������� GC
	void addObject(
		Object * pObject
	);

	// ������ж���
	void clear();

private:
	GC() {}

	~GC();

	E2D_DISABLE_COPY(GC);

	// ���� GC
	void __update();

private:
	bool				_notifyed;
	std::set<Object*>	_pool;

	static GC _instance;
};

}