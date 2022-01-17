#include "stdafx.h"
#include "line_manager.h"

// 라인매니저의 전역 변수 초기화
LineManager* LineManager::m_instance;

LineManager::LineManager()
{
	ZeroMemory(m_line_pos, sizeof(m_line_pos)); // 라인을 저장할 배열을 0으로 초기화, 
												//디버그 에러 잡는 데 30분 정도 걸림 
}


LineManager::~LineManager()
{
	Release();
}

void LineManager::SaveData(void)
{
	// 파일 개방
	HANDLE		file = CreateFile(L"../Save/Line.dat",	    // 파일 경로와 이름을 명시
		GENERIC_WRITE,			// 파일 접근모드(쓰기 전용)
		NULL,					// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해 설정 가능(NULL로 지정하면 공유하지 않는다)
		NULL,					// 보안모드, NULL인 경우 DEFAULT상태
		CREATE_ALWAYS,			// 생성 방식, CREATE_ALWAYS(파일이 없으면 만들고, 있으면 덮어쓰기를 한다), OPEN_EXITING 파일 있을 경우에만 열겠다는 의미
		FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등), FILE_ATTRIBUTE_NORMAL 아무 속성이 없다는 뜻
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(우리는 졸업때까지 사용할 일이 없어서 NULL)

	if (INVALID_HANDLE_VALUE == file)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	// 파일 쓰기
	DWORD	byte = 0;

	for (auto& iter : m_line_list)
	{
		// 1인자 : 개방한 파일
		// 2인자 : 내가 파일에 저장하고자 하는 데이터
		// 3인자 : 저장하고자 하는 데이터 크기 단위
		// 4인자 : dwByte 값이 0이면 저장할 것이 없다. 
		WriteFile(file, &(iter->GetInfo()), sizeof(LINEINFO), &byte, NULL);
	}

	CloseHandle(file);

	MessageBox(g_hWnd, _T("Save 완료"), _T("Success"), MB_OKCANCEL);
}

void LineManager::LoadData(const TCHAR* file_)
{
	// 파일을 개방하는 함수
	HANDLE			file = CreateFile(file_,  // 파일 경로와 이름을 명시
		GENERIC_READ,		// 파일 접근모드(쓰기 전용)
		NULL,				// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허ㅇ가하는 것에 대해 설정 가능(NULL로 지정하면 공유하지 않는다)
		NULL,				// 보안모드, NULL인 경우 DEFAULT상태
		OPEN_EXISTING,		// 생성 방식, CREATE_ALWAYS(파일이 없으면 만들고, 있으면 덮어쓰기를 한다), OPEN_EXITING 파일 있을 경우에만 열겠다는 의미
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김 등), FILE_ATTRIBUTE_NORMAL 아무 속성이 없다는 뜻
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일(우리는 졸업때까지 사용할 일이 없어서 NULL)

	if (INVALID_HANDLE_VALUE == file)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 파일 읽기
	DWORD			byte = 0;
	LINEINFO		info{};

	while (true)
	{
		// 1인자 : 개방한 파일
		// 2인자 : 내가 파일에 저장하고자 하는 데이터
		// 3인자 : 저장하고자 하는 데이터 크기 단위
		// 4인자 : dwByte 값이 0이면 저장할 것이 없다. 
		ReadFile(file, &info, sizeof(LINEINFO), &byte, NULL);

		if (0 == byte)
			break;

		m_line_list.push_back(new Line(info));
	}

	CloseHandle(file);

	// MessageBox(g_hWnd, _T("Load 성공"), _T("Success"), MB_OKCANCEL);

}

void LineManager::PickingLine(void)	// 라인 선택하기
{
	POINT	pt{};					// 두 좌표를 가지는 구조체 변수 생성

	GetCursorPos(&pt);				// 커서의 좌표를 알아오는 함수
	ScreenToClient(g_hWnd, &pt);	// 좌표를 변환하는 함수

	pt.x -= (long)ScrollManager::GetInstance()->GetScrollX();
	// pt의 x 좌표 -= 스크롤한 만큼

	if (!m_line_pos[0].x && !m_line_pos[0].y)
	{
		m_line_pos[0].x = (float)pt.x;
		m_line_pos[0].y = (float)pt.y;
	}
	else
	{
		m_line_pos[1].x = (float)pt.x;
		m_line_pos[1].y = (float)pt.y;

		m_line_list.push_back(new Line(m_line_pos[0], m_line_pos[1]));

		m_line_pos[0].x = m_line_pos[1].x;
		m_line_pos[0].y = m_line_pos[1].y;

	}
}

void LineManager::Initialize(void)
{
//	//LoadData();
//	// linepos형 변수를 배열로 만든 후 좌표 4개 저장
//	LINEPOS point[2] = {
//		{ 100.f, 1474.f },
//		{ 800.f, 1474.f },
//};
//
//	//// 좌표 4개를 list에 원소로 넣음과 동시에 line 생성 + 라인 이어주기
//	m_line_list.push_back(new Line(point[0], point[1])); 
	//m_line_list.push_back(new Line(point[1], point[2]));
	//m_line_list.push_back(new Line(point[2], point[3]));
}


