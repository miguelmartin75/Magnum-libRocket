///
/// Magnum-libRocket
/// libRocket's RenderInterface implemented with Magnum
///
/// Copyright (C) 2014 Miguel Martin (miguel@miguel-martin.com)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
/// 
/// ------------------------------------------------------------------------------
///
/// PRE-PROCESSOR CONFIGURATION:
/// ===========================
///
/// MLR_CUSTOM_SHADER
///
///   A flag to determine if we should be using a custom shader,
///   if this flag is not defined, it is assumed we will use a 
///   Magnum::Shaders::Flat2D shader. You should declare the following
///   macros (if you enable this macro):
/// 
///     - MLR_CUSTOM_SHADER_PATh
///     
///         The path for the definition of the shader. Note, this
///         can't just be a class forward declaration, unless you
///         include the approriate file within `RenderInterface.cpp`.
///
///     - MLR_CUSTOM_SHADER_NAME
///
///         The name of your custom shader class, e.g. `CustomShader`
///         without the `'s.
///

#ifndef ROCKET_RENDERINTERFACE_H
#define ROCKET_RENDERINTERFACE_H

#include <cassert>

#include <Rocket/Core/RenderInterface.h>

#ifdef MLR_CUSTOM_SHADER
    #include MLR_CUSTOM_SHADER_PATH
#else
    #include <Magnum/Shaders/Flat.h>
#endif // CUSTOM_SHADER


namespace mlr
{
    typedef
#ifdef MLR_CUSTOM_SHADER
    MLR_CUSTOM_SHADER_NAME 
#else
    Magnum::Shaders::Flat2D 
#endif // MLR_CUSTOM_SHADER
    Shader;

    typedef Magnum::Vector2ui Dimension;

    class RenderInterface : public Rocket::Core::RenderInterface
    {
    public:

        RenderInterface()
        RenderInterface(Shader& shader, const Dimension& dimension);

        /// Set the shader the RenderInterface is using.
        /// \param shader The shader you wish to use, null if nothing
        void setShader(Shader* shader) { _shader = shader; }
        Shader* getShader() const { return _shader; }

        /// Retrieves the size of where libRocket will draw to
        const Dimension& getSize() { return _size; }
        /// Sets the size of where libRocket will draw to
        /// \param size The size you wish to set it to
        void setSize(const Dimension& size) { _size = size; }

        // OVERRIDDEN FUNCTIONS

        virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation) override;
        virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture) override;
        virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation) override;
        virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry) override;
        virtual void EnableScissorRegion(bool enable) override;
        virtual void SetScissorRegion(int x, int y, int width, int height) override;
        virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source) override;
        virtual bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions) override;
        virtual void ReleaseTexture(Rocket::Core::TextureHandle texture) override;

    private:

        /// The shader the render interface uses
        Shader* _shader;

        /// The size of the view in the rendering context
        Dimension _size;
    };
}
#endif // ROCKET_RENDERINTERFACE_H
