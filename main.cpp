#include "table.h"

int main(int argc, char *argv[]) {

    SDL_Window* window = SDL_CreateWindow("Race", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, INITIAL_WIDTH, INITIAL_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    if (window == NULL) {
        printf("Window Creation Error: %s\n", SDL_GetError());
        exit(0);
    }
    Table table(window);
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    table.resize(w, h);
    table.initialize();
    table.render();
    SDL_Event ev;
    int i = 0;
    while (table.is_running()) {
        while (SDL_PollEvent(&ev) != 0) {
            if (ev.type == SDL_QUIT) {
                table.quit_event();
            } else if (ev.type == SDL_WINDOWEVENT) {
                table.window_event(&ev);
            } else if (ev.type == SDL_KEYDOWN) {
                table.key_press_event(&ev);
            } else if (ev.type == SDL_KEYUP) {
                table.key_release_event(&ev);
            } else if (ev.type == SDL_MOUSEBUTTONDOWN) {
                table.mouse_press_event(&ev);
            } else if (ev.type == SDL_MOUSEBUTTONUP) {
                table.mouse_release_event(&ev);
            } else if (ev.type == SDL_MOUSEMOTION) {
                table.mouse_move_event(&ev);
            } else if (ev.type == SDL_MOUSEWHEEL) {
                table.mouse_wheel_event(&ev);
            }
        }
        table.render();
        SDL_Delay(1);
	++i;
    }
    SDL_GetWindowSize(window, &w, &h);
    SDL_DestroyWindow(window);
    return 0;
}
