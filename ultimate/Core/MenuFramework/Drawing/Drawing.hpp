#pragma once

#include "../../Includes/includes.hpp"
#include "../../SDK/RustStructs.h"
#include "../../SDK/UnityEngine/UnityEngine.hpp"
#include <vector>

inline void AnsiToUnicodeRRR(const char* m_szAnsi, wchar_t* m_pBuffer)
{
	for (int i = 0; ; ++i)
	{
		m_pBuffer[i] = static_cast<char>(m_szAnsi[i]);

		if (!m_szAnsi[i])
			return;
	}
}

inline char* itoass(int m_iValue, char* m_pBuffer, int m_iRadix)
{
	auto xtoa = [](int a1, char* a2, int a3, bool a4) -> char
		{
			char* v5; // r10
			char* v6; // r8
			char* v7; // r11
			char* v8; // r9
			unsigned int v9; // edx
			char v10; // al
			char result; // al
			char v12; // cl

			v5 = a2;
			if (a4)
			{
				v5 = a2 + 1;
				*a2 = 45;
				a1 = -a1;
			}
			v6 = v5;
			do
			{
				v7 = v5 + 1;
				v8 = v5;
				v9 = a1 % a3;
				a1 /= a3;
				v10 = 87;
				if (v9 <= 9)
					v10 = 48;
				*v5++ = v9 + v10;
			} while (a1);
			*v7 = 0;
			do
			{
				result = *v6;
				v12 = *v8;
				*v8-- = *v6;
				*v6++ = v12;
			} while (v6 < v8);
			return result;
		};

	bool v3; // r9

	v3 = false;
	if (m_iRadix == 10 && m_iValue < 0)
		v3 = true;
	xtoa(m_iValue, m_pBuffer, m_iRadix, v3);
	return m_pBuffer;
}

inline static float accent_color_[4] = { 252, 3, 98, 255 };
inline float menu_alpha;
inline static bool wakeup{ false };
inline static bool sex{ false };
inline Vector2 window_pos{ 50, 50 }, mouse_pos, next_item_pos, next_color_pos;
inline Vector2 window_sizemain;
inline Vector2 old_mouse_pos;
inline bool mouse_state, insert_state;
inline RustStructs::EventType menu_event;
inline bool main_menu_open = false;
inline bool old_mouse_state, old_insert_state;
inline RustStructs::KeyCode key_code;
inline Vector2 widget_mouse_pos, old_widget_mouse_pos, next_tab_pos, next_subtab_pos;
inline bool widget_state, old_widget_state;
inline float color_picker_alpha;
inline bool is_menu_open{ true };
inline bool interacting;
inline 	bool InsertPressed;
inline 	bool LMBPressed;
inline Vector2 SubTabPos;
inline const wchar_t* keybind_str;
inline int* kbref = 0;
inline int* ref_clicked = 0;
inline bool getting_keybind = false;
inline bool combo_clicked = false;
inline bool true_placehold = true;
inline bool false_placehold = false;
inline bool _ti = false;
inline bool inputting_text = false;
inline RustStructs::KeyCode iSelectedg = RustStructs::KeyCode::Insert;
inline Vector2 window_position = { 650, 200 };
inline Vector2 lmp = { 650, 200 };
inline float opacity = 0.f;
inline int active_tab = 0;
inline Vector2 tab_size;
inline int last_active_id = 0;
inline bool hover_element = false;
inline bool list_clicked = false;
inline int table = 0;
inline int activetab = 0;
inline int activesubtab = 0;
inline int activesubtabv = 0;
inline static bool IsInteractingWidthObject = false;
inline unsigned long long iCurrentOpenedCombo = 0;
inline Vector2 vecLastCringePosition = { 0, 0 };
inline int iOpenedCringeY = 0;
inline int iLastCringeAmount = 0;
inline bool bComboOpenedInThisFrame = false;
static inline bool IsComboOpen = false;
static inline unsigned long long iCurrentSelectedKeybind = 0;

inline void fill_box(UnityEngine::rect_t pos, Color clr)
{
	UnityEngine::Texture2D* white_texture = nullptr;
	if (!white_texture)
	{
		white_texture = UnityEngine::Texture2D::get_whiteTexture();
	}

	UnityEngine::GUI::SetColor(clr.GetUnityColor());
	UnityEngine::GUI::DrawTexture(pos, white_texture);
}


