#pragma once
#ifndef STRUCT_H_
#define STRUCT_H_


typedef struct TagInfo		// 물체 정보
{
	float	x;				// 중점좌표 x
	float	y;				// 중점좌표 y
	float	cx;				// 사이즈 x
	float	cy;				// 사이즈 y

}INFO;

typedef struct TagLinePos	// 라인 좌표
{
	float	x;				// 중점좌표 x
	float	y;				// 중점좌표 y

	TagLinePos()			// 생성자 
	{	// this 에 있는 정보를 sizeof(taginfo)만큼 0으로 메모리 초기화
		ZeroMemory(this, sizeof(TagLinePos));
	}

	TagLinePos(float x_, float y_)	// 생성자 오버로딩 
		:x(x_), y(y_)
	{

	}

}LINEPOS;

typedef struct TagLineInfo	// 라인 정보
{
	LINEPOS		left_pos;	// 라인의 왼쪽 좌표
	LINEPOS		right_pos;	// 라인의 오른쪽 좌표

							// this에 있는 정보중 tagLineInfo 사이즈만큼 0으로 메모리 초기화
	TagLineInfo() { ZeroMemory(this, sizeof(TagLineInfo)); }  // 생성자
	TagLineInfo(LINEPOS& left_, LINEPOS& right_)			  // 생성자 오버로딩
		:left_pos(left_), right_pos(right_)
	{}

}LINEINFO;

typedef	struct tagFrame
{
	int		frame_start;	// 프레임 시작
	int		frame_end;		// 프레임 끝
	int		frame_scene;	// 모션

	DWORD	frame_speed;	// 프레임 스피드
	DWORD	frame_time;	// 프레임 시간

}FRAME;

class DeleteObj						// 객체 지우는 클래스
{
public:
	DeleteObj() {}
	~DeleteObj() {}

public:
	template<typename T>			// 함수 템플릿
	void operator() (T& temp)		// 객체 지우는 연산자 오버로딩
	{
		if (nullptr != temp)		// temp가 있다면
		{
			delete temp;			// temp 삭제
			temp = nullptr;			// temp null 초기화
		}
	}
};

class DeleteMap		// 맵 지우는 클래스
{
public:
	DeleteMap() {}
	~DeleteMap() {}

public:
	template<typename T>			// 함수 탬플릿, 
	void operator()(T& temp)		// 연산자 오버로딩을 이용한 객체 삭제
	{
		if (nullptr != temp.second)
		{
			delete temp.second;
			temp.second = nullptr;
		}
	}
};

class TagFinder			// 무언가를 찾는 클래스
{
private:
	const TCHAR*	m_string;	// 문자열 변수

public:
	TagFinder(const TCHAR* string)	// 생성자
		:m_string(string) {}

public:
	template<typename T>			// 함수 템플릿
	bool operator()(T& temp)		// 연산자 오버로딩
	{
		return !lstrcmp(m_string, temp.first);
	}
};

template<typename T>				// 함수 템플릿
void	SafeDelete(T& temp)			// 객체를 안전하게 지우는 용도
{
	if (temp)						// 만약 T자료형의 temp가 있다면
	{
		delete temp;				// temp를 삭제해라
		temp = nullptr;				// temp를 null로 채워라
	}
}

template<typename T>
bool CompareY(T Dest, T Sour)
{
	return Dest->GetInfo().y < Sour->GetInfo().y;
}
#endif // !STRUCT_H_
