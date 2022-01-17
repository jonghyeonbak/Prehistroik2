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

// 비트맵 저장하기
void BmpManager::InsertBmp(const TCHAR * filepath, const TCHAR * imgkey)
{
	// map의 시작부터 끝까지 뒤져서 imgkey를 찾아 iter에 저장
	auto	iter = find_if(m_mapbit.begin(), m_mapbit.end(), TagFinder(imgkey));

	// mapbit 끝까지 뒤져도 없으면 리턴
	if (iter != m_mapbit.end())
		return;


	// 비트맵 인스턴스화
	MyBmpMap*	bmp = new MyBmpMap;
	// 비트맵 불러오기
	bmp->LoadBmp(filepath);

	// emplace도 insert와 비슷하지만, 생
	m_mapbit.emplace(imgkey, bmp);
}

HDC BmpManager::FindImage(const TCHAR * pImgKey)			// 이미지 찾아오기
{
	// auto	iter = m_mapBit.find(pImgKey);					// 이미지 찾아서 iter에 저장

	// mapbit의 처음부터 끝까지 뒤져서 imgkey를 찾아 iter에 저장
	auto	iter = find_if(m_mapbit.begin(), m_mapbit.end(), TagFinder(pImgKey));

	if (iter == m_mapbit.end())		// iter가 mapbit.end에 도달하면 nullptr 반환
		return nullptr;

	return iter->second->GetMemDC();	// second?
}

void BmpManager::Release(void)			// 맵 지우기
{
	for_each(m_mapbit.begin(), m_mapbit.end(), DeleteMap());
	m_mapbit.clear();
}
