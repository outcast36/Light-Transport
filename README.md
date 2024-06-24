# Ray Tracing 2.0
Only named this way because I already have a public raytracer repo (written in Julia). This project has a few goals:
* Implement raytracing and a family of rendering algorithms using C++
* Implement expansion style rendering techniques such as Monte Carlo Path Tracing (both bidirectional and unidirectional), Metropolis Light Transport, Photon Mapping
* Support multiple shading models like Blinn-Phong, Cook-Torrance, and other microfacet models
* Render images with complex lighting interactions like indirect illumination, dispersion, sub-surface scattering
* Implement an acceleration structure, such as a Bounding Voume Hierarchy or a Binary Space Partitioning Tree to make the ray-scene intersection loop run in sub-linear time
* Support both RGB and spectral rendering

This is a work in progress project, maybe this will be updated in the future
