#pragma once
#ifndef DEFINE_H_
#define DEFINE_H_

#define		WINCX	800		// Ŭ���̾�Ʈ ������ x
#define		WINCY	600		//				   y
#define		PURE	= 0			// ���� �����Լ� ǥ��

#define		OBJ_NOEVENT		0	// �̺�Ʈ�� ������ 0 ��ȯ
#define		OBJ_DEAD		1	// obj�� ������ 1 ��ȯ

#define		PI		3.141592f	// ���� ����

#define		VK_MAX	0xff		// 0~255 ������ �� 
#define		VK_ATTACK			VK_SPACE

#define		PLAYER_POS_X		300
#define		PLAYER_POS_Y		500



extern		HWND	g_hWnd;

// hwnd = ������ �ڵ顡��
// �����쿡 �����ϱ� ���� �ڵ��� �ʿ��ϸ�,
// hwnd�� ���� ���ڷ� �̷���� �ִ�. (�� ������ ��ȣ�� �˾ƾ� �ü������ ���� ����)
// ������ ���α׷����� �⺻������ �޼��� ó�� ����̱⿡, ���������� �޼��� ť�� ����.
// �޼��� ť�� ����� �޼������� �ش� ������� �귯 �� ó���ϴ� ���� winapi�� �⺻ ����
// ������ �ڵ��� �̷��� �����츦 ������ �� ���� �̸�ǥ

#endif // !DEFINE_H_
