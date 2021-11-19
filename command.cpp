
#include "command.h"
#include <stdio.h>

#define notVERBOSE

Command::~Command()
{
}

AddElementCommand::AddElementCommand(Element* e, View* view)
    : m_ix(0)
    , m_element_to_add(e)
    , m_doc(view->get_doc())
{
#ifdef VERBOSE
    printf("Construct AddElementCommand\n");
#endif
}

AddElementCommand::~AddElementCommand()
{
#ifdef VERBOSE
    printf("Destroy AddElementCommand\n");
#endif
    if (m_element_to_add != NULL)
        delete m_element_to_add;
}

void AddElementCommand::execute()
{
#ifdef VERBOSE
    printf("Execute AddElementCommand\n");
#endif
    m_ix = m_doc->elements();
    m_doc->add_element(m_element_to_add);
    m_element_to_add = NULL;
}

void AddElementCommand::unexecute()
{
#ifdef VERBOSE
    printf("Unexecute AddElementCommand\n");
#endif
    m_element_to_add = m_doc->remove_element(m_ix);
}

RemoveElementCommand::RemoveElementCommand(int ix, View* view)
    : m_ix(ix)
    , m_removed_element(NULL)
    , m_doc(view->get_doc())
{
#ifdef VERBOSE
    printf("Construct RemoveElementCommand\n");
#endif
}

RemoveElementCommand::~RemoveElementCommand()
{
#ifdef VERBOSE
    printf("Destroy RemoveElementCommand\n");
#endif
    if (m_removed_element != NULL)
        delete m_removed_element;
}

void RemoveElementCommand::execute()
{
#ifdef VERBOSE
    printf("Execute RemoveElementCommand\n");
#endif
    m_removed_element = m_doc->remove_element(m_ix);
}

void RemoveElementCommand::unexecute()
{
#ifdef VERBOSE
    printf("Unexecute RemoveElementCommand\n");
#endif
    m_doc->add_element(m_removed_element, m_ix);
    m_removed_element = NULL;
}

LoadCommand::LoadCommand(const QString& file_name, View* view)
    : m_file_name(file_name)
    , m_view(view)
    , m_new_doc(new Document(file_name))
    , m_replaced_doc(NULL)
{
#ifdef VERBOSE
    printf("Construct LoadCommand('%s')\n", m_file_name.toLatin1().data());
#endif
}

LoadCommand::~LoadCommand()
{
#ifdef VERBOSE
    printf("Destroy LoadCommand('%s')\n", m_file_name.toLatin1().data());
#endif
    if (m_new_doc != NULL)
        delete m_new_doc;
    if (m_replaced_doc != NULL)
        delete m_replaced_doc;
}

void LoadCommand::execute()
{
#ifdef VERBOSE
    printf("Execute LoadCommand('%s')\n", m_file_name.toLatin1().data());
#endif
    m_new_doc->make_dirty();
    m_replaced_doc = m_view->replace_doc(m_new_doc);
    m_new_doc = NULL;
}

void LoadCommand::unexecute()
{
#ifdef VERBOSE
    printf("Unexecute LoadCommand('%s')\n", m_file_name.toLatin1().data());
#endif
    m_replaced_doc->make_dirty();
    m_new_doc = m_view->replace_doc(m_replaced_doc);
    m_replaced_doc = NULL;
}
