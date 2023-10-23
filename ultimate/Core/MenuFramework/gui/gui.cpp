#include "gui.hpp"
#include "../../Il2Cpp/CIl2Cpp.hpp"

// cba, to setup the project includes properly...
#include "framework/components/groupbox/groupbox.cpp"
#include "framework/components/window/window.cpp"
#include "framework/components/slider/slider.cpp"
#include "framework/components/keybind/keybind.cpp"
#include "framework/components/checkbox/checkbox.cpp"
#include "framework/components/colorpicker/colorpicker.cpp"
#include "framework/components/dropdown/dropdown.cpp"
#include "framework/components/textbox/textbox.cpp"

#include "../../Includes/settings.hpp"

namespace game {
    void create_game_object(uint64_t game_object, uint64_t unity_str) {
        const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GameObject")), XS("Internal_CreateGameObject"), 2));
        return reinterpret_cast<void(*)(uint64_t, uint64_t)>(_method)(game_object, unity_str);
    }

    void dont_destroy_object(uint64_t object) {
        const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("Object")), XS("DontDestroyOnLoad"), 1));
        return reinterpret_cast<void(*)(uint64_t)>(_method)(object);
    }

    uint64_t add_component(uint64_t game_object, uint64_t type_object) {
        const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GameObject")), XS("AddComponent"), 1));
        return reinterpret_cast<uint64_t(*)(uint64_t, uint64_t)>(_method)(game_object, type_object);
    }

    // engine drawing functions
    struct rect {
        float x, y, w, h;
    };

    /*
            struct drawing_prototypes_t {
            void( *line )( vec2_t start, vec2_t end, color_t color );
            void( *rect )( vec2_t position, vec2_t size, color_t color, float rounding );
            void( *filled_rect )( vec2_t position, vec2_t size, color_t color, float rounding );
            void( *text )( vec2_t position, const char* text, color_t color, int flags );
#ifdef CALLIOPE_USE_TEXT_SIZE
            vec2_t( *calc_text_size )( const char* text );
#endif
            void( *image )( vec2_t position, vec2_t size, void* source );
            void( *multi_color_filled_rect )( vec2_t position, vec2_t size, std::array<color_t, 4> colors );
            void( *push_clip_rect )( vec2_t mins, vec2_t maxs, bool allow_intersections );
            void( *pop_clip_rect )( );
            float( *get_frame_time )( );
        } drawing;
    */

    struct string
    {
        char zpad[0x10]{ };
        int size{ };
        wchar_t buffer[MAX_PATH];

        string(const wchar_t* st) : size((int)wcslen(st))
        {
            for (int idx = 0; idx < size; idx++)
            {
                buffer[idx] = st[idx];
            }
            buffer[size] = 0;
        }
    };

    struct color {
        float r, g, b, a;
    };

    struct vec2 {
        float x, y;
    };

    struct vec4 {
        float x, y, z, w;
    };

    namespace input {

        vec2 get_mouseScrollDelta()
        {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("Input")), XS("get_mouseScrollDelta"), 0));
            return reinterpret_cast<decltype(&get_mouseScrollDelta)>(_method)();
        }

    }

    namespace drawing {
        void rotate_around_pivot(float angle, vec2 pivot_point) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUIUtility")), XS("RotateAroundPivot"), 2));
            return reinterpret_cast<decltype(&rotate_around_pivot)>(_method)(angle, pivot_point);
        }

        void draw_texture(rect r, uint64_t texture) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUI")), XS("DrawTexture"), 2));
            return reinterpret_cast<decltype(&draw_texture)>(_method)(r, texture);
        }

        void draw_texture_with_color_and_rounding(rect r, uint64_t texture, int scale_mode, bool alpha_blend, float image_aspect, color c, float border_width, float border_radius) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUI")), XS("DrawTexture"), 8));
            return reinterpret_cast<decltype(&draw_texture_with_color_and_rounding)>(_method)(r, texture, scale_mode, alpha_blend, image_aspect, c, border_width, border_radius);
        }

        void draw_texture_multi_colored(rect position, uint64_t image, int scaleMode, bool alphaBlend, float imageAspect, color leftColor, color topColor, color rightColor, color bottomColor, vec4 borderWidths, vec4 borderRadiuses, bool drawSmoothCorners) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUI")), XS("DrawTexture"), 12));
            return reinterpret_cast<decltype(&draw_texture_multi_colored)>(_method)(position, image, scaleMode, alphaBlend, imageAspect, leftColor, topColor, rightColor, bottomColor, borderWidths, borderRadiuses, drawSmoothCorners);
        }

        uint64_t get_white_texture() {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("Texture2D")), XS("get_whiteTexture"), 0));
            return reinterpret_cast<decltype(&get_white_texture)>(_method)();
        }

        uint64_t temp_content(game::string* str) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr_with_args(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUIContent")), XS("Temp"), XS("t"), 1));
            return reinterpret_cast<decltype(&temp_content)>(_method)(str);
        }

        void set_gui_color(color c) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUI")), XS("set_color"), 1));
            return reinterpret_cast<decltype(&set_gui_color)>(_method)(c);
        }

        void set_font_size(uint64_t style, int size) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUIStyle")), XS("set_fontSize"), 1));
            return reinterpret_cast<decltype(&set_font_size)>(_method)(style, size);
        }

        void set_alignment(uint64_t style, int text_anchor) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUIStyle")), XS("set_alignment"), 1));
            return reinterpret_cast<decltype(&set_font_size)>(_method)(style, text_anchor);
        }

        void calc_text_size(uint64_t style, uint64_t content, vec2& out) {
            const static auto _method = CIl2Cpp::il2cpp_resolve_icall(XS("UnityEngine.GUIStyle::Internal_CalcSize_Injected"));
            return reinterpret_cast<decltype(&calc_text_size)>(_method)(style, content, out);
        }

        void label(rect position, uint64_t content, uint64_t style) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr_with_args(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUI")), XS("Label"), XS("content"), 3));
            return reinterpret_cast<decltype(&label)>(_method)(position, content, style);
        }

        uint64_t get_label(uint64_t skin) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUISkin")), XS("get_label"), 0));
            return reinterpret_cast<decltype(&get_label)>(_method)(skin);
        }

        uint64_t get_gui_skin() {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUI")), XS("get_skin"), 0));
            return reinterpret_cast<decltype(&get_gui_skin)>(_method)();
        }

        void gui_clip_push(rect r, vec2 scroll_offset, vec2 render_offset, bool reset_offset) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUIClip")), XS("Internal_Push"), 4));
            return reinterpret_cast<decltype(&gui_clip_push)>(_method)(r, scroll_offset, render_offset, reset_offset);
        }

        void gui_clip_pop() {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUIClip")), XS("Internal_Pop"), 0));
            return reinterpret_cast<decltype(&gui_clip_pop)>(_method)();
        }
    }
}



