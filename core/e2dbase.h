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

	// ��Ϸ�Ƿ���ͣ
	bool isPaused();

	// �޸���Ϸ����
	void setConfig(
		Config* config
	);

	// ��ȡ��Ϸ����
	Config* getConfig();

private:
	Game();

	~Game();

	E2D_DISABLE_COPY(Game);

private:
	bool	_ended;
	bool	_paused;
	Config*	_config;

	static Game * _instance;
};


// ����
class Window
{
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

	// ������ʽ
	enum class Popup : int
	{
		Information,	/* ��Ϣ */
		Warning,		/* ���� */
		Error			/* ���� */
	};

public:
	// ��ȡ����ʵ��
	static Window * getInstance();

	// ���ٴ���ʵ��
	static void destroyInstance();

	// �������廥����
	bool createMutex(
		const String& mutex = L""	/* ���̻��������� */
	);

	// �޸Ĵ����С
	void setSize(
		int width,			/* ������ */
		int height			/* ����߶� */
	);

	// ���ô������
	void setTitle(
		const String& title	/* ������� */
	);

	// ���ô���ͼ��
	void setIcon(
		int iconID
	);

	// �������ָ����ʽ
	void setCursor(
		Cursor cursor
	);

	// ��ȡ�������
	String getTitle();

	// ��ȡ������
	double getWidth();

	// ��ȡ����߶�
	double getHeight();

	// ��ȡ�����С
	Size getSize();

	// ��ȡ���ھ��
	HWND getHWnd();

	// �򿪻����ؿ���̨
	void setConsoleEnabled(
		bool enabled
	);

	// �Ƿ�������Ӧ���뷨
	void setTypewritingEnabled(
		bool enabled
	);

	// ��������
	// ����ֵ�������ڰ���ȡ����ťʱ������ֵ��ʾ�û��Ƿ���ȷ�ϰ�ť
	bool popup(
		const String& text,					/* �������� */
		const String& title,				/* ���ڱ��� */
		Popup style = Popup::Information,	/* ������ʽ */
		bool hasCancel = false				/* ����ȡ����ť */
	);

	// ��������Ϣ
	void poll();

private:
	Window();

	~Window();

	E2D_DISABLE_COPY(Window);

	// ע�ᴰ��
	HWND __create();

	// Win32 ������Ϣ�ص�����
	static LRESULT CALLBACK WndProc(
		HWND hWnd, 
		UINT message, 
		WPARAM wParam, 
		LPARAM lParam
	);

private:
	HWND	_hWnd;
	MSG		_msg;
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


// �����豸
class Input
{
public:
	// ��ȡ�����豸ʵ��
	static Input * getInstance();

	// ���������豸ʵ��
	static void destroyInstance();

	// ������ĳ�����Ƿ���������
	bool isDown(
		KeyCode key
	);

	// ������ĳ�����Ƿ񱻵��
	bool isPress(
		KeyCode key
	);

	// ������ĳ�����Ƿ������ɿ�
	bool isRelease(
		KeyCode key
	);

	// �����갴���Ƿ���������
	bool isDown(
		MouseCode code
	);

	// �����갴���Ƿ񱻵��
	bool isPress(
		MouseCode code
	);

	// �����갴���Ƿ������ɿ�
	bool isRelease(
		MouseCode code
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

	// ˢ�������豸״̬
	void update();

private:
	Input();

	~Input();

	E2D_DISABLE_COPY(Input);

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

	// ��Ⱦ��Ϸ����
	void render();

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


// ����������
class GC
{
	friend class Game;

public:
	// �Զ��ͷ�
	static void autorelease(
		Ref* ref
	);

	// �Զ��ͷ�����
	static void autoreleaseArray(
		Ref* ref
	);

	// ����
	static void retain(
		Ref* ref
	);

	// �ͷ�
	static void release(
		Ref* ref
	);

	// ��ȫ���ͷŶ���
	template <typename Type>
	static inline void safeRelease(Type*& p)
	{
		if (p != nullptr)
		{
			GC::release(p);
			p = nullptr;
		}
	}

	// ˢ���ڴ��
	static void flush();

	// �����ڴ���е����ж���
	static void clear();

private:
	GC();

	~GC();

	E2D_DISABLE_COPY(GC);

private:
	bool _notifyed;
	bool _cleanup;
	std::map<Ref*, bool> _pool;

	static GC _instance;
};

}