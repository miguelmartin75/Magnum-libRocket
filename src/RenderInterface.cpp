#include "RenderInterface.h"

#include <memory>
#include <string>

#include <Magnum/Renderer.h>
#include <Magnum/Math/Range.h>
#include <Magnum/Mesh.h>
#include <Magnum/Buffer.h>
#include <Magnum/Texture.h>
#include <Magnum/TextureFormat.h>
#include <Magnum/ImageReference.h>
#include <Magnum/ImageFormat.h>
using namespace Magnum;

#include "util/LoadImage.hpp"

namespace
{
    Matrix3 myOrtho(float left, float right, float bottom, float top)
    {
        return Matrix3::projection({right-left, top-bottom}) * Matrix3::translation({-(left+right) / 2, -(top+bottom) /2});
    }
}

struct Geometry
{
    Magnum::Mesh mesh;
    Magnum::Buffer vbo;
    Magnum::Buffer index;
    Magnum::Texture2D* texture;
};

RenderInterface::RenderInterface()
#ifdef LIBROCKET_MAGNUM_CREATE_SHADER
: _shader(Shaders::Flat2D::Flag::Textured)
#else
: _shader(nullptr)
#endif // LIBROCKET_MAGNUM_CREATE_SHADER
{
}

void RenderInterface::setSize(unsigned int width, unsigned int height)
{
    _size = {width, height};
}

void RenderInterface::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
{
    // leave empty :P
}

Rocket::Core::CompiledGeometryHandle RenderInterface::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture_handle)
{
    std::unique_ptr<Geometry> geometry{new Geometry};
    geometry->texture = (Magnum::Texture2D*)texture_handle;
    
    if(num_indices)
    {
        geometry->index.setData({indices, num_indices}, Buffer::Usage::StaticDraw);
        
        geometry->mesh
        .setIndexCount(num_indices)
        .setIndexBuffer(geometry->index, 0, Magnum::Mesh::IndexType::UnsignedInt);
    }
    
    geometry->vbo.setData({vertices, num_vertices}, Buffer::Usage::StaticDraw);
    
    geometry->mesh
    .setPrimitive(Magnum::Mesh::Primitive::Triangles)
    .setVertexCount(num_vertices)
    .addVertexBuffer(geometry->vbo, 0,  Shader::Position(),
                     sizeof(Rocket::Core::Colourb),
                     Shader::TextureCoordinates());
    
    return (Rocket::Core::CompiledGeometryHandle)geometry.release();
}

void RenderInterface::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& pos)
{
	Geometry* geo = (Geometry*)geometry;
    
    _shader.setTransformationProjectionMatrix(myOrtho(0, _size.x(), _size.y(), 0) * Matrix3::translation({pos.x, pos.y}));
    
    geo->texture->bind(Shader::TextureLayer);
    
    _shader.use();
    
    geo->mesh.draw();
}

void RenderInterface::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
    delete (Geometry*)geometry;
}

void RenderInterface::EnableScissorRegion(bool enable)
{
    Renderer::setFeature(Renderer::Feature::ScissorTest, enable);
}

void RenderInterface::SetScissorRegion(int x, int y, int width, int height)
{
    Renderer::setScissor({{x, y}, {width, height}});
}

bool RenderInterface::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
    util::ImageData imageData = util::loadImage(source.CString());
    
    if(!imageData.pixels)
    {
        return false;
    }
    
    texture_dimensions = {imageData.width, imageData.height};
    
    return GenerateTexture(texture_handle, imageData.pixels.release(), texture_dimensions);
}

bool RenderInterface::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
    Magnum::ImageReference2D image{Magnum::ColorFormat::RGBA, Magnum::ColorType::UnsignedByte, {source_dimensions.x, source_dimensions.y}, (void*)source};
    
    std::unique_ptr<Magnum::Texture2D> texture{new Magnum::Texture2D};
    
    (*texture)
    .setWrapping(Magnum::Sampler::Wrapping::ClampToEdge)
    .setMagnificationFilter(Magnum::Sampler::Filter::Linear)
    .setMinificationFilter(Magnum::Sampler::Filter::Linear)
    .setImage(0, Magnum::TextureFormat::RGBA8, Magnum::ImageReference2D{Magnum::ColorFormat::RGBA, Magnum::ColorType::UnsignedByte, {source_dimensions.x, source_dimensions.y}, source});
    
    
    texture_handle = (Rocket::Core::TextureHandle)texture.release();
    
    return true;
}

void RenderInterface::ReleaseTexture(Rocket::Core::TextureHandle texture)
{
    delete (Magnum::Texture2D*)texture;
}