void filled_rect(calliope::vec2_t position, calliope::vec2_t size, calliope::color_t color, float rounding = 0.f) {
    game::drawing::draw_texture_with_color_and_rounding({ position.x, position.y, size.x, size.y }, white_texture, 0, true, 0.f, *(game::color*)(&color), 0.f, rounding);
}

// you might have to modify this to fix rounding if you care about that...
void rect(calliope::vec2_t position, calliope::vec2_t size, calliope::color_t color, float rounding = 0.f)
{
    filled_rect(position, calliope::vec2_t(1, size.y), color, rounding);
    filled_rect(calliope::vec2_t(position.x + size.x, position.y), calliope::vec2_t(1, size.y), color, rounding);
    filled_rect(position, calliope::vec2_t(size.x, 1), color, rounding);
    filled_rect(calliope::vec2_t(position.x, position.y + size.y), calliope::vec2_t(size.x, 1), color, rounding);
}

// you will need to modify this to fix gradients...
// Import the Unity GL class from here, etc... 
// Or write your gradients another way... 
// you need to use GL.Viewport if you are going to use GL since it is not effected by GUIClip's.
// https://github.com/clxxe/sapphire/blob/main/sapphire/unity_gl.hpp#L85

void multi_color_filled_rect(calliope::vec2_t position, calliope::vec2_t size, std::array<calliope::color_t, 4> colors) {
    game::drawing::draw_texture_multi_colored({ position.x, position.y, size.x, size.y }, white_texture, 0, true, 0.f, { colors[0].r, colors[0].g, colors[0].b, colors[0].a },
        { colors[1].r, colors[1].g, colors[1].b, colors[1].a },
        { colors[2].r, colors[2].g, colors[2].b, colors[2].a },
        { colors[3].r, colors[3].g, colors[3].b, colors[3].a }, { 0.f, 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f, 0.f }, false);
}

