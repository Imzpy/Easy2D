#include "..\e2dtool.h"
#include <commdlg.h>

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

e2d::String e2d::File::getFilePath() const
{
	return _fileName;
}

e2d::String e2d::File::getExtension() const
{
	String fileExtension;
	// �ҵ��ļ����е����һ�� '.' ��λ��
	size_t pos = _fileName.getWString().find_last_of(L'.');
	// �ж� pos �Ƿ�����Чλ��
	if (pos != std::wstring::npos)
	{
		// ��ȡ��չ��
		fileExtension = _fileName.subtract(static_cast<int>(pos));
		// ת��ΪСд��ĸ
		fileExtension = fileExtension.toLower();
	}
	return fileExtension;
}

bool e2d::File::deleteFile()
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

e2d::String e2d::File::getSaveFilePath(const String& title, const String& defExt)
{
	auto window = Game::getInstance()->getWindow();
	HWND hwnd = window->getHWnd();

	// ��������Ի���
	OPENFILENAME ofn = { 0 };
	wchar_t strFilename[MAX_PATH] = { 0 };				// ���ڽ����ļ���
	ofn.lStructSize = sizeof(OPENFILENAME);				// �ṹ���С
	ofn.hwndOwner = hwnd;								// ���ھ��
	ofn.lpstrFilter = L"�����ļ�\0*.*\0\0";				// ���ù���
	ofn.nFilterIndex = 1;								// ����������
	ofn.lpstrFile = strFilename;						// ���շ��ص��ļ�·�����ļ���
	ofn.nMaxFile = sizeof(strFilename);					// ����������
	ofn.lpstrInitialDir = nullptr;						// ��ʼĿ¼ΪĬ��
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrTitle = (LPCWSTR)title;					// ����
	ofn.lpstrDefExt = (LPCWSTR)defExt;					// Ĭ��׷�ӵ���չ��

	if (::GetSaveFileName(&ofn))
	{
		return strFilename;
	}
	return std::move(String());
}