inline void outline_box(Vector2 pos, Vector2 size, Color clr)
{
	UnityEngine::Texture2D* white_texture = nullptr;

	if (!white_texture)
	{
		white_texture = UnityEngine::Texture2D::get_whiteTexture();
	}

	UnityEngine::GUI::SetColor(clr.GetUnityColor());
	UnityEngine::GUI::DrawTexture(UnityEngine::rect_t(pos.x, pos.y, 1, size.y), white_texture);
	UnityEngine::GUI::DrawTexture(UnityEngine::rect_t(pos.x + size.x, pos.y, 1, size.y), white_texture);
	UnityEngine::GUI::DrawTexture(UnityEngine::rect_t(pos.x, pos.y, size.x, 1), white_texture);
	UnityEngine::GUI::DrawTexture(UnityEngine::rect_t(pos.x, pos.y + size.y, size.x, 1), white_texture);
}

inline void Arrow(const Vector2& screensize, float x, float y, Color Color)
{
	//UnityEngine::GL::GlFillRectangle({ x, y }, { 1, 3 }, Color);
	//UnityEngine::GL::GlFillRectangle({ x - 1, y - 1 }, { 1, 3 }, Color);
	//UnityEngine::GL::GlFillRectangle({ x - 2, y - 2 }, { 1, 3 }, Color);
	//UnityEngine::GL::GlFillRectangle({ x - 3, y - 3 }, { 1, 3 }, Color);
	UnityEngine::GL::RectangleFilled({ x, y }, { 1, 3 }, Color.GetUnityColor());
	UnityEngine::GL::RectangleFilled({ x + 1, y + 1 }, { 1, 3 }, Color.GetUnityColor());
	UnityEngine::GL::RectangleFilled({ x + 2, y + 2 }, { 1, 3 }, Color.GetUnityColor());
	UnityEngine::GL::RectangleFilled({ x + 3, y + 1 }, { 1, 3 }, Color.GetUnityColor());
	UnityEngine::GL::RectangleFilled({ x + 4, y }, { 1, 3 }, Color.GetUnityColor());
	UnityEngine::GL::RectangleFilled({ x + 5, y - 1 }, { 1, 3 }, Color.GetUnityColor());
	UnityEngine::GL::RectangleFilled({ x + 6, y - 2 }, { 1, 3 }, Color.GetUnityColor());
	UnityEngine::GL::RectangleFilled({ x + 7, y - 3 }, { 1, 3 }, Color.GetUnityColor());

}

class Menu {
public:
	bool window(UnityEngine::Event* event, wchar_t* title, const Vector2& pos, const Vector2& window_size, bool always_open);
	bool is_mouse_in_box(const Vector2& pos1, const Vector2& pos2);
	void Tab(const wchar_t* name, int id, Vector2 tab_size = Vector2(112, 35));
	void SubTab(const wchar_t* name, int id, Vector2 tab_size = Vector2(112, 35));
	void BeginChild(const wchar_t* title, const Vector2& pos, const Vector2& size);
	void Slider(const wchar_t* szTitle, float& flValue, float iMin, float iMax, bool color = false);
	void Slider(const wchar_t* szTitle, int& iValue, int iMin, int iMax, bool color = false);
	void MultiDropdown(const std::string& title, const std::vector<std::string> items, std::vector<bool>& value, bool& is_open);
	void Dropdown(const std::string& title, const std::vector<std::string> items, int& value, bool& is_open);
	void ListBox(const std::string& title, const std::vector<std::string> items, int& selected_index);
	void Button(const std::string& title, void* callback);
	void Spacer(int size);
	void CheckBox(const wchar_t* szTitle, bool& bValue);
	void Text(const wchar_t* szTitle);
	void CheckBoxKeyBind(const wchar_t* szTitle, bool& bValue, RustStructs::KeyCode& iKey);
	void ColorPicker(const wchar_t* name, Color selectedColor);
	void Hotkey(const wchar_t* szTitle, RustStructs::KeyCode& iKey);
	void end_window();
};