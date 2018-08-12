#pragma once
#include "e2dmacros.h"
#include "e2dcommon.h"
#include "e2dcustom.h"


// Base Classes

namespace e2d
{


// ����
class Config
{
public:
	Config();

	virtual ~Config();

	// �޸���Ϸ����
	// Ĭ�ϣ���
	void setGameName(
		const String& name
	);

	// ��ʾ������ FPS
	// Ĭ�ϣ�����
	void showFps(
		bool show
	);

	// ��ʾ�����ؽڵ�����
	// Ĭ�ϣ�����
	void setOutlineVisible(
		bool visible
	);

	// �򿪻�ر���ײ����
	// Ĭ�ϣ��ر�
	void setCollisionEnabled(
		bool enabled
	);

	// �򿪻�ر���ײ����ӻ�
	// Ĭ�ϣ��ر�
	void setColliderVisible(
		bool visible
	);

	// ��ȡ��Ϸ����
	String getGameName() const;

	// ��ȡ FPS ��ʾ״̬
	bool isFpsShow() const;

	// ��ȡ�ڵ�������ʾ״̬
	bool isOutlineVisible() const;

	// ��ȡ��ײ����״̬
	bool isCollisionEnabled() const;

	// ��ȡ��ײ����ӻ�״̬
	bool isColliderVisible() const;

protected:
	bool			_showFps;
	bool			_outlineVisible;
	bool			_collisionEnabled;
	bool			_colliderVisible;
	String			_gameName;
};


// ��Ϸ����
class Game
{
public:
	// ��ȡ��Ϸʵ��
	static Game * getInstance();

	// ����ʵ��
	static void destroyInstance();

	// ������Ϸ
	void start();

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
		const Config& config
	);

	// ��ȡ��Ϸ����
	const Config& getConfig();

private:
	Game();

	~Game();

	E2D_DISABLE_COPY(Game);

private:
	bool		_quit;
	bool		_paused;
	Config		_config;

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
	float getWidth();

	// ��ȡ����߶�
	float getHeight();

	// ��ȡ�����С
	Size getSize();

	// ��ȡ���� DPI
	float getDpi();

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
	HWND __registerWindow();

	// ���ݿͻ�����С������ʵĴ�������
	Rect __adjustWindow(
		int width,
		int height
	);

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
	float	_dpi;

	static Window * _instance;
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

	// �����갴���Ƿ���������
	bool isDown(
		MouseCode code
	);

	// ������X������ֵ
	float getMouseX();

	// ������Y������ֵ
	float getMouseY();

	// ����������ֵ
	Point getMousePos();

	// ������X����������
	float getMouseDeltaX();

	// ������Y����������
	float getMouseDeltaY();

	// ������Z�ᣨ�����֣���������
	float getMouseDeltaZ();

	// ˢ�������豸״̬
	void update();

private:
	Input();

	~Input();

	E2D_DISABLE_COPY(Input);

private:
	IDirectInput8W* _directInput;
	IDirectInputDevice8W* _keyboardDevice;
	IDirectInputDevice8W* _mouseDevice;
	DIMOUSESTATE _mouseState;
	char _keyBuffer[256];

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

	// ��ȡ������Ⱦ��
	TextRenderer * getTextRenderer();

	// ��ȡ ID2D1HwndRenderTarget ����
	ID2D1HwndRenderTarget * getRenderTarget();

	// ��ȡ ID2D1SolidColorBrush ����
	ID2D1SolidColorBrush * getSolidColorBrush();

	// ��Ⱦ��Ϸ����
	void render();

	// ɾ���豸�����Դ
	void discardDeviceResources();

	// ��ȡ ID2D1Factory ����
	static ID2D1Factory * getFactory();

	// ��ȡ IWICImagingFactory ����
	static IWICImagingFactory * getImagingFactory();

	// ��ȡ IDWriteFactory ����
	static IDWriteFactory * getWriteFactory();

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

	// ��Ⱦ FPS
	void _renderFps();

private:
	int						_renderTimes;
	Time					_lastRenderTime;
	D2D1_COLOR_F			_clearColor;
	TextRenderer*			_textRenderer;
	IDWriteTextFormat*		_fpsFormat;
	IDWriteTextLayout*		_fpsLayout;
	ID2D1SolidColorBrush*	_solidBrush;
	ID2D1HwndRenderTarget*	_renderTarget;

	static ID2D1Factory*		_d2dFactory;
	static IWICImagingFactory*	_imagingFactory;
	static IDWriteFactory*		_writeFactory;
	static ID2D1StrokeStyle*	_miterStrokeStyle;
	static ID2D1StrokeStyle*	_bevelStrokeStyle;
	static ID2D1StrokeStyle*	_roundStrokeStyle;
	static Renderer *			_instance;
};


// ����������
class GC
{
public:
	// ��ȡ GC ʵ��
	static GC * getInstance();

	// �Զ��ͷ�
	void autorelease(
		Ref* ref
	);

	// ��ȫ���ͷŶ���
	void safeRelease(
		Ref* ref
	);

	// ˢ���ڴ��
	void flush();

	// �����ڴ���е����ж���
	void clear();

private:
	GC();

	~GC();

	E2D_DISABLE_COPY(GC);

private:
	bool _notifyed;
	bool _cleanup;
	std::set<Ref*> _pool;

	static GC _instance;
};

}