#include <imgui.h>

#include <tesseratos/themes/themes.hpp>

using namespace tesseratos;

void Themes::presetThemeDark()
{
    ImGui::StyleColorsDark();
}

void Themes::presetThemeLight()
{
    ImGui::StyleColorsLight();
}

void Themes::presetThemeClassic()
{
    ImGui::StyleColorsClassic();
}

void Themes::changeTheme(int presetTheme)
{
    switch (presetTheme)
    {
    case 0:
        presetThemeDark();
        break;
    case 1:
        presetThemeLight();
        break;
    case 2:
        presetThemeClassic();
        break;

    default:
        break;
    }
}
