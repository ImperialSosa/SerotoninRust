#include "Drawing.hpp"
#pragma optimize( "", on )


inline const char* GetKey(RustStructs::KeyCode iKey)
{
	switch (iKey)
	{
	case 0:
		return "-";
	case 8:
		return "Backspace";
	case 127:
		return "Delete";
	case 9:
		return "Tab";
	case 12:
		return "Clear";
	case 13:
		return "Return";
	case 19:
		return "Pause";
	case 27:
		return "Escape";
	case 32:
		return "Space";
	case 256:
		return "Keypad0";
	case 257:
		return "Keypad1";
	case 258:
		return "Keypad2";
	case 259:
		return "Keypad3";
	case 260:
		return "Keypad4";
	case 261:
		return "Keypad5";
	case 262:
		return "Keypad6";
	case 263:
		return "Keypad7";
	case 264:
		return "Keypad8";
	case 265:
		return "Keypad9";
	case 266:
		return "KeypadPeriod";
	case 267:
		return "KeypadDivide";
	case 268:
		return "KeypadMultiply";
	case 269:
		return "KeypadMinus";
	case 270:
		return "KeypadPlus";
	case 271:
		return "KeypadEnter";
	case 272:
		return "KeypadEquals";
	case 273:
		return "UpArrow";
	case 274:
		return "DownArrow";
	case 275:
		return "RightArrow";
	case 276:
		return "LeftArrow";
	case 277:
		return "Insert";
	case 278:
		return "Home";
	case 279:
		return "End";
	case 280:
		return "PageUp";
	case 281:
		return "PageDown";
	case 282:
		return "F1";
	case 283:
		return "F2";
	case 284:
		return "F3";
	case 285:
		return "F4";
	case 286:
		return "F5";
	case 287:
		return "F6";
	case 288:
		return "F7";
	case 289:
		return "F8";
	case 290:
		return "F9";
	case 291:
		return "F10";
	case 292:
		return "F11";
	case 293:
		return "F12";
	case 294:
		return "F13";
	case 295:
		return "F14";
	case 296:
		return "F15";
	case 48:
		return "Alpha0";
	case 49:
		return "Alpha1";
	case 50:
		return "Alpha2";
	case 51:
		return "Alpha3";
	case 52:
		return "Alpha4";
	case 53:
		return "Alpha5";
	case 54:
		return "Alpha6";
	case 55:
		return "Alpha7";
	case 56:
		return "Alpha8";
	case 57:
		return "Alpha9";
	case 33:
		return "Exclaim";
	case 34:
		return "DoubleQuote";
	case 35:
		return "Hash";
	case 36:
		return "Dollar";
	case 37:
		return "Percent";
	case 38:
		return "Ampersand";
	case 39:
		return "Quote";
	case 40:
		return "LeftParen";
	case 41:
		return "RightParen";
	case 42:
		return "Asterisk";
	case 43:
		return "Plus";
	case 44:
		return "Comma";
	case 45:
		return "Minus";
	case 46:
		return "Period";
	case 47:
		return "Slash";
	case 58:
		return "Colon";
	case 59:
		return "Semicolon";
	case 60:
		return "Less";
	case 61:
		return "Equals";
	case 62:
		return "Greater";
	case 63:
		return "Question";
	case 64:
		return "At";
	case 91:
		return "LeftBracket";
	case 92:
		return "Backslash";
	case 93:
		return "RightBracket";
	case 94:
		return "Caret";
	case 95:
		return "Underscore";
	case 96:
		return "BackQuote";
	case 97:
		return "A";
	case 98:
		return "B";
	case 99:
		return "C";
	case 100:
		return "D";
	case 101:
		return "E";
	case 102:
		return "F";
	case 103:
		return "G";
	case 104:
		return "H";
	case 105:
		return "I";
	case 106:
		return "J";
	case 107:
		return "K";
	case 108:
		return "L";
	case 109:
		return "M";
	case 110:
		return "N";
	case 111:
		return "O";
	case 112:
		return "P";
	case 113:
		return "Q";
	case 114:
		return "R";
	case 115:
		return "S";
	case 116:
		return "T";
	case 117:
		return "U";
	case 118:
		return "V";
	case 119:
		return "W";
	case 120:
		return "X";
	case 121:
		return "Y";
	case 122:
		return "Z";
	case 123:
		return "LeftCurlyBracket";
	case 124:
		return "Pipe";
	case 125:
		return "RightCurlyBracket";
	case 126:
		return "Tilde";
	case 300:
		return "Numlock";
	case 301:
		return "CapsLock";
	case 302:
		return "ScrollLock";
	case 303:
		return "RightShift";
	case 304:
		return "LeftShift";
	case 305:
		return "RightControl";
	case 306:
		return "LeftControl";
	case 307:
		return "RightAlt";
	case 308:
		return "LeftAlt";
	case 309:
		return "Left Windows";
	case 310:
		return "Right Windows";
	case 311:
		return "LeftWindows";
	case 312:
		return "RightWindows";
	case 313:
		return "AltGr";
	case 315:
		return "Help";
	case 316:
		return "Print";
	case 317:
		return "SysReq";
	case 318:
		return "Break";
	case 319:
		return "Menu";
	case 323:
		return "Mouse0";
	case 324:
		return "Mouse1";
	case 325:
		return "Mouse2";
	case 326:
		return "Mouse3";
	case 327:
		return "Mouse4";
	case 328:
		return "Mouse5";
	case 329:
		return "Mouse6";
	case 900:
		return "Left mouse";
	case 901:
		return "Right mouse";
	case 902:
		return "Middle button";
	}

	char str[128];
	sprintf(str, XS("%s"), iKey);

	return str;
}

