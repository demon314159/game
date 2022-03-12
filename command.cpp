
#include "command.h"
#include <stdio.h>

Command::~Command()
{
}

AddElementCommand::AddElementCommand(Element* e, View* view)
    : m_ix(0)
    , m_element_to_add(e)
    , m_doc(view->get_doc())
{
}

AddElementCommand::~AddElementCommand()
{
    if (m_element_to_add != NULL)
        delete m_element_to_add;
}

void AddElementCommand::execute()
{
    if (m_element_to_add == NULL) {
        m_doc->unremove_element(m_ix);
    } else {
        m_ix = m_doc->elements();
        m_doc->add_element(m_element_to_add);
        m_element_to_add = NULL;
    }
}

void AddElementCommand::unexecute()
{
    if (m_ix == (m_doc->elements() - 1)) {
        m_element_to_add = m_doc->remove_last_element();
    } else {
        m_doc->remove_element(m_ix);
    }
}

RemoveElementCommand::RemoveElementCommand(int ix, View* view)
    : m_ix(ix)
    , m_doc(view->get_doc())
{
}

RemoveElementCommand::~RemoveElementCommand()
{
}

void RemoveElementCommand::execute()
{
    m_doc->remove_element(m_ix);
}

void RemoveElementCommand::unexecute()
{
    m_doc->unremove_element(m_ix);
}

LoadCommand::LoadCommand(const QString& file_name, View* view)
    : m_file_name(file_name)
    , m_view(view)
    , m_new_doc(new Document(file_name))
    , m_replaced_doc(NULL)
{
}

LoadCommand::~LoadCommand()
{
    if (m_new_doc != NULL)
        delete m_new_doc;
    if (m_replaced_doc != NULL)
        delete m_replaced_doc;
}

void LoadCommand::execute()
{
    m_new_doc->note_many_changes();
    m_replaced_doc = m_view->replace_doc(m_new_doc);
    m_new_doc = NULL;
}

void LoadCommand::unexecute()
{
    m_replaced_doc->note_many_changes();
    m_new_doc = m_view->replace_doc(m_replaced_doc);
    m_replaced_doc = NULL;
}

NewCommand::NewCommand(View* view)
    : m_view(view)
    , m_new_doc(new Document())
    , m_replaced_doc(NULL)
{
}

NewCommand::~NewCommand()
{
    if (m_new_doc != NULL)
        delete m_new_doc;
    if (m_replaced_doc != NULL)
        delete m_replaced_doc;
}

void NewCommand::execute()
{
    m_new_doc->note_many_changes();
    m_replaced_doc = m_view->replace_doc(m_new_doc);
    m_new_doc = NULL;
}

void NewCommand::unexecute()
{
    m_replaced_doc->note_many_changes();
    m_new_doc = m_view->replace_doc(m_replaced_doc);
    m_replaced_doc = NULL;
}


