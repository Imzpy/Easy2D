#include "..\e2dbase.h"
#include "..\e2dmanager.h"
#include <imm.h>
#pragma comment (lib ,"imm32.lib")


e2d::Window * e2d::Window::_instance = nullptr;

e2d::Window::Window()
	: _hWnd(nullptr)
	, _size(640, 480)
	, _title(L"Easy2D Game")
	, _iconID(0)
{
}

e2d::Window::~Window()
{
	// �رտ���̨
	if (::GetConsoleWindow())
	{
		::FreeConsole();
	}
	// �رմ���
	if (_hWnd)
	{
		::DestroyWindow(_hWnd);
		_hWnd = nullptr;
	}
}

e2d::Window * e2d::Window::getInstance()
{
	if (!_instance)
		_instance = new (std::nothrow) Window;
	return _instance;
}

void e2d::Window::destroyInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}

bool e2d::Window::createMutex(const String & mutex)
{
	if (mutex.isEmpty())
		return false;

	// �������̻�����
	String fullMutexName = L"Easy2DApp-" + mutex;
	HANDLE hMutex = ::CreateMutex(nullptr, TRUE, (LPCWSTR)fullMutexName);

	if (hMutex == nullptr)
	{
		WARN("CreateMutex Failed!");
		return false;
	}
	else if (::GetLastError() == ERROR_ALREADY_EXISTS)
	{
		// �رս��̻�����
		::CloseHandle(hMutex);
		// ����Ϸ����
		if (!this->_title.isEmpty())
		{
			// ��ȡ���ھ��
			HWND hProgramWnd = ::FindWindow(L"Easy2DApp", (LPCTSTR)this->_title);
			if (hProgramWnd)
			{
				// ��ȡ������ʾ״̬
				WINDOWPLACEMENT wpm;
				::GetWindowPlacement(hProgramWnd, &wpm);
				// �����еĳ��򴰿ڻ�ԭ������״̬
				wpm.showCmd = SW_SHOW;
				::SetWindowPlacement(hProgramWnd, &wpm);
				::SetWindowPos(hProgramWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			}
		}
		return false;
	}
	return true;
}

HWND e2d::Window::__create()
{
	// ע�ᴰ����
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = L"Easy2DApp";
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Window::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);

	if (this->_iconID != 0)
	{
		wcex.hIcon = (HICON)::LoadImage(
			HINST_THISCOMPONENT,
			MAKEINTRESOURCE(this->_iconID),
			IMAGE_ICON,
			0,
			0,
			LR_DEFAULTCOLOR | LR_CREATEDIBSECTION | LR_DEFAULTSIZE
		);
	}
	else
	{
		wcex.hIcon = nullptr;
	}

	RegisterClassEx(&wcex);

	// ��Ϊ CreateWindow ����ʹ�õ������ش�С����ȡϵͳ�� DPI ��ʹ��
	// ��Ӧ��������
	float dpiScaleX = 0.f, dpiScaleY = 0.f;
	Renderer::getFactory()->GetDesktopDpi(&dpiScaleX, &dpiScaleY);

	int nWidth = static_cast<int>(ceil(this->_size.width * dpiScaleX / 96.f));
	int nHeight = static_cast<int>(ceil(this->_size.height * dpiScaleY / 96.f));

	// ���㴰�ڴ�С
	DWORD dwStyle = WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX &~WS_THICKFRAME;
	RECT wr = { 0, 0, static_cast<LONG>(nWidth), static_cast<LONG>(nHeight) };
	::AdjustWindowRectEx(&wr, dwStyle, FALSE, NULL);
	// ��ȡ�µĿ��
	nWidth = static_cast<int>(wr.right - wr.left);
	nHeight = static_cast<int>(wr.bottom - wr.top);

	// ��ȡ��Ļ�ֱ���
	int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

	// ��������
	HWND hWnd = ::CreateWindowEx(
		NULL,
		L"Easy2DApp",
		(LPCTSTR)this->_title,
		dwStyle,
		(screenWidth - nWidth) / 2, (screenHeight - nHeight) / 2,
		nWidth, nHeight,
		nullptr,
		nullptr,
		HINST_THISCOMPONENT,
		nullptr
	);

	HRESULT hr = hWnd ? S_OK : E_FAIL;

	if (SUCCEEDED(hr))
	{
		// �������뷨
		this->setTypewritingEnabled(false);
		// ���ÿ���̨�رհ�ť
		HWND consoleHWnd = ::GetConsoleWindow();
		if (consoleHWnd)
		{
			HMENU hmenu = ::GetSystemMenu(consoleHWnd, FALSE);
			::RemoveMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
		}
	}
	else
	{
		::UnregisterClass(L"Easy2DApp", HINST_THISCOMPONENT);
	}
	return hWnd;
}