bool Menu::window(UnityEngine::Event* event, wchar_t* title, const Vector2& pos, const Vector2& window_size, bool always_open)
{
	if (!sex) {
		window_pos = pos;
		sex = true;
	}
	auto mouse = UnityEngine::Input::GetMousePosition();
	auto width = UnityEngine::Screen::get_width();
	auto height = UnityEngine::Screen::get_height();

	window_sizemain = window_size;
	menu_event = event->Type();
	key_code = UnityEngine::Event::get_keyCode(event);
	insert_state = menu_event == RustStructs::EventType::KeyDown && key_code == RustStructs::KeyCode::Insert;
	mouse_pos.x = UnityEngine::Input::GetMousePosition().x;
	mouse_pos.y = UnityEngine::Screen::get_height() - UnityEngine::Input::GetMousePosition().y;
	mouse_state = UnityEngine::Input::GetMouseButton(0);
	if (insert_state && !old_insert_state && !always_open)
		is_menu_open = !is_menu_open;
	if (is_mouse_in_box({ window_pos.x, window_pos.y }, { window_pos.x + window_size.x, window_pos.y + window_size.y }) && mouse_state && is_menu_open && main_menu_open && !hover_element) {

		if (!IsInteractingWidthObject)
		{
			int newPosX = window_pos.x + mouse_pos.x - old_mouse_pos.x;
			int newPosY = window_pos.y + mouse_pos.y - old_mouse_pos.y;

			// Adjust new position to ensure the window stays inside the screen
			if (newPosX < 0) {
				newPosX = 0;
			}
			if (newPosX + window_size.x > width) {
				newPosX = width - window_size.x;
			}
			if (newPosY < 0) {
				newPosY = 0;
			}
			if (newPosY + window_size.y > height) {
				newPosY = height - window_size.y;
			}

			window_pos.x = newPosX;
			window_pos.y = newPosY;
		}

	}
	else {
		hover_element = false;
	}

	if (menu_event == RustStructs::EventType::Repaint && is_menu_open)
	{

		/* BackGround */
		UnityEngine::GL().RectangleFilled(Vector2(window_pos), Vector2(window_pos + window_size), Color(22.f, 22.f, 22.f, 255.f).GetUnityColor());

		/* Side + Top bar */
		UnityEngine::GL().RectangleFilled(Vector2(window_pos), Vector2(window_pos.x + window_size.x, window_pos.y + 35), Color(28, 28, 28, 255.f).GetUnityColor());
		UnityEngine::GL().RectangleFilled(Vector2(window_pos), Vector2(window_pos.x + 50, window_pos.y + window_size.y), Color(28, 28, 28, 255.f).GetUnityColor());

		/* BackGround Outline */
		UnityEngine::GL().Rectangle(Vector2(window_pos), Vector2(window_pos + window_size), Color(0, 0, 0, 255.f).GetUnityColor());
	}
	next_tab_pos = { window_pos.x, window_pos.y + 55 };
	next_subtab_pos = { window_pos.x + 50, window_pos.y };
	return true;
}

void Menu::end_window() {
	if (!mouse_state) {
		IsInteractingWidthObject = false;
	}


	old_insert_state = insert_state;
	old_mouse_pos = mouse_pos;
	old_mouse_state = mouse_state;
}


//inline auto resolve_icon(int index) -> const char* {
//
//	switch (index)
//	{
//	case 0:
//		return SECURE("accuracy.png");
//	case 1:
//		return SECURE("eye.png");
//	case 2:
//		return SECURE("settings.png");
//	case 3:
//		return SECURE("download (3).png");
//	case 4:
//		return SECURE("palette.png");
//	}
//
//	return SECURE("");
//}

void Menu::Tab(const wchar_t* name, int id, Vector2 tab_size) {

	if (!is_menu_open)
		return;

	float spacer = 5.f;

	if (is_mouse_in_box({ next_tab_pos.x + spacer, next_tab_pos.y - 25 }, { next_tab_pos.x + spacer + 45 ,next_tab_pos.y + 5 + tab_size.y - 15 }) && mouse_state) {
		IsInteractingWidthObject = true;
	}

	if (is_mouse_in_box({ next_tab_pos.x + spacer, next_tab_pos.y - 25 }, { next_tab_pos.x + spacer + 45 ,next_tab_pos.y + 5 + tab_size.y - 15 }) && mouse_state && !old_mouse_state && !interacting)
	{
		activetab = id;
		hover_element = true;
	}

	static int CachedSubTab = 0;
	static int CachedTab = 0;
	if (activetab != CachedTab) {
		activesubtab = 0;
		CachedTab = activetab;
	}

	bool isHovered = is_mouse_in_box({ next_tab_pos.x + spacer, next_tab_pos.y - 25 }, { next_tab_pos.x + spacer + 45 ,next_tab_pos.y + tab_size.y - 15 });
	bool isActive = activetab == id;
	if (menu_event == RustStructs::EventType::Repaint)
	{
		Color txt2 = isHovered ? Color(77, 75, 75, 255.f) : Color(accent_color_[0], accent_color_[1], accent_color_[2], accent_color_[3]);
		Color clrr;
		if (isActive)
		{
			//UnityEngine::GL::Line(Vector2{ next_tab_pos.x + 50, next_tab_pos.y + tab_size.y - 15 }, Vector2{ next_tab_pos.x + 50, next_tab_pos.y + tab_size.y - 55 }, Color(accent_color_[0], accent_color_[1], accent_color_[2], 255.f).GetUnityColor());
			//outline_box(Vector2{ next_tab_pos.x + 50, next_tab_pos.y + tab_size.y - 15 }, Vector2{ next_tab_pos.x + 50, next_tab_pos.y + tab_size.y - 55 }, Color(accent_color_[0], accent_color_[1], accent_color_[2], 255.f).GetUnityColor());

			clrr = isActive ? Color(accent_color_[0], accent_color_[1], accent_color_[2], accent_color_[3]) : txt2;
		}
		else
		{
			clrr = isHovered ? Color(166, 166, 166, 255.f) : Color(77, 75, 75, 255.f);
		}

		const char* icon1;

		switch (id)
		{
		case 0:
			icon1 = ("accuracy.png");
			break;
		case 1:
			icon1 = ("eye.png");
			break;
		case 2:
			icon1 = ("settings.png");
			break;
		case 3:
			icon1 = ("download_3.png");
			break;
		case 4:
			icon1 = ("palette.png");
			break;
		}

		auto texture = MenuIconBundles->LoadAsset<UnityEngine::Texture2D>(icon1, (Il2CppType*)CIl2Cpp::FindType(CIl2Cpp::FindClass(XS("UnityEngine"), XS("Texture"))));

		UnityEngine::GL().DrawIcon(Vector2(next_tab_pos.x + 5 + tab_size.x / 2 - 55, next_tab_pos.y + tab_size.y / 2 - 30), Vector2(35.f, 35.f), texture, clrr.GetUnityColor());
	}
	//next_tab_pos.x += 112;
	next_tab_pos.y += 42;
}

