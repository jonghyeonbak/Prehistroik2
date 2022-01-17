#pragma once
#ifndef LINE_MANAGER_H_
#define LINE_MANAGER_H_

#include "line.h"		// line 클래스 사용 용도
#include "key_manager.h"
#include "scroll_manager.h" 

class LineManager		// 라인 관리하는 매니저 (싱글톤)
{
private:
	static LineManager*		m_instance;		// 전역변수로 선언

	LINEPOS					m_line_pos[2];  // 라인 저장할 배열(왼쪽, 오른쪽)
	list<Line*>				m_line_list;	// 라인들을 담을 리스트

private:
	LineManager();
	~LineManager();

public:
	void	SaveData(void);		// 데이터 저장하는 함수
	void	LoadData(const TCHAR* file_);		// 데이터 불러오는 함수
	void	PickingLine(void);	// 원하는 라인 고르는 함수
								// x 값은 변경하지 않으니 const& 타입, y는 값변경이 있으니 * 타입
	bool	CollisionLine(const float& x_, const float& y_, float* newy_); // 라인 충돌 함수
	bool	CollisionLineNoDistance(const float& x_, const float& y_, float* newy_);

public:
	void	Initialize(void);
	void	Update(void);
	void	LateUpdate(void);
	void	Render(HDC dc);
	void	Release(void);


public:
	// 클래스와 전역변수의 생성 시점이 다르기 때문에 static으로 함수 생성
	static LineManager*	GetInstance(void)		// 인스턴스 얻어오는 함수
	{
		if (nullptr == m_instance)				// 인스턴스가 null이라면
			m_instance = new LineManager;		// 인스턴스화

		return m_instance;						// 인스턴스 반환
	}

	static void	DestroyInstance(void)				// 인스턴스 지우는 함수
	{
		if (nullptr != m_instance)				// 인스턴스가 null이 아니라면
		{
			delete m_instance;					// 인스턴스 삭제
			m_instance = nullptr;				// null 초기화
		}
	}
};

#endif // !LINEMANAGER_H_
