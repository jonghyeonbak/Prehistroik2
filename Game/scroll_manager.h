#pragma once
#ifndef SCROLL_MANAGER_H_
#define SCROLL_MANAGER_H_

#include "include.h"

class ScrollManager
{
private:
	static ScrollManager* m_instance;
	static float		  m_scroll_x;
	static float		  m_scroll_y;

//public:
//	INFO				  m_scroll;

private:
	ScrollManager();
	~ScrollManager();

public:
	void		Initialize(void) {}
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC dc) {}
	void		Release(void);


public:
	void		SetScrollX(float x_) { m_scroll_x += x_; }	// 스크롤 x 좌표 세팅하는 함수, scroll에 매개변수를 더한다.
	void		SetScrollX2(float x_) { m_scroll_x = x_; }
	void		SetScrollY(float y_) { m_scroll_y += y_; }	// 스크롤 y 좌표 세팅하는 함수, scroll에 매개변수를 더한다.
	void		SetScrollY2(float y_) { m_scroll_y = y_; }
	void		SetScrollY3(float y_); 
	
	
	float		GetScrollX() { return m_scroll_x; }			// 스크롤을 얻어오는 함수, m_scroll을 반환.
	float		GetScrollY() { return m_scroll_y; }			// 스크롤을 얻어오는 함수, m_scroll을 반환.
	void		ScrollLock(void);							// 스크롤 잠구는 함수
	void		InitScrollX(float x_) { m_scroll_x = x_; }
	void		InitScrollY(float y_) { m_scroll_x = y_; }

public:
	static	ScrollManager*		GetInstance(void)
	{
		if (nullptr == m_instance)
			m_instance = new ScrollManager;

		return m_instance;
	}

	static	void		DestroyIntance(void)
	{
		if (nullptr != m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
};

#endif // !SCROLL_MANAGER_H_
