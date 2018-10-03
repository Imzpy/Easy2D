#pragma once
#include "e2dimpl.h"
#include "e2dobject.h"
#include "e2dtransition.h"


namespace e2d
{

	// ͼ���豸
	class Graphics
	{
	public:
		Graphics(
			HWND hwnd
		);

		~Graphics();

		// ��ʼ��Ⱦ
		void BeginDraw();

		// ������Ⱦ
		void EndDraw();

		// ��Ⱦ������Ϣ
		void DrawDebugInfo();

		// ��ȡ ID2D1Factory ����
		ID2D1Factory * GetFactory() const;

		// ��ȡ IWICImagingFactory ����
		IWICImagingFactory * GetImagingFactory() const;

		// ��ȡ IDWriteFactory ����
		IDWriteFactory * GetWriteFactory() const;

		// ��ȡ ID2D1HwndRenderTarget ����
		ID2D1HwndRenderTarget * GetRenderTarget() const;

		// ��ȡ ID2D1SolidColorBrush ����
		ID2D1SolidColorBrush * GetSolidBrush() const;

		// ��ȡ������Ⱦ����
		E2DTextRender * GetTextRender() const;

		// ��ȡ Miter ��ʽ�� ID2D1StrokeStyle
		ID2D1StrokeStyle * GetMiterStrokeStyle();

		// ��ȡ Bevel ��ʽ�� ID2D1StrokeStyle
		ID2D1StrokeStyle * GetBevelStrokeStyle();

		// ��ȡ Round ��ʽ�� ID2D1StrokeStyle
		ID2D1StrokeStyle * GetRoundStrokeStyle();

	protected:
		D2D1_COLOR_F			clear_color_;
		ID2D1Factory*			factory_;
		IWICImagingFactory*		imaging_factory_;
		IDWriteFactory*			write_factory_;
		ID2D1StrokeStyle*		miter_stroke_style_;
		ID2D1StrokeStyle*		bevel_stroke_style_;
		ID2D1StrokeStyle*		round_stroke_style_;
		E2DTextRender*			text_renderer_;
		IDWriteTextFormat*		fps_text_format_;
		IDWriteTextLayout*		fps_text_layout_;
		ID2D1SolidColorBrush*	solid_brush_;
		ID2D1HwndRenderTarget*	render_target_;
	};


	// �����豸
	class Input
	{
	public:
		Input(
			HWND hwnd
		);

		~Input();

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

		// ˢ���豸״̬
		void Flush();

	protected:
		IDirectInput8W *		direct_input_;
		IDirectInputDevice8W*	keyboard_device_;
		IDirectInputDevice8W*	mouse_device_;
		DIMOUSESTATE			mouse_state_;
		char					key_buffer_[256];
	};

	// ��Ƶ�豸
	class Audio
	{
	public:
		Audio();

		~Audio();

		// �����豸
		void Open();

		// �ر��豸
		void Close();

		// ������Դ
		HRESULT CreateVoice(
			IXAudio2SourceVoice ** voice,
			WAVEFORMATEX * wfx,
			VoiceCallback * callback
		);

	protected:
		IXAudio2 * x_audio2_;
		IXAudio2MasteringVoice*	mastering_voice_;
	};


	// �豸
	class Device
	{
	public:
		// ��ȡͼ���豸
		static Graphics * GetGraphics();

		// ��ȡ�����豸
		static Input * GetInput();

		// ��ȡ��Ƶ�豸
		static Audio * GetAudio();

		// ��ʼ��
		static void Init(
			HWND hwnd
		);

		// ������Դ
		static void Destroy();
	};


	// ����ѡ��
	struct Options
	{
		String	title;		// ����
		int		width;		// ���
		int		height;		// �߶�
		int		icon;		// ͼ����Դ ID
		bool	debug_mode;	// ����ģʽ

		Options()
			: title(L"Easy2D Game")
			, width(640)
			, height(480)
			, icon(0)
			, debug_mode(false)
		{
		}
	};


	// ��Ϸ������
	class Game
	{
	public:
		// ��ʼ
		virtual void Start() = 0;

		// ����
		void Run(
			const Options& options = Options()
		);

		// ����
		void Quit();

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

		// ��ȡʵ��
		static Game * GetInstance();

	protected:
		Game();

		~Game();

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

	protected:
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
	};

}
