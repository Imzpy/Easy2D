#include "..\e2dcustom.h"

e2d::SystemException::SystemException() E2D_NOEXCEPT
	: Exception(L"δ֪��ϵͳ�쳣")
{
}

e2d::SystemException::SystemException(const String& message) E2D_NOEXCEPT
	: Exception(message)
{
}

