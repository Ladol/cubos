#include <cubos/engine/imgui/plugin.hpp>

#include <tesseratos/themes/plugin.hpp>

using cubos::engine::Cubos;

using namespace tesseratos;

void tesseratos::themesPlugin(Cubos& cubos)
{
    cubos.addPlugin(cubos::engine::imguiPlugin);
    cubos.addResource<Themes>();
}