void Menu::SubTab(const char* name, int id, Vector2 tab_size) {

	if (!is_menu_open)
		return;

	if (is_mouse_in_box({ next_subtab_pos.x + 5, next_subtab_pos.y + 5 }, { next_subtab_pos.x + 5 + tab_size.x,next_subtab_pos.y + 5 + tab_size.y }) && mouse_state && !old_mouse_state && !interacting)
	{
		activesubtab = id;
		hover_element = true;
	}

	bool isHovered = is_mouse_in_box({ next_subtab_pos.x + 5, next_subtab_pos.y + 5 }, { next_subtab_pos.x + 5 + tab_size.x,next_subtab_pos.y + 5 + tab_size.y });

	if (menu_event == RustStructs::EventType::Repaint)
	{
		Color txt = isHovered ? Color(255.f, 255.f, 255.f, 255.f) : Color(166, 166, 166, 255.f);
		Color Active = Color(accent_color_[0], accent_color_[1], accent_color_[2], 255.f);
		//UnityEngine::GL().MenuText(UnityEngine::gui_style, next_subtab_pos.x + 5 + tab_size.x / 2 - 5, next_subtab_pos.y + tab_size.y / 2, tab_size.x, tab_size.y, (name), txt.GetUnityColor(), true, true);
		UnityEngine::GL().MenuText(Vector2(next_subtab_pos.x + 5 + tab_size.x / 2 - 5, next_subtab_pos.y + tab_size.y / 2), txt.GetUnityColor(), Color::Black(), name, true);

		if (id == activesubtab) {
			//UnityEngine::GL().Rectangle({ next_subtab_pos.x, next_subtab_pos.y }, { tab_size.x - 1, tab_size.y }, Color(accent_color_[0], accent_color_[1], accent_color_[2], 255.f));
			//UnityEngine::GL::Line(Vector2{ next_subtab_pos.x, next_subtab_pos.y + tab_size.y }, Vector2{ next_subtab_pos.x + tab_size.x - 1 , next_subtab_pos.y + tab_size.y }, Color(accent_color_[0], accent_color_[1], accent_color_[2], 255.f).GetUnityColor());
			//outline_box(Vector2{ next_subtab_pos.x, next_subtab_pos.y + tab_size.y }, Vector2{ next_subtab_pos.x + tab_size.x - 1 , next_subtab_pos.y + tab_size.y }, Color(accent_color_[0], accent_color_[1], accent_color_[2], 255.f).GetUnityColor());
			//UnityEngine::GL().MenuText(UnityEngine::gui_style, next_subtab_pos.x + 5 + tab_size.x / 2 - 5, next_subtab_pos.y + tab_size.y / 2, tab_size.x, tab_size.y, (name), Active.GetUnityColor(), true, true);

			UnityEngine::GL().Line(Vector2(next_subtab_pos.x, next_subtab_pos.y + tab_size.y), Vector2(next_subtab_pos.x + tab_size.x, next_subtab_pos.y + tab_size.y), Color::White());

			UnityEngine::GL().MenuText(Vector2(next_subtab_pos.x + 5 + tab_size.x / 2 - 5, next_subtab_pos.y + tab_size.y / 2), Active.GetUnityColor(), Color::Black(), name, true);
		}
	}
	next_subtab_pos.x += tab_size.x; //112
}

void Menu::BeginChild(const char* title, const Vector2& pos, const Vector2& size)
{
	if (!is_menu_open)
		return;

	if (menu_event == RustStructs::EventType::Repaint)
	{
		auto AccentColor = Color(accent_color_[0], accent_color_[1], accent_color_[2], accent_color_[3]);

		UnityEngine::GL().RectangleFilled(Vector2(window_pos + pos), Vector2(window_pos + pos + size), Color(28, 28, 28, 255.f).GetUnityColor());
		UnityEngine::GL().Rectangle(Vector2(window_pos + pos), Vector2(window_pos + pos + size), AccentColor.GetUnityColor());

		UnityEngine::GL().MenuText(Vector2(window_pos.x + pos.x + 15.f, window_pos.y + pos.y - 10.f), AccentColor.GetUnityColor(), Color::Black(), title, false);
	}
	next_item_pos = { window_pos.x + pos.x + 10, window_pos.y + pos.y + 15 };
}

void Menu::Hotkey(const char* szTitle, RustStructs::KeyCode& iKey)
{
	if (!is_menu_open)
		return;


	if (is_mouse_in_box(Vector2(next_item_pos.x, next_item_pos.y + 20), Vector2(next_item_pos.x + 80, next_item_pos.y + 20 + 28)) && mouse_state) {
		IsInteractingWidthObject = true;
	}

	static bool bWaited = false;

	bool bCringe = false;

	if (bWaited && iCurrentSelectedKeybind != Hash(szTitle, false))
		bCringe = true;

	if (bWaited && !bCringe)
	{
		iKey = RustStructs::Nonez;
		/* Handle mouse */
		if (UnityEngine::Input::GetMouseButton(0))
		{
			iKey = RustStructs::Mouse0;
			bWaited = false;
		}
		else if (UnityEngine::Input::GetMouseButton(1))
		{
			iKey = RustStructs::Mouse1;
			bWaited = false;
		}
		else if (UnityEngine::Input::GetMouseButton(2))
		{
			iKey = RustStructs::Mouse3;
			bWaited = false;
		}
		else if (UnityEngine::Input::GetMouseButton(4))
		{
			iKey = RustStructs::Mouse4;
			bWaited = false;
		}

		if (menu_event == RustStructs::EventType::KeyUp)
		{
			iKey = (key_code);
			bWaited = false;
		}
	}

	bool bHovered = false;

	if (is_mouse_in_box(Vector2(next_item_pos.x, next_item_pos.y + 20), Vector2(next_item_pos.x + 80, next_item_pos.y + 20 + 28)))
	{
		iCurrentSelectedKeybind = Hash(szTitle, false);
		bHovered = true;

		if (mouse_state && (!old_mouse_state || !bComboOpenedInThisFrame) && !interacting) {
			bWaited = true;
			hover_element = true;

		}
	}
	/* Dont draw if combo opened */
	if (bComboOpenedInThisFrame && vecLastCringePosition.x == next_item_pos.x && vecLastCringePosition.y > next_item_pos.y + 24 + 20 + 6 && iOpenedCringeY < next_item_pos.y)
	{
		//	next_item_pos.y += 38;
		return;
	}

	if (menu_event == RustStructs::EventType::Repaint)
	{
		UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x, next_item_pos.y + 30), Vector2(next_item_pos.x + 80, next_item_pos.y + 50), Color(61, 61, 61, 255.f).GetUnityColor());
		UnityEngine::GL().Rectangle(Vector2(next_item_pos.x, next_item_pos.y + 30), Vector2(next_item_pos.x + 80, next_item_pos.y + 50), Color(0, 0, 0, 255.f).GetUnityColor());

		Color cNotReadColor = bHovered ? Color(189.f, 189.f, 189.f, 255.f) : Color(255.f, 255.f, 255.f, 0.6 * 255.f);
		Color cTextColor = bWaited ? Color(accent_color_[0], accent_color_[1], accent_color_[2], 255.f) : cNotReadColor;

		auto key = iKey == 0 ? std::string(XS("Unbinded")) : std::string(XS("")) + GetKey((RustStructs::KeyCode)iKey);

		UnityEngine::GL().MenuText(Vector2(next_item_pos.x + static_cast<float>(80) / 2, next_item_pos.y + 40), cTextColor.GetUnityColor(), Color::Black(), key.c_str(), false);
	}


	next_item_pos.y += 50;
}

