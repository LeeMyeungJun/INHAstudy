#include "stdafx.h"



cFontManager::cFontManager()
{
}


cFontManager::~cFontManager()
{
}

LPD3DXFONT cFontManager::GetFont(eFontType e)
{
	if(m_mapFont.find(e) != m_mapFont.end())
	{
		return  m_mapFont[e];
	}
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

	if(e == E_DEFALUT)//만약에 폰트가 디폴트면
	{
		fd.Height = 25;
		fd.Width = 12;
		fd.Weight = FW_BOLD; //이거는 F12눌르고 타입좀 확인해봐
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		//일단은 시스템에있는 폰트가지고 사용해볼게
		wcscpy_s(fd.FaceName, L"굴림체");
	}
	else if(e == E_QUEST)
	{
		fd.Height = 50;
		fd.Width = 25;
		fd.Weight = FW_MEDIUM; //이거는 F12눌르고 타입좀 확인해봐
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		AddFontResourceA("font/umberto.ttf");
		wcscpy_s(fd.FaceName, L"umberto");
	}

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);
	
	return m_mapFont[e];
}

void cFontManager::Destroy()
{
	for each(auto it in m_mapFont)
	{
		SafeRelease(it.second);
	}
	m_mapFont.clear();
}
