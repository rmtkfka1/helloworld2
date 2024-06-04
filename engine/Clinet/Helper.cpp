#include "pch.h"
#include "Helper.h"

std::wstring Helper::ToWString(string value)
{
	return wstring(value.begin(), value.end());
}

std::string Helper::ToString(wstring value)
{
	return string(value.begin(), value.end());
}