// You will also want to include, https://docs.unity3d.com/ScriptReference/GL.Viewport.html

void push_clip_rect(calliope::vec2_t mins, calliope::vec2_t maxs, bool allow_intersections) {
    game::drawing::gui_clip_push({ mins.x, mins.y, maxs.x, maxs.y }, { 0.f, 0.f }, { 0.f, 0.f }, true);
}

void pop_clip_rect() {
    game::drawing::gui_clip_pop();
}

size_t custom_mbstowcs(wchar_t* dest, const char* src, size_t destsz) {
    if (dest == nullptr || src == nullptr) {
        return static_cast<size_t>(-1); // Invalid argument
    }

    size_t i = 0;
    while (i < destsz - 1 && src[i] != '\0') {
        dest[i] = static_cast<wchar_t>(src[i]);
        i++;
    }

    dest[i] = L'\0';

    if (i == destsz - 1 && src[i] != '\0') {
        dest[0] = L'\0';
        return static_cast<size_t>(-1); // Insufficient space in the destination buffer
    }

    return i; // Number of characters converted
}

calliope::vec2_t calc_text_size(const char* text) {
    game::vec2 text_size{ 0, 0 };

    wchar_t buf[MAX_PATH]{ };
    custom_mbstowcs(buf, text, sizeof(buf));

    auto _strbuf = game::string(buf);
    auto content = game::drawing::temp_content(&_strbuf);

    game::drawing::calc_text_size(label_style, content, text_size);

    return { text_size.x, text_size.y };
}

void text(calliope::vec2_t position, const char* text, calliope::color_t color, int flags) {
    if (!label_style)
        return;

    wchar_t buf[MAX_PATH]{ };
    custom_mbstowcs(buf, text, sizeof(buf));

    auto _strbuf = game::string(buf);
    auto content = game::drawing::temp_content(&_strbuf);

    game::vec2 text_size{ 0, 0 };
    game::drawing::calc_text_size(label_style, content, text_size);

    if (flags & calliope::menu_t::text_flags::text_flags_style_outline) {
        game::drawing::set_gui_color({ 0.f, 0.f, 0.f, color.a });
        game::drawing::label({ position.x + 1, position.y + 1, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x - 1, position.y - 1, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x + 1, position.y - 1, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x - 1, position.y + 1, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x + 1, position.y, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x - 1, position.y, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x, position.y - 1, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x, position.y + 1, text_size.x, text_size.y }, content, label_style);
    }

    if (flags & calliope::menu_t::text_flags::text_flags_style_dropshadow) {
        game::drawing::set_gui_color({ 0.f, 0.f, 0.f, color.a });
        game::drawing::label({ position.x + 1, position.y + 1, text_size.x, text_size.y }, content, label_style);
    }

    game::drawing::set_gui_color({ color.r, color.g, color.b, color.a });
    game::drawing::label({ position.x, position.y, text_size.x, text_size.y }, content, label_style);
}

int calliope::globals::menu_alpha = 255;
calliope::color_t calliope::globals::menu_accent(255, 255, 255, 255);

bool tracking_prediction;

