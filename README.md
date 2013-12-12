# Magnum-libRocket

Rendering integration with [libRocket](https://github.com/lloydw/libRocket) via [Magnum](https://github.com/mosra/magnum).

# Usage

Usage is quite simple and straight-foward, you simply create an object of `RenderInterface` and set the size of it and register it to libRocket, via `Rocket::Core::SetRenderInteface()`.

# NOTES

The RenderInteface uses a Flat2D shader, provided by Magnum. If memory is your concern it may be of you to actually create your own Flat2D shader, and use it with the RenderInterface. You may do this by uncommenting `#define LIBROCKET_MAGNUM_CREATE_SHADER`. Once this is done, you may provide the shader by: (1) the constructor or (2) the `setShader(Shader&)` method. Your shader MUST have texturing enabled, otherwise it will not work.

# License
Copyright (C) 2013 Miguel Martin (miguel.martin7.5@hotmail.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
