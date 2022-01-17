#include "stdafx.h"
#include "line.h"
#include "scroll_manager.h"

Line::Line()
{
}

Line::Line(LINEINFO& info_)
	: m_info(info_)
{

}

Line::Line(LINEPOS& left_, LINEPOS& right_)
	: m_info(left_, right_)
{}

Line::~Line()
{

}

void Line::Render(HDC dc_)
{
	// 스크롤을 얻어온 다음 scroll_x에 복사
	float	scroll_x = ScrollManager::GetInstance()->GetScrollX();
	float	scroll_y = ScrollManager::GetInstance()->GetScrollY();

	//여기다 scroll 값을 더해줘야 스크롤이 먹는다.
	MoveToEx(dc_, (int)m_info.left_pos.x + scroll_x, (int)m_info.left_pos.y + scroll_y, nullptr);
	LineTo(dc_, (int)m_info.right_pos.x + scroll_x, (int)m_info.right_pos.y + scroll_y);
																			
	// 라인 왼쪽 좌표를 기준으로 라인 오른쪽 좌표까지 이어라.					
}																			
																			