void GUI::SetupGUI()
{
    static bool do_once = false;

    if (!do_once)
    {
        calliope::menu.drawing.calc_text_size = calc_text_size;
        calliope::menu.drawing.filled_rect = filled_rect;
        calliope::menu.drawing.rect = rect;
        calliope::menu.drawing.text = text;
        calliope::menu.drawing.multi_color_filled_rect = multi_color_filled_rect;
        //calliope::menu.drawing.image = image;
        calliope::menu.drawing.push_clip_rect = push_clip_rect;
        calliope::menu.drawing.pop_clip_rect = pop_clip_rect;

        do_once = true;
    }


    if (!white_texture)
        white_texture = (uint64_t)UnityEngine::Texture2D::get_whiteTexture();

    if (!skin || !label_style) {
        skin = (uint64_t)UnityEngine::GUI::GetSkin();
        label_style = (uint64_t)reinterpret_cast<UnityEngine::GUISkin*>(skin)->m_label();
    }

    game::drawing::set_font_size(label_style, 11);
    game::drawing::set_alignment(label_style, 4);

   // game::drawing::draw_texture_with_color_and_rounding({ 10, 10, 50, 50 }, white_texture, 0, true, 0.f, { 1.f, 0.f, 0.f, 1.f }, 0.f, 4.f);

    // you may want to change this to use the Unity VK Keys instead, etc... unity mouse buttons its all up to your preferences...
    calliope::util::get_key_states();

    // replace this with... https://docs.unity3d.com/ScriptReference/Input-mouseScrollDelta.html
    calliope::menu.mouse_wheel_delta
        = game::input::get_mouseScrollDelta().y * 0.1f;
}
std::string nigga = "";
int keybd = 0;
int groupbox_sz = 250;
int groupbox_sz_y = 360;

