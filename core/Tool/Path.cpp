#include "..\e2dtool.h"
#include <algorithm>
#include <commdlg.h>


extern "C" const GUID DECLSPEC_SELECTANY FOLDERID_LocalAppData = { 
	0xF1B32785, 0x6FBA, 0x4FCF, { 0x9D, 0x55, 0x7B, 0x8E, 0x7F, 0x15, 0x70, 0x91 }
};


e2d::String				e2d::Path::_tempPath;
e2d::String				e2d::Path::_dataPath;
std::list<e2d::String>	e2d::Path::_paths;


void e2d::Path::setGameFolderName(const String & name)
{
	if (name.isEmpty())
		return;

	// �������ݵ�Ĭ�ϱ���·��
	String localAppDataPath = Path::getLocalAppDataPath();
	if (!localAppDataPath.isEmpty())
	{
		_dataPath = localAppDataPath + L"\\Easy2DGameData\\" << name << L"\\";
		
		if (!Path::exists(_dataPath) && !Path::createFolder(_dataPath))
		{
			_dataPath = L"";
		}
		_dataPath << L"Data.ini";
	}

	// ������ʱ�ļ�����·��
	wchar_t path[_MAX_PATH];
	if (0 != ::GetTempPath(_MAX_PATH, path))
	{
		_tempPath << path << L"\\Easy2DGameTemp\\" << name << L"\\";

		if (!Path::exists(_tempPath) && !Path::createFolder(_tempPath))
		{
			_tempPath = L"";
		}
	}
}

void e2d::Path::addSearchPath(String path)
{
	path.replace(L"/", L"\\");
	if (path[path.getLength() - 1] != L'\\')
	{
		path << L"\\";
	}
	auto iter = std::find(_paths.cbegin(), _paths.cend(), path);
	if (iter == _paths.cend())
	{
		_paths.push_front(path);
	}
}

e2d::String e2d::Path::getTempPath()
{
	return _tempPath;
}

e2d::String e2d::Path::getLocalAppDataPath()
{
	static String localAppDataPath;
	if (localAppDataPath.isEmpty())
	{
		// ��ȡ AppData/Local �ļ��е�·��
		typedef HRESULT(WINAPI* pFunSHGetKnownFolderPath)(const GUID& rfid, DWORD dwFlags, HANDLE hToken, PWSTR *ppszPath);

		PWSTR pszPath = nullptr;
		HMODULE hModule = LoadLibrary(L"shell32.dll");
		pFunSHGetKnownFolderPath SHGetKnownFolderPath = (pFunSHGetKnownFolderPath)GetProcAddress(hModule, "SHGetKnownFolderPath");
		HRESULT hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &pszPath);

		if (SUCCEEDED(hr))
		{
			localAppDataPath = pszPath;
			CoTaskMemFree(pszPath);
		}
	}

	return localAppDataPath;
}

e2d::String e2d::Path::getCurrentFilePath()
{
	TCHAR szPath[_MAX_PATH] = { 0 };
	if (::GetModuleFileName(nullptr, szPath, _MAX_PATH) != 0)
	{
		return std::move(String(szPath));
	}
	return std::move(String());
}

e2d::String e2d::Path::findFile(const String& path)
{
	if (Path::exists(path))
	{
		return path;
	}
	else
	{
		for (auto& resPath : _paths)
		{
			if (Path::exists(resPath + path))
			{
				return resPath + path;
			}
		}
	}
	return std::move(String());
}

e2d::String e2d::Path::extractResource(int resNameId, const String & resType, const String & destFileName)
{
	String destFilePath = _tempPath + destFileName;
	// �����ļ�
	HANDLE hFile = ::CreateFile((LPCWSTR)destFilePath, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return std::move(String());

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
		return destFilePath;
	}
	else
	{
		::CloseHandle(hFile);
		::DeleteFile((LPCWSTR)destFilePath);
		return std::move(String());
	}
}

e2d::String e2d::Path::getDataPath()
{
	return _dataPath;
}

e2d::String e2d::Path::getFileExtension(const String& filePath)
{
	String fileExtension;
	// �ҵ��ļ����е����һ�� '.' ��λ��
	size_t pos = filePath.getWString().find_last_of(L'.');
	// �ж� pos �Ƿ�����Чλ��
	if (pos != std::wstring::npos)
	{
		// ��ȡ��չ��
		fileExtension = filePath.subtract(static_cast<int>(pos));
		// ת��ΪСд��ĸ
		fileExtension = fileExtension.toLower();
	}

	return fileExtension;
}

e2d::String e2d::Path::getSaveFilePath(const String& title, const String& defExt)
{
	// ��������Ի���
	OPENFILENAME ofn = { 0 };
	wchar_t strFilename[MAX_PATH] = { 0 };				// ���ڽ����ļ���
	ofn.lStructSize = sizeof(OPENFILENAME);				// �ṹ���С
	ofn.hwndOwner = Window::getInstance()->getHWnd();	// ���ھ��
	ofn.lpstrFilter = L"�����ļ�\0*.*\0\0";				// ���ù���
	ofn.nFilterIndex = 1;								// ����������
	ofn.lpstrFile = strFilename;						// ���շ��ص��ļ�·�����ļ���
	ofn.nMaxFile = sizeof(strFilename);					// ����������
	ofn.lpstrInitialDir = nullptr;						// ��ʼĿ¼ΪĬ��
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrTitle = (LPCWSTR)title;					// ����
	ofn.lpstrDefExt = (LPCWSTR)defExt;					// Ĭ��׷�ӵ���չ��

	if (GetSaveFileName(&ofn))
	{
		return strFilename;
	}
	return std::move(String());
}

bool e2d::Path::createFolder(const String& dirPath)
{
	if (dirPath.isEmpty() || dirPath.getLength() >= MAX_PATH)
	{
		return false;
	}

	wchar_t tmpDirPath[_MAX_PATH] = { 0 };
	int length = dirPath.getLength();

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

bool e2d::Path::exists(const String & path)
{
	if (path.isEmpty() || path.getLength() >= MAX_PATH)
	{
		return false;
	}
	return ::_waccess((const wchar_t *)path, 0) == 0;
}
