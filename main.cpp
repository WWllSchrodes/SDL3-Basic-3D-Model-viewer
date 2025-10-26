/*
* Base for this code found at https://gist.github.com/omaraflak/165f6583807c5f7cb16559777b6c7ed1
*/
#include <vector>
#include <cmath>
#include <SDL3/SDL.h>
#include "myMath.h"
#include "indices.h"
#include "rows.h"

int WIDTH = 800;
int HEIGHT = 600;

void count(SDL_Renderer* renderer, std::vector<Point>& R05_3D) {     
    const uint16_t* ind_vertices = R05_3D_WF_vert_ind;
    double x, x1, y, y1, z, z1 = 0;
    float scale = 0.05;
    int nb_lines = 286 * 2; // from vert_ind must match or error!!
    for (int n = 0; n < nb_lines; n += 2) {
        Point L0 = (R05_3D[ind_vertices[n]]);
        Point L1 = (R05_3D[ind_vertices[n + 1]]);

        x = L0.x;
        y = L0.y;
        z = L0.z;   // z could be used to test z-buffer or something

        x1 = L1.x;
        y1 = L1.y;
        z1 = L1.z;  // z could be used to test z-buffer or something

        SDL_RenderLine(renderer, x, y, x1, y1);
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        SDL_Quit();
    }
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_CreateWindowAndRenderer("GAME", WIDTH, HEIGHT, 0, &window, &renderer) == false) {
        printf("error creating SDL window and renderer: %s\n", SDL_GetError());
        SDL_Quit();
    }

    Point screenShift(WIDTH / 2, HEIGHT / 2);
    Point screenShiftOpposite(-WIDTH / 2, -HEIGHT / 2);
    int scale = 3;

    // scale and move to center of screen
    for (Point& p : R05_3D) {
        p.x = (scale * p.x + screenShift.x);
        p.y = (scale * p.y + screenShift.y);
        p.z = (scale * p.z + screenShift.z);
    }

    // setup keys
    const bool* keys = SDL_GetKeyboardState(nullptr);

    bool close = false;
    float rx = 0.0;
    float ry = 0.0;
    float rz = 0.0;

    while (!close) {
        SDL_Event event;

        // application loop
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                close = true;
                break;
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    close = true;
                    break;

                }
            }
        }

        // handle rotation
        if (keys[SDL_SCANCODE_UP])
        {
            rx += 0.0001;
        }
        else {
            rx = 0;
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            rx += -0.0060;
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            ry += 0.0001;
        }
        else {
            ry = 0;
        }
        if (keys[SDL_SCANCODE_LEFT])
        {
            ry += -0.0060;
        }
        if (keys[SDL_SCANCODE_W])
        {
            screenShift.y -= 0.01;
        }
        if (keys[SDL_SCANCODE_S])
        {
            screenShift.y += 0.01;
        }

        Matrix rotationXYZ = getRotationMatrix(rx, ry, rz);

        // rotation then move to center of screen
        for (Point& p : R05_3D) {
            p = translate(screenShiftOpposite, p);
            p = transform(rotationXYZ, p);
            p = translate(screenShift, p);
        }

        /* draw stuff here */

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // draw 3D panels
        count(renderer, R05_3D);

        // swap buffers
        SDL_RenderPresent(renderer);
        SDL_Delay(3);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
