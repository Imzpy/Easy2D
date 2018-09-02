#include "..\e2dtool.h"
#include <shobjidl.h> 

std::list<e2d::String>	e2d::File::_searchPaths;

e2d::File::File()
	: _fileName()
	, _attributes(0)
{
}

e2d::File::File(const String & fileName)
	: _fileName(fileName)
	, _attributes(0)
{
	this->open(fileName);
}

e2d::File::~File()
{
}

bool e2d::File::open(const String & fileName)
{
	auto FindFile = [=](const String & path) -> bool
	{
		if (::_waccess((const wchar_t*)path, 0) == 0)
		{
			_attributes = ::GetFileAttributes((LPCTSTR)path);
			return true;
		}
		return false;
	};

	if (FindFile(fileName))
	{
		_fileName = fileName;
		return true;
	}
	else
	{
		for (const auto& resPath : _searchPaths)
		{
			if (FindFile(resPath + fileName))
			{
				_fileName = resPath + fileName;
				return true;
			}
		}
	}
	return false;
}

bool e2d::File::exists() const
{
	return ::_waccess((const wchar_t*)_fileName, 0) == 0;
}

bool e2d::File::isFolder() const
{
	return (_attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

const e2d::String& e2d::File::getPath() const
{
	return _fileName;
}

e2d::String e2d::File::getExtension() const
{
	String fileExtension;
	// �ҵ��ļ����е����һ�� '.' ��λ��
	size_t pos = std::wstring(_fileName).find_last_of(L'.');
	// �ж� pos �Ƿ�����Чλ��
	if (pos != std::wstring::npos)
	{
		// ��ȡ��չ��
		fileExtension = _fileName.subtract(static_cast<int>(pos));
		// ת��ΪСд��ĸ
		fileExtension = fileExtension.toLower();
	}
	return std::move(fileExtension);
}

bool e2d::File::del()
{
	if (::DeleteFile((LPCWSTR)_fileName))
		return true;
	return false;
}

e2d::File e2d::File::extract(int resNameId, const String & resType, const String& destFileName)
{
	String destFilePath = Path::getTempPath() + destFileName;
	// �����ļ�
	HANDLE hFile = ::CreateFile((LPCWSTR)destFilePath, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return std::move(File());

	// ������Դ�ļ��С�������Դ���ڴ桢�õ���Դ��С
	HRSRC hRes = ::FindResource(NULL, MAKEINTRESOURCE(resNameId), (LPCWSTR)resType);
	HGLOBAL hMem = ::LoadResource(NULL, hRes);
	DWORD dwSize = ::SizeofResource(NULL, hRes);

	if (hRes && hMem && dwSize)
	{
		// д���ļ�
		DWORD dwWrite = 0;
		::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
		::CloseHandle(hFile);
		return File(destFilePath);
	}
	else
	{
		::CloseHandle(hFile);
		::DeleteFile((LPCWSTR)destFilePath);
		return std::move(File());
	}
}

void e2d::File::addSearchPath(const String & path)
{
	String tmp = path;
	tmp.replace(L"/", L"\\");
	if (tmp[tmp.length() - 1] != L'\\')
	{
		tmp << L"\\";
	}
	auto iter = std::find(_searchPaths.cbegin(), _searchPaths.cend(), tmp);
	if (iter == _searchPaths.cend())
	{
		_searchPaths.push_front(path);
	}
}

bool e2d::File::createFolder(const String & dirPath)
{
	if (dirPath.isEmpty() || dirPath.length() >= MAX_PATH)
		return false;

	wchar_t tmpDirPath[_MAX_PATH] = { 0 };
	int length = dirPath.length();

	for (int i = 0; i < length; ++i)
	{
		tmpDirPath[i] = dirPath.at(i);
		if (tmpDirPath[i] == L'\\' || tmpDirPath[i] == L'/' || i == (length - 1))
		{
			if (::_waccess(tmpDirPath, 0) != 0)
			{
				if (::_wmkdir(tmpDirPath) != 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}

e2d::File e2d::File::showOpenDialog(const String & title, const String & filter)
{
	String filePath;
	HRESULT hr = ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		IFileOpenDialog *pFileOpen;

		hr = ::CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			if (!title.isEmpty())
			{
				pFileOpen->SetTitle(LPCWSTR(title));
			}

			if (!filter.isEmpty())
			{
				COMDLG_FILTERSPEC rgSpec[] =
				{
					{ L"", LPCWSTR(filter) }
				};
				pFileOpen->SetFileTypes(1, rgSpec);
			}
			else
			{
				COMDLG_FILTERSPEC rgSpec[] =
				{
					{ L"�����ļ�", L"*.*" }
				};
				pFileOpen->SetFileTypes(1, rgSpec);
			}

			Game::getInstance()->pause();
			{
				HWND hWnd = Window::getInstance()->getHWnd();
				hr = pFileOpen->Show(hWnd);
			}
			Game::getInstance()->resume();

			if (SUCCEEDED(hr))
			{
				IShellItem *pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					if (SUCCEEDED(hr))
					{
						filePath = pszFilePath;
						::CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		::CoUninitialize();
	}
	return std::move(File(filePath));
}

e2d::File e2d::File::showSaveDialog(const String & title, const String& defFile, const String & defExt)
{
	String filePath;
	HRESULT hr = ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	
	if (SUCCEEDED(hr))
	{
		IFileSaveDialog *pFileSave;

		hr = ::CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
			IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));

		if (SUCCEEDED(hr))
		{
			if (!title.isEmpty())
			{
				pFileSave->SetTitle(LPCWSTR(title));
			}

			if (!defFile.isEmpty())
			{
				pFileSave->SetFileName(LPCWSTR(defFile));
			}

			if (!defExt.isEmpty())
			{
				pFileSave->SetDefaultExtension(LPCWSTR(defExt));

				String spec = L"*." + defExt;
				COMDLG_FILTERSPEC rgSpec[] =
				{
					{ L"", LPCWSTR(spec) }
				};
				pFileSave->SetFileTypes(1, rgSpec);
			}
			else
			{
				COMDLG_FILTERSPEC rgSpec[] =
				{
					{ L"�����ļ�", L"*.*" }
				};
				pFileSave->SetFileTypes(1, rgSpec);
			}

			Game::getInstance()->pause();
			{
				HWND hWnd = Window::getInstance()->getHWnd();
				hr = pFileSave->Show(hWnd);
			}
			Game::getInstance()->resume();

			if (SUCCEEDED(hr))
			{
				IShellItem *pItem;
				hr = pFileSave->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					if (SUCCEEDED(hr))
					{
						filePath = pszFilePath;
						::CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileSave->Release();
		}
		::CoUninitialize();
	}
	return std::move(File(filePath));
}
