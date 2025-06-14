# Light Transport Thingamabob
This project has a few goals:
* Implement raytracing and a family of rendering algorithms using C++
* Implement expansion style rendering techniques such as Monte Carlo Path Tracing (both bidirectional and unidirectional), Metropolis Light Transport, Photon Mapping
* Support multiple shading models like Blinn-Phong, Cook-Torrance, and other microfacet models
* Render images with complex lighting interactions like indirect illumination, dispersion, sub-surface scattering
* Implement an acceleration structure, such as a Bounding Voume Hierarchy or a Binary Space Partitioning Tree to make the ray-scene intersection loop run in sub-linear time
* Support both RGB and spectral rendering
* Implement noice reduction methods like next event estimation
* High Dynamic Range images?

This is a work in progress project, maybe this will be updated in the future

Compile reference materials to nice looking PDFs using pandoc:
```pandoc [reference.md] -o [reference.pdf]```

To run:
1. ```git clone https://github.com/outcast36/Light-Transport```
2. cd to ```<path-to-cloned-repo>/Light-Transport/```
3. ```cmake -S . -B build```
4. ```cmake --build build```
5. From ```Light-Transport``` directory run ```./build/src/render <out-img-path>```

To run tests:
1. Generate build files using ```cmake -S . -B build -DBUILD_TESTING=ON```
2. ```cmake --build build```
3. ```ctest --test-dir=build```
   
# Implemented
* Support for HDR rendering using PFM image format
* Geometric primitives: Spheres, Cones, Cylinders, Planes, Triangles

# Future Work
* Rework geometry library into templates since primitive do not need dynamic polymorphism from virtual functions
* Organize geometry library codebase
* Expand list of primitives 
