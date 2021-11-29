
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

class LoadCommand: public Command
{
public:
    LoadCommand(const QString& file_name, View* view);
    ~LoadCommand();
    void execute() override;
    void unexecute() override;
private:
    QString m_file_name;
    View* m_view;
    Document* m_new_doc;
    Document* m_replaced_doc;
};

class NewCommand: public Command
{
public:
    NewCommand(View* view);
    ~NewCommand();
    void execute() override;
    void unexecute() override;
private:
    View* m_view;
    Document* m_new_doc;
    Document* m_replaced_doc;
};

#endif // _COMMAND_H_
