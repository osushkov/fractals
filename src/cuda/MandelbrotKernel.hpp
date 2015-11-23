
#pragma once

#include "CuVector.hpp"
#include <vector>

namespace MandelbrotKernel {

std::vector<int> calculateIterationsPerPixel(
    int samplesX, int samplesY,
    double pWidth, double pHeight, CuVector2 minPixel,
    int iters);

}
