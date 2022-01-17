#pragma once
#ifndef LINE_MANAGER_H_
#define LINE_MANAGER_H_

#include "line.h"		// line Ŭ���� ��� �뵵
#include "key_manager.h"
#include "scroll_manager.h" 

class LineManager		// ���� �����ϴ� �Ŵ��� (�̱���)
{
private:
	static LineManager*		m_instance;		// ���������� ����

	LINEPOS					m_line_pos[2];  // ���� ������ �迭(����, ������)
	list<Line*>				m_line_list;	// ���ε��� ���� ����Ʈ

private:
	LineManager();
	~LineManager();

public:
	void	SaveData(void);		// ������ �����ϴ� �Լ�
	void	LoadData(const TCHAR* file_);		// ������ �ҷ����� �Լ�
	void	PickingLine(void);	// ���ϴ� ���� ���� �Լ�
								// x ���� �������� ������ const& Ÿ��, y�� �������� ������ * Ÿ��
	bool	CollisionLine(const float& x_, const float& y_, float* newy_); // ���� �浹 �Լ�
	bool	CollisionLineNoDistance(const float& x_, const float& y_, float* newy_);

public:
	void	Initialize(void);
	void	Update(void);
	void	LateUpdate(void);
	void	Render(HDC dc);
	void	Release(void);


public:
	// Ŭ������ ���������� ���� ������ �ٸ��� ������ static���� �Լ� ����
	static LineManager*	GetInstance(void)		// �ν��Ͻ� ������ �Լ�
	{
		if (nullptr == m_instance)				// �ν��Ͻ��� null�̶��
			m_instance = new LineManager;		// �ν��Ͻ�ȭ

		return m_instance;						// �ν��Ͻ� ��ȯ
	}

	static void	DestroyInstance(void)				// �ν��Ͻ� ����� �Լ�
	{
		if (nullptr != m_instance)				// �ν��Ͻ��� null�� �ƴ϶��
		{
			delete m_instance;					// �ν��Ͻ� ����
			m_instance = nullptr;				// null �ʱ�ȭ
		}
	}
};

#endif // !LINEMANAGER_H_
