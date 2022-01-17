#include "stdafx.h"
#include "line_manager.h"

// ���θŴ����� ���� ���� �ʱ�ȭ
LineManager* LineManager::m_instance;

LineManager::LineManager()
{
	ZeroMemory(m_line_pos, sizeof(m_line_pos)); // ������ ������ �迭�� 0���� �ʱ�ȭ, 
												//����� ���� ��� �� 30�� ���� �ɸ� 
}


LineManager::~LineManager()
{
	Release();
}

void LineManager::SaveData(void)
{
	// ���� ����
	HANDLE		file = CreateFile(L"../Save/Line.dat",	    // ���� ��ο� �̸��� ���
		GENERIC_WRITE,			// ���� ���ٸ��(���� ����)
		NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�ϴ� �Ϳ� ���� ���� ����(NULL�� �����ϸ� �������� �ʴ´�)
		NULL,					// ���ȸ��, NULL�� ��� DEFAULT����
		CREATE_ALWAYS,			// ���� ���, CREATE_ALWAYS(������ ������ �����, ������ ����⸦ �Ѵ�), OPEN_EXITING ���� ���� ��쿡�� ���ڴٴ� �ǹ�
		FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ� �Ӽ��� ���ٴ� ��
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ���������� ����� ���� ��� NULL)

	if (INVALID_HANDLE_VALUE == file)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	// ���� ����
	DWORD	byte = 0;

	for (auto& iter : m_line_list)
	{
		// 1���� : ������ ����
		// 2���� : ���� ���Ͽ� �����ϰ��� �ϴ� ������
		// 3���� : �����ϰ��� �ϴ� ������ ũ�� ����
		// 4���� : dwByte ���� 0�̸� ������ ���� ����. 
		WriteFile(file, &(iter->GetInfo()), sizeof(LINEINFO), &byte, NULL);
	}

	CloseHandle(file);

	MessageBox(g_hWnd, _T("Save �Ϸ�"), _T("Success"), MB_OKCANCEL);
}