void Menu::Spacer(int size)
{
	if (!is_menu_open)
		return;

	next_item_pos.y += size;
}

void Menu::Button(const std::string& title, void* callback) {
	if (!is_menu_open)
		return;

	if (is_mouse_in_box({ next_item_pos.x - 25, next_item_pos.y + 16 }, { next_item_pos.x - 25 + 196, next_item_pos.y + 16 + 20 }) && mouse_state) {
		IsInteractingWidthObject = true;
	}

	bool isHovered = is_mouse_in_box({ next_item_pos.x - 25, next_item_pos.y + 16 }, { next_item_pos.x - 25 + 196, next_item_pos.y + 16 + 20 });

	Color txt = isHovered ? Color(23, 23, 23, 255.f) : Color(61, 61, 61, 255.f);


	const auto wstring = std::string(title.begin(), title.end());

	if (menu_event == RustStructs::EventType::Repaint)
		UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x, next_item_pos.y + 16), Vector2(next_item_pos.x + 140, next_item_pos.y + 36), txt.GetUnityColor());


	if (is_mouse_in_box({ next_item_pos.x - 25, next_item_pos.y + 16 }, { next_item_pos.x - 25 + 196, next_item_pos.y + 16 + 20 }) && mouse_state && !old_mouse_state)
	{
		if (menu_event == RustStructs::EventType::Repaint)
			UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x, next_item_pos.y + 16), Vector2(next_item_pos.x + 140, next_item_pos.y + 36), Color(23, 23, 23, 255.f).GetUnityColor());


		if (callback != 0x0)
			reinterpret_cast<void(*)(void)>(callback)();
	}

	if (menu_event == RustStructs::EventType::Repaint)
	{
		UnityEngine::GL().Rectangle(Vector2(next_item_pos.x, next_item_pos.y + 16), Vector2(next_item_pos.x + 140, next_item_pos.y + 36), Color(52, 52, 52, 255.f).GetUnityColor());

		UnityEngine::GL().MenuText(Vector2(next_item_pos.x + 140 / 2, next_item_pos.y + 27), Color::White(), Color::Black(), wstring.c_str(), true);
	}

	next_item_pos.y += 25;
}

void Menu::ListBox(const std::string& title, const std::vector<std::string> items, int& selected_index)
{
	if (!is_menu_open)
		return;


	const auto wstring = std::wstring(title.begin(), title.end());

	for (size_t idx{ 0 }; idx < items.size(); idx++) {

		if (is_mouse_in_box({ next_item_pos.x, next_item_pos.y + (idx * 18) }, { next_item_pos.x + 100, next_item_pos.y + (idx * 18) + 15 }) && mouse_state) {
			IsInteractingWidthObject = true;
		}

		if (is_mouse_in_box({ next_item_pos.x, next_item_pos.y + (idx * 18) }, { next_item_pos.x + 100, next_item_pos.y + (idx * 18) + 15 }) && mouse_state && !old_mouse_state && !interacting)
			selected_index = idx;
	}

	if (menu_event == RustStructs::EventType::Repaint)
	{
		for (size_t idx{ 0 }; idx < items.size(); idx++) {
			const auto current_item = std::wstring(items.at(idx).begin(), items.at(idx).end());
			auto cleaned = current_item.substr(current_item.find_last_of(L"\\") + 1);


			Color clr = idx == selected_index ? Color(255, 255, 255, 255.f).GetUnityColor() : Color(54, 54, 54, 255.f).GetUnityColor();

			char str[128];
			sprintf(str, XS("%s"), cleaned.c_str());

			UnityEngine::GL().MenuText(Vector2(next_item_pos.x + 7, next_item_pos.y + (idx * 18)), clr.GetUnityColor(), Color::Black(), str, false);
		}

		UnityEngine::GL().Rectangle(Vector2(next_item_pos), Vector2(next_item_pos.x + 130, next_item_pos.y + (items.size() * 18) + 10.f), Color(52, 52, 52, 255.f).GetUnityColor());
	}

	next_item_pos.y += (items.size() * 18) + 10.f;
}

void Menu::Text(const char* szTitle) {
	if (!is_menu_open)
		return;

	if (bComboOpenedInThisFrame && vecLastCringePosition.x == next_item_pos.x && vecLastCringePosition.y > next_item_pos.y + 24 + 20 && iOpenedCringeY < next_item_pos.y)
	{
		return;
	}

	bool isHovered = is_mouse_in_box({ next_item_pos.x - 6, next_item_pos.y }, { next_item_pos.x + 16 + 80.f, next_item_pos.y + 10 });

	if (is_mouse_in_box({ next_item_pos.x - 6, next_item_pos.y }, { next_item_pos.x + 16 + 80.f, next_item_pos.y + 10 }) && mouse_state && !old_mouse_state && !interacting && !bComboOpenedInThisFrame) {
		hover_element = true;
	}

	if (menu_event == RustStructs::EventType::Repaint)
	{
		UnityEngine::GL().MenuText(Vector2(next_item_pos.x + 17, next_item_pos.y - 4), Color::White(), Color::Black(), szTitle, false);
	}
	next_item_pos.y += 15;
}

