#include <cubos/engine/settings/settings.hpp>

#include <tesseratos/plugin.hpp>
#include <tesseratos/themes/plugin.hpp>

using cubos::core::ecs::Write;

using cubos::engine::Cubos;
using cubos::engine::Settings;

using tesseratos::Themes;

static void settingsSystem(Write<Settings> settings)
{
    settings->setString("assets.io.path", SAMPLE_ASSETS_FOLDER);
    settings->setBool("assets.io.readOnly", false);
}

static void testTheme(Write<Themes> themes)
{
    themes->changeTheme(0);
}

int main(int argc, char** argv)
{
    Cubos cubos{argc, argv};
    cubos.addPlugin(tesseratos::plugin);
    cubos.startupSystem(settingsSystem).tagged("cubos.settings");
    cubos.startupSystem(testTheme).after("cubos.imgui.init");
    cubos.run();
}
