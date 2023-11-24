#include <cubos/engine/imgui/plugin.hpp>
#include <cubos/engine/settings/settings.hpp>

#include <tesseratos/themes/plugin.hpp>

using cubos::core::ecs::Write;

using cubos::engine::Cubos;
using cubos::engine::Settings;

using namespace tesseratos;

static void initTheme(Write<Settings> settings, Write<Themes> themes)
{
    themes->changeTheme(settings->getInteger("tesseratos.theme", 0));
}

void tesseratos::themesPlugin(Cubos& cubos)
{
    cubos.addPlugin(cubos::engine::imguiPlugin);
    cubos.addResource<Themes>();

    cubos.startupSystem(initTheme).after("cubos.imgui.init");
}
