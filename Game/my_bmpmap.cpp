#include "stdafx.h"
#include "my_bmpmap.h"

MyBmpMap::MyBmpMap()
{
}


MyBmpMap::~MyBmpMap()
{
}

void MyBmpMap::LoadBmp(const TCHAR* filepath)
{
	HDC			dc = GetDC(g_hWnd);

	// hDC ȣȯ�Ǵ� dc�� �Ҵ��ϴ� �Լ�
	m_mem_dc = CreateCompatibleDC(dc);

	ReleaseDC(g_hWnd, dc);

	// ��ηκ��� �̹��� ������ �о���̴� �Լ�
	m_bitbmp = (HBITMAP)LoadImage(NULL, // �ν��Ͻ�Ʈ �ڵ�, ���Ϸκ��� �о���̱� ������ NULL
		filepath, // ������ ���
		IMAGE_BITMAP,	// � Ÿ���� �о���� �����ϴ� �÷���
		0,				//	���� ������ 
		0,				//  ���� ������(������ �̹��� ������ �״�� �о���� ���̱� ������ ���� ����� ������ �ʿ䰡 ����)
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); //LR_LOADFROMFILE : ���Ͽ��� �̹����� �ҷ����� | �о�� ������ DIBSECTION���·� ��ȯ

	if (nullptr == m_bitbmp)
	{
		MessageBox(g_hWnd, L"�ε� ����", L"����", MB_OK);
		return;
	}

	// �غ��� DC�� GDI ������Ʈ�� �ҷ��� ��Ʈ���� �����ϱ� ���� ����ϴ� �Լ�
	// SelectObject GDI ������Ʈ�� �����ϱ� ���� ������ ������ �ִ� ������Ʈ�� ��ȯ
	m_oldmap = (HBITMAP)SelectObject(m_mem_dc, m_bitbmp);
}

void MyBmpMap::Release(void)
{
	SelectObject(m_mem_dc, m_oldmap);

	// ���� dc�� ���õ� gdi ������Ʈ�� ������ �� ����.
	// ���� ����ϰ� �ִ� ��ü�� �Ժη� �����ϵ��� ������ �� �� ���� ������ ���� ���� ��ġ ������ �ϴ� ����
	// �����ϱ� ���� ������ ����ϴ� gdi ������Ʈ�� ��ü�ϰ�, ������ ����

	DeleteObject(m_bitbmp);
	DeleteDC(m_mem_dc);
}