bool LineManager::CollisionLine(const float& x_, const float& y_, float* newy_)
{
	if (m_line_list.empty()) // linelist가 비어있다면
		return false;		 // false 반환

	// 두 점을 지나는 직선의 방정식
	// y - y1 = ((y2 - y1) / (x2 - x1)) * (x - x1)

	// 플레이어 y값 구하는 공식
	// y = ((y2 - y1) / (x2 - x1)) * (x - x1) + y1

	Line* min = nullptr;
	float m_distance = -1.f;


	for (auto& iter : m_line_list)		// linelist를 iter에 복사
	{
		// 충돌한 선의 왼쪽x 좌표보다 부딪힌 녀석의 x가 크고,
		// 충돌한 선의 오른쪽 x 좌표보다 부딪힌 녀석의 x가 작을 때
		if (iter->GetInfo().left_pos.x < x_ &&
			iter->GetInfo().right_pos.x > x_)
		{
			float x1 = iter->GetInfo().left_pos.x;
			float y1 = iter->GetInfo().left_pos.y;

			float x2 = iter->GetInfo().right_pos.x;
			float y2 = iter->GetInfo().right_pos.y;

			float line_y = ((y2 - y1) / (x2 - x1)) * (x_ - x1) + y1;

			// 오브젝트 X값을 직선의 방정식에 대입했을때 나오는 Y값이 오브젝트의 Y값보다 크다면
			if (line_y > y_)
			{
				// 오브젝트 X값을 직선의 방정식에 대입했을때 나오는 Y값과 오브젝트의 Y값의 거리가 m_fDistance보다 작다면 또는 기존 m_fDistance가 없었다면(m_fDistance==-1.f)
				if ((m_distance > (line_y - y_)) || (m_distance == -1.f))
				{
					// 조건에 알맞는 최소 거리 라인 기준으로 m_fDistance와 Min 설정
					m_distance = line_y - y_;
					min = iter;
				}
			}
		}
	}

	// Min값이 nullptr이 아니라면 (조건에 맞는 라인이 있었다면)
	if (min != nullptr)
	{
		float x1 = min->GetInfo().left_pos.x;
		float y1 = min->GetInfo().left_pos.y;

		float x2 = min->GetInfo().right_pos.x;
		float y2 = min->GetInfo().right_pos.y;

		// 오브젝트 Y값 변경
		*newy_ = ((y2 - y1) / (x2 - x1)) * (x_ - x1) + y1;

		return true;
	}
	return false;
}



void LineManager::Update(void)
{
}

void LineManager::LateUpdate(void)
{
}

void LineManager::Render(HDC dc)
{
	for (auto& iter : m_line_list) // linelist를 iter에 복사
		iter->Render(dc);		   // iter의 모든 것을 그려라
}

void LineManager::Release(void)
{
	//list 시작부터 끝까지 객체 소멸 + null 초기화
	for_each(m_line_list.begin(), m_line_list.end(), DeleteObj());
	// list의 모든 원소 삭제
	m_line_list.clear();

	/*DeleteObj(m_line_pos);
	DeleteObj(info);*/
}

bool  LineManager::CollisionLineNoDistance(const float& x_, const float& y_, float* newy_)
{
	// 리스트가 비었으면 반환
	if (m_line_list.empty())
		return false;

	Line* min = nullptr;		// 조건 검사해서 알맞는 라인을 저장할 포인터변수 (모든라인을 검사했을때 조건에 맞고, m_fDistance가 최소인 라인)
	float m_distance = -1.f;	// 모든 라인을 비교하면서 조건에 맞는 라인과 오브젝트의 거리를 저장할 변수

								// 리스트 안의 라인을 모두 검사
	for (auto& iter : m_line_list)
	{
		// 현재 라인의 leftX가 오브젝트의 X보다 작고, rightX가 오브젝트의 X보다 크다면
		if (iter->GetInfo().left_pos.x < x_ &&
			iter->GetInfo().right_pos.x > x_)
		{
			// 직선의 방정식에 대입할 변수 초기화
			float x1 = iter->GetInfo().left_pos.x;
			float y1 = iter->GetInfo().left_pos.y;

			float x2 = iter->GetInfo().right_pos.x;
			float y2 = iter->GetInfo().right_pos.y;

			float LineY = (((y2 - y1) / (x2 - x1)) * (x_ - x1) + y1);
			min = iter;
		}
	}

	// Min값이 nullptr이 아니라면 (조건에 맞는 라인이 있었다면)
	if (min != nullptr)
	{
		float x1 = min->GetInfo().left_pos.x;
		float y1 = min->GetInfo().left_pos.y;

		float x2 = min->GetInfo().right_pos.x;
		float y2 = min->GetInfo().right_pos.y;

		// 오브젝트 Y값 변경
		*newy_ = ((y2 - y1) / (x2 - x1)) * (x_ - x1) + y1;

		return true;
	}

	return false;
}

