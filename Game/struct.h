#pragma once
#ifndef STRUCT_H_
#define STRUCT_H_


typedef struct TagInfo		// ��ü ����
{
	float	x;				// ������ǥ x
	float	y;				// ������ǥ y
	float	cx;				// ������ x
	float	cy;				// ������ y

}INFO;

typedef struct TagLinePos	// ���� ��ǥ
{
	float	x;				// ������ǥ x
	float	y;				// ������ǥ y

	TagLinePos()			// ������ 
	{	// this �� �ִ� ������ sizeof(taginfo)��ŭ 0���� �޸� �ʱ�ȭ
		ZeroMemory(this, sizeof(TagLinePos));
	}

	TagLinePos(float x_, float y_)	// ������ �����ε� 
		:x(x_), y(y_)
	{

	}

}LINEPOS;

typedef struct TagLineInfo	// ���� ����
{
	LINEPOS		left_pos;	// ������ ���� ��ǥ
	LINEPOS		right_pos;	// ������ ������ ��ǥ

							// this�� �ִ� ������ tagLineInfo �����ŭ 0���� �޸� �ʱ�ȭ
	TagLineInfo() { ZeroMemory(this, sizeof(TagLineInfo)); }  // ������
	TagLineInfo(LINEPOS& left_, LINEPOS& right_)			  // ������ �����ε�
		:left_pos(left_), right_pos(right_)
	{}

}LINEINFO;

typedef	struct tagFrame
{
	int		frame_start;	// ������ ����
	int		frame_end;		// ������ ��
	int		frame_scene;	// ���

	DWORD	frame_speed;	// ������ ���ǵ�
	DWORD	frame_time;	// ������ �ð�

}FRAME;

class DeleteObj						// ��ü ����� Ŭ����
{
public:
	DeleteObj() {}
	~DeleteObj() {}

public:
	template<typename T>			// �Լ� ���ø�
	void operator() (T& temp)		// ��ü ����� ������ �����ε�
	{
		if (nullptr != temp)		// temp�� �ִٸ�
		{
			delete temp;			// temp ����
			temp = nullptr;			// temp null �ʱ�ȭ
		}
	}
};

class DeleteMap		// �� ����� Ŭ����
{
public:
	DeleteMap() {}
	~DeleteMap() {}

public:
	template<typename T>			// �Լ� ���ø�, 
	void operator()(T& temp)		// ������ �����ε��� �̿��� ��ü ����
	{
		if (nullptr != temp.second)
		{
			delete temp.second;
			temp.second = nullptr;
		}
	}
};

class TagFinder			// ���𰡸� ã�� Ŭ����
{
private:
	const TCHAR*	m_string;	// ���ڿ� ����

public:
	TagFinder(const TCHAR* string)	// ������
		:m_string(string) {}

public:
	template<typename T>			// �Լ� ���ø�
	bool operator()(T& temp)		// ������ �����ε�
	{
		return !lstrcmp(m_string, temp.first);
	}
};

template<typename T>				// �Լ� ���ø�
void	SafeDelete(T& temp)			// ��ü�� �����ϰ� ����� �뵵
{
	if (temp)						// ���� T�ڷ����� temp�� �ִٸ�
	{
		delete temp;				// temp�� �����ض�
		temp = nullptr;				// temp�� null�� ä����
	}
}

template<typename T>
bool CompareY(T Dest, T Sour)
{
	return Dest->GetInfo().y < Sour->GetInfo().y;
}
#endif // !STRUCT_H_
