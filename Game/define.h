#pragma once
#ifndef DEFINE_H_
#define DEFINE_H_

#define		WINCX	800		// 클라이언트 사이즈 x
#define		WINCY	600		//				   y
#define		PURE	= 0			// 순수 가상함수 표시

#define		OBJ_NOEVENT		0	// 이벤트가 없으면 0 반환
#define		OBJ_DEAD		1	// obj가 죽으면 1 반환

#define		PI		3.141592f	// 파이 공식

#define		VK_MAX	0xff		// 0~255 까지의 수 
#define		VK_ATTACK			VK_SPACE

#define		PLAYER_POS_X		300
#define		PLAYER_POS_Y		500



extern		HWND	g_hWnd;

// hwnd = 윈도우 핸들　　
// 윈도우에 접근하기 위해 핸들이 필요하며,
// hwnd의 값은 숫자로 이루어져 있다. (이 윈도우 번호를 알아야 운영체제에서 관리 가능)
// 윈도우 프로그래밍은 기본적으로 메세지 처리 방식이기에, 공통적으로 메세지 큐를 가짐.
// 메세지 큐에 저장된 메세지들이 해당 윈도우로 흘러 들어가 처리하는 것이 winapi의 기본 원리
// 윈도우 핸들은 이러한 윈도우를 제어할 때 쓰는 이름표

#endif // !DEFINE_H_
