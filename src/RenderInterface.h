#ifndef __ROCKET_RENDERINTERFACE_H__
#define __ROCKET_RENDERINTERFACE_H__

#include <cassert>

#include <Rocket/Core/RenderInterface.h>

#include <Magnum/Shaders/Flat.h>

#define LIBROCKET_MAGNUM_CREATE_SHADER

class RenderInterface
: public Rocket::Core::RenderInterface
{
public:
    
    typedef Magnum::Shaders::Flat2D Shader;
    
    RenderInterface();
    
#ifndef LIBROCKET_MAGNUM_CREATE_SHADER
    /// \note shader MUST have texturing enabled.
    RenderInterface(Shader& shader)
    : _shader(&shader)
    {
    }
    
    void setShader(Shader& shader)
    {
        _shader = &shader;
    }
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

#endif // __ROCKET_RENDERINTERFACE_H__