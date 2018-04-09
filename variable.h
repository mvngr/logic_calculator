#ifndef VARIABLE_H
#define VARIABLE_H
#include <QList>
#include <QDebug>

class Variable
{
public:
    Variable(char name);
    Variable(char name, int numberVariables, int positionVariable);
    Variable(char name, QList<bool> *vars);

    //operations

    void setName(char name);
    void setVars(QList<bool> *vars);
    void setVars(int numberVariables, int positionVariable);

    char getName();
    QList<bool> *getVars();

private:
    void debugVars();
    int pow2(int power);
    char name_;
    QList<bool> *vars_;
};

#endif // VARIABLE_H
