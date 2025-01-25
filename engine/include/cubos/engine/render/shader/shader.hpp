/// @file
/// @brief Class @ref cubos::engine::Shader.
/// @ingroup render-shader-plugin

#pragma once

#include <cubos/core/gl/render_device.hpp>
#include <cubos/core/reflection/reflect.hpp>

#include <cubos/engine/api.hpp>
#include <cubos/engine/render/shader/shader_builder.hpp>

namespace cubos::engine
{
    /// @brief Contains a shader stage created from GLSL code.
    /// @ingroup render-shader-plugin
    class CUBOS_ENGINE_API Shader final
    {
    public:
        CUBOS_REFLECT;

        ~Shader() = default;

        /// @brief Constructs a shader from code.
        /// @param shaderStage Shader stage created from GLSL code.
        Shader(cubos::core::gl::ShaderStage shaderStage, cubos::core::gl::RenderDevice& renderDevice,
               cubos::core::gl::Stage stage, const std::string& contents)
            : mShaderStage(std::move(shaderStage))
            , mBuilder(renderDevice, stage, contents){};

        /// @brief Returns the asset's shader stage.
        /// @return Shader stage.
        cubos::core::gl::ShaderStage shaderStage() const;

        const ShaderBuilder& builder() const;

    private:
        cubos::core::gl::ShaderStage mShaderStage;
        ShaderBuilder mBuilder;
    };
} // namespace cubos::engine
