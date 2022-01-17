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
	// ��ũ���� ���� ���� scroll_x�� ����
	float	scroll_x = ScrollManager::GetInstance()->GetScrollX();
	float	scroll_y = ScrollManager::GetInstance()->GetScrollY();

	//����� scroll ���� ������� ��ũ���� �Դ´�.
	MoveToEx(dc_, (int)m_info.left_pos.x + scroll_x, (int)m_info.left_pos.y + scroll_y, nullptr);
	LineTo(dc_, (int)m_info.right_pos.x + scroll_x, (int)m_info.right_pos.y + scroll_y);
																			
	// ���� ���� ��ǥ�� �������� ���� ������ ��ǥ���� �̾��.					
}																			
																			