void Menu::CheckBox(const char* szTitle, bool& bValue) {
	if (!is_menu_open)
		return;

	if (is_mouse_in_box({ next_item_pos.x - 6, next_item_pos.y }, { next_item_pos.x + 10 + 80.f, next_item_pos.y + 10 }) && mouse_state) {
		IsInteractingWidthObject = true;
	}

	if (bComboOpenedInThisFrame && vecLastCringePosition.x == next_item_pos.x && vecLastCringePosition.y > next_item_pos.y + 24 + 20 && iOpenedCringeY < next_item_pos.y)
	{
		return;
	}

	bool isHovered = is_mouse_in_box({ next_item_pos.x - 6, next_item_pos.y }, { next_item_pos.x + 16 + 80.f, next_item_pos.y + 10 });

	if (is_mouse_in_box({ next_item_pos.x - 6, next_item_pos.y }, { next_item_pos.x + 16 + 80.f, next_item_pos.y + 10 }) && mouse_state && !old_mouse_state && !interacting && !bComboOpenedInThisFrame) {
		bValue = !bValue;
		hover_element = true;
	}

	if (menu_event == RustStructs::EventType::Repaint)
	{

		//fill_box({ next_item_pos.x, next_item_pos.y , 11, 11 }, Color(34, 34, 34, 255.f));
		UnityEngine::GL().RectangleFilled(Vector2(next_item_pos), Vector2(next_item_pos.x + 11, next_item_pos.y + 10), Color(34, 34, 34, 255.f).GetUnityColor());

		if (bValue)
			UnityEngine::GL().RectangleFilled(Vector2(next_item_pos), Vector2(next_item_pos.x + 11, next_item_pos.y + 10), Color(accent_color_[0], accent_color_[1], accent_color_[2], 255.f).GetUnityColor());

		UnityEngine::GL().Rectangle(Vector2(next_item_pos), Vector2(next_item_pos.x + 11, next_item_pos.y + 11), Color(0, 0, 0, 255.f).GetUnityColor());

		Color txt = isHovered ? Color(77, 75, 75, 255.f) : Color(224.f, 224.f, 224.f, 255.f);

		Color cText = bValue ? Color(224.f, 224.f, 224.f, 255.f) : Color(255.f, 255.f, 255.f, 0.6 * 255.f);

		// Render text
		UnityEngine::GL().MenuText(Vector2(next_item_pos.x + 17, next_item_pos.y - 4), txt.GetUnityColor(), Color::Black(), szTitle, false);
	}
	next_item_pos.y += 15;
}

void Menu::CheckBoxKeyBind(const char* szTitle, bool& bValue, RustStructs::KeyCode& iKey) {
	if (!is_menu_open)
		return;

	if (is_mouse_in_box({ next_item_pos.x - 6, next_item_pos.y }, { next_item_pos.x + 16 + 80.f, next_item_pos.y + 10 }) && mouse_state) {
		IsInteractingWidthObject = true;
	}

	if (bComboOpenedInThisFrame && vecLastCringePosition.x == next_item_pos.x && vecLastCringePosition.y > next_item_pos.y + 24 + 20 && iOpenedCringeY < next_item_pos.y)
	{
		return;
	}

	bool isHovered = is_mouse_in_box({ next_item_pos.x - 6, next_item_pos.y }, { next_item_pos.x + 16 + 80.f, next_item_pos.y + 10 });

	if (is_mouse_in_box({ next_item_pos.x - 6, next_item_pos.y }, { next_item_pos.x + 16 + 80.f, next_item_pos.y + 10 }) && mouse_state && !old_mouse_state && !interacting && !bComboOpenedInThisFrame) {
		bValue = !bValue;
		hover_element = true;
	}

	if (menu_event == RustStructs::EventType::Repaint)
	{
		UnityEngine::GL().RectangleFilled(Vector2(next_item_pos), Vector2(next_item_pos.x + 11, next_item_pos.y + 10), Color(34, 34, 34, 255.f).GetUnityColor());

		if (bValue)
			UnityEngine::GL().RectangleFilled(Vector2(next_item_pos), Vector2(next_item_pos.x + 11, next_item_pos.y + 10), Color(accent_color_[0], accent_color_[1], accent_color_[2], 255.f).GetUnityColor());

		UnityEngine::GL().Rectangle(Vector2(next_item_pos), Vector2(next_item_pos.x + 11, next_item_pos.y + 11), Color(0, 0, 0, 255.f).GetUnityColor());

		Color txt = isHovered ? Color(77, 75, 75, 255.f) : Color(224.f, 224.f, 224.f, 255.f);

		Color cText = bValue ? Color(224.f, 224.f, 224.f, 255.f) : Color(255.f, 255.f, 255.f, 0.6 * 255.f);
		// Render text

		UnityEngine::GL().MenuText(Vector2(next_item_pos.x + 17, next_item_pos.y - 4), txt.GetUnityColor(), Color::Black(), szTitle, false);
	}
	next_item_pos.y += 15;

	/////////////////////////////////////////////

	float keybindwidth = 80.f;
	float keybindheight = 15.f;
	float keybindheightpos = -15.f;
	float keybindwidthpos = 120.f;
	if (is_mouse_in_box(Vector2(next_item_pos.x + keybindwidthpos, (next_item_pos.y - 15) + keybindheightpos), Vector2(next_item_pos.x + keybindwidth + keybindwidthpos, (next_item_pos.y - 15) + keybindheightpos + 28)) && mouse_state) {
		IsInteractingWidthObject = true;
	}

	static bool bWaited = false;

	bool bCringe = false;

	if (bWaited && iCurrentSelectedKeybind != Hash(szTitle, false))
		bCringe = true;

	if (bWaited && !bCringe)
	{
		iKey = RustStructs::Nonez;
		/* Handle mouse */
		if (UnityEngine::Input::GetMouseButton(0))
		{
			iKey = RustStructs::Mouse0;
			bWaited = false;
		}
		else if (UnityEngine::Input::GetMouseButton(1))
		{
			iKey = RustStructs::Mouse1;
			bWaited = false;
		}
		else if (UnityEngine::Input::GetMouseButton(2))
		{
			iKey = RustStructs::Mouse3;
			bWaited = false;
		}
		else if (UnityEngine::Input::GetMouseButton(4))
		{
			iKey = RustStructs::Mouse4;
			bWaited = false;
		}

		if (menu_event == RustStructs::EventType::KeyUp)
		{
			iKey = (key_code);
			bWaited = false;
		}
	}

	bool bHovered = false;

	if (is_mouse_in_box(Vector2(next_item_pos.x + keybindwidthpos, (next_item_pos.y + 3) + keybindheightpos), Vector2(next_item_pos.x + keybindwidth + keybindwidthpos, (next_item_pos.y - 15) + keybindheightpos + 25)))
	{
		iCurrentSelectedKeybind = Hash(szTitle, false);
		bHovered = true;

		if (mouse_state && (!old_mouse_state || !bComboOpenedInThisFrame) && !interacting) {
			bWaited = true;
			hover_element = true;

		}
	}
	/* Dont draw if combo opened */
	if (bComboOpenedInThisFrame && vecLastCringePosition.x == next_item_pos.x && vecLastCringePosition.y > (next_item_pos.y - 15) + 24 + 20 + 6 && iOpenedCringeY < (next_item_pos.y - 15))
	{
		//	next_item_pos.y += 38;
		return;
	}

	if (menu_event == RustStructs::EventType::Repaint)
	{
		UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x + keybindwidthpos, (next_item_pos.y - 15) + (keybindheightpos + 15)), Vector2(next_item_pos.x + keybindwidthpos + keybindwidth, (next_item_pos.y - 15) + (keybindheightpos + 15) + keybindheight), Color(34, 34, 34, 255.f).GetUnityColor());
		UnityEngine::GL().Rectangle(Vector2(next_item_pos.x + keybindwidthpos, (next_item_pos.y - 15) + (keybindheightpos + 15)), Vector2(next_item_pos.x + keybindwidthpos + keybindwidth, (next_item_pos.y - 15) + (keybindheightpos + 15) + keybindheight), Color(0, 0, 0, 255.f).GetUnityColor());

		Color cNotReadColor = bHovered ? Color(189.f, 189.f, 189.f, 255.f) : Color(255.f, 255.f, 255.f, 0.6 * 255.f);
		Color cTextColor = bWaited ? Color(accent_color_[0], accent_color_[1], accent_color_[2], 255.f) : cNotReadColor;

		//auto key = iKey == 0 ? std::wstring(XS(L"no key")) : std::wstring(XS(L"key: ")) + GetKey((RustStructs::KeyCode)iKey);
		auto key = iKey == 0 ? std::string(XS("Unbinded")) : std::string(XS("")) + GetKey((RustStructs::KeyCode)iKey);

		UnityEngine::GL().MenuText(Vector2(next_item_pos.x + static_cast<float>(keybindwidth) / 2 + keybindwidthpos, (next_item_pos.y - 7) + (keybindheightpos) + keybindheight), cTextColor.GetUnityColor(), Color::Black(), key.c_str(), true);
	}


	//next_item_pos.y += 15;
}

