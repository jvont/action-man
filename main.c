#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "morse_tree.h"

#define FONT_PATH "./munro-small.ttf"
#define WIDTH 320
#define HEIGHT 180

int main() {
  // morse_branch tree[MAX_CODE_BRANCHES];
  // morse_tree_init(tree);
  // morse_tree_test(tree);

  int app_quit = 0;

  // measure typing speed from last N gaps
  // get inputs
  // print dits/dahs
  // print translation below
  // feature: update translation based on context (error correction)

  // if (clock_gettime(CLOCK_MONOTONIC, &t0) < 0) {
  //   perror("clock_gettime()");
  // }

  // Initialize SDL libraries
  if (SDL_Init(SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "%s", SDL_GetError());
    return 1;
  }

  // Create a window
  SDL_Window *window = SDL_CreateWindow("Window", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
  if (!window) {
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "%s", SDL_GetError());
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL, 0);
  if (!renderer) {
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "%s", SDL_GetError());
    return 1;
  }

  // Initialize SDL_TTF
  if (TTF_Init()) {
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "%s", TTF_GetError());
  }

  // Load a font
  TTF_Font *font = TTF_OpenFont(FONT_PATH, 30);
  if (!font) {
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "%s", SDL_GetError());
    return 1;
  }

  SDL_ShowWindow(window);
  SDL_Log("Application started successfully!");

  // Main loop
  while (!app_quit) {
    SDL_Event event;

    // Events
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_QUIT:
          app_quit = 1;
          break;
        case SDL_EVENT_KEY_DOWN:
          printf("Press!\n");
          break;
        case SDL_EVENT_KEY_UP:
          printf("Release\n");
          break;
        default:
          break;
      }
    }

    // Draw
    SDL_Color text_col = {255, 255, 255};
    SDL_Surface *text_surf = TTF_RenderText_Blended(font, "beans", text_col);
    SDL_Texture *text_tex = SDL_CreateTextureFromSurface(renderer, text_surf);

    // Clear background
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
    SDL_RenderClear(renderer);

    SDL_FRect dest;
    dest.x = 0.0f;
    dest.y = 0.0f;
    dest.w = (float)text_surf->w;
    dest.h = (float)text_surf->h;
    SDL_RenderTexture(renderer, text_tex, NULL, &dest);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(text_tex);
    SDL_DestroySurface(text_surf);
  }

  // Destroy
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  SDL_Log("Application quit successfully!");

  return 0;
}