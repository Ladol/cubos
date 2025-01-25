/// @file
/// @brief Class @ref cubos::engine::ShaderBuilder.
/// @ingroup render-shader-plugin

#pragma once

#include <string>

#include <cubos/core/gl/render_device.hpp>

#include <cubos/engine/api.hpp>

namespace cubos::engine
{
    class Shader;

    /// @brief TODO
    /// @ingroup render-shader-plugin
    class CUBOS_ENGINE_API ShaderBuilder final
    {
    public:
        ShaderBuilder(cubos::core::gl::RenderDevice& renderDevice, const cubos::core::gl::Stage stage,
                      const std::string& contents)
            : mRenderDevice(renderDevice)
            , mStage(stage)
            , mContents(contents){};

        ShaderBuilder(const ShaderBuilder& shaderBuilder, const std::string& contents)
            : mRenderDevice(shaderBuilder.mRenderDevice)
            , mStage(shaderBuilder.mStage)
            , mContents(contents){};

        ShaderBuilder with(const std::string& defineName) const;

        ShaderBuilder with(const std::string& defineName, const std::string& defineValue) const;

        std::shared_ptr<Shader> build() const;

    private:
        cubos::core::gl::RenderDevice& mRenderDevice; ///< Render device used to recreate the shader.
        const cubos::core::gl::Stage mStage;          ///< Shader stage type to create.
        const std::string mContents;                  ///< Shader source code.
    };
} // namespace cubos::engine