void e2d::Window::poll()
{
	while (::PeekMessage(&_msg, nullptr, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&_msg);
		::DispatchMessage(&_msg);
	}
}

double e2d::Window::getWidth()
{
	return _size.width;
}

double e2d::Window::getHeight()
{
	return _size.height;
}

e2d::Size e2d::Window::getSize()
{
	return _size;
}

e2d::String e2d::Window::getTitle()
{
	return _title;
}

HWND e2d::Window::getHWnd()
{
	if (!_hWnd)
	{
		_hWnd = this->__create();
		if (_hWnd == nullptr)
		{
			throw SystemException(L"ע�ᴰ��ʧ��");
		}
	}
	return _hWnd;
}

void e2d::Window::setSize(int width, int height)
{
	this->_size = Size(width, height);
	if (_hWnd)
	{
		// ���㴰�ڴ�С
		DWORD dwStyle = WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX &~WS_THICKFRAME;
		RECT wr = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
		::AdjustWindowRectEx(&wr, dwStyle, FALSE, NULL);
		// ��ȡ�µĿ��
		width = static_cast<int>(wr.right - wr.left);
		height = static_cast<int>(wr.bottom - wr.top);
		// ��ȡ��Ļ�ֱ���
		int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);
		// ������Ĵ��ڴ�С�ȷֱ��ʴ�ʱ����������
		WARN_IF(screenWidth < width || screenHeight < height, "The window is larger than screen!");
		// ȡ��Сֵ
		width = std::min(width, screenWidth);
		height = std::min(height, screenHeight);
		// �޸Ĵ��ڴ�С�������ô�������Ļ����
		::MoveWindow(_hWnd, (screenWidth - width) / 2, (screenHeight - height) / 2, width, height, TRUE);
	}
}

void e2d::Window::setTitle(const String& title)
{
	this->_title = title;
	if (_hWnd)
	{
		::SetWindowText(_hWnd, (LPCWSTR)title);
	}
}

