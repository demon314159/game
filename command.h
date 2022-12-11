
#ifndef _COMMAND_H_
#define _COMMAND_H

class Command
{
public:
    virtual ~Command();
    virtual void execute() = 0;
    virtual void unexecute() = 0;
};

class DropPieceCommand: public Command
{
public:
    DropPieceCommand(int pix, int orientation, int posh, int posv);
    ~DropPieceCommand();
    void execute() override;
    void unexecute() override;
private:
    int m_pix;
};

class LiftPieceCommand: public Command
{
public:
    LiftPieceCommand(int pix);
    ~LiftPieceCommand();
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
