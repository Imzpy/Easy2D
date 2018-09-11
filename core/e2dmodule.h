#pragma once
#include "e2dimpl.h"
#include "e2dobject.h"
#include "e2dtransition.h"


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
		enum class PopupStyle : int
		{
			Info,		/* ��ʾ */
			Warning,	/* ���� */
			Error		/* ���� */
		};

	public:
		// ��ȡ����ʵ��
		static Window * GetInstance();

		// ���ٴ���ʵ��
		static void DestroyInstance();

		// ��ȡ��Ļ��С
		static Size GetScreenSize();

		// ��ȡ�������
		const String& GetTitle() const;

		// ��ȡ������
		int GetWidth() const;

		// ��ȡ����߶�
		int GetHeight() const;

		// ��ȡ�����С
		Size GetSize() const;

		// ��ȡ���� DPI
		float GetDpi() const;

		// ��ȡ���ھ��
		HWND GetHWnd();

		// �޸Ĵ����С
		void SetSize(
			int width,			/* ������ */
			int height			/* ����߶� */
		);

		// ���ô������
		void SetTitle(
			const String& title	/* ������� */
		);

		// ���ô���ͼ��
		void SetIcon(
			int resource_id		/* ͼ����Դ ID */
		);

		// �������ָ����ʽ
		void SetCursor(
			Cursor cursor
		);

		// �򿪻����ؿ���̨
		void SetConsoleEnabled(
			bool enabled
		);

		// �Ƿ�������Ӧ���뷨
		void SetTypewritingEnabled(
			bool enabled
		);

		// ��ⴰ���Ƿ�Ψһ
		// ����ֵ������ false ˵����Ϸ�Ѿ����ڽ��У����Է�ֹ�û�ͬʱ�򿪶����Ϸ����
		bool CheckUnique();

		// ��������
		// ����ֵ�������ڰ���ȡ����ťʱ������ֵ��ʾ�û��Ƿ���ȷ�ϰ�ť
		bool Popup(
			const String& text,					/* �������� */
			const String& title,				/* ���ڱ��� */
			PopupStyle style = PopupStyle::Info,/* ������ʽ */
			bool has_cancel = false				/* ����ȡ����ť */
		);

		// ��������Ϣ
		void Poll();

	private:
		Window();

		~Window();

		E2D_DISABLE_COPY(Window);

		// ���ݿͻ�����С��λ����
		Rect Locate(
			int width,
			int height
		);

		// Win32 ������Ϣ�ص�����
		static LRESULT CALLBACK WndProc(
			HWND hwnd,
			UINT msg,
			WPARAM w_param,
			LPARAM l_param
		);

	private:
		HWND	hwnd_;
		MSG		msg_;
		int		width_;
		int		height_;
		int		icon_id_;
		float	dpi_;
		String	title_;

		static Window * instance_;
	};


	// ��Ⱦ��
	class Renderer
	{
	public:
		// ��ȡ��Ⱦ��ʵ��
		static Renderer * GetInstance();

		// ����ʵ��
		static void DestroyInstance();

		// ��ȡ ID2D1Factory ����
		static ID2D1Factory * GetFactory();

		// ��ȡ IWICImagingFactory ����
		static IWICImagingFactory * GetImagingFactory();

		// ��ȡ IDWriteFactory ����
		static IDWriteFactory * GetWriteFactory();

		// ��ȡ Miter ��ʽ�� ID2D1StrokeStyle
		static ID2D1StrokeStyle * GetMiterStrokeStyle();

		// ��ȡ Bevel ��ʽ�� ID2D1StrokeStyle
		static ID2D1StrokeStyle * GetBevelStrokeStyle();

		// ��ȡ Round ��ʽ�� ID2D1StrokeStyle
		static ID2D1StrokeStyle * GetRoundStrokeStyle();

		// ��ȡ������Ⱦ��
		E2DTextRenderer * GetTextRenderer();

		// ��ȡ ID2D1HwndRenderTarget ����
		ID2D1HwndRenderTarget * GetRenderTarget();

		// ��ȡ ID2D1SolidColorBrush ����
		ID2D1SolidColorBrush * GetSolidBrush();

		// ��ȡ����ɫ
		Color GetBackgroundColor();

		// �޸ı���ɫ
		void SetBackgroundColor(
			const Color& color
		);

		// ��ʾ������ FPS
		// Ĭ�ϣ�����
		void ShowFps(
			bool show
		);

		// ��ʼ��Ⱦ
		void BeginDraw();

		// ������Ⱦ
		void EndDraw();

	protected:
		Renderer();

		~Renderer();

		E2D_DISABLE_COPY(Renderer);

	protected:
		bool					show_fps_;
		int						render_times_;
		Time					last_render_time_;
		D2D1_COLOR_F			clear_color_;
		E2DTextRenderer*		text_renderer_;
		IDWriteTextFormat*		fps_text_format_;
		IDWriteTextLayout*		fps_text_layout_;
		ID2D1SolidColorBrush*	solid_brush_;
		ID2D1HwndRenderTarget*	render_target_;

		static ID2D1Factory*		factory_;
		static IWICImagingFactory*	imaging_factory_;
		static IDWriteFactory*		write_factory_;
		static ID2D1StrokeStyle*	miter_stroke_style_;
		static ID2D1StrokeStyle*	bevel_stroke_style_;
		static ID2D1StrokeStyle*	round_stroke_style_;
		static Renderer *			instance_;
	};


	// �����豸
	class Input
	{
	public:
		// ��ȡ�����豸ʵ��
		static Input * GetInstance();

		// ���������豸ʵ��
		static void DestroyInstance();

		// ������ĳ�����Ƿ���������
		bool IsDown(
			KeyCode key
		);

		// �����갴���Ƿ���������
		bool IsDown(
			MouseCode code
		);

		// ������X������ֵ
		float GetMouseX();

		// ������Y������ֵ
		float GetMouseY();

		// ����������ֵ
		Point GetMousePos();

		// ������X����������
		float GetMouseDeltaX();

		// ������Y����������
		float GetMouseDeltaY();

		// ������Z�ᣨ�����֣���������
		float GetMouseDeltaZ();

		// ˢ�������豸״̬
		void Update();

	protected:
		Input();

		~Input();

		E2D_DISABLE_COPY(Input);

	protected:
		IDirectInput8W *		direct_input_;
		IDirectInputDevice8W*	keyboard_device_;
		IDirectInputDevice8W*	mouse_device_;
		DIMOUSESTATE			mouse_state_;
		char					key_buffer_[256];

		static Input * instance_;
	};


	// ��Ƶ�豸
	class Audio
	{
	public:
		// ��ȡ��Ƶ�豸ʵ��
		static Audio * GetInstance();

		// ����ʵ��
		static void DestroyInstance();

		// ��ȡ XAudio2 ʵ������
		IXAudio2 * GetXAudio2();

		// ��ȡ MasteringVoice ʵ������
		IXAudio2MasteringVoice* GetMasteringVoice();

	protected:
		Audio();

		virtual ~Audio();

		E2D_DISABLE_COPY(Audio);

	protected:
		IXAudio2 * x_audio2_;
		IXAudio2MasteringVoice*	mastering_voice_;

		static Audio * instance_;
	};


	// ��Ϸ
	class Game
	{
	public:
		// ��ȡ Game ʵ��
		static Game * GetInstance();

		// ����ʵ��
		static void DestroyInstance();

		// ������Ϸ
		void Start();

		// ��ͣ��Ϸ
		void Pause();

		// ������Ϸ
		void Resume();

		// ������Ϸ
		void Quit();

		// ��Ϸ�Ƿ���ͣ
		bool IsPaused();

		// �л�����
		void EnterScene(
			Scene * scene,						/* ���� */
			Transition * transition	= nullptr	/* �������� */
		);

		// ��ȡ��ǰ����
		Scene * GetCurrentScene();

		// �Ƿ����ڽ��г�������
		bool IsTransitioning() const;

		// ���³�������
		void UpdateScene();

		// ��Ⱦ��������
		void DrawScene();

	protected:
		Game();

		~Game();

		E2D_DISABLE_COPY(Game);

	private:
		bool			quit_;
		bool			paused_;
		Scene*			curr_scene_;
		Scene*			next_scene_;
		Transition*		transition_;

		static Game * instance_;
	};


	// ��������
	class GC
	{
	private:
		GC();

		~GC();

		E2D_DISABLE_COPY(GC);

		static GC instance_;
	};

}