void e2d::Window::setIcon(int iconID)
{
	this->_iconID = iconID;
	if (_hWnd)
	{
		HICON hIcon = (HICON)::LoadImage(HINST_THISCOMPONENT, MAKEINTRESOURCE(iconID), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
		// ���ô��ڵ�ͼ��
		::SendMessage(_hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		::SendMessage(_hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	}
}

void e2d::Window::setCursor(Cursor cursor)
{
	LPCWSTR pCursorName = nullptr;
	switch (cursor)
	{
	case Cursor::Normal:
		pCursorName = IDC_ARROW;
		break;

	case Cursor::Hand:
		pCursorName = IDC_HAND;
		break;

	case Cursor::No:
		pCursorName = IDC_NO;
		break;

	case Cursor::Wait:
		pCursorName = IDC_WAIT;
		break;

	case Cursor::ArrowWait:
		pCursorName = IDC_APPSTARTING;
		break;

	default:
		break;
	}

	HCURSOR hCursor = ::LoadCursor(nullptr, pCursorName);
	::SetCursor(hCursor);
}

void e2d::Window::setConsoleEnabled(bool enabled)
{
	// �����Ѵ��ڵĿ���̨���
	HWND hwnd = ::GetConsoleWindow();
	// �رտ���̨
	if (enabled)
	{
		if (hwnd)
		{
			::ShowWindow(hwnd, SW_SHOWNORMAL);
		}
		else
		{
			// ��ʾһ���¿���̨
			if (::AllocConsole())
			{
				hwnd = ::GetConsoleWindow();
				// �ض����������
				FILE * stdoutStream, * stdinStream, * stderrStream;
				freopen_s(&stdoutStream, "conout$", "w+t", stdout);
				freopen_s(&stdinStream, "conin$", "r+t", stdin);
				freopen_s(&stderrStream, "conout$", "w+t", stderr);
				// ���ÿ���̨�رհ�ť
				HMENU hmenu = ::GetSystemMenu(hwnd, FALSE);
				::RemoveMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
			}
			else
			{
				this->error(L"Alloc Console Failed!");
			}
		}
	}
	else 
	{
		if (hwnd)
		{
			::ShowWindow(hwnd, SW_HIDE);
		}
	}
}

void e2d::Window::setTypewritingEnabled(bool enabled)
{
	static HIMC hImc = nullptr;

	if (enabled)
	{
		if (hImc != nullptr)
		{
			::ImmAssociateContext(_hWnd, hImc);
			hImc = nullptr;
		}
	}
	else
	{
		if (hImc == nullptr)
		{
			hImc = ::ImmAssociateContext(_hWnd, nullptr);
		}
	}
}

void e2d::Window::info(const String & text, const String & title)
{
	Game::getInstance()->pause();
	::MessageBox(_hWnd, (LPCWSTR)text, (LPCWSTR)title, MB_ICONINFORMATION | MB_OK);
	Game::getInstance()->resume();
}

void e2d::Window::warning(const String& title, const String& text)
{
	Game::getInstance()->pause();
	::MessageBox(_hWnd, (LPCWSTR)text, (LPCWSTR)title, MB_ICONWARNING | MB_OK);
	Game::getInstance()->resume();
}

void e2d::Window::error(const String & text, const String & title)
{
	Game::getInstance()->pause();
	::MessageBox(_hWnd, (LPCWSTR)text, (LPCWSTR)title, MB_ICONERROR | MB_OK);
	Game::getInstance()->resume();
}


LRESULT e2d::Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	bool hasHandled = false;

	switch (message)
	{

	// �����ڴ�С�仯��Ϣ
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);

		if (wParam == SIZE_RESTORED)
		{
			Window::getInstance()->_size = Size(width, height);
		}

		// ���������յ�һ�� WM_SIZE ��Ϣ�����������������Ⱦ
		// Ŀ���ʵ��������ܻ����ʧ�ܣ�����������Ժ����п��ܵ�
		// ������Ϊ�����������һ�ε��� EndDraw ʱ����
		auto pRT = Renderer::getInstance()->getRenderTarget();
		if (pRT)
		{
			pRT->Resize(D2D1::SizeU(width, height));
		}
	}
	break;

	// �����ڱ���仯��Ϣ
	case WM_SETTEXT:
	{
		Window::getInstance()->_title = (const wchar_t*)lParam;
	}
	break;

	// ����ֱ��ʱ仯��Ϣ
	case WM_DISPLAYCHANGE:
	{
		// �ػ�ͻ���
		InvalidateRect(hWnd, nullptr, FALSE);
	}
	result = 0;
	hasHandled = true;
	break;

	// �ػ洰��
	case WM_PAINT:
	{
		e2d::Renderer::getInstance()->render();
		ValidateRect(hWnd, nullptr);
	}
	result = 0;
	hasHandled = true;
	break;

	// ���ڹر���Ϣ
	case WM_CLOSE:
	{
		e2d::Scene * pCurrentScene = e2d::SceneManager::getInstance()->getCurrentScene();
		if (!pCurrentScene || pCurrentScene->onCloseWindow())
		{
			e2d::Game::getInstance()->quit();
		}
	}
	result = 0;
	hasHandled = true;
	break;

	// ����������Ϣ
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	result = 1;
	hasHandled = true;
	break;

	}

	if (!hasHandled)
	{
		result = DefWindowProc(hWnd, message, wParam, lParam);
	}

	return result;
}