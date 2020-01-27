#ifndef VARIABLE_H
#define VARIABLE_H
#include <QList>
#include <QDebug>
#include <QChar>

class Variable
{
public:
    Variable(const QChar name);
    Variable(const QString &name);
    Variable(const QChar name, const QList<bool> *vars);
    Variable(QChar name, int numberVariables, int positionVariable);

    //Some logical operations cannot be easily converted to statements
    //Therefore, operators have replaced by basic functions
    Variable conjunction(const Variable &other) const;
    Variable disjunction(const Variable &other) const;
    Variable implication(const Variable &other) const;
    Variable converse(const Variable &other) const;
    Variable notAnd(const Variable &other) const;
    Variable notOr(const Variable &other) const;
    Variable exclusiveDisjunction(const Variable &other) const;
    Variable equivalent(const Variable &other) const;
    Variable negation();

    void setName(const QString &name);
    void setVars(const QList<bool> &vars);
    void setVars(const int index, const int size);

    QString getName() const;
    QList<bool> getVars() const;

    bool operator > (const Variable &other);
    bool operator < (const Variable &other);

private:
    void debugVars();
    int pow2(const int power) const;
    QString makeName(const QString &first, const QString &operation, const QString &second) const;
    QString name_;
    QList<bool> vars_;
};

#endif // VARIABLE_H
