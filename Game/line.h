#pragma once
#ifndef LINE_H_
#define LINE_H_

#include "include.h"		// linepos, lineinfo 구조체 사용 위함

class Line
{
private:
	LINEINFO	m_info;		// 라인을 가지는 멤버 변수

public:
	Line();
	Line(LINEINFO& info_);							 // LINEINFO&타입의 매개변수를 가지는 복사 생성자 생성
	Line(/*const*/LINEPOS& left_, LINEPOS& right_);  // LINEPOS& 타입의 매개변수를 가지는 복사 생성자 생성
													 // 클래스 내부에서 메모리를 동적 할당 및 해제하고 이를 멤버 포인터 변수로 관리하는 경우 필요함
													 // const는 생략가능, 특별한 이유 없으면 붙이기
	~Line();

public:
	// LINEINFO형 멤버변수 m_info를 얻어 반환하는 함수
	// 필요없는 값 변경을 막기 위해 const 키워드 추가
	// lineinfo에 &를 붙여 메모리 절약
	const	LINEINFO&	GetInfo(void) const { return m_info; }

public:
	void Render(HDC dc_);		// 라인을 그리기 위한 함수 생성
								// HDC는 그리기 위한 데이터를 가지고 있음. 

};

#endif // !LINE_H_

// 매개변수가 클래스형식인 함수일 경우, &를 붙여야 객체가 2 개 생성되지 않음.
// 매개변수가 참조자가 될 경우, 사용자 코드에서는 '참조에 의한 호출' 인지 알 수 없음
// 따라서 값에 의한 호출인지, 참조에 의한 호출인기 구별을 해야 하는 이유는 
// 함수의 실인수로 기술한 변수가 함수 호출 때문에 값이 변경될 수 있기 때문.
// 그러므로, 함수의 매개변수 형식이 클래스라면 무조건 상수형 참조로 선언해라.
// 값을 변경해야 하는 경우를 제외하고.
// ex) void TestFun(const CTestData &param)