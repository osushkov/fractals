/*
 * MultiThreadedEscapeGenerator.cpp
 *
 *  Created on: 18 Nov 2015
 *      Author: osushkov
 */

#include "MultiThreadedEscapeGenerator.hpp"
#include "SingleThreadedEscapeGenerator.hpp"
#include <cassert>
#include <future>
#include <thread>


class MultiThreadedEscapeGenerator::MultiThreadedEscapeGeneratorImpl {

  std::shared_ptr<Fractal> fractal;
  unsigned maxIterations = 256;

public:
  MultiThreadedEscapeGeneratorImpl(std::shared_ptr<Fractal> fractal) :
    fractal(fractal) {}

  virtual ~MultiThreadedEscapeGeneratorImpl() = default;

  std::vector<FractalPoint> sampleRegion(
      const Vector2 &regionMin, const Vector2 &regionMax,
      unsigned samplesX, unsigned samplesY) const {

    assert(regionMin.x <= regionMax.x);
    assert(regionMin.y <= regionMax.y);

    std::vector<std::future<std::vector<FractalPoint>>> taskFutures =
        getTaskFuture(regionMin, regionMax, samplesX, samplesY, 8);

    std::vector<FractalPoint> result;
    for (auto& future : taskFutures) {
      future.wait();

      std::vector<FractalPoint> taskPoints = future.get();
      for (auto& p : taskPoints) {
        result.push_back(p);
      }
    }

    return result;
  }

  void setMaxIterations(unsigned maxIterations) {
    assert(maxIterations > 0);
    this->maxIterations = maxIterations;
  }

private:

   std::vector<std::future<std::vector<FractalPoint>>> getTaskFuture(
       const Vector2 &regionMin, const Vector2 &regionMax,
       unsigned samplesX, unsigned samplesY,
       unsigned numWorkers) const {

     double taskExtentHeight = (regionMax - regionMin).y / numWorkers;
     unsigned taskHeight = samplesY / numWorkers;

     std::vector<std::future<std::vector<FractalPoint>>> result;
     for (unsigned i = 0; i < numWorkers; i++) {
       Vector2 taskMinExtents(regionMin.x, regionMin.y + taskExtentHeight*i);
       Vector2 taskMaxExtents(regionMax.x, regionMin.y + taskExtentHeight*(i+1));

       std::packaged_task<std::vector<FractalPoint>()> task =
           regionSubtask(taskMinExtents, taskMaxExtents, samplesX, taskHeight);

       result.push_back(task.get_future());
       std::thread(std::move(task)).detach();
     }
     return result;
   }

   std::packaged_task<std::vector<FractalPoint>()> regionSubtask(
       const Vector2 &regionMin, const Vector2 &regionMax,
       unsigned samplesX, unsigned samplesY) const {
     return std::packaged_task<std::vector<FractalPoint>()>(
         [this, regionMin, regionMax, samplesX, samplesY]() {
       SingleThreadedEscapeGenerator gen(this->fractal);
       gen.setMaxIterations(this->maxIterations);
       return gen.sampleRegion(regionMin, regionMax, samplesX, samplesY);
     });
   }
};


MultiThreadedEscapeGenerator::MultiThreadedEscapeGenerator(std::shared_ptr<Fractal> fractal) :
    impl(new MultiThreadedEscapeGeneratorImpl(fractal)) {}

MultiThreadedEscapeGenerator::~MultiThreadedEscapeGenerator() = default;

std::vector<FractalPoint> MultiThreadedEscapeGenerator::sampleRegion(
    const Vector2 &regionMin, const Vector2 &regionMax,
    unsigned samplesX, unsigned samplesY) const {

  return impl->sampleRegion(regionMin, regionMax, samplesX, samplesY);
}

void MultiThreadedEscapeGenerator::setMaxIterations(unsigned maxIterations) {
  impl->setMaxIterations(maxIterations);
}