void AimbotTab()
{
    if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("General"), calliope::vec2_t(50, 0), calliope::vec2_t(groupbox_sz, groupbox_sz_y))) {
        calliope::menu.components.checkbox(XS("Silent Aim"), m_settings::SilentAim);
        if (m_settings::SilentAim)
        {
            m_settings::RotationAimbot = false;
        }

        calliope::menu.components.checkbox(XS("Legit Silent"), m_settings::RotationAimbot);
        calliope::menu.components.checkbox(XS("Melee SilentAim"), m_settings::MeleeAimbot);
        calliope::menu.components.checkbox(XS("Silent Melee"), m_settings::SilentMelee);
        calliope::menu.components.checkbox(XS("Manipulation"), m_settings::Manipulation);
        if (m_settings::Manipulation)
        {
            calliope::menu.components.checkbox(XS("AutoShoot"), m_settings::Autoshoot);
            if (m_settings::Autoshoot)
            {
                calliope::menu.components.keybind(XS("AutoShoot Bind"), (int&)m_settings::AutoshootKey, true);
            }
            calliope::menu.components.checkbox(XS("AutoStop"), m_settings::StopPlayer);
            calliope::menu.components.checkbox(XS("PierceMaterials"), m_settings::PierceMaterials);
            calliope::menu.components.checkbox(XS("Bullet Queue"), m_settings::InstantKill);
        }

        calliope::menu.components.checkbox(XS("Bullet TP"), m_settings::BulletTP);

        if (m_settings::BulletTP)
        {
            calliope::menu.components.checkbox(XS("Cache BulletTP Angles (Saves FPS)"), m_settings::CacheBulletTP);
            if (m_settings::CacheBulletTP)
            {
                calliope::menu.components.checkbox(XS("AdvancedCaching (Saves FPS)"), m_settings::AdvancedChecks);
            }
        }

        if (m_settings::BulletTP && m_settings::Manipulation) {
            calliope::menu.components.checkbox(XS("Behind Wall (FPS)"), m_settings::BehindWall);
        }
        else {
            m_settings::BehindWall = false;
        }


        calliope::menu.components.checkbox(XS("Instant Hit"), m_settings::InstantBullet);
        calliope::menu.components.checkbox(XS("WaitForInstantHit"), m_settings::WaitForInstantHit);


        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two = calliope::menu.components.groupbox(XS("Other"), calliope::vec2_t(60 + groupbox_sz, 0), calliope::vec2_t(groupbox_sz, groupbox_sz_y))) {

        calliope::menu.components.checkbox(XS("Target NPC"), m_settings::AimbotNPC);
        calliope::menu.components.checkbox(XS("Target Wounded"), m_settings::TargetWounded);


        calliope::menu.components.slider<float>(XS("Accuracy"), XS(""), m_settings::AimbotAccuracy, 0, 100);
        calliope::menu.components.slider<float>(XS("Fov Slider"), XS(""), m_settings::AimbotFOV, 0, 1000);
        calliope::menu.components.dropdown(XS("Aimbone"), { ("Head"), ("Neck"), ("Chest"), ("Random"), ("Closest To Crosshair") }, m_settings::SelectedAimbone);

        calliope::menu.components.checkbox(XS("AutoReload"), m_settings::AutoReload);
       // if (m_settings::AutoReload)
        /*    calliope::menu.components.checkbox(XS("AutoReload Icon"), m_settings::AutoReloadIcon);

            Menu().CheckBox(XS("AutoReload Icon"), m_settings::AutoReloadIcon);*/


        calliope::menu.components.checkbox(XS("Hitbox Override"), m_settings::HitboxOverride);

        //Menu().CheckBox(XS("Hitbox Override"), m_settings::HitboxOverride);
        //if (m_settings::HitboxOverride)
        //{
        //    Menu().Dropdown(XS("Hitbox"), { XS("Head"), XS("Chest"), XS("Random") }, m_settings::SelectedHitbox, aim_type_opene2);
        //}

        calliope::menu.components.end_groupbox();
    }


    if (auto groupbox_three = calliope::menu.components.groupbox(XS("Visuals"), calliope::vec2_t(320 + groupbox_sz, 0), calliope::vec2_t(groupbox_sz, groupbox_sz_y))) {
      
        calliope::menu.components.checkbox(XS("Crosshair"), m_settings::Crosshair);
        if (m_settings::Crosshair)
        {
           m_settings::Swastika = false;
        }
        calliope::menu.components.checkbox(XS("SwastikaCrosshair"), m_settings::Swastika);

        ////Menu().CheckBox(XS("SwastikaCrosshair"), m_settings::Swastika);
        if (m_settings::Swastika)
        {
        	m_settings::Crosshair = false;
            calliope::menu.components.slider<float>(XS("SwastikaSize"), XS(""), m_settings::SwastikaSize, 1, 20);
        }
        calliope::menu.components.checkbox(XS("FOV Circle"), m_settings::DrawFov);
        calliope::menu.components.checkbox(XS("Target Snapline"), m_settings::Aimline);
        calliope::menu.components.checkbox(XS("Target Marker"), m_settings::AimMarker);
        calliope::menu.components.checkbox(XS("Target Indicator"), m_settings::Target_Indicator);
        calliope::menu.components.checkbox(XS("Bullet Tracers"), m_settings::BulletTracers);
        calliope::menu.components.dropdown(XS("HitMaterial"), { ("Flesh"), ("Glass"), ("Metal"), ("Water") }, m_settings::HitMaterial);

        calliope::menu.components.checkbox(XS("Manipulation Indicator"), m_settings::ManipFlags);
        calliope::menu.components.checkbox(XS("Manip Angle"), m_settings::DrawManipPoints);
        calliope::menu.components.checkbox(XS("BulletTP Indicator"), m_settings::BulletTPFlags);
        calliope::menu.components.checkbox(XS("BulletTP Arrows"), m_settings::Thickbullet_Arrows);
        calliope::menu.components.checkbox(XS("BulletTP Angle"), m_settings::ShowBulletTPAngle);

        calliope::menu.components.checkbox(XS("Cached Indicator"), m_settings::ShowCachedLOS);
        calliope::menu.components.checkbox(XS("Cached Point"), m_settings::ShowCachedPoint);
        calliope::menu.components.checkbox(XS("SnickerBullet"), m_settings::SnickerBullet);

        //Menu().CheckBox(XS("FOV Circle"), m_settings::DrawFov);
        //Menu().CheckBox(XS("Target Snapline"), m_settings::Aimline);
        //Menu().CheckBox(XS("Target Marker"), m_settings::AimMarker);
        //Menu().CheckBox(XS("Target Indicator"), m_settings::Target_Indicator);
        //Menu().CheckBox(XS("Bullet Tracers"), m_settings::BulletTracers);
        //Menu().Dropdown(XS("HitMaterial"), { XS("Flesh"), XS("Glass"), XS("Metal"), XS("Water") }, m_settings::HitMaterial, hitmat_open);


        calliope::menu.components.end_groupbox();
    }
}

