#ifndef VARIABLE_H
#define VARIABLE_H
#include <QList>
#include <QDebug>
#include <QChar>

class Variable
{
public:
    Variable(QChar name);
    Variable(QString name);
    Variable(QChar name, int numberVariables, int positionVariable);
    Variable(QChar name, QList<bool> *vars);

    //Some logical operations cannot be easily converted to statements
    //Therefore, operators have replaced by basic functions
    Variable conjunction(Variable other);
    Variable disjunction(Variable other);
    Variable implication(Variable other);
    Variable converse(Variable other);
    Variable notAnd(Variable other);
    Variable notOr(Variable other);
    Variable exclusiveDisjunction(Variable other);
    Variable equivalent(Variable other);
    Variable negation();

    void setName(QString name);
    void setVars(QList<bool> vars);
    void setVars(int index, int size);

    QString getName();
    QList<bool> getVars();

private:
    void debugVars();
    int pow2(int power);
    QString makeName(QString first, QString operation, QString second);
    QString name_;
    QList<bool> vars_;
};

#endif // VARIABLE_H
