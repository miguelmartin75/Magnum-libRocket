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

///
/// Pre-processor Configuration:
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
typedef Magnum::Shader
#endif // CUSTOM_SHADER

#include <Magnum/Shaders/Flat.h>

// Uncomment or add to compiler flags
// for the render interface to create a shader.
//#define LIBROCKET_MAGNUM_CREATE_SHADER

namespace mlr
{
    class RenderInterface : public Rocket::Core::RenderInterface
    {
    public:

        typedef Magnum::Shaders::Flat2D Shader;

        RenderInterface();

#ifndef LIBROCKET_MAGNUM_CREATE_SHADER
        /// \note shader MUST have texturing enabled.
        RenderInterface(Shader& shader) : _shader(&shader)
        {
        }

        void setShader(Shader& shader) { _shader = &shader; }
#endif

        /// Sets the size of the rendering context
        void setSize(unsigned int width, unsigned int height);

        virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);

        virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);

        virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);

        virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);

        virtual void EnableScissorRegion(bool enable);

        virtual void SetScissorRegion(int x, int y, int width, int height);

        virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);

        virtual bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);

        virtual void ReleaseTexture(Rocket::Core::TextureHandle texture);

        Shader& getShader()
        {
#ifdef LIBROCKET_MAGNUM_CREATE_SHADER
            return _shader;
#else
            assert(_shader && "Please provide a shader");
            return *_shader;
#endif // LIBROCKET_MAGNUM_CREATE_SHADER
        }

    private:

        /// The shader the render interface uses
#ifdef LIBROCKET_MAGNUM_CREATE_SHADER
        Shader
#else
        Shader*
#endif // LIBROCKET_MAGNUM_CREATE_SHADER
        _shader;

        /// The size of the view in the rendering context
        Magnum::Vector2 _size;
    };
}
#endif // ROCKET_RENDERINTERFACE_H
