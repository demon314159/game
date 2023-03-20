//
// table.cpp
//
#include "table.h"

Table::Table(SDL_Window* window)
    : m_view(window)
    , m_navigate()
    , m_is_running(true)
{
}

Table::~Table()
{
}

bool Table::is_running() const
{
    return m_is_running;
}

void Table::resize(int w, int h)
{
    m_view.resize(w, h);
}

void Table::initialize()
{
    m_view.initialize();
}

void Table::render()
{
    m_view.render();
}

void Table::quit_event()
{
    m_is_running = false;
}

void Table::window_event(SDL_Event* e)
{
    if (e->window.event == SDL_WINDOWEVENT_RESIZED) {
        m_view.resize(e->window.data1, e->window.data2);
    }
}

void Table::key_press_event(SDL_Event* e)
{
    unsigned int a = e->key.keysym.scancode;
    bool shifted = (e->key.keysym.mod & KMOD_SHIFT) ? true : false;
    if (a == SDL_SCANCODE_UP) {
        if (shifted) {
            m_view.translate_y(-m_view.height() / 10);
        } else {
            m_view.rotate_ax(-10.0);
        }
    } else if (a == SDL_SCANCODE_DOWN) {
        if (shifted) {
            m_view.translate_y(m_view.height() / 10);
        } else {
            m_view.rotate_ax(10.0);
        }
    } else if (a == SDL_SCANCODE_LEFT) {
        if (shifted) {
            m_view.translate_x(-m_view.width() / 10);
        } else {
            m_view.rotate_ay(-10.0);
        }
    } else if (a == SDL_SCANCODE_RIGHT) {
        if (shifted) {
            m_view.translate_x(m_view.width() / 10);
        } else {
            m_view.rotate_ay(10.0);
        }
    } else if (a == SDL_SCANCODE_I) {
        m_view.zoom(3.0 / 2.0);
    } else if (a == SDL_SCANCODE_O) {
        m_view.zoom(2.0 / 3.0);
    } else if (a == SDL_SCANCODE_H) {
        m_view.zoom_home();
        if (shifted) {
            m_view.rotate_home();
            m_view.translate_home();
        }
        m_navigate.stop();
    } else if (a == SDL_SCANCODE_Q) {
        m_is_running = false;
    }
}

void Table::key_release_event(SDL_Event* e)
{
}

void Table::mouse_press_event(SDL_Event* e)
{
    if (e->button.button == SDL_BUTTON_MIDDLE) {
        m_view.zoom_home();
        m_view.rotate_home();
        m_view.translate_home();
        m_navigate.stop();
    } else if (e->button.button == SDL_BUTTON_LEFT) {
        m_navigate.start_rotate(e->button.x, e->button.y);
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
        m_navigate.start_translate(e->button.x, e->button.y);
    }
}

void Table::mouse_navigate(int mx, int my)
{
    if (m_navigate.is_rotate()) {
        float degx, degy;
        if (m_navigate.rotate_threshold_exceeded(mx, my, degx, degy)) {
            m_view.rotate_ay(degx);
            m_view.rotate_ax(degy);
        }
    } else if (m_navigate.is_translate()) {
        int dx, dy;
        if (m_navigate.translate_threshold_exceeded(mx, my, dx, dy)) {
            m_view.translate_x(dx);
            m_view.translate_y(dy);
        }
    }
}

void Table::mouse_release_event(SDL_Event* e)
{
    if (e->button.button == SDL_BUTTON_LEFT) {
        if (m_navigate.active())
            mouse_navigate(e->button.x, e->button.y);
        m_navigate.stop();
    } else if (e->button.button == SDL_BUTTON_RIGHT) {
        if (m_navigate.active())
            mouse_navigate(e->button.x, e->button.y);
         m_navigate.stop();
    }
}

void Table::mouse_move_event(SDL_Event* e)
{
    if (m_navigate.active())
        mouse_navigate(e->motion.x, e->motion.y);
}

void Table::mouse_wheel_event(SDL_Event *e)
{
    int angle = e->wheel.y;
    if (angle > 0) {
        m_view.zoom(3.0 / 2.0);
    }
    if (angle < 0) {
        m_view.zoom(2.0 / 3.0);
    }
}

