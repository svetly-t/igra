#include <string.h>
#include <SDL2/SDL.h>

SDL_Window *__window;
int __window_width = 640;
int __window_height = 480;
SDL_Renderer *__renderer;

enum Buttons {
    FIRST_BUTTON = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    LAST_BUTTON
};

// Byte array for keys pressed this frame
char _keys_pressed[LAST_BUTTON];

// Byte array for keys held down
char _keys_down[LAST_BUTTON];

int main(int argc, char **argv) {
    // SDL initialization
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(__window_width, __window_height, 0, &__window, &__renderer);
    SDL_SetWindowTitle(__window, "nothing");

    while (1) {
        // Event loop
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return 0;

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_W) {
                    _keys_pressed[UP] = 1;
                    _keys_down[UP] = 1;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                    _keys_pressed[DOWN] = 1;
                    _keys_down[DOWN] = 1;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_A){
                    _keys_pressed[LEFT] = 1;
                    _keys_down[LEFT] = 1;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_D){
                    _keys_pressed[RIGHT] = 1;
                    _keys_down[RIGHT] = 1;
                }
            }

            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.scancode == SDL_SCANCODE_W) {
                    _keys_pressed[UP] = 0;
                    _keys_down[UP] = 0;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                    _keys_pressed[DOWN] = 0;
                    _keys_down[DOWN] = 0;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_A){
                    _keys_pressed[LEFT] = 0;
                    _keys_down[LEFT] = 0;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_D){
                    _keys_pressed[RIGHT] = 0;
                    _keys_down[RIGHT] = 0;
                }                    
            }
        }

        // drawing stuff //
        SDL_SetRenderDrawColor(__renderer, 0, 0, 0, 255);
        SDL_RenderClear(__renderer);
        
        // key boxes!
        SDL_Rect keys[4];
        int side = 64;
        
        // lay out key boxes like so:
        //   0
        // 2 1 3
        keys[2].w = keys[2].h = side;
        keys[2].x = __window_width / 2 - (side + side / 2);
        keys[2].y = __window_height / 2 - side;
        keys[3] = keys[1] = keys[2];
        keys[1].x = keys[2].x + side + 4;
        keys[3].x = keys[1].x + side + 4;
        keys[0] = keys[1];
        keys[0].y = keys[1].y - side - 4;

        // key colors!
        SDL_Color colors[4];
        colors[0].a = 255;
        colors[3] = colors[2] = colors[1] = colors[0];
        
        // adjust colors
        int i, idx;
        for (i = 0; i < 4; ++i) {
            colors[i].r = colors[i].g = colors[i].b = 100;
            if (_keys_down[UP + i])
                colors[i].r = colors[i].g = colors[i].b = 200;
            SDL_SetRenderDrawColor(__renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
            SDL_RenderDrawRect(__renderer, &keys[i]);
        }

        SDL_RenderPresent(__renderer);

        // clear transient keypress events
        for (i = FIRST_BUTTON; i < LAST_BUTTON; ++i)
            _keys_pressed[i] = 0;
        
        SDL_Delay(16);

    }

    return 0;
}