
// table.h
//
#ifndef _TABLE_H_
#define _TABLE_H_

#include "view.h"
#include "navigate.h"

class Table
{
public:
    Table(SDL_Window* window);
    ~Table();
    bool is_running() const;
    void resize(int w, int h);
    void initialize();
    void render();
    void quit_event();
    void window_event(SDL_Event* e);
    void key_press_event(SDL_Event* e);
    void key_release_event(SDL_Event* e);
    void mouse_press_event(SDL_Event* e);
    void mouse_release_event(SDL_Event* e);
    void mouse_move_event(SDL_Event* e);
    void mouse_wheel_event(SDL_Event *e);
    void mouse_navigate(int mx, int my);
private:
    View m_view;
    Navigate m_navigate;
    bool m_is_running;
};

#endif // _TABLE_H_
