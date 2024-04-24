#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

// screen dimensions
const int SCREEN_WIDTH = 2500;
const int SCREEN_HEIGHT = 2000;

// main window
SDL_Window* window = NULL;

// renderer redirected into texture
SDL_Renderer* renderer = NULL;

// texture with the drawing
SDL_Texture* texture = NULL;

// flag for early quit
bool quit = false;

// zelva state
double x = 0.0;
double y = 0.0;
double angle = 0.0;
unsigned char r = 0;
unsigned char g = 0;
unsigned char b = 0;

const double PI = 3.141592653589793;

void _free_globals()
{
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }
}

void _handle_events()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT)
            quit = true;
    }
}

void _redraw()
{
    // switch to on-screen rendering
    if (SDL_SetRenderTarget(renderer, NULL) != 0) {
        fprintf(stderr, "Setting screen as the render target failed! SDL_Error: %s\n", SDL_GetError());
    }

    // copy texture to the screen
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // restore rendering into texture
    if (SDL_SetRenderTarget(renderer, texture) != 0) {
        fprintf(stderr, "Setting texture as the render target failed! SDL_Error: %s\n", SDL_GetError());
    }
}

void _clear()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);  // white background
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);  // blue foreground
}

void zelva_color(unsigned char red, unsigned char green, unsigned char blue)
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    r = red;
    g = green;
    b = blue;
}

void zelva_reset()
{
    x = 0.0;
    y = 0.0;
    angle = 0.0;
    _clear();
}

bool zelva_init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // create window
    window = SDL_CreateWindow("ZPRO zelva", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        goto error;
    }

    // create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE);
    if (!renderer) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        goto error;
    }

    // create texture
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!texture) {
        fprintf(stderr, "Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        goto error;
    }

    // render into texture
    if (SDL_SetRenderTarget(renderer, texture) != 0) {
        fprintf(stderr, "Setting texture as the render target failed! SDL_Error: %s\n", SDL_GetError());
        goto error;
    }

    _clear();
    zelva_reset();

    return true;

error:
    _free_globals();
    return false;
}

void zelva_quit()
{
    // main loop: keep updating the window until the user quits the program
    while (!quit) {
        _handle_events();
        _redraw();
        SDL_Delay(50);
    }

    _free_globals();
    SDL_Quit();
}

void dopredu(double vzdalenost)
{
    // destination coordinates
    double x2 = x + cos(angle * PI / 180) * vzdalenost;
    double y2 = y + sin(angle * PI / 180) * vzdalenost;

    // draw
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 + x, SCREEN_HEIGHT / 2 - y, SCREEN_WIDTH / 2 + x2, SCREEN_HEIGHT / 2 - y2);

    // update coordinates
    x = x2;
    y = y2;
}

void dozadu(double vzdalenost)
{
    dopredu(-vzdalenost);
}

void doleva(double uhel)
{
    angle += uhel;
}

void doprava(double uhel)
{
    angle -= uhel;
}

void sleep(double t)
{
    // handle piled up events
    _handle_events();

    // update the screen
    _redraw();

    // blocking delay (in ms)
    if (!quit)
        SDL_Delay(1000*t);
}