void LineManager::LoadData(const TCHAR* file_)
{
	// ������ �����ϴ� �Լ�
	HANDLE			file = CreateFile(file_,  // ���� ��ο� �̸��� ���
		GENERIC_READ,		// ���� ���ٸ��(���� ����)
		NULL,				// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㤷���ϴ� �Ϳ� ���� ���� ����(NULL�� �����ϸ� �������� �ʴ´�)
		NULL,				// ���ȸ��, NULL�� ��� DEFAULT����
		OPEN_EXISTING,		// ���� ���, CREATE_ALWAYS(������ ������ �����, ������ ����⸦ �Ѵ�), OPEN_EXITING ���� ���� ��쿡�� ���ڴٴ� �ǹ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ� �Ӽ��� ���ٴ� ��
		NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����(�츮�� ���������� ����� ���� ��� NULL)

	if (INVALID_HANDLE_VALUE == file)
	{
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// ���� �б�
	DWORD			byte = 0;
	LINEINFO		info{};

	while (true)
	{
		// 1���� : ������ ����
		// 2���� : ���� ���Ͽ� �����ϰ��� �ϴ� ������
		// 3���� : �����ϰ��� �ϴ� ������ ũ�� ����
		// 4���� : dwByte ���� 0�̸� ������ ���� ����. 
		ReadFile(file, &info, sizeof(LINEINFO), &byte, NULL);

		if (0 == byte)
			break;

		m_line_list.push_back(new Line(info));
	}

	CloseHandle(file);

	// MessageBox(g_hWnd, _T("Load ����"), _T("Success"), MB_OKCANCEL);

}

void LineManager::PickingLine(void)	// ���� �����ϱ�
{
	POINT	pt{};					// �� ��ǥ�� ������ ����ü ���� ����

	GetCursorPos(&pt);				// Ŀ���� ��ǥ�� �˾ƿ��� �Լ�
	ScreenToClient(g_hWnd, &pt);	// ��ǥ�� ��ȯ�ϴ� �Լ�

	pt.x -= (long)ScrollManager::GetInstance()->GetScrollX();
	// pt�� x ��ǥ -= ��ũ���� ��ŭ

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
//	// linepos�� ������ �迭�� ���� �� ��ǥ 4�� ����
//	LINEPOS point[2] = {
//		{ 100.f, 1474.f },
//		{ 800.f, 1474.f },
//};
//
//	//// ��ǥ 4���� list�� ���ҷ� ������ ���ÿ� line ���� + ���� �̾��ֱ�
//	m_line_list.push_back(new Line(point[0], point[1])); 
	//m_line_list.push_back(new Line(point[1], point[2]));
	//m_line_list.push_back(new Line(point[2], point[3]));
}


bool LineManager::CollisionLine(const float& x_, const float& y_, float* newy_)
{
	if (m_line_list.empty()) // linelist�� ����ִٸ�
		return false;		 // false ��ȯ

	// �� ���� ������ ������ ������
	// y - y1 = ((y2 - y1) / (x2 - x1)) * (x - x1)

	// �÷��̾� y�� ���ϴ� ����
	// y = ((y2 - y1) / (x2 - x1)) * (x - x1) + y1

	Line* min = nullptr;
	float m_distance = -1.f;


	for (auto& iter : m_line_list)		// linelist�� iter�� ����
	{
		// �浹�� ���� ����x ��ǥ���� �ε��� �༮�� x�� ũ��,
		// �浹�� ���� ������ x ��ǥ���� �ε��� �༮�� x�� ���� ��
		if (iter->GetInfo().left_pos.x < x_ &&
			iter->GetInfo().right_pos.x > x_)
		{
			float x1 = iter->GetInfo().left_pos.x;
			float y1 = iter->GetInfo().left_pos.y;

			float x2 = iter->GetInfo().right_pos.x;
			float y2 = iter->GetInfo().right_pos.y;

			float line_y = ((y2 - y1) / (x2 - x1)) * (x_ - x1) + y1;

			// ������Ʈ X���� ������ �����Ŀ� ���������� ������ Y���� ������Ʈ�� Y������ ũ�ٸ�
			if (line_y > y_)
			{
				// ������Ʈ X���� ������ �����Ŀ� ���������� ������ Y���� ������Ʈ�� Y���� �Ÿ��� m_fDistance���� �۴ٸ� �Ǵ� ���� m_fDistance�� �����ٸ�(m_fDistance==-1.f)
				if ((m_distance > (line_y - y_)) || (m_distance == -1.f))
				{
					// ���ǿ� �˸´� �ּ� �Ÿ� ���� �������� m_fDistance�� Min ����
					m_distance = line_y - y_;
					min = iter;
				}
			}
		}
	}

	// Min���� nullptr�� �ƴ϶�� (���ǿ� �´� ������ �־��ٸ�)
	if (min != nullptr)
	{
		float x1 = min->GetInfo().left_pos.x;
		float y1 = min->GetInfo().left_pos.y;

		float x2 = min->GetInfo().right_pos.x;
		float y2 = min->GetInfo().right_pos.y;

		// ������Ʈ Y�� ����
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
	for (auto& iter : m_line_list) // linelist�� iter�� ����
		iter->Render(dc);		   // iter�� ��� ���� �׷���
}

void LineManager::Release(void)
{
	//list ���ۺ��� ������ ��ü �Ҹ� + null �ʱ�ȭ
	for_each(m_line_list.begin(), m_line_list.end(), DeleteObj());
	// list�� ��� ���� ����
	m_line_list.clear();

	/*DeleteObj(m_line_pos);
	DeleteObj(info);*/
}

bool  LineManager::CollisionLineNoDistance(const float& x_, const float& y_, float* newy_)
{
	// ����Ʈ�� ������� ��ȯ
	if (m_line_list.empty())
		return false;

	Line* min = nullptr;		// ���� �˻��ؼ� �˸´� ������ ������ �����ͺ��� (�������� �˻������� ���ǿ� �°�, m_fDistance�� �ּ��� ����)
	float m_distance = -1.f;	// ��� ������ ���ϸ鼭 ���ǿ� �´� ���ΰ� ������Ʈ�� �Ÿ��� ������ ����

								// ����Ʈ ���� ������ ��� �˻�
	for (auto& iter : m_line_list)
	{
		// ���� ������ leftX�� ������Ʈ�� X���� �۰�, rightX�� ������Ʈ�� X���� ũ�ٸ�
		if (iter->GetInfo().left_pos.x < x_ &&
			iter->GetInfo().right_pos.x > x_)
		{
			// ������ �����Ŀ� ������ ���� �ʱ�ȭ
			float x1 = iter->GetInfo().left_pos.x;
			float y1 = iter->GetInfo().left_pos.y;

			float x2 = iter->GetInfo().right_pos.x;
			float y2 = iter->GetInfo().right_pos.y;

			float LineY = (((y2 - y1) / (x2 - x1)) * (x_ - x1) + y1);
			min = iter;
		}
	}

	// Min���� nullptr�� �ƴ϶�� (���ǿ� �´� ������ �־��ٸ�)
	if (min != nullptr)
	{
		float x1 = min->GetInfo().left_pos.x;
		float y1 = min->GetInfo().left_pos.y;

		float x2 = min->GetInfo().right_pos.x;
		float y2 = min->GetInfo().right_pos.y;

		// ������Ʈ Y�� ����
		*newy_ = ((y2 - y1) / (x2 - x1)) * (x_ - x1) + y1;

		return true;
	}

	return false;
}

