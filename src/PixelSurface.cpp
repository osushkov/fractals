/*
 * PixelSurface.cpp
 *
 *  Created on: 11 Nov 2015
 *      Author: sushkov
 */

#include "PixelSurface.hpp"

#include <cassert>

#include <SDL2/SDL.h>
#include <cairo/cairo.h>

class PixelSurface::PixelSurfaceImpl {

  SDL_Renderer* const renderer; // this is passed in, not owner of this resource
  const unsigned width, height;

  SDL_Texture *canvasTexture; // owner, should destroy this in cleanup.

public:

  PixelSurfaceImpl(SDL_Renderer *renderer, unsigned width, unsigned height) :
      renderer(renderer), width(width), height(height) {

    assert(renderer != nullptr);
    assert(width > 0);
    assert(height > 0);

    init();
  }

  ~PixelSurfaceImpl() {
    if (canvasTexture != nullptr) {
      SDL_DestroyTexture(canvasTexture);
    }
  }

  unsigned getWidth(void) const {
    return width;
  }

  unsigned getHeight(void) const {
    return height;
  }

  void renderPixels(const std::vector<Color> &pixels) {
    assert(pixels.size() == width*height);

    unsigned char *pixelsBuffer;
    int pitch;
    SDL_LockTexture(canvasTexture, NULL, (void **)&pixelsBuffer, &pitch);

    cairo_surface_t *cairo_surface = cairo_image_surface_create_for_data(
        pixelsBuffer, CAIRO_FORMAT_ARGB32, width, height, pitch);
    assert(cairo_surface != nullptr);

    cairo_t *cr = cairo_create(cairo_surface);
    assert(cairo_surface != nullptr);

    renderToSurface(cr, pixels);

    cairo_destroy(cr);
    cairo_surface_destroy(cairo_surface);
    SDL_UnlockTexture(canvasTexture);

    pushToRenderer();
  }

private:

  void init(void) {
    canvasTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
        width, height);
    assert(canvasTexture != nullptr);
  }

  void renderToSurface(cairo_t *cr, const std::vector<Color> &pixels) {
    const int stride = cairo_format_stride_for_width (CAIRO_FORMAT_RGB24, width);

    unsigned char *data = new unsigned char[stride * height];
    fillImageData(pixels, data, stride);

    cairo_surface_t *surface =
        cairo_image_surface_create_for_data (data, CAIRO_FORMAT_RGB24, width, height, stride);

    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint (cr);

    cairo_surface_destroy (surface);
    delete[] data;
  }

  void fillImageData(const std::vector<Color> &srcPixels, unsigned char *dstBuffer, int stride) {
    for (unsigned y = 0; y < height; y++) {
      unsigned char* rowStart = dstBuffer + (y * stride);
      for (unsigned x = 0; x < width; x++) {
        int dstOffset = x * 4;
        int srcIndex = x + y*width;

        rowStart[dstOffset + 0] = srcPixels[srcIndex].blue * 255;
        rowStart[dstOffset + 1] = srcPixels[srcIndex].green * 255;
        rowStart[dstOffset + 2] = srcPixels[srcIndex].red * 255;
        rowStart[dstOffset + 3] = srcPixels[srcIndex].alpha * 255;
      }
    }
  }

  void pushToRenderer() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, canvasTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }
};


PixelSurface::PixelSurface(SDL_Renderer *renderer, unsigned width, unsigned height) :
    impl(new PixelSurface::PixelSurfaceImpl(renderer, width, height)) {}

PixelSurface::~PixelSurface() = default;

unsigned PixelSurface::getWidth(void) const {
  return impl->getWidth();
}

unsigned PixelSurface::getHeight(void) const {
  return impl->getHeight();
}

void PixelSurface::renderPixels(const std::vector<Color> &pixels) {
  impl->renderPixels(pixels);
}
