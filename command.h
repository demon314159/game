
#ifndef _COMMAND_H_
#define _COMMAND_H

class Command
{
public:
    virtual ~Command();
    virtual void execute() = 0;
    virtual void unexecute() = 0;
};

class AddPieceCommand: public Command
{
public:
    AddPieceCommand(int pix, int pid, int orientation, int posh, int posv);
    ~AddPieceCommand();
    void execute() override;
    void unexecute() override;
private:
    int m_pix;
};

class RemovePieceCommand: public Command
{
public:
    RemovePieceCommand(int pix);
    ~RemovePieceCommand();
    void execute() override;
    void unexecute() override;
private:
    int m_pix;
};

class NextChallengeCommand: public Command
{
public:
    NextChallengeCommand();
    ~NextChallengeCommand();
    void execute() override;
    void unexecute() override;
private:
};

#endif // _COMMAND_H_
