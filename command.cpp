
#include "command.h"
#include <stdio.h>

Command::~Command()
{
}

AddElementCommand::AddElementCommand(Element* e, Document* doc)
    : m_ix(0)
    , m_element_to_add(e)
    , m_doc(doc)
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

RemoveElementCommand::RemoveElementCommand(int ix, Document* doc)
    : m_ix(ix)
    , m_removed_element(NULL)
    , m_doc(doc)
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