enum class WidgetType
{
	None,
	WColorPicker,
	WComboBox
};

struct ColorPickerWidget
{
	Vector2 position;
	Vector2 size;
	Color selectedColor;
	WidgetType type;
	bool hovered;
};

ColorPickerWidget currentColorPicker;


bool is_mouse_hovering(const Vector2& pos1, const Vector2& pos2) {
	if (old_mouse_pos.x < pos1.x || old_mouse_pos.y < pos1.y)
		return false;

	if (old_mouse_pos.x > pos2.x || old_mouse_pos.y > pos2.y)
		return false;

	// If the next_item_pos is within the box, return true.
	return true;
}

Color HSVToRGB(float h, float s, float v)
{
	int i;
	float f, p, q, t;
	if (s == 0)
	{
		// Achromatic (gray)
		return { v, v, v };
	}
	h /= 60; // sector 0 to 5
	i = static_cast<int>(Math::floor(h));
	f = h - i; // fractional part of h
	p = v * (1 - s);
	q = v * (1 - s * f);
	t = v * (1 - s * (1 - f));

	switch (i)
	{
	case 0:
		return { v, t, p };
	case 1:
		return { q, v, p };
	case 2:
		return { p, v, t };
	case 3:
		return { p, q, v };
	case 4:
		return { t, p, v };
	default: // case 5:
		return { v, p, q };
	}
}

bool niggerr = false;
void DrawColorPickerBox(const Vector2& position, const Vector2& size)
{

	UnityEngine::Texture2D* texture = UnityEngine::Texture2D().New(size.x, size.y);

	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			// Calculate the hue value based on the x position
			float hue = (float)x / (float)size.x;

			// Convert the hue to RGB color
			Color color = Color(hue, (float)y / size.y <= 0.f ? 1.f : (float)y / size.y, 1.f);
			if (x == mouse_pos.x && y == mouse_pos.y && mouse_state && !old_mouse_state && !interacting && !bComboOpenedInThisFrame)
			{
				// Set the pixel color based on the mouse position
				color.m_red = mouse_pos.x;
				color.m_green = mouse_pos.y;
			}
			// Set the pixel color in the texture
			texture->SetPixel(x, y, color);
		}
	}
	// Apply the texture changes
	texture->Apply();

	UnityEngine::GUI::DrawTexture(UnityEngine::rect_t(next_item_pos.x, next_item_pos.y, size.x, size.y), texture);
	next_item_pos.y += 20;
	//DrawFilledBox({ position.x - 5.f, position.y - 5.f, size.x + 10.f, size.y + 10.f }, { 37.f, 37.f, 41.f, 255.f });
	//DrawFilledBox({ position.x, position.y, size.x, size.y }, { 255.f, 255.f, 255.f, 255.f }, ColorPickerTexture);
}

void Menu::Slider(const char* szTitle, float& flValue, float iMin, float iMax, bool color)
{
	if (!is_menu_open)
		return;

	float slidersize = 190.f;

	if (is_mouse_in_box({ next_item_pos.x, next_item_pos.y + 20 }, { next_item_pos.x + slidersize + 0.1f, next_item_pos.y + 35 }) && mouse_state) {
		IsInteractingWidthObject = true;
	}

	bool bHovered = false;
	if (bComboOpenedInThisFrame && vecLastCringePosition.x == next_item_pos.x && vecLastCringePosition.y > next_item_pos.y + 14 + 20 + 6 && iOpenedCringeY < next_item_pos.y)
	{
		//next_item_pos.y += 20 + 20 + 6 + 20;
		return;
	}


	if (is_mouse_in_box({ next_item_pos.x, next_item_pos.y + 20 }, { next_item_pos.x + slidersize + 0.1f, next_item_pos.y + 35 }) && !bComboOpenedInThisFrame)
	{
		bHovered = true;
		if (mouse_state && (!old_mouse_state || !bComboOpenedInThisFrame) && !interacting)
		{
			if (old_mouse_pos.x < next_item_pos.x)
				flValue = static_cast <float>(iMin);
			else if (old_mouse_pos.x > next_item_pos.x + slidersize + 0.1f)
				flValue = static_cast <float>(iMax);
			else
				flValue = static_cast <float> ((old_mouse_pos.x - (next_item_pos.x)) * (iMax - iMin) / slidersize + 0.1f);
			hover_element = true;
		}
	}

	if (menu_event == RustStructs::EventType::Repaint)
	{


		Color cLableColor = bHovered ? Color(77, 75, 75, 255.f) : Color(189.f, 189.f, 189.f, 255.f);

		/* Render lable name */
		UnityEngine::GL().MenuText(Vector2(next_item_pos.x, next_item_pos.y), cLableColor.GetUnityColor(), Color::Black(), szTitle, false);

		/* Convert text */
		char szValue[64];
		char wszValue[64];

		// Conversion without itoass
		int intValue = static_cast<int>(flValue);
		int length = 0;
		do
		{
			int digit = intValue % 10;
			szValue[length++] = static_cast<char>('0' + digit);
			intValue /= 10;
		} while (intValue > 0);

		// Reverse the string
		for (int i = 0; i < length / 2; ++i)
		{
			char temp = szValue[i];
			szValue[i] = szValue[length - i - 1];
			szValue[length - i - 1] = temp;
		}
		szValue[length] = '\0';

		// Convert to wide char
		for (int i = 0; i < length; ++i)
		{
			wszValue[i] = static_cast<wchar_t>(szValue[i]);
		}
		wszValue[length] = '\0';

		int iValueToAddForText = 0;

		/* Cringe hardcode to normalize text */
		if (flValue >= 10000)
			iValueToAddForText = -5;
		else if (flValue >= 1000)
			iValueToAddForText = 1;
		else if (flValue >= 100)
			iValueToAddForText = 8;
		else if (flValue >= 10)
			iValueToAddForText = 15;
		else if (flValue >= 0)
			iValueToAddForText = 20;

		/* Render value text*/
		UnityEngine::GL().MenuText(Vector2(next_item_pos.x - 12 + (slidersize - 18) + iValueToAddForText, next_item_pos.y), Color(accent_color_[0], accent_color_[1], accent_color_[2], 255.f).GetUnityColor(), Color::Black(), wszValue, false);

		/* Render slider bar */
		UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x, next_item_pos.y + 20), Vector2(next_item_pos.x + slidersize, next_item_pos.y + 24), Color(34, 34, 34, 255.f).GetUnityColor());

		/* Calculate one amount */
		float flOneAmount = slidersize / (iMax - iMin);

		if (is_mouse_in_box({ next_item_pos.x, next_item_pos.y + 20 }, { next_item_pos.x + 250 + 0.1f, next_item_pos.y + 35 }) && mouse_state && (!old_mouse_state || !bComboOpenedInThisFrame) && !interacting)
		{
			flValue = static_cast<float>((old_mouse_pos.x - next_item_pos.x) * (iMax - iMin) / slidersize + 0.1f);
		}

		/* clamp for slider */
		if (flValue < iMin)
			flValue = iMin;

		if (flValue > iMax)
			flValue = iMax;

		/* Calculate current size of value */
		float flCurrentSize = flOneAmount * flValue;

		/* clamp for slider */
		if (flValue < iMin)
			flValue = iMin;

		if (flValue > iMax)
			flValue = iMax;

		/* Render progress */
		UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x, next_item_pos.y + 20), Vector2(next_item_pos.x + flCurrentSize, next_item_pos.y + 24), Color(accent_color_[0], accent_color_[1], accent_color_[2], 255.f).GetUnityColor());
		UnityEngine::GL().Rectangle(Vector2(next_item_pos.x, next_item_pos.y + 20), Vector2(next_item_pos.x + slidersize, next_item_pos.y + 25), Color(0, 0, 0, 255.f).GetUnityColor());
	}

	next_item_pos.y += 20 + 10;
}

