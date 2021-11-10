
#ifndef _COMMAND_H_
#define _COMMAND_H

#include <QString>

class Command
{
public:
    virtual ~Command();
    virtual void execute() = 0;
    virtual void unexecute() = 0;
};

class AddBrickCommand: public Command
{
public:
    AddBrickCommand(const QString& msg);
    ~AddBrickCommand();
    void execute() override;
    void unexecute() override;
private:
    QString m_msg;
};

#endif // _COMMAND_H_
