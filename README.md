# simple-collada-viewer

# This is outdated! I'll update it later. All these libraries are updated and become better. 

This repo shows hot to load a document and render it using these libraries:
- [AssetKit](https://github.com/recp/assetkit) 3D loader
- [libgk](https://github.com/recp/libgk) Renderer
- [assetkit-gl](https://github.com/recp/assetkit-gl) Load AssetKit to libgk
- [cglm](https://github.com/recp/cglm) 3D math library similar to GLM but for C

I've NOT provided build files, just wanted to show how to combine these libs and how to load/render a COLLADA file.

After AssetKit and libgk finished this library may full support COLLADA and glTF

You can use custom shaders I've put some commented codes to bottom, but this program uses default program/shaders.

Also this viewer resizes itself with window, you can see resize func.
