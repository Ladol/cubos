#pragma once

namespace tesseratos
{
    class Themes final
    {
    private:
        void presetThemeDark();
        void presetThemeLight();
        void presetThemeClassic();

    public:
        void changeTheme(int presetTheme);
    };
} // namespace tesseratos
