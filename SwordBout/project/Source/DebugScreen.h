#pragma once

#include "../Library/GameObject.h"
#ifdef _DEBUG
#include <list>
#endif

class DebugScreen : public GameObject {
public:
#ifdef _DEBUG
	DebugScreen();
	explicit DebugScreen(SceneBase* scene);
	~DebugScreen();
	void Draw() override;
	void SetColor(unsigned char r, unsigned char g, unsigned char b) { m_color = GetColor(r, g, b); }
	void Puts(int x, int y, const char* str);
private:
	unsigned int m_color;
	struct String {
		int x, y; // 表示座標
		unsigned int color; // 表示色
		std::string str;
		String(int _x, int _y, unsigned int _color, const char* _str) {
			x = _x; y = _y; color = _color; str = _str;
		}
	};
	std::list<String> m_string;
#else
	DebugScreen() {}
	DebugScreen(SceneBase* scene);
	~DebugScreen() {}
	inline void Draw() override {}
	inline void SetColor(unsigned int color) {}
	inline void Puts(int x, int y, const char* str);
#endif
};

#include "../Library/SceneManager.h"
#include "../Library/SceneBase.h"

inline void DebugPrintf(int x, int y, const char* fmt, ...) {
#ifdef _DEBUG
	va_list list;
	va_start(list, fmt);
	char str[2048];
	vsprintf_s(str, 2048, fmt, list);
//	SceneManager::CommonScene()->FindGameObject<DebugScreen>()->Puts(x, y, str);
	ObjectManager::FindGameObject<DebugScreen>()->Puts(x, y, str);
	va_end(list);
#endif
}

inline void DebugPuts(int x, int y, const char* str) {
#ifdef _DEBUG
//	SceneManager::CommonScene()->FindGameObject<DebugScreen>()->Puts(x, y, str);
	ObjectManager::FindGameObject<DebugScreen>()->Puts(x, y, str);
#endif
}

inline void DebugSetColor(unsigned char r, unsigned char g, unsigned char b) {
#ifdef _DEBUG
//	SceneManager::CommonScene()->FindGameObject<DebugScreen>()->SetColor(r,g,b);
	ObjectManager::FindGameObject<DebugScreen>()->SetColor(r, g, b);
#endif
}
