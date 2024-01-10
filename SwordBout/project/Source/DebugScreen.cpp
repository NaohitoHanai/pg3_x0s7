#ifdef _DEBUG
#include "DebugScreen.h"
#include <stdarg.h>

DebugScreen::DebugScreen()
{
	m_string.clear();
	m_color = GetColor(255, 255, 255);
}

DebugScreen::~DebugScreen()
{
	m_string.clear();
}

void DebugScreen::Draw()
{
	for (auto obj : m_string) {
		DrawString(obj.x, obj.y, obj.str.c_str(), obj.color);
	}
	m_string.clear();
}

void DebugScreen::Puts(int x, int y, const char* str)
{
	m_string.emplace_back(String(x, y, m_color, str));
}
#endif