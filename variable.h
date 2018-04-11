#ifndef VARIABLE_H
#define VARIABLE_H
#include <QList>
#include <QDebug>
#include <QChar>

class Variable
{
public:
    Variable(QChar name);
    Variable(QChar name, int numberVariables, int positionVariable);
    Variable(QChar name, QList<bool> *vars);

    //operations
    Variable & operator=(Variable & v);

    void setName(QChar name);
    void setVars(QList<bool> *vars);
    void setVars(int index, int size);

    QChar getName();
    QList<bool> *getVars();

private:
    void debugVars();
    int pow2(int power);
    QChar name_;
    QList<bool> *vars_;
};

#endif // VARIABLE_H
