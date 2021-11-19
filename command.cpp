
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
    printf("Construct AddElementCommand\n");
}

AddElementCommand::~AddElementCommand()
{
    printf("Destroy AddElementCommand\n");
    if (m_element_to_add != NULL)
        delete m_element_to_add;
}

void AddElementCommand::execute()
{
    printf("Execute AddElementCommand\n");
    m_ix = m_doc->elements();
    m_doc->add_element(m_element_to_add);
    m_element_to_add = NULL;
}

void AddElementCommand::unexecute()
{
    printf("Unexecute AddElementCommand\n");
    m_element_to_add = m_doc->remove_element(m_ix);
}

RemoveElementCommand::RemoveElementCommand(int ix, View* view)
    : m_ix(ix)
    , m_removed_element(NULL)
    , m_doc(view->get_doc())
{
    printf("Construct RemoveElementCommand\n");
}

RemoveElementCommand::~RemoveElementCommand()
{
    printf("Destroy RemoveElementCommand\n");
    if (m_removed_element != NULL)
        delete m_removed_element;
}

void RemoveElementCommand::execute()
{
    printf("Execute RemoveElementCommand\n");
    m_removed_element = m_doc->remove_element(m_ix);
}

void RemoveElementCommand::unexecute()
{
    printf("Unexecute RemoveElementCommand\n");
    m_doc->add_element(m_removed_element, m_ix);
    m_removed_element = NULL;
}

LoadCommand::LoadCommand(const QString& file_name, View* view)
    : m_file_name(file_name)
    , m_view(view)
    , m_new_doc(new Document(file_name))
    , m_replaced_doc(NULL)
{
    printf("Construct LoadCommand('%s')\n", m_file_name.toLatin1().data());
}

LoadCommand::~LoadCommand()
{
    printf("Destroy LoadCommand('%s')\n", m_file_name.toLatin1().data());
    if (m_new_doc != NULL)
        delete m_new_doc;
    if (m_replaced_doc != NULL)
        delete m_replaced_doc;
}

void LoadCommand::execute()
{
    printf("Execute LoadCommand('%s')\n", m_file_name.toLatin1().data());
    m_new_doc->make_dirty();
    m_replaced_doc = m_view->replace_doc(m_new_doc);
    m_new_doc = NULL;
}

void LoadCommand::unexecute()
{
    printf("Unexecute LoadCommand('%s')\n", m_file_name.toLatin1().data());
    m_replaced_doc->make_dirty();
    m_new_doc = m_view->replace_doc(m_replaced_doc);
    m_replaced_doc = NULL;
}
