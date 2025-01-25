#include <cubos/core/reflection/external/glm.hpp>
#include <cubos/core/reflection/external/primitives.hpp>
#include <cubos/core/reflection/traits/constructible.hpp>
#include <cubos/core/reflection/type.hpp>

#include <cubos/engine/render/shader/shader_builder.hpp>
#include <cubos/engine/render/shader/shader.hpp>

using namespace cubos::engine;

ShaderBuilder ShaderBuilder::with(const std::string& defineName) const
{
    return ShaderBuilder(*this, "#define " + defineName + "\n" + mContents);
}

ShaderBuilder ShaderBuilder::with(const std::string& defineName, const std::string& defineValue) const
{
    return ShaderBuilder(*this, "#define " + defineName + " " + defineValue + "\n" + mContents);
}

std::shared_ptr<Shader> ShaderBuilder::build() const
{
    cubos::core::gl::ShaderStage shaderStage = mRenderDevice.createShaderStage(mStage, mContents.c_str());
    if (shaderStage == nullptr)
    {
        CUBOS_ERROR("Shader asset stage creation failed");
        return nullptr;
    }
    return std::make_shared<Shader>(shaderStage, mRenderDevice, mStage, mContents);
}
