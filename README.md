# Ray Tracer

A simple ray tracer, based on the popular ['Ray Tracing in One Weekend' guide](https://raytracing.github.io/books/RayTracingInOneWeekend.html).

While the guide was written to run on a single thread, this is a multi-threaded implementation of the ray tracer.

The resolution, samples per pixel, and max. bounces per ray (maxDepth) can be modified in the main function.

The number of threads to be used can also be increased/decreased. Currently, it is set to use half the threads available.
