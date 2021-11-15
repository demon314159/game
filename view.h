
#ifndef _VIEW_H_
#define _VIEW_H_

#include <QOpenGLFunctions>
#include "document.h"

class View : protected QOpenGLFunctions
{
public:
    View(Document& doc);
    virtual ~View();
    void initialize();
    void resize(int w, int h);
    void paint();
    void rotate_ax(float degrees);
    void rotate_ay(float degrees);
    void rotate_home();
    void zoom(float factor);
    void zoom_home();

private:
    Document& m_doc;
};

#endif // _VIEW_H_