void Menu::Dropdown(const std::string& title, const std::vector<std::string> items, int& value, bool& is_open) {
	if (!is_menu_open)
		return;

	float left = 85.f;
	float leveling = 0.f;
	float width = 100;
	const auto wstring = std::string(title.begin(), title.end());
	
	if (is_mouse_in_box({ next_item_pos.x + left, next_item_pos.y + leveling }, { next_item_pos.x + left + width , next_item_pos.y + 15 }) && mouse_state) {
		IsInteractingWidthObject = true;
	}
	
	if (is_mouse_in_box({ next_item_pos.x + left, next_item_pos.y + leveling }, { next_item_pos.x + left + width , next_item_pos.y + 15 }) && mouse_state && !old_mouse_state && !interacting) {
		is_open = true;
		interacting = true;
		IsComboOpen = true;
	}
	
	if (menu_event == RustStructs::EventType::Repaint)
	{
	
		UnityEngine::GL().MenuText(Vector2(next_item_pos.x + 3, next_item_pos.y), Color::White(), Color::Black(), wstring.c_str(), false);
	
		if (is_open && !is_mouse_in_box({ next_item_pos.x + left, next_item_pos.y + leveling }, { next_item_pos.x + left + width , next_item_pos.y + 1 + 13 + items.size() * 15 + 16 }) && mouse_state) {
			is_open = false;
			interacting = false;
			IsComboOpen = false;
		}
	
		const auto str = std::string(items.at(value).begin(), items.at(value).end());
	
		if (is_open)
		{
			UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x + left, next_item_pos.y + leveling + 1), Vector2(next_item_pos.x + left + width, next_item_pos.y + leveling + 1 + 15), Color(34, 34, 34, 255.f).GetUnityColor());
			UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x + left, next_item_pos.y + 1 + 14 + leveling), Vector2(next_item_pos.x + left + width, next_item_pos.y + 1 + 14 + leveling + items.size() * 15.f), Color(27, 27, 27, 255.f).GetUnityColor());

			for (auto i{ 0 }; i < items.size(); i++) {
	
				const auto cur = std::string(items.at(i).begin(), items.at(i).end());
	
				if (value == i)
				{
					UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x + left, next_item_pos.y + 1 + 14 + (i * 15) + leveling), Vector2(next_item_pos.x + left + width, next_item_pos.y + 1 + 14 + (i * 15) + leveling + 15), Color(accent_color_[0], accent_color_[1], accent_color_[2], 255.f).GetUnityColor());
				}
	
				if (is_mouse_in_box({ next_item_pos.x + left, next_item_pos.y + 1 + 13 + (i * 15) + leveling }, { next_item_pos.x + left + width , next_item_pos.y + 1 + 23 + (i * 15) + 10 + 16 }))
				{
					if (mouse_state)
					{
						value = i;
						is_open = false;
						interacting = false;
					}
				}
	
				UnityEngine::GL().Rectangle(Vector2(next_item_pos.x + left, next_item_pos.y + 1 + 14 + (i * 15) + leveling), Vector2(next_item_pos.x + left + width, next_item_pos.y + 1 + 14 + (i * 15) + leveling + 15), Color(0, 0, 0, 255.f).GetUnityColor());

				UnityEngine::GL().MenuText(Vector2(next_item_pos.x + left + 3.f, next_item_pos.y + 15 + (i * 15) - 2 + leveling), Color::White(), Color::Black(), cur.c_str(), false);
				
			}
	
			UnityEngine::GL().Rectangle(Vector2(next_item_pos.x + left, next_item_pos.y + leveling), Vector2(next_item_pos.x + left + width, next_item_pos.y + leveling + 15), Color::Black());
			UnityEngine::GL().MenuText(Vector2(next_item_pos.x + left + 3.f, next_item_pos.y - 1 + leveling), Color::White(), Color::Black(), str.c_str(), false);
	
			next_item_pos.y += items.size() * 15.f;
		}
		else {
			UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x + left, next_item_pos.y + 1 + leveling), Vector2(next_item_pos.x + left + width, next_item_pos.y + leveling + 15), Color(34, 34, 34, 255.f).GetUnityColor());
			UnityEngine::GL().Rectangle(Vector2(next_item_pos.x + left, next_item_pos.y + 1 + leveling), Vector2(next_item_pos.x + left + width, next_item_pos.y + leveling + 15), Color(0, 0, 0, 255.f).GetUnityColor());
	
			UnityEngine::GL().MenuText(Vector2(next_item_pos.x + left + 3.f, next_item_pos.y - 1 + leveling), Color::White(), Color::Black(), str.c_str(), false);
		}
	}

	next_item_pos.y += 20;
}

