
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <future>
#include <thread>
#include <SDL2/SDL.h>
#include <cairo/cairo.h>

#include "PixelSurface.hpp"
#include "util/Color.hpp"

#include "fractals/MandelbrotFractal.hpp"
#include "fractals/JuliaSetFractal.hpp"
#include "fractals/SingleThreadedEscapeGenerator.hpp"
#include "fractals/MultiThreadedEscapeGenerator.hpp"
#include "fractals/BinaryColorGenerator.hpp"
#include "fractals/GradientColorGenerator.hpp"
#include "fractals/FractalRenderer.hpp"

const double GOLDEN_RATIO = 1.61803398875;

const Vector2 JULIA_CONST(GOLDEN_RATIO - 2.0, GOLDEN_RATIO - 1.0);
std::shared_ptr<Fractal> fractal(new JuliaSetFractal(JULIA_CONST, 256));

std::shared_ptr<FractalEscapeGenerator> pointGenerator(
    new MultiThreadedEscapeGenerator(fractal));
std::shared_ptr<ColorGenerator> colorGenerator(
    new GradientColorGenerator(Color::RED(1.0), Color::WHITE(1.0), 128));

std::unique_ptr<FractalRenderer> renderer(
    new FractalRenderer(pointGenerator, colorGenerator));


static const unsigned SCREEN_PIXELS_WIDTH = 800;
static const unsigned SCREEN_PIXELS_HEIGHT = 800;
static const double ZOOM_FACTOR = 2.0;

static const Vector2 baseMinExtents(-2.0, -2.0);
static const Vector2 baseMaxExtents(2.0, 2.0);

double curZoomLevel = 1.0;
Vector2 curFocusPoint(0.0, 0.0);

std::vector<Color> cachedPixels;
bool shouldRefresh = true;


Vector2 getCurMinExtents() {
  Vector2 extentsSize = (baseMaxExtents - baseMinExtents) / curZoomLevel;
  return curFocusPoint - (extentsSize / 2.0);
}

Vector2 getCurMaxExtents() {
  Vector2 extentsSize = (baseMaxExtents - baseMinExtents) / curZoomLevel;
  return curFocusPoint + (extentsSize / 2.0);
}

std::vector<Color> generatePixels(unsigned width, unsigned height) {
  if (!shouldRefresh) {
    return cachedPixels;
  }

  unsigned newMaxIterations = 128 + log(curZoomLevel)*10;
  fractal->setMaxIterations(newMaxIterations);

  Vector2 minExtents = getCurMinExtents();
  Vector2 maxExtents = getCurMaxExtents();

  cachedPixels = renderer->renderPixels(minExtents, maxExtents, width, height);
  shouldRefresh = false;

  return cachedPixels;
}

Vector2 screenPosToWorldPos(const Vector2 &screenPos) {
  Vector2 minExtents = getCurMinExtents();
  Vector2 maxExtents = getCurMaxExtents();
  Vector2 extents = maxExtents - minExtents;

  double xFrac = screenPos.x / (double) SCREEN_PIXELS_WIDTH;
  double yFrac = screenPos.y / (double) SCREEN_PIXELS_HEIGHT;

  return minExtents + Vector2(extents.x * xFrac, extents.y * yFrac);
}

void handleMouseButtonEvent(const SDL_Event &event) {
  Vector2 clickPos(event.button.x, event.button.y);
  curFocusPoint = screenPosToWorldPos(clickPos);

  if (event.button.button == SDL_BUTTON_LEFT) {
    curZoomLevel *= ZOOM_FACTOR;
  } else if (event.button.button == SDL_BUTTON_RIGHT) {
    curZoomLevel /= ZOOM_FACTOR;
  }

  shouldRefresh = true;
}

void eventLoop(PixelSurface &pixelSurface) {
  bool quitting = false;

  while(!quitting) {
    SDL_Event event;
    while( SDL_PollEvent(&event) ) {
      switch (event.type) {
      case SDL_QUIT:
        quitting = true;
        break;
      case SDL_MOUSEBUTTONDOWN:
        handleMouseButtonEvent(event);
        break;
      }
    }

    std::vector<Color> pixels = generatePixels(pixelSurface.getWidth(), pixelSurface.getHeight());
    pixelSurface.renderPixels(pixels);

    SDL_Delay(2);
  }
}

int main() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("fractals", 100, 100,
	    SCREEN_PIXELS_WIDTH, SCREEN_PIXELS_HEIGHT, SDL_WINDOW_SHOWN);

	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
	  SDL_DestroyWindow(win);
	  std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
	  SDL_Quit();
	  return 1;
	}

	PixelSurface pixelSurface(ren, SCREEN_PIXELS_WIDTH, SCREEN_PIXELS_HEIGHT);
	eventLoop(pixelSurface);

	SDL_DestroyRenderer(ren);
	return 0;
}
