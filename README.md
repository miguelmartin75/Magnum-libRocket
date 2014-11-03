# Magnum-libRocket

Rendering integration with [libRocket](https://github.com/lloydw/libRocket) via [Magnum](https://github.com/mosra/magnum).

# Usage

Usage is quite simple and straight-foward, you simply:

- create an object of `mlr::RenderInterface`
- set the shader for the render interface
- set the size (typically the size of your window)
- register it to libRocket, via `Rocket::Core::SetRenderInteface()`.

# Dependencies

This requires my [image loader library](https://github.com/miguelishawt/LoadImage), alternatively instead of getting my library, you can write your own code to load images for libRocket. See `LoadTexture` within the `RenderInterface`.

# Configuration

Configuration is can be done manually (obviously), or through a some macros:

## Pre-processor Configuration

### MLR_CUSTOM_SHADER

A flag to determine if we should be using a custom shader,
if this flag is not defined, it is assumed we will use a 
Magnum::Shaders::Flat2D shader. You should declare the following
macros (if you enable this macro):

#### MLR_CUSTOM_SHADER_PATh

The path for the definition of the shader. Note, this
can't just be a class forward declaration, unless you
include the approriate file within `RenderInterface.cpp`.

####  MLR_CUSTOM_SHADER_NAME

The name of your custom shader class, e.g. `CustomShader`
without the `'s.

# License

See [LICENSE](LICENSE).