void Menu::MultiDropdown(const std::string& title, const std::vector<std::string> items, std::vector<bool>& value, bool& is_open) {
	if (!is_menu_open)
		return;

	float left = 85.f;
	float leveling = 0.f;
	float width = 100;
	const auto wstring = std::string(title.begin(), title.end());
	
	if (is_mouse_in_box({ next_item_pos.x + left, next_item_pos.y + leveling }, { next_item_pos.x + left + width , next_item_pos.y + 15 }) && mouse_state && !old_mouse_state && !interacting) {
		is_open = true;
		interacting = true;
	}
	
	if (is_open)
	{
		for (size_t i{ 0 }; i < items.size(); i++)
		{
			if (is_mouse_in_box({ next_item_pos.x + left, next_item_pos.y + 1 + 13 + (i * 15) + leveling }, { next_item_pos.x + left + width , next_item_pos.y + 1 + 13 + (i * 15) + leveling + 15 }) && mouse_state) {
				IsInteractingWidthObject = true;
			}
	
			if (is_mouse_in_box({ next_item_pos.x + left, next_item_pos.y + 1 + 13 + (i * 15) + leveling }, { next_item_pos.x + left + width , next_item_pos.y + 1 + 13 + (i * 15) + leveling + 15 })) {
				if (mouse_state && !old_mouse_state)
				{
					value[i] = !value[i];
				}
			}
		}
	}
	
	if (menu_event == RustStructs::EventType::Repaint)
	{ //
		if (is_mouse_in_box({ next_item_pos.x + left, next_item_pos.y + leveling }, { next_item_pos.x + left + width , next_item_pos.y + 1 + 13 + items.size() * 15 + 16 }) && mouse_state) {
			IsInteractingWidthObject = true;
		}
	
		UnityEngine::GL().MenuText(Vector2(next_item_pos.x + 2.f, next_item_pos.y), Color::White(), Color::Black(), wstring.c_str(), false);
	
		if (is_open && !is_mouse_in_box({ next_item_pos.x + left, next_item_pos.y + leveling }, { next_item_pos.x + left + width , next_item_pos.y + 1 + 13 + items.size() * 15 + 16 }) && mouse_state) {
			is_open = false;
			interacting = false;
		}
	
		std::string str;
	
		for (size_t i{ 0 }; i < items.size(); i++) {
			if (value[i]) {
				auto wstr = std::string(items.at(i).begin(), items.at(i).end());
	
				if (str.length() + wstr.length() <= 15) {
					if (!str.empty()) {
						str.append(XS(", "));
					}
					str.append(wstr);
				}
				else {
					str.append(XS("..."));
					break;
				}
			}
		}
	
		if (is_open)
		{
			UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x + left, next_item_pos.y + leveling + 1), Vector2(next_item_pos.x + left + width, next_item_pos.y + leveling + 1 + 15), Color(34, 34, 34, 255.f).GetUnityColor());
			UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x + left, next_item_pos.y + 1 + 14 + leveling), Vector2(next_item_pos.x + left + width, next_item_pos.y + 1 + 14 + leveling + items.size() * 15.f), Color(27, 27, 27, 255.f).GetUnityColor());

			for (size_t i{ 0 }; i < items.size(); i++) {
	
				const auto cur = std::string(items.at(i).begin(), items.at(i).end());
	
				if (value[i])
				{
				//	UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x, next_item_pos.y + 1 + 14 + (i * 15) + 16), Vector2(next_item_pos.x + 140, next_item_pos.y + 1 + 14 + (i * 15) + 16 + 15), Color(171, 171, 171, 255.f).GetUnityColor());
					UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x + left, next_item_pos.y + 1 + 14 + (i * 15) + leveling), Vector2(next_item_pos.x + left + width, next_item_pos.y + 1 + 14 + (i * 15) + leveling + 15), Color(255, 255, 255, 255.f).GetUnityColor());

				}
	
				Color clrr = value[i] ? Color::Red() : Color::White();

				UnityEngine::GL().Rectangle(Vector2(next_item_pos.x + left, next_item_pos.y + 1 + 14 + (i * 15) + leveling), Vector2(next_item_pos.x + left + width, next_item_pos.y + 1 + 14 + (i * 15) + leveling + 15), Color(0, 0, 0, 255.f).GetUnityColor());

				UnityEngine::GL().MenuText(Vector2(next_item_pos.x + left + 3.f, next_item_pos.y + 15 + (i * 15) - 2 + leveling), Color::White(), Color::Black(), cur.c_str(), false);
			}
	
			UnityEngine::GL().Rectangle(Vector2(next_item_pos.x + left, next_item_pos.y + leveling), Vector2(next_item_pos.x + left + width, next_item_pos.y + leveling + 15), Color::Black());
			UnityEngine::GL().MenuText(Vector2(next_item_pos.x + left + 3.f, next_item_pos.y - 1 + leveling), Color::White(), Color::Black(), str.empty() ? XS("None") : str.c_str(), false);

			next_item_pos.y += items.size() * 15.f;
		}
		else {

			UnityEngine::GL().RectangleFilled(Vector2(next_item_pos.x + left, next_item_pos.y + 1 + leveling), Vector2(next_item_pos.x + left + width, next_item_pos.y + 1 + leveling + 15), Color(34, 34, 34, 255.f).GetUnityColor());
			UnityEngine::GL().Rectangle(Vector2(next_item_pos.x + left, next_item_pos.y + 1 + leveling), Vector2(next_item_pos.x + left + width, next_item_pos.y + 1 + leveling + 15), Color(0, 0, 0, 255.f).GetUnityColor());

			UnityEngine::GL().MenuText(Vector2(next_item_pos.x + left + 3.f, next_item_pos.y - 1 + leveling), Color::White(), Color::Black(), str.empty() ? XS("None") : str.c_str(), false);
		}
	}

	next_item_pos.y += 20;
}


bool Menu::is_mouse_in_box(const Vector2& pos1, const Vector2& pos2) {

	if (old_mouse_pos.x < pos1.x || old_mouse_pos.y < pos1.y)
		return false;

	if (old_mouse_pos.x > pos2.x || old_mouse_pos.y > pos2.y)
		return false;

	return true;
}