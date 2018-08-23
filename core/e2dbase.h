#pragma once
#include "e2dmacros.h"
#include "e2dcommon.h"
#include "e2dcustom.h"


// Base Classes

namespace e2d
{


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
	Window& size(
		int width,			/* ������ */
		int height			/* ����߶� */
	);

	// ���ô������
	Window& title(
		const String& title	/* ������� */
	);

	// ���ô���ͼ��
	Window& icon(
		int iconID
	);

	// �������ָ����ʽ
	Window& cursor(
		Cursor c
	);

	// ��ȡ�������
	const String& title() const;

	// ��ȡ������
	int width() const;

	// ��ȡ����߶�
	int height() const;

	// ��ȡ�����С
	Size size() const;

	// ��ȡ���� DPI
	float dpi() const;

	// ��ȡ���ھ��
	HWND hWnd() const;

	// �򿪻����ؿ���̨
	Window& showConsole(
		bool enabled
	);

	// �Ƿ�������Ӧ���뷨
	Window& typewritingEnabled(
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
	// ���ݿͻ�����С��λ����
	Rect _locate(
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
	float mouseX();

	// ������Y������ֵ
	float mouseY();

	// ����������ֵ
	Point mousePos();

	// ������X����������
	float mouseDeltaX();

	// ������Y����������
	float mouseDeltaY();

	// ������Z�ᣨ�����֣���������
	float mouseDeltaZ();

	// ��ʼ�������豸
	void initWithWindow(
		Window * window
	);

	// ˢ�������豸״̬
	void update();

private:
	IDirectInput8W* _directInput;
	IDirectInputDevice8W* _keyboardDevice;
	IDirectInputDevice8W* _mouseDevice;
	DIMOUSESTATE _mouseState;
	char _keyBuffer[256];
};


// ��Ⱦ��
class Renderer
{
public:
	Renderer();

	~Renderer();

	// ��ȡ����ɫ
	Color backgroundColor();

	// �޸ı���ɫ
	void backgroundColor(
		const Color& color
	);

	// ��ʾ������ FPS
	// Ĭ�ϣ�����
	void showFps(
		bool show
	);

	// ��ȡ������Ⱦ��
	TextRenderer * textRenderer() const { return _textRenderer; }

	// ��ȡ ID2D1HwndRenderTarget ����
	ID2D1HwndRenderTarget * renderTarget() const { return _renderTarget; }

	// ��ȡ ID2D1SolidColorBrush ����
	ID2D1SolidColorBrush * solidBrush() const { return _solidBrush; }

	// ��ȡ ID2D1Factory ����
	ID2D1Factory * factory() const { return _factory; }

	// ��ȡ IWICImagingFactory ����
	IWICImagingFactory * imagingFactory() const { return _imagingFactory; }

	// ��ȡ IDWriteFactory ����
	IDWriteFactory * writeFactory() const { return _writeFactory; }

	// ��ȡ Miter ��ʽ�� ID2D1StrokeStyle
	ID2D1StrokeStyle * miterStrokeStyle();

	// ��ȡ Bevel ��ʽ�� ID2D1StrokeStyle
	ID2D1StrokeStyle * bevelStrokeStyle();

	// ��ȡ Round ��ʽ�� ID2D1StrokeStyle
	ID2D1StrokeStyle * roundStrokeStyle();

	// ��ʼ����Ⱦ��
	void initWithWindow(
		Window * window
	);

	// ��ʼ��Ⱦ
	void beginDraw();

	// ������Ⱦ
	void endDraw();

private:
	bool					_showFps;
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


class Timer;
class ActionManager;
class Scene;
class Transition;

// ��Ϸ
class Game
{
public:
	// ��ȡ Game ʵ��
	static Game * instance();

	// ��ʼ��
	void initWithWindow(
		Window * window
	);

	// ��ȡ����
	Window * window() const { return _window; }

	// ��ȡ�����豸
	Input * input() const { return _input; }

	// ��ȡͼ���豸
	Renderer * renderer() const { return _renderer; }

	// ������Ϸ
	void start();

	// ��ͣ��Ϸ
	void pause();

	// ������Ϸ
	void resume();

	// ������Ϸ
	void quit();

	// ��Ϸ�Ƿ���ͣ
	bool paused();

	// ������ջ
	void pushScene(
		Scene * scene,					/* ��һ��������ָ�� */
		bool saveCurrentScene = true	/* �Ƿ񱣴浱ǰ���� */
	);

	// ������ջ
	void pushScene(
		Transition * transition,		/* �������� */
		bool saveCurrentScene = true	/* �Ƿ񱣴浱ǰ���� */
	);

	// ������ջ
	Scene* popScene();

	// ������ջ
	Scene* popScene(
		Transition * transition			/* �������� */
	);

	// ��ձ�������г���
	void clearAllScenes();

	// ��ȡ��ǰ����
	Scene * currentScene();

	// ��ȡ����ջ
	const std::stack<Scene*>& sceneStack();

	// �Ƿ����ڽ��г�������
	bool transitioning() const;

	// ���³�������
	void updateScene();

	// ��Ⱦ��������
	void drawScene();

protected:
	Game();

	~Game();

	E2D_DISABLE_COPY(Game);

private:
	bool		_quit;
	bool		_paused;
	Window*		_window;
	Input*		_input;
	Renderer*	_renderer;
	Timer*		_timer;
	Scene*		_currScene;
	Scene*		_nextScene;
	Transition*	_transition;
	ActionManager*		_actionManager;
	std::stack<Scene*>	_scenes;
};


// �������ճ�
class GC
{
public:
	// ��ȡ GC ʵ��
	static GC * instance();

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
};

}