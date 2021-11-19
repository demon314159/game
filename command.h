
#ifndef _COMMAND_H_
#define _COMMAND_H

#include "element.h"
#include "view.h"
#include <QString>

class Command
{
public:
    virtual ~Command();
    virtual void execute() = 0;
    virtual void unexecute() = 0;
};

class AddElementCommand: public Command
{
public:
    AddElementCommand(Element* e, View* view);
    ~AddElementCommand();
    void execute() override;
    void unexecute() override;
private:
    int m_ix;
    Element* m_element_to_add;
    Document* m_doc;
};

class RemoveElementCommand: public Command
{
public:
    RemoveElementCommand(int ix, View* view);
    ~RemoveElementCommand();
    void execute() override;
    void unexecute() override;
private:
    int m_ix;
    Element* m_removed_element;
    Document* m_doc;
};

#endif // _COMMAND_H_
