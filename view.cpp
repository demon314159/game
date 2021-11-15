
#include "view.h"

#include <stdio.h>

#define VERBOSE

View::View(Document& doc)
    : m_doc(doc)
{
#ifdef VERBOSE
    printf("View::View(doc)\n");
#endif
}

View::~View()
{
#ifdef VERBOSE
    printf("View::~View()\n");
#endif
}

void View::initialize()
{
#ifdef VERBOSE
    printf("View::initialize()\n");
#endif
}

void View::resize(int w, int h)
{
#ifdef VERBOSE
    printf("View::resize(%d, %d)\n", w, h);
#endif
}

void View::paint()
{
#ifdef VERBOSE
    printf("View::paint()\n");
#endif
}

void View::rotate_ax(float degrees)
{
#ifdef VERBOSE
    printf("View::rotate_ax(%f)\n", degrees);
#endif
}

void View::rotate_ay(float degrees)
{
#ifdef VERBOSE
    printf("View::rotate_ay(%f)\n", degrees);
#endif
}

void View::rotate_home()
{
#ifdef VERBOSE
    printf("View::rotate_home()\n");
#endif
}

void View::zoom(float factor)
{
#ifdef VERBOSE
    printf("View::zoom(%f)\n", factor);
#endif
}

void View::zoom_home()
{
#ifdef VERBOSE
    printf("View::zoom_home()\n");
#endif
}

