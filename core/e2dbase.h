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
	Window(
		const String& title,	/* ������� */
		int width,				/* ������ */
		int height,				/* ����߶� */
		int iconID = 0			/* ����ͼ�� */
	);

	~Window();

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
	String getTitle() const;

	// ��ȡ������
	int getWidth() const;

	// ��ȡ����߶�
	int getHeight() const;

	// ��ȡ�����С
	Size getSize() const;

	// ��ȡ���� DPI
	float getDpi() const;

	// ��ȡ���ھ��
	HWND getHWnd() const;

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
	// ���ݿͻ�����С������ʵĴ�������
	Rect __adjustWindow(
		int width,
		int height
	);

	// Win32 ������Ϣ�ص�����
	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam
	);

private:
	HWND	_hWnd;
	MSG		_msg;
	int		_width;
	int		_height;
	String	_title;
	int		_iconID;
	float	_dpi;
};


// �����豸
class Input
{
public:
	Input();

	~Input();

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

	// ��ʼ����Ⱦ������Ӧ�ֶ����øú�����
	void init(
		Window * window
	);

private:
	IDirectInput8W* _directInput;
	IDirectInputDevice8W* _keyboardDevice;
	IDirectInputDevice8W* _mouseDevice;
	DIMOUSESTATE _mouseState;
	char _keyBuffer[256];
};


// ͼ���豸
class Renderer
{
public:
	Renderer();

	~Renderer();

	// ��ȡ����ɫ
	Color getBackgroundColor();

	// �޸ı���ɫ
	void setBackgroundColor(
		Color color
	);

	// ��Ⱦ��Ϸ����
	void render();

	// ��ȡ������Ⱦ��
	TextRenderer * getTextRenderer() const { return _textRenderer; }

	// ��ȡ ID2D1HwndRenderTarget ����
	ID2D1HwndRenderTarget * getRenderTarget() const { return _renderTarget; }

	// ��ȡ ID2D1SolidColorBrush ����
	ID2D1SolidColorBrush * getSolidColorBrush() const { return _solidBrush; }

	// ��ȡ ID2D1Factory ����
	ID2D1Factory * getFactory() const { return _factory; }

	// ��ȡ IWICImagingFactory ����
	IWICImagingFactory * getImagingFactory() const { return _imagingFactory; }

	// ��ȡ IDWriteFactory ����
	IDWriteFactory * getWriteFactory() const { return _writeFactory; }

	// ��ȡ Miter ��ʽ�� ID2D1StrokeStyle
	ID2D1StrokeStyle * getMiterStrokeStyle();

	// ��ȡ Bevel ��ʽ�� ID2D1StrokeStyle
	ID2D1StrokeStyle * getBevelStrokeStyle();

	// ��ȡ Round ��ʽ�� ID2D1StrokeStyle
	ID2D1StrokeStyle * getRoundStrokeStyle();

	// ��ʼ����Ⱦ������Ӧ�ֶ����øú�����
	void init(
		Window * window
	);

private:
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
	ID2D1Factory*			_factory;
	IWICImagingFactory*		_imagingFactory;
	IDWriteFactory*			_writeFactory;
	ID2D1StrokeStyle*		_miterStrokeStyle;
	ID2D1StrokeStyle*		_bevelStrokeStyle;
	ID2D1StrokeStyle*		_roundStrokeStyle;
};


// ��Ϸ
class Game
{
public:
	// ��ȡ Game ʵ��
	static Game * getInstance();

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
	const Config& getConfig() const;

	// ���ô���
	void setWindow(
		Window * window
	);

	// ��ȡ����
	Window * getWindow() const { return _window; }

	// ��ȡ�����豸
	Input * getInput() const { return _input; }

	// ��ȡͼ���豸
	Renderer * getRenderer() const { return _renderer; }

protected:
	Game();

	~Game();

	E2D_DISABLE_COPY(Game);

private:
	bool		_quit;
	bool		_paused;
	Config		_config;
	Window *	_window;
	Input *		_input;
	Renderer *	_renderer;
	
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