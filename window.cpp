// compile with clang -lSDL2 window.cpp
// create another file to ask this file to produce what should
// be shown. use this file as the graphics processor?

#include <stdio.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>


int main(int argc, char* args[]) {

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow(
        "hello_sdl_pxbuf",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        480, 480, SDL_WINDOW_SHOWN
    );
    SDL_Surface * surface = SDL_GetWindowSurface(window);
    assert(surface->format->BytesPerPixel == 4);
    assert(!SDL_MUSTLOCK(surface));

    int should_keep_running = 1;

    int box_x = 50;
    int box_y = 50;

    while (should_keep_running) {

        // fill the whole screen with greenish.
        for (int y = 0; y < surface->h; y++) {
            for (int x = 0; x < surface->w; x++) {
                auto pixel = (unsigned char *)surface->pixels + y * surface->pitch + x * 4;
                pixel[0] = 0x50; // Red
                pixel[1] = 0x80; // Green
                pixel[2] = 0x00; // Blue
                pixel[3] = 0x00; // Alpha
            }
        }

        // Draw a white box at box_x, box_y that is 10px x 10px
        for (int box_px_y = 0; box_px_y < 10; box_px_y++) {
            for (int box_px_x = 0; box_px_x < 10; box_px_x++) {
                auto px_x = box_x + box_px_x;
                auto px_y = box_y + box_px_y;
                
                // color the box to contrast against main surface.
                auto pixel = (unsigned char *)surface->pixels + px_y * surface->pitch + px_x * 4;
                if (px_x >= 0 && px_x < surface->w && px_y >= 0 && px_y < surface->h) {
                    pixel[0] = 0x00; //red
                    pixel[1] = 0x00; //green
                    pixel[2] = 0x00; //blue
                    pixel[3] = 0xff; //alpha
                }
            }
        }

        SDL_UpdateWindowSurface( window );

        // Handle input
        SDL_Event e;
        while( SDL_PollEvent( &e ) != 0 )
        {
            switch (e.type) {
                case SDL_QUIT: {
                    should_keep_running = false;
                } break;
            }
        }

        if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]) box_x++;
        if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT ]) box_x--;
        if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN ]) box_y++;
        if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP   ]) box_y--;

    }

}
