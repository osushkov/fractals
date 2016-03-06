# fractals

Some code to render different fractals (Julia set and Mandelbrot are implemented, but easy to add others).
There are 2 ways to compute a fractal, using the CPU (multi-threaded) and using the GPU through CUDA. This
is really the main point of this exercise, I wanted to play around with CUDA. Turns out its pretty easy
and straightforward.

Dependencies:
C++11/14
CUDA and a compatible GPU
SDL and Cairo libraries for rendering
tup used for building

