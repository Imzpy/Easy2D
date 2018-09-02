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

	static Window * _instance;
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

	// ��ʾ������ FPS
	// Ĭ�ϣ�����
	void showFps(
		bool show
	);

	// ��ʼ��Ⱦ
	void beginDraw();

	// ������Ⱦ
	void endDraw();

	// ��ȡ������Ⱦ��
	TextRenderer * getTextRenderer() const { return _textRenderer; }

	// ��ȡ ID2D1HwndRenderTarget ����
	ID2D1HwndRenderTarget * getRenderTarget() const { return _renderTarget; }

	// ��ȡ ID2D1SolidColorBrush ����
	ID2D1SolidColorBrush * getSolidColorBrush() const { return _solidBrush; }

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

protected:
	Renderer();

	~Renderer();

	E2D_DISABLE_COPY(Renderer);

protected:
	bool					_showFps;
	int						_renderTimes;
	Time					_lastRenderTime;
	D2D1_COLOR_F			_clearColor;
	TextRenderer*			_textRenderer;
	IDWriteTextFormat*		_fpsFormat;
	IDWriteTextLayout*		_fpsLayout;
	ID2D1SolidColorBrush*	_solidBrush;
	ID2D1HwndRenderTarget*	_renderTarget;

	static ID2D1Factory*		_factory;
	static IWICImagingFactory*	_imagingFactory;
	static IDWriteFactory*		_writeFactory;
	static ID2D1StrokeStyle*	_miterStrokeStyle;
	static ID2D1StrokeStyle*	_bevelStrokeStyle;
	static ID2D1StrokeStyle*	_roundStrokeStyle;
	static Renderer *			_instance;
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

protected:
	Input();

	~Input();

	E2D_DISABLE_COPY(Input);

protected:
	IDirectInput8W * _directInput;
	IDirectInputDevice8W* _keyboardDevice;
	IDirectInputDevice8W* _mouseDevice;
	DIMOUSESTATE _mouseState;
	char _keyBuffer[256];

	static Input * _instance;
};


// ��Ƶ�豸
class Audio
{
public:
	// ��ȡ��Ƶ�豸ʵ��
	static Audio * getInstance();

	// ����ʵ��
	static void destroyInstance();

	// ��ȡ XAudio2 ʵ������
	IXAudio2 * getXAudio2();

	// ��ȡ MasteringVoice ʵ������
	IXAudio2MasteringVoice* getMasteringVoice();

protected:
	Audio();

	virtual ~Audio();

	E2D_DISABLE_COPY(Audio);

protected:
	IXAudio2 * _xAudio2;
	IXAudio2MasteringVoice* _masteringVoice;

	static Audio * _instance;
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

	// ��Ϸ�Ƿ���ͣ
	bool isPaused();

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
	Scene * getCurrentScene();

	// ��ȡ����ջ
	const std::stack<Scene*>& getSceneStack();

	// �Ƿ����ڽ��г�������
	bool isTransitioning() const;

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
	Timer*		_timer;
	Scene*		_currScene;
	Scene*		_nextScene;
	Transition*	_transition;
	Window*		_window;
	Input*		_input;
	Renderer*	_renderer;
	ActionManager* _actionManager;
	std::stack<Scene*> _scenes;

	static Game * _instance;
};


// �������ճ�
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