void ColorsTab()
{
    if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("Menu Colors"), calliope::vec2_t(50, 0), calliope::vec2_t(groupbox_sz, groupbox_sz_y))) {

        calliope::menu.components.colorpicker(XS("menu accent"), calliope::globals::menu_accent, false);
        calliope::menu.components.keybind(XS("test"), keybd, false);
        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two = calliope::menu.components.groupbox(XS("Other"), calliope::vec2_t(60 + groupbox_sz, 0), calliope::vec2_t(groupbox_sz, groupbox_sz_y))) {
        calliope::menu.components.checkbox(XS("Tracking Prediction"), tracking_prediction);


        calliope::menu.components.end_groupbox();
    }

}

void PlayersVisuals()
{

    if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("General"), calliope::vec2_t(50, 0), calliope::vec2_t(groupbox_sz, groupbox_sz_y))) {
        calliope::menu.components.checkbox(XS("Username"), m_settings::nameEsp);
        calliope::menu.components.checkbox(XS("Skeleton"), m_settings::Skeleton);


        calliope::menu.components.dropdown(XS("BoxType"), { ("None"), ("Box"), ("CornerBox") }, m_settings::SelectedBoxESP);
        calliope::menu.components.dropdown(XS("HeldItem"), { ("None"), ("Text"), ("Icons"), ("Both") }, m_settings::HeldItemType);
        calliope::menu.components.dropdown(XS("HealthBar"), { ("None"), ("Bottom"), ("Left") }, m_settings::SelectedHealthBar);
        calliope::menu.components.dropdown(XS("Inventory"), { ("None"), ("Text"), ("Icons") }, m_settings::SelectedHotbar);
        calliope::menu.components.dropdown(XS("Clothing"), { ("None"), ("Text"), ("Icons") }, m_settings::SelectedClothing);
        calliope::menu.components.dropdown(XS("BaseCheck"), { ("None"), ("Outside"), ("Inside"), ("Both") }, m_settings::SelectedOutsideType);
       

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two = calliope::menu.components.groupbox(XS("Other"), calliope::vec2_t(60 + groupbox_sz, 0), calliope::vec2_t(groupbox_sz, groupbox_sz_y))) {
        calliope::menu.components.dropdown(XS("Vischeck"), { ("None"), ("Enabled"), ("Tags Enabled"), ("Both") }, m_settings::VisCheckType);
       
        calliope::menu.components.multi_dropdown(XS("Load Chams"), { ("Lightning"), ("Geometric"), ("Galaxy"), ("WireFrame") }, m_settings::LoadChams);
        //calliope::menu.components.dropdown(("Load Chams"), { ("Lightning"), ("Geometric"), ("Galaxy"), ("WireFrame") }, m_settings::LoadChams);
        calliope::menu.components.dropdown(XS("Chams"), { ("None"), ("NightFire Blue"), ("NightFire Red"), ("Lightning"), ("Geometric Disolve"), ("Galaxy"), ("WireFrame"), ("Color") }, m_settings::SelectedChams);

        if (m_settings::SelectedChams == 0)
            m_settings::PlayerChams = false;
        else
            m_settings::PlayerChams = true;

        if (m_settings::VisCheckType == 0) {
            m_settings::EspVisCheck = false;
            m_settings::TagsVisCheck = false;
        }
        else if (m_settings::VisCheckType == 1) {
            m_settings::EspVisCheck = true;
            m_settings::TagsVisCheck = false;
        }
        else if (m_settings::VisCheckType == 2) {
            m_settings::EspVisCheck = false;
            m_settings::TagsVisCheck = true;
        }
        else if (m_settings::VisCheckType == 3) {
            m_settings::EspVisCheck = true;
            m_settings::TagsVisCheck = true;
        }


        if (m_settings::LoadChams[0]) {
            static bool HasLoaded = false;
            if (!HasLoaded)
                m_settings::LoadLightning = true;
        }
        if (m_settings::LoadChams[1]) {
            static bool HasLoaded = false;
            if (!HasLoaded)
                m_settings::LoadGeometric = true;
        }
        if (m_settings::LoadChams[2]) {
            static bool HasLoaded = false;
            if (!HasLoaded)
                m_settings::LoadGalaxy = true;
        }
        if (m_settings::LoadChams[3]) {
            static bool HasLoaded = false;
            if (!HasLoaded)
                m_settings::LoadWireFrame = true;
        }
        if (m_settings::LoadChams[4]) {
            static bool HasLoaded = false;
            if (!HasLoaded)
                m_settings::LoadRBP = true;
        }

   
      /*  Menu().CheckBox(XS("Corpse"), m_settings::Corpse);
        Menu().CheckBox(XS("Backpack"), m_settings::BackPack);
        Menu().CheckBox(XS("ShowAlerts"), m_settings::ShowAlerts);
        Menu().CheckBox(XS("Radar"), m_settings::Radar);
        Menu().CheckBoxKeyBind(XS("Save Pos"), m_settings::SavePos, m_settings::SavePosKey);
        Menu().CheckBox(XS("Show Target"), m_settings::DrawTarget);
        Menu().CheckBox(XS("Wounded"), m_settings::DrawWounded);
        Menu().CheckBox(XS("Safezone"), m_settings::DrawSafezone);
        Menu().CheckBox(XS("Npc's"), m_settings::DrawNPC);
        Menu().CheckBox(XS("Sleepers"), m_settings::DrawSleepers);*/
        //Menu().CheckBox(XS("Disconnected"), m_settings::DrawAis);
        //Menu().CheckBox(XS("ShowCheatsUsers"), m_settings::ShowUsers);

      

    /*    Menu().Slider(XS("PlayerDistance"), m_settings::PlayerESPDistance, 0, 500);
        Menu().Slider(XS("NPC Distance"), m_settings::NPCDistance, 0, 500);
        Menu().Slider(XS("Drops Distance"), m_settings::MaxPlayerDropsDistance, 0, 500);
        Menu().Slider(XS("RadarSize"), m_settings::RadarSize, 0, 300);*/

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_three = calliope::menu.components.groupbox(XS("Other 2"), calliope::vec2_t(320 + groupbox_sz, 0), calliope::vec2_t(groupbox_sz, groupbox_sz_y))) {
        
        calliope::menu.components.checkbox(XS("Radar"), m_settings::Radar);
        calliope::menu.components.checkbox(XS("Save Pos"), m_settings::SavePos);

        if (m_settings::SavePos)
        {
            calliope::menu.components.keybind(XS("SavePos Bind"), (int&)m_settings::SavePosKey, true);
        }

        calliope::menu.components.checkbox(XS("Corpse"), m_settings::Corpse);
        calliope::menu.components.checkbox(XS("Backpack"), m_settings::BackPack);
        calliope::menu.components.checkbox(XS("ShowAlerts"), m_settings::ShowAlerts);

        calliope::menu.components.checkbox(XS("Show Target"), m_settings::DrawTarget);
        calliope::menu.components.checkbox(XS("Wounded"), m_settings::DrawWounded);
        calliope::menu.components.checkbox(XS("Safezone"), m_settings::DrawSafezone);

        calliope::menu.components.checkbox(XS("Npc"), m_settings::DrawNPC);
        calliope::menu.components.checkbox(XS("Sleepers"), m_settings::DrawSleepers);

        
        calliope::menu.components.slider<float>(XS("PlayerDistance"), XS(""), m_settings::PlayerESPDistance, 0, 500);
        calliope::menu.components.slider<float>(XS("NPC Distance"), XS(""), m_settings::NPCDistance, 0, 500);
        calliope::menu.components.slider<float>(XS("Drops Distance"), XS(""), m_settings::MaxPlayerDropsDistance, 0, 500);


        calliope::menu.components.end_groupbox();
    }
}

void GUI::DrawMenu()
{


    if (calliope::menu.components.window(XS("serotonin"), calliope::vec2_t(250, 250), calliope::vec2_t(850, 400), calliope::menu_t::window_flags_none)) {
        switch (auto selected_tab = calliope::menu.components.tabs({ XS("Aimbot"), XS("Visuals"), XS("World"), XS("Local"), XS("Weapon"), XS("Settings"), XS("Colors") })) {
        case 0: {
            AimbotTab();
            break;
        }
        case 1: {
            PlayersVisuals();
            break;
        }
        case 6: {
            ColorsTab();
            break;
        }
        }
        calliope::menu.components.end_window();
    }
}
