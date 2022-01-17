#include "stdafx.h"
#include "bmp_manager.h"

BmpManager*	BmpManager::m_instance = nullptr;

BmpManager::BmpManager()
{
}


BmpManager::~BmpManager()
{
	Release();
}

// ��Ʈ�� �����ϱ�
void BmpManager::InsertBmp(const TCHAR * filepath, const TCHAR * imgkey)
{
	// map�� ���ۺ��� ������ ������ imgkey�� ã�� iter�� ����
	auto	iter = find_if(m_mapbit.begin(), m_mapbit.end(), TagFinder(imgkey));

	// mapbit ������ ������ ������ ����
	if (iter != m_mapbit.end())
		return;


	// ��Ʈ�� �ν��Ͻ�ȭ
	MyBmpMap*	bmp = new MyBmpMap;
	// ��Ʈ�� �ҷ�����
	bmp->LoadBmp(filepath);

	// emplace�� insert�� ���������, ��
	m_mapbit.emplace(imgkey, bmp);
}

HDC BmpManager::FindImage(const TCHAR * pImgKey)			// �̹��� ã�ƿ���
{
	// auto	iter = m_mapBit.find(pImgKey);					// �̹��� ã�Ƽ� iter�� ����

	// mapbit�� ó������ ������ ������ imgkey�� ã�� iter�� ����
	auto	iter = find_if(m_mapbit.begin(), m_mapbit.end(), TagFinder(pImgKey));

	if (iter == m_mapbit.end())		// iter�� mapbit.end�� �����ϸ� nullptr ��ȯ
		return nullptr;

	return iter->second->GetMemDC();	// second?
}

void BmpManager::Release(void)			// �� �����
{
	for_each(m_mapbit.begin(), m_mapbit.end(), DeleteMap());
	m_mapbit.clear();
}
