#include "..\e2dbase.h"
#include "..\e2dmanager.h"
#include "..\e2dnode.h"
#include <imm.h>
#pragma comment (lib ,"imm32.lib")

#define WINDOW_STYLE	WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME
#define REGISTER_CLASS	L"Easy2DApp"


e2d::Window::Window(const String & title, int width, int height, int iconID)
	: _hWnd(nullptr)
	, _width(width)
	, _height(height)
	, _title(title)
	, _iconID(iconID)
	, _dpi(0.f)
{
	CoInitialize(nullptr);

	// ��ȡϵͳ DPI
	_dpi = static_cast<float>(::GetDpiForSystem());

	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = REGISTER_CLASS;
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = Window::WndProc;
	wcex.hIcon = nullptr;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);

	if (_iconID != 0)
	{
		wcex.hIcon = (HICON)::LoadImage(
			HINST_THISCOMPONENT,
			MAKEINTRESOURCE(_iconID),
			IMAGE_ICON,
			0,
			0,
			LR_DEFAULTCOLOR | LR_CREATEDIBSECTION | LR_DEFAULTSIZE
		);
	}

	// ע�ᴰ����
	RegisterClassEx(&wcex);

	// ���㴰�ڴ�С
	Rect clientRect = _locate(_width, _height);

	// ��������
	_hWnd = ::CreateWindowEx(
		NULL,
		REGISTER_CLASS,
		(LPCTSTR)_title,
		WINDOW_STYLE,
		int(clientRect.origin.x),
		int(clientRect.origin.y),
		int(clientRect.size.width),
		int(clientRect.size.height),
		nullptr,
		nullptr,
		HINST_THISCOMPONENT,
		this
	);

	if (_hWnd)
	{
		// �������뷨
		setTypewritingEnabled(false);
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
		::UnregisterClass(REGISTER_CLASS, HINST_THISCOMPONENT);
		throw SystemException("Create window failed");
	}
}

e2d::Window::~Window()
{
	// �رտ���̨
	if (::GetConsoleWindow())
		::FreeConsole();

	// �رմ���
	if (_hWnd)
		::DestroyWindow(_hWnd);

	CoUninitialize();
}

