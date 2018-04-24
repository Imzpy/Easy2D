#include "..\e2dtool.h"
#include "..\e2dmanager.h"

using namespace e2d;

#define MUSIC_CLASS_NAME L"Easy2DMusicCallbackWnd"

static HINSTANCE s_hInstance = nullptr;


bool e2d::Music::__init()
{
	s_hInstance = HINST_THISCOMPONENT;

	WNDCLASS  wc;
	wc.style = 0;
	wc.lpfnWndProc = Music::MusicProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = s_hInstance;
	wc.hIcon = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = MUSIC_CLASS_NAME;

	if (!RegisterClass(&wc) && 1410 != GetLastError())
	{
		return false;
	}
	return true;
}

e2d::Music::Music()
	: m_wnd(NULL)
	, m_dev(0L)
	, m_nMusicID(0)
	, m_bPlaying(false)
	, m_nRepeatTimes(0)
{
	m_wnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		MUSIC_CLASS_NAME,
		NULL,
		WS_POPUPWINDOW,
		0, 0, 0, 0,
		NULL,
		NULL,
		s_hInstance,
		NULL);

	if (m_wnd)
	{
		SetWindowLongPtr(m_wnd, GWLP_USERDATA, (LONG_PTR)this);
	}
}

e2d::Music::~Music()
{
	close();
	DestroyWindow(m_wnd);
}

bool e2d::Music::open(String pFileName)
{
	if (pFileName.isEmpty())
		return false;

	close();

	MCI_OPEN_PARMS mciOpen = { 0 };
	mciOpen.lpstrDeviceType = 0;
	mciOpen.lpstrElementName = pFileName;

	MCIERROR mciError;
	mciError = mciSendCommand(
		0,
		MCI_OPEN,
		MCI_OPEN_ELEMENT,
		reinterpret_cast<DWORD_PTR>(&mciOpen)
	);

	if (mciError == 0)
	{
		m_dev = mciOpen.wDeviceID;
		m_nMusicID = pFileName.getHashCode();
		m_bPlaying = false;
		return true;
	}
	return false;
}

bool e2d::Music::play(int nLoopCount)
{
	if (!m_dev)
	{
		return false;
	}

	MCI_PLAY_PARMS mciPlay = { 0 };
	mciPlay.dwCallback = reinterpret_cast<DWORD_PTR>(m_wnd);

	// 播放声音
	MCIERROR mciError = mciSendCommand(
		m_dev,
		MCI_PLAY,
		MCI_FROM | MCI_NOTIFY,
		reinterpret_cast<DWORD_PTR>(&mciPlay)
	);

	if (!mciError)
	{
		m_bPlaying = true;
		m_nRepeatTimes = nLoopCount;
		return true;
	}
	return false;
}

void e2d::Music::close()
{
	if (m_bPlaying)
	{
		stop();
	}

	if (m_dev)
	{
		__sendCommand(MCI_CLOSE);
	}

	m_dev = 0;
	m_bPlaying = false;
}

void e2d::Music::pause()
{
	__sendCommand(MCI_PAUSE);
	m_bPlaying = false;
}

void e2d::Music::resume()
{
	__sendCommand(MCI_RESUME);
	m_bPlaying = true;
}

void e2d::Music::stop()
{
	__sendCommand(MCI_STOP);
	m_bPlaying = false;
}

bool e2d::Music::isPlaying() const
{
	return m_bPlaying;
}

double Music::getVolume() const
{
	return 1.0f;
}

bool Music::setVolume(double fVolume)
{
	return false;
}

double Music::getFrequencyRatio() const
{
	return 1.0f;
}

bool Music::setFrequencyRatio(double fFrequencyRatio)
{
	return false;
}

void e2d::Music::__sendCommand(int nCommand, DWORD_PTR param1, DWORD_PTR parma2)
{
	// 空设备时忽略这次操作
	if (!m_dev)
	{
		return;
	}
	// 向当前设备发送操作
	mciSendCommand(m_dev, nCommand, param1, parma2);
}


LRESULT WINAPI e2d::Music::MusicProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	e2d::Music * pPlayer = NULL;

	if (Msg == MM_MCINOTIFY
		&& wParam == MCI_NOTIFY_SUCCESSFUL
		&& (pPlayer = (Music *)GetWindowLongPtr(hWnd, GWLP_USERDATA)))
	{
		if (pPlayer->m_nRepeatTimes > 0)
		{
			pPlayer->m_nRepeatTimes--;
		}

		if (pPlayer->m_nRepeatTimes)
		{
			mciSendCommand(static_cast<MCIDEVICEID>(lParam), MCI_SEEK, MCI_SEEK_TO_START, 0);

			MCI_PLAY_PARMS mciPlay = { 0 };
			mciPlay.dwCallback = reinterpret_cast<DWORD_PTR>(hWnd);
			mciSendCommand(static_cast<MCIDEVICEID>(lParam), MCI_PLAY, MCI_NOTIFY, reinterpret_cast<DWORD_PTR>(&mciPlay));
		}
		else
		{
			pPlayer->m_bPlaying = false;
			return 0;
		}
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}
