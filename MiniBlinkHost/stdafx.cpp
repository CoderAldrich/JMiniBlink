// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// MiniBlinkHost.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H �������κ�����ĸ���ͷ�ļ���
//�������ڴ��ļ�������

std::string ReadText(const wchar_t * path)
{
	std::vector<char> vctSZ;
	WCharToMByte(path, wcslen(path), &vctSZ, CP_ACP);
	if (vctSZ.size() < 1)
		return "";
	vctSZ.push_back('\0');

	FILE *f = NULL;
	long sz;

	if (!path)
	{
		return "";
	}

	std::string sRet;

	f = fopen(vctSZ.data(), "rb");
	if (!f)
	{
		return "";
	}

	do
	{
		if (fseek(f, 0, SEEK_END) < 0)
		{
			break;
		}

		sz = ftell(f);
		if (sz < 0)
		{
			break;
		}

		if (fseek(f, 0, SEEK_SET) < 0)
		{
			break;
		}

		sRet.resize((size_t)sz + 1, '\0');

		if ((size_t)fread(const_cast<char*>(sRet.c_str()), 1, (size_t)sz, f) != (size_t)sz)
		{
			sRet = "";
			break;
		}
	} while (0);

	fclose(f);

	return sRet;
}

void MByteToWChar(LPCSTR lpcszStr, DWORD cbMultiByte, std::vector<wchar_t>* out, UINT codePage)
{
	out->clear();

	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar(codePage, 0, lpcszStr, cbMultiByte, NULL, 0);
	if (0 == dwMinSize)
		return;

	out->resize(dwMinSize);

	// Convert headers from ASCII to Unicode.
	MultiByteToWideChar(codePage, 0, lpcszStr, cbMultiByte, &out->at(0), dwMinSize);
}

void WCharToMByte(LPCWSTR lpWideCharStr, DWORD cchWideChar, std::vector<char>* out, UINT codePage)
{
	out->clear();

	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(codePage, 0, lpWideCharStr, cchWideChar, NULL, 0, NULL, FALSE);
	if (0 == dwMinSize)
		return;

	out->resize(dwMinSize);

	// Convert headers from ASCII to Unicode.
	WideCharToMultiByte(codePage, 0, lpWideCharStr, cchWideChar, &out->at(0), dwMinSize, NULL, FALSE);
}