bool e2d::Window::createMutex(const String & mutex)
{
	if (mutex.isEmpty())
		return false;

	HANDLE hMutex = ::CreateMutex(nullptr, TRUE, LPCWSTR(L"Easy2DApp-" + mutex));

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
			HWND hProgramWnd = ::FindWindow(REGISTER_CLASS, (LPCTSTR)_title);
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

e2d::Rect e2d::Window::_locate(int width, int height)
{
	Rect result;
	RECT wRECT		= { 0, 0, LONG(ceil(width * _dpi / 96.f)), LONG(ceil(height * _dpi / 96.f)) };
	int maxWidth	= ::GetSystemMetrics(SM_CXSCREEN);
	int maxHeight	= ::GetSystemMetrics(SM_CYSCREEN);

	// ������ʵĴ��ڴ�С
	::AdjustWindowRectEx(&wRECT, WINDOW_STYLE, FALSE, NULL);
	width = static_cast<int>(wRECT.right - wRECT.left);
	height = static_cast<int>(wRECT.bottom - wRECT.top);

	// ������Ĵ��ڴ�С�ȷֱ��ʴ�ʱ����������
	WARN_IF(maxWidth < width || maxHeight < height, "The window is larger than screen!");
	width = std::min(width, maxWidth);
	height = std::min(height, maxHeight);

	float x = float((maxWidth - width) / 2), y = float((maxHeight - height) / 2);
	return std::move(Rect(x, y, float(width), float(height)));
}

void e2d::Window::poll()
{
	while (::PeekMessage(&_msg, nullptr, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&_msg);
		::DispatchMessage(&_msg);
	}
}

int e2d::Window::getWidth() const
{
	return _width;
}

int e2d::Window::getHeight() const
{
	return _height;
}

e2d::Size e2d::Window::getSize() const
{
	return Size(float(_width), float(_height));
}

float e2d::Window::getDpi() const
{
	return _dpi;
}

e2d::String e2d::Window::getTitle() const
{
	return _title;
}

HWND e2d::Window::getHWnd() const
{
	return _hWnd;
}

void e2d::Window::setSize(int width, int height)
{
	if (_width == width && _height == height)
		return;

	_width = width;
	_height = height;

	if (_hWnd)
	{
		Rect wRect = _locate(width, height);
		::MoveWindow(
			_hWnd,
			int(wRect.origin.x),
			int(wRect.origin.y),
			int(wRect.size.width),
			int(wRect.size.height),
			TRUE
		);
	}
}

void e2d::Window::setTitle(const String& title)
{
	_title = title;
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

bool e2d::Window::popup(const String & text, const String & title, Popup style, bool hasCancel)
{
	UINT type = 0;
	switch (style)
	{
	case e2d::Window::Popup::Information:
		type = MB_ICONINFORMATION;
		break;
	case e2d::Window::Popup::Warning:
		type = MB_ICONWARNING;
		break;
	case e2d::Window::Popup::Error:
		type = MB_ICONERROR;
		break;
	default:
		break;
	}

	if (hasCancel)
	{
		type |= MB_OKCANCEL;
	}

	Game::getInstance()->pause();
	int ret = ::MessageBox(_hWnd, (LPCWSTR)text, (LPCWSTR)title, type);
	Game::getInstance()->resume();
	return ret == IDOK;
}


LRESULT e2d::Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if (uMsg == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		Window *window = (Window *)pcs->lpCreateParams;

		::SetWindowLongPtrW(
			hWnd,
			GWLP_USERDATA,
			PtrToUlong(window)
		);

		result = 1;
	}
	else
	{
		bool hasHandled = false;
		Window *window = reinterpret_cast<Window *>(
			static_cast<LONG_PTR>(
				::GetWindowLongPtrW(hWnd, GWLP_USERDATA)
			)
		);

		switch (uMsg)
		{

		// ���������Ϣ
		case WM_LBUTTONUP:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
		case WM_MBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONDBLCLK:
		case WM_RBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONDBLCLK:
		case WM_MOUSEMOVE:
		case WM_MOUSEWHEEL:
		{
			auto game = Game::getInstance();
			if (game->isTransitioning())
				break;

			if (game->getCurrentScene())
			{
				game->getCurrentScene()->dispatch(MouseEvent(hWnd, uMsg, wParam, lParam, window->_dpi), false);
			}
		}
		result = 0;
		hasHandled = true;
		break;

		// ��������Ϣ
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			auto game = Game::getInstance();
			if (game->isTransitioning())
				break;

			if (game->getCurrentScene())
			{
				game->getCurrentScene()->dispatch(KeyEvent(hWnd, uMsg, wParam, lParam), false);
			}
		}
		result = 0;
		hasHandled = true;
		break;

		// �����ڴ�С�仯��Ϣ
		case WM_SIZE:
		{
			UINT width = LOWORD(lParam);
			UINT height = HIWORD(lParam);

			if (wParam == SIZE_RESTORED)
			{
				window->_width = static_cast<int>(width * 96.f / window->_dpi);
				window->_height = static_cast<int>(height * 96.f / window->_dpi);
			}

			// ���������յ�һ�� WM_SIZE ��Ϣ�����������������Ⱦ
			// Ŀ���ʵ��������ܻ����ʧ�ܣ�����������Ժ����п��ܵ�
			// ������Ϊ�����������һ�ε��� EndDraw ʱ����
			auto renderer = Game::getInstance()->getRenderer();
			auto pRT = renderer->getRenderTarget();
			if (pRT)
			{
				pRT->Resize(D2D1::SizeU(width, height));
			}
		}
		break;

		// �����ڱ���仯��Ϣ
		case WM_SETTEXT:
		{
			window->_title = (const wchar_t*)lParam;
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
			Game::getInstance()->drawScene();
			ValidateRect(hWnd, nullptr);
		}
		result = 0;
		hasHandled = true;
		break;

		// ���ڹر���Ϣ
		case WM_CLOSE:
		{
			auto game = Game::getInstance();
			auto currScene = game->getCurrentScene();
			if (!currScene || currScene->onCloseWindow())
			{
				game->quit();
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
			result = DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
	return result;
}