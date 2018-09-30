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
		// �������ָ����ʽ
		static void SetCursor(
			Cursor cursor
		);

		// �򿪻����ؿ���̨
		static void ShowConsole(
			bool enabled
		);

		// ��������
		// ����ֵ�������ڰ���ȡ����ťʱ������ֵ��ʾ�û��Ƿ���ȷ�ϰ�ť
		static bool Popup(
			const String& text,					/* �������� */
			const String& title,				/* ���ڱ��� */
			PopupStyle style = PopupStyle::Info,/* ������ʽ */
			bool has_cancel = false				/* ����ȡ����ť */
		);

		// ��ȡ��Ļ��С
		static Size GetScreenSize();
	};


	// ��Ⱦ��
	class Graphics
	{
	public:
		// ��ȡ��Ⱦ��ʵ��
		static Graphics * Get();

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

		// ��ʾ������ FPS
		// Ĭ�ϣ�����
		void ShowFps(
			bool show
		);

		// ��ʼ��Ⱦ
		void BeginDraw();

		// ������Ⱦ
		void EndDraw();

		// ��Ⱦ������Ϣ
		void DrawDebugInfo();

	protected:
		Graphics();

		~Graphics();

		E2D_DISABLE_COPY(Graphics);

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
		static Graphics *			instance_;
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
		static Audio * Get();

		// ��ȡ XAudio2 ʵ������
		IXAudio2 * GetXAudio2() const;

		// ��ȡ MasteringVoice ʵ������
		IXAudio2MasteringVoice* GetMasteringVoice() const;

	protected:
		Audio();

		virtual ~Audio();

		E2D_DISABLE_COPY(Audio);

	protected:
		IXAudio2 * x_audio2_;
		IXAudio2MasteringVoice*	mastering_voice_;
	};


	// ѡ��
	struct Option
	{
		String	title;				// ���ڱ���
		int		width;				// ���ڿ��
		int		height;				// ���ڸ߶�
		int		icon;				// ����ͼ��
		Color	background_color;	// ����ɫ
		bool	debug_mode;			// Debug ģʽ

		Option()
			: title(L"Easy2D Game")
			, width(640)
			, height(480)
			, icon(0)
			, background_color(Color::Black)
			, debug_mode(false)
		{
		}
	};


	// ��Ϸ������
	class Game
	{
	public:
		static Game * New(
			const Option& option
		);

		// ��ȡ������
		static Game * Get();

		// ������Ϸ
		void Run();

		// ������Ϸ
		void Quit();

		// ��ȡ�������
		const String& GetTitle() const;

		// ��ȡ������
		int GetWidth() const;

		// ��ȡ����߶�
		int GetHeight() const;

		// ��ȡ�����С
		Size GetSize() const;

		// ��ȡ���ھ��
		HWND GetHWnd() const;

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

		// ��ʼ��
		void Init();

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
		HWND		hwnd_;
		String		title_;
		int			width_;
		int			height_;
		int			icon_;
		bool		debug_mode_;
		bool		quit_;
		Scene*		curr_scene_;
		Scene*		next_scene_;
		Transition*	transition_;

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
