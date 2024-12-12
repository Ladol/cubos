#include <cubos/core/io/window.hpp>
#include <cubos/core/reflection/external/primitives.hpp>

#include <cubos/engine/render/picker/picker.hpp>
#include <cubos/engine/render/picker/plugin.hpp>
#include <cubos/engine/render/target/plugin.hpp>
#include <cubos/engine/render/target/target.hpp>
#include <cubos/engine/window/plugin.hpp>

using cubos::core::gl::Texture2DDesc;
using cubos::core::gl::TextureFormat;
using cubos::core::gl::Usage;
using cubos::core::io::Window;

CUBOS_DEFINE_TAG(cubos::engine::createRenderPickerTag);
CUBOS_DEFINE_TAG(cubos::engine::drawToRenderPickerTag);

void cubos::engine::renderPickerPlugin(Cubos& cubos)
{
    cubos.depends(windowPlugin);
    cubos.depends(renderTargetPlugin);

    cubos.component<RenderPicker>();

    cubos.tag(createRenderPickerTag).after(resizeRenderTargetTag);
    cubos.tag(drawToRenderPickerTag).after(createRenderPickerTag);

    cubos.system("resize RenderPickers")
        .tagged(createRenderPickerTag)
        .call([](const Window& window, Query<const RenderTarget&, RenderPicker&> query) {
            for (auto [target, renderPicker] : query)
            {
                if (target.size != renderPicker.size)
                {
                    renderPicker.size = target.size;

                    // Prepare common texture description.
                    Texture2DDesc desc{};
                    desc.width = renderPicker.size.x;
                    desc.height = renderPicker.size.y;
                    desc.usage = Usage::Dynamic;
                    desc.format = TextureFormat::RG16UInt;

                    auto& rd = window->renderDevice();

                    renderPicker.texture = rd.createTexture2D(desc);

                    // TODO: dedup this code
                    renderPicker.pixelBuffers.clear();
                    renderPicker.currentPixelBuffer = 0;
                    for (int i = 0; i < renderPicker.numPixelBuffers; i++)
                    {
                        // Since copyTo outputs only RGBA data with 4 bytes per channel, we need to allocate 16 bytes
                        // per pixel.
                        renderPicker.pixelBuffers.push_back(
                            rd.createPixelPackBuffer(renderPicker.size.x * renderPicker.size.y * 4 * 4));
                    }

                    CUBOS_INFO("Resized RenderPicker to {}x{}", renderPicker.size.x, renderPicker.size.y);
                }
                else if (renderPicker.pixelBuffers.size() != static_cast<size_t>(renderPicker.numPixelBuffers))
                {
                    // TODO: dedup this code
                    auto& rd = window->renderDevice();
                    renderPicker.pixelBuffers.clear();
                    renderPicker.currentPixelBuffer = 0;
                    for (int i = 0; i < renderPicker.numPixelBuffers; i++)
                    {
                        // Since copyTo outputs only RGBA data with 4 bytes per channel, we need to allocate 16 bytes
                        // per pixel.
                        renderPicker.pixelBuffers.push_back(
                            rd.createPixelPackBuffer(renderPicker.size.x * renderPicker.size.y * 4 * 4));
                    }
                }

                // Copy the back texture to the pixel buffer.
                renderPicker.currentPixelBuffer++;
                if (renderPicker.currentPixelBuffer == renderPicker.numPixelBuffers)
                {
                    renderPicker.currentPixelBuffer = 0;
                }
                size_t copyIndex = renderPicker.currentPixelBuffer == 0 ? renderPicker.numPixelBuffers - 1
                                                                        : renderPicker.currentPixelBuffer - 1;
                renderPicker.texture->copyTo(0, 0, renderPicker.size.x, renderPicker.size.y,
                                             renderPicker.pixelBuffers[copyIndex]);

                // New frame, hint that the front texture needs to be cleared.
                renderPicker.cleared = false;
            }
        });
}
